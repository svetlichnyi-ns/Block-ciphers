#ifndef AES_H
#define AES_H

#include <stddef.h>

/****************************** MACROS ******************************/
#define AES_BLOCK_SIZE 16

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE;
typedef unsigned int WORD;

typedef struct KPI {
    double encryption_mean_time, encryption_std, decryption_mean_time, decryption_std;
} KPI;

void xor_of_two_blocks_AES(BYTE* block_1, BYTE* block_2);
void AES_time_performance(unsigned long int number_of_blocks, int option_key, int user_choice, int NumOfExperiments, KPI* AES_results);

/*********************** FUNCTION DECLARATIONS **********************/
///////////////////
// AES
///////////////////
// Key setup must be done before any AES en/de-cryption functions can be used.
void aes_key_setup(const BYTE key[],          // The key, must be 128, 192, or 256 bits
                   WORD w[],                  // Output key schedule to be used later
                   int keysize);              // Bit length of the key, 128, 192, or 256

void aes_encrypt(const BYTE in[],             // 16 bytes of plaintext
                 BYTE out[],                  // 16 bytes of ciphertext
                 const WORD key[],            // From the key setup
                 int keysize);                // Bit length of the key, 128, 192, or 256

void aes_decrypt(const BYTE in[],             // 16 bytes of ciphertext
                 BYTE out[],                  // 16 bytes of plaintext
                 const WORD key[],            // From the key setup
                 int keysize);                // Bit length of the key, 128, 192, or 256

///////////////////
// Test functions
///////////////////
int aes_test();
int aes_ecb_test();
int aes_cbc_test();
int aes_ctr_test();

#endif   // AES_H