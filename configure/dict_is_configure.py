
configure = {
	'PROJECT_NAME': 'dict',
	'TYPE_NAME': 'is', 

	'INCLUDE_FILE_SUFFIX': '.h', 
	'SRC_FILE_SUFFIX': '.c', 

	'INCLUDE_HEAD': '''
	''',
	'SRC_HEAD': '''
	#include <string.h>
	#include <stdio.h>
	''', 

	'KEY_TYPE': 'int', 
	'VALUE_TYPE': 'char*', 

	'KEY_ALLOCATOR': '''
	*key_dup = key;
	return 0;
	''', 

	'VALUE_ALLOCATOR': '''
	*value_dup = strdup(value);
	return 0;
	''', 

	'KEY_DEALLOCATOR': '''
	return 0;
	''', 

	'VALUE_DEALLOCATOR': '''
	free(value);
	return 0;
	''', 

	'KEY_COMPARATOR': '''
	if (key_1 > key_2)
		return 1;
	else if (key_1 < key_2)
		return -1;
	else
		return 0;
	''', 

	'KEY_PRINTOR': '''
	printf("%d", key);
	''', 

	'VALUE_PRINTOR': '''
	printf("'%s'", value);
	''', 
}

try:
	configure['TYPE_NAME_U'] = configure['TYPE_NAME'].upper()
except Exception as e:
	print 'Missing configure parameter. (%s)' % e
