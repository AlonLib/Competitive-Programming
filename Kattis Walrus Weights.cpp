//
// Created by Alon on 02/06/2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;



#define POSSIBLE_SIZE 2001
bool possible[POSSIBLE_SIZE] = { false }; // init to false
int main() {
    int n, cur;
    cin >> n;
    while (n--) {
        cin >> cur;
        for (int i = POSSIBLE_SIZE - cur - 1; i > 0; --i) {
            if (possible[i]) possible[i+cur] = true;
        }
        possible[cur] = true;
    }
    for (int i = 0; i < 1000; ++i) {
        if (possible[1000 + i]) {
            cout << 1000 + i << endl;
            break;
        }
        if (possible[1000 - i]) {
            cout << 1000 - i << endl;
            break;
        }
    }
    return 0;
}

