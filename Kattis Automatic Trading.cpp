//
// Created by Alon on 29/05/2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;



int main() { // automatictrading
    string s;
    cin >> s;
    int q, a, b, res;
    cin >> q;
    while (q--) {
        cin >> a >> b;
        res = 0;
        while (b+res < s.size() && s[a+res] == s[b+res]) ++res;
        cout << res << endl;
    }
    return 0;
}
