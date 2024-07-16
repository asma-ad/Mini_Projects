#pragma once
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsBankClient.h"

class clsFindClientScreen : protected clsScreen {

private:
    //---print client card---
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

	static void showFindClientScreen() {
		
        // Check permissions 
        if (!checkAccessRights(clsUser::enPermissions::pFindClient))
        {
            // if the user hasn't access, exit!
            return;
        }

		// print the main header
		_DrawScreenHeader("\t\tFind client screen.");
	    
        // Read account number
        string accountNumber = "";
        cout << "\nPlease, enter account number: ";
        accountNumber = clsInputValidate::readString();

        // check if the account number exists
        while (!clsBankClient::isClientExist(accountNumber)) {
            cout << "\nAccount number not found!\nPlease, enter account number: ";
            accountNumber = clsInputValidate::readString();
        }

        // create an obj of client
        clsBankClient client = clsBankClient::findClient(accountNumber);

        if (!client.isEmpty()) {
            cout << "\n\nClient found :)\n\n";
        }
        else
        {
            cout << "\n\nClient not found :(\n\n";
        }

        // Print client info
        _PrintClient(client);
    }
};