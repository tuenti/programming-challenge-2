#! /usr/bin/env python
import Image

img = Image.open('newspaper.png')
(sx, sy) = img.size

tmp = img.convert('RGB')
for x in range(sx):
  for y in range(sy):
    (r, g, b, a) = img.getpixel((x, y))
    t = tmp.getpixel((x, y))
    if t != (255, 0, 0):
      tmp.putpixel((x, y), (r, g, b))
      if a == 0:
        for i in range(-2, 2 + 1):
          for j in range(0, 2):
            tmp.putpixel((x + i, y + j), (255, 0, 0))
tmp.save('out.png')
