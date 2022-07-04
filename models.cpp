#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>

#pragma once

using namespace std;

class Model
{
};

class Branch
{
public:
    int id;
    string name;
};

class Account : Model
{
public:
    int id;
    int registered_on_branch_id;
    string name;
    double amount;
};

class Transaction : Model
{
public:
    int id;
    int account_id;
    int receiver_id;
    double amount;
    int branch_id;
    long int date;
    string type;
    string description;
};
