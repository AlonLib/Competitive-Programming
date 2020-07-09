
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



int main() {
    int T, N, temp;
    cin >> T;
    while (T--) {
        // read
        cin >> N;
        priority_queue<ll, vector<ll>, greater<ll> > heap;
        while (N--) {
            cin >> temp;
            heap.push(temp);
        }
        // calc
        ll sum = 0, a, b;
        while (heap.size() > 1) {
            // sort the canvasses from the last epoch to the first epoch
            a = heap.top();
            heap.pop();
            b = heap.top();
            heap.pop();
            // we want the 2 lightest (smallest) to become one block of canvasses
            sum += a + b;
            heap.push(a + b);
        }
        cout << sum << endl;
    }
    return 0;
}
