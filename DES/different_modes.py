import matplotlib.pyplot as plt
import numpy as np

NumOfBlocks = [pow(10, i + 1) for i in range(3)]

# ECB (1)

ECB_encryption = np.array([0.081832, 0.755412, 7.509637])
ECB_decryption = np.array([0.081749, 0.754958, 7.500610])

ECB_encryption_std = np.array([0.012183, 0.026151, 0.254769])
ECB_decryption_std = np.array([0.011849, 0.025180, 0.177836])

# CBC (2)

CBC_encryption = np.array([0.089082, 0.857085, 8.479485])
CBC_decryption = np.array([0.089053, 0.860029, 8.515597])

CBC_encryption_std = np.array([0.026347, 0.239483, 1.608684])
CBC_decryption_std = np.array([0.025638, 0.241172, 1.607775])

# PCBC (3)

PCBC_encryption = np.array([0.093276, 0.877241, 8.654829])
PCBC_decryption = np.array([0.093167, 0.877875, 8.658609])

PCBC_encryption_std = np.array([0.031211, 0.256998, 1.672714])
PCBC_decryption_std = np.array([0.030999, 0.253920, 1.637694])

# CFB (4)

CFB_encryption = np.array([0.088713, 0.880506, 8.453465])
CFB_decryption = np.array([0.088544, 0.879843, 8.508793])

CFB_encryption_std = np.array([0.025634, 0.278133, 1.566999])
CFB_decryption_std = np.array([0.025157, 0.263218, 1.660604])

# OFB (5)

OFB_encryption = np.array([0.087837, 0.878865, 8.638903])
OFB_decryption = np.array([0.087913, 0.879435, 8.627442])

OFB_encryption_std = np.array([0.025665, 0.242433, 1.668572])
OFB_decryption_std = np.array([0.027389, 0.245298, 1.616948])

# CTR (6)

CTR_encryption = np.array([0.088141, 0.859550, 8.672700])
CTR_decryption = np.array([0.088028, 0.858267, 8.689559])

CTR_encryption_std = np.array([0.024825, 0.205662, 1.684348])
CTR_decryption_std = np.array([0.023391, 0.205526, 1.708839])

plt.title("Encryption, 10000 экспериментов", size=32)
plt.xlabel('Длина сообщения (в 64-битных блоках)', size=28)
plt.ylabel('Время исполнения, мс', size=28)
plt.grid()
plt.xticks(fontsize=24)
plt.yticks(fontsize=24)
plt.errorbar(NumOfBlocks, ECB_encryption, yerr=ECB_encryption_std, fmt='-o')
plt.errorbar(NumOfBlocks, CBC_encryption, yerr=CBC_encryption_std, fmt='-o')
plt.errorbar(NumOfBlocks, PCBC_encryption, yerr=PCBC_encryption_std, fmt='-o')
plt.errorbar(NumOfBlocks, CFB_encryption, yerr=CFB_encryption_std, fmt='-o')
plt.errorbar(NumOfBlocks, OFB_encryption, yerr=OFB_encryption_std, fmt='-o')
plt.errorbar(NumOfBlocks, CTR_encryption, yerr=CTR_encryption_std, fmt='-o')
plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()

plt.title("Decryption, 10000 экспериментов", size=32)
plt.xlabel('Длина сообщения (в 64-битных блоках)', size=28)
plt.ylabel('Время исполнения, мс', size=28)
plt.grid()
plt.xticks(fontsize=24)
plt.yticks(fontsize=24)
plt.errorbar(NumOfBlocks, ECB_decryption, yerr=ECB_decryption_std, fmt='-o')
plt.errorbar(NumOfBlocks, CBC_decryption, yerr=CBC_decryption_std, fmt='-o')
plt.errorbar(NumOfBlocks, PCBC_decryption, yerr=PCBC_decryption_std, fmt='-o')
plt.errorbar(NumOfBlocks, CFB_decryption, yerr=CFB_decryption_std, fmt='-o')
plt.errorbar(NumOfBlocks, OFB_decryption, yerr=OFB_decryption_std, fmt='-o')
plt.errorbar(NumOfBlocks, CTR_decryption, yerr=CTR_decryption_std, fmt='-o')
plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()