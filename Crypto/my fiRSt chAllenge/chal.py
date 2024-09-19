from secret import FLAG
from Crypto.Util.number import getPrime, bytes_to_long

n = getPrime(2048)
e = getPrime(16)
c = pow(bytes_to_long(FLAG), e, n)

with open("output.txt", "w") as f:
    f.write(f"n = {n}\ne = {e}\nc = {c}")
