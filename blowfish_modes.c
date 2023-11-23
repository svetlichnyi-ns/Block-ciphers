#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
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

int main(int argc, char* argv[]) {
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
    //printf("Enter the length of the message (in 64 bit-blocks): ");
    //scanf("%lu", &number_of_blocks);
    number_of_blocks = atoi(argv[1]);
    unsigned long int length_of_message = number_of_blocks * BLOWFISH_BLOCK_SIZE;
    BYTE* message = (BYTE*) calloc (length_of_message, sizeof(BYTE));
    BYTE* cyphertext = (BYTE*) calloc (length_of_message, sizeof(BYTE));
    BYTE* decrypted_message = (BYTE*) calloc (length_of_message, sizeof(BYTE));

    int length_of_key;
    //printf("Enter the length of the key (in bytes): ");
    //scanf("%d", &length_of_key);
    length_of_key = atoi(argv[2]);
    BYTE* user_key = (BYTE*) calloc (length_of_key, sizeof(BYTE));

    int user_choice;
    user_choice = atoi(argv[3]);
    //printf("Which mode? 1 - ECB, 2 - CBC, 3 - PCBC, 4 - CFB, 5 - OFB, 6 - CTR\n");
    //scanf("%d", &user_choice);
    int NumOfExperiments = 10000;

    double* key_setup_times = (double*) calloc (NumOfExperiments, sizeof(double));
    double* encryption_times = (double*) calloc (NumOfExperiments, sizeof(double));
    double* decryption_times = (double*) calloc (NumOfExperiments, sizeof(double));

    for (int i = 0; i < NumOfExperiments; i++) {
        for (int j = 0; j < length_of_message; j++) {
            message[j] = rand() % 256;
        }
        for (int j = 0; j < length_of_key; j++) {
            user_key[j] = rand() % 256;
        }

        struct timeval time_1, time_2, time_3, time_4, time_5;
        
        gettimeofday(&time_1, NULL); // START OF KEY SETUP
        blowfish_key_setup(user_key, &key, length_of_key);
        gettimeofday(&time_2, NULL); // END OF KEY SETUP

        switch (user_choice) {
            case 1: // ECB
                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
                for (int k = 0; k < number_of_blocks; k++) {
                    extract_block(message, one_block, k);
                    blowfish_encrypt(one_block, enc_buf, &key);
                    insert_block(cyphertext, enc_buf, k);
                }
                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                for (int k = 0; k < number_of_blocks; k++) {
                    extract_block(cyphertext, one_block, k);
                    blowfish_decrypt(one_block, enc_buf, &key);
                    insert_block(decrypted_message, enc_buf, k);
                }
                gettimeofday(&time_5, NULL); // END OF DECRYPTION
                break;
            case 2: // CBC
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }

                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
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
                
                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
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

                gettimeofday(&time_5, NULL); // END OF DECRYPTION
                break;
            case 3: // PCBC
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }
                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
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
                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
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
                gettimeofday(&time_5, NULL); // END OF DECRYPTION
                break;
            case 4: // CFB
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }
                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
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
                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
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
                gettimeofday(&time_5, NULL); // END OF DECRYPTION
                break;
            case 5: // OFB
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }
                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
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
                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
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
                gettimeofday(&time_5, NULL); // END OF DECRYPTION
                break;
            case 6: // CTR
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE - 2; j++) { // the initialization of a counter
                    counter[j] = rand() % 256;
                }
                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
                for (int k = 0; k < number_of_blocks; k++) {
                    counter[BLOWFISH_BLOCK_SIZE - 2] = k / 256;
                    counter[BLOWFISH_BLOCK_SIZE - 1] = k % 256;
                    blowfish_encrypt(counter, enc_buf, &key);
                    extract_block(message, one_block, k);
                    xor_of_two_blocks(enc_buf, one_block);
                    insert_block(cyphertext, enc_buf, k);
                }
                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                for (int k = 0; k < number_of_blocks; k++) {
                    counter[BLOWFISH_BLOCK_SIZE - 2] = k / 256;
                    counter[BLOWFISH_BLOCK_SIZE - 1] = k % 256;
                    blowfish_encrypt(counter, enc_buf, &key);
                    extract_block(cyphertext, one_block, k);
                    xor_of_two_blocks(enc_buf, one_block);
                    insert_block(decrypted_message, enc_buf, k);
                }
                gettimeofday(&time_5, NULL); // END OF DECRYPTION
                break;
            default:
                printf("Error! This mode was not found!\n");
                return -1;
        }

        // CHECK THE RESULTS
        pass = pass && !memcmp(message, decrypted_message, length_of_message);

        key_setup_times[i] = ((time_2.tv_sec - time_1.tv_sec) * 1000000 + time_2.tv_usec - time_1.tv_usec) / 1000.0;
        encryption_times[i] = ((time_4.tv_sec - time_3.tv_sec) * 1000000 + time_4.tv_usec - time_3.tv_usec) / 1000.0;
        decryption_times[i] = ((time_5.tv_sec - time_4.tv_sec) * 1000000 + time_5.tv_usec - time_4.tv_usec) / 1000.0;
    }

    double key_setup_total_time = 0;
    double encryption_total_time = 0;
    double decryption_total_time = 0;
    for (int k = 0; k < NumOfExperiments; k++) {
        key_setup_total_time += key_setup_times[k];
        encryption_total_time += encryption_times[k];
        decryption_total_time += decryption_times[k];
    }
    double key_setup_mean_time = key_setup_total_time / NumOfExperiments;
    double encryption_mean_time = encryption_total_time / NumOfExperiments;
    double decryption_mean_time = decryption_total_time / NumOfExperiments;
    
    double sum_key_setup = 0;
    double sum_encryption = 0;
    double sum_decryption = 0;

    for (int k = 0; k < NumOfExperiments; k++) {
        sum_key_setup += pow(key_setup_times[k] - key_setup_mean_time, 2);
        sum_encryption += pow(encryption_times[k] - encryption_mean_time, 2);
        sum_decryption += pow(decryption_times[k] - decryption_mean_time, 2);
    }

    double key_setup_std = sqrt(sum_key_setup / (NumOfExperiments - 1));
    double encryption_std = sqrt(sum_encryption / (NumOfExperiments - 1));
    double decryption_std = sqrt(sum_decryption / (NumOfExperiments - 1));

    // PRINT THE RESULTS
    printf("\nKey setup: %f ± %f (milliseconds)\n", key_setup_mean_time, key_setup_std);
    printf("Encryption: %f ± %f (milliseconds)\n", encryption_mean_time, encryption_std);
    printf("Decryption: %f ± %f (milliseconds)\n", decryption_mean_time, decryption_std);

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