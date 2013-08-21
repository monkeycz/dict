#include <dict/dict_ii.h>

#include <stdio.h>

#define DICT_KEY_TYPE		int
#define DICT_VALUE_TYPE		int
#include <dict.h>

static int dict_key_allocator_ii(int key, int* key_dup)
{
	*key_dup = key;
	return 0;
}

static int dict_value_allocator_ii(int value, int* value_dup)
{
	*value_dup = value;
	return 0;
}

static int dict_key_deallocator_ii(int key)
{
	return 0;
}

static int dict_value_deallocator_ii(int value)
{
	return 0;
}

static int dict_key_comparator_ii(int key_1, int key_2)
{
	if (key_1 > key_2)
		return 1;
	else if (key_1 < key_2)
		return -1;
	else
		return 0;
}

static void dict_key_printor_ii(int key)
{
	printf("%d", key);
}

static void dict_value_printor_ii(int value)
{
	printf("%d", value);
}

dict_context_ii_t* dict_new_ii(void)
{
	return dict_new_length_ii(DICT_LENGTH_DEFAULT);
}

dict_context_ii_t* dict_new_length_ii(size_t length)
{
	return dict_new(length, 
		dict_key_allocator_ii, dict_value_allocator_ii, 
		dict_key_deallocator_ii, dict_value_deallocator_ii, 
		dict_key_comparator_ii, 
		dict_key_printor_ii, dict_value_printor_ii);
}

void dict_delete_ii(dict_context_ii_t* context)
{
	dict_delete(context);
}

dict_context_ii_t* dict_retain_ii(dict_context_ii_t* context)
{
	return dict_retain(context);
}

size_t dict_retain_count_ii(dict_context_ii_t* context)
{
	return dict_retain_count(context);
}

dict_context_ii_t* dict_copy_ii(dict_context_ii_t* context)
{
	return dict_copy(context);
}

int dict_set_ii(dict_context_ii_t* context, int key, int value)
{
	return dict_set(context, key, value);
}

int dict_get_ii(dict_context_ii_t* context, int key, int* value)
{
	return dict_get(context, key, value);
}

int dict_remove_ii(dict_context_ii_t* context, int key)
{
	return dict_remove(context, key);
}

int dict_clear_ii(dict_context_ii_t* context)
{
	return dict_clear(context);
}

int dict_has_key_ii(dict_context_ii_t* context, int key)
{
	return dict_has_key(context, key);
}

size_t dict_count_ii(dict_context_ii_t* context)
{
	return dict_count(context);
}

dict_iter_ii_t* dict_iter_new_ii(dict_context_ii_t* context)
{
	return dict_iter_new(context);	
}

int dict_iter_get_ii(dict_iter_ii_t* iter, int* key, int* value)
{
	return dict_iter_get(iter, key, value);
}

void dict_iter_delete_ii(dict_iter_ii_t* iter)
{
	dict_iter_delete(iter);
}

void dict_print_ii(dict_context_ii_t* context)
{
	dict_print(context);
}