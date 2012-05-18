import sys, collections

class Graph:
    def __init__(self, seqs):
        self.transitions = collections.defaultdict(set)
        for seq in seqs:
            for f, t in zip(seq, seq[1:]):
                self.transitions[f].add(t)
                if not t in self.transitions:
                    self.transitions[t] = set()

    def get_topological_sorts(self):
        return self._get_topological_sorts(set())

    def _get_topological_sorts(self, visited):
        leaves = list(f for f, t in self.transitions.items() if f not in visited and t <= visited)
        if len(leaves) == 0:
            sorts = [""]
        else:
            sorts = []
            for leaf in leaves:
                visited.add(leaf)
                sorts += map(lambda s: s + leaf, self._get_topological_sorts(visited))
                visited.remove(leaf)
        return sorts

if __name__ == "__main__":
    graph = Graph(list(seq.strip() for seq in sys.stdin))
    print "\n".join(sorted(graph.get_topological_sorts()))
