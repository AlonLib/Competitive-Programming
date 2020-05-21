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



ll rec(int const location, int const last_jump, vector<int> const& cost, vector<vector<ll>> &memo) {
    if (location == cost.size() - 1) return cost[location]; // end
    if (location < 0 || location >= cost.size()) return INTMAX_MAX; // impossible location
    if (memo[last_jump][location] < INTMAX_MAX) return memo[last_jump][location]; // if the location has already been checked before
    ll a = rec(location + last_jump + 1, last_jump + 1, cost, memo); // step forward
    if (last_jump == 0) return a + cost[location]; // edge case: initial step only
    ll b = rec(location - last_jump, last_jump, cost, memo); // step backwards
    memo[last_jump][location] = min(a,b) + cost[location]; // save location answer
    return min(a,b) + cost[location];
}

int main() {
    int N;
    cin >> N;
    vector<int> cost(N, 0);
    std::vector<std::vector<ll>> memo; // memory matrix to prevent repeating calc (steps X location)
    memo.resize(N + 1, vector<ll>(N + 1, INTMAX_MAX));
    for (int i = 0; i < N; ++i) {
        cin >> cost[i];
    }
    cout << (rec(0, 0, cost, memo) - cost[0]) << endl;
    return 0;
}
