#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

class clsDeleteUserScreen : protected clsScreen {
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


public:

	static void showDeleteUsersScreen() {
		
        // Print the main header
        _DrawScreenHeader("\t\tDelete user screen.");

        // read username to check if user exists
        string username = "";
        cout << "\nPlease enter the username: ";
        username = clsInputValidate::readString();

        while (!clsUser::isUserExist(username))
        {
            cout << "\nUsername is not found!\nPlease enter again: ";
            username = clsInputValidate::readString();
        }

        // Print user data and ask for deletion
        clsUser user = clsUser::Find(username);
        _PrintUser(user);

        char deleteUser = 'Y';
        cout << "\n\nAre you sure you want to delete this user [Y/N]?  ";
        cin >> deleteUser;

        if (deleteUser == 'Y' || deleteUser == 'y')
        {
            if (user.Delete())
            {
                cout << "\nUser is deleted successfully\n";
                _PrintUser(user);
            }
            else
            {
                cout << "\nError! User is not deleted! ...\n";
            }
        }
	}

};