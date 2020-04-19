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
    //17:50
    ll W = 0, N = 0, sum = 0;
    while (cin >> W) {
        cin >> N;
        sum = 0;
        //while (!cin.eof()) {
        while (N--) {
            int w, l;
            cin >> w;
            cin >> l;
            sum += w * l;
        }
        cout << sum / W << endl;
    }
    return 0;
}
