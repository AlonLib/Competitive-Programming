//
// Created by Alon on 02/06/2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <cassert>

using namespace std;
typedef long long ll;

enum edge {END = 0, START = 1};
struct pillar {
    int y, x1, x2;
};

int main() {
    int N, res = 0;
    cin >> N;
    vector<pillar> pillars(N); // Y X1 X2
//    vector<pair<int, int>> starts(N); // X1 N
//    vector<pair<int, int>> ends(N); // X2 N
    vector<pair<int, int>> axis; // X2 N
    for (int i = 0; i < N; ++i) {
        cin >> pillars[i].y >> pillars[i].x1 >> pillars[i].x2;
//        starts[i] = {pillars[i].x1, i};
//        ends[i] = {pillars[i].x2, i};
        axis.push_back(make_pair(pillars[i].x1, i)); // start
        axis.push_back(make_pair(pillars[i].x2, i)); // end
    }
//    sort(starts.begin(), starts.end());
//    sort(ends.begin(), ends.end());
    sort(axis.begin(), axis.end());
    set<int> current_heights = { 0 };
    int i = -1;
    while (i + 1 < (int)axis.size()) {
        stack<int> pillar_to_remove;
        vector<int> pillar_to_add;
        do {
            ++i;
            int number_of_pillar = axis[i].second;
            if (axis[i].first == pillars[number_of_pillar].x1) { /// begin pillar
                pillar_to_add.push_back(number_of_pillar);
            } else { /// end pillar
                assert(axis[i].first == pillars[number_of_pillar].x2);
                pillar_to_remove.push(number_of_pillar);
                int len = pillars[number_of_pillar].y - *(--(current_heights.find(pillars[number_of_pillar].y))); // upper_bound is exclusive
                res += len;
            }
        } while (i + 1 < axis.size() && axis[i].first == axis[i+1].first);
        while (!pillar_to_remove.empty()) {
            current_heights.erase(pillars[pillar_to_remove.top()].y);
            pillar_to_remove.pop();
        }
        for (int p : pillar_to_add) current_heights.insert(pillars[p].y);
        for (int p : pillar_to_add) {
            int len = pillars[p].y - *(--(current_heights.find(pillars[p].y))); // upper_bound is exclusive
            res += len;
        }
    }
    cout << res << endl;
    return 0;
}
