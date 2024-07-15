#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

class clsScreen {

protected:

    // Print the main header of the sceen
    static void _DrawScreenHeader(string title, string subtitle = "") {

        cout << "\t\t\t\t\t------------------------------------------------------------";
        cout << "\n\n\t\t\t\t\t\t" << title;
        if (subtitle != "")
        {
            cout << "\n\t\t\t\t\t\t\t" << subtitle;
        }
        cout << "\n";
        cout << "\n\t\t\t\t\t------------------------------------------------------------\n\n";
 

    }

};