//
// Created by Alon on 28/03/2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;
typedef long long ll;


int main() { // orders
    int n, m, s;
    vector<int> memo(30002, -1); // -1 no impossible, -2 ambiguous, i = dish
    cin >> n;
    vector<int> dishes(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> dishes[i];
    }
    memo[0] = 0;
    for (int j = 1; j < dishes.size(); ++j) {
        for (int i = 0; i < memo.size() - dishes[j]; ++i) {
            assert(i + dishes[j] < memo.size());
            if (memo[i] > -1) { // reachable
                if (memo[i + dishes[j]] == -1) { // unreachable
                    memo[i + dishes[j]] = j; // make reachable by mark dish #
                } else memo[i + dishes[j]] = -2; // reachable more than once
            } else if (memo[i] == -2) {
                memo[i + dishes[j]] = -2; // pass on the ambiguous
            }
        }
    }
    cin >> m;
    while (m--) {
        cin >> s;
        switch (memo[s]) {
            case -1:
                cout << "Impossible" << endl;
                break;
            case -2:
                cout << "Ambiguous" << endl;
                break;
            default:
                vector<int> res;
                while (s > 0) {
                    assert(memo[s] > 0);
                    res.push_back(memo[s]); // add dish # to print
                    s -= dishes[memo[s]]; // less dish price
                }
                assert(s == 0);
                for (int i = res.size() - 1; i >= 0; --i) {
                    cout << res[i] << " ";
                }
                cout << endl;
        }
    }
    return 0;
}

