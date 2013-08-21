#ifndef DICT_PP_H
#define DICT_PP_H

#include <stdlib.h>



typedef struct dict_context dict_context_pp_t;
typedef struct dict_iter dict_iter_pp_t;

#ifdef __cplusplus
extern "C" {
#endif

dict_context_pp_t* dict_new_pp(void);
dict_context_pp_t* dict_new_length_pp(size_t length);
void dict_delete_pp(dict_context_pp_t* context);

dict_context_pp_t* dict_retain_pp(dict_context_pp_t* context);
size_t dict_retain_count_pp(dict_context_pp_t* context);

dict_context_pp_t* dict_copy_pp(dict_context_pp_t* context);

int dict_set_pp(dict_context_pp_t* context, void* key, void* value);
int dict_get_pp(dict_context_pp_t* context, void* key, void** value);

int dict_remove_pp(dict_context_pp_t* context, void* key);
int dict_clear_pp(dict_context_pp_t* context);

int dict_has_key_pp(dict_context_pp_t* context, void* key);
size_t dict_count_pp(dict_context_pp_t* context);

dict_iter_pp_t* dict_iter_new_pp(dict_context_pp_t* context);
int dict_iter_get_pp(dict_iter_pp_t* iter, void** key, void** value);
void dict_iter_delete_pp(dict_iter_pp_t* iter);

void dict_print_pp(dict_context_pp_t* context);

#ifdef __cplusplus
}
#endif

#endif /* DICT_PP_H */