//
// Created by Alon on 16/06/2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <map>

using namespace std;
typedef long long ll;

#define EMPTY ('-')
#define PEBBLE ('o')

map<string, int> m;
int func11_D_rec(string s) {
    if (m.find(s) != m.end()) return m[s];
    int max_moves = 0;
    for (int i = 0; i < 23; ++i) {
        if (i < 21 && s[i] == PEBBLE && s[i+1] == PEBBLE && s[i+2] == EMPTY) {
            string new_s(s);
            new_s[i] = EMPTY, new_s[i + 1] = EMPTY, new_s[i + 2] = PEBBLE;
            max_moves = max(max_moves, func11_D_rec(new_s) + 1);
        }
        if (1 < i && s[i-2] == EMPTY && s[i-1] == PEBBLE && s[i] == PEBBLE) {
            string new_s(s);
            new_s[i-2] = PEBBLE, new_s[i-1] = EMPTY, new_s[i] = EMPTY;
            max_moves = max(max_moves, func11_D_rec(new_s) + 1);
        }
    }
    return m[s] = max_moves;
}
int main() { // pebblesolitaire2
    int n;
    cin >> n;
    m = map<string, int>(); // one map for all should be fine
    while (n--) {
        string s;
        cin >> s;
        int pebbeles = 0;
//        bitset<23> state;
        for (int i = 0; i < 23; ++i) if (s[i] == 'o') ++pebbeles;
//        m = map<string, int>();
        cout << pebbeles - func11_D_rec(s) << endl;
    }
    return 0;
}

