#include <stdio.h>
#include "decoder.h"

int decode(pkt_len_t pkt_len, frame_packet_t *new_frame)
{
    uint16_t frame_size;
    channel_id_t channel;

    // Frame size is the size of the packet minus the size of non-frame elements
    frame_size = pkt_len - (sizeof(new_frame->channel) + sizeof(new_frame->timestamp));
    channel = new_frame->channel;

    // The reference design doesn't use the timestamp, but you may want to in your design
    timestamp_t timestamp = new_frame->timestamp;
    printf("channel = %d\ntimestamp = %llu\n", channel, timestamp);
    // Check that we are subscribed to the channel...
    if (channel == 1)
    {
        /* The reference design doesn't need any extra work to decode, but your design likely will.
         *  Do any extra decoding here before returning the result to the host. */

        for (size_t i = 0; i < frame_size; i++)
        {
            new_frame->data[i] ^= 0xA1;
            printf("%c", new_frame->data[i]);
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Receiving unsubscribed channel data from channel %u\n", channel);
        return -1;
    }
}
