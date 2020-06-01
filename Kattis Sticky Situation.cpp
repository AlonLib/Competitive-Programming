#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <chrono>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef long long ll;

int main()
{ /// stickysituation
    ll N, temp;
    cin >> N;
    vector<ll> v;
    while (N--) {
        cin >> temp;
        v.push_back(temp);
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] + v[i + 1] > v[i + 2] && v[i + 1] + v[i + 2] > v[i] && v[i + 2] + v[i] > v[i + 1]) {
            cout << "possible" << endl;
            return 0;
        }
    }
    cout << "impossible" << endl;
    return 0;
}
