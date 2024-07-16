#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"


class clsDeleteClientScreen : protected clsScreen {

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

	static void showDeleteClientScreen() {
	    
        // Check permissions 
        if (!checkAccessRights(clsUser::enPermissions::pDeletClient))
        {
            // if the user hasn't access, exit!
            return;
        }

            // Print the main header
             _DrawScreenHeader("\t\tDelete client screen.");
       
            // read account number to check if client exists
            string accountNumber = "";
            cout << "\nPlease enter client account number: ";
            accountNumber = clsInputValidate::readString();

            while (!clsBankClient::isClientExist(accountNumber))
            {
                cout << "\nAccount number is not found!\nPlease enter again: ";
                accountNumber = clsInputValidate::readString();
            }

            // Print client data and ask for deletion
            clsBankClient client = clsBankClient::findClient(accountNumber);
            _PrintClient(client);

            char deleteAccount = 'Y';
            cout << "\n\nAre you sure you want to delete this client account [Y/N]?  ";
            cin >> deleteAccount;

            if (deleteAccount == 'Y' || deleteAccount == 'y')
            {
                if (client.Delete())
                {
                    cout << "\nClient account is deleted successfully\n";
                    _PrintClient(client);
                }
                else
                {
                    cout << "\nError! Client account is not deleted!\n";
                }
            }

        
	}

};