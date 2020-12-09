//
// Created by Alon on 02/06/2020.
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

using namespace std;
typedef long long ll;


int main() {
    int n, new_c;
    cin >> n;
    assert(n > 1);
    vector<int> coins(n);
    for (int i = n-1; i >= 0; --i) cin >> coins[i]; // sorted from big to small
    vector<int> num_of_coins(coins[0] + coins[1], INT_MAX);
    /// real minimum
    for (int c = 0; c < n; ++c) {
        int coin = coins[c];
        num_of_coins[coin] = 1;
        for (int i = 0; i + coin < num_of_coins.size(); ++i) {
            if (num_of_coins[i+coin] > num_of_coins[i]) {
                num_of_coins[i+coin] = num_of_coins[i] + 1;
            }
        }
    }
    /// greedy search
    for (int i = 1; i < num_of_coins.size(); ++i) {
        int temp = i, num = 0;
        for (int coin : coins) {
            num += floor(temp / coin);
            temp %= coin;
        }
        if (num_of_coins[i] < num) {
            cout << "non-canonical" << endl;
            return 0;
        }

    }
    cout << "canonical" << endl;
    return 0;
}

