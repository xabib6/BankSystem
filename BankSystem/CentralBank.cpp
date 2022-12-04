#pragma once
#include "CentralBank.h"

BankSystem* BankSystem::GetInstance()
{
    if (Instance == nullptr)
    {
        Instance = new BankSystem;
    }
    return Instance;
}

void BankSystem::Manager()
{
    
    char input;
    int id;
    while (true)
    {
        cout << "=========================" << endl;
        cout << "1)�������� ��� �����. \n2)�������� ����� ����. \n3)������� ����. \n4)������� ����. \n5)��������� ������. " << endl;
        cout << "=========================" << endl;
        cin >> input;
        switch (input)
        {
        case '1':
            ShowBanks();
            break;
        case '2':
            AddBank();
            break;
        case '3':
            cout << "������� ID �����, ������� ������ �������. " << endl;
            cin >> id;
            RemoveBank(id);
            break;
        case '4':
            cout << "������� ID �����, ������� ������ �������. " << endl;
            cin >> id;
            ChooseBank(id);
            break;
        case '5':
            return;
        default:
            cout << "������ �����. ���������� �����. " << endl;
            continue;
        }
    }
}

void BankSystem::AddBank()
{
    string name;
    float money;
    int percent;

    cout << "������� �������� �����. " << endl;
    cin >> name;
    cout << "������� ����� ����� � �����. " << endl;
    cin >> money;
    cout << "������� ������� �� �������. " << endl;
    cin >> percent;

    Bank newBank = Bank(name, money, _nextBankID, percent);

    Bank* newBanksList = new Bank[_banksCount + 1];

    for (int i = 0; i < _banksCount; i++)
    {
        newBanksList[i] = _banks[i];
    }
    newBanksList[_banksCount] = newBank;
    _banksCount++;
    delete[] _banks;
    _banks = newBanksList;

    _nextBankID++;
}

void BankSystem::RemoveBank(int chosenBankID)
{
    if (_banksCount == 0)
    {
        cout << "� ������ ����� ��� ��������." << endl;
        return;
    }
    if (FindBank(chosenBankID) == nullptr)
    {
        cout << "����� � ����� ID �� ����������. " << endl;
        return;
    }

    Bank* newBanksList = new Bank[_banksCount - 1];
    int removal = 0;
    for (int i = 0; i < _banksCount - 1; i++)
    {
        if (i == chosenBankID)
            removal = 1;
        newBanksList[i] = _banks[i + removal];
    }
    _banksCount--;

    delete[] _banks;
    _banks = newBanksList;
}

void BankSystem::ChooseBank(int chosenBankID)
{
    if (_banksCount == 0)
    {
        cout << "� ��������� ����� ��� ��������� ������." << endl;
            return;
    }
    _currentBank = FindBank(chosenBankID);
    if (_currentBank == nullptr)
    {
        cout << "����� � ����� ID �� ����������. " << endl;
        return;
    }
    _currentBank->Manager();
}

Bank* BankSystem::FindBank(int id)
{
    for (int i = 0; i < _banksCount; i++)
    {
        if (_banks[i].ID == id)
            return &_banks[i];
    }
    return nullptr;
}



void BankSystem::ShowBanks()
{
    cout << endl;
    for (int i = 0; i < _banksCount; i++)
    {        
        _banks[i].ShowInfo();
        cout << endl;
    }
}

BankSystem* BankSystem::Instance = nullptr;