
configure = {
	'PROJECT_NAME': 'dict',
	'TYPE_NAME': 'pn',  

	'INCLUDE_FILE_SUFFIX': '.h', 
	'SRC_FILE_SUFFIX': '.m', 

	'INCLUDE_HEAD': '''
	@class NSObject;
	''',
	'SRC_HEAD': '''
	#import <Foundation/Foundation.h>
	#include <stdio.h>
	''', 

	'KEY_TYPE': 'void*', 
	'VALUE_TYPE': 'NSObject*',

	'KEY_ALLOCATOR': '''
	*key_dup = key;
	return 0;
	''', 

	'VALUE_ALLOCATOR': '''
	*value_dup = [value retain];
	return 0;
	''', 

	'KEY_DEALLOCATOR': '''
	return 0;
	''', 

	'VALUE_DEALLOCATOR': '''
	[value release];
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
	printf("<%p>", key);
	''', 

	'VALUE_PRINTOR': '''
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	printf("%s", [[value description] UTF8String]);
	[pool release];
	''', 
}

try:
	configure['TYPE_NAME_U'] = configure['TYPE_NAME'].upper()
except Exception as e:
	print 'Missing configure parameter. (%s)' % e
