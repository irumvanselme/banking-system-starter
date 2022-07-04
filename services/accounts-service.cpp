#include "./service.cpp"

class AccountService : Service
{
public:
    AccountService() : Service("accounts.txt") {}

    int store(Account account)
    {
        int id = next_id();
        fstream file;
        file.open(get_file_path(), ios::app | ios::out);

        file << id << "," << account.name << "," << account.amount << "," << account.registered_on_branch_id << "\n";

        return id;
    }
    vector<Account> get_all()
    {
        vector<Account> accounts;

        fstream file;
        file.open(get_file_path(), ios::in);

        string line;

        while (getline(file, line))
        {
            string field;
            stringstream ss(line);

            vector<string> fields;

            while (getline(ss, field, ','))
                fields.push_back(field);

            Account account;

            account.id = stoi(fields[0]);
            account.name = fields[1];
            account.amount = stod(fields[2]);
            account.registered_on_branch_id = stoi(fields[3]);

            accounts.push_back(account);
        }

        file.close();

        return accounts;
    }

    Account get_by_id(int id)
    {
        vector<Account> accounts = get_all();
        Account account;

        for (int i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].id == id)
            {
                account = accounts[i];
            }
        }

        return account;
    }

    void update(int id, Account accountInfo)
    {
        fstream file;
        vector<Account> accounts = get_all();

        file.open(get_file_path(), ios::out);

        for (Account account : accounts)
        {
            if (account.id == id)
            {
                file << id << "," << accountInfo.name << "," << accountInfo.amount << "," << accountInfo.registered_on_branch_id << "\n";
            }
            else
            {
                file << account.id << "," << account.name << "," << account.amount << "," << account.registered_on_branch_id << "\n";
            }
        }

        file.close();
    }

    void delete_by_id(int id)
    {
        fstream file;
        file.open(get_file_path(), ios::in | ios::out);
        string line;
        while (getline(file, line))
        {
            string field;
            stringstream ss(line);
            vector<string> fields;
            while (getline(ss, field, ','))
                fields.push_back(field);
            if (stoi(fields[0]) == id)
            {
                continue;
            }
            else
            {
                file << line << "\n";
            }
        }
        file.close();
    }
};