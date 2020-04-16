#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;


int main()
{
    //std::cout << "Hello World!\n";
    string str;
    getline(cin, str);
    while (str != "DONE")
    {
        int l = 0, r = str.length() - 1;
        while (l <= r) {
            if (str[l] == ',' || str[l] == '.' || str[l] == '!' || str[l] == '?' || str[l] == ' ') {
                l++;
                continue;
            }
            if (str[r] == ',' || str[r] == '.' || str[r] == '!' || str[r] == '?' || str[r] == ' ') {
                r--;
                continue;
            }
            char a = (str[l] > 'Z') ? str[l] - 'a' + 'A' : str[l];
            char b = (str[r] > 'Z') ? str[r] - 'a' + 'A' : str[r];
            if (a != b) break;
            l++;
            r--;
        }
        //std::cout << l << ":" << r << std::endl;
        if (l >= r) std::cout << "You won't be eaten!" << std::endl;
        else std::cout << "Uh oh.." << std::endl;
        getline(cin, str);
    }
    return 0;
}
