#!/usr/bin/env python
# -*- coding: utf-8 -*-

# *** Challenge 13: The crazy croupier ***

import sys
from fractions import gcd


def lcm_list(l):
    ''' Calculate the least common multiple for a list of integers '''
    if len(l) == 0:
        return 0

    if len(l) == 1:
        return l[0]

    # We calculate the lcm in pairs of integers
    lcm = (l[0] * l[1]) / gcd(l[0], l[1])

    for i in range(2, len(l)):
        lcm = (l[i] * lcm) / gcd(l[i], lcm)

    return lcm



if __name__ == '__main__':
    num_cases = int(sys.stdin.readline())
    
    for ncase in range(num_cases):
        N, L = [int(x) for x in sys.stdin.readline().split()]

        # Calculate the state of the deck after 1 shuffle
        deck = [i for i in range(N)]
        pile1 = deck[:L]
        pile2 = deck[L:]

        deck = []
        while len(pile1) > 0 or len(pile2) > 0:
            if len(pile1) > 0:
                deck.append(pile1.pop())

            if len(pile2) > 0:
                deck.append(pile2.pop())

        # All the shuffles will put the cards in the same order
        # so we make a list to allow us to do the shuffle faster
        order = [0 for i in range(N)]
        for index, value in enumerate(deck):
            order[value] = index

        # And now we don't want to make extra shuffles.
        # We are going to check the cycle for each card
        # but we save computations doing it only once 
        # for each position
        visited = [False for x in range(N)]
        cycles = set()
        positions_visited = 0

        while positions_visited < N:
            # Get the next position of which we don't know its cycle count
            original_pos = visited.index(False)

            cycle_count = 0
            pos = original_pos

            # Until we come back to our original position...
            while(True):
                cycle_count += 1

                # Mark this position as visited
                if (visited[pos] == False):
                    visited[pos] = True
                    positions_visited += 1
                
                # Move the card to its position after the shuffle
                pos = order[pos]
                if pos == original_pos:
                    # We have completed a cycle, add it to the cycles set
                    cycles.add(cycle_count)
                    break
                
        # Now we have to compute the least common multiple of all the cycles found
        lcm = lcm_list(list(cycles))
        
        print "Case #%d: %d" % (ncase + 1, lcm)

