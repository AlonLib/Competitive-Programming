//
// Created by Alon on 23/06/2020.
//

// bachetsgame

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;

bool stan_wins[1000002] = { false }; // limit is only 1048576 bytes!

int main() {
    int n, m;
    stan_wins[0] = false; // Stan always loses if there are no stones at his turn
    while (cin >> n >> m) {
        vector<int> option_set(m, -1);
        for (int& num : option_set) cin >> num;

        for (int i = 0; i <= n; ++i) {
            stan_wins[i] = false;
            for (int const j : option_set) {
                if (i-j >= 0 && !stan_wins[i-j]) {
                    stan_wins[i] = true; // Stan can win with i stones if he removes j stones
                    break;
                }
            }
        }
        cout << (stan_wins[n] ? "Stan" : "Ollie") << " wins" << endl;
    }
    return 0;
}
