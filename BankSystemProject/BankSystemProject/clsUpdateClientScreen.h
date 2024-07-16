#pragma once
#include "clsScreen.h"

class clsUpdateClientScreen : protected clsScreen {
	
private:

    //---Read client info---
    static void _ReadClientInfo(clsBankClient& client) {

        cout << "\nEnter first name: ";
        client.firstName = clsInputValidate::readString();

        cout << "\nEnter last name: ";
        client.lastName = clsInputValidate::readString();

        cout << "\nEnter email: ";
        client.email = clsInputValidate::readString();

        cout << "\nEnter phone: ";
        client.phone = clsInputValidate::readString();

        cout << "\nEnter PIN code: ";
        client.pinCode = clsInputValidate::readString();

        cout << "\nEnter balance: ";
        client.accountBalance = clsInputValidate::readFloatNumber();
    }

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

	static void showUpdateClientScreen() {

        // Check permissions 
        if (!checkAccessRights(clsUser::enPermissions::pUpdateClient))
        {
            // if the user hasn't access, exit!
            return;
        }

        // Print the main header
        _DrawScreenHeader("\t\tUpdate client screen.");

        // read account number to check if client exists
        string accountNumber = "";
        cout << "\nPlease enter client account number: ";
        accountNumber = clsInputValidate::readString();
        while (!clsBankClient::isClientExist(accountNumber))
        {
            cout << "\nAccount number is not found!\nPlease enter again: ";
            accountNumber = clsInputValidate::readString();
        }

        // return client's information to update
        clsBankClient client = clsBankClient::findClient(accountNumber);

        // Print info before updation
        _PrintClient(client);

        // Ask for Update
        char answer = 'N';
        cout << "\nAre you sure you want to update this client [Y/N]: ";
        cin >> answer;

        // Update
        if (answer == 'Y' || answer == 'y')
        {
            cout << "\n\nUpdate client info:";
            cout << "\n-----------------------\n";

            _ReadClientInfo(client);

            // Save new update
            clsBankClient::enSaveResults saveResult = client.Save();

            // Show success message and print the new info
            switch (saveResult) // UI
            {
                case clsBankClient::enSaveResults::svSucceded: {
                    cout << "\nAccount updates successfully!\n";
                    _PrintClient(client);
                    break;
                }
                case clsBankClient::enSaveResults::svFailedEmptyObj: {
                    cout << "\nError! Updated wasn't saved! No data!\n";
                    break;
                }
            }

        }  

	}
};