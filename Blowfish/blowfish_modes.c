#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "blowfish.h"

void xor_of_two_blocks(BYTE* block_1, BYTE* block_2) {
    for (int i = 0; i < BLOWFISH_BLOCK_SIZE; i++) {
        block_1[i] ^= block_2[i];
    }
    return;
}

int main(int argc, char* argv[]) {

    srand(0);

    BYTE enc_buf[BLOWFISH_BLOCK_SIZE];
    BYTE one_block[BLOWFISH_BLOCK_SIZE];
    BYTE initialize_vector[BLOWFISH_BLOCK_SIZE];
    BYTE counter[BLOWFISH_BLOCK_SIZE];
    BYTE tmp_buf[BLOWFISH_BLOCK_SIZE];
    BYTE feedback[BLOWFISH_BLOCK_SIZE];
    
    BLOWFISH_KEY key;
    int pass = 1;
    
    unsigned long int number_of_blocks;
    number_of_blocks = atoi(argv[1]);
    unsigned long int length_of_message = number_of_blocks * BLOWFISH_BLOCK_SIZE;

    BYTE* message = (BYTE*) calloc (length_of_message, sizeof(BYTE));
    BYTE* cyphertext = (BYTE*) calloc (length_of_message, sizeof(BYTE));
    BYTE* decrypted_message = (BYTE*) calloc (length_of_message, sizeof(BYTE));

    int length_of_key;
    length_of_key = atoi(argv[2]);
    BYTE* user_key = (BYTE*) calloc (length_of_key, sizeof(BYTE));

    int user_choice;
    user_choice = atoi(argv[3]);
    int NumOfExperiments = (int) 1e3;

    double* encryption_times = (double*) calloc (NumOfExperiments, sizeof(double));
    double* decryption_times = (double*) calloc (NumOfExperiments, sizeof(double));

    struct timeval time_1, time_2, time_3;

    for (int i = 0; i < NumOfExperiments; i++) {
        for (int j = 0; j < length_of_message; j++) {
            message[j] = rand() % 256;
        }
        for (int j = 0; j < length_of_key; j++) {
            user_key[j] = rand() % 256;
        }
        
        blowfish_key_setup(user_key, &key, length_of_key);

        switch (user_choice) {
            case 1: // ECB mode
                gettimeofday(&time_1, NULL); // START OF ENCRYPTION
                
                for (int k = 0; k < number_of_blocks; k++) {
                    blowfish_encrypt(&message[k * BLOWFISH_BLOCK_SIZE], &cyphertext[k * BLOWFISH_BLOCK_SIZE], &key);
                }

                gettimeofday(&time_2, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                for (int k = 0; k < number_of_blocks; k++) {
                    blowfish_decrypt(&cyphertext[k * BLOWFISH_BLOCK_SIZE], &decrypted_message[k * BLOWFISH_BLOCK_SIZE], &key);
                }

                gettimeofday(&time_3, NULL); // END OF DECRYPTION

                break;

            case 2: // CBC mode
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }

                gettimeofday(&time_1, NULL); // START OF ENCRYPTION
                
                memcpy(one_block, &message[0], BLOWFISH_BLOCK_SIZE);
                xor_of_two_blocks(one_block, initialize_vector);
                blowfish_encrypt(one_block, enc_buf, &key);
                memcpy(&cyphertext[0], enc_buf, BLOWFISH_BLOCK_SIZE);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    memcpy(one_block, &message[k * BLOWFISH_BLOCK_SIZE], BLOWFISH_BLOCK_SIZE);
                    xor_of_two_blocks(one_block, enc_buf);
                    blowfish_encrypt(one_block, enc_buf, &key);
                    memcpy(&cyphertext[k * BLOWFISH_BLOCK_SIZE], enc_buf, BLOWFISH_BLOCK_SIZE);
                }
                
                gettimeofday(&time_2, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                memcpy(feedback, &cyphertext[0], BLOWFISH_BLOCK_SIZE);
                blowfish_decrypt(feedback, enc_buf, &key);
                xor_of_two_blocks(enc_buf, initialize_vector);
                memcpy(&decrypted_message[0], enc_buf, BLOWFISH_BLOCK_SIZE);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    memcpy(tmp_buf, &cyphertext[k * BLOWFISH_BLOCK_SIZE], BLOWFISH_BLOCK_SIZE);
                    blowfish_decrypt(tmp_buf, enc_buf, &key);
                    xor_of_two_blocks(enc_buf, feedback);
                    memcpy(feedback, tmp_buf, BLOWFISH_BLOCK_SIZE);
                    memcpy(&decrypted_message[k * BLOWFISH_BLOCK_SIZE], enc_buf, BLOWFISH_BLOCK_SIZE);
                }

                gettimeofday(&time_3, NULL); // END OF DECRYPTION
                
                break;

            case 3: // PCBC mode
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }

                gettimeofday(&time_1, NULL); // START OF ENCRYPTION

                memcpy(one_block, &message[0], BLOWFISH_BLOCK_SIZE);
                memcpy(feedback, one_block, BLOWFISH_BLOCK_SIZE);
                xor_of_two_blocks(one_block, initialize_vector);
                blowfish_encrypt(one_block, enc_buf, &key);
                memcpy(&cyphertext[0], enc_buf, BLOWFISH_BLOCK_SIZE);
                xor_of_two_blocks(feedback, enc_buf);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    memcpy(one_block, &message[k * BLOWFISH_BLOCK_SIZE], BLOWFISH_BLOCK_SIZE);
                    memcpy(tmp_buf, one_block, BLOWFISH_BLOCK_SIZE);
                    xor_of_two_blocks(one_block, feedback);
                    blowfish_encrypt(one_block, enc_buf, &key);
                    memcpy(&cyphertext[k * BLOWFISH_BLOCK_SIZE], enc_buf, BLOWFISH_BLOCK_SIZE);
                    xor_of_two_blocks(tmp_buf, enc_buf);
                    memcpy(feedback, tmp_buf, BLOWFISH_BLOCK_SIZE);
                }
                
                gettimeofday(&time_2, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                memcpy(one_block, &cyphertext[0], BLOWFISH_BLOCK_SIZE);
                memcpy(feedback, one_block, BLOWFISH_BLOCK_SIZE);
                blowfish_decrypt(one_block, enc_buf, &key);
                xor_of_two_blocks(enc_buf, initialize_vector);
                memcpy(&decrypted_message[0], enc_buf, BLOWFISH_BLOCK_SIZE);
                xor_of_two_blocks(feedback, enc_buf);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    memcpy(one_block, &cyphertext[k * BLOWFISH_BLOCK_SIZE], BLOWFISH_BLOCK_SIZE);
                    memcpy(tmp_buf, one_block, BLOWFISH_BLOCK_SIZE);
                    blowfish_decrypt(one_block, enc_buf, &key);
                    xor_of_two_blocks(enc_buf, feedback);
                    memcpy(&decrypted_message[k * BLOWFISH_BLOCK_SIZE], enc_buf, BLOWFISH_BLOCK_SIZE);
                    xor_of_two_blocks(tmp_buf, enc_buf);
                    memcpy(feedback, tmp_buf, BLOWFISH_BLOCK_SIZE);
                }
                
                gettimeofday(&time_3, NULL); // END OF DECRYPTION
                
                break;

            case 4: // CFB mode
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }
                
                gettimeofday(&time_1, NULL); // START OF ENCRYPTION
                
                blowfish_encrypt(initialize_vector, enc_buf, &key);
                memcpy(one_block, &message[0], BLOWFISH_BLOCK_SIZE);
                xor_of_two_blocks(one_block, enc_buf);
                memcpy(&cyphertext[0], one_block, BLOWFISH_BLOCK_SIZE);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    blowfish_encrypt(one_block, enc_buf, &key);
                    memcpy(one_block, &message[k * BLOWFISH_BLOCK_SIZE], BLOWFISH_BLOCK_SIZE);
                    xor_of_two_blocks(one_block, enc_buf);
                    memcpy(&cyphertext[k * BLOWFISH_BLOCK_SIZE], one_block, BLOWFISH_BLOCK_SIZE);
                }
                
                gettimeofday(&time_2, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                blowfish_encrypt(initialize_vector, enc_buf, &key);
                memcpy(one_block, &cyphertext[0], BLOWFISH_BLOCK_SIZE);
                xor_of_two_blocks(enc_buf, one_block);
                memcpy(&decrypted_message[0], enc_buf, BLOWFISH_BLOCK_SIZE);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    blowfish_encrypt(one_block, enc_buf, &key);
                    memcpy(one_block, &cyphertext[k * BLOWFISH_BLOCK_SIZE], BLOWFISH_BLOCK_SIZE);
                    xor_of_two_blocks(enc_buf, one_block);
                    memcpy(&decrypted_message[k * BLOWFISH_BLOCK_SIZE], enc_buf, BLOWFISH_BLOCK_SIZE);
                }

                gettimeofday(&time_3, NULL); // END OF DECRYPTION

                break;

            case 5: // OFB mode
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }
                
                gettimeofday(&time_1, NULL); // START OF ENCRYPTION
                
                blowfish_encrypt(initialize_vector, enc_buf, &key);
                memcpy(feedback, enc_buf, BLOWFISH_BLOCK_SIZE);
                memcpy(one_block, &message[0], BLOWFISH_BLOCK_SIZE);
                xor_of_two_blocks(enc_buf, one_block);
                memcpy(&cyphertext[0], enc_buf, BLOWFISH_BLOCK_SIZE);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    blowfish_encrypt(feedback, enc_buf, &key);
                    memcpy(feedback, enc_buf, BLOWFISH_BLOCK_SIZE);
                    memcpy(one_block, &message[k * BLOWFISH_BLOCK_SIZE], BLOWFISH_BLOCK_SIZE);
                    xor_of_two_blocks(enc_buf, one_block);
                    memcpy(&cyphertext[k * BLOWFISH_BLOCK_SIZE], enc_buf, BLOWFISH_BLOCK_SIZE);
                }
                
                gettimeofday(&time_2, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                blowfish_encrypt(initialize_vector, enc_buf, &key);
                memcpy(feedback, enc_buf, BLOWFISH_BLOCK_SIZE);
                memcpy(one_block, &cyphertext[0], BLOWFISH_BLOCK_SIZE);
                xor_of_two_blocks(enc_buf, one_block);
                memcpy(&decrypted_message[0], enc_buf, BLOWFISH_BLOCK_SIZE);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    blowfish_encrypt(feedback, enc_buf, &key);
                    memcpy(feedback, enc_buf, BLOWFISH_BLOCK_SIZE);
                    memcpy(one_block, &cyphertext[k * BLOWFISH_BLOCK_SIZE], BLOWFISH_BLOCK_SIZE);
                    xor_of_two_blocks(enc_buf, one_block);
                    memcpy(&decrypted_message[k * BLOWFISH_BLOCK_SIZE], enc_buf, BLOWFISH_BLOCK_SIZE);
                }
                
                gettimeofday(&time_3, NULL); // END OF DECRYPTION
                
                break;

            case 6: // CTR mode
                for (int j = 0; j < BLOWFISH_BLOCK_SIZE - 2; j++) { // the initialization of a counter
                    counter[j] = rand() % 256;
                }
                
                gettimeofday(&time_1, NULL); // START OF ENCRYPTION
                
                for (int k = 0; k < number_of_blocks; k++) {
                    counter[BLOWFISH_BLOCK_SIZE - 2] = k / 256;
                    counter[BLOWFISH_BLOCK_SIZE - 1] = k % 256;
                    blowfish_encrypt(counter, enc_buf, &key);
                    memcpy(one_block, &message[k * BLOWFISH_BLOCK_SIZE], BLOWFISH_BLOCK_SIZE);
                    xor_of_two_blocks(enc_buf, one_block);
                    memcpy(&cyphertext[k * BLOWFISH_BLOCK_SIZE], enc_buf, BLOWFISH_BLOCK_SIZE);
                }

                gettimeofday(&time_2, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                for (int k = 0; k < number_of_blocks; k++) {
                    counter[BLOWFISH_BLOCK_SIZE - 2] = k / 256;
                    counter[BLOWFISH_BLOCK_SIZE - 1] = k % 256;
                    blowfish_encrypt(counter, enc_buf, &key);
                    memcpy(one_block, &cyphertext[k * BLOWFISH_BLOCK_SIZE], BLOWFISH_BLOCK_SIZE);
                    xor_of_two_blocks(enc_buf, one_block);
                    memcpy(&decrypted_message[k * BLOWFISH_BLOCK_SIZE], enc_buf, BLOWFISH_BLOCK_SIZE);
                }

                gettimeofday(&time_3, NULL); // END OF DECRYPTION
                
                break;

            default:
                printf("Error! This mode was not found!\n");
                return -1;
        }

        pass = pass && !memcmp(message, decrypted_message, length_of_message);

        encryption_times[i] = ((time_2.tv_sec - time_1.tv_sec) * 1000000 + time_2.tv_usec - time_1.tv_usec) / 1000.0;
        decryption_times[i] = ((time_3.tv_sec - time_2.tv_sec) * 1000000 + time_3.tv_usec - time_2.tv_usec) / 1000.0;
    }

    // time_estimation
    double encryption_total_time = 0;
    double decryption_total_time = 0;
    for (int k = 0; k < NumOfExperiments; k++) {
        encryption_total_time += encryption_times[k];
        decryption_total_time += decryption_times[k];
    }
    
    double encryption_mean_time = encryption_total_time / NumOfExperiments;
    double decryption_mean_time = decryption_total_time / NumOfExperiments;
    
    double sum_encryption = 0;
    double sum_decryption = 0;

    for (int k = 0; k < NumOfExperiments; k++) {
        sum_encryption += pow(encryption_times[k] - encryption_mean_time, 2);
        sum_decryption += pow(decryption_times[k] - decryption_mean_time, 2);
    }

    double encryption_std = sqrt(sum_encryption / (NumOfExperiments - 1));
    double decryption_std = sqrt(sum_decryption / (NumOfExperiments - 1));

    // PRINT THE RESULTS
    printf("Encryption: %f ± %f (milliseconds)\n", encryption_mean_time, encryption_std);
    printf("Decryption: %f ± %f (milliseconds)\n", decryption_mean_time, decryption_std);

    // CHECK THE RESULTS
    if (pass) printf("TESTS PASSED!!!\n");
    else printf("TESTS FAILED(\n");
    
    free(message);
    free(cyphertext);
    free(decrypted_message);
    free(user_key);

    free(encryption_times);
    free(decryption_times);

    return 0;
}