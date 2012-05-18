#! /usr/bin/env python

v = []
while True:
  try: line = raw_input()
  except: break
  v.extend(line.split())

st = []
for x in v:
  if x == '.':
    print st[0]
    st = []
  elif x == '#':
    st[-2] *= st[-1]
    st.pop()
  elif x == '@':
    st[-2] += st[-1]
    st.pop()
  elif x == '$':
    st[-2] -= st[-1]
    st.pop()
  elif x == '&':
    st[-2] = st[-2]/st[-1]
    st.pop()
  elif x == 'conquer':
    st[-2] = st[-2]%st[-1]
    st.pop()
  elif x == 'dance':
    a = st[-2]
    b = st[-1]
    st[-2] = b
    st[-1] = a
  elif x == 'mirror': st[-1] = -st[-1]
  elif x == 'breadandfish': st.append(st[-1])
  elif x == 'fire': st.pop()
  else: st.append(int(x))
