#include <iostream>
#include <ctime>
#include <time.h>

using namespace std;

string generate_account_number()
{
    return "No account number";
}

int main()
{
    string account_number = generate_account_number();

    srand(time(NULL));

    cout << rand() % 10 << endl;
    return 0;
}