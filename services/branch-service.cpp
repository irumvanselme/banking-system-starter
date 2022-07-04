#include "./service.cpp"

class BranchService : Service
{
public:
    BranchService() : Service("branches.txt") {}

    void store(Branch branch)
    {
        fstream file;
        file.open(get_file_path(), ios::app | ios::out);

        file << next_id() << "," << branch.name << "\n";

        file.close();
    }

    vector<Branch> get_all()
    {
        vector<Branch> branches;

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

            Branch branch;

            branch.id = stoi(fields[0]);
            branch.name = fields[1];

            branches.push_back(branch);
        }

        file.close();

        return branches;
    }

    Branch find_by_id(int id)
    {
        vector<Branch> branches = get_all();
        Branch branch{-1, ""};

        for (int i = 0; i < branches.size(); i++)
        {
            if (branches[i].id == id)
            {
                branch = branches[i];
            }
        }

        return branch;
    }

    void update(int id, Branch branch)
    {
        fstream file;
        file.open(get_file_path(), ios::in);
        string line;
        vector<string> lines;
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
        file.open(get_file_path(), ios::out);
        for (int i = 0; i < lines.size(); i++)
        {
            if (stoi(lines[i].substr(0, lines[i].find(','))) == id)
            {
                file << id << "," << branch.name << "\n";
            }
            else
            {
                file << lines[i] << "\n";
            }
        }
        file.close();
    }

    void delete_by_id(int id)
    {
        fstream file;
        file.open(get_file_path(), ios::in);
        string line;
        vector<string> lines;
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
        file.open(get_file_path(), ios::out);
        for (int i = 0; i < lines.size(); i++)
        {
            if (stoi(lines[i].substr(0, lines[i].find(','))) != id)
            {
                file << lines[i] << "\n";
            }
        }
        file.close();
    }
};