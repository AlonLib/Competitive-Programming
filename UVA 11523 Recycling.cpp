//
// Created by Alon on 25/07/2020.
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


vvi memo;

int func93_D_rec(vector<string> &items, int begin, int end) {
    // from (begin) -> (end-1)
    if (begin == end) return 0;
    if (memo[begin][end] >= 0) return memo[begin][end];

    int left = begin + 1; // first element that is different from items[begin]
    while (left < end && items[begin] == items[left]) ++left;

    int best = 1 + func93_D_rec(items, left, end);

    for (int right = left; right < end; ++right) {
        if (items[begin] != items[right]) continue;
        int left_side = func93_D_rec(items, left, right);
        int right_side = func93_D_rec(items, right, end); // first element is still items[begin]
        best = min(best, left_side + right_side);
    }
    return memo[begin][end] = best;
}

int main() {
    int cases, number_of_items;
    cin >> cases;
    for (int i = 1; i <= cases; ++i) {
        int res = 0;
        cin >> number_of_items;

        string line, word;
        getline(cin,line);
        getline(cin,line);
        istringstream ss(line);

        vector<string> items;
        while (number_of_items--) {
            ss >> word;
            if (isupper(word[0])) {
                if (!items.empty()) {
                    memo = vvi(101, vi(101, -1)); // clear
                    res += func93_D_rec(items, 0, items.size());
                    items = vector<string>(); // clear
                }
                continue;
            }
            assert(islower(word[0]));
            items.push_back(word);
        }
        memo = vvi(101, vi(101, -1)); // clear
        if (!items.empty()) res += func93_D_rec(items, 0, items.size());

        cout << "Case " << i << ": " << res << endl;
    }
    return 0;
}
