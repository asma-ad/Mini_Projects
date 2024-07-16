#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen {

private:

    //---Read user info---
    static void _ReadUserInfo(clsUser &user) {

        cout << "\nEnter first name : ";
        user.firstName = clsInputValidate::readString();

        cout << "\nEnter last name  : ";
        user.lastName = clsInputValidate::readString();

        cout << "\nEnter email      : ";
        user.email = clsInputValidate::readString();

        cout << "\nEnter phone      : ";
        user.phone = clsInputValidate::readString();

        cout << "\nEnter password   : ";
        user.password = clsInputValidate::readString();

        cout << "\nEnter Permissios : ";
        user.permissions = _ReadPermissions();
    }

    //---Read permissions
    static int _ReadPermissions() {

        int permissions = 0;
        char answer = 'n';

        cout << "\nDo you want to give full access [Y/N]? ";
        cin >> answer;

        // giva full access
        if (answer == 'Y' || answer == 'y')
        {
            return -1;
        }

        // choose access
        cout << "\nDo you want to give access to :\n";

        cout << "\nShow client list [Y/N]? ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            permissions += clsUser::enPermissions::pListClient;
        }

        cout << "\nAdd new client [Y/N]? ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete client [Y/N]? ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            permissions += clsUser::enPermissions::pDeletClient;
        }

        cout << "\nUpdate client [Y/N]? ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            permissions += clsUser::enPermissions::pUpdateClient;
        }

        cout << "\nFind client [Y/N]? ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions [Y/N]? ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            permissions += clsUser::enPermissions::pTransactions;
        }

        cout << "\nManage users [Y/N]? ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nShow Login register [Y/N]? ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
        {
            permissions += clsUser::enPermissions::pLoginRegister;
        }

        return permissions;
    }

    //---print user info---
    static void _PrintUser(clsUser user)
    {
        cout << "\nUser info    :";
        cout << "\n-----------------------------------------";
        cout << "\nFirst name       :" << user.firstName;
        cout << "\nLast name        :" << user.lastName;
        cout << "\nFull name        :" << user.fullName();
        cout << "\nEmail            :" << user.email;
        cout << "\nPhone            :" << user.phone;
        cout << "\nUsername         :" << user.userName;
        cout << "\nPassword         :" << user.password;
        cout << "\nPermissions      :" << user.permissions;
        cout << "\n-----------------------------------------\n";
    }
   
public:

	static void showAddNewUsersScreen() {

        // print main header
        _DrawScreenHeader("\t\tAdd new user screen.");

        // read (a new) username
        string username = "";
        cout << "\nPlease enter an username: ";
        username = clsInputValidate::readString();

        // check if the username is exist
        while (clsUser::isUserExist(username))
        {
            cout << "\nThis username is already exist.\nPlease enter a new username: ";
            username = clsInputValidate::readString();
        }

        // add new user 
        clsUser newUser = clsUser::GetAddNewUserObject(username);  // create an obj for the new user
       _ReadUserInfo(newUser);

        // save new user
       clsUser::enSaveResults saveResult = newUser.Save();

        // Show success message and print the new info
        switch (saveResult)
        {
            case clsUser::enSaveResults::svSucceded: {
                cout << "\nUser added successfully!\n";
                _PrintUser(newUser);
                break;
            }
            case clsUser::enSaveResults::svFailedEmptyObj: {
                cout << "\nError! Updated wasn't saved! No data!\n";
                break;
            }
            case clsUser::enSaveResults::svFailUsernameExists: {
                cout << "\nError! Username already exists!\n";
                break;
            }
        }

    }
};