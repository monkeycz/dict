#include <dict/dict_pp.h>
#include <assert.h>

int main(int argc, char* argv[])
{
	dict_context_pp_t* dict_context_pp = dict_new_pp();
	assert(dict_context_pp != NULL);

	dict_context_pp_t* dict_context_pp_retain = dict_retain_pp(dict_context_pp);
	assert(dict_retain_count_pp(dict_context_pp) == 2);
	assert(dict_retain_count_pp(dict_context_pp_retain) == 2);
	dict_delete_pp(dict_context_pp_retain);
	assert(dict_retain_count_pp(dict_context_pp) == 1);
	assert(dict_retain_count_pp(dict_context_pp_retain) == 1);

	dict_context_pp_t* dict_context_pp_copy = dict_copy_pp(dict_context_pp);
	assert(dict_context_pp_copy != NULL);
	assert(dict_retain_count_pp(dict_context_pp_copy) == 1);
	dict_delete_pp(dict_context_pp_copy);

	int a = 1, aaa = 111;
	int b = 2, bbb = 222;
	int c = 3, ccc = 333;
	int d = 4, ddd = 444;

	for (int i = 0; i < 2; i++) {
		assert(dict_set_pp(dict_context_pp, &a, &aaa) == 0);
		assert(dict_set_pp(dict_context_pp, &b, &bbb) == 0);
		assert(dict_set_pp(dict_context_pp, &c, &ccc) == 0);

		assert(dict_count_pp(dict_context_pp) == 3);

		assert(dict_has_key_pp(dict_context_pp, &a) == 0);
		assert(dict_has_key_pp(dict_context_pp, &b) == 0);
		assert(dict_has_key_pp(dict_context_pp, &c) == 0);
		assert(dict_has_key_pp(dict_context_pp, &d) != 0);

		void* value;
		assert(dict_get_pp(dict_context_pp, &a, &value) == 0);
		assert(*(int*)value == 111);
		assert(dict_get_pp(dict_context_pp, &b, &value) == 0);
		assert(*(int*)value == 222);
		assert(dict_get_pp(dict_context_pp, &c, &value) == 0);
		assert(*(int*)value == 333);
		assert(dict_get_pp(dict_context_pp, &d, &value) != 0);

		dict_iter_pp_t* dict_iter_pp = dict_iter_new_pp(dict_context_pp);
		assert(dict_iter_pp != NULL);
		void* key;
		assert(dict_iter_get_pp(dict_iter_pp, &key, &value) == 0);
		assert(key == &a); assert(*(int*)value == 111);
		assert(dict_iter_get_pp(dict_iter_pp, &key, &value) == 0);
		assert(key == &b); assert(*(int*)value == 222);
		assert(dict_iter_get_pp(dict_iter_pp, &key, &value) == 0);
		assert(key == &c); assert(*(int*)value == 333);
		assert(dict_iter_get_pp(dict_iter_pp, &key, &value) != 0);
		dict_iter_delete_pp(dict_iter_pp);

		assert(dict_remove_pp(dict_context_pp, &a) == 0);
		assert(dict_has_key_pp(dict_context_pp, &a) != 0);
		assert(dict_remove_pp(dict_context_pp, &b) == 0);
		assert(dict_has_key_pp(dict_context_pp, &b) != 0);
		assert(dict_remove_pp(dict_context_pp, &d) != 0);
		assert(dict_has_key_pp(dict_context_pp, &d) != 0);

		assert(dict_count_pp(dict_context_pp) == 1);

		assert(dict_clear_pp(dict_context_pp) == 0);
		assert(dict_count_pp(dict_context_pp) == 0);
	}

	dict_delete_pp(dict_context_pp);

	return 0;
}
