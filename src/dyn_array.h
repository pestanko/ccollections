#ifndef __COLLECTIONS_DYN_ARRAY__
#define __COLLECTIONS_DYN_ARRAY__

#include "entity.h"
#include <stdbool.h>

typedef entity_t item_t;

typedef struct darray {
  item_t *buffer;
  size_t alloc_size;
  size_t size;
  bool wrapped;
} darray_t;


typedef void (*each_func)(item_t, size_t, void*);
typedef int (*pred_func)(item_t);

darray_t *darray_create(size_t initial_size);
void darray_wrap(darray_t *arr, entity_t *buffer, size_t size);
void darray_init(darray_t *a, size_t initial_size);
void darray_push(darray_t *a, entity_t element);
void darray_free(darray_t *a);
void darray_destroy(darray_t *a);

size_t darray_size(const darray_t *a);
entity_t *darray_buffer(darray_t *a);
int darray_empty(const darray_t *a);

entity_t darray_get(const darray_t *a, size_t pos);
void darray_set(darray_t *a, size_t pos, entity_t val);

void darray_foreach(darray_t *array, void *result, each_func func);
void darray_filter(darray_t *from, darray_t *to, pred_func predicate);

void darray_copy(const darray_t *from, darray_t *to);
darray_t *darray_clone(const darray_t *origin);


#endif //__COLLECTIONS_DYN_ARRAY__
