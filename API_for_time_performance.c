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

int main() {
    int NumOfExperiments = (int) 1e3;
    unsigned long int number_of_blocks[3] = {10, 20, 30};

    // arrays for mean values
    double AES_1_encryption_mean[6][3], AES_2_encryption_mean[6][3], AES_3_encryption_mean[6][3];
    double DES_encryption_mean[6][3];
    double Blowfish_encryption_mean[6][3];

    double AES_1_decryption_mean[6][3], AES_2_decryption_mean[6][3], AES_3_decryption_mean[6][3];
    double DES_decryption_mean[6][3];
    double Blowfish_decryption_mean[6][3];

    // arrays for std values
    double AES_1_encryption_std[6][3];
    double AES_2_encryption_std[6][3];
    double AES_3_encryption_std[6][3];
    double DES_encryption_std[6][3];
    double Blowfish_encryption_std[6][3];

    double AES_1_decryption_std[6][3];
    double AES_2_decryption_std[6][3];
    double AES_3_decryption_std[6][3];
    double DES_decryption_std[6][3];
    double Blowfish_decryption_std[6][3];

    KPI results;

    // collect the results
    for (int i = 0; i < 6; i++) {
        printf("Mode: %d\n", i + 1);
        for (int j = 0; j < 3; j++) {
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

    FILE *ff;
    ff = fopen("results.txt", "w");

    for (int i = 0; i < 6; i++) {
        fprintf(ff, "Mode: %d\n", i + 1);
        // print results for AES-1
        fprintf(ff, "AES_1_encryption_mean = [");
        for (int j = 0; j < 2; j++) {
            fprintf(ff, "%lf, ", AES_1_encryption_mean[i][j]);
        }
        fprintf(ff, "%lf]\n", AES_1_encryption_mean[i][2]);

        // print results for AES-2
        fprintf(ff, "AES_2_encryption_mean = [");
        for (int j = 0; j < 2; j++) {
            fprintf(ff, "%lf, ", AES_2_encryption_mean[i][j]);
        }
        fprintf(ff, "%lf]\n", AES_2_encryption_mean[i][2]);

        // print results for AES-3
        fprintf(ff, "AES_3_encryption_mean = [");
        for (int j = 0; j < 2; j++) {
            fprintf(ff, "%lf, ", AES_3_encryption_mean[i][j]);
        }
        fprintf(ff, "%lf]\n", AES_3_encryption_mean[i][2]);

        // print results for DES
        fprintf(ff, "DES_encryption_mean = [");
        for (int j = 0; j < 2; j++) {
            fprintf(ff, "%lf, ", DES_encryption_mean[i][j]);
        }
        fprintf(ff, "%lf]\n", DES_encryption_mean[i][2]);

        // print results for Blowfish
        fprintf(ff, "Blowfish_encryption_mean = [");
        for (int j = 0; j < 2; j++) {
            fprintf(ff, "%lf, ", Blowfish_encryption_mean[i][j]);
        }
        fprintf(ff, "%lf]\n", Blowfish_encryption_mean[i][2]);

    }

    fclose(ff);
    return 0;
}
