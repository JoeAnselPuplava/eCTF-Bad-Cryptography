#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>

/**********************************************************
 ******************* PRIMITIVE TYPES **********************
 **********************************************************/

#define timestamp_t uint64_t
#define channel_id_t uint32_t
#define decoder_id_t uint32_t
#define pkt_len_t uint16_t

/**********************************************************
 *********************** CONSTANTS ************************
 **********************************************************/

#define FRAME_SIZE 64
#define TAG_SIZE 16

#pragma pack(push, 1) // Tells the compiler not to pad the struct members

typedef struct
{
    channel_id_t channel;
    timestamp_t timestamp;
    uint8_t data[FRAME_SIZE];
} frame_packet_t;

#pragma pack(pop) // Tells the compiler to resume padding struct members

int decode(pkt_len_t pkt_len, unsigned char *encrypted);

#endif