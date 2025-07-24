enc_hex = "13247520662627234c506e614c202658554c66234c2476467072664461645e4750724c77242761674c5d234a6168"
enc_vals = [int(enc_hex[i:i+2], 16) for i in range(0, len(enc_hex), 2)]

# linked list inserted reversely, so we need to do it reversely also
enc_vals = enc_vals[::-1]

key = 0x13
order = [7,  42, 12, 27, 0,  29, 36, 25, 16, 23, 30, 15,
         33, 1,  5,  20, 10, 17, 8,  41, 31, 39, 3,  24,
         32, 11, 9,  38, 26, 6,  2,  35, 43, 19, 37, 44,
         4,  34, 13, 21, 22, 14, 18, 28, 40]

flag = [''] * len(order)

# Decrypt
for i in range(len(order)):
    decrypted_char = chr(enc_vals[i] ^ key)
    flag[order[i]] = decrypted_char

print("".join(flag))

