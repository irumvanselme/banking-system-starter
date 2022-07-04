#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    time_t now = time(0);

    cout << ctime(&now) << endl;

    return 0;
}