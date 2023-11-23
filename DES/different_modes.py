import matplotlib.pyplot as plt
import numpy as np

NumOfBlocks = [pow(10, i + 1) for i in range(3)]

# ECB (1)

ECB_encryption = np.array([0.057399, 0.552944, 5.352524])
ECB_decryption = np.array([0.057365, 0.551652, 5.328100])

ECB_encryption_std = np.array([0.005487, 0.112644, 0.735063])
ECB_decryption_std = np.array([0.005396, 0.113515, 0.709034])

# CBC (2)

CBC_encryption = np.array([0.058923, 0.538595, 5.194137])
CBC_decryption = np.array([0.059031, 0.539035, 5.219954])

CBC_encryption_std = np.array([0.009153, 0.088239, 0.380838])
CBC_decryption_std = np.array([0.010136, 0.083961, 0.350033])

# PCBC (3)

PCBC_encryption = np.array([0.059292, 0.532469, 5.484848])
PCBC_decryption = np.array([0.058972, 0.530236, 5.474984])

PCBC_encryption_std = np.array([0.010031, 0.054795, 0.844884])
PCBC_decryption_std = np.array([0.009853, 0.057040, 0.845736])

# CFB (4)

CFB_encryption = np.array([0.057238, 0.544991, 5.416663])
CFB_decryption = np.array([0.057234, 0.544128, 5.410549])

CFB_encryption_std = np.array([0.010095, 0.101883, 0.810590])
CFB_decryption_std = np.array([0.009900, 0.100705, 0.791703])

# OFB (5)

OFB_encryption = np.array([0.058239, 0.524647, 5.352304])
OFB_decryption = np.array([0.058405, 0.526437, 5.348848])

OFB_encryption_std = np.array([0.009481, 0.032734, 0.763953])
OFB_decryption_std = np.array([0.009505, 0.033434, 0.708635])

# CTR (6)

CTR_encryption = np.array([0.057531, 0.544885, 5.466048])
CTR_decryption = np.array([0.057411, 0.544955, 5.458344])

CTR_encryption_std = np.array([0.007034, 0.104830, 0.882041])
CTR_decryption_std = np.array([0.007046, 0.103829, 0.867002])

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