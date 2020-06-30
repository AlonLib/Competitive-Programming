//
// Created by Alon on 26/05/2020.
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

vector<vector<int>> gallery;
vector<vector<vector<int>>> memo;
enum room_closed {
    NONE=0, R=1, L=2
};

int func08_A_rec(int k, int i, room_closed status) {
    if (k == 0) return 0;
    if (i == -1) return (105 * 205); // max_val_of_room * max_num_of_rooms
    if (memo[k][i][status] > -1) return memo[k][i][status];
    int res = func08_A_rec(k, i - 1, NONE);
    switch (status) {
        case R:
            res = min(res, func08_A_rec(k - 1, i - 1, R) + gallery[i][1]);
            break;
        case L:
            res = min(res, func08_A_rec(k - 1, i - 1, L) + gallery[i][0]);
            break;
        case NONE:
            int case_right = func08_A_rec(k - 1, i - 1, R) + gallery[i][1];
            int case_left = func08_A_rec(k - 1, i - 1, L) + gallery[i][0];
            res = min(res, min(case_right, case_left));
            break;
    }
    return memo[k][i][status] = res;
}

int main() { // narrowartgallery
    int N, K, sum;
    while (cin >> N >> K && N + K > 0) {
        sum = 0;
        gallery = vector<vector<int>>(N, vector<int>(2));
        memo = vector<vector<vector<int>>>(K + 1, vector<vector<int>>(N, vector<int>(3, -1)));
        for (int i = 0; i < N; ++i) {
            cin >> gallery[i][0] >> gallery[i][1];
            sum += gallery[i][0] + gallery[i][1];
        }
        cout << sum - func08_A_rec(K, N - 1, NONE) << endl;
    }

    return 0;
}
