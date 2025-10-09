

#ifndef DECODER_H
#define DECODER_H
#include <inttypes.h>
#include <stdint.h>

#define pkt_len_t uint16_t
#define channel_id_t uint32_t
#define timestamp_t uint64_t
#define FRAME_SIZE 64
#define ENC_FRAME_SIZE 96
#define KEY_SIZE 32
#define IV_SIZE 16

typedef struct
{
    channel_id_t channel;
    int rsvd1;
    timestamp_t timestamp;
    int pad_len;
    int rsvd2;
    uint8_t rsvd3[8];
    uint8_t raw_data[FRAME_SIZE];
} frame_packet_t;

typedef struct
{
    uint8_t enc_frame[ENC_FRAME_SIZE];
} team_frame_packet_t;

int decode(pkt_len_t pkt_len, team_frame_packet_t *new_frame);

#endif