import sys, re

vertical_move_cost = 300
horizontal_move_cost = 200
diagonal_move_cost = 350
press_cost = 100
same_key_wait = 500

keyboard_layout = {
    ' ': (1, 1), '1': (1, 2), '2': (2, 4), '3': (3, 4), '4': (4, 4), '5': (5, 4), '6': (6, 4), 
    '7': (7, 5), '8': (8, 4), '9': (9, 5), '0': (11, 1), 'A': (2, 1), 'B': (2, 2), 'C': (2, 3), 
    'D': (3, 1), 'E': (3, 2), 'F': (3, 3), 'G': (4, 1), 'H': (4, 2), 'I': (4, 3), 'J': (5, 1), 
    'K': (5, 2), 'L': (5, 3), 'M': (6, 1), 'N': (6, 2), 'O': (6, 3), 'P': (7, 1), 'Q': (7, 2), 
    'R': (7, 3), 'S': (7, 4), 'T': (8, 1), 'U': (8, 2), 'V': (8, 3), 'W': (9, 1), 'X': (9, 2), 
    'Y': (9, 3), 'Z': (9, 4), '^': (12, 1)
}
for k, v in keyboard_layout.items():
    keyboard_layout[k.lower()] = v
caps_lock_key = 12
initial_key = 11

def compute_costs():
    move_costs = {}
    for f in range (12):
        fr = f / 3
        fc = f % 3
        for t in range(12):
            if f == t:
                cost = same_key_wait
            else:
                tr = t / 3
                tc = t % 3
                rd = abs(tr - fr)
                cd = abs(tc - fc)
                diagonal = min(rd, cd)
                cost = diagonal * diagonal_move_cost + \
                       (rd - diagonal) * vertical_move_cost + \
                       (cd - diagonal) * horizontal_move_cost
            move_costs[(f+1, t+1)] = cost
    return move_costs

move_costs = compute_costs()
cases = int(sys.stdin.readline())
for c in range(cases):
    text = sys.stdin.readline().strip()
    caps = False
    current_key = initial_key
    cost = 0
    for c in text:
        if c.isalpha() and c.isupper() != caps:
            cost = cost + move_costs[(current_key, caps_lock_key)] + press_cost
            current_key = caps_lock_key
            caps = not caps
        target_key, press_count = keyboard_layout[c]
        cost = cost + move_costs[(current_key, target_key)]
        current_key = target_key
        cost = cost + press_count * press_cost
    print cost
