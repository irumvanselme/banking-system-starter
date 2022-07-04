#include "./models.h"
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
        time_t now = time(0);
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

    menu:
        cout << "[1] Create a new Account" << endl;
        cout << "[2] Deposit money" << endl;
        cout << "[3] Withdraw money" << endl;
        cout << "[4] Transfer money" << endl;
        cout << "[5] View all transfers" << endl;
        cout << "[6] View all transaction [sorted by balance]" << endl;
        cout << "[-1] Exist the System \n>";
        cin >> choice;

        if (choice == 1)
        {
            int account_number = accountService.store(Mapper::get_account_info(branch_id));
            cout << "Your account number is : " << account_number << endl;
        }
        else if (choice == 2)
        {
            int account_id = Mapper::input<int>("Enter the account number");
            double balance = Mapper::input<double>("Enter the amount to deposit");
            // string description = Mapper::input<string>("Enter the description");

            Account account = accountService.get_by_id(account_id);
            // update the account balance
            account.amount += balance;
            accountService.update(account_id, account);

            // create a new transaction
            Transaction transaction;
            transaction.account_id = account_id;
            transaction.branch_id = branch_id;
            transaction.receiver_id = -1;
            transaction.amount = balance;
            transaction.type = "DEPOSIT";
            transaction.description = "Deposit money";
            transaction.date = now;

            transactionsService.store(transaction);
        }
        else if (choice == 3)
        {
            int account_id = Mapper::input<int>("Enter the account number");
            double balance = Mapper::input<double>("Enter the amount to withdraw");
            // string description = Mapper::input<string>("Enter the description");

            Account account = accountService.get_by_id(account_id);

            if (account.amount < balance)
            {
                cout << "\n\n===== "
                     << "\033[31m"
                     << "You don't have enough money to withdraw"
                     << "\033[0m"
                     << " =====\n\n\n";
                goto branch;
            }

            // update the account balance
            account.amount -= balance;
            accountService.update(account_id, account);

            // create a new transaction
            Transaction transaction;
            transaction.account_id = account_id;
            transaction.receiver_id = -1;
            transaction.branch_id = branch_id;
            transaction.amount = balance;
            transaction.type = "WITHDRAW";
            transaction.description = "Withdraw money";
            transaction.date = now;

            transactionsService.store(transaction);
        }
        else if (choice == 4)
        {
            int sender_id = Mapper::input<int>("Enter the sending account number :");
            int receiver_id = Mapper::input<int>("Enter the receiving account number :");
            double balance = Mapper::input<double>("Enter the amount to send :");

            if (sender_id == receiver_id)
            {
                cout << "\n\n===== "
                     << "\033[31m"
                     << "You can't send money to yourself"
                     << "\033[0m"
                     << " =====\n\n\n";
                goto branch;
            }

            Account sender = accountService.get_by_id(sender_id);
            Account receiver = accountService.get_by_id(receiver_id);

            if (sender.amount < balance)
            {
                cout << "\n\n===== "
                     << "\033[31m"
                     << "You don't have enough money to send"
                     << "\033[0m"
                     << " =====\n\n\n";
                goto branch;
            }

            // update the account balance
            sender.amount -= balance;
            accountService.update(sender_id, sender);
            receiver.amount += balance;
            accountService.update(receiver_id, receiver);

            // create a new transaction
            Transaction transaction;
            transaction.account_id = sender_id;
            transaction.receiver_id = receiver_id;
            transaction.branch_id = branch_id;
            transaction.amount = balance;
            transaction.type = "TRANSFER";
            transaction.description = "Transfer money";
            transaction.date = now;

            transactionsService.store(transaction);
        }
        else if (choice == 5)
        {

            int date = 4;

            vector<Transaction> transactions = transactionsService.find_by_date(date);

            cout << setw(20) << "Account" << setw(20) << "Receiver" << setw(20) << "Branch" << setw(10) << "Amount" << setw(10) << "Type" << setw(20) << "Description" << setw(45) << "Date " << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";

            for (Transaction transaction : transactions)
            {
                cout << setw(20) << accountService.get_by_id(transaction.account_id).name << setw(20) << accountService.get_by_id(transaction.receiver_id).name << setw(20) << branchService.find_by_id(transaction.branch_id).name << setw(10) << transaction.amount << setw(10) << transaction.type << setw(20) << transaction.description << setw(45) << ctime(&transaction.date);
            }
        }
        else if (choice == 6)
        {
            cout << "Tring to print the accounts in a sorted manner" << endl;

            vector<Account> accounts = accountService.get_all();

            for (int i = 0; i < accounts.size(); i++)
            {
                for (int j = i + 1; j < accounts.size(); j++)
                {
                    if (accounts[i].amount < accounts[j].amount)
                    {
                        Account temp = accounts[i];
                        accounts[i] = accounts[j];
                        accounts[j] = temp;
                    }
                }
            }

            cout << setw(20) << "Account number" << setw(20) << "Full names" << setw(20) << "Balance" << setw(20) << "Registered on Branch" << endl;
            for (Account account : accounts)
            {
                cout << setw(20) << account.id << setw(20) << account.name << setw(20) << account.amount << setw(20) << branchService.find_by_id(account.registered_on_branch_id).name << endl;
            }
        }
        else if (choice == -1)
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
        int k = 1 / 2;

        goto menu;
    }

private:
};