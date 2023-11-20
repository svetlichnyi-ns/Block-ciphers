#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include "blowfish.h"

void extract_block(BYTE* message, BYTE* block, int number_of_block) {
    for (int k = 0; k < BLOWFISH_BLOCK_SIZE; k++) {
        block[k] = message[BLOWFISH_BLOCK_SIZE * number_of_block + k];
    }
    return;
}

void insert_block(BYTE* cyphertext, BYTE* block, int number_of_block) {
    for (int k = 0; k < BLOWFISH_BLOCK_SIZE; k++) {
        cyphertext[BLOWFISH_BLOCK_SIZE * number_of_block + k] = block[k];
    }
    return;
}

void xor_of_two_blocks(BYTE* block_1, BYTE* block_2) {
    for (int i = 0; i < BLOWFISH_BLOCK_SIZE; i++) {
        block_1[i] ^= block_2[i];
    }
    return;
}

void copy_block(BYTE* block_1, BYTE* block_2) {
    for (int i = 0; i < BLOWFISH_BLOCK_SIZE; i++) {
        block_1[i] = block_2[i];
    }
    return;
}

int main() {
    srand(time(NULL));
    BYTE* enc_buf = (BYTE*) calloc (BLOWFISH_BLOCK_SIZE, sizeof(BYTE));
    BYTE* one_block = (BYTE*) calloc (BLOWFISH_BLOCK_SIZE, sizeof(BYTE));
    BYTE* initialize_vector = (BYTE*) calloc (BLOWFISH_BLOCK_SIZE, sizeof(BYTE));
    BYTE* counter = (BYTE*) calloc (BLOWFISH_BLOCK_SIZE, sizeof(BYTE));
    BYTE* tmp_buf = (BYTE*) calloc (BLOWFISH_BLOCK_SIZE, sizeof(BYTE));
    BYTE* feedback = (BYTE*) calloc (BLOWFISH_BLOCK_SIZE, sizeof(BYTE));
    BLOWFISH_KEY key;
    int pass = 1;
    
    unsigned long int number_of_blocks;
    printf("Enter the length of the message (in 64 bit-blocks): ");
    scanf("%lu", &number_of_blocks);
    unsigned long int length_of_message = number_of_blocks * BLOWFISH_BLOCK_SIZE;
    BYTE* message = (BYTE*) calloc (length_of_message, sizeof(BYTE));
    BYTE* cyphertext = (BYTE*) calloc (length_of_message, sizeof(BYTE));
    BYTE* decrypted_message = (BYTE*) calloc (length_of_message, sizeof(BYTE));

    int length_of_key;
    printf("Enter the length of the key (in bytes): ");
    scanf("%d", &length_of_key);
    BYTE* user_key = (BYTE*) calloc (length_of_key, sizeof(BYTE));

    int user_choice;
    printf("Which mode? 1 - ECB, 2 - CBC, 3 - PCBC, 4 - CFB, 5 - OFB, 6 - CTR\n");
    scanf("%d", &user_choice);
    int NumOfExperiments = 10000;

    clock_t* key_setup_times = (clock_t*) calloc (NumOfExperiments, sizeof(clock_t));
    clock_t* encryption_times = (clock_t*) calloc (NumOfExperiments, sizeof(clock_t));
    clock_t* decryption_times = (clock_t*) calloc (NumOfExperiments, sizeof(clock_t));

    for (int i = 0; i < NumOfExperiments; i++) {
        for (int j = 0; j < length_of_message; j++) {
            message[j] = rand() % 256;
        }
        for (int j = 0; j < length_of_key; j++) {
            user_key[j] = rand() % 256;
        }
        clock_t time_1 = clock(); // START OF KEY SETUP
        blowfish_key_setup(user_key, &key, length_of_key);
        clock_t time_2 = clock(); // END OF KEY SETUP

        clock_t time_3, time_4, time_5;

        switch (user_choice) {
            case 1: // ECB
                time_3 = clock(); // START OF ENCRYPTION
                for (int k = 0; k < number_of_blocks; k++) {
                    extract_block(message, one_block, k);
                    blowfish_encrypt(one_block, enc_buf, &key);
                    insert_block(cyphertext, enc_buf, k);
                }
                time_4 = clock(); // END OF ENCRYPTION and START OF DECRYPTION
                for (int k = 0; k < number_of_blocks; k++) {
                    extract_block(cyphertext, one_block, k);
                    blowfish_decrypt(one_block, enc_buf, &key);
                    insert_block(decrypted_message, enc_buf, k);
                }
                time_5 = clock(); // END OF DECRYPTION
                break;
            case 2: // CBC
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }

                time_3 = clock(); // START OF ENCRYPTION
                extract_block(message, one_block, 0);
                xor_of_two_blocks(one_block, initialize_vector);
                blowfish_encrypt(one_block, enc_buf, &key);
                insert_block(cyphertext, enc_buf, 0);

                for (int k = 1; k < number_of_blocks; k++) {
                    extract_block(message, one_block, k);
                    xor_of_two_blocks(one_block, enc_buf);
                    blowfish_encrypt(one_block, enc_buf, &key);
                    insert_block(cyphertext, enc_buf, k);
                }
                time_4 = clock(); // END OF ENCRYPTION and START OF DECRYPTION
                
                extract_block(cyphertext, feedback, 0);
                blowfish_decrypt(feedback, enc_buf, &key);
                xor_of_two_blocks(enc_buf, initialize_vector);
                insert_block(decrypted_message, enc_buf, 0);

                for (int k = 1; k < number_of_blocks; k++) {
                    extract_block(cyphertext, tmp_buf, k);
                    blowfish_decrypt(tmp_buf, enc_buf, &key);
                    xor_of_two_blocks(enc_buf, feedback);
                    copy_block(feedback, tmp_buf);
                    insert_block(decrypted_message, enc_buf, k);
                }

                time_5 = clock(); // END OF DECRYPTION
                break;
            case 3: // PCBC
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }
                time_3 = clock(); // START OF ENCRYPTION
                extract_block(message, one_block, 0);
                copy_block(feedback, one_block);
                xor_of_two_blocks(one_block, initialize_vector);
                blowfish_encrypt(one_block, enc_buf, &key);
                insert_block(cyphertext, enc_buf, 0);
                xor_of_two_blocks(feedback, enc_buf);
                for (int k = 1; k < number_of_blocks; k++) {
                    extract_block(message, one_block, k);
                    copy_block(tmp_buf, one_block);
                    xor_of_two_blocks(one_block, feedback);
                    blowfish_encrypt(one_block, enc_buf, &key);
                    insert_block(cyphertext, enc_buf, k);
                    xor_of_two_blocks(tmp_buf, enc_buf);
                    copy_block(feedback, tmp_buf);
                }
                time_4 = clock(); // END OF ENCRYPTION and START OF DECRYPTION
                extract_block(cyphertext, one_block, 0);
                copy_block(feedback, one_block);
                blowfish_decrypt(one_block, enc_buf, &key);
                xor_of_two_blocks(enc_buf, initialize_vector);
                insert_block(decrypted_message, enc_buf, 0);
                xor_of_two_blocks(feedback, enc_buf);
                for (int k = 1; k < number_of_blocks; k++) {
                    extract_block(cyphertext, one_block, k);
                    copy_block(tmp_buf, one_block);
                    blowfish_decrypt(one_block, enc_buf, &key);
                    xor_of_two_blocks(enc_buf, feedback);
                    insert_block(decrypted_message, enc_buf, k);
                    xor_of_two_blocks(tmp_buf, enc_buf);
                    copy_block(feedback, tmp_buf);
                }
                time_5 = clock(); // END OF DECRYPTION
                break;
            case 4: // CFB
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }
                time_3 = clock(); // START OF ENCRYPTION
                blowfish_encrypt(initialize_vector, enc_buf, &key);
                extract_block(message, one_block, 0);
                xor_of_two_blocks(one_block, enc_buf);
                insert_block(cyphertext, one_block, 0);
                for (int k = 1; k < number_of_blocks; k++) {
                    blowfish_encrypt(one_block, enc_buf, &key);
                    extract_block(message, one_block, k);
                    xor_of_two_blocks(one_block, enc_buf);
                    insert_block(cyphertext, one_block, k);
                }
                time_4 = clock(); // END OF ENCRYPTION and START OF DECRYPTION
                blowfish_encrypt(initialize_vector, enc_buf, &key);
                extract_block(cyphertext, one_block, 0);
                xor_of_two_blocks(enc_buf, one_block);
                insert_block(decrypted_message, enc_buf, 0);
                for (int k = 1; k < number_of_blocks; k++) {
                    blowfish_encrypt(one_block, enc_buf, &key);
                    extract_block(cyphertext, one_block, k);
                    xor_of_two_blocks(enc_buf, one_block);
                    insert_block(decrypted_message, enc_buf, k);
                }
                time_5 = clock(); // END OF DECRYPTION
                break;
            case 5: // OFB
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }
                time_3 = clock(); // START OF ENCRYPTION
                blowfish_encrypt(initialize_vector, enc_buf, &key);
                copy_block(feedback, enc_buf);
                extract_block(message, one_block, 0);
                xor_of_two_blocks(enc_buf, one_block);
                insert_block(cyphertext, enc_buf, 0);
                for (int k = 1; k < number_of_blocks; k++) {
                    blowfish_encrypt(feedback, enc_buf, &key);
                    copy_block(feedback, enc_buf);
                    extract_block(message, one_block, k);
                    xor_of_two_blocks(enc_buf, one_block);
                    insert_block(cyphertext, enc_buf, k);
                }
                time_4 = clock(); // END OF ENCRYPTION and START OF DECRYPTION
                blowfish_encrypt(initialize_vector, enc_buf, &key);
                copy_block(feedback, enc_buf);
                extract_block(cyphertext, one_block, 0);
                xor_of_two_blocks(enc_buf, one_block);
                insert_block(decrypted_message, enc_buf, 0);
                for (int k = 1; k < number_of_blocks; k++) {
                    blowfish_encrypt(feedback, enc_buf, &key);
                    copy_block(feedback, enc_buf);
                    extract_block(cyphertext, one_block, k);
                    xor_of_two_blocks(enc_buf, one_block);
                    insert_block(decrypted_message, enc_buf, k);
                }
                time_5 = clock(); // END OF DECRYPTION
                break;
            case 6: // CTR
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE - 2; j++) { // the initialization of a counter
                    counter[j] = rand() % 256;
                }
                time_3 = clock(); // START OF ENCRYPTION
                for (int k = 0; k < number_of_blocks; k++) {
                    counter[BLOWFISH_BLOCK_SIZE - 2] = k / 256;
                    counter[BLOWFISH_BLOCK_SIZE - 1] = k % 256;
                    blowfish_encrypt(counter, enc_buf, &key);
                    extract_block(message, one_block, k);
                    xor_of_two_blocks(enc_buf, one_block);
                    insert_block(cyphertext, enc_buf, k);
                }
                time_4 = clock(); // END OF ENCRYPTION and START OF DECRYPTION
                for (int k = 0; k < number_of_blocks; k++) {
                    counter[BLOWFISH_BLOCK_SIZE - 2] = k / 256;
                    counter[BLOWFISH_BLOCK_SIZE - 1] = k % 256;
                    blowfish_encrypt(counter, enc_buf, &key);
                    extract_block(cyphertext, one_block, k);
                    xor_of_two_blocks(enc_buf, one_block);
                    insert_block(decrypted_message, enc_buf, k);
                }
                time_5 = clock(); // END OF DECRYPTION
                break;
            default:
                printf("Error! This mode was not found!\n");
                return -1;
        }

        // CHECK THE RESULTS
        pass = pass && !memcmp(message, decrypted_message, length_of_message);
    
        key_setup_times[i] = (int) pow(10, 9) * (time_2 - time_1) / CLOCKS_PER_SEC;
        encryption_times[i] = (int) pow(10, 9) * (time_4 - time_3) / CLOCKS_PER_SEC;
        decryption_times[i] = (int) pow(10, 9) * (time_5 - time_4) / CLOCKS_PER_SEC;
    }

    clock_t key_setup_total_time = 0;
    clock_t encryption_total_time = 0;
    clock_t decryption_total_time = 0;
    for (int k = 0; k < NumOfExperiments; k++) {
        key_setup_total_time += key_setup_times[k];
        encryption_total_time += encryption_times[k];
        decryption_total_time += decryption_times[k];
    }
    clock_t key_setup_mean_time = key_setup_total_time / NumOfExperiments;
    clock_t encryption_mean_time = encryption_total_time / NumOfExperiments;
    clock_t decryption_mean_time = decryption_total_time / NumOfExperiments;
    
    clock_t sum_key_setup = 0;
    clock_t sum_encryption = 0;
    clock_t sum_decryption = 0;

    for (int k = 0; k < NumOfExperiments; k++) {
        sum_key_setup += pow(key_setup_times[k] - key_setup_mean_time, 2);
        sum_encryption += pow(encryption_times[k] - encryption_mean_time, 2);
        sum_decryption += pow(decryption_times[k] - decryption_mean_time, 2);
    }

    long double key_setup_std = sqrtl((long double) sum_key_setup / (NumOfExperiments - 1));
    long double encryption_std = sqrtl((long double) sum_encryption / (NumOfExperiments - 1));
    long double decryption_std = sqrtl((long double) sum_decryption / (NumOfExperiments - 1));

    // PRINT THE RESULTS
    printf("\nKey setup: %ld ± %Lf (ns)\n", key_setup_mean_time, key_setup_std);
    printf("Encryption: %ld ± %Lf (ns)\n", encryption_mean_time, encryption_std);
    printf("Decryption: %ld ± %Lf (ns)\n", decryption_mean_time, decryption_std);

    // CHECK THE RESULTS
    printf("PASS: %d\n", pass);
    
    free(message);
    free(cyphertext);
    free(decrypted_message);
    free(one_block);
    free(initialize_vector);
    free(counter);
    free(enc_buf);
    free(tmp_buf);
    free(feedback);
    free(user_key);

    free(key_setup_times);
    free(encryption_times);
    free(decryption_times);
    return 0;
}