from pwn import *

p = process("./chal")

p.sendline(b"7")

p.recvuntil(b"Start!\n")

# start_time = time.time()
#
# target_delay = 10.0
# while True:
#     now = time.time()
#     if now - start_time >= target_delay:
#         break

p.sendline(b' ')

result = p.recvall(timeout=1).decode(errors="ignore")
print(result)

