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

bool func09_B_cmp(char const &a, char const &b) {
    return (tolower(a) < tolower(b) || (tolower(a) == tolower(b) && a < b));
}

int main() {
    ll n = 0;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        sort(s.begin(), s.end(), func09_B_cmp);
        do {
            cout << s << endl;
        } while (next_permutation(s.begin(), s.end(), func09_B_cmp));
    }
    return 0;
}

