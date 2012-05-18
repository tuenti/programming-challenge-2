#! /usr/bin/env python

r1 = 0
r2 = 0
res = 0

p = 0

while True:
  try: line = raw_input()
  except: break
  
  t = int(line)
  if p == 0 or t < mini:
    mini = t
    minipos = p
  
  if t - mini > res:
    res = t - mini
    r1 = minipos
    r2 = p
  
  p += 1

print 100*r1, 100*r2, res
