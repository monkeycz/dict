#include <dict/dict_si.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[])
{
	dict_context_si_t* dict_context_si = dict_new_si();
	assert(dict_context_si != NULL);

	dict_context_si_t* dict_context_si_retain = dict_retain_si(dict_context_si);
	assert(dict_retain_count_si(dict_context_si) == 2);
	assert(dict_retain_count_si(dict_context_si_retain) == 2);
	dict_delete_si(dict_context_si_retain);
	assert(dict_retain_count_si(dict_context_si) == 1);
	assert(dict_retain_count_si(dict_context_si_retain) == 1);

	dict_context_si_t* dict_context_si_copy = dict_copy_si(dict_context_si);
	assert(dict_context_si_copy != NULL);
	assert(dict_retain_count_si(dict_context_si_copy) == 1);
	dict_delete_si(dict_context_si_copy);

	for (int i = 0; i < 2; i++) {
		assert(dict_set_si(dict_context_si, "a", 111) == 0);
		assert(dict_set_si(dict_context_si, "b", 222) == 0);
		assert(dict_set_si(dict_context_si, "c", 333) == 0);

		assert(dict_count_si(dict_context_si) == 3);

		assert(dict_has_key_si(dict_context_si, "a") == 0);
		assert(dict_has_key_si(dict_context_si, "b") == 0);
		assert(dict_has_key_si(dict_context_si, "c") == 0);
		assert(dict_has_key_si(dict_context_si, "d") != 0);

		int value;
		assert(dict_get_si(dict_context_si, "a", &value) == 0);
		assert(value == 111);
		assert(dict_get_si(dict_context_si, "b", &value) == 0);
		assert(value == 222);
		assert(dict_get_si(dict_context_si, "c", &value) == 0);
		assert(value == 333);
		assert(dict_get_si(dict_context_si, "d", &value) != 0);

		dict_iter_si_t* dict_iter_si = dict_iter_new_si(dict_context_si);
		assert(dict_iter_si != NULL);
		char* key;
		assert(dict_iter_get_si(dict_iter_si, &key, &value) == 0);
		assert(strcmp(key, "a") == 0); assert(value == 111);
		assert(dict_iter_get_si(dict_iter_si, &key, &value) == 0);
		assert(strcmp(key, "b") == 0); assert(value == 222);
		assert(dict_iter_get_si(dict_iter_si, &key, &value) == 0);
		assert(strcmp(key, "c") == 0); assert(value == 333);
		assert(dict_iter_get_si(dict_iter_si, &key, &value) != 0);
		dict_iter_delete_si(dict_iter_si);

		assert(dict_remove_si(dict_context_si, "a") == 0);
		assert(dict_has_key_si(dict_context_si, "a") != 0);
		assert(dict_remove_si(dict_context_si, "b") == 0);
		assert(dict_has_key_si(dict_context_si, "b") != 0);
		assert(dict_remove_si(dict_context_si, "d") != 0);
		assert(dict_has_key_si(dict_context_si, "d") != 0);

		assert(dict_count_si(dict_context_si) == 1);

		assert(dict_clear_si(dict_context_si) == 0);
		assert(dict_count_si(dict_context_si) == 0);
	}

	dict_delete_si(dict_context_si);

	return 0;
}
