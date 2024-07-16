#include <iostream>
#include "clsLoginScreen.h"


int main()
{

    while (true)
    {
        // Lock the System after 3 failed Logins.
        if (!clsLoginScreen::showLoginScreen())
        {
            break;
        }
    }

    return 0;
}
