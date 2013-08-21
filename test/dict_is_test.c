#include <dict/dict_is.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[])
{
	dict_context_is_t* dict_context_is = dict_new_is();
	assert(dict_context_is != NULL);

	dict_context_is_t* dict_context_is_retain = dict_retain_is(dict_context_is);
	assert(dict_retain_count_is(dict_context_is) == 2);
	assert(dict_retain_count_is(dict_context_is_retain) == 2);
	dict_delete_is(dict_context_is_retain);
	assert(dict_retain_count_is(dict_context_is) == 1);
	assert(dict_retain_count_is(dict_context_is_retain) == 1);

	dict_context_is_t* dict_context_is_copy = dict_copy_is(dict_context_is);
	assert(dict_context_is_copy != NULL);
	assert(dict_retain_count_is(dict_context_is_copy) == 1);
	dict_delete_is(dict_context_is_copy);

	for (int i = 0; i < 2; i++) {
		assert(dict_set_is(dict_context_is, 1, "aaa") == 0);
		assert(dict_set_is(dict_context_is, 2, "bbb") == 0);
		assert(dict_set_is(dict_context_is, 3, "ccc") == 0);

		assert(dict_count_is(dict_context_is) == 3);

		assert(dict_has_key_is(dict_context_is, 1) == 0);
		assert(dict_has_key_is(dict_context_is, 2) == 0);
		assert(dict_has_key_is(dict_context_is, 3) == 0);
		assert(dict_has_key_is(dict_context_is, 4) != 0);

		char* value;
		assert(dict_get_is(dict_context_is, 1, &value) == 0);
		assert(strcmp(value, "aaa") == 0);
		assert(dict_get_is(dict_context_is, 2, &value) == 0);
		assert(strcmp(value, "bbb") == 0);
		assert(dict_get_is(dict_context_is, 3, &value) == 0);
		assert(strcmp(value, "ccc") == 0);
		assert(dict_get_is(dict_context_is, 4, &value) != 0);

		dict_iter_is_t* dict_iter_is = dict_iter_new_is(dict_context_is);
		assert(dict_iter_is != NULL);
		int key;
		assert(dict_iter_get_is(dict_iter_is, &key, &value) == 0);
		assert(key == 1); assert(strcmp(value, "aaa") == 0);
		assert(dict_iter_get_is(dict_iter_is, &key, &value) == 0);
		assert(key == 2); assert(strcmp(value, "bbb") == 0);
		assert(dict_iter_get_is(dict_iter_is, &key, &value) == 0);
		assert(key == 3); assert(strcmp(value, "ccc") == 0);
		assert(dict_iter_get_is(dict_iter_is, &key, &value) != 0);
		dict_iter_delete_is(dict_iter_is);

		assert(dict_remove_is(dict_context_is, 1) == 0);
		assert(dict_has_key_is(dict_context_is, 1) != 0);
		assert(dict_remove_is(dict_context_is, 2) == 0);
		assert(dict_has_key_is(dict_context_is, 2) != 0);
		assert(dict_remove_is(dict_context_is, 4) != 0);
		assert(dict_has_key_is(dict_context_is, 4) != 0);

		assert(dict_count_is(dict_context_is) == 1);

		assert(dict_clear_is(dict_context_is) == 0);
		assert(dict_count_is(dict_context_is) == 0);
	}

	dict_delete_is(dict_context_is);

	return 0;
}
