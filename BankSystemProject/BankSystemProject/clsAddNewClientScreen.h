#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen {

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
       cout << "\nFirst name       :" <<client.firstName;
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

    static void showAddNewClientScreen() {

        // Check permissions 
        if (!checkAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            // if the user hasn't access, exit!
            return;
        }

        // print main header
        _DrawScreenHeader("\t\tAdd new client screen.");

        // read (a new) account number
        string accountNumber = "";
        cout << "\nPlease enter account number: ";
        accountNumber = clsInputValidate::readString();

        // check if the account number is exist
        while (clsBankClient::isClientExist(accountNumber))
        {
            cout << "\nThis account number is already exist.\nPlease enter account number: ";
            accountNumber = clsInputValidate::readString();
        }

        // add new client 
        clsBankClient newClient = clsBankClient::GetAddNewClientObject(accountNumber); // create an obj for the new client
        _ReadClientInfo(newClient);

        // save new client
        clsBankClient::enSaveResults saveResult = newClient.Save();

        // Show success message and print the new info
        switch (saveResult)
        {
        case clsBankClient::enSaveResults::svSucceded: {
            cout << "\nAccount added successfully!\n";
            _PrintClient(newClient);
            break;
        }
        case clsBankClient::enSaveResults::svFailedEmptyObj: {
            cout << "\nError! Updated wasn't saved! No data!\n";
            break;
        }
        case clsBankClient::enSaveResults::svFailAccountNumberExists: {
            cout << "\nError! Account number exists!\n";
            break;
        }
        }

    }

};