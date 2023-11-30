#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "Blowfish/blowfish.h"
#include "AES/aes.h"
#include "DES/des.h"
#include "Base64/base64.h"

int main() {
    int i, j;
    int NumOfExperiments = (int) 1e3;
    unsigned long int number_of_blocks[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // arrays for mean values
    double AES_1_encryption_mean[6][10], AES_2_encryption_mean[6][10], AES_3_encryption_mean[6][10];
    double DES_encryption_mean[6][10];
    double Blowfish_encryption_mean[6][10];

    double AES_1_decryption_mean[6][10], AES_2_decryption_mean[6][10], AES_3_decryption_mean[6][10];
    double DES_decryption_mean[6][10];
    double Blowfish_decryption_mean[6][10];

    double EB64_coding_mean[1][10], EB64_decoding_mean[1][10], EB64_coding_std[1][10], EB64_decoding_std[1][10];

    // arrays for std values
    double AES_1_encryption_std[6][10], AES_2_encryption_std[6][10], AES_3_encryption_std[6][10];
    double DES_encryption_std[6][10];
    double Blowfish_encryption_std[6][10];

    double AES_1_decryption_std[6][10], AES_2_decryption_std[6][10], AES_3_decryption_std[6][10];
    double DES_decryption_std[6][10];
    double Blowfish_decryption_std[6][10];

    // collect the results
    for (i = 0; i < 6; i++) {
        printf("Mode: %d\n", i + 1);
        for (j = 0; j < 10; j++) {
            printf("Number of blocks (for AES; for DES and Blowfish - twice as large): %ld\n", number_of_blocks[j]);

            // AES-1
            {
                KPI results;
                AES_time_performance(number_of_blocks[j], 1, i + 1, NumOfExperiments, &results);
                
                AES_1_encryption_mean[i][j] = results.encryption_mean_time;
                AES_1_encryption_std[i][j] = results.encryption_std;
                
                AES_1_decryption_mean[i][j] = results.decryption_mean_time;
                AES_1_decryption_std[i][j] = results.decryption_std;
            }

            // AES-2
            {
                KPI results;
                AES_time_performance(number_of_blocks[j], 2, i + 1, NumOfExperiments, &results);
                
                AES_2_encryption_mean[i][j] = results.encryption_mean_time;
                AES_2_encryption_std[i][j] = results.encryption_std;
                
                AES_2_decryption_mean[i][j] = results.decryption_mean_time;
                AES_2_decryption_std[i][j] = results.decryption_std;
            }
            
            // AES-3
            {
                KPI results;
                AES_time_performance(number_of_blocks[j], 3, i + 1, NumOfExperiments, &results);
                
                AES_3_encryption_mean[i][j] = results.encryption_mean_time;
                AES_3_encryption_std[i][j] = results.encryption_std;
                
                AES_3_decryption_mean[i][j] = results.decryption_mean_time;
                AES_3_decryption_std[i][j] = results.decryption_std;
            }
            
            // DES
            {
                KPI results;
                DES_time_performance(2 * number_of_blocks[j], i + 1, NumOfExperiments, &results);
            
                DES_encryption_mean[i][j] = results.encryption_mean_time;
                DES_encryption_std[i][j] = results.encryption_std;
                
                DES_decryption_mean[i][j] = results.decryption_mean_time;
                DES_decryption_std[i][j] = results.decryption_std;
            }
            
            // Blowfish
            {
                KPI results;
                Blowfish_time_performance(2 * number_of_blocks[j], 56, i + 1, NumOfExperiments, &results);
            
                Blowfish_encryption_mean[i][j] = results.encryption_mean_time;
                Blowfish_encryption_std[i][j] = results.encryption_std;
                
                Blowfish_decryption_mean[i][j] = results.decryption_mean_time;
                Blowfish_decryption_std[i][j] = results.decryption_std;
            }
        }
    }

    EB64_time_performance();

    // print results for AES-1
    FILE* file_1;
    file_1 = fopen("AES_1_encryption.txt", "w");
    for (i = 0; i < 6; i++) {
        // encryption
        for (j = 0; j < 10; j++) {
            fprintf(file_1, "%lf ", AES_1_encryption_mean[i][j]);
        }

        fprintf(file_1, "\n");

        for (j = 0; j < 10; j++) {
            fprintf(file_1, "%lf ", AES_1_encryption_std[i][j]);
        }
        fprintf(file_1, "\n");
    }
    fclose(file_1);

    // print results for AES-1
    FILE* file_2;
    file_2 = fopen("AES_1_decryption.txt", "w");
    for (i = 0; i < 6; i++) {
        // decryption
        for (j = 0; j < 10; j++) {
            fprintf(file_2, "%lf ", AES_1_decryption_mean[i][j]);
        }
        
        fprintf(file_2, "\n");

        for (j = 0; j < 10; j++) {
            fprintf(file_2, "%lf ", AES_1_decryption_std[i][j]);
        }
        fprintf(file_2, "\n");

    }
    fclose(file_2);

    // print results for AES-2
    FILE* file_3;
    file_3 = fopen("AES_2_encryption.txt", "w");
    for (i = 0; i < 6; i++) {
        // encryption
        for (j = 0; j < 10; j++) {
            fprintf(file_3, "%lf ", AES_2_encryption_mean[i][j]);
        }
        fprintf(file_3, "\n");

        for (j = 0; j < 10; j++) {
            fprintf(file_3, "%lf ", AES_2_encryption_std[i][j]);
        }
        fprintf(file_3, "\n");
    }
    fclose(file_3);

    // print results for AES-2
    FILE* file_4;
    file_4 = fopen("AES_2_decryption.txt", "w");
    for (i = 0; i < 6; i++) {
        // decryption
        for (j = 0; j < 10; j++) {
            fprintf(file_4, "%lf ", AES_2_decryption_mean[i][j]);
        }
        fprintf(file_4, "\n");

        for (j = 0; j < 10; j++) {
            fprintf(file_4, "%lf ", AES_2_decryption_std[i][j]);
        }
        fprintf(file_4, "\n");
    }
    fclose(file_4);

    // print results for AES-3
    FILE* file_5;
    file_5 = fopen("AES_3_encryption.txt", "w");
    for (i = 0; i < 6; i++) {
        // encryption
        for (j = 0; j < 10; j++) {
            fprintf(file_5, "%lf ", AES_3_encryption_mean[i][j]);
        }
        fprintf(file_5, "\n");

        for (j = 0; j < 10; j++) {
            fprintf(file_5, "%lf ", AES_3_encryption_std[i][j]);
        }
        fprintf(file_5, "\n");
    }
    fclose(file_5);

    // print results for AES-3
    FILE* file_6;
    file_6 = fopen("AES_3_decryption.txt", "w");
    for (i = 0; i < 6; i++) {
        // decryption
        for (j = 0; j < 10; j++) {
            fprintf(file_6, "%lf ", AES_3_decryption_mean[i][j]);
        }
        fprintf(file_6, "\n");

        for (j = 0; j < 10; j++) {
            fprintf(file_6, "%lf ", AES_3_decryption_std[i][j]);
        }
        fprintf(file_6, "\n");
    }
    fclose(file_6);

    // print results for DES
    FILE* file_7;
    file_7 = fopen("DES_encryption.txt", "w");
    for (i = 0; i < 6; i++) {
        // encryption
        for (j = 0; j < 10; j++) {
            fprintf(file_7, "%lf ", DES_encryption_mean[i][j]);
        }
        fprintf(file_7, "\n");

        for (j = 0; j < 10; j++) {
            fprintf(file_7, "%lf ", DES_encryption_std[i][j]);
        }
        fprintf(file_7, "\n");
    }
    fclose(file_7);

    // print results for DES
    FILE* file_8;
    file_8 = fopen("DES_decryption.txt", "w");
    for (i = 0; i < 6; i++) {
        // decryption
        for (j = 0; j < 10; j++) {
            fprintf(file_8, "%lf ", DES_decryption_mean[i][j]);
        }
        fprintf(file_8, "\n");

        for (j = 0; j < 10; j++) {
            fprintf(file_8, "%lf ", DES_decryption_std[i][j]);
        }
        fprintf(file_8, "\n");
    }
    fclose(file_8);

    // print results for Blowfish
    FILE* file_9;
    file_9 = fopen("Blowfish_encryption.txt", "w");
    for (i = 0; i < 6; i++) {
        // encryption
        for (j = 0; j < 10; j++) {
            fprintf(file_9, "%lf ", Blowfish_encryption_mean[i][j]);
        }
        fprintf(file_9, "\n");

        for (j = 0; j < 10; j++) {
            fprintf(file_9, "%lf ", Blowfish_encryption_std[i][j]);
        }
        fprintf(file_9, "\n");
    }
    fclose(file_9);

    // print results for Blowfish
    FILE* file_10;
    file_10 = fopen("Blowfish_decryption.txt", "w");
    for (i = 0; i < 6; i++) {
        // decryption
        for (j = 0; j < 10; j++) {
            fprintf(file_10, "%lf ", Blowfish_decryption_mean[i][j]);
        }
        fprintf(file_10, "\n");

        for (j = 0; j < 10; j++) {
            fprintf(file_10, "%lf ", Blowfish_decryption_std[i][j]);
        }
        fprintf(file_10, "\n");

    }
    fclose(file_10);

    //fclose(ff);
    return 0;
}