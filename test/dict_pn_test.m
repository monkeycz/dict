#include <dict/dict_pn.h>
#include <assert.h>
#import <Foundation/Foundation.h>

int main(int argc, char* argv[])
{
	dict_context_pn_t* dict_context_pn = dict_new_pn();
	assert(dict_context_pn != NULL);

	dict_context_pn_t* dict_context_pn_retain = dict_retain_pn(dict_context_pn);
	assert(dict_retain_count_pn(dict_context_pn) == 2);
	assert(dict_retain_count_pn(dict_context_pn_retain) == 2);
	dict_delete_pn(dict_context_pn_retain);
	assert(dict_retain_count_pn(dict_context_pn) == 1);
	assert(dict_retain_count_pn(dict_context_pn_retain) == 1);

	dict_context_pn_t* dict_context_pn_copy = dict_copy_pn(dict_context_pn);
	assert(dict_context_pn_copy != NULL);
	assert(dict_retain_count_pn(dict_context_pn_copy) == 1);
	dict_delete_pn(dict_context_pn_copy);

	int a = 1; NSObject* aaa = [[NSObject alloc] init];
	int b = 2; NSObject* bbb = [[NSObject alloc] init];
	int c = 3; NSObject* ccc = [[NSObject alloc] init];
	int d = 4; NSObject* ddd = [[NSObject alloc] init];

	for (int i = 0; i < 2; i++) {
		assert(dict_set_pn(dict_context_pn, &a, aaa) == 0);
		assert(dict_set_pn(dict_context_pn, &b, bbb) == 0);
		assert(dict_set_pn(dict_context_pn, &c, ccc) == 0);

		assert(dict_count_pn(dict_context_pn) == 3);

		assert(dict_has_key_pn(dict_context_pn, &a) == 0);
		assert(dict_has_key_pn(dict_context_pn, &b) == 0);
		assert(dict_has_key_pn(dict_context_pn, &c) == 0);
		assert(dict_has_key_pn(dict_context_pn, &d) != 0);

		NSObject* value;
		assert(dict_get_pn(dict_context_pn, &a, &value) == 0);
		assert(value == aaa);
		assert(dict_get_pn(dict_context_pn, &b, &value) == 0);
		assert(value == bbb);
		assert(dict_get_pn(dict_context_pn, &c, &value) == 0);
		assert(value == ccc);
		assert(dict_get_pn(dict_context_pn, &d, &value) != 0);

		dict_iter_pn_t* dict_iter_pn = dict_iter_new_pn(dict_context_pn);
		assert(dict_iter_pn != NULL);
		void* key;
		assert(dict_iter_get_pn(dict_iter_pn, &key, &value) == 0);
		assert(key == &a); assert(value == aaa);
		assert(dict_iter_get_pn(dict_iter_pn, &key, &value) == 0);
		assert(key == &b); assert(value == bbb);
		assert(dict_iter_get_pn(dict_iter_pn, &key, &value) == 0);
		assert(key == &c); assert(value == ccc);
		assert(dict_iter_get_pn(dict_iter_pn, &key, &value) != 0);
		dict_iter_delete_pn(dict_iter_pn);

		assert(dict_remove_pn(dict_context_pn, &a) == 0);
		assert(dict_has_key_pn(dict_context_pn, &a) != 0);
		assert(dict_remove_pn(dict_context_pn, &b) == 0);
		assert(dict_has_key_pn(dict_context_pn, &b) != 0);
		assert(dict_remove_pn(dict_context_pn, &d) != 0);
		assert(dict_has_key_pn(dict_context_pn, &d) != 0);

		assert(dict_count_pn(dict_context_pn) == 1);

		assert(dict_clear_pn(dict_context_pn) == 0);
		assert(dict_count_pn(dict_context_pn) == 0);
	}

	[aaa release];
	[bbb release];
	[ccc release];
	[ddd release];

	dict_delete_pn(dict_context_pn);

	return 0;
}
