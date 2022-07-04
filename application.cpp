#include "./models.cpp"
#include "./mapper.cpp"

#include "./services/accounts-service.cpp"
#include "./services/transactions-service.cpp"
#include "./services/branch-service.cpp"

class Application
{
private:
    int branch_id;
    AccountService accountService;
    TransactionsService transactionsService;
    BranchService branchService;

public:
    void run()
    {
    welcome:
        system("clear");
        cout << "Welcome to the Banking System \n\n\n";
    start:
        cout << "Enter the branch Id to continue \n>";

        cin >> branch_id;

        Branch branch = branchService.find_by_id(branch_id);

        if (branch.id == -1)
        {
            cout << "\n\n===== "
                 << "\033[31m"
                 << "Branch with id [" << branch_id << "] not found TRY AGAIN"
                 << "\033[0m"
                 << " =====\n\n\n";
            goto start;
        }

    branch:
        cout << "\033[32m"
             << "Welcome to the bank management of a branch [" << branch.name << "]"
             << "\033[0m \n\n\n"
             << endl;

        int choice = -1;

        cout << "[1] Create a new Account" << endl;
        cout << "[2] Deposit money" << endl;
        cout << "[3] Withdraw money" << endl;
        cout << "[4] Transfer money" << endl;
        cout << "[5] Exist the System \n>";
        cin >> choice;

        if (choice == 1)
            accountService.store(Mapper::get_account_info(branch_id));
        else if (choice == 2)
        {
            // do something
        }
        else if (choice == 3)
        {
            // do something
        }
        else if (choice == 4)
        {
            // do something
        }
        else if (choice == 5)
        {
            cout << "\n\n\n\n\033[31m"
                 << "Thanks for using our system."
                 << "\033[0m" << endl;
        }
        else
        {
            cout << "\n\n\n\n \033[31m"
                 << "Invalid choice. TRY AGAIN"
                 << "\033[0m" << endl;
            goto branch;
        }

        cout << "\n\n\n";
    }

private:
};