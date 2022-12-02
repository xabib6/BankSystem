#pragma once
#include "Bank.h"
#include "CentralBank.h"
void Bank::AddClient()
{
    char input = ' ';
    while (input != '1' && input != '2')
    {
        cout << "�������� ��� �������. \n1)���������� ����. \n2)����������� ����. " << endl;
        cin >> input;
        if (input != '1' && input != '2')
            cout << "������ �����. ���������� �����. " << endl;
    }
    AbstractClient* newClient;
    if (input == '1')
        newClient = new IndividualClient(_nextClientID, 0);
    else if (input == '2')
        newClient = new EntityClient(_nextClientID, 0);
    else return;

    AbstractClient** newClientsList = new AbstractClient * [ClientsCount + 1];

    for (int i = 0; i < ClientsCount; i++)
    {
        newClientsList[i] = _clients[i];
    }
    newClientsList[ClientsCount] = newClient;
    ClientsCount++;
    delete[] _clients;
    _clients = newClientsList;

    _nextClientID++;

}

void Bank::RemoveClient(int chosenClientID)
{
    if (ClientsCount == 0)
    {
        cout << "� ������ ����� ��� ��������." << endl;
        return;
    }
    if (FindClient(chosenClientID) == nullptr)
    {
        cout << "������� � ����� ID �� ����������. " << endl;
        return;
    }

    AbstractClient** newClientsList = new AbstractClient * [ClientsCount - 1];
    int removal = 0;
    for (int i = 0; i < ClientsCount - 1; i++)
    {
        if (i == chosenClientID - 1)
            removal = 1;
        newClientsList[i] = _clients[i + removal];
    }
    ClientsCount--;

    delete[] _clients;
    _clients = newClientsList;
}

void Bank::SendMoney()
{
    Bank* bank = this;

    if (_currentClient->State == "Entity")
    {
        cout << "� ����� ���� ��������� �������? " << endl;
        char input = ' ';
        cout << "1)� ������� ����. \n2)� ������ ����. " << endl;
        while (input != '1' && input != '2')
        {
            cin >> input;
            if (input == '2')
            {
                cout << "�������� ���� ����������. " << endl;
                int choosenBank;
                cin >> choosenBank;
                bank = BankSystem::GetInstance()->FindBank(choosenBank);
            }
            if (input != '1' && input != '2')
            {
                cout << "������ �����. ��������� �������." << endl;
            }
        }
    }


    AbstractClient* other = nullptr;
    while (other == nullptr)
    {

        cout << "������� ID �������. " << endl;
        bank->ShowClients();
        int ID;
        cin >> ID;
        other = bank->FindClient(ID);
        if (other == nullptr)
        {
            cout << "������� � ����� ID �� �������. " << endl;
        }
    }

    cout << "������� ����� ��������. " << endl;
    float money;
    cin >> money;

    if (_currentClient->SendMoney(other, money, _transactionPercent))
        _moneyAmount += money / 100 * _transactionPercent;
}

void Bank::PutMoney()
{
    cout << "������� ����� ��� ����������. " << endl;
    float money;
    cin >> money;
    _currentClient->PutMoney(money);
    cout << "������ ��������. " << endl;
    _currentClient->ShowBalance();
}

void Bank::ChooseClient(int ID)
{
    if (ClientsCount == 0)
    {
        cout << "� ������ ����� ��� ��������." << endl;
        return;
    }
    _currentClient = FindClient(ID);
    if (_currentClient == nullptr)
    {
        cout << "������ � ����� ID �� ������. ���������� �����." << endl;
    }
}

void Bank::ShowClients()
{
    if (ClientsCount == 0)
    {
        cout << "� ������ ����� ��� ��������." << endl;
        return;
    }
    cout << endl;
    for (int i = 0; i < ClientsCount; i++)
    {
        _clients[i]->ShowClientInfo();
        cout << endl;
    }
}

void Bank::ShowInfo()
{
    cout << "�������� �����: " << Name << ". " << endl;
    cout << "ID �����: " << ID << endl;
    cout << "����� �����: " << _moneyAmount << endl;
    cout << "���������� ��������: " << ClientsCount << endl;
}

void Bank::Serve()
{
    _currentClient->ShowClientInfo();

    char input;
    float money;

    while (true)
    {
        cout << "=========================" << endl;
        cout << "1)�������� ������ �� ����. \n2)����� ������ �� �����. \n3)��������� ������ ������� �������. "
             << "  \n4)������ ������. \n5)��������� ������������." << endl;
        cout << "=========================" << endl;
        cin >> input;
        switch (input)
        {
        case '1':
            cout << "������� ����� ��� ����������: ";
            cin >> money;
            _currentClient->PutMoney(money);
            break;
        case '2':
            cout << "������� ����� ��� ������: ";
            cin >> money;
            if (_currentClient->TakeMoney(money))
                cout << "������ �����. " << endl;
            else
                cout << "������������ ������� �� �����. " << endl;
            break;
        case '3':
            SendMoney();
            break;
        case '4':
            _currentClient->ShowBalance();
            break;
        case '5':
            return;
        default:
            cout << "������ �����. ���������� �����. " << endl;
            continue;
        }
    }
}

AbstractClient* Bank::FindClient(int Id)
{
    for (int i = 0; i < ClientsCount; i++)
    {
        if (_clients[i]->ID == Id)
            return _clients[i];
    }
    return nullptr;
}

void Bank::Manager()
{
    cout << "����� ���������� � " << Name << ". " << endl;

    
    char input;
    int id;
    while (true)
    {
        cout << "=========================" << endl;
        cout << "1)�������� �������� �����. \n2)�������� ������ �������. \n3)������� �������. \n4)������� �������. \n5)����� �� �����. " << endl;
        cout << "=========================" << endl;
        cin >> input;
        switch (input)
        {
        case '1':
            ShowClients();
            break;
        case '2':
            AddClient();
            break;
        case '3':
            cout << "������� ID �������, �������� ������ �������. " << endl;
            cin >> id;
            RemoveClient(id);
            break;
        case '4':
            cout << "������� ID �������, �������� ������ �������. " << endl;
            cin >> id;
            ChooseClient(id);
            Serve();
            break;
        case '5':
            return;
        default:
            cout << "������ �����. ���������� �����. " << endl;
            continue;
        }
    }
}

Bank::Bank(string name, float money, int id, int percent)
{
    Name = name;
    _moneyAmount = money;
    ID = id;
    _transactionPercent = percent;
}
