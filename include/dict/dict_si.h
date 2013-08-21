#ifndef DICT_SI_H
#define DICT_SI_H

#include <stdlib.h>



typedef struct dict_context dict_context_si_t;
typedef struct dict_iter dict_iter_si_t;

#ifdef __cplusplus
extern "C" {
#endif

dict_context_si_t* dict_new_si(void);
dict_context_si_t* dict_new_length_si(size_t length);
void dict_delete_si(dict_context_si_t* context);

dict_context_si_t* dict_retain_si(dict_context_si_t* context);
size_t dict_retain_count_si(dict_context_si_t* context);

dict_context_si_t* dict_copy_si(dict_context_si_t* context);

int dict_set_si(dict_context_si_t* context, char* key, int value);
int dict_get_si(dict_context_si_t* context, char* key, int* value);

int dict_remove_si(dict_context_si_t* context, char* key);
int dict_clear_si(dict_context_si_t* context);

int dict_has_key_si(dict_context_si_t* context, char* key);
size_t dict_count_si(dict_context_si_t* context);

dict_iter_si_t* dict_iter_new_si(dict_context_si_t* context);
int dict_iter_get_si(dict_iter_si_t* iter, char** key, int* value);
void dict_iter_delete_si(dict_iter_si_t* iter);

void dict_print_si(dict_context_si_t* context);

#ifdef __cplusplus
}
#endif

#endif /* DICT_SI_H */