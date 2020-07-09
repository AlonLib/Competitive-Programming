#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cfloat>
#include <climits>

using namespace std;
typedef long long ll;




static inline double calc_time(pair<double, double> const& c, double r, double k) {
    return r/c.first + k/c.second;
}




int main() {
    int t, n;
    while (cin >> t && t != 0) {
        // reading input
        cin >> n;
        vector<pair<double, double>> vec;
        while (--n) {
            pair<double, double> temp;
            cin >> temp.first >> temp.second;
            vec.push_back(temp);
        }
        pair<double, double> winner;
        cin >> winner.first >> winner.second;
        // trenary search on r's range from start to end
        double s = 0, e = t;
        while (s < e && e - s > 1e-4) {
            double mid_s = s + (e - s) / 3;
            double mid_e = e - (e - s) / 3;

            double win_s = calc_time(winner, mid_s, t - mid_s), win_e = calc_time(winner, mid_e, t - mid_e);
            double time_s = DBL_MAX, time_e = DBL_MAX;
            for (auto const& p : vec) {
                double temp_s = calc_time(p, mid_s, t - mid_s), temp_e = calc_time(p, mid_e, t - mid_e);
                if (temp_s < time_s) time_s = temp_s;
                if (temp_e < time_e) time_e = temp_e;
            }

            if (time_s - win_s > time_e - win_e)
                e = mid_e;
            else
                s = mid_s;
        }
        // calc the result and print
        double r = s, k = t - s;
        double best_temp = DBL_MAX, win_time = calc_time(winner, r, k);
        for (auto const& p : vec) {
            double temp = calc_time(p, r, k);
            if (temp < best_temp) best_temp = temp;
        }
        double diff = best_temp - win_time;


        if (diff >= 0) {
            std::cout << std::setprecision(2) << std::fixed;
            cout << "The cheater can win by " << (int)std::round(diff * 3600) << " seconds with r = " << r << "km and k = " << k << "km." << endl;
        } else {
            cout << "The cheater cannot win." << endl;
        }
    }
    return 0;
}
