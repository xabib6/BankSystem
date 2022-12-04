#pragma once
#include <iostream>
#include <string>
using namespace std;
class AbstractClient
{
protected:
    float _moneyAmount;
public:
    int ID;
    string State;
    void PutMoney(float money)
    {
        _moneyAmount += money;
    }

    bool TakeMoney(float money)
    {
        if (_moneyAmount < money)
        {
            return false;
        }
        _moneyAmount -= money;
        return true;
    }

    void ShowBalance()
    {
        cout << "������� ������ �� �����: " << _moneyAmount << endl;
    }

    bool SendMoney(AbstractClient* other, float money, int percent)
    {
        if (TakeMoney(money + money/100 * percent))
        {
            other->PutMoney(money);
            cout << "������ ������� ����������." << endl;
            return true;
        }
        else
        {
            cout << "������������ ������� �� �����. �������� �� ���������." << endl;
            return false;
        }
    }
    AbstractClient(int id, float moneyAmount)
    {
        ID = id;
        _moneyAmount = moneyAmount;
    }

    void ShowClientInfo()
    {
        cout << "ID �������: " << ID << endl;
        if (State == "Entity")
            cout << "����������� ����. " << endl;
        else
            cout << "���������� ����. " << endl;
        cout << "������� ������: " << _moneyAmount << endl;
    }
};

class IndividualClient : public AbstractClient
{
public:
    IndividualClient(int id, float moneyAmount) : AbstractClient(id, moneyAmount)
    {
        State = "Individual";
    };
};

class EntityClient : public AbstractClient
{
public:
    EntityClient(int id, float moneyAmount) : AbstractClient(id, moneyAmount)
    {
        State = "Entity";
    };
};
