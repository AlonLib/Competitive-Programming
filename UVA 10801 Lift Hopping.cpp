//
// Created by Alon on 25/07/2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <limits.h>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <queue>
#include <set>

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


int func93_A() {
}

// input: non-negatively weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1), source (s).
// output: distances from s (dist).
// time: O(ElogV).
void Dijkstra(const vvii& g, int s, vi& dist) {
    dist = vi(g.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> q;
    q.push({0, s});
    while (!q.empty()) {
        ii front = q.top(); q.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue; // We may have found a shorter way to get to u after inserting it to q.
        // In that case, we want to ignore the previous insertion to q.
        for (ii next : g[u]) {
            int v = next.first, w = next.second;
            if (dist[u]+w < dist[v]) {
                dist[v] = dist[u]+w;
                q.push({dist[v], v});
            }
        }
    }
}


int main() {
    int n, k, floor;
    string line;
    while (cin >> n >> k) {
        vector<int> elevator_time(n, 0);
        for (int &time : elevator_time) cin >> time;

        vvii g(101, vii(0)); // g[u] contains pairs (v,w) such that u->v has weight w
        getline(cin, line);
        for (int elevator = 0; elevator < n; ++elevator) {
            getline(cin, line);
            stringstream ss(line);
            vector<int> floors;
            while (ss >> floor) {
                assert(0 <= floor && floor <= 100);
                floors.push_back(floor);
            }
            for (int i : floors) {
                for (int j : floors) {
                    if (i == j) continue;
                    assert(elevator_time[elevator] * abs(j - i) >= 0);
                    g[i].push_back({j, 60 + elevator_time[elevator] * abs(j - i)});
                }
            }
        }
        if (!k) {
            cout << 0 << endl;
            continue;
        }
        vi dist;
        Dijkstra(g, 0, dist);
        cout << (dist[k] < INF ? to_string(dist[k] - 60) : "IMPOSSIBLE") << endl;
    }
    return 0;
}


