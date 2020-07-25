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
#include <cfloat>
#include <cmath>
#include <iomanip>

using namespace std;
typedef long long ll;


double dist(pair<double, double> p1, pair<double, double> p2) {
    return hypot(p1.first - p2.first, p1.second - p2.second); 
}

/// Closest Pair (Uniform) Kattis - closestpair1
int main() {
    int n;
    while (cin >> n && n) {
        vector<pair<double, double>> axis;
        while (n--) {
            pair<double, double> p;
            cin >> p.first >> p.second;
            axis.push_back(p);
        }
        pair<double, double> p1, p2;
        double d = 100001, i_to_remove = 0;
        sort(axis.begin(), axis.end());
        set<pair<double, double>> ys;
        for (int i = 0; i < axis.size(); ++i) {
            pair<double, double> main_p = axis[i];
            auto it = ys.lower_bound({main_p.second - d, -100001});
            while (it != ys.end() && (*it).first <= main_p.second + d) {
                pair<double, double> temp_p = {(*it).second, (*it).first}; // x,y
                double temp_d = dist(main_p, temp_p);
                if (temp_d < d) {
                    d = temp_d;
                    p1 = temp_p;
                    p2 = main_p;
                }
                it++;
            }
            while (i_to_remove < i && axis[i_to_remove].first < axis[i].first - d) {
                pair<double, double> temp_p = {axis[i_to_remove].second, axis[i_to_remove].first};
                ys.erase(temp_p);
                ++i_to_remove;
            }
            ys.insert(make_pair(main_p.second, main_p.first));
        }
        cout << fixed << setprecision(2)<< p1.first << " " << p1.second << " " << p2.first << " " << p2.second << endl;
    }

    return 0;
}