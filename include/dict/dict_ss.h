#ifndef DICT_SS_H
#define DICT_SS_H

#include <stdlib.h>



typedef struct dict_context dict_context_ss_t;
typedef struct dict_iter dict_iter_ss_t;

#ifdef __cplusplus
extern "C" {
#endif

dict_context_ss_t* dict_new_ss(void);
dict_context_ss_t* dict_new_length_ss(size_t length);
void dict_delete_ss(dict_context_ss_t* context);

dict_context_ss_t* dict_retain_ss(dict_context_ss_t* context);
size_t dict_retain_count_ss(dict_context_ss_t* context);

dict_context_ss_t* dict_copy_ss(dict_context_ss_t* context);

int dict_set_ss(dict_context_ss_t* context, char* key, char* value);
int dict_get_ss(dict_context_ss_t* context, char* key, char** value);

int dict_remove_ss(dict_context_ss_t* context, char* key);
int dict_clear_ss(dict_context_ss_t* context);

int dict_has_key_ss(dict_context_ss_t* context, char* key);
size_t dict_count_ss(dict_context_ss_t* context);

dict_iter_ss_t* dict_iter_new_ss(dict_context_ss_t* context);
int dict_iter_get_ss(dict_iter_ss_t* iter, char** key, char** value);
void dict_iter_delete_ss(dict_iter_ss_t* iter);

void dict_print_ss(dict_context_ss_t* context);

#ifdef __cplusplus
}
#endif

#endif /* DICT_SS_H */