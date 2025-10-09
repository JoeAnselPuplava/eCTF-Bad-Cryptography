#include <stdio.h>
#include "decoder.h"
#include "secrets.h"
#include "string.h"
#include "simple_crypto.h"

int decode(pkt_len_t pkt_len, uint8_t *new_frame)
{
    uint8_t decrypted_frame[pkt_len];

    if (pkt_len > MAX_PACKET_SIZE)
    {
        printf("packet length exceeds max length");
        return -1;
    }
    // Perform first round of decryption on entire packet
    if (decrypt_sym(new_frame, pkt_len, (uint8_t *)secret_key, decrypted_frame) != 0)
    {
        printf("failed to decrypt");
        return -1; // decryption failed
    }

    // cast the raw data as a frame_packet type in order to easily read the data.
    frame_packet_t *decrypted_packet = (frame_packet_t *)decrypted_frame;

    /*
     * This will calulate the size of the data with padding included.
     * decrypted_packet->size used here is the size of the data without padding
     * Padding needed for decryption to be successful (16 byte block size)
     */
    int padded_data_size = 0;

    if (((int)decrypted_packet->size % 16) != 0)
    {
        padded_data_size = (decrypted_packet->size + (16 - ((int)decrypted_packet->size % 16))); // rounds up to nearst multiple of 16
    }
    else
    {
        padded_data_size = decrypted_packet->size;
    }

    uint8_t decrypted_message[padded_data_size];      // decrypted data with padding
    uint8_t trimmed_encrypted_data[padded_data_size]; // encrypted data with padding

    // trims encrypted message with padding
    memcpy(trimmed_encrypted_data, decrypted_packet->data, padded_data_size);
    uint8_t trimmed_message[decrypted_packet->size]; // decrypted message without padding

    // Subscribed Channel
    if (decrypted_packet->channel == 1)
    {
        uint8_t *second_key = (uint8_t *)channel_keys[((decrypted_packet->channel) % 10007)];
        if (decrypt_sym(trimmed_encrypted_data, padded_data_size, second_key, decrypted_message) != 0)
        {
            printf("Failed to decrypt frame");
            return -1; // decryption failed
        }

        // trims off extra padding
        memcpy(trimmed_message, decrypted_message, decrypted_packet->size);
        printf("channel = %d\ntimestamp = %llu\n", decrypted_packet->channel, decrypted_packet->timestamp);
        for (size_t i = 0; i < decrypted_packet->size; i++)
        {
            printf("%c", trimmed_message[i]);
        }
        return 0;
    }
    // unsubscribed channel data
    else
    {
        printf("Receiving unsubscribed channel data from channel %u\n", decrypted_packet->channel);
        return -1;
    }
}
