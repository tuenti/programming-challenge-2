#! /usr/bin/env python
import base64

# This is not funny...

encoded = raw_input()
decoded = base64.b64decode(encoded)

tmp = ''
last = 0

for i in range(0, len(decoded), 8):
  numhex = decoded[i : i + 8]
  num = int(decoded[i : i + 8], 16)
  
  dif = num - last
  if -16 <= dif and dif < 16:
    t = dif
    if dif < 0: t = 32 + dif
    t = bin(t)[2:]
    while len(t) < 5: t = '0' + t
    tmp += '0' + t
  else:
    t = bin(num)[2:]
    while len(t) < 32: t = '0' + t
    tmp += '1' + t
  
  last = num

while len(tmp)%4 != 0: tmp += '0'

res = ''
for i in range(0, len(tmp), 4):
  res += hex(int(tmp[i : i + 4], 2))[2:]

res = base64.b64encode(res)
while res[-1] == '=': res = res[:-1]

print res
