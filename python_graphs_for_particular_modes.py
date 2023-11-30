import matplotlib.pyplot as plt
import numpy as np

numbers_of_blocks = [200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000]
numbers_of_bytes = [8 * numbers_of_blocks[i] for i in range(10)]

########################### ECB (1) #####################################
plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('ECB mode, encryption', size=32)
plt.grid()

# AES-1
AES_1_encryption_mean = [0.151369, 0.284564, 0.424700, 0.569365, 0.698102, 0.837333, 0.983023, 1.257675, 1.331647, 1.463812]
AES_1_encryption_std = [0.034795, 0.034502, 0.029468, 0.082805, 0.037148, 0.086460, 0.112224, 0.346041, 0.292482, 0.299053]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

# AES-2
AES_2_encryption_mean = [0.183695, 0.344780, 0.511129, 0.671645, 0.839642, 1.006692, 1.201904, 1.488592, 1.561953, 1.940305]
AES_2_encryption_std = [0.046352, 0.041888, 0.034477, 0.052263, 0.016038, 0.095478, 0.187024, 0.369208, 0.240303, 0.550759]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

# AES-3
AES_3_encryption_mean = [0.208156, 0.403873, 0.597180, 0.786308, 0.982035, 1.260190, 1.445785, 1.743599, 2.047580, 2.133474]
AES_3_encryption_std = [0.043508, 0.038402, 0.055040, 0.028428, 0.063591, 0.258348, 0.275247, 0.441110, 0.591886, 0.458606]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

# DES
DES_encryption_mean = [1.037628, 2.154931, 3.282519, 4.387411, 5.197374, 6.286591, 7.591534, 8.680842, 9.444536, 10.865555]
DES_encryption_std = [0.100160, 0.430141, 0.708501, 0.936862, 0.614872, 0.771567, 1.305841, 1.445353, 1.138585, 1.745332]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

# Blowfish
Blowfish_encryption_mean = [0.056537, 0.103769, 0.151480, 0.197629, 0.249010, 0.289066, 0.337308, 0.390166, 0.438936, 0.480561]
Blowfish_encryption_std = [0.015344, 0.026031, 0.035557, 0.031863, 0.053848, 0.038435, 0.053146, 0.075881, 0.085939, 0.071615]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

plt.legend(['AES-1', 'AES-2', 'AES-3', 'DES', 'Blowfish'], prop={'size': 26})

plt.show()

########################### CBC (2) #####################################
plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('CBC mode, encryption', size=32)
plt.grid()

# AES-1
AES_1_encryption_mean = [0.152944, 0.314471, 0.446350, 0.617841, 0.740424, 1.007318, 1.131989, 1.233369, 1.419115, 1.603533]
AES_1_encryption_std = [0.015406, 0.053415, 0.020093, 0.110669, 0.084852, 0.280640, 0.265687, 0.271435, 0.289860, 0.406920]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

# AES-2
AES_2_encryption_mean = [0.181643, 0.355681, 0.540215, 0.753954, 0.883208, 1.173884, 1.397860, 1.555448, 1.794041, 2.069535]
AES_2_encryption_std = [0.017517, 0.022061, 0.066299, 0.177735, 0.096951, 0.304965, 0.393025, 0.380613, 0.502461, 0.574155]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

# AES-3
AES_3_encryption_mean = [0.229867, 0.437310, 0.627769, 0.832465, 1.083424, 1.285148, 1.652439, 1.748046, 1.975317, 2.254758]
AES_3_encryption_std = [0.069915, 0.103374, 0.106749, 0.099643, 0.187794, 0.219488, 0.445159, 0.328139, 0.409852, 0.552616]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

# DES
DES_encryption_mean = [1.104383, 2.122567, 3.323533, 4.176501, 5.194123, 6.370813, 7.715241, 9.015017, 9.337809, 10.711104]
DES_encryption_std = [0.259105, 0.399328, 0.704518, 0.459492, 0.462825, 0.772812, 1.380027, 1.598686, 0.548875, 1.342560]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

# Blowfish
Blowfish_encryption_mean = [0.063701, 0.120081, 0.172896, 0.228358, 0.284632, 0.334628, 0.387475, 0.455730, 0.498949, 0.557943]
Blowfish_encryption_std = [0.016246, 0.028558, 0.032747, 0.042126, 0.054670, 0.038179, 0.034467, 0.097465, 0.058120, 0.077502]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

plt.legend(['AES-1', 'AES-2', 'AES-3', 'DES', 'Blowfish'], prop={'size': 26})

plt.show()

########################### PCBC (3) #####################################
plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('PCBC mode, encryption', size=32)
plt.grid()

# AES-1
AES_1_encryption_mean = [0.197602, 0.347294, 0.567104, 0.730279, 0.875684, 0.948547, 1.143880, 1.322669, 1.571424, 1.565079]
AES_1_encryption_std = [0.049906, 0.082679, 0.176679, 0.232269, 0.254309, 0.206311, 0.208581, 0.294149, 0.453766, 0.272423]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

# AES-2
AES_2_encryption_mean = [0.216290, 0.444265, 0.608978, 0.804479, 0.954979, 1.216417, 1.412662, 1.596616, 1.720381, 1.825387]
AES_2_encryption_std = [0.067068, 0.152009, 0.158186, 0.211699, 0.193102, 0.318386, 0.337369, 0.379913, 0.392729, 0.229293]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

# AES-3
AES_3_encryption_mean = [0.249624, 0.525328, 0.752823, 0.890603, 1.072184, 1.417311, 1.655375, 1.828661, 1.924832, 2.141260]
AES_3_encryption_std = [0.066106, 0.143577, 0.217220, 0.099729, 0.169941, 0.373205, 0.394604, 0.453487, 0.240140, 0.282294]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

# DES
DES_encryption_mean = [1.102065, 2.176084, 3.313012, 4.386403, 5.318512, 6.527293, 7.361898, 8.514983, 9.942162, 10.869308]
DES_encryption_std = [0.233317, 0.429242, 0.679940, 0.859692, 0.715881, 1.066250, 0.735770, 1.057792, 1.540866, 1.533564]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

# Blowfish
Blowfish_encryption_mean = [0.070342, 0.127282, 0.188760, 0.241835, 0.304263, 0.362549, 0.414832, 0.475741, 0.533263, 0.592852]
Blowfish_encryption_std = [0.022063, 0.028487, 0.042365, 0.031084, 0.056935, 0.057136, 0.033772, 0.052753, 0.055715, 0.070976]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

plt.legend(['AES-1', 'AES-2', 'AES-3', 'DES', 'Blowfish'], prop={'size': 26})

plt.show()

########################### CFB (4) #####################################
plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('CFB mode, encryption', size=32)
plt.grid()

# AES-1
AES_1_encryption_mean = [0.160142, 0.325024, 0.503486, 0.623913, 0.809393, 0.956049, 1.080025, 1.168030, 1.408647, 1.588531]
AES_1_encryption_std = [0.024163, 0.085664, 0.157844, 0.139837, 0.233504, 0.227921, 0.234650, 0.119039, 0.284384, 0.376602]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

# AES-2
AES_2_encryption_mean = [0.203422, 0.417953, 0.562482, 0.812692, 0.947783, 1.101154, 1.296053, 1.490773, 1.673232, 1.740001]
AES_2_encryption_std = [0.062095, 0.113487, 0.086105, 0.278833, 0.201313, 0.187828, 0.208790, 0.288010, 0.339325, 0.058295]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

# AES-3
AES_3_encryption_mean = [0.248640, 0.450487, 0.706202, 0.875953, 1.148375, 1.294218, 1.482775, 1.736299, 1.992893, 2.079825]
AES_3_encryption_std = [0.073765, 0.105756, 0.201055, 0.185310, 0.316585, 0.215425, 0.191120, 0.307989, 0.479237, 0.317262]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

# DES
DES_encryption_mean = [1.085713, 2.078236, 3.100611, 4.154955, 5.366156, 6.483851, 7.287632, 8.400757, 9.914948, 10.915925]
DES_encryption_std = [0.246423, 0.163245, 0.267912, 0.398411, 0.838041, 1.099465, 0.621884, 0.962492, 1.668757, 1.656039]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

# Blowfish
Blowfish_encryption_mean = [0.062671, 0.115148, 0.174929, 0.225058, 0.276770, 0.330163, 0.388608, 0.437823, 0.497846, 0.547609]
Blowfish_encryption_std = [0.015778, 0.017521, 0.040500, 0.043847, 0.039708, 0.036417, 0.065576, 0.057797, 0.088045, 0.075514]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

plt.legend(['AES-1', 'AES-2', 'AES-3', 'DES', 'Blowfish'], prop={'size': 26})

plt.show()

########################### OFB (5) #####################################
plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('OFB mode, encryption', size=32)
plt.grid()

# AES-1
AES_1_encryption_mean = [0.157708, 0.307239, 0.493940, 0.754243, 1.085922, 0.980921, 1.252680, 1.197149, 1.300122, 1.447491]
AES_1_encryption_std = [0.033017, 0.057431, 0.128654, 0.235433, 0.403735, 0.268261, 0.391603, 0.154130, 0.046242, 0.038471]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

# AES-2
AES_2_encryption_mean = [0.192914, 0.358355, 0.554067, 0.947985, 1.066892, 1.216129, 1.410678, 1.585290, 1.565891, 1.734839]
AES_2_encryption_std = [0.054694, 0.031144, 0.100290, 0.330607, 0.369778, 0.353862, 0.438667, 0.385242, 0.125733, 0.051061]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

# AES-3
AES_3_encryption_mean = [0.221319, 0.426759, 0.778526, 1.007511, 1.199415, 1.496399, 1.650965, 1.630909, 1.813021, 2.011807]
AES_3_encryption_std = [0.049092, 0.073531, 0.275472, 0.363284, 0.380381, 0.484058, 0.537403, 0.133068, 0.069951, 0.025005]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

# DES
DES_encryption_mean = [1.096241, 2.130228, 3.185981, 4.349638, 5.309273, 6.357515, 7.599397, 8.712970, 9.565850, 10.693276]
DES_encryption_std = [0.243609, 0.320579, 0.482099, 0.829057, 1.108902, 0.815490, 1.281735, 1.669690, 1.194243, 1.414311]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

# Blowfish
Blowfish_encryption_mean = [0.060617, 0.117540, 0.172989, 0.224395, 0.284214, 0.341105, 0.385523, 0.456325, 0.505300, 0.565111]
Blowfish_encryption_std = [0.007156, 0.024281, 0.031934, 0.025591, 0.052313, 0.067472, 0.030471, 0.094757, 0.087428, 0.092789]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

plt.legend(['AES-1', 'AES-2', 'AES-3', 'DES', 'Blowfish'], prop={'size': 26})

plt.show()

########################### CTR (6) #####################################
plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('CTR mode, encryption', size=32)
plt.grid()

# AES-1
AES_1_encryption_mean = [0.157208, 0.304789, 0.459745, 0.692826, 0.919465, 0.927643, 1.040804, 1.265828, 1.741629, 1.743949]
AES_1_encryption_std = [0.035441, 0.063561, 0.091679, 0.233272, 0.322099, 0.177578, 0.044662, 0.339814, 0.608571, 0.496976]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

# AES-2
AES_2_encryption_mean = [0.180811, 0.352602, 0.568105, 0.872966, 1.160202, 1.081796, 1.531924, 1.923181, 1.755977, 2.133087]
AES_2_encryption_std = [0.021144, 0.016161, 0.108785, 0.345883, 0.452666, 0.105131, 0.520107, 0.766997, 0.487609, 0.615054]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

# AES-3
AES_3_encryption_mean = [0.208507, 0.409560, 0.736693, 0.958757, 1.197547, 1.259285, 1.729505, 2.115044, 2.009310, 2.360055]
AES_3_encryption_std = [0.006940, 0.008045, 0.270222, 0.303973, 0.348525, 0.107364, 0.635492, 0.667956, 0.483236, 0.672056]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

# DES
DES_encryption_mean = [1.051589, 2.113575, 3.193528, 4.320937, 5.264324, 6.370272, 7.852911, 8.685253, 9.969030, 10.855586]
DES_encryption_std = [0.140315, 0.322678, 0.505084, 0.721005, 0.704760, 0.857030, 1.688205, 1.317518, 1.678844, 1.738302]
plt.errorbar(numbers_of_bytes, DES_encryption_mean, yerr=DES_encryption_std, fmt='-o')

# Blowfish
Blowfish_encryption_mean = [0.063037, 0.115609, 0.172001, 0.223008, 0.278315, 0.338362, 0.396752, 0.447193, 0.503070, 0.565066]
Blowfish_encryption_std = [0.015769, 0.018697, 0.032900, 0.024745, 0.037291, 0.067576, 0.083100, 0.084907, 0.099180, 0.131084]
plt.errorbar(numbers_of_bytes, Blowfish_encryption_mean, yerr=Blowfish_encryption_std, fmt='-o')

plt.legend(['AES-1', 'AES-2', 'AES-3', 'DES', 'Blowfish'], prop={'size': 26})

plt.show()