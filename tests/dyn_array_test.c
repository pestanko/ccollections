#define TESTING
#include "testing.h"
#include "../src/dyn_array.h"

#define UNUSED(a) ((void) (a))

/*
 *
darray_t *darray_create(size_t initial_size);
void darray_init(darray_t *a, size_t initial_size);
void darray_push(darray_t *a, entity_t element);
void darray_free(darray_t *a);
void darray_destroy(darray_t *a);
size_t darray_size(darray_t *a);
int darray_empty(darray_t *a);
entity_t darray_get(darray_t *a, size_t pos);
void darray_set(darray_t *a, size_t pos, entity_t val);
entity_t *darray_buffer(darray_t *a);
void darray_foreach(darray_t *array, entity_t *result, each_func func);
void darray_copy(darray_t *from, darray_t *to);
darray_t *darray_clone(darray_t *origin);
 *
 */

TEST(test_darray_wrapped) {
    item_t items[] = { { .i8 = 1 }, { .i8 = 2 }, { .i8 = 3 } };
    darray_t arr = { .buffer = items, .size=0x100, .alloc_size=0x141, .wrapped = 0 };
    darray_wrap(&arr,items, 3);
    ASSERT(arr.size == 0);
    ASSERT(arr.alloc_size == 3);
    ASSERT(arr.buffer == items);
    ASSERT(arr.wrapped);
}


TEST(test_darray_init) {
    darray_t arr = { .buffer = (void*) 0x11100, .size=0x100, .alloc_size=0x141, .wrapped = 1 };
    darray_init(&arr, 100);
    ASSERT(arr.size == 0);
    ASSERT(arr.alloc_size == 100);
    ASSERT(arr.buffer);
    ASSERT(!arr.wrapped);
    free(arr.buffer);
}

TEST(test_darray_create) {
    darray_t *arr = darray_create(100);
    ASSERT(arr->size == 0);
    ASSERT(arr->alloc_size == 100);
    ASSERT(arr->buffer);
    free(arr->buffer);
    free(arr);
}

TEST(test_darray_free) {
    darray_t arr = { .buffer = (void*) 0x11100, .size=0x100, .alloc_size=0x141 };
    arr.buffer = malloc(sizeof(item_t));
    darray_free(&arr);
    ASSERT(arr.size == 0);
    ASSERT(arr.alloc_size == 0);
    ASSERT(arr.buffer == 0);
}


TEST(test_darray_destroy) {
    darray_t *arr = malloc(sizeof(darray_t));
    arr->buffer = malloc(sizeof(item_t));
    arr->wrapped = false;
    darray_destroy(arr);
}

TEST(test_darray_size) {
    darray_t arr = {.alloc_size = 0, .size = 0, .buffer = NULL};
    ASSERT(darray_size(&arr) == 0);
    arr.size = 1000;
    ASSERT(darray_size(&arr) == 1000);
}

TEST(test_darray_empty) {
    darray_t arr = {.alloc_size = 0, .size = 0, .buffer = NULL};
    ASSERT(darray_empty(&arr) == 0);
    arr.size = 1000;
    ASSERT(darray_empty(&arr) != 0);
}

TEST(test_darray_get) {
    item_t items[] = { { .i8 = 1 }, { .i8 = 2 }, { .i8 = 3 } };
    darray_t arr = {.alloc_size = 3, .size = 3, .buffer = items};
    ASSERT(darray_get(&arr, 0).i8 == items[0].i8);
    ASSERT(darray_get(&arr, 1).i8 == items[1].i8);
    ASSERT(darray_get(&arr, 2).i8 == items[2].i8);
}

TEST(test_darray_set) {
    item_t items[] = { { .i8 = 1 }, { .i8 = 2 }, { .i8 = 3 } };
    darray_t arr = {.alloc_size = 3, .size = 3, .buffer = items};
    item_t item = { .i8 = 100 };
    darray_set(&arr, 0, item);
    ASSERT(items[0].i8 == 100);
}

TEST(test_darray_buffer) {
    item_t items[] = { { .i8 = 1 }, { .i8 = 2 }, { .i8 = 3 } };
    darray_t arr = {.alloc_size = 3, .size = 3, .buffer = items};
    ASSERT(darray_buffer(&arr) == items);
}

static void _internal_sum(item_t item, size_t index, void *result) {
    UNUSED(index);
    int * res = (int*) result;
    *res += item.i8;
}

TEST(test_darray_foreach) {
    item_t items[] = { { .i8 = 1 }, { .i8 = 2 }, { .i8 = 3 } };
    darray_t arr = {.alloc_size = 3, .size = 3, .buffer = items, .wrapped = false};
    int result = 0;

    darray_foreach(&arr, &result, _internal_sum);
    ASSERT(result == 6);
}

static int _internal_pred(item_t item) {
    return item.u8 < 3;
}

TEST(test_darray_filter) {
    item_t items[] = { { .i8 = 1 }, { .i8 = 2 }, { .i8 = 3 } };
    item_t res_items[5] = {{.i8 = 0}};
    darray_t arr = { .alloc_size = 3, .size = 3, .buffer = items };
    darray_t res = { .alloc_size = 5, .size = 0, .buffer = res_items };

    darray_filter(&arr, &res, _internal_pred);

    ASSERT(res_items[0].u8 == 1);
    ASSERT(res_items[1].u8 == 2);
    ASSERT(res_items[2].u8 == 0);
    ASSERT(res_items[3].u8 == 0);
    ASSERT(res_items[4].u8 == 0);
    ASSERT(res.size = 2);
}

TEST(test_darray_push_alloc) {
    darray_t arr = {.alloc_size = 0, .size = 0, .buffer = NULL, .wrapped = false};
    item_t item = { .i8 = 100 };
    darray_push(&arr,  item);
    ASSERT(arr.buffer != NULL);
    ASSERT(arr.buffer[0].i8 == 100);
    ASSERT(arr.alloc_size == 2);
    ASSERT(arr.size == 1);
    free(arr.buffer);
}

TEST(test_darray_push_wrap) {
    item_t items[3] = { { .i8 = 0 } };
    darray_t arr = {.alloc_size = 2, .size = 0, .buffer = items, .wrapped = true};
    item_t item = { .i8 = 100 };

    darray_push(&arr,  item);
    ASSERT(items[0].i8 == 100);
    ASSERT(items[1].i8 == 0);
    ASSERT(items[2].i8 == 0);
    ASSERT(arr.alloc_size == 2);
    ASSERT(arr.size == 1);

    darray_push(&arr,  item);
    ASSERT(items[0].i8 == 100);
    ASSERT(items[1].i8 == 100);
    ASSERT(items[2].i8 == 0);

    darray_push(&arr,  item);
    ASSERT(items[0].i8 == 100);
    ASSERT(items[1].i8 == 100);
    ASSERT(items[2].i8 == 0);

}






