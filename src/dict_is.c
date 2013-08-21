#include <dict/dict_is.h>

#include <string.h>
	#include <stdio.h>

#define DICT_KEY_TYPE		int
#define DICT_VALUE_TYPE		char*
#include <dict.h>

static int dict_key_allocator_is(int key, int* key_dup)
{
	*key_dup = key;
	return 0;
}

static int dict_value_allocator_is(char* value, char** value_dup)
{
	*value_dup = strdup(value);
	return 0;
}

static int dict_key_deallocator_is(int key)
{
	return 0;
}

static int dict_value_deallocator_is(char* value)
{
	free(value);
	return 0;
}

static int dict_key_comparator_is(int key_1, int key_2)
{
	if (key_1 > key_2)
		return 1;
	else if (key_1 < key_2)
		return -1;
	else
		return 0;
}

static void dict_key_printor_is(int key)
{
	printf("%d", key);
}

static void dict_value_printor_is(char* value)
{
	printf("'%s'", value);
}

dict_context_is_t* dict_new_is(void)
{
	return dict_new_length_is(DICT_LENGTH_DEFAULT);
}

dict_context_is_t* dict_new_length_is(size_t length)
{
	return dict_new(length, 
		dict_key_allocator_is, dict_value_allocator_is, 
		dict_key_deallocator_is, dict_value_deallocator_is, 
		dict_key_comparator_is, 
		dict_key_printor_is, dict_value_printor_is);
}

void dict_delete_is(dict_context_is_t* context)
{
	dict_delete(context);
}

dict_context_is_t* dict_retain_is(dict_context_is_t* context)
{
	return dict_retain(context);
}

size_t dict_retain_count_is(dict_context_is_t* context)
{
	return dict_retain_count(context);
}

dict_context_is_t* dict_copy_is(dict_context_is_t* context)
{
	return dict_copy(context);
}

int dict_set_is(dict_context_is_t* context, int key, char* value)
{
	return dict_set(context, key, value);
}

int dict_get_is(dict_context_is_t* context, int key, char** value)
{
	return dict_get(context, key, value);
}

int dict_remove_is(dict_context_is_t* context, int key)
{
	return dict_remove(context, key);
}

int dict_clear_is(dict_context_is_t* context)
{
	return dict_clear(context);
}

int dict_has_key_is(dict_context_is_t* context, int key)
{
	return dict_has_key(context, key);
}

size_t dict_count_is(dict_context_is_t* context)
{
	return dict_count(context);
}

dict_iter_is_t* dict_iter_new_is(dict_context_is_t* context)
{
	return dict_iter_new(context);	
}

int dict_iter_get_is(dict_iter_is_t* iter, int* key, char** value)
{
	return dict_iter_get(iter, key, value);
}

void dict_iter_delete_is(dict_iter_is_t* iter)
{
	dict_iter_delete(iter);
}

void dict_print_is(dict_context_is_t* context)
{
	dict_print(context);
}