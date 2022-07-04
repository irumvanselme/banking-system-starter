#include "./service.cpp"

class AccountService : Service
{
public:
    AccountService() : Service("accounts.txt") {}

    void store(Account account)
    {
        fstream file;
        file.open(get_file_path(), ios::app | ios::out);

        file << next_id() << "," << account.name << "," << account.amount << "," << account.registered_on_branch_id << "\n";
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

    void update(int id, Account account)
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
                file << account.id << "," << account.name << "," << account.amount << "\n";
            }
            else
            {
                file << line << "\n";
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