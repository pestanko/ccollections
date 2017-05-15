#include <stdlib.h>
#include "dyn_array.h"

#define UNUSED(a) ((void) (a))

void darray_wrap(darray_t *arr, entity_t *buffer, size_t size)
{
    if(!arr) 
        return;

    arr->wrapped = true;
    arr->buffer = buffer;
    arr->alloc_size = size;
    arr->size = 0;
}

darray_t *darray_create(size_t initial_size) 
{
    darray_t *array = malloc(sizeof(darray_t));

    if(!array) {
        return NULL;
    }
    
    darray_init(array, initial_size);
    
    return array;
}

void darray_init(darray_t *a, size_t initialSize) 
{
    if(!a) 
        return;
    a->buffer = (initialSize) ? (item_t *) malloc(initialSize * sizeof(item_t)) : NULL;
    a->size = 0;
    a->alloc_size = initialSize;
    a->wrapped = false;
}


void darray_push(darray_t *a, entity_t element) 
{
    if (!a) 
        return;
    
    if (a->alloc_size == a->size) {
        if(a->wrapped) 
            return;
        
        if(a->alloc_size == 0){
            a->alloc_size = 1;
        }

        a->alloc_size *= 2;
        a->buffer = (entity_t *) realloc(a->buffer, a->alloc_size * sizeof(entity_t));
    }

    a->buffer[a->size++] = element;
}

void darray_free(darray_t *a) 
{
    if(!a) 
        return;
    
    if(!a->wrapped) {
        free(a->buffer);
    }

    a->buffer = NULL;
    a->alloc_size = a->size = 0;
}

void darray_destroy(darray_t *a) 
{
    darray_free(a);
    free(a);
}

size_t darray_size(const darray_t *a) 
{
    if(!a) 
        return 0;

    return a->size;
}

int darray_empty(const darray_t *a) 
{
    if(!a) 
        return true;

    return a->size;
}

item_t darray_get(const darray_t *a, size_t pos) 
{
    static item_t empty = {.pointer = NULL};
    if(!a) 
        return empty;

    return a->buffer[pos];
}

void darray_set(darray_t *a, size_t pos, item_t val) 
{
    if(!a) 
        return;

    a->buffer[pos] = val;
}

item_t* darray_buffer(darray_t *a) 
{
    if(!a) {
        return NULL;
    }

    return a->buffer;
}

static void _internal_copy_func(item_t item, size_t index, void *result) 
{
    darray_t *cloned = (darray_t*) result;
    darray_set(cloned, index, item);   
}

void darray_foreach(darray_t *array, void *result, each_func func) 
{
    if(!array || !func) 
        return; 
   
    for(size_t i = 0; i < array->size; i++) {
        func(array->buffer[i], i, result);    
    }
}

void darray_copy(const darray_t *from, darray_t *to) 
{
    if(!from || !to) 
        return;

    darray_free(to);
    darray_init(to, from->size);
    
    darray_foreach(from, to, _internal_copy_func);
}

void darray_filter(darray_t *from, darray_t *to, pred_func predicate) 
{
     if(!from || !to || !predicate) 
        return; 
   
    for(size_t i = 0; i < from->size; i++) {
        if(predicate(from->buffer[i])) {
            darray_push(to, from->buffer[i]);
        }    
    }
}

darray_t * darray_clone(const darray_t *origin) 
{
    if(!origin) 
        return NULL;

    darray_t *new_arr = darray_create(origin->size);

    if(!new_arr) {
        return NULL;
    }

    darray_copy(origin, new_arr);

    return new_arr;
}

