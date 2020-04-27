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



int main()
{
    int n;
    while (cin >> n) {
        int max_amount = 0, max = 0, temp;
        map<string, int> m;
        while (n--) {
            vector<int> vec;
            for (int i = 0; i < 5; i++) {
                cin >> temp;
                vec.push_back(temp);
            }
            sort(vec.begin(), vec.end());
            string word;
            for (int i = 0; i < 5; i++) {
                word += to_string(vec[i]);
            }
            m[word]++;
            if (m[word] == max) {
                max_amount++;
            }
            else if (m[word] > max) {
                max = m[word];
                max_amount = 1;
            }
        }
        cout << max * max_amount << endl;
    }
    return 0;
}
