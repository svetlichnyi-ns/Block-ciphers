/*********************************************************************
* Filename:   blowfish.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding Blowfish implementation.
*********************************************************************/

#ifndef BLOWFISH_H
#define BLOWFISH_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>
#include "../AES/aes.h"

/****************************** MACROS ******************************/
#define BLOWFISH_BLOCK_SIZE 8           // Blowfish operates on 8 bytes at a time

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE;             // 8-bit byte
typedef unsigned int  WORD;             // 32-bit word, change to "long" for 16-bit machines

typedef struct {
   WORD p[18];
   WORD s[4][256];
} BLOWFISH_KEY;

void xor_of_two_blocks_Blowfish(BYTE* block_1, BYTE* block_2);
void Blowfish_time_performance(unsigned long int number_of_blocks, int length_of_key, int user_choice,
                               int NumOfExperiments, KPI* Blowfish_results);

/*********************** FUNCTION DECLARATIONS **********************/
void blowfish_key_setup(const BYTE user_key[], BLOWFISH_KEY *keystruct, size_t len);
void blowfish_encrypt(const BYTE in[], BYTE out[], const BLOWFISH_KEY *keystruct);
void blowfish_decrypt(const BYTE in[], BYTE out[], const BLOWFISH_KEY *keystruct);

#endif   // BLOWFISH_H
