from pwn import *

# p = process("./chal")
p = remote("chall.nckuctf.org", 28147)

p.sendline(b"7")

p.recvuntil(b"Start!\n")

p.sendline(b' ')

result = p.recvall(timeout=1).decode(errors="ignore")
print(result)

