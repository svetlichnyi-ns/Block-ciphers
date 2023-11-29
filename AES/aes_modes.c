#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <sys/time.h>
#include "aes.h"

void xor_of_two_blocks(BYTE* block_1, BYTE* block_2) {
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        block_1[i] ^= block_2[i];
    }
    return;
}

int main(int argc, char* argv[]) {
    srand(0); //init random keys and messages

    WORD key_schedule[60];

    int pass = 1;
    unsigned long int number_of_blocks;

    BYTE enc_buf[AES_BLOCK_SIZE];
    BYTE one_block[AES_BLOCK_SIZE];
    BYTE initialize_vector[AES_BLOCK_SIZE];
    BYTE counter[AES_BLOCK_SIZE];
    BYTE tmp_buf[AES_BLOCK_SIZE];
    BYTE feedback[AES_BLOCK_SIZE];

    //printf("Enter the length of the message (in 128 bit-blocks): ");
    //scanf("%lu", &number_of_blocks);
    number_of_blocks = atoi(argv[1]);

    unsigned long int length_of_message = number_of_blocks * AES_BLOCK_SIZE; //in bytes

    BYTE* message = (BYTE*) calloc (length_of_message, sizeof(BYTE));
    BYTE* cyphertext = (BYTE*) calloc (length_of_message, sizeof(BYTE));
    BYTE* decrypted_message = (BYTE*) calloc (length_of_message, sizeof(BYTE));

    int option_key;
    /*do {
        printf("Choose the option for the length of the key (1 - 128 bits, 2 - 192 bits, 3 - 256 bits): ");
        scanf("%d", &option_key);
    } while((option_key > 3) || (option_key < 1));*/

    option_key = atoi(argv[2]);

    int length_of_key_bytes = 16 + (option_key - 1) * 8; //length of key in bytes
    int keysize = length_of_key_bytes * 8; // length of key in bits

    //debug
    //printf("Key_size = %d bits\n", keysize);

    BYTE* user_key = (BYTE*) calloc (length_of_key_bytes, sizeof(BYTE));

    int user_choice;
    /*printf("Which mode? (1 - ECB, 2 - CBC, 3 - PCBC, 4 - CFB, 5 - OFB, 6 - CTR)\n");
    scanf("%d", &user_choice);*/
    user_choice = atoi(argv[3]);

    int NumOfExperiments = (int) 1e4;

    double* key_setup_times = (double*) calloc (NumOfExperiments, sizeof(double));
    double* encryption_times = (double*) calloc (NumOfExperiments, sizeof(double));
    double* decryption_times = (double*) calloc (NumOfExperiments, sizeof(double));

    struct timeval time_1, time_2, time_3, time_4, time_5;

    for (int i = 0; i < NumOfExperiments; i++) {
        for (int j = 0; j < length_of_message; j++) {
            message[j] = rand() % 256;
        }
        for (int j = 0; j < length_of_key_bytes; j++) {
            user_key[j] = rand() % 256;
        }

        gettimeofday(&time_1, NULL); // START OF KEY SETUP
        aes_key_setup(user_key, key_schedule, keysize);
        gettimeofday(&time_2, NULL); // END OF KEY SETUP

        switch (user_choice) {
            case 1: // ECB mode
                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
                
                for (int k = 0; k < number_of_blocks; k++) {
                    aes_encrypt(&message[k * AES_BLOCK_SIZE], &cyphertext[k * AES_BLOCK_SIZE], key_schedule, keysize);
                }

                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                for (int k = 0; k < number_of_blocks; k++) {
                    aes_decrypt(&cyphertext[k * AES_BLOCK_SIZE], &decrypted_message[k * AES_BLOCK_SIZE], key_schedule, keysize);
                }

                gettimeofday(&time_5, NULL); // END OF DECRYPTION
                
                break;

            case 2: // CBC mode
                for (int j = 0; j < AES_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }

                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
                
                memcpy(one_block, &message[0], AES_BLOCK_SIZE);
                xor_of_two_blocks(one_block, initialize_vector);
                aes_encrypt(one_block, enc_buf, key_schedule, keysize);
                memcpy(&cyphertext[0], enc_buf, AES_BLOCK_SIZE);

                for (int k = 1; k < number_of_blocks; k++) {
                    memcpy(one_block, &message[k * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
                    xor_of_two_blocks(one_block, enc_buf);
                    aes_encrypt(one_block, enc_buf, key_schedule, keysize);
                    memcpy(&cyphertext[k * AES_BLOCK_SIZE], enc_buf, AES_BLOCK_SIZE);
                }

                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                memcpy(feedback, &cyphertext[0], AES_BLOCK_SIZE);
                aes_decrypt(feedback, enc_buf, key_schedule, keysize);
                xor_of_two_blocks(enc_buf, initialize_vector);
                memcpy(&decrypted_message[0], enc_buf, AES_BLOCK_SIZE);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    memcpy(tmp_buf, &cyphertext[k * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
                    aes_decrypt(tmp_buf, enc_buf, key_schedule, keysize);
                    xor_of_two_blocks(enc_buf, feedback);
                    memcpy(feedback, tmp_buf, AES_BLOCK_SIZE);
                    memcpy(&decrypted_message[k * AES_BLOCK_SIZE], enc_buf, AES_BLOCK_SIZE);
                }

                gettimeofday(&time_5, NULL); // END OF DECRYPTION
                
                break;

            case 3: // PCBC mode
                for (int j = 0; j < AES_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }

                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
                
                memcpy(one_block, &message[0], AES_BLOCK_SIZE);
                memcpy(feedback, one_block, AES_BLOCK_SIZE);
                xor_of_two_blocks(one_block, initialize_vector);
                aes_encrypt(one_block, enc_buf, key_schedule, keysize);
                memcpy(&cyphertext[0], enc_buf, AES_BLOCK_SIZE);
                xor_of_two_blocks(feedback, enc_buf);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    memcpy(one_block, &message[k * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
                    memcpy(tmp_buf, one_block, AES_BLOCK_SIZE);
                    xor_of_two_blocks(one_block, feedback);
                    aes_encrypt(one_block, enc_buf, key_schedule, keysize);
                    memcpy(&cyphertext[k * AES_BLOCK_SIZE], enc_buf, AES_BLOCK_SIZE);
                    xor_of_two_blocks(tmp_buf, enc_buf);
                    memcpy(feedback, tmp_buf, AES_BLOCK_SIZE);
                }

                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                memcpy(one_block, &cyphertext[0], AES_BLOCK_SIZE);
                memcpy(feedback, one_block, AES_BLOCK_SIZE);
                aes_decrypt(one_block, enc_buf, key_schedule, keysize);
                xor_of_two_blocks(enc_buf, initialize_vector);
                memcpy(&decrypted_message[0], enc_buf, AES_BLOCK_SIZE);
                xor_of_two_blocks(feedback, enc_buf);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    memcpy(one_block, &cyphertext[k * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
                    memcpy(tmp_buf, one_block, AES_BLOCK_SIZE);
                    aes_decrypt(one_block, enc_buf, key_schedule, keysize);
                    xor_of_two_blocks(enc_buf, feedback);
                    memcpy(&decrypted_message[k * AES_BLOCK_SIZE], enc_buf, AES_BLOCK_SIZE);
                    xor_of_two_blocks(tmp_buf, enc_buf);
                    memcpy(feedback, tmp_buf, AES_BLOCK_SIZE);
                }

                gettimeofday(&time_5, NULL); // END OF DECRYPTION

                break;

            case 4: // CFB mode
                for (int j = 0; j < AES_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }

                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
                
                aes_encrypt(initialize_vector, enc_buf, key_schedule, keysize);
                memcpy(one_block, &message[0], AES_BLOCK_SIZE);
                xor_of_two_blocks(one_block, enc_buf);
                memcpy(&cyphertext[0], one_block, AES_BLOCK_SIZE);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    aes_encrypt(one_block, enc_buf, key_schedule, keysize);
                    memcpy(one_block, &message[k * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
                    xor_of_two_blocks(one_block, enc_buf);
                    memcpy(&cyphertext[k * AES_BLOCK_SIZE], one_block, AES_BLOCK_SIZE);
                }

                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                aes_encrypt(initialize_vector, enc_buf, key_schedule, keysize);
                memcpy(one_block, &cyphertext[0], AES_BLOCK_SIZE);
                xor_of_two_blocks(enc_buf, one_block);
                memcpy(&decrypted_message[0], enc_buf, AES_BLOCK_SIZE);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    aes_encrypt(one_block, enc_buf, key_schedule, keysize);
                    memcpy(one_block, &cyphertext[k * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
                    xor_of_two_blocks(enc_buf, one_block);
                    memcpy(&decrypted_message[k * AES_BLOCK_SIZE], enc_buf, AES_BLOCK_SIZE);
                }

                gettimeofday(&time_5, NULL); // END OF DECRYPTION
                
                break;

            case 5: // OFB mode
                for (int j = 0; j < AES_BLOCK_SIZE; j++) { // the initialization of an IV
                    initialize_vector[j] = rand() % 256;
                }

                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
                
                aes_encrypt(initialize_vector, enc_buf, key_schedule, keysize);
                memcpy(feedback, enc_buf, AES_BLOCK_SIZE);
                memcpy(one_block, &message[0], AES_BLOCK_SIZE);
                xor_of_two_blocks(enc_buf, one_block);
                memcpy(&cyphertext[0], enc_buf, AES_BLOCK_SIZE);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    aes_encrypt(feedback, enc_buf, key_schedule, keysize);
                    memcpy(feedback, enc_buf, AES_BLOCK_SIZE);
                    memcpy(one_block, &message[k * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
                    xor_of_two_blocks(enc_buf, one_block);
                    memcpy(&cyphertext[k * AES_BLOCK_SIZE], enc_buf, AES_BLOCK_SIZE);
                }

                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                aes_encrypt(initialize_vector, enc_buf, key_schedule, keysize);
                memcpy(feedback, enc_buf, AES_BLOCK_SIZE);
                memcpy(one_block, &cyphertext[0], AES_BLOCK_SIZE);
                xor_of_two_blocks(enc_buf, one_block);
                memcpy(&decrypted_message[0], enc_buf, AES_BLOCK_SIZE);
                
                for (int k = 1; k < number_of_blocks; k++) {
                    aes_encrypt(feedback, enc_buf, key_schedule, keysize);
                    memcpy(feedback, enc_buf, AES_BLOCK_SIZE);
                    memcpy(one_block, &cyphertext[k * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
                    xor_of_two_blocks(enc_buf, one_block);
                    memcpy(&decrypted_message[k * AES_BLOCK_SIZE], enc_buf, AES_BLOCK_SIZE);
                }

                gettimeofday(&time_5, NULL); // END OF DECRYPTION

                break;

            case 6: // CTR mode
                for (int j = 0; j < AES_BLOCK_SIZE - 2; j++) { // the initialization of a counter
                    counter[j] = rand() % 256;
                }
                
                gettimeofday(&time_3, NULL); // START OF ENCRYPTION
                
                for (int k = 0; k < number_of_blocks; k++) {
                    counter[AES_BLOCK_SIZE - 2] = k / 256;
                    counter[AES_BLOCK_SIZE - 1] = k % 256;
                    aes_encrypt(counter, enc_buf, key_schedule, keysize);
                    memcpy(one_block, &message[k * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
                    xor_of_two_blocks(enc_buf, one_block);
                    memcpy(&cyphertext[k * AES_BLOCK_SIZE], enc_buf, AES_BLOCK_SIZE);
                }

                gettimeofday(&time_4, NULL); // END OF ENCRYPTION and START OF DECRYPTION
                
                for (int k = 0; k < number_of_blocks; k++) {
                    counter[AES_BLOCK_SIZE - 2] = k / 256;
                    counter[AES_BLOCK_SIZE - 1] = k % 256;
                    aes_encrypt(counter, enc_buf, key_schedule, keysize);
                    memcpy(one_block, &cyphertext[k * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
                    xor_of_two_blocks(enc_buf, one_block);
                    memcpy(&decrypted_message[k * AES_BLOCK_SIZE], enc_buf, AES_BLOCK_SIZE);
                }

                gettimeofday(&time_5, NULL); // END OF DECRYPTION

                break;

            default:
                printf("Error! This mode was not found!\n");
                return -1;
        }

        pass = pass && !memcmp(message, decrypted_message, length_of_message);

        key_setup_times[i] = ((time_2.tv_sec - time_1.tv_sec) * 1000000 + time_2.tv_usec - time_1.tv_usec) / 1000.0;
        encryption_times[i] = ((time_4.tv_sec - time_3.tv_sec) * 1000000 + time_4.tv_usec - time_3.tv_usec) / 1000.0;
        decryption_times[i] = ((time_5.tv_sec - time_4.tv_sec) * 1000000 + time_5.tv_usec - time_4.tv_usec) / 1000.0;
    }

    // time_estimation
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
    if (pass) printf("TESTS PASSED!!!\n");
    else printf("TESTS FAILED(\n");

    free(message);
    free(cyphertext);
    free(decrypted_message);
    free(user_key);

    free(key_setup_times);
    free(encryption_times);
    free(decryption_times);
    
    return 0;
}