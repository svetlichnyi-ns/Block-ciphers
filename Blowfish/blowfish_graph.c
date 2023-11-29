#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include "blowfish.h"

int main() {
    srand(time(NULL));
    BYTE enc_buf[BLOWFISH_BLOCK_SIZE];
    BLOWFISH_KEY key;
    int pass = 1;
    clock_t key_setup_mean_time_array[53];
    clock_t encryption_mean_time_array[53];
    clock_t decryption_mean_time_array[53];
    long double key_setup_std_array[53];
    long double encryption_std_array[53];
    long double decryption_std_array[53];
    for (int i = 4; i <= 56; i++) {
        printf("Currently: %d stage.\n", i);
        int NumOfExperiments = 10000;
        clock_t* key_setup_times = (clock_t*) calloc (NumOfExperiments, sizeof(clock_t));
        clock_t* encryption_times = (clock_t*) calloc (NumOfExperiments, sizeof(clock_t));
        clock_t* decryption_times = (clock_t*) calloc (NumOfExperiments, sizeof(clock_t));
        for (int k = 0; k < NumOfExperiments; k++) {
            BYTE* key_experimental = (BYTE*) calloc (i, sizeof(BYTE));
            for (int j = 0; j < i; j++) {
                key_experimental[j] = rand() % 256;
            }
            BYTE message[BLOWFISH_BLOCK_SIZE];
            for (int j = 0; j < BLOWFISH_BLOCK_SIZE; j++) {
                message[j] = rand() % 256;
            }
            clock_t time_1 = clock();
            blowfish_key_setup(key_experimental, &key, i);
            clock_t time_2 = clock();
            blowfish_encrypt(message, enc_buf, &key);
            clock_t time_3 = clock();
            BYTE cyphertext[BLOWFISH_BLOCK_SIZE];
            memcpy(cyphertext, enc_buf, BLOWFISH_BLOCK_SIZE);
            clock_t time_4 = clock();
            blowfish_decrypt(cyphertext, enc_buf, &key);
            clock_t time_5 = clock();

            pass = pass && !memcmp(message, enc_buf, BLOWFISH_BLOCK_SIZE);

            free(key_experimental);
            key_setup_times[k] = (time_2 - time_1) * 1000000000 / CLOCKS_PER_SEC;
            encryption_times[k] = (time_3 - time_2) * 1000000000 / CLOCKS_PER_SEC;
            decryption_times[k] = (time_5 - time_4) * 1000000000 / CLOCKS_PER_SEC;
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
        key_setup_mean_time_array[i - 4] = key_setup_mean_time;
        encryption_mean_time_array[i - 4] = encryption_mean_time;
        decryption_mean_time_array[i - 4] = decryption_mean_time;
        
        clock_t sum_key_setup = 0;
        clock_t sum_encryption = 0;
        clock_t sum_decryption = 0;

        for (int k = 0; k < NumOfExperiments; k++) {
            sum_key_setup += (key_setup_times[k] - key_setup_mean_time) * (key_setup_times[k] - key_setup_mean_time);
            sum_encryption += (encryption_times[k] - encryption_mean_time) * (encryption_times[k] - encryption_mean_time);
            sum_decryption += (decryption_times[k] - decryption_mean_time) * (decryption_times[k] - decryption_mean_time);
        }

        key_setup_std_array[i - 4] = sqrtl((long double) sum_key_setup / (NumOfExperiments - 1));
        encryption_std_array[i - 4] = sqrtl((long double) sum_encryption / (NumOfExperiments - 1));
        decryption_std_array[i - 4] = sqrtl((long double) sum_decryption / (NumOfExperiments - 1));

        free(key_setup_times);
        free(encryption_times);
        free(decryption_times);
    }
    printf("PASS: %d\n", pass);
    printf("\nKEY SETUP:\n");
    for (int k = 0; k < 53; k++) {
        printf("%ld,\n", key_setup_mean_time_array[k]);
    }
    printf("\nKEY SETUP, STD:\n");
    for (int k = 0; k < 53; k++) {
        printf("%Lf,\n", key_setup_std_array[k]);
    }
    printf("\nENCRYPTION:\n");
    for (int k = 0; k < 53; k++) {
        printf("%ld,\n", encryption_mean_time_array[k]);
    }
    printf("\nENCRYPTION, STD:\n");
    for (int k = 0; k < 53; k++) {
        printf("%Lf,\n", encryption_std_array[k]);
    }
    printf("\nDECRYPTION:\n");
    for (int k = 0; k < 53; k++) {
        printf("%ld,\n", decryption_mean_time_array[k]);
    }
    printf("\nDECRYPTION, STD:\n");
    for (int k = 0; k < 53; k++) {
        printf("%Lf,\n", decryption_std_array[k]);
    }
    return 0;
}