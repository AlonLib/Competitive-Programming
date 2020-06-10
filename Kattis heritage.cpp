#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

string KMP_str; // The string to search in
string KMP_pat; // The pattern to search
vi lps;
vvii v;
typedef long long ll;
//ll mulmodn(ll a, ll b, ll n){
//    ll res = 0;
//    while(b){
//        if(b & 1) res= (res+a) %n;
//        a = (a*2)%n;
//        b >>= 1;
//    }
//    return res;
//}

// KMP Init
void KMP_init(){
    int m = KMP_pat.length();
    lps.resize(m+1,0); // m+1 or m
    lps[0]=-1;
    int i = 0, j = -1;
    while (i < m) {
        while (j >= 0 && KMP_pat[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        lps[i] = j;
    }
}

// Search a pattern in a string
// Assuming lps is allready initialized with KMP_init
void KMP_search(int options) {
    int n = KMP_str.length();
    int m = KMP_pat.length();
    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && KMP_str[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        if (j == m) { // Pattern found
            v[i-j].push_back({i-j+m, options});
//            cout << "The pattern " << KMP_pat << " is found at index " << i-j  << "-" << i-j+m << endl;
            j = lps[j];
        }
    }
}

int main() { // Kattis - What Does It Mean? - heritage
    int dict, options;
    cin >> dict;
    cin >> KMP_str;
    v = vvii(KMP_str.size(), vii(0)); // init
    while (dict--) {
        cin >> KMP_pat >> options;
        KMP_init();
        KMP_search(options);
    }
    vector<ll> res(KMP_str.length()+1, 0);
    res[KMP_str.size()] = 1;
    for (int i = KMP_str.length() - 1; i >= 0 ; --i) {
        for (int j = 0; j < v[i].size(); ++j) {
            assert(v[i][j].first <= res.size());
//            res[i] += mulmodn(res[v[i][j].first], v[i][j].second, 1000000007);
            res[i] += (res[v[i][j].first] * v[i][j].second) % 1000000007;
            res[i] %= 1000000007;
        }
    }
    cout << res[0];
    return 0;
}

