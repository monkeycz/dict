#include <dict/dict_pp.h>

#include <stdio.h>

#define DICT_KEY_TYPE		void*
#define DICT_VALUE_TYPE		void*
#include <dict.h>

static int dict_key_allocator_pp(void* key, void** key_dup)
{
	*key_dup = key;
	return 0;
}

static int dict_value_allocator_pp(void* value, void** value_dup)
{
	*value_dup = value;
	return 0;
}

static int dict_key_deallocator_pp(void* key)
{
	return 0;
}

static int dict_value_deallocator_pp(void* value)
{
	return 0;
}

static int dict_key_comparator_pp(void* key_1, void* key_2)
{
	if (key_1 > key_2)
		return 1;
	else if (key_1 < key_2)
		return -1;
	else
		return 0;
}

static void dict_key_printor_pp(void* key)
{
	printf("<%p>", key);
}

static void dict_value_printor_pp(void* value)
{
	printf("<%p>", value);
}

dict_context_pp_t* dict_new_pp(void)
{
	return dict_new_length_pp(DICT_LENGTH_DEFAULT);
}

dict_context_pp_t* dict_new_length_pp(size_t length)
{
	return dict_new(length, 
		dict_key_allocator_pp, dict_value_allocator_pp, 
		dict_key_deallocator_pp, dict_value_deallocator_pp, 
		dict_key_comparator_pp, 
		dict_key_printor_pp, dict_value_printor_pp);
}

void dict_delete_pp(dict_context_pp_t* context)
{
	dict_delete(context);
}

dict_context_pp_t* dict_retain_pp(dict_context_pp_t* context)
{
	return dict_retain(context);
}

size_t dict_retain_count_pp(dict_context_pp_t* context)
{
	return dict_retain_count(context);
}

dict_context_pp_t* dict_copy_pp(dict_context_pp_t* context)
{
	return dict_copy(context);
}

int dict_set_pp(dict_context_pp_t* context, void* key, void* value)
{
	return dict_set(context, key, value);
}

int dict_get_pp(dict_context_pp_t* context, void* key, void** value)
{
	return dict_get(context, key, value);
}

int dict_remove_pp(dict_context_pp_t* context, void* key)
{
	return dict_remove(context, key);
}

int dict_clear_pp(dict_context_pp_t* context)
{
	return dict_clear(context);
}

int dict_has_key_pp(dict_context_pp_t* context, void* key)
{
	return dict_has_key(context, key);
}

size_t dict_count_pp(dict_context_pp_t* context)
{
	return dict_count(context);
}

dict_iter_pp_t* dict_iter_new_pp(dict_context_pp_t* context)
{
	return dict_iter_new(context);	
}

int dict_iter_get_pp(dict_iter_pp_t* iter, void** key, void** value)
{
	return dict_iter_get(iter, key, value);
}

void dict_iter_delete_pp(dict_iter_pp_t* iter)
{
	dict_iter_delete(iter);
}

void dict_print_pp(dict_context_pp_t* context)
{
	dict_print(context);
}