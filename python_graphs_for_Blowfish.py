import matplotlib.pyplot as plt
import numpy as np

numbers_of_blocks = [200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000]
numbers_of_bytes = [8 * numbers_of_blocks[i] for i in range(10)]

############################ ENCRYPTION ##########################

plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('Blowfish, encryption (length of key: 56 bytes)', size=32)
plt.grid()

# ECB (1)
Blowfish_encryption_mean = [0.056537, 0.103769, 0.151480, 0.197629, 0.249010, 0.289066, 0.337308, 0.390166, 0.438936, 0.480561]
Blowfish_encryption_std = [0.015344, 0.026031, 0.035557, 0.031863, 0.053848, 0.038435, 0.053146, 0.075881, 0.085939, 0.071615]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

# CBC (2)
Blowfish_encryption_mean = [0.063701, 0.120081, 0.172896, 0.228358, 0.284632, 0.334628, 0.387475, 0.455730, 0.498949, 0.557943]
Blowfish_encryption_std = [0.016246, 0.028558, 0.032747, 0.042126, 0.054670, 0.038179, 0.034467, 0.097465, 0.058120, 0.077502]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

# PCBC (3)
Blowfish_encryption_mean = [0.070342, 0.127282, 0.188760, 0.241835, 0.304263, 0.362549, 0.414832, 0.475741, 0.533263, 0.592852]
Blowfish_encryption_std = [0.022063, 0.028487, 0.042365, 0.031084, 0.056935, 0.057136, 0.033772, 0.052753, 0.055715, 0.070976]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

# CFB (4)
Blowfish_encryption_mean = [0.062671, 0.115148, 0.174929, 0.225058, 0.276770, 0.330163, 0.388608, 0.437823, 0.497846, 0.547609]
Blowfish_encryption_std = [0.015778, 0.017521, 0.040500, 0.043847, 0.039708, 0.036417, 0.065576, 0.057797, 0.088045, 0.075514]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

# OFB (5)
Blowfish_encryption_mean = [0.060617, 0.117540, 0.172989, 0.224395, 0.284214, 0.341105, 0.385523, 0.456325, 0.505300, 0.565111]
Blowfish_encryption_std = [0.007156, 0.024281, 0.031934, 0.025591, 0.052313, 0.067472, 0.030471, 0.094757, 0.087428, 0.092789]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

# CTR (6)
Blowfish_encryption_mean = [0.063037, 0.115609, 0.172001, 0.223008, 0.278315, 0.338362, 0.396752, 0.447193, 0.503070, 0.565066]
Blowfish_encryption_std = [0.015769, 0.018697, 0.032900, 0.024745, 0.037291, 0.067576, 0.083100, 0.084907, 0.099180, 0.131084]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()

############################ DECRYPTION ##########################

plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('Blowfish, decryption (length of key: 56 bytes)', size=32)
plt.grid()

# ECB (1)
Blowfish_decryption_mean = [0.056710, 0.104053, 0.151860, 0.197858, 0.247629, 0.289824, 0.336890, 0.389790, 0.439814, 0.479800]
Blowfish_decryption_std = [0.016276, 0.027812, 0.037397, 0.034066, 0.050708, 0.040549, 0.050150, 0.075238, 0.084336, 0.065345]
plt.errorbar(numbers_of_bytes, Blowfish_decryption_mean, yerr=Blowfish_decryption_std, fmt='-o')

# CBC (2)
Blowfish_decryption_mean = [0.063070, 0.118824, 0.172067, 0.226859, 0.282512, 0.332398, 0.384987, 0.453023, 0.494588, 0.553285]
Blowfish_decryption_std = [0.015583, 0.026905, 0.033544, 0.041407, 0.056134, 0.037042, 0.039163, 0.100370, 0.052016, 0.079497]
plt.errorbar(numbers_of_bytes, Blowfish_decryption_mean, yerr=Blowfish_decryption_std, fmt='-o')

# PCBC (3)
Blowfish_decryption_mean = [0.069860, 0.126419, 0.187414, 0.240418, 0.302688, 0.359380, 0.412456, 0.474582, 0.530162, 0.589478]
Blowfish_decryption_std = [0.021707, 0.027913, 0.042179, 0.030519, 0.055001, 0.053434, 0.028297, 0.054517, 0.048337, 0.058235]
plt.errorbar(numbers_of_bytes, Blowfish_decryption_mean, yerr=Blowfish_decryption_std, fmt='-o')

# CFB (4)
Blowfish_decryption_mean = [0.062594, 0.114797, 0.173223, 0.224842, 0.276147, 0.330184, 0.387393, 0.437346, 0.496078, 0.547762]
Blowfish_decryption_std = [0.015603, 0.016056, 0.039282, 0.042754, 0.034469, 0.040245, 0.060302, 0.051140, 0.079169, 0.074289]
plt.errorbar(numbers_of_bytes, Blowfish_decryption_mean, yerr=Blowfish_decryption_std, fmt='-o')

# OFB (5)
Blowfish_decryption_mean = [0.060660, 0.117411, 0.172747, 0.223908, 0.283680, 0.340120, 0.385806, 0.457269, 0.503920, 0.564619]
Blowfish_decryption_std = [0.007157, 0.023301, 0.030726, 0.023155, 0.051868, 0.064154, 0.026149, 0.098724, 0.085785, 0.088898]
plt.errorbar(numbers_of_bytes, Blowfish_decryption_mean, yerr=Blowfish_decryption_std, fmt='-o')

# CTR (6)
Blowfish_decryption_mean = [0.062911, 0.115638, 0.171676, 0.223038, 0.278735, 0.338127, 0.396243, 0.445353, 0.503526, 0.562792]
Blowfish_decryption_std = [0.015826, 0.017635, 0.032659, 0.026171, 0.040719, 0.066214, 0.081603, 0.075316, 0.101059, 0.116481]
plt.errorbar(numbers_of_bytes, Blowfish_decryption_mean, yerr=Blowfish_decryption_std, fmt='-o')

plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()