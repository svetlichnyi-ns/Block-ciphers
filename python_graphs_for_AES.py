import matplotlib.pyplot as plt
import numpy as np

numbers_of_blocks = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
numbers_of_bytes = [16 * numbers_of_blocks[i] for i in range(10)]

############################ ENCRYPTION ##########################

# AES-1

plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('AES, encryption (length of key: 128 bits)', size=32)
plt.grid()

# ECB (1)
AES_1_encryption_mean = [0.151369, 0.284564, 0.424700, 0.569365, 0.698102, 0.837333, 0.983023, 1.257675, 1.331647, 1.463812]
AES_1_encryption_std = [0.034795, 0.034502, 0.029468, 0.082805, 0.037148, 0.086460, 0.112224, 0.346041, 0.292482, 0.299053]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

# CBC (2)
AES_1_encryption_mean = [0.152944, 0.314471, 0.446350, 0.617841, 0.740424, 1.007318, 1.131989, 1.233369, 1.419115, 1.603533]
AES_1_encryption_std = [0.015406, 0.053415, 0.020093, 0.110669, 0.084852, 0.280640, 0.265687, 0.271435, 0.289860, 0.406920]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

# PCBC (3)
AES_1_encryption_mean = [0.197602, 0.347294, 0.567104, 0.730279, 0.875684, 0.948547, 1.143880, 1.322669, 1.571424, 1.565079]
AES_1_encryption_std = [0.049906, 0.082679, 0.176679, 0.232269, 0.254309, 0.206311, 0.208581, 0.294149, 0.453766, 0.272423]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

# CFB (4)
AES_1_encryption_mean = [0.160142, 0.325024, 0.503486, 0.623913, 0.809393, 0.956049, 1.080025, 1.168030, 1.408647, 1.588531]
AES_1_encryption_std = [0.024163, 0.085664, 0.157844, 0.139837, 0.233504, 0.227921, 0.234650, 0.119039, 0.284384, 0.376602]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

# OFB (5)
AES_1_encryption_mean = [0.157708, 0.307239, 0.493940, 0.754243, 1.085922, 0.980921, 1.252680, 1.197149, 1.300122, 1.447491]
AES_1_encryption_std = [0.033017, 0.057431, 0.128654, 0.235433, 0.403735, 0.268261, 0.391603, 0.154130, 0.046242, 0.038471]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

# CTR (6)
AES_1_encryption_mean = [0.157208, 0.304789, 0.459745, 0.692826, 0.919465, 0.927643, 1.040804, 1.265828, 1.741629, 1.743949]
AES_1_encryption_std = [0.035441, 0.063561, 0.091679, 0.233272, 0.322099, 0.177578, 0.044662, 0.339814, 0.608571, 0.496976]
plt.errorbar(numbers_of_bytes, AES_1_encryption_mean, yerr=AES_1_encryption_std, fmt='-o')

plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()

# AES-2

plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('AES, encryption (length of key: 192 bits)', size=32)
plt.grid()

# ECB (1)
AES_2_encryption_mean = [0.183695, 0.344780, 0.511129, 0.671645, 0.839642, 1.006692, 1.201904, 1.488592, 1.561953, 1.940305]
AES_2_encryption_std = [0.046352, 0.041888, 0.034477, 0.052263, 0.016038, 0.095478, 0.187024, 0.369208, 0.240303, 0.550759]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

# CBC (2)
AES_2_encryption_mean = [0.181643, 0.355681, 0.540215, 0.753954, 0.883208, 1.173884, 1.397860, 1.555448, 1.794041, 2.069535]
AES_2_encryption_std = [0.017517, 0.022061, 0.066299, 0.177735, 0.096951, 0.304965, 0.393025, 0.380613, 0.502461, 0.574155]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

# PCBC (3)
AES_2_encryption_mean = [0.216290, 0.444265, 0.608978, 0.804479, 0.954979, 1.216417, 1.412662, 1.596616, 1.720381, 1.825387]
AES_2_encryption_std = [0.067068, 0.152009, 0.158186, 0.211699, 0.193102, 0.318386, 0.337369, 0.379913, 0.392729, 0.229293]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

# CFB (4)
AES_2_encryption_mean = [0.203422, 0.417953, 0.562482, 0.812692, 0.947783, 1.101154, 1.296053, 1.490773, 1.673232, 1.740001]
AES_2_encryption_std = [0.062095, 0.113487, 0.086105, 0.278833, 0.201313, 0.187828, 0.208790, 0.288010, 0.339325, 0.058295]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

# OFB (5)
AES_2_encryption_mean = [0.192914, 0.358355, 0.554067, 0.947985, 1.066892, 1.216129, 1.410678, 1.585290, 1.565891, 1.734839]
AES_2_encryption_std = [0.054694, 0.031144, 0.100290, 0.330607, 0.369778, 0.353862, 0.438667, 0.385242, 0.125733, 0.051061]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

# CTR (6)
AES_2_encryption_mean = [0.180811, 0.352602, 0.568105, 0.872966, 1.160202, 1.081796, 1.531924, 1.923181, 1.755977, 2.133087]
AES_2_encryption_std = [0.021144, 0.016161, 0.108785, 0.345883, 0.452666, 0.105131, 0.520107, 0.766997, 0.487609, 0.615054]
plt.errorbar(numbers_of_bytes, AES_2_encryption_mean, yerr=AES_2_encryption_std, fmt='-o')

plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()

# AES-3

plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('AES, encryption (length of key: 256 bits)', size=32)
plt.grid()

# ECB (1)
AES_3_encryption_mean = [0.208156, 0.403873, 0.597180, 0.786308, 0.982035, 1.260190, 1.445785, 1.743599, 2.047580, 2.133474]
AES_3_encryption_std = [0.043508, 0.038402, 0.055040, 0.028428, 0.063591, 0.258348, 0.275247, 0.441110, 0.591886, 0.458606]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

# CBC (2)
AES_3_encryption_mean = [0.229867, 0.437310, 0.627769, 0.832465, 1.083424, 1.285148, 1.652439, 1.748046, 1.975317, 2.254758]
AES_3_encryption_std = [0.069915, 0.103374, 0.106749, 0.099643, 0.187794, 0.219488, 0.445159, 0.328139, 0.409852, 0.552616]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

# PCBC (3)
AES_3_encryption_mean = [0.249624, 0.525328, 0.752823, 0.890603, 1.072184, 1.417311, 1.655375, 1.828661, 1.924832, 2.141260]
AES_3_encryption_std = [0.066106, 0.143577, 0.217220, 0.099729, 0.169941, 0.373205, 0.394604, 0.453487, 0.240140, 0.282294]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

# CFB (4)
AES_3_encryption_mean = [0.248640, 0.450487, 0.706202, 0.875953, 1.148375, 1.294218, 1.482775, 1.736299, 1.992893, 2.079825]
AES_3_encryption_std = [0.073765, 0.105756, 0.201055, 0.185310, 0.316585, 0.215425, 0.191120, 0.307989, 0.479237, 0.317262]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

# OFB (5)
AES_3_encryption_mean = [0.221319, 0.426759, 0.778526, 1.007511, 1.199415, 1.496399, 1.650965, 1.630909, 1.813021, 2.011807]
AES_3_encryption_std = [0.049092, 0.073531, 0.275472, 0.363284, 0.380381, 0.484058, 0.537403, 0.133068, 0.069951, 0.025005]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

# CTR (6)
AES_3_encryption_mean = [0.208507, 0.409560, 0.736693, 0.958757, 1.197547, 1.259285, 1.729505, 2.115044, 2.009310, 2.360055]
AES_3_encryption_std = [0.006940, 0.008045, 0.270222, 0.303973, 0.348525, 0.107364, 0.635492, 0.667956, 0.483236, 0.672056]
plt.errorbar(numbers_of_bytes, AES_3_encryption_mean, yerr=AES_3_encryption_std, fmt='-o')

plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()

############################ DECRYPTION ##########################

# AES-1

plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('AES, decryption (length of key: 128 bits)', size=32)
plt.grid()

# ECB (1)
AES_1_decryption_mean = [0.164188, 0.310895, 0.462367, 0.619390, 0.761688, 0.912672, 1.065580, 1.393063, 1.454463, 1.593770]
AES_1_decryption_std = [0.039850, 0.039883, 0.030492, 0.084926, 0.049321, 0.082840, 0.092738, 0.445452, 0.324318, 0.304510]
plt.errorbar(numbers_of_bytes, AES_1_decryption_mean, yerr=AES_1_decryption_std, fmt='-o')

# CBC (2)
AES_1_decryption_mean = [0.165004, 0.341409, 0.482064, 0.671087, 0.803101, 1.103324, 1.235103, 1.341725, 1.544283, 1.749001]
AES_1_decryption_std = [0.015591, 0.057758, 0.021281, 0.123959, 0.099843, 0.328935, 0.300416, 0.312902, 0.337066, 0.457955]
plt.errorbar(numbers_of_bytes, AES_1_decryption_mean, yerr=AES_1_decryption_std, fmt='-o')

# PCBC (3)
AES_1_decryption_mean = [0.213950, 0.378717, 0.613713, 0.797202, 0.948005, 1.021590, 1.234378, 1.444212, 1.688590, 1.688001]
AES_1_decryption_std = [0.055130, 0.094613, 0.189384, 0.258819, 0.273969, 0.218347, 0.247246, 0.351902, 0.479119, 0.287310]
plt.errorbar(numbers_of_bytes, AES_1_decryption_mean, yerr=AES_1_decryption_std, fmt='-o')

# CFB (4)
AES_1_decryption_mean = [0.160147, 0.324555, 0.500878, 0.626845, 0.810382, 0.960837, 1.081796, 1.168355, 1.411315, 1.588489]
AES_1_decryption_std = [0.024990, 0.083810, 0.151842, 0.156838, 0.226301, 0.242414, 0.238575, 0.130257, 0.281048, 0.370166]
plt.errorbar(numbers_of_bytes, AES_1_decryption_mean, yerr=AES_1_decryption_std, fmt='-o')

# OFB (5)
AES_1_decryption_mean = [0.157448, 0.308138, 0.493678, 0.747815, 1.085164, 0.982314, 1.249723, 1.195890, 1.298555, 1.445869]
AES_1_decryption_std = [0.031894, 0.062054, 0.127890, 0.228484, 0.410847, 0.274656, 0.399855, 0.141140, 0.042857, 0.038939]
plt.errorbar(numbers_of_bytes, AES_1_decryption_mean, yerr=AES_1_decryption_std, fmt='-o')

# CTR (6)
AES_1_decryption_mean = [0.157112, 0.304759, 0.459460, 0.697255, 0.927755, 0.931327, 1.040747, 1.262082, 1.738653, 1.776699]
AES_1_decryption_std = [0.034559, 0.062729, 0.092189, 0.239875, 0.330650, 0.174831, 0.041087, 0.334063, 0.579369, 0.573595]
plt.errorbar(numbers_of_bytes, AES_1_decryption_mean, yerr=AES_1_decryption_std, fmt='-o')

plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()

# AES-2

plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('AES, decryption (length of key: 192 bits)', size=32)
plt.grid()

# ECB (1)
AES_2_decryption_mean = [0.199780, 0.376117, 0.555309, 0.734860, 0.913928, 1.100567, 1.309306, 1.633469, 1.697515, 2.125760]
AES_2_decryption_std = [0.049813, 0.044797, 0.039188, 0.058580, 0.012699, 0.108092, 0.177769, 0.429125, 0.234687, 0.601576]
plt.errorbar(numbers_of_bytes, AES_2_decryption_mean, yerr=AES_2_decryption_std, fmt='-o')

# CBC (2)
AES_2_decryption_mean = [0.197638, 0.387209, 0.585503, 0.821451, 0.957486, 1.279625, 1.523466, 1.691251, 1.965516, 2.250566]
AES_2_decryption_std = [0.016528, 0.029205, 0.066418, 0.193655, 0.091846, 0.334851, 0.412682, 0.421197, 0.554222, 0.619896]
plt.errorbar(numbers_of_bytes, AES_2_decryption_mean, yerr=AES_2_decryption_std, fmt='-o')

# PCBC (3)
AES_2_decryption_mean = [0.234754, 0.485935, 0.660644, 0.874006, 1.034074, 1.317809, 1.549403, 1.733145, 1.872888, 1.961585]
AES_2_decryption_std = [0.074445, 0.171648, 0.168204, 0.234015, 0.212813, 0.348155, 0.410456, 0.439569, 0.483591, 0.200337]
plt.errorbar(numbers_of_bytes, AES_2_decryption_mean, yerr=AES_2_decryption_std, fmt='-o')

# CFB (4)
AES_2_decryption_mean = [0.202931, 0.419901, 0.561803, 0.808757, 0.952977, 1.101462, 1.300475, 1.488668, 1.675488, 1.737929]
AES_2_decryption_std = [0.061682, 0.113642, 0.085198, 0.256448, 0.221280, 0.197266, 0.246931, 0.308339, 0.374944, 0.079348]
plt.errorbar(numbers_of_bytes, AES_2_decryption_mean, yerr=AES_2_decryption_std, fmt='-o')

# OFB (5)
AES_2_decryption_mean = [0.193124, 0.357732, 0.554856, 0.951831, 1.070340, 1.210867, 1.411632, 1.582052, 1.564083, 1.733695]
AES_2_decryption_std = [0.054128, 0.031541, 0.103734, 0.339573, 0.353545, 0.345135, 0.438445, 0.402785, 0.122784, 0.071833]
plt.errorbar(numbers_of_bytes, AES_2_decryption_mean, yerr=AES_2_decryption_std, fmt='-o')

# CTR (6)
AES_2_decryption_mean = [0.180656, 0.353081, 0.569052, 0.881089, 1.162985, 1.080735, 1.536517, 1.925604, 1.765025, 2.126813]
AES_2_decryption_std = [0.017793, 0.020397, 0.106523, 0.360680, 0.448888, 0.093308, 0.517769, 0.746690, 0.524801, 0.592437]
plt.errorbar(numbers_of_bytes, AES_2_decryption_mean, yerr=AES_2_decryption_std, fmt='-o')

plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()

# AES-3

plt.xlabel('Количество байт в шифруемом сообщении', size=26)
plt.ylabel('Время исполнения, мс', size=26)
plt.title('AES, decryption (length of key: 256 bits)', size=32)
plt.grid()

# ECB (1)
AES_3_decryption_mean = [0.226613, 0.440278, 0.656083, 0.865528, 1.079003, 1.377982, 1.591917, 1.915107, 2.253312, 2.328227]
AES_3_decryption_std = [0.046292, 0.044831, 0.069786, 0.036352, 0.073590, 0.277481, 0.332637, 0.511863, 0.666304, 0.519150]
plt.errorbar(numbers_of_bytes, AES_3_decryption_mean, yerr=AES_3_decryption_std, fmt='-o')

# CBC (2)
AES_3_decryption_mean = [0.249661, 0.478072, 0.684646, 0.910345, 1.184031, 1.410809, 1.807869, 1.904190, 2.163752, 2.466189]
AES_3_decryption_std = [0.075496, 0.111433, 0.116653, 0.123601, 0.212833, 0.291918, 0.476043, 0.348965, 0.482112, 0.628485]
plt.errorbar(numbers_of_bytes, AES_3_decryption_mean, yerr=AES_3_decryption_std, fmt='-o')

# PCBC (3)
AES_3_decryption_mean = [0.270232, 0.573566, 0.817221, 0.971038, 1.160432, 1.535527, 1.809145, 1.986596, 2.082109, 2.321368]
AES_3_decryption_std = [0.070795, 0.159169, 0.245486, 0.127377, 0.174310, 0.396941, 0.469607, 0.493862, 0.254556, 0.345994]
plt.errorbar(numbers_of_bytes, AES_3_decryption_mean, yerr=AES_3_decryption_std, fmt='-o')

# CFB (4)
AES_3_decryption_mean = [0.248222, 0.448193, 0.709607, 0.874019, 1.149354, 1.295176, 1.486094, 1.736389, 2.000641, 2.072729]
AES_3_decryption_std = [0.073700, 0.102743, 0.207476, 0.178857, 0.321202, 0.239694, 0.217934, 0.311016, 0.467426, 0.294745]
plt.errorbar(numbers_of_bytes, AES_3_decryption_mean, yerr=AES_3_decryption_std, fmt='-o')

# OFB (5)
AES_3_decryption_mean = [0.220787, 0.426332, 0.783416, 1.008215, 1.198302, 1.500931, 1.654647, 1.631049, 1.811622, 2.010406]
AES_3_decryption_std = [0.049390, 0.073288, 0.284194, 0.360795, 0.382316, 0.486519, 0.544544, 0.144184, 0.097829, 0.027485]
plt.errorbar(numbers_of_bytes, AES_3_decryption_mean, yerr=AES_3_decryption_std, fmt='-o')

# CTR (6)
AES_3_decryption_mean = [0.208665, 0.409901, 0.735657, 0.953327, 1.201097, 1.263101, 1.732964, 2.125717, 2.019986, 2.360635]
AES_3_decryption_std = [0.008275, 0.008592, 0.263666, 0.293043, 0.361274, 0.129668, 0.630053, 0.677075, 0.495535, 0.633228]
plt.errorbar(numbers_of_bytes, AES_3_decryption_mean, yerr=AES_3_decryption_std, fmt='-o')

plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()