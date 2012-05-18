import sys, math

class Point:
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

    @staticmethod
    def are_equal(p1, p2, epsilon=1e-6):
        return abs(p1.x - p2.x) <= epsilon and abs(p1.y - p2.y) <= epsilon

    def __add__(self, v):
        return Point(self.x + v.x, self.y + v.y)

    def __sub__(self, p):
        return Vector(self.x - p.x, self.y - p.y)

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return "(%f, %f)" % (self.x, self.y)

class Vector:
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

    @staticmethod
    def from_polar(r, ang):
        return Vector(r * math.cos(ang), r * math.sin(ang))

    def normal(self):
        return Vector(-self.y, self.x)

    @staticmethod
    def dot(v1, v2):
        return v1.x * v2.x + v1.y * v2.y

    def __abs__(self):
        return math.sqrt(Vector.dot(self, self))

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return "<%f, %f>" % (self.x, self.y)

class Line:
    def __init__(self, p1, p2):
        self.p = p1
        self.n = (p2 - p1).normal()

    def get_point_position(self, p):
        """pos: left, 0: on, neg: right
        """
        return Vector.dot(p - self.p, self.n)

class Polygon:
    def __init__(self, N, C, V):
        self.N = N
        self.C = C
        vec = V - C
        self.R = abs(vec)
        self.ang = math.atan2(vec.y, vec.x)

    def get_vertices(self):
        ang_inc = 2 * math.pi / self.N
        ang = self.ang
        for n in range(self.N):
            yield self.C + Vector.from_polar(self.R, ang)
            ang += ang_inc

    def get_position_with_line(self, line, epsilon=1e-6):
        """pos: left, 0: crossed, neg: right
        """
        point_positions = map(line.get_point_position, self.get_vertices())
        if all(map(lambda r: r >= -epsilon, point_positions)):
            return 1
        elif all(map(lambda r: r <= epsilon, point_positions)):
            return -1
        else:
            return 0

def get_lines(pizza_center, pizza_ingredients):
    for ingredient in pizza_ingredients.values():
        for ing_item in ingredient:
            for vertex in ing_item.get_vertices():
                if not Point.are_equal(pizza_center, vertex):
                    yield Line(pizza_center, vertex)

def splits_ingredient_evenly(line, ingredient):
    ingredient_pos = map(lambda ing_item: ing_item.get_position_with_line(line), ingredient)
    return all(map(lambda pos: pos != 0, ingredient_pos)) and sum(ingredient_pos) == 0

def splits_pizza_evenly(line, pizza_ingredients):
    return all(map(lambda ingredient: splits_ingredient_evenly(line, ingredient), \
                   pizza_ingredients.values()))

def solve(pizza_center, pizza_ingredients):
    return any(map(lambda line: splits_pizza_evenly(line, pizza_ingredients), \
                   get_lines(pizza_center, pizza_ingredients)))

if __name__ == "__main__":
    cases = int(sys.stdin.readline())
    for c in range(cases):
        px, py, pizza_radius = map(float, sys.stdin.readline().split())
        pizza_center = Point(px, py)
        ingredient_type_count = int(sys.stdin.readline())
        ingredients = {}
        for it in range(ingredient_type_count):
            ingredient_type_name, sing_sides, sing_count = sys.stdin.readline().split()
            ingredient_sides, ingredient_count = int(sing_sides), int(sing_count)
            ingredients[ingredient_type_name] = []
            for n in range(ingredient_count):
                cx, cy, vx, vy = map(float, sys.stdin.readline().split())
                ingredients[ingredient_type_name].append(Polygon(ingredient_sides, Point(cx, cy), Point(vx, vy)))
        print "Case #%d: %s" % (c + 1, "TRUE" if solve(pizza_center, ingredients) else "FALSE")
