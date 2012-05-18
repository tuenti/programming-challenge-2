#!/usr/bin/env python
# -*- coding: utf-8 -*-

# *** Challenge 17: The Solomonic pizza cut ***
#
# I'm sorry, Fry, but anchovies went extinct in the 2200s.

from math import *

def cross_product(a, b):
    return a[0] * b[1] - a[1] * b[0]

def check_point_in_polygon(point, vertices):
    ''' Check if a point is inside a convex polygon
    
    point - Point to check (x,y)
    vertices - List of vertices of the polygon
    
    Check that the point lies always in the same side of all the edges
    '''
    sign = 0
    num_vertices = len(vertices)

    for i in range(num_vertices):
        segment = (vertices[i], vertices[(i + 1) % num_vertices])

        affine_segment = (segment[1][0] - segment[0][0], segment[1][1] - segment[0][1])
        affine_point = (point[0] - segment[0][0], point[1] - segment[0][1])

        k = cross_product(affine_segment, affine_point)
        if k == 0:  # Point in the center, considering that this is not possible
            return True

        k = int(k / abs(k))  # normalized to 1 or -1
        
        if sign == 0:
            sign = k
        elif k != sign:
            return False

    return True      


def get_min_and_max_vertices(vertices, center):
    ''' Return only two vertices for each polygon
    
    vertices - List of vertices of the polygon
    center - Center of the pizza
    
    Our polygons will be convex and never will be on the center. So for cut testing
    we don't need to test with all the vertex, we only need two.
    
    This function finds these two vertex in a polygon. It looks for the vertex that
    tracing a line to the center, let all other vertex in the same side of the line.
    There are two vertex that satifies this condition in each polygon.
    '''
    result = []
    
    first_index = 0  # Index of the first found vertex, to avoid looking for it the the second loop
    
    for i in range(len(vertices)):
        # Segment from vertex to the center
        affine_segment = (vertices[i][0] - center[0], vertices[i][1] - center[1])
        valid_vertex = True        
        for j in range(len(vertices)):
            if i == j:
                continue            
            affine_point = (vertices[j][0] - center[0], vertices[j][1] - center[1])
            k = cross_product(affine_segment, affine_point)
            
            if k < 0:
                valid_vertex = False
                break

        if valid_vertex:
            result.append(vertices[i])
            first_index = i
            break
            

    for i in range(len(vertices)):
        if i == first_index:
            continue
        
        affine_segment = (vertices[i][0] - center[0], vertices[i][1] - center[1])
        valid_vertex = True
        
        for j in range(len(vertices)):
            if i == j or j == first_index:
                continue                       
            
            affine_point = (vertices[j][0] - center[0], vertices[j][1] - center[1])
            k = cross_product(affine_segment, affine_point)
            
            if k > 0:
                valid_vertex = False
                break

        if valid_vertex:
            result.append(vertices[i])
            break
        
        
    return result
    


def get_polygon_vertices(num_vertices, C, V):
    ''' Returns the vertices of a polygon
    
    num_vertices - Number of vertices of the polygon
    C - Center of the polygon
    V - One vertex of the polygon as (x,y)
    
    Returns a list of (x,y) tuples with all the vertices of the polygon
    '''
    r = sqrt(((C[0] - V[0]) ** 2.0) + ((C[1] - V[1]) ** 2.0))

    angle = atan2(V[1] - C[1], V[0] - C[0])

    if (angle < 0):
        angle += 2*pi

    inc_angle = (2*pi) / num_vertices

    vertices = [V]
    for i in range(num_vertices - 1):
        angle += inc_angle
        vertex = (C[0] + r * cos(angle), C[1] + r * sin(angle))
        vertices.append(vertex)

    return vertices



import sys

if __name__ == '__main__':
    total_cases = int(sys.stdin.readline())

    for ncase in range(total_cases):
        can_be_cut = True
        data = map(float, sys.stdin.readline().split())

        pizza = tuple(data[0:2])
        R = data[2]

        num_ingredients = int(sys.stdin.readline())
        ingredients = []
    
        for i in range(num_ingredients):
            data = sys.stdin.readline().split()

            name = data[0]
            edges = int(data[1])
            Ni = int(data[2])

            if Ni % 2 != 0:
                # Odd number of this ingredient, can't be cut
                can_be_cut = False

            for j in range(Ni):
                data = map(float, sys.stdin.readline().split())

                if can_be_cut:
                    C = tuple(data[0:2])
                    V = tuple(data[2:4])

                    vertices = get_polygon_vertices(edges, C, V)
                    if check_point_in_polygon(pizza, vertices):
                        # There is pepperoni on the center !!!
                        can_be_cut = False
                        continue

                    vertices = get_min_and_max_vertices(vertices, pizza)
                    ingredients.append([name, vertices])
                

        if not can_be_cut:
            print "Case #%d: FALSE" % (ncase + 1)
            continue

        valid_cut = False
        # Try to cut using a line from the center of the pizza to the vertices of the ingredients
        for i in range(len(ingredients)):
            for j, vertex in enumerate(ingredients[i][1]):
                affine_segment = (vertex[0] - pizza[0], vertex[1] - pizza[1])
                ingredients_in_sides = [[], []]
                can_be_cut = True
                # Check if we are cutting any ingredient
                for name, vertices in ingredients:
                    side = 0   # It can be -1 or 1, to one side of the cut or to the other
                    for vertex2 in vertices:
                        affine_point = (vertex2[0] - pizza[0], vertex2[1] - pizza[1])
                        k = cross_product(affine_segment, affine_point)
                        if (k == 0): # The point lies exactly in the cut, this is allowed
                            continue

                        k = int(k/abs(k)) # Convert to 1 or -1
                        if side == 0:
                            side = k
                        elif k != side:
                            can_be_cut = False
                            break
                    
                    if not can_be_cut:  # This segment cut ingredients, try another one
                        break

                    if side == -1:
                        ingredients_in_sides[0].append(name)
                    else:
                        ingredients_in_sides[1].append(name)
                
                if not can_be_cut:
                    continue

                # Are there the same ingredients and quantities in each piece?
                ingredients_in_sides[0].sort()
                ingredients_in_sides[1].sort()

                if ingredients_in_sides[0] == ingredients_in_sides[1]:
                    valid_cut = True
                    break
                
            if valid_cut:
                break
            
        if valid_cut:
            print "Case #%d: TRUE" % (ncase + 1)
        else:
            print "Case #%d: FALSE" % (ncase + 1)


