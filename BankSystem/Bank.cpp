#pragma once
#include "Bank.h"
#include "CentralBank.h"
void Bank::AddClient()
{
    char input = ' ';
    while (input != '1' && input != '2')
    {
        cout << "Выберите тип клиента. \n1)Физическое лицо. \n2)Юридическое лицо. " << endl;
        cin >> input;
        if (input != '1' && input != '2')
            cout << "Ошибка ввода. Попробуйте снова. " << endl;
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
        cout << "В данном банке нет клиентов." << endl;
        return;
    }
    if (FindClient(chosenClientID) == nullptr)
    {
        cout << "Клиента с таким ID не существует. " << endl;
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
        cout << "В какой банк выполнить перевод? " << endl;
        char input = ' ';
        cout << "1)В текущий банк. \n2)В другой банк. " << endl;
        while (input != '1' && input != '2')
        {
            cin >> input;
            if (input == '2')
            {
                cout << "Выберите банк получателя. " << endl;
                int choosenBank;
                cin >> choosenBank;
                bank = BankSystem::GetInstance()->FindBank(choosenBank);
            }
            if (input != '1' && input != '2')
            {
                cout << "Ошибка ввода. Повторите попытку." << endl;
            }
        }
    }


    AbstractClient* other = nullptr;
    while (other == nullptr)
    {

        cout << "Введите ID клиента. " << endl;
        bank->ShowClients();
        int ID;
        cin >> ID;
        other = bank->FindClient(ID);
        if (other == nullptr)
        {
            cout << "Клиента с таким ID не найдено. " << endl;
        }
    }

    cout << "Введите сумму перевода. " << endl;
    float money;
    cin >> money;

    if (_currentClient->SendMoney(other, money, _transactionPercent))
        _moneyAmount += money / 100 * _transactionPercent;
}

void Bank::PutMoney()
{
    cout << "Введите сумму для пополнения. " << endl;
    float money;
    cin >> money;
    _currentClient->PutMoney(money);
    cout << "Баланс пополнен. " << endl;
    _currentClient->ShowBalance();
}

void Bank::ChooseClient(int ID)
{
    if (ClientsCount == 0)
    {
        cout << "В данном банке нет клиентов." << endl;
        return;
    }
    _currentClient = FindClient(ID);
    if (_currentClient == nullptr)
    {
        cout << "Клиент с таким ID не найден. Попробуйте снова." << endl;
    }
}

void Bank::ShowClients()
{
    if (ClientsCount == 0)
    {
        cout << "В данном банке нет клиентов." << endl;
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
    cout << "Название банка: " << Name << ". " << endl;
    cout << "ID банка: " << ID << endl;
    cout << "Сумма денег: " << _moneyAmount << endl;
    cout << "Количество клиентов: " << ClientsCount << endl;
}

void Bank::Serve()
{
    _currentClient->ShowClientInfo();

    char input;
    float money;

    while (true)
    {
        cout << "=========================" << endl;
        cout << "1)Положить деньги на счёт. \n2)Снять деньги со счёта. \n3)Отправить деньги другому клиенту. "
             << "  \n4)Узнать баланс. \n5)Завершить обслуживание." << endl;
        cout << "=========================" << endl;
        cin >> input;
        switch (input)
        {
        case '1':
            cout << "Введите сумму для пополнения: ";
            cin >> money;
            _currentClient->PutMoney(money);
            break;
        case '2':
            cout << "Введите сумму для снятия: ";
            cin >> money;
            if (_currentClient->TakeMoney(money))
                cout << "Деньги сняты. " << endl;
            else
                cout << "Недостаточно средств на счёте. " << endl;
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
            cout << "Ошибка ввода. Попробуйте снова. " << endl;
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
    cout << "Добро пожаловать в " << Name << ". " << endl;

    
    char input;
    int id;
    while (true)
    {
        cout << "=========================" << endl;
        cout << "1)Показать клиентов банка. \n2)Добавить нового клиента. \n3)Удалить клиента. \n4)Выбрать клиента. \n5)Выйти из банка. " << endl;
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
            cout << "Введите ID клиента, которого хотите удалить. " << endl;
            cin >> id;
            RemoveClient(id);
            break;
        case '4':
            cout << "Введите ID клиента, которого хотите выбрать. " << endl;
            cin >> id;
            ChooseClient(id);
            Serve();
            break;
        case '5':
            return;
        default:
            cout << "Ошибка ввода. Попробуйте снова. " << endl;
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
