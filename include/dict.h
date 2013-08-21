#ifndef DICT_H
#define DICT_H

/* ************************** INCLUDE BEGIN *************************** */

#include <stdlib.h>

#ifndef DICT_KEY_TYPE
#error NO define DICT_KEY_TYPE, eg: `#define DICT_KEY_TYPE int`
#endif
#ifndef DICT_VALUE_TYPE
#error NO define DICT_VALUE_TYPE, eg: `#define DICT_VALUE_TYPE int`
#endif

#if 0
#define DICT_KEY_TYPE		void*
#define DICT_VALUE_TYPE		void*
#endif

#define DICT_LENGTH_DEFAULT 1024

typedef struct dict_context dict_context_t;
typedef struct dict_iter dict_iter_t;

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*dict_key_allocator)(DICT_KEY_TYPE, DICT_KEY_TYPE*);
typedef int (*dict_value_allocator)(DICT_VALUE_TYPE, DICT_VALUE_TYPE*);
typedef int (*dict_key_deallocator)(DICT_KEY_TYPE);
typedef int (*dict_value_deallocator)(DICT_VALUE_TYPE);
typedef int (*dict_key_comparator)(DICT_KEY_TYPE, DICT_KEY_TYPE);
typedef void (*dict_key_printor)(DICT_KEY_TYPE);
typedef void (*dict_value_printor)(DICT_VALUE_TYPE);

static dict_context_t* dict_new(size_t length, 
	dict_key_allocator key_allocator, dict_value_allocator value_allocator, 
	dict_key_deallocator key_deallocator, dict_value_deallocator value_deallocator, 
	dict_key_comparator key_comparator, 
	dict_key_printor key_printor, dict_value_printor value_printor);
static void dict_delete(dict_context_t* context);

static dict_context_t* dict_retain(dict_context_t* context);
static size_t dict_retain_count(dict_context_t* context);

static dict_context_t* dict_copy(dict_context_t* context);

static int dict_set(dict_context_t* context, DICT_KEY_TYPE key, DICT_VALUE_TYPE value);
static int dict_get(dict_context_t* context, DICT_KEY_TYPE key, DICT_VALUE_TYPE* value);

static int dict_remove(dict_context_t* context, DICT_KEY_TYPE key);
static int dict_clear(dict_context_t* context);

static int dict_has_key(dict_context_t* context, DICT_KEY_TYPE key);
static size_t dict_count(dict_context_t* context);

static dict_iter_t* dict_iter_new(dict_context_t* context);
static int dict_iter_get(dict_iter_t* iter, DICT_KEY_TYPE* key, DICT_VALUE_TYPE* value);
static void dict_iter_delete(dict_iter_t* iter);

static void dict_print(dict_context_t* context);

#ifdef __cplusplus
}
#endif

/* *************************** INCLUDE END **************************** */

/* **************************** SRC BEGIN ***************************** */

#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>

struct dict_context
{
	pthread_mutex_t mutex;

	size_t retain_count;

	DICT_KEY_TYPE* key_list;
	DICT_VALUE_TYPE* value_list;
	size_t length;
	size_t count;

	dict_key_allocator key_allocator;
	dict_value_allocator value_allocator;
	dict_key_deallocator key_deallocator;
	dict_value_deallocator value_deallocator;
	dict_key_comparator key_comparator;
	dict_key_printor key_printor;
	dict_value_printor value_printor;
};

struct dict_iter
{
	pthread_mutex_t mutex;

	dict_context_t* context;

	size_t count;
	size_t index;
};

static int dict_key_allocator_default(DICT_KEY_TYPE key, DICT_KEY_TYPE* key_dup)
{
	*key_dup = key;
	return 0;
}

static int dict_value_allocator_default(DICT_VALUE_TYPE value, DICT_VALUE_TYPE* value_dup)
{
	*value_dup = value;
	return 0;
}

static int dict_key_deallocator_default(DICT_KEY_TYPE key)
{
	return 0;
}

static int dict_value_deallocator_default(DICT_VALUE_TYPE value)
{
	return 0;
}

static int dict_key_comparator_default(DICT_KEY_TYPE key_1, DICT_KEY_TYPE key_2)
{
	if (key_1 > key_2)
		return 1;
	else if (key_1 < key_2)
		return -1;
	else
		return 0;
}

static void dict_key_printor_default(DICT_KEY_TYPE key)
{
	printf("k");
}

static void dict_value_printor_default(DICT_VALUE_TYPE value)
{
	printf("v");
}

static dict_context_t* dict_new(size_t length, 
	dict_key_allocator key_allocator, dict_value_allocator value_allocator, 
	dict_key_deallocator key_deallocator, dict_value_deallocator value_deallocator, 
	dict_key_comparator key_comparator, 
	dict_key_printor key_printor, dict_value_printor value_printor)
{
	dict_context_t* context = (dict_context_t*)malloc(sizeof(dict_context_t));
	if (context == NULL)
		goto __dict_new_failed_1;

	if (pthread_mutex_init(&context->mutex, NULL) != 0)
		goto __dict_new_failed_2;

	context->retain_count = 1;

	context->key_list = calloc(length, sizeof(DICT_KEY_TYPE));
	if (context->key_list == NULL)
		goto __dict_new_failed_3;
	context->value_list = calloc(length, sizeof(DICT_VALUE_TYPE));
	if (context->value_list == NULL)
		goto __dict_new_failed_4;
	context->length = length;
	context->count = 0;

	context->key_allocator = key_allocator == NULL ? 
		dict_key_allocator_default : key_allocator;
	context->value_allocator = value_allocator == NULL ? 
		dict_value_allocator_default : value_allocator;
	context->key_deallocator = key_deallocator == NULL ? 
		dict_key_deallocator_default : key_deallocator;
	context->value_deallocator = value_deallocator == NULL ? 
		dict_value_deallocator_default : value_deallocator;
	context->key_comparator = key_comparator == NULL ? 
		dict_key_comparator_default : key_comparator;
	context->key_printor = key_printor == NULL ? 
		dict_key_printor_default : key_printor;
	context->value_printor = value_printor == NULL ? 
		dict_value_printor_default : value_printor;

	return context;

__dict_new_failed_5:
	free(context->value_list);

__dict_new_failed_4:
	free(context->key_list);

__dict_new_failed_3:
	pthread_mutex_destroy(&context->mutex);

__dict_new_failed_2:
	free(context);

__dict_new_failed_1:
	return NULL;
}

static void dict_delete(dict_context_t* context)
{
	if (context == NULL)
		return;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return;

	if (context->retain_count > 1) {
		context->retain_count--;
		pthread_mutex_unlock(&context->mutex);
		return;
	}

	for (size_t i = 0; i < context->count; i++) {
		context->key_deallocator(context->key_list[i]);
		context->value_deallocator(context->value_list[i]);
	}

	if (context->key_list != NULL)
		free(context->key_list);
	if (context->value_list != NULL)
		free(context->value_list);

	pthread_mutex_unlock(&context->mutex);

	pthread_mutex_destroy(&context->mutex);

	free(context);
}

static dict_context_t* dict_retain(dict_context_t* context)
{
	if (context == NULL)
		return NULL;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return NULL;

	context->retain_count++;

	pthread_mutex_unlock(&context->mutex);

	return context;
}

static size_t dict_retain_count(dict_context_t* context)
{
	if (context == NULL)
		return 0;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return 0;

	size_t retain_count = context->retain_count;

	pthread_mutex_unlock(&context->mutex);

	return retain_count;
}

static dict_context_t* dict_copy(dict_context_t* context)
{
	if (context == NULL)
		return NULL;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return NULL;

	dict_context_t* new_context = dict_new(context->length, 
		context->key_allocator, context->value_allocator, 
		context->key_deallocator, context->value_deallocator, 
		context->key_comparator, 
		context->key_printor, context->value_printor);
	if (new_context != NULL) {
		for (size_t i = 0; i < context->count; i++) {
			if (dict_set(new_context, context->key_list[i], context->value_list[i]) != 0) {
				dict_delete(new_context);
				new_context = NULL;
				break;
			}
		}
	}

	pthread_mutex_unlock(&context->mutex);

	return new_context;
}

static int dict_set(dict_context_t* context, DICT_KEY_TYPE key, DICT_VALUE_TYPE value)
{
	if (context == NULL)
		goto __dict_set_failed_1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		goto __dict_set_failed_1;

	bool is_existed = false;
	DICT_KEY_TYPE key_dup;
	DICT_VALUE_TYPE value_dup;

	for (size_t i = 0; i < context->count; i++) {
		if (context->key_comparator(context->key_list[i], key) == 0) {
			is_existed = true;

			if (context->value_allocator(value, &value_dup) != 0)
				goto __dict_set_failed_2;
			if (context->value_deallocator(context->value_list[i]) != 0)
				goto __dict_set_failed_3;

			context->value_list[i] = value_dup;
			break;
		}
	}

	if (!is_existed) {
		if (context->count >= context->length)
			goto __dict_set_failed_2;

		if (context->value_allocator(value, &value_dup) != 0)
			goto __dict_set_failed_2;
		if (context->key_allocator(key, &key_dup) != 0)
			goto __dict_set_failed_3;

		context->key_list[context->count] = key_dup;
		context->value_list[context->count] = value_dup;

		context->count++;
	}

	pthread_mutex_unlock(&context->mutex);

	return 0;

__dict_set_failed_4:
	context->key_deallocator(key_dup);

__dict_set_failed_3:
	context->value_deallocator(value_dup);

__dict_set_failed_2:
	pthread_mutex_unlock(&context->mutex);

__dict_set_failed_1:
	return -1;
}

static int dict_get(dict_context_t* context, DICT_KEY_TYPE key, DICT_VALUE_TYPE* value)
{
	if (context == NULL)
		return -1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return -1;

	bool is_existed = false;

	for (size_t i = 0; i < context->count; i++) {
		if (context->key_comparator(context->key_list[i], key) == 0) {
			is_existed = true;
			if (value != NULL)
				*value = context->value_list[i];
			break;
		}
	}

	pthread_mutex_unlock(&context->mutex);

	return is_existed ? 0 : 1;
}

static int dict_remove(dict_context_t* context, DICT_KEY_TYPE key)
{
	if (context == NULL)
		return -1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return -1;

	bool is_existed = false;

	for (size_t i = 0; i < context->count; i++) {
		if (context->key_comparator(context->key_list[i], key) == 0) {
			is_existed = true;

			context->key_deallocator(context->key_list[i]);
			context->value_deallocator(context->value_list[i]);

			for (size_t l = i; l + 1 < context->count; l++) {
				context->key_list[l] = context->key_list[l + 1];
				context->value_list[l] = context->value_list[l + 1];
			}

			context->count--;
			break;
		}
	}

	pthread_mutex_unlock(&context->mutex);

	return is_existed ? 0 : 1;
}

static int dict_clear(dict_context_t* context)
{
	if (context == NULL)
		return -1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return -1;	

	for (size_t i = 0; i < context->count; i++) {
		context->key_deallocator(context->key_list[i]);
		context->value_deallocator(context->value_list[i]);
	}
	context->count = 0;

	pthread_mutex_unlock(&context->mutex);

	return 0;
}

static int dict_has_key(dict_context_t* context, DICT_KEY_TYPE key)
{
	return dict_get(context, key, NULL) == 0 ? 0 : -1;
}

static size_t dict_count(dict_context_t* context)
{
	if (context == NULL)
		return 0;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return 0;

	size_t count = context->count;

	pthread_mutex_unlock(&context->mutex);

	return count;
}

static dict_iter_t* dict_iter_new(dict_context_t* context)
{
	if (context == NULL)
		goto __dict_iter_new_failed_1;

	dict_iter_t* iter = (dict_iter_t*)malloc(sizeof(dict_iter_t));
	if (iter == NULL)
		goto __dict_iter_new_failed_1;

	if (pthread_mutex_init(&iter->mutex, NULL) != 0)
		goto __dict_iter_new_failed_2;

	iter->context = dict_retain(context);
	if (iter->context == NULL)
		goto __dict_iter_new_failed_3;

	iter->count = iter->context->count;
	iter->index = 0;

	return iter;

__dict_iter_new_failed_4:
	dict_delete(iter->context);

__dict_iter_new_failed_3:
	pthread_mutex_destroy(&iter->mutex);

__dict_iter_new_failed_2:
	free(iter);

__dict_iter_new_failed_1:
	return NULL;
}

static int dict_iter_get(dict_iter_t* iter, DICT_KEY_TYPE* key, DICT_VALUE_TYPE* value)
{
	if (iter == NULL)
		return -1;

	if (pthread_mutex_lock(&iter->mutex) != 0)
		return -1;

	if (iter->count != iter->context->count) {
		pthread_mutex_unlock(&iter->mutex);
		return -1;
	}

	if (iter->index >= iter->count) {
		pthread_mutex_unlock(&iter->mutex);
		return 1;
	}

	if (key != NULL)
		*key = iter->context->key_list[iter->index];
	if (value != NULL)
		*value = iter->context->value_list[iter->index];

	iter->index++;

	pthread_mutex_unlock(&iter->mutex);

	return 0;
}

static void dict_iter_delete(dict_iter_t* iter)
{
	if (iter == NULL)
		return;

	if (pthread_mutex_lock(&iter->mutex) != 0)
		return;

	dict_delete(iter->context);

	pthread_mutex_unlock(&iter->mutex);

	pthread_mutex_destroy(&iter->mutex);

	free(iter);
}

static void dict_print(dict_context_t* context)
{
	if (context == NULL)
		return;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return;

	printf("{");
	for (size_t i = 0; i < context->count; i++) {
		if (i != 0)
			printf(", ");
		context->key_printor(context->key_list[i]);
		printf(": ");
		context->value_printor(context->value_list[i]);
	}
	printf("}\n");

	pthread_mutex_unlock(&context->mutex);
}

/* ***************************** SRC END ****************************** */

#endif /* DICT_H */