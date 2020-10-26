//
// Created by Alon on 16/06/2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <map>
#include <cassert>

using namespace std;
typedef long long ll;

#define MAX_N (101)
#define MODULO (1001113)
vector<vector<int>> memo;
int a = 1001113;
int func11_B_rec(int N, int v) {
    assert(N >= v);
    if (v == 0 || v == N - 1) return 1;
    if (memo[N][v] > 0) return memo[N][v];
    int per = 0;
    /// case first number will be bigger
    per += (N - v) * func11_B_rec(N - 1, v - 1);
    per %= MODULO;
    /// case first number will be smaller
    per += (v + 1) * func11_B_rec(N - 1, v);
    per %= MODULO;
    return memo[N][v] = per;
}

int main() { // permutationdescent
    int P;
    cin >> P;
    memo = vector<vector<int>>(MAX_N, vector<int>(MAX_N, 0)); // memo[N][v]
    while (P--) {
        int K, N, v;
        cin >> K >> N >> v;
        cout << K << " " << func11_B_rec(N, v) << endl;
    }
    return 0;
}
