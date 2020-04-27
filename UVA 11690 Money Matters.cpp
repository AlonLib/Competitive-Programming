#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
typedef long long ll;

#include <iostream>
#include <vector>
using namespace std;

struct unionfind
{
    vector<int> rank;
    vector<int> parent;
    unionfind(int size)
    {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++)
            parent[i]=i;
    }

    int find(int x){
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x)//for log*, not needed most of the time
        {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }
    void Union(int p, int q){
        p = find(p);
        q = find(q);
        if(q==p)
        {
            //alredy in the same group
            return;
        }
        if(rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if(rank[p] == rank[q]) rank[p]++;
    }
};

int main() {
    ll N, M;
    cin >> N;
    cin >> M;
    vector<ll> each;
    for (ll i = 0; i < N ; i++) {
        int temp = 0;
        cin >> temp;
        each.push_back(temp);
    }
    unionfind uf(N);
    while (M--) {
        int a, b;
        cin >> a; cin >> b;
        int _a = uf.find(a);
        int _b = uf.find(b);
        uf.Union(a, b);
        int _c = uf.find(a);
        if (_a == _c && _b != _c) {
            each[_c] += each[_b];
        } else if (_a != _c && _b == _c) {
            each[_c] += each[_a];
        }
    }
    for (ll i = 0; i < N ; i++) {
        if (each[uf.find(i)] != 0) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    cout << "POSSIBLE" << endl;
    return 0;
}
