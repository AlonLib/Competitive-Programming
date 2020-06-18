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
    map<string, string> dict;
    string word;
    cin >> word;
    while (word != "#") {
        string sorted(word);
        transform(sorted.begin(), sorted.end(), sorted.begin(), ::tolower);
        sort(sorted.begin(), sorted.end());
        if (dict.find(sorted) == dict.end()) {
            dict[sorted] = string(word); // new
        } else {
            dict[sorted] = "#"; // exist
        }
        cin >> word;
    }
    vector<string> vec;
    for (auto const& x : dict) {
        if (x.second != "#") vec.push_back(x.second);
    }
    sort(vec.begin(), vec.end());
    for (string const& w : vec) {
        cout << w << endl;
    }
    return 0;
}

