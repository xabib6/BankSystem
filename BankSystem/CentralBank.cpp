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
        cout << "1)Показать все банки. \n2)Добавить новый банк. \n3)Удалить банк. \n4)Выбрать банк. \n5)Завершить работу. " << endl;
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
            cout << "Введите ID банка, который хотите удалить. " << endl;
            cin >> id;
            RemoveBank(id);
            break;
        case '4':
            cout << "Введите ID банка, который хотите выбрать. " << endl;
            cin >> id;
            ChooseBank(id);
            break;
        case '5':
            return;
        default:
            cout << "Ошибка ввода. Попробуйте снова. " << endl;
            continue;
        }
    }
}

void BankSystem::AddBank()
{
    string name;
    float money;
    int percent;

    cout << "Введите название банка. " << endl;
    cin >> name;
    cout << "Введите сумму денег в банке. " << endl;
    cin >> money;
    cout << "Введите процент за перевод. " << endl;
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
        cout << "В данном банке нет клиентов." << endl;
        return;
    }
    if (FindBank(chosenBankID) == nullptr)
    {
        cout << "Банка с таким ID не существует. " << endl;
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
        cout << "В настоящее время нет доступных банков." << endl;
            return;
    }
    _currentBank = FindBank(chosenBankID);
    if (_currentBank == nullptr)
    {
        cout << "Банка с таким ID не существует. " << endl;
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