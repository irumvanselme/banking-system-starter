#include "../models.cpp"
#pragma once

class Service
{
private:
    string data_file;

public:
    Service(string filename) : data_file(filename) {}

    string get_file_path()
    {
        return "./store/" + data_file;
    }

protected:
    long next_id()
    {
        long id = 0;

        fstream file;

        file.open(get_file_path(), ios::in);

        string line;

        while (getline(file, line))
        {
            string field;
            stringstream ss(line);

            getline(ss, field, ',');

            id = stoi(field);
        }

        return id + 1;
    }
};