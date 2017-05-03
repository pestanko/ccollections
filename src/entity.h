#ifndef __COLLECTIONS_ENTITY_H__
#define __COLLECTIONS_ENTITY_H__

#include <stdint.h>
#include <stdlib.h>


typedef union entity {
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;

    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;

    void * pointer;
    char * string;

} entity_t;




#endif // __COLLECTIONS_ENTITY_H__