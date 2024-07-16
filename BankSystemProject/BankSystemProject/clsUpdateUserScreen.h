#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen  {
private:

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

    //---Read user info---
    static void _ReadUserInfo(clsUser& user) {

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


public:

	static void showUpdateUsersScreen() {

        // Print the main header
        _DrawScreenHeader("\t\tUpdate user screen.");

        // read username check if user exists
        string username = "";
        cout << "\nPlease enter username: ";
        username = clsInputValidate::readString();
        while (!clsUser::isUserExist(username))
        {
            cout << "\nUsername is not found!\nPlease enter again: ";
            username = clsInputValidate::readString();
        }

        // return client's information to update
        clsUser user = clsUser::Find(username);

        // Print info before updation
        _PrintUser(user);

        // Ask for Update
        char answer = 'N';
        cout << "\nAre you sure you want to update this user [Y/N]: ";
        cin >> answer;

        // Update
        if (answer == 'Y' || answer == 'y')
        {
            cout << "\n\nUpdate user info:";
            cout << "\n-----------------------\n";

            _ReadUserInfo(user);

            // Save new update
            clsUser::enSaveResults saveResult = user.Save();

            // Show success message and print the new info
            switch (saveResult) // UI
                {
            case clsUser::enSaveResults::svSucceded: {
                    cout << "\nUser updates successfully!\n";
                    _PrintUser(user);
                    break;
                }
                case clsUser::enSaveResults::svFailedEmptyObj: {
                    cout << "\nError! Updated wasn't saved! No data!\n";
                    break;
                }
            }

        }

	}

};