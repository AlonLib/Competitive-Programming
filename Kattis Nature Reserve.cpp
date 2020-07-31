//
// Created by Alon on 09/06/2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
const int INF = 1e9;
typedef long long ll;

/********** Min Spanning Tree **********/

struct unionfind {
    vector<int> rank;
    vector<int> parent;

    unionfind(int size) {
        rank = vector<int>(size, 0);
        parent = vector<int>(size);
        for (int i = 0; i < size; i++) parent[i] = i;
    }

    int find(int x) {
        int tmp = x;
        while (x != parent[x]) x = parent[x];
        while (tmp != x) {
            int remember = parent[tmp];
            parent[tmp] = x;
            tmp = remember;
        }
        return x;
    }

    void unite(int p, int q) {
        p = find(p);
        q = find(q);
        if (q == p) return;
        if (rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if (rank[p] == rank[q]) rank[p]++;
    }
};


// input: edges v1->v2 of the form (weight,(v1,v2)),
//        number of nodes (n), all nodes are between 0 and n-1.
// output: weight of a minimum spanning tree.
// time: O(ElogV).
int Kruskal(vector<iii> &edges, int n) {
    sort(edges.begin(), edges.end());
    int mst_cost = 0;
    unionfind components(n);
    for (iii e : edges) {
        if (components.find(e.second.first) !=
            components.find(e.second.second)) {
            mst_cost += e.first;
            components.unite(e.second.first, e.second.second);
        }
    }
    return mst_cost;
}



int main() {
    int data_sets;
    cin >> data_sets;
    while (data_sets--) {
        int N, M, L, S;
        cin >> N >> M >> L >> S;
        // node 0 is new station connecting all the stations with edges with zero weight
        vector<iii> edges(S + M, {0, {-1, 0}});
        // node n is new station connecting all the stations
        for (int i = 0; i < S; ++i)
            cin >> edges[i].second.first;
        for (int i = 0; i < M; ++i)
            cin >> edges[S + i].second.first >> edges[S + i].second.second >> edges[S + i].first;

        cout << Kruskal(edges, N + 1) + (long long)(N - S) * L << endl;
    }
    return 0;
}
