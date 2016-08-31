#ifndef SERSIAL_DATA_PACK 
#define SERSIAL_DATA_PACK

#include <stdint.h>
#include <stddef.h>


struct data_pack{
    uint8_t height;
    uint16_t weight;
    uint32_t position[2];
};

typedef struct data_pack data_pack_t;

#endif

