import matplotlib.pyplot as plt
import numpy as np

numbers_of_blocks = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
numbers_of_bytes = [16 * numbers_of_blocks[i] for i in range(10)]

filenames = ["AES_1_encryption.txt",
             "AES_1_decryption.txt",
             "AES_2_encryption.txt",
             "AES_2_decryption.txt",
             "AES_3_encryption.txt",
             "AES_3_decryption.txt",
             "DES_encryption.txt",
             "DES_decryption.txt",
             "Blowfish_encryption.txt",
             "Blowfish_decryption.txt"]

headers = ['AES, encryption (length of key: 128 bits)',
           'AES, decryption (length of key: 128 bits)',
           'AES, encryption (length of key: 192 bits)',
           'AES, decryption (length of key: 192 bits)',
           'AES, encryption (length of key: 256 bits)',
           'AES, decryption (length of key: 256 bits)',
           'DES, encryption',
           'DES, decryption',
           'Blowfish, encryption (length of key: 56 bytes)',
           'Blowfish, decryption (length of key: 56 bytes)']

for i in range(10):
    data = []
    with open(filenames[i], "r") as file:
        for line in file:
            row = [float(num) for num in line.split()]
            data.append(row)

    plt.xlabel('Количество байт в шифруемом сообщении', size=26)
    plt.ylabel('Время исполнения, мс', size=26)
    plt.title(headers[i], size=32)
    plt.grid()
    plt.errorbar(numbers_of_bytes, data[0], yerr=data[1], fmt='-o')
    plt.errorbar(numbers_of_bytes, data[2], yerr=data[3], fmt='-o')
    plt.errorbar(numbers_of_bytes, data[4], yerr=data[5], fmt='-o')
    plt.errorbar(numbers_of_bytes, data[6], yerr=data[7], fmt='-o')
    plt.errorbar(numbers_of_bytes, data[8], yerr=data[9], fmt='-o')
    plt.errorbar(numbers_of_bytes, data[10], yerr=data[11], fmt='-o')
    plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
    plt.show()
    
