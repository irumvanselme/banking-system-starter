#include "./service.cpp"

class TransactionsService : Service
{
public:
    TransactionsService() : Service("transactions.txt") {}

    void store(Transaction transaction)
    {
        fstream file;
        file.open(get_file_path(), ios::app | ios::out);

        file << next_id() << "," << transaction.account_id << "," << transaction.amount << "," << transaction.type << "," << transaction.description << "," << transaction.date << "\n";

        file.close();
    }

    vector<Transaction> get_all()
    {
        vector<Transaction> transactions;

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

            Transaction transaction;

            transaction.id = stoi(fields[0]);
            transaction.account_id = stoi(fields[1]);
            transaction.amount = stod(fields[2]);
            transaction.type = fields[3];
            transaction.description = fields[4];
            transaction.date = fields[5];

            transactions.push_back(transaction);
        }

        file.close();

        return transactions;
    }

    Transaction get_by_id(int id)
    {
        vector<Transaction> transactions = get_all();
        Transaction transaction;

        for (int i = 0; i < transactions.size(); i++)
        {
            if (transactions[i].id == id)
            {
                transaction = transactions[i];
                break;
            }
        }

        return transaction;
    }

    void update(Transaction transaction)
    {
        vector<Transaction> transactions = get_all();
        Transaction updated_transaction;
        bool found = false;
        for (int i = 0; i < transactions.size(); i++)
        {
            if (transactions[i].id == transaction.id)
            {
                transactions[i] = transaction;
                found = true;
                break;
            }
        }
        if (found)
        {
            fstream file;
            file.open(get_file_path(), ios::out);
            for (int i = 0; i < transactions.size(); i++)
            {
                file << transactions[i].id << "," << transactions[i].account_id << "," << transactions[i].amount << "\n";
            }

            file.close();
        }
    }

    void delete_by_id(int id)
    {
        vector<Transaction> transactions = get_all();
        vector<Transaction> updated_transactions;
        for (int i = 0; i < transactions.size(); i++)
        {
            if (transactions[i].id != id)
            {
                updated_transactions.push_back(transactions[i]);
            }
        }
        fstream file;
        file.open(get_file_path(), ios::out);
        for (int i = 0; i < updated_transactions.size(); i++)
        {
            file << updated_transactions[i].id << "," << updated_transactions[i].account_id << "," << updated_transactions[i].amount << "\n";
        }

        file.close();
    }
};