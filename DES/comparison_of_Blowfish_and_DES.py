import matplotlib.pyplot as plt
import numpy as np

NumOfBlocks_for_DES = [pow(10, i + 1) for i in range(3)]

# ECB (1)

ECB_encryption_DES = np.array([0.057399, 0.552944, 5.352524])
ECB_decryption_DES = np.array([0.057365, 0.551652, 5.328100])

ECB_encryption_std_DES = np.array([0.005487, 0.112644, 0.735063])
ECB_decryption_std_DES = np.array([0.005396, 0.113515, 0.709034])

# CBC (2)

CBC_encryption_DES = np.array([0.058923, 0.538595, 5.194137])
CBC_decryption_DES = np.array([0.059031, 0.539035, 5.219954])

CBC_encryption_std_DES = np.array([0.009153, 0.088239, 0.380838])
CBC_decryption_std_DES = np.array([0.010136, 0.083961, 0.350033])

# PCBC (3)

PCBC_encryption_DES = np.array([0.059292, 0.532469, 5.484848])
PCBC_decryption_DES = np.array([0.058972, 0.530236, 5.474984])

PCBC_encryption_std_DES = np.array([0.010031, 0.054795, 0.844884])
PCBC_decryption_std_DES = np.array([0.009853, 0.057040, 0.845736])

# CFB (4)

CFB_encryption_DES = np.array([0.057238, 0.544991, 5.416663])
CFB_decryption_DES = np.array([0.057234, 0.544128, 5.410549])

CFB_encryption_std_DES = np.array([0.010095, 0.101883, 0.810590])
CFB_decryption_std_DES = np.array([0.009900, 0.100705, 0.791703])

# OFB (5)

OFB_encryption_DES = np.array([0.058239, 0.524647, 5.352304])
OFB_decryption_DES = np.array([0.058405, 0.526437, 5.348848])

OFB_encryption_std_DES = np.array([0.009481, 0.032734, 0.763953])
OFB_decryption_std_DES = np.array([0.009505, 0.033434, 0.708635])

# CTR (6)

CTR_encryption_DES = np.array([0.057531, 0.544885, 5.466048])
CTR_decryption_DES = np.array([0.057411, 0.544955, 5.458344])

CTR_encryption_std_DES = np.array([0.007034, 0.104830, 0.882041])
CTR_decryption_std_DES = np.array([0.007046, 0.103829, 0.867002])


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