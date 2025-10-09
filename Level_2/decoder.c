#include <stdio.h>
#include "decoder.h"
#include <wolfssl/options.h>
#include "wolfssl/wolfcrypt/aes.h"
#include "wolfssl/wolfcrypt/hash.h"

uint8_t aes_key[KEY_SIZE] = {
    0x24, 0xf6, 0x75, 0x43, 0x64, 0xb9, 0x54, 0xcf,
    0xb3, 0x36, 0x71, 0xc8, 0x31, 0xda, 0x58, 0x2e,
    0xdb, 0x88, 0xb9, 0x42, 0x44, 0x23, 0x57, 0xd9,
    0xc9, 0x5a, 0xe9, 0x4e, 0x9f, 0x8f, 0xe2, 0x0d};

uint8_t cbc_iv[IV_SIZE] = {
    0xc6, 0xd3, 0x0c, 0x12, 0x4f, 0xbe, 0x47, 0xe8,
    0x6a, 0x02, 0xfc, 0x2a, 0x64, 0xb2, 0x30, 0xbf};

// #pragma pack(push, 1) // Tells the compiler not to pad the struct members

/** @brief Processes a packet containing frame data.
 *
 *  @param pkt_len A pointer to the incoming packet.
 *  @param new_frame A pointer to the incoming packet.
 *
 *  @return 0 if successful.  -1 if data is from unsubscribed channel.
 */
int decode(pkt_len_t pkt_len, team_frame_packet_t *new_frame)
{
    if (pkt_len != ENC_FRAME_SIZE)
    {
        printf("Failed to decrypt frame\n");
        return -1;
    }

    // Decrypt the frame
    Aes aes;
    byte dec[ENC_FRAME_SIZE];

    wc_AesSetKey(&aes, aes_key, KEY_SIZE, cbc_iv, AES_DECRYPTION);
    wc_AesCbcDecrypt(&aes, dec, new_frame->enc_frame, ENC_FRAME_SIZE);

    channel_id_t channel;

    frame_packet_t *dec_ptr = (frame_packet_t *)dec;

    channel = dec_ptr->channel;

    // Check that we are subscribed to the channel...
    if (channel == 1)
    {
        printf("channel = %d\ntimestamp = %llu\n", channel, dec_ptr->timestamp);
        printf("%s\n", dec_ptr->raw_data);
        return 0;
    }
    else
    {
        printf("Receiving unsubscribed channel data from channel %u\n", channel);
        return -1;
    }
}
