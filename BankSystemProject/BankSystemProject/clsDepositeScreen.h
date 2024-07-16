#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsDepositeScreen : protected clsScreen {

private:

	//---Read account number---
	static string _ReadAccountNumber() {

		string accountNumber;

		cout << "Please, enter your Acount number: ";
		accountNumber = clsInputValidate::readString();
		return accountNumber;
	}

	//---Print client info---
	static void _PrintClient(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n-----------------------------------------";
		cout << "\nFirst name       :" << client.firstName;
		cout << "\nLast name        :" << client.lastName;
		cout << "\nFull name        :" << client.fullName();
		cout << "\nEmail            :" << client.email;
		cout << "\nPhone            :" << client.phone;
		cout << "\nAccount number   :" << client.getAccountNumber();
		cout << "\nPassword         :" << client.pinCode;
		cout << "\nBalance          :" << client.accountBalance;
		cout << "\n-----------------------------------------\n";
	}


public:

	static void showDepositeScreen() {

		// print the main header
		system("cls");
		_DrawScreenHeader("\t\tDeposite screen.");

		// Read account number
		string accountNumber = _ReadAccountNumber();

		// check if account exists
		while (!clsBankClient::isClientExist(accountNumber)) {
			cout << "Account doesn't exists\nPlease, enter a valid Acount number: ";
			accountNumber = _ReadAccountNumber();
		}

		// create an obj with client's info
		clsBankClient client = clsBankClient::findClient(accountNumber);

		// Print client info
		_PrintClient(client);

		// Read deposite amount
		double amount = 0;
		cout << "\nPlease, enter deposite amount: ";
		amount = clsInputValidate::readDoubleNumber();

		// check for sure
		char answer = 'n';
		cout << "\nAre you sure you want to perform this transaction [Y/N] ? ";
		cin >> answer;

		// Add amount then print new balance
		if (answer == 'Y' || answer == 'y')
		{
			if (client.Deposite(amount))
			{
				cout << "\nAmount deposited successfully\n";
				cout << "\nNew balance is : " << client.accountBalance;
			}
			else
			{
				cout << "\nError ...\nCan't deposite!! Negative value!.\n";
				cout << "\nAmount to deposite is : " << amount;
				cout << "\nYour balance is : " << client.accountBalance;
			}
		}
		else
		{
			cout << "\nOperation's cancelled!\n";
		}
	}

};