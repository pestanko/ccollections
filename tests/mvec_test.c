#define TESTING
#include "testing.h"
#include "../src/mvec.h"

#define UNUSED(a) ((void) (a))

typedef int item_t;

typedef struct darray {
    size_t  alloc_size;
    size_t  size;
    size_t  type_size;
    item_t   *buffer; 
} darray_t;

TEST(test_mvec_init) {
    
    MVEC_TYPE(int) arr;
    MVEC_INIT(arr);

    ASSERT(arr.size == 0);
    ASSERT(arr.alloc_size == 1);
    ASSERT(arr.type_size == sizeof(int));
    ASSERT(arr.buffer == NULL);
}

TEST(test_mvec_create) {

    MVEC_CREATE(int, arr);

    ASSERT(arr.size == 0);
    ASSERT(arr.alloc_size == 1);
    ASSERT(arr.type_size == sizeof(int));
    ASSERT(arr.buffer == NULL);
}


TEST(test_mvec_free) {
    darray_t arr = {.alloc_size = 100, .size = 10, .type_size = 4};    
    arr.buffer = malloc(1000);
    MVEC_FREE(arr);
    ASSERT(arr.buffer == NULL);
    ASSERT(arr.size == 0);
    ASSERT(arr.alloc_size == 1);
}


TEST(test_mvec_empty_size) {
    darray_t arr = {.alloc_size = 0, .size = 0, .buffer = NULL};
    ASSERT(MVEC_EMPTY(arr));
    arr.size = 1000;
    ASSERT(MVEC_SIZE(arr) == 1000);
}

TEST(test_mvec_get) {
    item_t items[] = { 1,2,3 };
    darray_t arr = {.alloc_size = 3, .size = 3, .buffer = items};
    for(size_t i = 0; i < 3; i++) {
        ASSERT(MVEC_GET(arr, i) && i == i);
    }
}

TEST(test_mvec_set) {
    item_t items[] = { 1,2,3 };
    darray_t arr = {.alloc_size = 3, .size = 3, .buffer = items};
    MVEC_SET(arr, 0, 100);
    ASSERT(items[0] == 100);
}

TEST(test_mvec_each) {
    item_t items[] = { 1,2,3 };
    darray_t arr = {.alloc_size = 3, .size = 3, .buffer = items};
    int result = 0;
    MVEC_EACH(int, arr, item, {
        result += *item;
    });

    ASSERT(result == 6);
}


TEST(test_mvec_push) {
    darray_t arr = {.alloc_size = 1, .size = 0, .buffer = NULL, .type_size = sizeof(int)};
    MVEC_PUSH(arr, 100);
    ASSERT(arr.buffer != NULL);
    ASSERT(arr.buffer[0] == 100);
    ASSERT(arr.alloc_size == 2);
    ASSERT(arr.size == 1);
    free(arr.buffer);
}





