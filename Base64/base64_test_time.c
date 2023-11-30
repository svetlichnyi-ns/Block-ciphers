#include <stdlib.h>
#include "base64.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>


#define STRINGLENGHT 76

static const BYTE charset[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"}; //алфавит
double avr_time_decode;
double avr_time_encode;
double delta_times_encode[20000];
double delta_times_decode[20000];
double sigma_encode;
double sigma_decode;

int key;

void base64_test(char *text)
{

	BYTE buf[20000];
	BYTE out[20000];
	
	size_t buf_len;
	int iterations = 1000;
	double sum_time_encode = 0;
	double sum_time_decode = 0;

	for (int i = 0; i < iterations; i++) {
		memset(buf, 0, sizeof(buf)); //очитска памяти переменных от мусора
		memset(out, 0, sizeof(out));

		struct timeval stop, start;
    	gettimeofday(&start, NULL);
		buf_len = base64_encode(text, buf, strlen(text), 1);
		gettimeofday(&stop, NULL);
		double delta_encode = ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) / 1000.0;
		sum_time_encode += delta_encode;
		delta_times_encode[i] = delta_encode;
		//printf("%s\n", buf);

		gettimeofday(&start, NULL);
		buf_len = base64_decode(buf, out, strlen(buf));
       	gettimeofday(&stop, NULL);
    	double delta_decode = ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) / 1000.0;
	    sum_time_decode += delta_decode;
		delta_times_decode[i] = delta_decode;
		//printf("%s\n", out);

		memset(buf, 0, sizeof(buf));
		memset(out, 0, sizeof(out));
	}
	avr_time_decode = sum_time_decode / iterations;
	avr_time_encode = sum_time_encode / iterations;
	sigma_decode = 0;
	sigma_encode = 0;
	
	for (int i = 0; i < iterations; i++){
		sigma_decode += (delta_times_decode[i] - avr_time_decode) * (delta_times_decode[i] - avr_time_decode);
		sigma_encode += (delta_times_encode[i] - avr_time_encode) * (delta_times_encode[i] - avr_time_encode);
	}
	sigma_decode = sqrt(sigma_decode / (iterations - 1));
	sigma_encode = sqrt(sigma_encode / (iterations - 1));
}

void EB64_time_performance() {
	int key = rand() % 256; //8 битный ключ
	int size_samples_array = 1600;
    int limit = 11;
    double times_array_encode[limit]; //массив с временами шифрования если вдруг захочется куда в файл выписать
	double times_array_decode[limit]; //массив с временами дешифрования
	double times_array_sigmas_encode[limit]; //массив с сигмами шифрования
	double times_array_sigmas_decode[limit]; //массив с сигмами дешифрования

    for(int j = 1; j < limit; ++j){
        char *text = malloc(size_samples_array * j * sizeof(char) + 2 * sizeof(char));
		for(int i = 0; i < size_samples_array * j; i+=10){
            text[i] = (char)('A' + rand() % 26);
            text[i + 1] = (char)('a' + rand() % 26);
            text[i + 2] = (char)('0' + rand() % 10);
            text[i + 3] = (char)('A' + rand() % 26);
            text[i + 4] = (char)('a' + rand() % 26);
            text[i + 5] = (char)('A' + rand() % 26);
            text[i + 6] = (char)('0' + rand() % 10);
            text[i + 7] = (char)('0' + rand() % 10);
            text[i + 8] = (char)('a' + rand() % 26);
            text[i + 9] = (char)('A' + rand() % 26);
        }
        base64_test(text);

		times_array_encode[j-1] = avr_time_encode;
		times_array_decode[j-1] = avr_time_decode;
		times_array_sigmas_encode[j-1] = sigma_encode;
		times_array_sigmas_decode[j-1] = sigma_decode;
		free(text);
    }
    
	// results for encoding
	FILE* file_1;
	file_1 = fopen("EB64_encoding.txt", "w");
	for (int j = 1; j < limit; j++) {
        fprintf(file_1, "%lf ", times_array_encode[j - 1]);
    }
    fprintf(file_1, "\n");
    for (int j = 1; j < limit; j++) {
        fprintf(file_1, "%lf ", times_array_sigmas_encode[j - 1]);
    }
	fclose(file_1);

	// results for decoding
	FILE* file_2;
	file_2 = fopen("EB64_decoding.txt", "w");
	for (int j = 1; j < limit; j++) {
        fprintf(file_2, "%lf ", times_array_decode[j - 1]);
    }
    fprintf(file_2, "\n");
    for (int j = 1; j < limit; j++) {
        fprintf(file_2, "%lf ", times_array_sigmas_decode[j - 1]);
    }
	fclose(file_2);

	return;
}