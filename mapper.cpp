#include "./models.cpp"

class Mapper
{
public:
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