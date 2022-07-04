#include "./service.cpp"

class TransactionsService : Service
{
public:
    TransactionsService() : Service("transactions.txt") {}

    void store(Transaction transaction)
    {
        fstream file;
        file.open(get_file_path(), ios::app | ios::out);

        file << next_id() << "," << transaction.account_id << "," << transaction.receiver_id << "," << transaction.amount << "," << transaction.branch_id << "," << transaction.date << "," << transaction.type << "," << transaction.description << "\n";

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
            transaction.receiver_id = stoi(fields[2]);

            transaction.amount = stod(fields[3]);
            transaction.branch_id = stoi(fields[4]);
            transaction.date = stol(fields[5]);
            transaction.type = fields[6];
            transaction.description = fields[7];

            transactions.push_back(transaction);
        }

        file.close();

        return transactions;
    }

    vector<Transaction> find_by_date(int date)
    {
        vector<Transaction> transactions = get_all();
        vector<Transaction> filtered_transactions;

        for (Transaction transaction : transactions)
        {
            tm *time = localtime(&transaction.date);
            int day = time->tm_mday;

            if (day == date)
            {
                filtered_transactions.push_back(transaction);
            }
        }

        return filtered_transactions;
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
                file << transactions[i].id << "," << transactions[i].account_id << "," << transactions[i].receiver_id << "," << transactions[i].amount << "," << transactions[i].branch_id << "," << transactions[i].date << "," << transactions[i].type << "," << transactions[i].description << "\n";
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
            file << updated_transactions[i].id << "," << updated_transactions[i].account_id << "," << updated_transactions[i].receiver_id << "," << updated_transactions[i].amount << "," << updated_transactions[i].branch_id << "," << updated_transactions[i].date << "," << updated_transactions[i].type << "," << updated_transactions[i].description << "\n";
        }

        file.close();
    }
};