#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "global_secrets.h"
#include "decoder.h"

/* The simple crypto example included with the reference design is intended
 *  to be an example of how you *may* use cryptography in your design. You
 *  are not limited nor required to use this interface in your design. It is
 *  recommended for newer teams to start by only using the simple crypto
 *  library until they have a working design. */
#include "simple_crypto.h"

/** @brief Processes a packet containing frame data.
 *
 *  @param pkt_len A pointer to the incoming packet.
 *  @param new_frame A pointer to the incoming packet.
 *
 *  @return 0 if successful.  -1 if data is from unsubscribed channel.
 */
int decode(pkt_len_t pkt_len, unsigned char *encrypted)
{
    uint16_t frame_size;
    channel_id_t channel;
    frame_packet_t new_frame[pkt_len];

    // Frame size is the size of the packet minus the size of non-frame elements
    int status = decrypt_sym(encrypted, pkt_len, secret_key_imported, (uint8_t *)new_frame);
    if (status != 0)
    {
        printf("Decryption failed!");
        return -1;
    }

    frame_size = pkt_len - (sizeof(new_frame->channel) + sizeof(new_frame->timestamp)) - TAG_SIZE;
    channel = new_frame->channel;

    if (channel == 1)
    {
        printf("channel = %d\ntimestamp = %llu\n", new_frame->channel, new_frame->timestamp);
        for (int i = 0; i < frame_size; i++)
        {
            printf("%c", new_frame->data[i]);
        }

        return 0;
    }
    else
    {
        printf("Receiving unsubscribed channel data or an unsubcribed timestamp.  %u\n", channel);
        return -1;
    }
}
