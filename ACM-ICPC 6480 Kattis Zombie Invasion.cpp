//
// Created by Alon on 07/04/2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cfloat>
#include <queue>
#include <cassert>
#include <set>
#include <cstdlib>

using namespace std;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;



int Dijkstra(const vvii& g, int s, int maxd, vi& dist) {
// input: non-negatively weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1), source (s).
// output: distances from s (dist).
// time: O(ElogV).
    int new_unsafe_towns = 0;
    if (dist[s] >= maxd) ++new_unsafe_towns;
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> q;
    q.push({0, s});
    while (!q.empty()) {
        ii front = q.top(); q.pop();
        int d = front.first, u = front.second;
        if (d >= maxd) break; // (alon) early stop
        if (d > dist[u]) continue; // We may have found a shorter way to get to u after inserting it to q.
        // In that case, we want to ignore the previous insertion to q.
        for (ii next : g[u]) {
            int v = next.first, w = next.second;
            if (dist[u]+w < maxd/*(alon)*/ && dist[u]+w < dist[v]) {
                if (dist[v] >= maxd) ++new_unsafe_towns;
                dist[v] = dist[u]+w;
                q.push({dist[v], v});
            }
        }
    }
    return new_unsafe_towns;
}
int main() {
    int towns, roads, bases, min_distance;
    cin >> towns >> roads >> bases >> min_distance;
    while (towns || roads || bases || min_distance) {
        vvii mat(towns+1, vii(0));
        while (roads--) {
            int t1, t2, d;
            cin >> t1 >> t2 >> d;
            mat[t1].push_back({t2, d});
            mat[t2].push_back({t1, d});
        }
        // calc distances
        // get bases and store unsafe_towns
        int unsafe_towns = 0;
        vi dist_from_base(mat.size(), INF);
        while (bases--) {
            int b;
            cin >> b;
            unsafe_towns += Dijkstra(mat, b, min_distance, dist_from_base);
            cout << towns - unsafe_towns << endl;
        }
        cout << endl;
        cin >> towns >> roads >> bases >> min_distance;
    }

    return 0;
}
