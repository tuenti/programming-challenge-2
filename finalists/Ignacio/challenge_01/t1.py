#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

press_button_time = 100
wait_button_time = 500

# This matrix marks the enabled buttons, for which we will calculate their shortests paths
active_keys = [ [1, 1, 1],
                [1, 1, 1],
                [1, 1, 1],
                [0, 1, 1] ]

letters = {    ' 1': (0, 0), 'ABC2': (0, 1),  'DEF3': (0, 2),
             'GHI4': (1, 0), 'JKL5': (1, 1),  'MNO6': (1, 2),
            'PQRS7': (2, 0), 'TUV8': (2, 1), 'WXYZ9': (2, 2),
                                '0': (3, 1) }

letters_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
letters_lowercase = "abcdefghijklmnopqrstuvwxyz"

# Position of the CAPS LOCK key
caps_lock_key = (3, 2)

# Possible moves and their associated costs
move_costs = [ ( 300, -1,  0 ),     # Up
               ( 300,  1,  0 ),     # Down
               ( 200,  0, -1 ),     # Left
               ( 200,  0,  1 ),     # Right
               ( 350,  1,  1 ),     # Down-Right
               ( 350, -1,  1 ),     # Up-Right
               ( 350,  1, -1 ),     # Down-Left
               ( 350, -1, -1 ) ]    # Up-Left


def get_neighbours(pos):
    """ For a position, returns the lists of their closer neighbours and it costs """
    y = pos[0]
    x = pos[1]
    neighbours = []
    for m in move_costs:
        new_y = y + m[1]
        new_x = x + m[2]
        if new_x >= 0 and new_x < 3 and new_y >= 0 and new_y < 4 and active_keys[new_y][new_x] == 1:
            neighbours.append((m[0], (new_y, new_x)))

    return neighbours

    
# Dijkstra algorithm
def shortest_path(orig):
    """ For a position, calculates all the costs to all others positions, return the result as a dictionary """
    vertex_list = set([(y,x) for x in range(3) for y in range(4)])
    # Uses sys.maxint as infinity
    dist = dict([(pos, sys.maxint) for pos in vertex_list])

    if active_keys[orig[0]][orig[1]] == 0:
        return dist

    dist[orig] = 0

    while len(vertex_list) > 0:
        min_dist = sys.maxint
        for vertex in vertex_list:
            if dist[vertex] <= min_dist:
                u = vertex
                min_dist = dist[vertex]

        if dist[u] == sys.maxint:
            break

        vertex_list.remove(u)
        neighbours = get_neighbours(u)
        for cost, v in neighbours:
            alt = dist[u] + cost
            if alt < dist[v]:
                dist[v] = alt
    
    return dist
                


def find_key(c):
    """ Returns the letters of the corresponding button """
    upper_c = c.upper()
    for key in letters:
        if upper_c in key:
            return key, letters[key]


if __name__ == "__main__":

    # Calculates all the costs from all the position to all the destinations as a dictionary
    # so we can get the cost just using costs[orig][dest]
    costs = dict([((y,x),shortest_path((y,x))) for x in range(3) for y in range(4)])

    # Number of test cases
    count = int(sys.stdin.readline())

    for i in range(count):
        text = sys.stdin.readline().rstrip('\r\n')
        time = 0
        first_time = True

        caps_lock_enabled = False
        current_key = (3, 1)

        for c in text:
            upper_c = c.upper()

            # Check if it's a letter
            if upper_c in letters_uppercase:
                if (c in letters_uppercase and not caps_lock_enabled) or (c in letters_lowercase and caps_lock_enabled):
                    time += costs[current_key][caps_lock_key] + press_button_time
                    current_key = caps_lock_key
                    caps_lock_enabled = not caps_lock_enabled
        
            letters_in_button, dest_key = find_key(c)
            time += costs[current_key][dest_key]
            time += (letters_in_button.find(upper_c) + 1) * 100

            # The first time we don't have to wait 500 ms
            if current_key == dest_key and not first_time:
                time += 500

            current_key = dest_key
            first_time = False

        print time

