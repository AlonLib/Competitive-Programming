//
// Created by Alon on 30/06/2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;

#define MAX_FOR_H 1000001

int BIT[MAX_FOR_H] = {0}, n;
void update(int x, int val) { for (; x <= n; x += x & -x) BIT[x] += val; }
int query(int x) {
    int sum = 0;
    for (; x > 0; x -= x & -x) sum += BIT[x];
    return sum;
}
int main() {
    int K;
    cin >> n >> K;
    while (K--) {
        char c;
        cin >> c;
        if (c == 'F') {
            int num;
            cin >> num;
            int c = (query(num) - query(num-1) == 1) ? -1 : 1;
            update(num, c);
        } else { // case C
            int start, end;
            cin >> start >> end;
            cout << query(end) - query(start-1) << endl;
        }
    }

    return 0;
}