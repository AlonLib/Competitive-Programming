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
    int N = 0, T = 0, sum = 0;
    cin >> N >> T;
    vector<bool> spot(T, false);
    vector<pair<int, int>> people;
    while (N--) {
        pair<int, int> ct(0, 0);
        cin >> ct.first >> ct.second;
        people.push_back(ct);
    }
    sort(people.begin(), people.end());

    for (int i = people.size() - 1; i >= 0; --i) {
    	// highest value person to his last possible time spot or before that
        for (int j = people[i].second; j >= 0; --j) {
            if (spot[j] == false) {
                spot[j] = true;
                sum += people[i].first;
                break;
            }
        }
    }
    cout << sum;
    return 0;
}
