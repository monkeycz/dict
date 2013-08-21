#include <dict/dict_ss.h>

#include <string.h>
	#include <stdio.h>

#define DICT_KEY_TYPE		char*
#define DICT_VALUE_TYPE		char*
#include <dict.h>

static int dict_key_allocator_ss(char* key, char** key_dup)
{
	*key_dup = strdup(key);
	return 0;
}

static int dict_value_allocator_ss(char* value, char** value_dup)
{
	*value_dup = strdup(value);
	return 0;
}

static int dict_key_deallocator_ss(char* key)
{
	free(key);
	return 0;
}

static int dict_value_deallocator_ss(char* value)
{
	free(value);
	return 0;
}

static int dict_key_comparator_ss(char* key_1, char* key_2)
{
	return strcmp(key_1, key_2);
}

static void dict_key_printor_ss(char* key)
{
	printf("'%s'", key);
}

static void dict_value_printor_ss(char* value)
{
	printf("'%s'", value);
}

dict_context_ss_t* dict_new_ss(void)
{
	return dict_new_length_ss(DICT_LENGTH_DEFAULT);
}

dict_context_ss_t* dict_new_length_ss(size_t length)
{
	return dict_new(length, 
		dict_key_allocator_ss, dict_value_allocator_ss, 
		dict_key_deallocator_ss, dict_value_deallocator_ss, 
		dict_key_comparator_ss, 
		dict_key_printor_ss, dict_value_printor_ss);
}

void dict_delete_ss(dict_context_ss_t* context)
{
	dict_delete(context);
}

dict_context_ss_t* dict_retain_ss(dict_context_ss_t* context)
{
	return dict_retain(context);
}

size_t dict_retain_count_ss(dict_context_ss_t* context)
{
	return dict_retain_count(context);
}

dict_context_ss_t* dict_copy_ss(dict_context_ss_t* context)
{
	return dict_copy(context);
}

int dict_set_ss(dict_context_ss_t* context, char* key, char* value)
{
	return dict_set(context, key, value);
}

int dict_get_ss(dict_context_ss_t* context, char* key, char** value)
{
	return dict_get(context, key, value);
}

int dict_remove_ss(dict_context_ss_t* context, char* key)
{
	return dict_remove(context, key);
}

int dict_clear_ss(dict_context_ss_t* context)
{
	return dict_clear(context);
}

int dict_has_key_ss(dict_context_ss_t* context, char* key)
{
	return dict_has_key(context, key);
}

size_t dict_count_ss(dict_context_ss_t* context)
{
	return dict_count(context);
}

dict_iter_ss_t* dict_iter_new_ss(dict_context_ss_t* context)
{
	return dict_iter_new(context);	
}

int dict_iter_get_ss(dict_iter_ss_t* iter, char** key, char** value)
{
	return dict_iter_get(iter, key, value);
}

void dict_iter_delete_ss(dict_iter_ss_t* iter)
{
	dict_iter_delete(iter);
}

void dict_print_ss(dict_context_ss_t* context)
{
	dict_print(context);
}