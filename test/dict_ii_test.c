#include <dict/dict_ii.h>
#include <assert.h>

int main(int argc, char* argv[])
{
	dict_context_ii_t* dict_context_ii = dict_new_ii();
	assert(dict_context_ii != NULL);

	dict_context_ii_t* dict_context_ii_retain = dict_retain_ii(dict_context_ii);
	assert(dict_retain_count_ii(dict_context_ii) == 2);
	assert(dict_retain_count_ii(dict_context_ii_retain) == 2);
	dict_delete_ii(dict_context_ii_retain);
	assert(dict_retain_count_ii(dict_context_ii) == 1);
	assert(dict_retain_count_ii(dict_context_ii_retain) == 1);

	dict_context_ii_t* dict_context_ii_copy = dict_copy_ii(dict_context_ii);
	assert(dict_context_ii_copy != NULL);
	assert(dict_retain_count_ii(dict_context_ii_copy) == 1);
	dict_delete_ii(dict_context_ii_copy);

	for (int i = 0; i < 2; i++) {
		assert(dict_set_ii(dict_context_ii, 1, 111) == 0);
		assert(dict_set_ii(dict_context_ii, 2, 222) == 0);
		assert(dict_set_ii(dict_context_ii, 3, 333) == 0);

		assert(dict_count_ii(dict_context_ii) == 3);

		assert(dict_has_key_ii(dict_context_ii, 1) == 0);
		assert(dict_has_key_ii(dict_context_ii, 2) == 0);
		assert(dict_has_key_ii(dict_context_ii, 3) == 0);
		assert(dict_has_key_ii(dict_context_ii, 4) != 0);

		int value;
		assert(dict_get_ii(dict_context_ii, 1, &value) == 0);
		assert(value == 111);
		assert(dict_get_ii(dict_context_ii, 2, &value) == 0);
		assert(value == 222);
		assert(dict_get_ii(dict_context_ii, 3, &value) == 0);
		assert(value == 333);
		assert(dict_get_ii(dict_context_ii, 4, &value) != 0);

		dict_iter_ii_t* dict_iter_ii = dict_iter_new_ii(dict_context_ii);
		assert(dict_iter_ii != NULL);
		int key;
		assert(dict_iter_get_ii(dict_iter_ii, &key, &value) == 0);
		assert(key == 1); assert(value == 111);
		assert(dict_iter_get_ii(dict_iter_ii, &key, &value) == 0);
		assert(key == 2); assert(value == 222);
		assert(dict_iter_get_ii(dict_iter_ii, &key, &value) == 0);
		assert(key == 3); assert(value == 333);
		assert(dict_iter_get_ii(dict_iter_ii, &key, &value) != 0);
		dict_iter_delete_ii(dict_iter_ii);

		assert(dict_remove_ii(dict_context_ii, 1) == 0);
		assert(dict_has_key_ii(dict_context_ii, 1) != 0);
		assert(dict_remove_ii(dict_context_ii, 2) == 0);
		assert(dict_has_key_ii(dict_context_ii, 2) != 0);
		assert(dict_remove_ii(dict_context_ii, 4) != 0);
		assert(dict_has_key_ii(dict_context_ii, 4) != 0);

		assert(dict_count_ii(dict_context_ii) == 1);

		assert(dict_clear_ii(dict_context_ii) == 0);
		assert(dict_count_ii(dict_context_ii) == 0);
	}

	dict_delete_ii(dict_context_ii);

	return 0;
}
