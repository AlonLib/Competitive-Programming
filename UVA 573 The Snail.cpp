#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;


int main()
{
    float H, U, D, F;
    std::cin >> H;
    while (H)
    {
        std::cin >> U;
        std::cin >> D;
        std::cin >> F;
        int day = 1;
        float current_height = 0, loss = U*(F/100);
        while (true) {
            current_height += U; // climb
            if (current_height > H) {
                cout << "success on day " << day << std::endl;
                break; // OK
            }
            current_height -= D; // slide
            if (current_height < 0) {
                cout << "failure on day " << day << std::endl;
                break; // FAIL
            }
            U = (U - loss >= 0) ? U - loss : 0;
            day++;
        }
        std::cin >> H;
    }
    return 0;
}
