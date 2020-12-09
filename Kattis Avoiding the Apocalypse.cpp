//
// Created by Alon on 13/06/2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <climits>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
typedef vector<map<int, int>> vmii;

const int INF = 1e9;
using namespace std;
typedef long long ll;

/********** Max Flow **********/
typedef pair<int, int> pii;

int augment(vector<map<int, int>>& res, int s, int t, const vi& p, int minEdge) {
        // traverse the path from s to t according to p.
        // change the residuals on this path according to the min edge weight along this path.
        // return the amount of flow that was added.
        if (t == s) {
            return minEdge;
        } else if (p[t] != -1) {
            int f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]));
            res[p[t]][t] -= f;
            res[t][p[t]] += f;
            return f;
        }
        return 0;
}

// input: number of nodes (n), all nodes are between 0 and n-1,
//        edges v1->v2 of the form (weight,(v1,v2)), source (s) and target (t).
// output: max flow from s to t over the edges.
// time: O(VE^2) and O(EF).
int EdmondsKarp (int n, vector<iii>& edges, int s, int t, vmii& res) {
    // initialise adjacenty list and residuals adjacency matrix

   // vvi res(n,vi(n,0));
    vvi adj(n);
    for (iii e : edges) {
        res[e.second.first][e.second.second] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    // while we can add flow
    int addedFlow, maxFlow = 0;
    do {
        // save to p the BFS tree from s to t using only edges with residuals
        //vi dist(res.size(), INF);
        vi dist(n, INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
       // vi p(res.size(), -1);
        vi p(n, -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int v : adj[u]) if (res[u][v] > 0 && dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    p[v] = u;
                }
        }
        // add flow on the path between s to t according to p
        addedFlow = augment(res, s, t, p, INF);
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    return maxFlow;
}



int locations, start_location, number_of_people, number_of_steps, number_of_medics, number_of_roads;
#define NODE(specific_location, time) (locations * (time) + specific_location)
#define START_NODE 0
#define END_NODE (locations * number_of_steps + 1)
#define NUMBER_OF_NODES (locations * number_of_steps + 2)
#define INF_PEOPLE (1000 * 1000)

int main() {
    int cases;
    cin >> cases;
    while (cases--) {
        vector<iii> edges;
        cin >> locations >> start_location >> number_of_people >> number_of_steps >> number_of_medics;
        number_of_steps++;
        // limit the flow
        edges.push_back({number_of_people, {START_NODE, NODE(start_location, 0)}});

        for (int i = 0; i < number_of_medics; ++i) { // all medics go to the sink
            int m;
            cin >> m;
            edges.push_back({INF_PEOPLE, {NODE(m, number_of_steps - 1), END_NODE}});
        }

        cin >> number_of_roads;
        for (int i = 0; i < number_of_roads; ++i) { //possible edges from input
            int from, to, max_people, stall_time;
            cin >> from >> to >> max_people >> stall_time;
            for (int time = 0; time + stall_time < number_of_steps; ++time) {
                edges.push_back({max_people, {NODE(from, time), NODE(to, time + stall_time)}});
            }
        }

        for (int location = 1; location <= locations; ++location) { // waiting edges
            for (int time = 1; time < number_of_steps; ++time) {
                edges.push_back({INF_PEOPLE, {NODE(location, time - 1), NODE(location, time)}});
            }
        }

        vector<map<int, int>> adj(NUMBER_OF_NODES);
        cout << EdmondsKarp(NUMBER_OF_NODES, edges, START_NODE, END_NODE, adj) << endl;
    }
    return 0;
}


