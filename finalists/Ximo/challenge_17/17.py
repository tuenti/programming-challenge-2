#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, division
input = raw_input
import math

N_TRIES = 20000

def create_polygon(cx, cy, vx, vy, edges):
    ''' calculates the points of a regular polygon given the center, one edge
    and the number of edges. '''

    vertices = [ ]
    d = math.sqrt((cx-vx)**2 + (cy-vy)**2)
    cos = (vx-cx)/d
    ang = math.acos(cos)
    ang_dif = 2.*math.pi/edges
    angles = [(i*ang_dif+ang)%(2.*math.pi) for i in range(edges)]
    for a in angles:
        x = cx + math.cos(a)*d
        y = cy + math.sin(a)*d
        vertices.append( (x, y) )
    return vertices

def dist(x, y, a, b=0):
    ''' distance from point x,y to the rect y = a*x + b '''
    return (a*x - y + b)/math.sqrt(a*a + 1)

def sign(x):
    if x <= 0: return '+'
    else: return '-'

if __name__ == '__main__':
    C = int(input())
    for c in range(C):
        # input
        Cx, Cy, R = map(float, input().split())
        N = int(input())
        ingredients = []
        for n in range(N):
            ident, edges, count = input().split()
            edges = int(edges)
            count = int(count)
            for _ in range(count):
                ix, iy, vx, vy = map(float, input().split())
                ix, iy = ix-Cx, iy-Cy
                vx, vy = vx-Cx, vy-Cy
                #print(ix, iy, '-', vx, vy)
                ingredients.append( [ ident, (ix, iy), create_polygon(ix, iy, vx, vy, edges) ] )

        for i in range(N_TRIES):
            # check if the rect y = tan(ang)*x is a valid cut
            ang = math.tan((math.pi/N_TRIES)*i)
            valid = True
            content = {'+':[], '-':[]}
            for ing in ingredients:
                distances = [dist(x,y,ang) for x,y in ing[2]]
                signs = [sign(dist(x,y,ang)) for x,y in ing[2]]
                if '+' in signs and '-' in signs: # ingredient cut!
                    valid = False
                    break
                content[signs[0]].append(ing[0])
            if valid: # no ingredient has been cut
                # checks the distance to the center to see if the ingredients are
                # equally distributed
                pos = sorted(content['+'])
                neg = sorted(content['-'])
                if pos == neg:
                    print('Case #{}: TRUE'.format(c+1))
                    break
        else:
            print('Case #{}: FALSE'.format(c+1))
