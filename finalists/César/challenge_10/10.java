import sys, hashlib

def process_program(program):
    tokens = program.split(" ")
    stack = []
    for token in tokens:
        if token.isdigit():
            stack.append(int(token))
        elif token == "mirror":
            stack.append(-stack.pop())
        elif token == "breadandfish":
            stack.append(stack[-1])
        elif token == "fire":
            stack.pop()
        elif token == "dance":
            op2 = stack.pop()
            op1 = stack.pop()
            stack.append(op2)
            stack.append(op1)
        elif token == "@":
            stack.append(stack.pop() + stack.pop())
        elif token == "$":
            stack.append(-stack.pop() + stack.pop())
        elif token == "#":
            stack.append(stack.pop() * stack.pop())
        elif token == "&":
            op2 = stack.pop()
            op1 = stack.pop()
            stack.append(op1 / op2)
        elif token == "conquer":
            op2 = stack.pop()
            op1 = stack.pop()
            stack.append(op1 % op2)
        elif token != ".":
            return "UNKNOWN: " + token
    return stack[0]

if __name__ == "__main__":
    for line in sys.stdin:
        print process_program(line.strip())
