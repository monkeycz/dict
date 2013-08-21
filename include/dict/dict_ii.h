#ifndef DICT_II_H
#define DICT_II_H

#include <stdlib.h>



typedef struct dict_context dict_context_ii_t;
typedef struct dict_iter dict_iter_ii_t;

#ifdef __cplusplus
extern "C" {
#endif

dict_context_ii_t* dict_new_ii(void);
dict_context_ii_t* dict_new_length_ii(size_t length);
void dict_delete_ii(dict_context_ii_t* context);

dict_context_ii_t* dict_retain_ii(dict_context_ii_t* context);
size_t dict_retain_count_ii(dict_context_ii_t* context);

dict_context_ii_t* dict_copy_ii(dict_context_ii_t* context);

int dict_set_ii(dict_context_ii_t* context, int key, int value);
int dict_get_ii(dict_context_ii_t* context, int key, int* value);

int dict_remove_ii(dict_context_ii_t* context, int key);
int dict_clear_ii(dict_context_ii_t* context);

int dict_has_key_ii(dict_context_ii_t* context, int key);
size_t dict_count_ii(dict_context_ii_t* context);

dict_iter_ii_t* dict_iter_new_ii(dict_context_ii_t* context);
int dict_iter_get_ii(dict_iter_ii_t* iter, int* key, int* value);
void dict_iter_delete_ii(dict_iter_ii_t* iter);

void dict_print_ii(dict_context_ii_t* context);

#ifdef __cplusplus
}
#endif

#endif /* DICT_II_H */