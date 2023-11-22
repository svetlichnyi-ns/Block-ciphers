import matplotlib.pyplot as plt
import numpy as np

NumOfBlocks = [pow(10, i + 1) for i in range(4)]

# ECB (1)

ECB_encryption = np.array([3149, 29259, 284994, 2825129])
ECB_decryption = np.array([3155, 29251, 285094, 2826365])

ECB_encryption_std = np.array([741.043396, 5381.394591, 34678.521179, 201185.699538])
ECB_decryption_std = np.array([606.156533, 5248.056956, 34295.847459, 212824.938906])

# CBC (2)

CBC_encryption = np.array([3445, 30395, 300701, 3146559])
CBC_decryption = np.array([3612, 32249, 318027, 3323868])

CBC_encryption_std = np.array([1160.497167, 2496.555082, 19601.743301, 529552.170799])
CBC_decryption_std = np.array([1076.421046, 2602.139103, 20002.423156, 584064.553219])

# PCBC (3)

PCBC_encryption = np.array([4090, 38121, 378060, 3921491])
PCBC_decryption = np.array([4047, 37775, 374540, 3900327])

PCBC_encryption_std = np.array([860.011606, 3771.446510, 15429.125373, 621878.526099])
PCBC_decryption_std = np.array([854.393820, 3640.638052, 15863.275209, 639465.194035])

# CFB (4)

CFB_encryption = np.array([3436, 31085, 318490, 3230837])
CFB_decryption = np.array([3443, 31131, 317373, 3233397])

CFB_encryption_std = np.array([1024.034797, 3579.372178, 25954.280388, 525517.305590])
CFB_decryption_std = np.array([1057.690158, 3851.280960, 26251.200174, 521943.541622])

# OFB (5)

OFB_encryption = np.array([3479, 33031, 327029, 3340908])
OFB_decryption = np.array([3503, 32992, 327868, 3330866])

OFB_encryption_std = np.array([706.992492, 5168.448576, 16120.915017, 492470.995634])
OFB_decryption_std = np.array([878.331228, 5113.292499, 15491.519445, 492365.674975])

# CTR (6)

CTR_encryption = np.array([3422, 31228, 314153, 3215615])
CTR_decryption = np.array([3412, 31217, 314223, 3216782])

CTR_encryption_std = np.array([1180.675993, 4181.654771, 48651.173771, 543671.879264])
CTR_decryption_std = np.array([1090.349892, 4232.849620, 49273.812116, 545006.956070])

plt.title("Encryption, 10000 экспериментов", size=32)
plt.xlabel('Длина сообщения (в 64-битных блоках)', size=28)
plt.ylabel('Время исполнения, мс', size=28)
plt.grid()
plt.xticks(fontsize=24)
plt.yticks(fontsize=24)
plt.errorbar(NumOfBlocks, ECB_encryption / 1e6, yerr=ECB_encryption_std / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks, CBC_encryption / 1e6, yerr=CBC_encryption_std / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks, PCBC_encryption / 1e6, yerr=PCBC_encryption_std / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks, CFB_encryption / 1e6, yerr=CFB_encryption_std / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks, OFB_encryption / 1e6, yerr=OFB_encryption_std / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks, CTR_encryption / 1e6, yerr=CTR_encryption_std / 1e6, fmt='-o')
plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()

plt.title("Decryption, 10000 экспериментов", size=32)
plt.xlabel('Длина сообщения (в 64-битных блоках)', size=28)
plt.ylabel('Время исполнения, мс', size=28)
plt.grid()
plt.xticks(fontsize=24)
plt.yticks(fontsize=24)
plt.errorbar(NumOfBlocks, ECB_decryption / 1e6, yerr=ECB_decryption_std / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks, CBC_decryption / 1e6, yerr=CBC_decryption_std / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks, PCBC_decryption / 1e6, yerr=PCBC_decryption_std / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks, CFB_decryption / 1e6, yerr=CFB_decryption_std / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks, OFB_decryption / 1e6, yerr=OFB_decryption_std / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks, CTR_decryption / 1e6, yerr=CTR_decryption_std / 1e6, fmt='-o')
plt.legend(['ECB', 'CBC', 'PCBC', 'CFB', 'OFB', 'CTR'], prop={'size': 26})
plt.show()