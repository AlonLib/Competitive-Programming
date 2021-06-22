//
// Created by Alon on 01/08/2020.
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
#include <bitset>

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


#define MODULO 1000000007
vector<bool> BASE_PERMUTATION = {false, false, false, true, true, true, true};
vector<vector<ll>> mul(vector<vector<ll>>& a, vector<vector<ll>>& b) {
    vector<vector<ll>> res(a.size(), vector<ll>(a.size(), 0));

    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a.size(); j++)
            for (int k = 0; k < a.size(); k++) {
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= MODULO;
            }
    return res;
}

vector<vector<ll>> fast_pow(vector<vector<ll>>& a, long n) {
    vector<vector<ll>> res(35, vector<ll>(35, false));
    for (int i = 0; i < 35; ++i) res[i][i] = true; // I
    while (n > 0) {
        if (n % 2 == 0) {
            a = mul(a, a);
            n /= 2;
        } else {
            res = mul(res, a);
            n--;
        }
    }
    return res;
}

int getIndexFromInput() {
    vector<bool> vec(7, false);
    for (int i = 0; i < 7; ++i) {
        int temp;
        cin >> temp;
        if (temp) vec[i] = true;
    }
    vector<bool> p(BASE_PERMUTATION);
    int index = 0;
    while (p != vec && next_permutation(p.begin(), p.end())) ++index;
    assert(index < 35);
    return index;
}

vector<bool> getPermutation(int n) {
    assert(n < 35);
    vector<bool> p(BASE_PERMUTATION);
    int index = 0;
    while (index < n && next_permutation(p.begin(), p.end())) ++index;
    assert(index < 35);
    return p;
}

bool validMove(int a, int b) {
    vector<bool> va = getPermutation(a);
    vector<bool> vb = getPermutation(b);
    for (int i = 0; i < va.size(); ++i) {
        if (!va[i]) continue;
        if (i > 0 && vb[i-1]) {
            vb[i-1] = false; // mark occupied
            continue;
        }
        if (i < 6 && vb[i+1]) {
            vb[i+1] = false; // mark occupied
            continue;
        }
        return false; // player at i from va cannot move to vb
    }
    return true; // valid move
}


int main() {
    int T;
    cin >> T;
    vector<vector<ll>> matrix(35, vector<ll>(35, 0));

    for (int i = 0; i < 35; ++i) {
        for (int j = 0; j < 35; ++j) {
            matrix[i][j] = validMove(i, j);
        }
    }

    while (T--) {
        long long n;
        cin >> n;

        // fast exp matrix n-1 with pow
        vector<vector<ll>> a(matrix);
        vector<vector<ll>> res_matrix = fast_pow(a, n - 1);

        int permutation_index = getIndexFromInput();

        ll res_sum = 0;
        for(int i = 0; i < 35; ++i){
            res_sum += (res_matrix[permutation_index][i] % MODULO);
            res_sum %= MODULO;
        }

        cout << res_sum << endl;
    }
}
