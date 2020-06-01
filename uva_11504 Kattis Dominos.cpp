#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
typedef long long ll;
#include <algorithm>
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


void rec_fell(vvi& mat, vector<bool>& fell, int n) {
    if (fell[n]) return;
    fell[n] = true;
    for (int v : mat[n]) {
        if (!fell[v]) rec_fell(mat, fell, v);
    }
}

// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: is g a DAG (return value), a topological ordering of g (order).
// comment: order is valid only if g is a DAG.
// time: O(V+E).
bool topological_sort(const vvi& g, vi& order) {
    // compute indegree of all nodes
    vi indegree (g.size(), 0);
    for (int v=0; v<g.size(); v++) for (int u : g[v]) indegree[u]++;
    // order sources first
    order = vector<int>();
    for (int v=0; v<g.size(); v++) if (indegree[v] == 0) order.push_back(v);
    // go over the ordered nodes and remove outgoing edges,
    // add new sources to the ordering
    for (int i=0; i<order.size(); i++) for (int u : g[order[i]]) {
            indegree[u]--;
            if (indegree[u]==0) order.push_back(u);
        }
    return order.size()==g.size();
}

/********** Strongly Connected Components **********/


const int UNSEEN = -1;
const int SEEN = 1;

void KosarajuDFS(const vvi& g, int u, vi& S, vi& colorMap, int color) {
    // DFS on digraph g from node u:
    // visit a node only if it is mapped to the color UNSEEN,
    // Mark all visited nodes in the color map using the given color.
    // input: digraph (g), node (v), mapping:node->color (colorMap), color (color).
    // output: DFS post-order (S), node coloring (colorMap).
    colorMap[u] = color;
    for (auto& v : g[u])
        if (colorMap[v] == UNSEEN)
            KosarajuDFS(g, v, S, colorMap, color);
    S.push_back(u);
}

// Compute the number of SCCs and maps nodes to their corresponding SCCs.
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: the number of SCCs (return value), a mapping from node to SCC color (components).
// time: O(V+E).
int findSCC(const vvi& g, vi& components) {
    // first pass: record the `post-order' of original graph
    vi postOrder, seen;
    seen.assign(g.size(), UNSEEN);
    for (int i = 0; i < g.size(); ++i)
        if (seen[i] == UNSEEN)
            KosarajuDFS(g, i, postOrder, seen, SEEN);
    // second pass: explore the SCCs based on first pass result
    vvi reverse_g(g.size(),vi());
    for (int u=0; u<g.size(); u++) for (int v : g[u]) reverse_g[v].push_back(u);
    vi dummy;
    components.assign(g.size(), UNSEEN);
    int numSCC = 0;
    for (int i = (int)g.size()-1; i >= 0; --i)
        if (components[postOrder[i]] == UNSEEN)
            KosarajuDFS(reverse_g, postOrder[i], dummy, components, numSCC++);
    return numSCC;
}

// Computes the SCC graph of a given digraph.
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: strongly connected components graph of g (sccg).
// time: O(V+E).
void findSCCgraph(const vvi& g, vsi& sccg) {
    vi component;
    int n = findSCC(g, component);
    sccg.assign(n, si());
    for (int u=0; u<g.size(); u++) for (int v: g[u]) // for every edge u->v
            if (component[u] != component[v])
                sccg[component[u]].insert(component[v]);
}

int main() {
    int cases;
    cin >> cases;
    while (cases--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n, vector<int>(0));

        while (m--) {
            int a, b;
            cin >> a >> b;

            g[a-1].push_back(b-1);
        }
        vi comp;
        int num_comp = findSCC(g, comp);

        vector<vector<int>> g_scc(num_comp, vector<int>(0));
        vector<bool> is_root(num_comp, true);
        for (int i = 0; i < n; ++i) {
            for (int v : g[i]) {
                is_root[comp[v]] = false;
                g_scc[comp[i]].push_back(comp[v]);
            }
        }
        int res = 0;
        vector<bool> fell(num_comp, false);
        for (int i = 0; i < num_comp; i++) {
            if (!is_root[i]) continue;
            res++;
            rec_fell(g_scc, fell, i);
        }
        for (int i = 0; i < num_comp; ++i) {
            if (!fell[i]) {
                rec_fell(g_scc, fell, i);
                res++;
            }
        }

        cout << res << endl;
    }
    return 0;
}
