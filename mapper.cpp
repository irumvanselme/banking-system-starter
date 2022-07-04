#include "./models.h"

class Mapper
{
public:
    template <typename T>
    static T input(string label)
    {
        T account_number;
        cout << label << "\n>";
        cin >> account_number;
        return account_number;
    }

    static Branch get_branch_dto()
    {
        Branch branch;

        cout << "Enter branch name: ";
        getline(cin, branch.name);

        return branch;
    }

    static Account get_account_info(int branch_id)
    {
        Account account;

        cout << "Full names:";

        cin.ignore();
        getline(cin, account.name);

        account.registered_on_branch_id = branch_id;
        account.amount = 0;

        return account;
    }
};