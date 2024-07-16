#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsInputValidate
{

public:
    //---Valid number in range---
    static bool isNumberBetween(short number, short from, short to)
    {
        return (number < from || number > to) ? false : true;
    }
    static bool isNumberBetween(int number, int from, int to)
    {
        return (number >= from && number <= to);
    }
    static bool isNumberBetween(float number, float from, float to)
    {
        return (number >= from && number <= to) ? true : false;
    }
    static bool isNumberBetween(double number, double from, double to)
    {
        return (number >= from && number <= to) ? true : false;
    }
    
    static bool isValideDate(clsDate date)
    {
        return clsDate::isValidDate(date);
    }

    static bool isDateBetween(clsDate date, clsDate from, clsDate to)
    {
        // date >= from && date <= to
        if ((clsDate::isDate1AfterDate2(date, from) || clsDate::isDate1EqualDate2(date, from)) && (clsDate::isDate1BeforeDate2(date, to) || clsDate::isDate1EqualDate2(date, to)))
        {
            return true;
        }

        // date >= to && date <= from
        if ((clsDate::isDate1AfterDate2(date, to) || clsDate::isDate1EqualDate2(date, to)) && (clsDate::isDate1BeforeDate2(date, from) || clsDate::isDate1EqualDate2(date, from)))
        {
            return true;
        }

        else
            return false;
    }
    
    //---Read data---
    static short readShortNumber(string errorMsg = "Invalid number! Enter again: ")
    {
        short n;
        while (!(cin >> n))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << errorMsg;
        }
        return n;
    }
    static int readIntNumber(string errorMsg = "Invalid number! Enter again: ")
    {
        int n;
        while (!(cin >> n))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << errorMsg;
        }
        return n;
    }
    static double readDoubleNumber(string errorMsg = "Invalid number! Enter again: ")
    {
        double n;
        while (!(cin >> n))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << errorMsg;
        }
        return n;
    }  
    static float readFloatNumber(string errorMsg = "Invalid number! Enter again: ")
    {
        float n;
        while (!(cin >> n))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << errorMsg;
        }
        return n;
    }
    static string readString(string errorMsg = "Invalid! Enter again: ") {
        string str = "";
        // ws extracts as all the whitespace characters 
        getline(cin >> ws, str);
        return str;
    }

    //---Read in a range---
    static short readShortNumberBetween(short from, short to, string errorMsg)
    {
        short n = readShortNumber();
        while (!isNumberBetween(n, from, to))
        {
            cout << errorMsg;
            n = readShortNumber();
        }
        return n;
    }
    static int readIntNumberBetween(int from, int to, string errorMsg)
    {
        int n = readIntNumber();
        while (!isNumberBetween(n, from, to))
        {
            cout << errorMsg;
            n = readIntNumber();
        }
        return n;
    }
    static float readFloatNumberBetween(float from, float to, string errorMsg)
    {
        float n = readFloatNumber();
        while (!isNumberBetween(n, from, to))
        {
            cout << errorMsg;
            n = readFloatNumber();
        }
        return n;
    }
    static double readDoubleNumberBetween(double from, double to, string errorMsg)
    {
        double n = readDoubleNumber();
        while (!isNumberBetween(n, from, to))
        {
            cout << errorMsg;
            n = readDoubleNumber();
        }
        return n;
    }

    


};