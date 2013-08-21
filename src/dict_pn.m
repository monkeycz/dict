#include <dict/dict_pn.h>

#import <Foundation/Foundation.h>
	#include <stdio.h>

#define DICT_KEY_TYPE		void*
#define DICT_VALUE_TYPE		NSObject*
#include <dict.h>

static int dict_key_allocator_pn(void* key, void** key_dup)
{
	*key_dup = key;
	return 0;
}

static int dict_value_allocator_pn(NSObject* value, NSObject** value_dup)
{
	*value_dup = [value retain];
	return 0;
}

static int dict_key_deallocator_pn(void* key)
{
	return 0;
}

static int dict_value_deallocator_pn(NSObject* value)
{
	[value release];
	return 0;
}

static int dict_key_comparator_pn(void* key_1, void* key_2)
{
	if (key_1 > key_2)
		return 1;
	else if (key_1 < key_2)
		return -1;
	else
		return 0;
}

static void dict_key_printor_pn(void* key)
{
	printf("<%p>", key);
}

static void dict_value_printor_pn(NSObject* value)
{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	printf("%s", [[value description] UTF8String]);
	[pool release];
}

dict_context_pn_t* dict_new_pn(void)
{
	return dict_new_length_pn(DICT_LENGTH_DEFAULT);
}

dict_context_pn_t* dict_new_length_pn(size_t length)
{
	return dict_new(length, 
		dict_key_allocator_pn, dict_value_allocator_pn, 
		dict_key_deallocator_pn, dict_value_deallocator_pn, 
		dict_key_comparator_pn, 
		dict_key_printor_pn, dict_value_printor_pn);
}

void dict_delete_pn(dict_context_pn_t* context)
{
	dict_delete(context);
}

dict_context_pn_t* dict_retain_pn(dict_context_pn_t* context)
{
	return dict_retain(context);
}

size_t dict_retain_count_pn(dict_context_pn_t* context)
{
	return dict_retain_count(context);
}

dict_context_pn_t* dict_copy_pn(dict_context_pn_t* context)
{
	return dict_copy(context);
}

int dict_set_pn(dict_context_pn_t* context, void* key, NSObject* value)
{
	return dict_set(context, key, value);
}

int dict_get_pn(dict_context_pn_t* context, void* key, NSObject** value)
{
	return dict_get(context, key, value);
}

int dict_remove_pn(dict_context_pn_t* context, void* key)
{
	return dict_remove(context, key);
}

int dict_clear_pn(dict_context_pn_t* context)
{
	return dict_clear(context);
}

int dict_has_key_pn(dict_context_pn_t* context, void* key)
{
	return dict_has_key(context, key);
}

size_t dict_count_pn(dict_context_pn_t* context)
{
	return dict_count(context);
}

dict_iter_pn_t* dict_iter_new_pn(dict_context_pn_t* context)
{
	return dict_iter_new(context);	
}

int dict_iter_get_pn(dict_iter_pn_t* iter, void** key, NSObject** value)
{
	return dict_iter_get(iter, key, value);
}

void dict_iter_delete_pn(dict_iter_pn_t* iter)
{
	dict_iter_delete(iter);
}

void dict_print_pn(dict_context_pn_t* context)
{
	dict_print(context);
}