#include "./models.cpp"
#include "./application.cpp"
/**
 * @brief
 * I am going to make a simple banking management system.
 * its main featuers will be as simple as possible.
 * 1. Registration of a new account. record also the branch it was registered in.
 * 2. Reistration of a branch
 * 3. Depositing of money.
 * 4. Withdraw of money
 * 5. Transfer of money.
 *
 * @return int
 */

int main()
{
	Application application;
	application.run();
	return 0;
}
