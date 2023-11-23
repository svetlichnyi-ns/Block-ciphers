import matplotlib.pyplot as plt
import numpy as np

NumOfBlocks_for_DES = [pow(10, i + 1) for i in range(3)]

# ECB (1)

ECB_encryption_DES = np.array([0.081832, 0.755412, 7.509637])
ECB_decryption_DES= np.array([0.081749, 0.754958, 7.500610])

ECB_encryption_std_DES = np.array([0.012183, 0.026151, 0.254769])
ECB_decryption_std_DES = np.array([0.011849, 0.025180, 0.177836])

# CBC (2)

CBC_encryption_DES = np.array([0.089082, 0.857085, 8.479485])
CBC_decryption_DES = np.array([0.089053, 0.860029, 8.515597])

CBC_encryption_std_DES = np.array([0.026347, 0.239483, 1.608684])
CBC_decryption_std_DES = np.array([0.025638, 0.241172, 1.607775])

# PCBC (3)

PCBC_encryption_DES = np.array([0.093276, 0.877241, 8.654829])
PCBC_decryption_DES = np.array([0.093167, 0.877875, 8.658609])

PCBC_encryption_std_DES = np.array([0.031211, 0.256998, 1.672714])
PCBC_decryption_std_DES = np.array([0.030999, 0.253920, 1.637694])

# CFB (4)

CFB_encryption_DES = np.array([0.088713, 0.880506, 8.453465])
CFB_decryption_DES = np.array([0.088544, 0.879843, 8.508793])

CFB_encryption_std_DES = np.array([0.025634, 0.278133, 1.566999])
CFB_decryption_std_DES = np.array([0.025157, 0.263218, 1.660604])

# OFB (5)

OFB_encryption_DES = np.array([0.087837, 0.878865, 8.638903])
OFB_decryption_DES = np.array([0.087913, 0.879435, 8.627442])

OFB_encryption_std_DES = np.array([0.025665, 0.242433, 1.668572])
OFB_decryption_std_DES = np.array([0.027389, 0.245298, 1.616948])

# CTR (6)

CTR_encryption_DES = np.array([0.088141, 0.859550, 8.672700])
CTR_decryption_DES = np.array([0.088028, 0.858267, 8.689559])

CTR_encryption_std_DES = np.array([0.024825, 0.205662, 1.684348])
CTR_decryption_std_DES = np.array([0.023391, 0.205526, 1.708839])



NumOfBlocks_for_Blowfish = [pow(10, i + 1) for i in range(4)]

# ECB (1)

ECB_encryption_Blowfish = np.array([3149, 29259, 284994, 2825129])
ECB_decryption_Blowfish = np.array([3155, 29251, 285094, 2826365])

ECB_encryption_std_Blowfish = np.array([741.043396, 5381.394591, 34678.521179, 201185.699538])
ECB_decryption_std_Blowfish = np.array([606.156533, 5248.056956, 34295.847459, 212824.938906])

# CBC (2)

CBC_encryption_Blowfish = np.array([3445, 30395, 300701, 3146559])
CBC_decryption_Blowfish = np.array([3612, 32249, 318027, 3323868])

CBC_encryption_std_Blowfish = np.array([1160.497167, 2496.555082, 19601.743301, 529552.170799])
CBC_decryption_std_Blowfish = np.array([1076.421046, 2602.139103, 20002.423156, 584064.553219])

# PCBC (3)

PCBC_encryption_Blowfish = np.array([4090, 38121, 378060, 3921491])
PCBC_decryption_Blowfish = np.array([4047, 37775, 374540, 3900327])

PCBC_encryption_std_Blowfish = np.array([860.011606, 3771.446510, 15429.125373, 621878.526099])
PCBC_decryption_std_Blowfish = np.array([854.393820, 3640.638052, 15863.275209, 639465.194035])

# CFB (4)

CFB_encryption_Blowfish = np.array([3436, 31085, 318490, 3230837])
CFB_decryption_Blowfish = np.array([3443, 31131, 317373, 3233397])

CFB_encryption_std_Blowfish = np.array([1024.034797, 3579.372178, 25954.280388, 525517.305590])
CFB_decryption_std_Blowfish = np.array([1057.690158, 3851.280960, 26251.200174, 521943.541622])

# OFB (5)

OFB_encryption_Blowfish = np.array([3479, 33031, 327029, 3340908])
OFB_decryption_Blowfish = np.array([3503, 32992, 327868, 3330866])

OFB_encryption_std_Blowfish = np.array([706.992492, 5168.448576, 16120.915017, 492470.995634])
OFB_decryption_std_Blowfish = np.array([878.331228, 5113.292499, 15491.519445, 492365.674975])

# CTR (6)

CTR_encryption_Blowfish = np.array([3422, 31228, 314153, 3215615])
CTR_decryption_Blowfish = np.array([3412, 31217, 314223, 3216782])

CTR_encryption_std_Blowfish = np.array([1180.675993, 4181.654771, 48651.173771, 543671.879264])
CTR_decryption_std_Blowfish = np.array([1090.349892, 4232.849620, 49273.812116, 545006.956070])

plt.title("Encryption, 10000 экспериментов", size=32)
plt.xlabel('Длина сообщения (в 64-битных блоках)', size=28)
plt.ylabel('Время исполнения, мс', size=28)
plt.grid()
plt.xticks(fontsize=24)
plt.yticks(fontsize=24)

plt.errorbar(NumOfBlocks_for_DES, ECB_encryption_DES, yerr=ECB_encryption_std_DES, fmt='-o')
plt.errorbar(NumOfBlocks_for_DES, CBC_encryption_DES, yerr=CBC_encryption_std_DES, fmt='-o')
plt.errorbar(NumOfBlocks_for_DES, PCBC_encryption_DES, yerr=PCBC_encryption_std_DES, fmt='-o')
plt.errorbar(NumOfBlocks_for_DES, CFB_encryption_DES, yerr=CFB_encryption_std_DES, fmt='-o')
plt.errorbar(NumOfBlocks_for_DES, OFB_encryption_DES, yerr=OFB_encryption_std_DES, fmt='-o')
plt.errorbar(NumOfBlocks_for_DES, CTR_encryption_DES, yerr=CTR_encryption_std_DES, fmt='-o')

plt.errorbar(NumOfBlocks_for_Blowfish, ECB_encryption_Blowfish / 1e6, yerr=ECB_encryption_std_Blowfish / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks_for_Blowfish, CBC_encryption_Blowfish / 1e6, yerr=CBC_encryption_std_Blowfish / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks_for_Blowfish, PCBC_encryption_Blowfish / 1e6, yerr=PCBC_encryption_std_Blowfish / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks_for_Blowfish, CFB_encryption_Blowfish / 1e6, yerr=CFB_encryption_std_Blowfish / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks_for_Blowfish, OFB_encryption_Blowfish / 1e6, yerr=OFB_encryption_std_Blowfish / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks_for_Blowfish, CTR_encryption_Blowfish / 1e6, yerr=CTR_encryption_std_Blowfish / 1e6, fmt='-o')

plt.legend(['ECB_DES', 'CBC_DES', 'PCBC_DES', 'CFB_DES', 'OFB_DES', 'CTR_DES',
            'ECB_Blowfish', 'CBC_Blowfish', 'PCBC_Blowfish', 'CFB_Blowfish', 'OFB_Blowfish', 'CTR_Blowfish'], prop={'size': 18})
plt.show()

plt.title("Decryption, 10000 экспериментов", size=32)
plt.xlabel('Длина сообщения (в 64-битных блоках)', size=28)
plt.ylabel('Время исполнения, мс', size=28)
plt.grid()
plt.xticks(fontsize=24)
plt.yticks(fontsize=24)

plt.errorbar(NumOfBlocks_for_DES, ECB_decryption_DES, yerr=ECB_decryption_std_DES, fmt='-o')
plt.errorbar(NumOfBlocks_for_DES, CBC_decryption_DES, yerr=CBC_decryption_std_DES, fmt='-o')
plt.errorbar(NumOfBlocks_for_DES, PCBC_decryption_DES, yerr=PCBC_decryption_std_DES, fmt='-o')
plt.errorbar(NumOfBlocks_for_DES, CFB_decryption_DES, yerr=CFB_decryption_std_DES, fmt='-o')
plt.errorbar(NumOfBlocks_for_DES, OFB_decryption_DES, yerr=OFB_decryption_std_DES, fmt='-o')
plt.errorbar(NumOfBlocks_for_DES, CTR_decryption_DES, yerr=CTR_decryption_std_DES, fmt='-o')

plt.errorbar(NumOfBlocks_for_Blowfish, ECB_decryption_Blowfish / 1e6, yerr=ECB_decryption_std_Blowfish / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks_for_Blowfish, CBC_decryption_Blowfish / 1e6, yerr=CBC_decryption_std_Blowfish / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks_for_Blowfish, PCBC_decryption_Blowfish / 1e6, yerr=PCBC_decryption_std_Blowfish / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks_for_Blowfish, CFB_decryption_Blowfish / 1e6, yerr=CFB_decryption_std_Blowfish / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks_for_Blowfish, OFB_decryption_Blowfish / 1e6, yerr=OFB_decryption_std_Blowfish / 1e6, fmt='-o')
plt.errorbar(NumOfBlocks_for_Blowfish, CTR_decryption_Blowfish / 1e6, yerr=CTR_decryption_std_Blowfish / 1e6, fmt='-o')

plt.legend(['ECB_DES', 'CBC_DES', 'PCBC_DES', 'CFB_DES', 'OFB_DES', 'CTR_DES',
            'ECB_Blowfish', 'CBC_Blowfish', 'PCBC_Blowfish', 'CFB_Blowfish', 'OFB_Blowfish', 'CTR_Blowfish'], prop={'size': 18})
plt.show()