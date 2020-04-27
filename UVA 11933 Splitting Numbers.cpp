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

int main()
{
    int N = 0;
    while (cin >> N && N != 0) {
        int checker = 1;
        int a = 0, b = 0;
        bool x = false;
        for (int i = 1; i < 32; i++) {
            if (N & checker) {
                //cout << i << ",";
                if (x) a |= checker;
                else b |= checker;
                x = !x;
            }
            checker <<= 1;
        }
        cout << b << " " << a << endl;
        //b = N ^ a;
    }
    return 0;
}
