#ifndef DICT_IS_H
#define DICT_IS_H

#include <stdlib.h>



typedef struct dict_context dict_context_is_t;
typedef struct dict_iter dict_iter_is_t;

#ifdef __cplusplus
extern "C" {
#endif

dict_context_is_t* dict_new_is(void);
dict_context_is_t* dict_new_length_is(size_t length);
void dict_delete_is(dict_context_is_t* context);

dict_context_is_t* dict_retain_is(dict_context_is_t* context);
size_t dict_retain_count_is(dict_context_is_t* context);

dict_context_is_t* dict_copy_is(dict_context_is_t* context);

int dict_set_is(dict_context_is_t* context, int key, char* value);
int dict_get_is(dict_context_is_t* context, int key, char** value);

int dict_remove_is(dict_context_is_t* context, int key);
int dict_clear_is(dict_context_is_t* context);

int dict_has_key_is(dict_context_is_t* context, int key);
size_t dict_count_is(dict_context_is_t* context);

dict_iter_is_t* dict_iter_new_is(dict_context_is_t* context);
int dict_iter_get_is(dict_iter_is_t* iter, int* key, char** value);
void dict_iter_delete_is(dict_iter_is_t* iter);

void dict_print_is(dict_context_is_t* context);

#ifdef __cplusplus
}
#endif

#endif /* DICT_IS_H */