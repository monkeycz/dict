
configure = {
	'PROJECT_NAME': 'dict',
	'TYPE_NAME': 'ss', 

	'INCLUDE_FILE_SUFFIX': '.h', 
	'SRC_FILE_SUFFIX': '.c', 

	'INCLUDE_HEAD': '''
	''',
	'SRC_HEAD': '''
	#include <string.h>
	#include <stdio.h>
	''', 

	'KEY_TYPE': 'char*', 
	'VALUE_TYPE': 'char*', 

	'KEY_ALLOCATOR': '''
	*key_dup = strdup(key);
	return 0;
	''', 

	'VALUE_ALLOCATOR': '''
	*value_dup = strdup(value);
	return 0;
	''', 

	'KEY_DEALLOCATOR': '''
	free(key);
	return 0;
	''', 

	'VALUE_DEALLOCATOR': '''
	free(value);
	return 0;
	''', 

	'KEY_COMPARATOR': '''
	return strcmp(key_1, key_2);
	''', 

	'KEY_PRINTOR': '''
	printf("'%s'", key);
	''', 

	'VALUE_PRINTOR': '''
	printf("'%s'", value);
	''', 
}

try:
	configure['TYPE_NAME_U'] = configure['TYPE_NAME'].upper()
except Exception as e:
	print 'Missing configure parameter. (%s)' % e
