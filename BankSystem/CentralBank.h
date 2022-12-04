#pragma once
#include <iostream>
#include <string>
#include "Bank.h"
using namespace std;

class BankSystem
{
private:
    Bank* _banks;
    int _banksCount = 0;
    Bank* _currentBank;
    int _nextBankID;
    
    void AddBank();

    void RemoveBank(int chosenBankID);

    void ChooseBank(int number);

    static BankSystem* Instance;  
    
public:
    
    void ShowBanks();
    
    Bank* FindBank(int id);
   
    static BankSystem* GetInstance();

    void Manager();

    

};
