#pragma once
#include <iostream>
#include <string>
#include "CentralBank.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    BankSystem::GetInstance()->Manager();
}
