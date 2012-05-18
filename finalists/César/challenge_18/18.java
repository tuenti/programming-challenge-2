import sys, re

instruction_translation = {
    ('Bee.', 'Bee?'): '>', ('Bee?', 'Bee.'): '<', ('Bee.', 'Bee.'): '+', ('Bee!', 'Bee!'): '-',
    ('Bee.', 'Bee!'): ',', ('Bee!', 'Bee.'): '.', ('Bee!', 'Bee?'): '[', ('Bee?', 'Bee!'): ']'
}
class BeeProgram:
    def __init__(self, beefile):
        self._load(beefile)

    def run(self):
        memory = [0] * 300000 # Apparently, this is the standard memory size.
        output, ip, dp = "", 0, 0
        while 0 <= ip < len(self.program):
            instr = self.program[ip]
            if instr == '>':
                dp += 1
            elif instr == '<':
                dp -= 1
            elif instr == '+':
                memory[dp] += 1
            elif instr == '-':
                memory[dp] -= 1
            elif instr == ',':
                pass
            elif instr == '.':
                output += chr(memory[dp])
            elif instr == '[':
                if memory[dp] == 0:
                    ip = self.brackets[ip]
            elif instr == ']':
                if memory[dp] != 0:
                    ip = self.brackets[ip]
            ip += 1
        return output

    def _load(self, beefile):
        f = open(beefile, "r")
        raw_program = re.findall("Bee.", f.read())
        f.close()
        self.program = map(instruction_translation.get, \
                           zip(raw_program[0:len(raw_program):2], raw_program[1:len(raw_program):2]))
        self.brackets = {}
        stack = []
        for ip in range(len(self.program)):
            if self.program[ip] == '[':
                stack.append(ip)
            elif self.program[ip] == ']':
                opening_pos = stack.pop()
                self.brackets[opening_pos] = ip
                self.brackets[ip] = opening_pos

def get_maximum_pieces(n):
    return 1 + n * (n + 1) / 2

if __name__ == "__main__":
    # program = BeeProgram("program.bee")
    # print program.run()
    # Input is the number of straight cuts made through a round chocolate cake and output is the maximum number of cake pieces that can be produced.
    cases = int(sys.stdin.readline())
    for c in range(cases):
        print "Case #%d: %s" % (c + 1, get_maximum_pieces(int(sys.stdin.readline())))
