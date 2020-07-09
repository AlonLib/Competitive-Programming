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
#include <queue>

using namespace std;
typedef long long ll;

ll pow_mod_n(ll a, ll q, ll n) {
    ll res = 1;
    while (q) {
        if (q % 2) res = (res * a) % n;
        a = (a * a) % n;
        q >>= 1;
    }
    return res;
}

bool isPrime(ll p) {
    if (p == 1 || p == 4)
        return false;
    if (p == 2 || p == 3)
        return true;
    ll m = p - 1;
    int k = 0;
    while (m % 2 == 0) {
        m >>= 1;
        k += 1;
    }
    /* !!! Deterministic version for n<2^64 !!! */
    int dtrm_set[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ll cur: dtrm_set) {
        if (cur >= p) break;
        ll b = pow_mod_n(cur, m, p);
        if (b == 1) continue;
        int i = k;
        while (i-- && b != p - 1) {
            b = (b * b) % p; // calc b_next
            if (b == 1) return false;
        }
        if (i == -1) return false;
    }
    return true;
}

int main() {
    int p, a;
    while (cin >> p >> a && p != 0 && a != 0) {
        if (isPrime(p)) {
            cout << "no" << endl;
            continue;
        }
        if (pow_mod_n(a, p, p) == a)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}
