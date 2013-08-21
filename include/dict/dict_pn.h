#ifndef DICT_PN_H
#define DICT_PN_H

#include <stdlib.h>

@class NSObject;

typedef struct dict_context dict_context_pn_t;
typedef struct dict_iter dict_iter_pn_t;

#ifdef __cplusplus
extern "C" {
#endif

dict_context_pn_t* dict_new_pn(void);
dict_context_pn_t* dict_new_length_pn(size_t length);
void dict_delete_pn(dict_context_pn_t* context);

dict_context_pn_t* dict_retain_pn(dict_context_pn_t* context);
size_t dict_retain_count_pn(dict_context_pn_t* context);

dict_context_pn_t* dict_copy_pn(dict_context_pn_t* context);

int dict_set_pn(dict_context_pn_t* context, void* key, NSObject* value);
int dict_get_pn(dict_context_pn_t* context, void* key, NSObject** value);

int dict_remove_pn(dict_context_pn_t* context, void* key);
int dict_clear_pn(dict_context_pn_t* context);

int dict_has_key_pn(dict_context_pn_t* context, void* key);
size_t dict_count_pn(dict_context_pn_t* context);

dict_iter_pn_t* dict_iter_new_pn(dict_context_pn_t* context);
int dict_iter_get_pn(dict_iter_pn_t* iter, void** key, NSObject** value);
void dict_iter_delete_pn(dict_iter_pn_t* iter);

void dict_print_pn(dict_context_pn_t* context);

#ifdef __cplusplus
}
#endif

#endif /* DICT_PN_H */