

#ifndef DECODER_H
#define DECODER_H
#include <inttypes.h>

#define timestamp_t uint64_t
#define pkt_len_t uint16_t
#define channel_id_t uint32_t
#define FRAME_SIZE 64
#define MAX_PACKET_SIZE 100
#define data_len_t uint32_t // just making it size of unsigned int so that packing the packet is easier > python has limited options

typedef struct
{
    channel_id_t channel;
    data_len_t size;
    timestamp_t timestamp;
    uint8_t data[FRAME_SIZE];
} frame_packet_t;

int decode(pkt_len_t pkt_len, uint8_t *new_frame);

#endif