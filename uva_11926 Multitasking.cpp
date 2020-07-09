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


int main() {
    // 11:15
    int n = 0, m = 0;
    while (cin >> n) {
        cin >> m;
        if (n == 0 && m == 0) break;
        vector<pair<int, int>> vec;
        while (n--) {
            int l, r;
            cin >> l >> r;
            vec.emplace_back(pair<int, int> (l, r));
        }
        while (m--) {
            int l, r, interval;
            cin >> l >> r >> interval;
            while (r <= 2000000) { // duplicate event as much as neeeded
                vec.emplace_back(pair<int, int> (l, r));
                l += interval;
                r += interval;
            }
        }
        sort(vec.begin(), vec.end());
        bool conflict = false;
        for (int i = 0; i + 1 < vec.size(); i++) {
            if (vec[i].second > vec[i + 1].first) {
                conflict = true;
                break;
            }
            if (vec[i].first > 1000000) break;
        }
        cout << (conflict ? "CONFLICT" : "NO CONFLICT") << endl;
    }
    return 0;
}
