#pragma once
#include <iostream>
#include <iomanip>
#include "Global.h"
#include "clsUser.h"
#include "clsDate.h"

using namespace std;

class clsScreen {

protected:

    // Print the main header of the sceen
	static void _DrawScreenHeader(string title, string subtitle = "") {

        /*

        cout << setw(40) << left << "" << "------------------------------------------------------------\n";
        cout << setw(40) << left << "" << "\t" << title << "\n";
       
        if (subtitle != "")
        {
            cout << setw(40) << left << "" << subtitle;
        
        }
        cout << setw(40) << left << "" << "------------------------------------------------------------\n";
	    
        */

        cout << "\t\t\t\t\t------------------------------------------------------------";
        cout << "\n\n\t\t\t\t\t\t" << title;
        if (subtitle != "")
        {
            cout << "\n\t\t\t\t\t\t\t" << subtitle;
        }
        cout << "\n";
        cout << "\n\t\t\t\t\t------------------------------------------------------------\n\n";

        // Print currentUser
        cout << "\n\t\t\t\t\tUser :" << currentUser.userName << "\n";

        // Print current date
        clsDate date;
        cout << "\t\t\t\t\tDate :" << clsDate::dateToString(clsDate()) << "\n\n";
    }

    // check access permissions
    static bool checkAccessRights(clsUser::enPermissions permission) {

        if (!currentUser.checkAccessPermission(permission))
        {
            cout << "\t\t\t\t\t=====================================================================\n\n";
            cout << "\t\t\t\t\t\t\tAccess Denied! Contact your Admin ...\n\n";
            cout << "\t\t\t\t\t=====================================================================\n";
            return false;
        }
        else
        {
            return true;
        }

    }

};