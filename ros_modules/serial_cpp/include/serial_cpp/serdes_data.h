#ifndef SERSIAL_SERDES_DATA 
#define SERSIAL_SERDES_DATA

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <arpa/inet.h>

namespace serial_cpp
{
extern const size_t DATA_PACK_SERIALIZED_SIZE;

size_t serialize_data_pack(const struct data_pack *source, uint8_t *outputBuffer, size_t outputBufferLength);

size_t deserialize_data_pack(const uint8_t *data, size_t dataLength, struct data_pack *output);

}

#endif

