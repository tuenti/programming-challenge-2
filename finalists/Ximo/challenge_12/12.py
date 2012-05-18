#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function
input = raw_input

code_qr  = 'ed8ce15da9b7b5e2ee70634cc235e363'
#code_in  = '1ee7453658914cd7463B77032fdbb623'
code_com = 'a541714a17804ac281e6ddda5b707952'
code_bin = '36326364323735393839653738656535'
code_lsb = '62cd275989e78ee56a81f0265a87562e'

if __name__ == '__main__':
    code_in = input().strip()
    for i in range(32):
        res = 0
        for code in [code_qr, code_in, code_com, code_lsb]:
            res += eval('0x' + code[i])
        print(hex(res%16)[2], end='')
    print()
