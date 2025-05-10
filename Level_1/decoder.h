

#ifndef DECODER_H
#define DECODER_H
#include <inttypes.h>

#define timestamp_t uint64_t
#define pkt_len_t uint16_t
#define channel_id_t uint32_t
#define FRAME_SIZE 64

typedef struct
{
    uint32_t channel;
    uint64_t timestamp;
    uint8_t data[FRAME_SIZE];
} frame_packet_t;

int decode(pkt_len_t pkt_len, frame_packet_t *new_frame);

#endif