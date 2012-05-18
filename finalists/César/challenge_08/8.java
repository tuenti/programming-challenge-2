import sys, hashlib

def transform(queue, transformation):
    return "".join([transformation[q] if q in transformation else q for q in queue])

if __name__ == "__main__":
    queue = sys.stdin.readline().strip()
    final_transformation = {}
    for line in sys.stdin:
        transformation = dict(tuple(t.split("=>")) for t in line.strip().split(","))
        for f, t in final_transformation.items():
            final_transformation[f] = transform(t, transformation)
        for f, t in transformation.items():
            if f not in final_transformation:
                final_transformation[f] = t
    
    # Calculate the md5.
    m = hashlib.md5()
    for q in queue:
        m.update(final_transformation[q] if q in final_transformation else q)
    print m.hexdigest()
