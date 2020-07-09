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

// input: weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1).
// output: the pairwise distances (d).
// time: O(V^3).
void FloydWarshall(const vvii& g, vvi& d) {
    // initialize distances according to the graph edges
    d.assign(g.size(), vi(g.size(), INF));
    for (int u=0; u<g.size(); ++u) d[u][u] = 0;
    for (int u=0; u<g.size(); ++u) for (ii e: g[u]) {
            int v = e.first; int w = e.second;
            d[u][v] = min(d[u][v],w);
        }
    // relax distances using the Floyd-Warshall algorithm
    for (int k=0; k<g.size(); ++k)
        for (int u=0; u<g.size(); ++u)
            for (int v=0; v<g.size(); ++v)
                d[u][v] = min(d[u][v], d[u][k]+d[k][v]);
}

int main() {
    int m, n;

    cin >> m >> n;
//    vector<vector<bool>> mat('z'-'a', vector<bool>('z'-'a'));
    vvii mat('z', vii(0));
    char letter1, letter2;
    while (m--) {
        cin >> letter1 >> letter2;
        letter1 -= 'a';
        letter2 -= 'a';
        mat[letter1].push_back({letter2, 1});
    }
    vvi d;
    FloydWarshall(mat, d);

    string word1, word2;
    while (n--) {
        cin >> word1 >> word2;
        bool trans_ok = true;
        if (word1.size() != word2.size()) {
            cout << "no" << endl;
            continue;
        }
        for (int i = 0; i < word1.size(); ++i) {
            int a = word1[i] - 'a', b = word2[i] - 'a';
            if (a == b || d[a][b] < INF) continue;
            trans_ok = false;
            break;
        }
        cout << (trans_ok ? "yes" : "no") << endl;
    }
    return 0;
}
