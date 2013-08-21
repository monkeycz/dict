
include_template = '''
#ifndef DICT_{TYPE_NAME_U}_H
#define DICT_{TYPE_NAME_U}_H

#include <stdlib.h>

{INCLUDE_HEAD}

typedef struct dict_context dict_context_{TYPE_NAME}_t;
typedef struct dict_iter dict_iter_{TYPE_NAME}_t;

#ifdef __cplusplus
extern "C" {
#endif

dict_context_{TYPE_NAME}_t* dict_new_{TYPE_NAME}(void);
dict_context_{TYPE_NAME}_t* dict_new_length_{TYPE_NAME}(size_t length);
void dict_delete_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context);

dict_context_{TYPE_NAME}_t* dict_retain_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context);
size_t dict_retain_count_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context);

dict_context_{TYPE_NAME}_t* dict_copy_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context);

int dict_set_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context, {KEY_TYPE} key, {VALUE_TYPE} value);
int dict_get_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context, {KEY_TYPE} key, {VALUE_TYPE}* value);

int dict_remove_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context, {KEY_TYPE} key);
int dict_clear_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context);

int dict_has_key_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context, {KEY_TYPE} key);
size_t dict_count_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context);

dict_iter_{TYPE_NAME}_t* dict_iter_new_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context);
int dict_iter_get_{TYPE_NAME}(dict_iter_{TYPE_NAME}_t* iter, {KEY_TYPE}* key, {VALUE_TYPE}* value);
void dict_iter_delete_{TYPE_NAME}(dict_iter_{TYPE_NAME}_t* iter);

void dict_print_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context);

#ifdef __cplusplus
}
#endif

#endif /* DICT_{TYPE_NAME_U}_H */
'''

src_template = '''
#include <dict/dict_{TYPE_NAME}.h>

{SRC_HEAD}

#define DICT_KEY_TYPE		{KEY_TYPE}
#define DICT_VALUE_TYPE		{VALUE_TYPE}
#include <dict.h>

static int dict_key_allocator_{TYPE_NAME}({KEY_TYPE} key, {KEY_TYPE}* key_dup)
{
	{KEY_ALLOCATOR}
}

static int dict_value_allocator_{TYPE_NAME}({VALUE_TYPE} value, {VALUE_TYPE}* value_dup)
{
	{VALUE_ALLOCATOR}
}

static int dict_key_deallocator_{TYPE_NAME}({KEY_TYPE} key)
{
	{KEY_DEALLOCATOR}
}

static int dict_value_deallocator_{TYPE_NAME}({VALUE_TYPE} value)
{
	{VALUE_DEALLOCATOR}
}

static int dict_key_comparator_{TYPE_NAME}({KEY_TYPE} key_1, {KEY_TYPE} key_2)
{
	{KEY_COMPARATOR}
}

static void dict_key_printor_{TYPE_NAME}({KEY_TYPE} key)
{
	{KEY_PRINTOR}
}

static void dict_value_printor_{TYPE_NAME}({VALUE_TYPE} value)
{
	{VALUE_PRINTOR}
}

dict_context_{TYPE_NAME}_t* dict_new_{TYPE_NAME}(void)
{
	return dict_new_length_{TYPE_NAME}(DICT_LENGTH_DEFAULT);
}

dict_context_{TYPE_NAME}_t* dict_new_length_{TYPE_NAME}(size_t length)
{
	return dict_new(length, 
		dict_key_allocator_{TYPE_NAME}, dict_value_allocator_{TYPE_NAME}, 
		dict_key_deallocator_{TYPE_NAME}, dict_value_deallocator_{TYPE_NAME}, 
		dict_key_comparator_{TYPE_NAME}, 
		dict_key_printor_{TYPE_NAME}, dict_value_printor_{TYPE_NAME});
}

void dict_delete_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context)
{
	dict_delete(context);
}

dict_context_{TYPE_NAME}_t* dict_retain_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context)
{
	return dict_retain(context);
}

size_t dict_retain_count_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context)
{
	return dict_retain_count(context);
}

dict_context_{TYPE_NAME}_t* dict_copy_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context)
{
	return dict_copy(context);
}

int dict_set_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context, {KEY_TYPE} key, {VALUE_TYPE} value)
{
	return dict_set(context, key, value);
}

int dict_get_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context, {KEY_TYPE} key, {VALUE_TYPE}* value)
{
	return dict_get(context, key, value);
}

int dict_remove_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context, {KEY_TYPE} key)
{
	return dict_remove(context, key);
}

int dict_clear_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context)
{
	return dict_clear(context);
}

int dict_has_key_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context, {KEY_TYPE} key)
{
	return dict_has_key(context, key);
}

size_t dict_count_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context)
{
	return dict_count(context);
}

dict_iter_{TYPE_NAME}_t* dict_iter_new_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context)
{
	return dict_iter_new(context);	
}

int dict_iter_get_{TYPE_NAME}(dict_iter_{TYPE_NAME}_t* iter, {KEY_TYPE}* key, {VALUE_TYPE}* value)
{
	return dict_iter_get(iter, key, value);
}

void dict_iter_delete_{TYPE_NAME}(dict_iter_{TYPE_NAME}_t* iter)
{
	dict_iter_delete(iter);
}

void dict_print_{TYPE_NAME}(dict_context_{TYPE_NAME}_t* context)
{
	dict_print(context);
}
'''

import sys, imp

def main():
	args = sys.argv[1:]
	if len(args) < 1:
		print '%s <configure_name>' % __file__
		print 'eg: %s xxxx_xx_configure' % __file__
		return

	try:
		configure_name = args[0]
		configure = imp.load_module(configure_name, *imp.find_module(configure_name)).configure
	except Exception as e:
		print 'Invalid configure file. (%s)' % e
		return

	try:
		include_filename = '%s_%s%s' % \
			(configure['PROJECT_NAME'], configure['TYPE_NAME'], configure['INCLUDE_FILE_SUFFIX'])
		with open(include_filename, 'w+') as f:
			global include_template
			include_code = include_template.strip()
			for k, v in configure.items():
				include_code = include_code.replace('{' + k + '}', v.strip())
			f.write(include_code)

		src_filename = '%s_%s%s' % \
			(configure['PROJECT_NAME'], configure['TYPE_NAME'], configure['SRC_FILE_SUFFIX'])
		with open(src_filename, 'w+') as f:
			global src_template
			src_code = src_template.strip()
			for k, v in configure.items():
				src_code = src_code.replace('{' + k + '}', v.strip())
			f.write(src_code)
	except Exception as e:
		print 'Failed to generate the code. (%s)' % e
		return

	print 'ok'
	print include_filename
	print src_filename

if __name__ == '__main__':
	main()
