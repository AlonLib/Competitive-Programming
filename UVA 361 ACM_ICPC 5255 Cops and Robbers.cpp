//
// Created by Alon on 30/06/2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;




#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <bitset>
#include <cmath>
#include <map>
#include <unordered_map>
#include <set>
#include <numeric>
#include <stack>

#define INF 1e9
#define EPS 1e-7
#define PI acos(-1.0)

#define FIND(ds, x) (find(ds.begin(), ds.end(), x))
#define CONTAINS(ds, x) (FIND(ds, x) != ds.end())

using namespace std;

typedef long long ll;

typedef pair<int, int> ipair;
typedef pair<long long, long long> llpair;
typedef pair<double, double> dpair;
typedef pair<double, double> dpair;
typedef pair<char, char> cpair;

typedef vector<int> ivec;
typedef vector<long long> llvec;
typedef vector<double> dvec;
typedef vector<bool> bvec;
typedef vector<char> cvec;

typedef set<int> iset;
typedef set<long long> llset;
typedef set<double> dset;
typedef set<bool> bset;
typedef set<char> cset;

typedef stack<int> istack;
typedef stack<long long> llstack;
typedef stack<double> dstack;
typedef stack<bool> bstack;
typedef stack<char> cstack;

typedef queue<int> iqueue;
typedef queue<long long> llqueue;

typedef priority_queue<int, vector<int>, greater<int>> ipqueue;
typedef priority_queue<long long, vector<long long>, greater<long long>> llpqueue;

typedef vector<vector<long long>> graph;
typedef vector<vector<pair<long long, long long>>> wgraph;

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

class point {
public:
    double x = 0, y = 0;

    point() = default;

    point(double x, double y) : x(x), y(y) {}

    bool operator<(point other) const {
        if (fabs(x - other.x) > EPS) {
            return x < other.x;
        }
        return y < other.y;
    }

    bool operator==(point other) const {
        return fabs(x - other.x) < EPS && fabs(y - other.y) < EPS;
    }

    point operator+(point other) const {
        return {x + other.x, y + other.y};
    }

    point operator-(point other) const {
        return {x - other.x, y - other.y};
    }

};

point operator*(double c, point p) {
    return {c * p.x, c * p.y};
}

double dot(point p, point q) {
    return p.x * q.x + p.y * q.y;
}

double norm2(point p) {
    return dot(p, p);
}

double dist2(point p, point q) {
    return norm2(p - q);
}

double cross(point p, point q) {
    return p.x * q.y - p.y * q.x;
}

point projectPointOntoSegment(point a, point b, point c) {
    double r = dist2(a, b);
    if (fabs(r) < EPS) return a;
    r = dot(c - a, b - a) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + r * (b - a);
}

bool pointOnPolygon(const vector<point>& p, point q) {
    for (int i = 0; i < p.size(); i++) {
        if (projectPointOntoSegment(p[i], p[(i + 1) % p.size()], q) == q) {
            return true;
        }
    }
    return false;
}

bool pointInPolygon(const vector<point>& p, point q) {
    bool c = false;
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        if ((p[i].y <= q.y && q.y < p[j].y || p[j].y <= q.y && q.y < p[i].y) &&
            q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y)) {
            c = !c;
        }
    }
    return c || pointOnPolygon(p,q);
}

bool ccw(point p, point q, point r) {
    return cross((p - q), (p - r)) > 0;
}

vector<point> convex_hull(vector<point> Points) {

    //-------------- incremental alg. ---------
    // upper hull
    sort(Points.begin(), Points.end());
    stack<point> stk_up;
    stk_up.push(Points[0]);
    stk_up.push(Points[1]);
    for (int i = 2; i < Points.size(); i++) {
        while ((stk_up.size() >= 2)) {
            point p2, p3;
            p2 = stk_up.top();
            stk_up.pop();
            p3 = stk_up.top();
            if (ccw(Points[i], p2, p3)) {
                stk_up.push(p2);
                break;
            }
        }
        stk_up.push(Points[i]);
    }
    // lower hull
    for (int i = 0; i < Points.size(); i++) {
        Points[i].x = -Points[i].x;
        Points[i].y = -Points[i].y;
    }
    sort(Points.begin(), Points.end());
    stack<point> stk_low;
    stk_low.push(Points[0]);
    stk_low.push(Points[1]);
    for (int i = 2; i < Points.size(); i++) {
        while ((stk_low.size() >= 2)) {
            point p2, p3;
            p2 = stk_low.top();
            stk_low.pop();
            p3 = stk_low.top();
            if (ccw(Points[i], p2, p3)) {
                stk_low.push(p2);
                break;
            }
        }
        stk_low.push(Points[i]);
    }

    // print convex hull - cw order from leftmost point
    vector<point> CH;
    stk_low.pop();
    point p;
    while (!stk_low.empty()) {
        p = stk_low.top();
        p.x = -p.x;
        p.y = -p.y;
        CH.push_back(p);
        stk_low.pop();
    }
    stk_up.pop();
    while (!stk_up.empty()) {
        CH.push_back(stk_up.top());
        stk_up.pop();
    }
    reverse(CH.begin(), CH.end());  // ccw -> cw
    return CH;
}



int main() { // Cops and Robbers - Kattis copsandrobbers 
    int c, r, o, index = 0;
    while (cin >> c >> r >> o) {
        if (!c && !r && !o) break;
        cout << "Data set " << ++index  << ":" << endl;
        vector<point> cops(c), robbers(r);
        for (point &p : cops) cin >> p.x >> p.y;
        vector<point> ch_cops = c > 2 ? convex_hull(cops) : vector<point>();
        for (point &p : robbers) cin >> p.x >> p.y;
        vector<point> ch_robbers = r > 2 ? convex_hull(robbers) : vector<point>();
        for (int i = 0; i < o; ++i) {
            point p;
            cin >>p. x >> p.y;
            cout << "     Citizen at (" << p.x << "," << p.y << ") is ";
            if (pointInPolygon(ch_cops, p)) {
                cout << "safe." << endl;
            } else {
                cout << (pointInPolygon(ch_robbers, p) ? "robbed." : "neither.") << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
