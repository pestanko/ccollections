#ifndef __COLLECTIONS_MVEC__
#define __COLLECTIONS_MVEC__

#include <string.h>
#include <stdlib.h>



#define MVEC_TYPE(type) struct {\
        size_t  alloc_size;\
        size_t  size;\
        size_t  type_size;\
        type    *buffer;\
    }

#define MVEC_INIT(a) do{ (a).buffer = NULL;\
                         (a).size = 0;\
                         (a).alloc_size = 1;\
                         (a).type_size = sizeof(*((a).buffer));\
                     }while(0)

#define MVEC_CREATE(type, a) MVEC_TYPE(type) a; MVEC_INIT(a)

#define MVEC_SIZE(a) ((a).size)

#define MVEC_ALLOC_SIZE(a) ((a).alloc_size)

#define MVEC_TYPE_SIZE(a) ((a).type_size)

#define MVEC_PUSH(a, value) do {\
    if(((a).size + 1) >= (a).alloc_size){\
        size_t old_size = (a).alloc_size;\
        (a).alloc_size *= 2;\
        if( (a).alloc_size > old_size) {\
            void *old_buffer = (a).buffer;\
            (a).buffer = realloc((a).buffer, ((a).alloc_size * (a).type_size)); \
            if((a).buffer == NULL) { (a).buffer = old_buffer; }\
        }\
    }\
    if((a).buffer && ((a).size+1) < (a).alloc_size) { (a).buffer[((a).size)++] = (value); }\
    }while(0)


#define MVEC_GET(a, index) (a).buffer[(index)]
#define MVEC_SET(a, index, value) (a).buffer[(index)] = value


#define MVEC_FREE(a) do { free((a).buffer); MVEC_INIT(a); }while(0)
#define MVEC_EMPTY(a) ((a).size == 0 && (a).buffer == NULL)
#define MVEC_POP(a) (a).buffer[((a).size)--]

#define MVEC_EACH_FUNC(a, func) do {\
    for(size_t i = 0; i < a.size; i++){\
        func((a).buffer[i], i);\
    }\
}while(0)

#define MVEC_EACH(type, a, item, PROC) do {\
    for(size_t i = 0; i < (a).size; i++){\
        type * item = &((a).buffer[i]);\
        do{ PROC }while(0);\
    }\
}while(0)


/* POINTER VERSION OF THE FUNCTIONS */

#define MVECP_TYPE(type)            MVEC_TYPE(type) *
#define MVECP_INIT(a)               MVEC_INIT(*a)
#define MVECP_SIZE(a)               MVEC_SIZE(*a)
#define MVECP_ALLOC_SIZE(a)         MVEC_ALLOC_SIZE(*a)
#define MVECP_TYPE_SIZE(a)          MVEC_TYPE_SIZE(*a)
#define MVECP_PUSH(a, value)        MVEC_PUSH(*a, value)
#define MVECP_FREE(a)               MVEC_FREE(*a)
#define MVECP_EMPTY(a)              MVEC_EMPTY(*a)
#define MVECP_GET(a, index)         MVEC_GET(*a, index)
#define MVECP_POP(a)                MVEC_POP(*a)
#define MVECP_EACH_FUNC(a, func)    MVEC_EACH_FUNC(*a, func)
#define MVECP_EACH(type, a, item, PROC)         MVEC_EACH(type, *a, item, PROC)

#endif // __COLLECTIONS_MVEC__