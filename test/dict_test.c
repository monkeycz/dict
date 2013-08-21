#include <assert.h>

#define DICT_KEY_TYPE		int
#define DICT_VALUE_TYPE		int
#include <dict.h>

static void dict_key_printor_i(DICT_VALUE_TYPE key)
{
	printf("%d", key);
}

static void dict_value_printor_i(DICT_VALUE_TYPE value)
{
	printf("%d", value);
}

int main(int argc, char* argv[])
{
	dict_context_t* dict_context = dict_new(DICT_LENGTH_DEFAULT, 
		NULL, NULL, NULL, NULL, NULL, dict_key_printor_i, dict_value_printor_i);
	assert(dict_context != NULL);

	dict_context_t* dict_context_retain = dict_retain(dict_context);
	assert(dict_retain_count(dict_context) == 2);
	assert(dict_retain_count(dict_context_retain) == 2);
	dict_delete(dict_context_retain);
	assert(dict_retain_count(dict_context) == 1);
	assert(dict_retain_count(dict_context_retain) == 1);

	dict_context_t* dict_context_copy = dict_copy(dict_context);
	assert(dict_context_copy != NULL);
	assert(dict_retain_count(dict_context_copy) == 1);
	dict_delete(dict_context_copy);

	for (int i = 0; i < 2; i++) {
		assert(dict_set(dict_context, 1, 111) == 0);
		assert(dict_set(dict_context, 2, 222) == 0);
		assert(dict_set(dict_context, 3, 333) == 0);

		assert(dict_count(dict_context) == 3);

		assert(dict_has_key(dict_context, 1) == 0);
		assert(dict_has_key(dict_context, 2) == 0);
		assert(dict_has_key(dict_context, 3) == 0);
		assert(dict_has_key(dict_context, 4) != 0);

		int value;
		assert(dict_get(dict_context, 1, &value) == 0);
		assert(value == 111);
		assert(dict_get(dict_context, 2, &value) == 0);
		assert(value == 222);
		assert(dict_get(dict_context, 3, &value) == 0);
		assert(value == 333);
		assert(dict_get(dict_context, 4, &value) != 0);

		dict_iter_t* dict_iter = dict_iter_new(dict_context);
		assert(dict_iter != NULL);
		int key;
		assert(dict_iter_get(dict_iter, &key, &value) == 0);
		assert(key == 1); assert(value == 111);
		assert(dict_iter_get(dict_iter, &key, &value) == 0);
		assert(key == 2); assert(value == 222);
		assert(dict_iter_get(dict_iter, &key, &value) == 0);
		assert(key == 3); assert(value == 333);
		assert(dict_iter_get(dict_iter, &key, &value) != 0);
		dict_iter_delete(dict_iter);

		assert(dict_remove(dict_context, 1) == 0);
		assert(dict_has_key(dict_context, 1) != 0);
		assert(dict_remove(dict_context, 2) == 0);
		assert(dict_has_key(dict_context, 2) != 0);
		assert(dict_remove(dict_context, 4) != 0);
		assert(dict_has_key(dict_context, 4) != 0);

		assert(dict_count(dict_context) == 1);

		assert(dict_clear(dict_context) == 0);
		assert(dict_count(dict_context) == 0);
	}

	dict_delete(dict_context);

	return 0;
}
