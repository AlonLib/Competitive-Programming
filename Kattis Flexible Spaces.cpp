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
    int W, P;
    cin >> W >> P;
    vector<bool> walls(W + 1, false);
    vector<bool> possible(W + 1, false);
    while (P--) { // walls are sorted within the input already
        int temp;
        cin >> temp;
        walls[temp] = true;
    }
    walls[0] = true;
    walls[W] = true;
    // O(n^2) count the walls:
    for (int i = 0; i < walls.size(); ++i) {
        if (!walls[i]) continue;
        for (int j = i + 1; j < walls.size(); ++j) {
            if (walls[j]) possible[j - i] = true;
        }
    }
    for (int k = 0; k < possible.size(); ++k) {
        if (possible[k]) cout << k << " ";
    }
    cout << endl;
    return 0;
}
