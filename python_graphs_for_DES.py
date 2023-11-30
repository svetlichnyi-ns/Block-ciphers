import matplotlib.pyplot as plt
import numpy as np

numbers_of_blocks = [200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000]
numbers_of_bytes = [8 * numbers_of_blocks[i] for i in range(10)]

############################ ENCRYPTION ##########################

plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('DES, encryption', size=32)
plt.grid()

# ECB (1)
DES_encryption_mean = [1.037628, 2.154931, 3.282519, 4.387411, 5.197374, 6.286591, 7.591534, 8.680842, 9.444536, 10.865555]
DES_encryption_std = [0.100160, 0.430141, 0.708501, 0.936862, 0.614872, 0.771567, 1.305841, 1.445353, 1.138585, 1.745332]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

# CBC (2)
DES_encryption_mean = [1.104383, 2.122567, 3.323533, 4.176501, 5.194123, 6.370813, 7.715241, 9.015017, 9.337809, 10.711104]
DES_encryption_std = [0.259105, 0.399328, 0.704518, 0.459492, 0.462825, 0.772812, 1.380027, 1.598686, 0.548875, 1.342560]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

# PCBC (3)
DES_encryption_mean = [1.102065, 2.176084, 3.313012, 4.386403, 5.318512, 6.527293, 7.361898, 8.514983, 9.942162, 10.869308]
DES_encryption_std = [0.233317, 0.429242, 0.679940, 0.859692, 0.715881, 1.066250, 0.735770, 1.057792, 1.540866, 1.533564]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

# CFB (4)
DES_encryption_mean = [1.085713, 2.078236, 3.100611, 4.154955, 5.366156, 6.483851, 7.287632, 8.400757, 9.914948, 10.915925]
DES_encryption_std = [0.246423, 0.163245, 0.267912, 0.398411, 0.838041, 1.099465, 0.621884, 0.962492, 1.668757, 1.656039]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

# OFB (5)
DES_encryption_mean = [1.096241, 2.130228, 3.185981, 4.349638, 5.309273, 6.357515, 7.599397, 8.712970, 9.565850, 10.693276]
DES_encryption_std = [0.243609, 0.320579, 0.482099, 0.829057, 1.108902, 0.815490, 1.281735, 1.669690, 1.194243, 1.414311]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

# CTR (6)
DES_encryption_mean = [1.051589, 2.113575, 3.193528, 4.320937, 5.264324, 6.370272, 7.852911, 8.685253, 9.969030, 10.855586]
DES_encryption_std = [0.140315, 0.322678, 0.505084, 0.721005, 0.704760, 0.857030, 1.688205, 1.317518, 1.678844, 1.738302]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()

############################ DECRYPTION ##########################

plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('DES, decryption', size=32)
plt.grid()

# ECB (1)
DES_decryption_mean = [1.036004, 2.155934, 3.279665, 4.379636, 5.187489, 6.308601, 7.637728, 8.729326, 9.439593, 10.917843]
DES_decryption_std = [0.080873, 0.411044, 0.680577, 0.890463, 0.572945, 0.718591, 1.310963, 1.511642, 1.063547, 1.765453]
plt.errorbar(numbers_of_bytes, DES_decryption_mean, yerr=DES_decryption_std, fmt='-o')

# CBC (2)
DES_decryption_mean = [1.099450, 2.112871, 3.343861, 4.150361, 5.182167, 6.371592, 7.660586, 8.993188, 9.337972, 10.696074]
DES_decryption_std = [0.261768, 0.338776, 0.766832, 0.328234, 0.375157, 0.748941, 1.222083, 1.499262, 0.604435, 1.319912]
plt.errorbar(numbers_of_bytes, DES_decryption_mean, yerr=DES_decryption_std, fmt='-o')

# PCBC (3)
DES_decryption_mean = [1.108229, 2.176628, 3.303937, 4.377422, 5.318479, 6.514560, 7.329263, 8.449529, 10.022158, 10.884483]
DES_decryption_std = [0.273030, 0.433642, 0.612779, 0.843298, 0.679641, 0.906858, 0.599073, 0.875811, 1.722833, 1.559198]
plt.errorbar(numbers_of_bytes, DES_decryption_mean, yerr=DES_decryption_std, fmt='-o')

# CFB (4)
DES_decryption_mean = [1.084749, 2.075478, 3.090747, 4.158327, 5.352929, 6.493081, 7.277803, 8.372924, 9.961278, 11.005955]
DES_decryption_std = [0.246986, 0.148343, 0.142734, 0.450968, 0.813117, 1.116659, 0.589928, 0.806273, 1.757048, 1.857146]
plt.errorbar(numbers_of_bytes, DES_decryption_mean, yerr=DES_decryption_std, fmt='-o')

# OFB (5)
DES_decryption_mean = [1.098533, 2.136566, 3.191432, 4.374235, 5.284494, 6.396593, 7.635644, 8.706408, 9.599009, 10.718561]
DES_decryption_std = [0.246661, 0.327979, 0.507611, 0.887038, 1.076350, 0.955818, 1.336406, 1.504022, 1.305547, 1.399335]
plt.errorbar(numbers_of_bytes, DES_decryption_mean, yerr=DES_decryption_std, fmt='-o')

# CTR (6)
DES_decryption_mean = [1.049049, 2.115763, 3.199850, 4.308201, 5.292787, 6.374381, 7.814806, 8.679329, 9.916167, 10.803536]
DES_decryption_std = [0.109077, 0.337483, 0.479732, 0.698262, 0.734566, 0.867154, 1.524580, 1.367313, 1.500916, 1.588128]
plt.errorbar(numbers_of_bytes, DES_decryption_mean, yerr=DES_decryption_std, fmt='-o')

plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()