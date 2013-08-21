#include <dict/dict_ss.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[])
{
	dict_context_ss_t* dict_context_ss = dict_new_ss();
	assert(dict_context_ss != NULL);

	dict_context_ss_t* dict_context_ss_retain = dict_retain_ss(dict_context_ss);
	assert(dict_retain_count_ss(dict_context_ss) == 2);
	assert(dict_retain_count_ss(dict_context_ss_retain) == 2);
	dict_delete_ss(dict_context_ss_retain);
	assert(dict_retain_count_ss(dict_context_ss) == 1);
	assert(dict_retain_count_ss(dict_context_ss_retain) == 1);

	dict_context_ss_t* dict_context_ss_copy = dict_copy_ss(dict_context_ss);
	assert(dict_context_ss_copy != NULL);
	assert(dict_retain_count_ss(dict_context_ss_copy) == 1);
	dict_delete_ss(dict_context_ss_copy);

	for (int i = 0; i < 2; i++) {
		assert(dict_set_ss(dict_context_ss, "a", "aaa") == 0);
		assert(dict_set_ss(dict_context_ss, "b", "bbb") == 0);
		assert(dict_set_ss(dict_context_ss, "c", "ccc") == 0);

		assert(dict_count_ss(dict_context_ss) == 3);

		assert(dict_has_key_ss(dict_context_ss, "a") == 0);
		assert(dict_has_key_ss(dict_context_ss, "b") == 0);
		assert(dict_has_key_ss(dict_context_ss, "c") == 0);
		assert(dict_has_key_ss(dict_context_ss, "d") != 0);

		char* value;
		assert(dict_get_ss(dict_context_ss, "a", &value) == 0);
		assert(strcmp(value, "aaa") == 0);
		assert(dict_get_ss(dict_context_ss, "b", &value) == 0);
		assert(strcmp(value, "bbb") == 0);
		assert(dict_get_ss(dict_context_ss, "c", &value) == 0);
		assert(strcmp(value, "ccc") == 0);
		assert(dict_get_ss(dict_context_ss, "d", &value) != 0);

		dict_iter_ss_t* dict_iter_ss = dict_iter_new_ss(dict_context_ss);
		assert(dict_iter_ss != NULL);
		char* key;
		assert(dict_iter_get_ss(dict_iter_ss, &key, &value) == 0);
		assert(strcmp(key, "a") == 0); assert(strcmp(value, "aaa") == 0);
		assert(dict_iter_get_ss(dict_iter_ss, &key, &value) == 0);
		assert(strcmp(key, "b") == 0); assert(strcmp(value, "bbb") == 0);
		assert(dict_iter_get_ss(dict_iter_ss, &key, &value) == 0);
		assert(strcmp(key, "c") == 0); assert(strcmp(value, "ccc") == 0);
		assert(dict_iter_get_ss(dict_iter_ss, &key, &value) != 0);
		dict_iter_delete_ss(dict_iter_ss);

		assert(dict_remove_ss(dict_context_ss, "a") == 0);
		assert(dict_has_key_ss(dict_context_ss, "a") != 0);
		assert(dict_remove_ss(dict_context_ss, "b") == 0);
		assert(dict_has_key_ss(dict_context_ss, "b") != 0);
		assert(dict_remove_ss(dict_context_ss, "d") != 0);
		assert(dict_has_key_ss(dict_context_ss, "d") != 0);

		assert(dict_count_ss(dict_context_ss) == 1);

		assert(dict_clear_ss(dict_context_ss) == 0);
		assert(dict_count_ss(dict_context_ss) == 0);
	}

	dict_delete_ss(dict_context_ss);

	return 0;
}
