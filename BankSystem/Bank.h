#pragma once
#include <iostream>
#include <string>
#include "Clients.h"
using namespace std;

class Bank
{
private:
    AbstractClient** _clients;
    int _nextClientID;
    AbstractClient* _currentClient;
    float _moneyAmount;
    int _transactionPercent;

    void AddClient();

    void RemoveClient(int chosenClientID);

    void SendMoney();

    void ChooseClient(int ID);

    void ShowClients();

    void Serve();

    AbstractClient* FindClient(int Id);

public:
    int ID;
    int ClientsCount;
    string Name;   

    void Manager();

    void ShowInfo();
    Bank(string name, float money, int id, int percent);

    Bank() {};
    ~Bank();
};