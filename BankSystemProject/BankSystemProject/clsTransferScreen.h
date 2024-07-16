#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferScreen : protected clsScreen {

private:
	
	// Read account number to transfer from/to & check if it exists
	static string _ReadAccountNumber(string text) {

		string accountNumber = "";
		cout << text;
		accountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(accountNumber)) {
			cout << "\nAccount number not found!\nPlease, enter a valid account number: ";
			accountNumber = clsInputValidate::readString();
		}

		return accountNumber;
	}

	// Read transfer amount
	static float _ReadAmount(clsBankClient SourceAccount) {

		float transferAmount = 0;
		cout << "\nPlease enter transfer amount: ";
		transferAmount = clsInputValidate::readFloatNumber();

		// check if the amount & balance
		while (transferAmount > SourceAccount.accountBalance || transferAmount < 0 )
		{
			cout << "\nAmount exceeds the available balance, enter another amount: ";
			transferAmount = clsInputValidate::readFloatNumber();
		}
		return transferAmount;
	}

	//---print client card---
	static void _PrintClient(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n-----------------------------------------";
		cout << "\nFull name        :" << client.fullName();
		cout << "\nAccount number   :" << client.getAccountNumber();
		cout << "\nBalance          :" << client.accountBalance;
		cout << "\n-----------------------------------------\n";
	}
	

public:

	static void showTransferScreen() {

		// Print the main header
		system("cls");
		_DrawScreenHeader("\n\nTransfer screen");

		// Prompt account number to transfer from, then create an obj of the client & print info
		clsBankClient sourceClient = clsBankClient::findClient(_ReadAccountNumber("\nPlease, enter account number to transfer from: "));
		_PrintClient(sourceClient);

		// Prompt account number to transfer to, then create an obj of the client & print info
		clsBankClient DestinationClient = clsBankClient::findClient(_ReadAccountNumber("\nPlease, enter account number to transfer to: "));
		// check if the DestinationClient is same as sourceClient
		while (DestinationClient.getAccountNumber() == sourceClient.getAccountNumber())
		{
			DestinationClient = clsBankClient::findClient(_ReadAccountNumber("\nYou entered the same account number!!\nPlease, enter another account number to transfer to: "));
		}
		_PrintClient(DestinationClient);
		
		// Ask for amount
		float amount = _ReadAmount(sourceClient);

		// Check to apply transfer
		char answer = 'N';
		cout << "\nAre you sure you want to perform this operation [Y/N]? ";
		cin >> answer;

		// transfer
		if (answer == 'Y' || answer == 'y')
		{
			if (sourceClient.Transfer(amount, DestinationClient))
			{
				cout << "\nTransfer done successfully!\n";
				_PrintClient(sourceClient);
				_PrintClient(DestinationClient);
			}
			else
			{
				cout << "\nTransfer failed\n";
			}
		}

		else
		{
			cout << "\nOperation's cancelled!\n";
		}

	}
};