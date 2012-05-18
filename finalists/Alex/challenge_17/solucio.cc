#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <list>
using namespace std;

//Mi libreria geometrica
#define x first
#define y second

typedef long double ld;
const ld EPS = 1e-11;
const ld INF = 1e18;

//:::::::::::::2D:::::::::::::::::::::::::::::::::
typedef pair<int, int> Punt; //Integer point type
typedef vector<Punt> Poligon; //Integer-Point Polygon Type
typedef pair<ld, ld> PDD;
typedef pair<PDD, PDD> PPDD;

//Polygon with list
struct Vertex {
    int index;
    Punt p;
    bool ear;
    Vertex *prev, *next;
};

struct Cercle {
    PDD c;
    ld r;
};

Vertex *vertexs = NULL;
int nvertexs = 0;

//Adds p (newed before) to head Polygon 
#define ADD(head, p)    if (head) {\
                            p->next = head;\
                            p->prev = head->prev;\
                            head->prev = p;\
                            p->prev->next = p;\
                        }\
                        else {\
                            head = p;\
                            head->next = head->prev = p;\
                        }
//Deletes p from the Polygon
#define FREE(p) if (p) { delete (p); p = NULL; }


//Returns the distance between two points
inline ld dist(PDD a, PDD b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

//Returns the square of the distance between two points
inline ld dist2(PDD a, PDD b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

//Returns the square of the distance between two points (int)
inline int dist2(Punt a, Punt b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

//Returns the Euclidean norm of a vector
inline ld modul(PDD v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

//Returns the ld of the abc-triangle's area
inline int Area2(Punt a, Punt b, Punt c) {
    return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
}

//Returns the ld of the abc-triangle's area (ld)
inline ld Area2(PDD a, PDD b, PDD c) {
    return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
}

//Returns the ld of the Polygon's area (list version)
int AreaPoly2() {
    int sum = 0;
    Vertex *p, *a;
    p = vertexs;
    a = p->next;
    do {
        sum += Area2(p->p, a->p, a->next->p);
        a = a->next;
    } while (a->next != vertexs);
    return sum;
}

//Returns the ld of the Polygon's area (vector version)
int AreaPoly2(Poligon& v) {
    int sum = 0;
    for (int i = 1; i + 1 < int(v.size()); ++i) 
        sum += Area2(v[0], v[i], v[i + 1]);
    return sum;
}

//True iff c Left de ab
inline bool Left(Punt a, Punt b, Punt c) {
    return Area2(a, b, c) > 0;
}

//True iff c LeftOn de ab
inline bool LeftOn(Punt a, Punt b, Punt c) {
    return Area2(a, b, c) >= 0;
}

//True iff c Left de ab
inline bool Left(PDD a, PDD b, PDD c) {
    return Area2(a, b, c) > 0;
}

//True iff c LeftOn de ab
inline bool LeftOn(PDD a, PDD b, PDD c) {
    return Area2(a, b, c) + EPS > 0;
}

//True iff c Collinear de la Linea que conte ab
inline bool Collinear(Punt a, Punt b, Punt c) {
    return Area2(a, b, c) == 0;
}

//True iff c Collinear de la Linea que conte ab (ld)
inline bool Collinear(PDD a, PDD b, PDD c) {
    return fabs(Area2(a, b, c)) < EPS;
}

//True iff c dins ab
inline bool Between(Punt a, Punt b, Punt c) {
    if (!Collinear(a, b, c)) return false;
    if (a.x != b.x) 
        return ((a.x<=c.x)and(c.x<=b.x))or((a.x>=c.x)and(c.x>=b.x));
    return ((a.y <= c.y)and(c.y <= b.y))or((a.y >= c.y)and(c.y >= b.y));
}

//True iff c dins ab
inline bool Between(PDD a, PDD b, PDD c) {
    if (!Collinear(a, b, c)) return false;
    if (fabs(a.x - b.x) > EPS) 
        return ((a.x<EPS+c.x)and(c.x<EPS+b.x))or((a.x+EPS>c.x)and(c.x+EPS>b.x));
    return ((a.y<EPS+c.y)and(c.y<EPS+b.y))or((a.y+EPS>c.y)and(c.y+EPS>b.y));
}

//True iff ab intersects cd properly
inline bool IntersectProp(Punt a, Punt b, Punt c, Punt d) {
    int abc = Area2(a, b, c), abd = Area2(a, b, d);
    int cda = Area2(c, d, a), cdb = Area2(c, d, b);
    if (abc == 0 or abd == 0 or cda == 0 or cdb == 0) return false;
    return (!(abc > 0) ^ !(abd > 0)) and (!(cda > 0) ^ !(cdb > 0));
}

//True iff ab intersects cd
inline bool Intersect(Punt a, Punt b, Punt c, Punt d) {
    return IntersectProp(a, b, c, d) or Between(a, b, c) or 
           Between(a, b, d) or Between(c, d, a) or Between(c, d, b);
}

//True iff ab doesn't intersect any edge (list version)
bool Diagonalie(Vertex* a, Vertex* b) {
    Vertex *c = vertexs, *c1;
    do {
        c1 = c->next;
        if ((c != a) and (c1 != a) and (c != b) and (c1 != b) and 
             Intersect(a->p, b->p, c->p, c1->p)) return false;
        c = c->next;
    } while (c != vertexs);
    return true;
}

//True iff ab doesn't intersect any edge (vector version)
bool Diagonalie(int i1, int i2, Poligon& v) {
    int c = 0, c1;
    do {
        c1 = (c + 1 == int(v.size())) ? 0 : c + 1;
        if ((c != i1) and (c1 != i1) and (c != i2) and (c1 != i2) and 
             Intersect(v[i1], v[i2], v[c], v[c1])) return false;
        c = (c + 1 == int(v.size())) ? 0 : c + 1;
    } while (c != 0);
    return true;
}

//True iff Diagonal ab is interior (list version)
inline bool InCone(Vertex* aV, Vertex* bV) {
    Punt a0 = aV->prev->p, a1 = aV->next->p, a = aV->p, b = bV->p;
    if (LeftOn(a, a1, a0)) return Left(a, b, a0) and Left(b, a, a1);
    return !(LeftOn(a, b, a1) and LeftOn(b, a, a0));
}

//True iff Diagonal ab is interior (vector version)
inline bool InCone(int i1, int i2, Poligon& v) {
    Punt a = v[i1], b = v[i2];
    Punt a0 = v[(i1 - 1 < 0) ? int(v.size()) - 1 : i1 - 1];
    Punt a1 = v[(i1 + 1 == int(v.size())) ? 0 : i1 + 1];
    if (LeftOn(a, a1, a0)) return Left(a, b, a0) and Left(b, a, a1);
    return !(LeftOn(a, b, a1) and LeftOn(b, a, a0));
}

//True iff ab is a diagonal (list version)
inline bool Diagonal(Vertex* a, Vertex* b) {
    return InCone(a, b) and Diagonalie(a, b);
}

//True iff ab is a diagonal (vector version)
inline bool Diagonal(int i1, int i2, Poligon& v) {
    return InCone(i1, i2, v) and Diagonalie(i1, i2, v);
}

//Initializes vertexs' ear parameter for ear cutting triangulation
void EarInit() {
    Vertex *v0, *v1 = vertexs, *v2;
    do {
        v2 = v1->next;
        v0 = v1->prev;
        v1->ear = Diagonal(v0, v2);
        v1 = v1->next;
    } while (v1 != vertexs);
}

void Triangulate() {
    Vertex *v0, *v1, *v2, *v3, *v4;
    int n = nvertexs;
    EarInit();
    while (n > 3) {
        v2 = vertexs;
        do {
            if (v2->ear) {
                v3 = v2->next; v4 = v3->next;
                v1 = v2->prev; v0 = v1->prev;
                v1->ear = Diagonal(v0, v3);
                v3->ear = Diagonal(v1, v4);
                cout <<"("<< v1->index <<","<< v3->index <<")"<< endl;
                v1->next = v3;
                v3->prev = v1;
                vertexs = v3;
                FREE(v2);
                --n;
                break;
            }
            v2 = v2->next;
        } while (v2 != vertexs);
    }
}

//Returns the principal angle in radians between the lines ab, cd
ld angle2Rectes(PDD a, PDD b, PDD c, PDD d) {
    PDD v1(a.x - b.x, a.y - b.y), v2(c.x - d.x, c.y - d.y);
    ld prod = v1.x*v2.x + v1.y*v2.y;
    prod /= (modul(v1)*modul(v2));
    return acos(prod);
}

//Returns the two lines' intersection
PDD InterRectaRecta(PDD a, PDD b, PDD c, PDD d) {
    ld A = b.y - a.y, B = a.x - b.x, C;
    C = A*a.x + B*a.y;
    ld E = c.x - d.x, D = d.y - c.y, F;
    F = D*c.x + E*c.y;
    ld det = A*E - B*D;
    if (fabs(det) < EPS) throw 0;
    return PDD( (E*C - B*F)/det, (-D*C +A*F)/det);
}

//Returns the circle defined by three points
Cercle Cercle3Punts(PDD a, PDD b, PDD c) {
    if (Collinear(a, b, c)) throw 0;
    ld A = -(a.x - b.x), B = b.y - a.y, C;
    PDD mig = PDD((a.x + b.x)/2.0, (a.y + b.y)/2.0);
    C = A*mig.x + B*mig.y;
    ld D = -(c.x - b.x), E = b.y - c.y, F;
    PDD mig2 = PDD((c.x + b.x)/2.0, (c.y + b.y)/2.0);
    F = D*mig2.x + E*mig2.y;
    ld det = A*E - B*D;
    ld x = (E*C - B*F)/det, y = (-D*C +A*F)/det;
    Cercle res;
    res.c = PDD(x, y); res.r = dist(res.c, a);
    return res;
}

//Returns a point from the line ab rotated counterclockwise
PDD giraRecta(PDD a, PDD b, ld alfa) {
    PDD v(b.x - a.x,b.y - a.y);
    PDD v2(v.x*cos(alfa)-v.y*sin(alfa),v.x*sin(alfa)+v.y*cos(alfa));
    return PDD(a.x + v2.x, a.y + v2.y);
}

//Returns the bisection of the lines ab and ac
PDD Bisectriu(PDD a, PDD b, PDD c) {
    ld alfa = angle2Rectes(a, b, a, c);
    if (LeftOn(a, c, b)) return giraRecta(a, c, alfa/2);
    else return giraRecta(a, b, alfa/2);
}

//Returns the distance between a Point and a line
ld distPuntRecta(PDD a, PDD b, PDD p) {
    ld B = (a.x - b.x), A = b.y - a.y, C;
    C = A*a.x + B*a.y;
    ld D = -(a.x - b.x), E = b.y - a.y, F;
    F = D*p.x + E*p.y;
    ld det = A*E - B*D;
    return dist(PDD( (E*C - B*F)/det, (-D*C +A*F)/det), p);
}

//Returns a vector with the intersection points between 
//line ab and circle c
vector<PDD> InterRectaCirc(PDD a, PDD b, Cercle c) {
    ld d = distPuntRecta(a, b, c.c);
    vector<PDD> res;
    if (d > c.r) return res;
    ld A = b.y - a.y, B = a.x - b.x, C;
    C = A*a.x + B*a.y;
    ld D = -(a.x - b.x), E = b.y - a.y, F;
    F = D*c.c.x + E*c.c.y;
    ld det = A*E - B*D;
    if (fabs(c.r - d) < EPS) 
        res.push_back(PDD((E*C - B*F)/det, (-D*C + A*F)/det));
    else if (Between(a, b, c.c)) {
        PDD v(a.x - b.x, a.y - b.y);
        ld norm = modul(v);
        v.x /= norm; v.y /= norm;
        res.push_back(PDD(c.c.x + c.r*v.x, c.c.y + c.r*v.y));
        res.push_back(PDD(c.c.x - c.r*v.x, c.c.y - c.r*v.y));
    }
    else {
        PDD p( (E*C - B*F)/det, (-D*C +A*F)/det);
        ld d2 = dist(c.c, p);
        ld alfa = acos(d2/c.r);
        PDD p2 = giraRecta(c.c, p, alfa);
        res.push_back(InterRectaRecta(a, b, c.c, p2));
        p2 = giraRecta(c.c, p, -alfa);
        res.push_back(InterRectaRecta(a, b, c.c, p2));
    }
    return res;
}

vector<PDD> InterCircCirc(Cercle C1, Cercle C2) {
    ld d = dist(C1.c, C2.c);
    vector<PDD> res;
    if (fabs(C1.c.x-C2.c.x)<EPS and fabs(C1.c.y-C2.c.y)<EPS 
        and fabs(C1.r-C2.r)<EPS) {
        if (C1.r > EPS) throw 0;
        res.push_back(C1.c);
        return res;
    }
    if (d>C1.r+C2.r+EPS or C1.r>d+C2.r+EPS or C2.r>d+C1.r+EPS) 
        return res;
    if (fabs(d-C1.r-C2.r)<EPS or fabs(C1.r-d-C2.r)<EPS 
        or fabs(C2.r-d-C1.r)<EPS) {
        res = InterRectaCirc(C1.c, C2.c, C1);
        vector<PDD> res2;
        for (int i = 0; i < res.size(); ++i) 
            if (fabs(dist(res[i], C2.c) - C2.r) < EPS) 
                res2.push_back(res[i]);
        return res2;
    }
    ld alfa2 = acos((C2.r*C2.r + d*d - C1.r*C1.r)/(2*C2.r*d));
    ld alfa1 = acos((C1.r*C1.r + d*d - C2.r*C2.r)/(2*C1.r*d));
    PDD p1 = giraRecta(C1.c, C2.c, alfa1);
    PDD p2 = giraRecta(C2.c, C1.c, -alfa2);
    res.push_back(InterRectaRecta(C1.c, p1, C2.c, p2));
    p1 = giraRecta(C1.c, C2.c, -alfa1);
    p2 = giraRecta(C2.c, C1.c, alfa2);
    res.push_back(InterRectaRecta(C1.c, p1, C2.c, p2));
    return res;
}

//Returns the two closest points
//vx is ordered by x, vy is ordered by y, NO REPEATED POINTS
PPDD ClosestPair(vector<PDD>& vx, vector<PDD>& vy) {
    int n = vx.size();
    if (n == 2) return PPDD(vx[0], vx[1]);
    if (n == 1) return PPDD(vx[0], PDD(vx[0].x + INF, vx[0].y + INF));
    vector<PDD> v2x((n - 1)/2 + 1), v2y((n - 1)/2 + 1);
    vector<PDD> v3x(vx.size() - v2x.size()), v3y(vy.size() - v2y.size());
    for (int i = 0; i < v2x.size(); ++i) v2x[i] = vx[i];
    for (int i = 0; i < v3x.size(); ++i) v3x[i] = vx[i + v2x.size()];
    for (int i = 0, t1 = 0, t2 = 0; i < vy.size(); ++i) {
        if (vy[i]<vx[(n - 1)/2] or dist2(vy[i],vx[(n - 1)/2])<EPS) 
            v2y[t1++] = vy[i];
        else v3y[t2++] = vy[i];
    }
    PPDD a = ClosestPair(v2x, v2y);
    PPDD b = ClosestPair(v3x, v3y);
    if (dist2(b.first, b.second) < dist2(a.first, a.second)) swap(a, b);
    ld dmin = dist2(a.first, a.second);
    list<PDD> aux;
    for (int i=0; i<vy.size(); ++i) 
        if (fabs(vy[i].x-vx[(n - 1)/2].x)<dmin) aux.push_back(vy[i]);
    for (list<PDD>::iterator it = aux.begin(); it != aux.end(); ++it) {
        list<PDD>::iterator it2 = it;
        ++it2;
        while (it2 != aux.end() and fabs(it->y - it2->y) < dmin) {
            if (dist2(*it, *it2) < dist2(a.first, a.second)) 
                a = PPDD(*it, *it2);
            ++it2;
        }
    }
    return a;
}

//Returns the lower and the upper bound of the convex hull
pair<vector<Punt>, vector<Punt> > ConvexHull(vector<Punt>& v) {
    int n = v.size(), k1 = 0, k2 = 0;
    vector<Punt> L(n), U(n);
    sort(v.begin(), v.end());
    for (int i = 0; i < n; ++i) {
        while (k1 >= 2 and Area2(L[k1 - 2], L[k1 - 1], v[i]) <= 0) --k1;
        while (k2 >= 2 and Area2(U[k2 - 2], U[k2 - 1], v[i]) >= 0) --k2;
        L[k1++] = U[k2++] = v[i];
    }
    L.resize(k1);
    U.resize(k2);
    return pair<vector<Punt>, vector<Punt> >(L, U);
}

//Return the farthest pair of points
pair<Punt, Punt> FarthestPair(vector<Punt>& v) {
    pair<vector<Punt>, vector<Punt> > convex = ConvexHull(v);
    vector<Punt> L = convex.first, U = convex.second;
    int maxdist = -1;
    pair<Punt, Punt> res;
    int i = 0, j = L.size() - 1;
    while (i < U.size() - 1 or j > 0) {
        int d = dist2(U[i], L[j]);
        if (d > maxdist) {
            maxdist = d;
            res = pair<Punt, Punt>(U[i], L[j]);
        }
        if (i == U.size() - 1) --j;
        else if (j == 0 or (U[i+1].y-U[i].y)*(L[j].x-L[j-1].x) > 
                           (L[j].y-L[j-1].y)*(U[i+1].x-U[i].x)) ++i;
        else --j;
    }
    return res;
}

//A partir de aqui empieza el codigo.................................................

typedef vector<PDD> VP;
typedef vector<VP> VVP;
typedef vector<VVP> VVVP;

VP genera_regular(PDD c, PDD v, int n) {
    VP res;
    for (int i = 0; i < n; ++i) {
        v = giraRecta(c, v, 2.0*M_PI/n);
        res.push_back(v);
    }
    return res;
}

bool check(PDD x, PDD y, VVVP& ing) {
    for (int i = 0; i < ing.size(); ++i) {
        int left = 0;
        for (int j = 0; j < ing[i].size(); ++j) {
            //Miro si el poligono se corta
            for (int k = 0; k < ing[i][j].size(); ++k) {
                PDD a = ing[i][j][k], b = ing[i][j][(k + 1)%ing[i][j].size()];
                if ((Left(x, y, a) and not LeftOn(x, y, b)) or (Left(x, y, b) and not LeftOn(x, y, a))) return false;
            }
            
            //Miro cuantos hay a cada lado (No miro el primero solo por si esta encima)
            for (int k = 0; k < ing[i][j].size(); ++k) {
                if (Left(x, y, ing[i][j][k])) {
                    ++left;
                    break;
                }
            }
        }
        
        int qtt = ing[i].size();
        if (qtt%2 == 1 or qtt/2 != left) return false;
    }
    return true;
}


//Basta comprobar las rectas que pasan por vertices de los poligonos
int main() {
    int casos;
    cin >> casos;
    for (int cas = 1; cas <= casos; ++cas) {
        PDD centre;
        ld spam;
        cin >> centre.x >> centre.y >> spam;
        int n;
        cin >> n;
        VVVP ing(n);
        for (int i = 0; i < n; ++i) {
            string spam2;
            int lados, m;
            cin >> spam2 >> lados >> m;
            ing[i].resize(m);
            for (int j = 0; j < m; ++j) {
                PDD c, v;
                cin >> c.x >> c.y >> v.x >> v.y;
                ing[i][j] = genera_regular(c, v, lados);
            }
        }
        bool ok = false;
        for (int i = 0; i < n and not ok; ++i) {
            for (int j = 0; j < ing[i].size() and not ok; ++j) {
                for (int k = 0; k < ing[i][j].size() and not ok; ++k) {
                    if (check(ing[i][j][k], centre, ing)) ok = true;
                }
            }
        }
        cout << "Case #" << cas << ": ";
        if (ok) cout << "TRUE" << endl;
        else cout << "FALSE" << endl;
    }
}