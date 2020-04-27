#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;

int main() // E
{
    ll N = 0;
    while (!cin.eof() && cin >> N && N != 0) {
        ll res = 0;
        vector<int> vec;
        while (N--) {
            ll temp = 0;
            cin >> temp;
            vec.push_back(temp);
        }
        priority_queue<ll, vector<ll>, greater<ll> > min_heap(vec.begin(),vec.end());
        while (!min_heap.empty()) {
            ll a = min_heap.top();
            min_heap.pop();
            if (min_heap.empty()) {
                break;
            }
            ll b = min_heap.top();
            min_heap.pop();
            res += a+b;
            min_heap.push(a+b);
        }
        cout << res << endl;
    }
    return 0;
}
