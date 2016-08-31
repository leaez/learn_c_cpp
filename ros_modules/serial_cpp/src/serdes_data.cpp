#include <serial_cpp/data_pack.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <arpa/inet.h>

namespace serial_cpp 
{
extern const size_t DATA_PACK_SERIALIZED_SIZE;

size_t serialize_data_pack(const struct data_pack *source, uint8_t *outputBuffer, size_t outputBufferLength);

size_t deserialize_data_pack(const uint8_t *data, size_t dataLength, struct data_pack *output);

const size_t DATA_PACK_SERIALIZED_SIZE = 11;

// **** AUTOMATICALLY GENERATED, DO NOT EDIT ****
size_t serialize_data_pack(const struct data_pack *source, uint8_t *outputBuffer, size_t outputBufferLength) {
    uint32_t temporary32;
    uint16_t temporary16;

    if(!outputBuffer) {
        return -1;
    }else if(outputBufferLength < DATA_PACK_SERIALIZED_SIZE) {
        return -2;
    }

    memcpy(outputBuffer, &(source->height), sizeof(uint8_t));
    outputBuffer += sizeof(uint8_t);

    temporary16 = htons(source->weight);
    memcpy(outputBuffer, &temporary16, sizeof(uint16_t));
    outputBuffer += sizeof(uint16_t);

    temporary32 = htonl(source->position[0]);
    memcpy(outputBuffer, &temporary32, sizeof(uint32_t));
    outputBuffer += sizeof(uint32_t);

    temporary32 = htonl(source->position[1]);
    memcpy(outputBuffer, &temporary32, sizeof(uint32_t));
    outputBuffer += sizeof(uint32_t);

    return DATA_PACK_SERIALIZED_SIZE;
}

// **** AUTOMATICALLY GENERATED, DO NOT EDIT ****
size_t deserialize_data_pack(const uint8_t *data, size_t dataLength, struct data_pack *output) {
    if(!data) {
        return -1;
    }else if(dataLength < DATA_PACK_SERIALIZED_SIZE) {
        return -2;
    }

    memcpy(&(output->height), data, sizeof(uint8_t));
    data += sizeof(uint8_t);

    memcpy(&(output->weight), data, sizeof(uint16_t));
    output->weight = ntohs(output->weight);
    data += sizeof(uint16_t);

    memcpy(&(output->position[0]), data, sizeof(uint32_t));
    output->position[0] = ntohl(output->position[0]);
    data += sizeof(uint32_t);

    memcpy(&(output->position[1]), data, sizeof(uint32_t));
    output->position[1] = ntohl(output->position[1]);
    data += sizeof(uint32_t);

    return DATA_PACK_SERIALIZED_SIZE;
}

}

