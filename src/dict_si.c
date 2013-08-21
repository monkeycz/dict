#include <dict/dict_si.h>

#include <string.h>
	#include <stdio.h>

#define DICT_KEY_TYPE		char*
#define DICT_VALUE_TYPE		int
#include <dict.h>

static int dict_key_allocator_si(char* key, char** key_dup)
{
	*key_dup = strdup(key);
	return 0;
}

static int dict_value_allocator_si(int value, int* value_dup)
{
	*value_dup = value;
	return 0;
}

static int dict_key_deallocator_si(char* key)
{
	free(key);
	return 0;
}

static int dict_value_deallocator_si(int value)
{
	return 0;
}

static int dict_key_comparator_si(char* key_1, char* key_2)
{
	return strcmp(key_1, key_2);
}

static void dict_key_printor_si(char* key)
{
	printf("'%s'", key);
}

static void dict_value_printor_si(int value)
{
	printf("%d", value);
}

dict_context_si_t* dict_new_si(void)
{
	return dict_new_length_si(DICT_LENGTH_DEFAULT);
}

dict_context_si_t* dict_new_length_si(size_t length)
{
	return dict_new(length, 
		dict_key_allocator_si, dict_value_allocator_si, 
		dict_key_deallocator_si, dict_value_deallocator_si, 
		dict_key_comparator_si, 
		dict_key_printor_si, dict_value_printor_si);
}

void dict_delete_si(dict_context_si_t* context)
{
	dict_delete(context);
}

dict_context_si_t* dict_retain_si(dict_context_si_t* context)
{
	return dict_retain(context);
}

size_t dict_retain_count_si(dict_context_si_t* context)
{
	return dict_retain_count(context);
}

dict_context_si_t* dict_copy_si(dict_context_si_t* context)
{
	return dict_copy(context);
}

int dict_set_si(dict_context_si_t* context, char* key, int value)
{
	return dict_set(context, key, value);
}

int dict_get_si(dict_context_si_t* context, char* key, int* value)
{
	return dict_get(context, key, value);
}

int dict_remove_si(dict_context_si_t* context, char* key)
{
	return dict_remove(context, key);
}

int dict_clear_si(dict_context_si_t* context)
{
	return dict_clear(context);
}

int dict_has_key_si(dict_context_si_t* context, char* key)
{
	return dict_has_key(context, key);
}

size_t dict_count_si(dict_context_si_t* context)
{
	return dict_count(context);
}

dict_iter_si_t* dict_iter_new_si(dict_context_si_t* context)
{
	return dict_iter_new(context);	
}

int dict_iter_get_si(dict_iter_si_t* iter, char** key, int* value)
{
	return dict_iter_get(iter, key, value);
}

void dict_iter_delete_si(dict_iter_si_t* iter)
{
	dict_iter_delete(iter);
}

void dict_print_si(dict_context_si_t* context)
{
	dict_print(context);
}