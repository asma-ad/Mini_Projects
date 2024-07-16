#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:

    enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkForDelete = false;

    //---Convert line to object---
    static clsUser _ConvertLineToUserObject(string line, string seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(line, seperator);
        
        // it's important to decrypt password to be able to login!
        return clsUser(enMode::updateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5]), stoi(vClientData[6]));
    }

    //---Convert User object to line (record)---
    static string _ConvertUserObjectToLine(clsUser client, string seperator = "#//#") {
        string clientRecord = "";

        clientRecord += client.firstName + seperator;
        clientRecord += client.lastName + seperator;
        clientRecord += client.email + seperator;
        clientRecord += client.phone + seperator;
        clientRecord += client.userName + seperator;
        clientRecord += clsUtil::EncryptText(client.password) + seperator; // encrypt pass
        clientRecord += to_string(client.permissions);

        return clientRecord;
    }

    //---Convert login register line to record---
    struct stLoginRegisterRecord;
    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string line, string seperator = "#//#") {

        stLoginRegisterRecord loginRegisterRecord; // record

        vector <string> vLoginRegisterLine = clsString::Split(line, seperator);

        loginRegisterRecord.dateTime = vLoginRegisterLine[0];
        loginRegisterRecord.username = vLoginRegisterLine[1];
        loginRegisterRecord.password = clsUtil::DecryptText(vLoginRegisterLine[2]); // it's important to decrypt password!
        loginRegisterRecord.permission =stoi(vLoginRegisterLine[3]);

        return loginRegisterRecord;

    }

    //---Get empty object---
    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::emptyMode, "", "", "", "", "", "", 0);
    }

    //---Load user data from file---
    static vector<clsUser> _LoadUsersDataFromFile() {

        vector<clsUser> vUsers;

        fstream myFile;
        myFile.open("Users.txt", ios::in);

        if (myFile.is_open())
        {
            string line = "";
            while (getline(myFile, line))
            {
                clsUser user = _ConvertLineToUserObject(line);
                vUsers.push_back(user);
            }
            myFile.close();
        }
        return vUsers;
    }

    //--- _Save users Data To File---
    static void  _SaveUsersDataToFile(vector<clsUser> vUsers) {

        fstream myFile;
        myFile.open("Users.txt", ios::out); // overwrite

        string line = "";

        if (myFile.is_open())
        {
            for (clsUser U : vUsers)
            {
                if (U._MarkForDelete == false)
                {
                    line = _ConvertUserObjectToLine(U);
                    myFile << line << endl;
                }
            }
            myFile.close();
        }
    }

    //---Update---
    void _Update() {

        // load user from a file to a vector
        vector<clsUser> vUser = _LoadUsersDataFromFile();

        // make changes - update the obj
        for (clsUser& U : vUser) {

            if (U.userName == _UserName) {
                U = *this; // update information
                break;
            }
        }

        // save user data to the file (updated data)
        _SaveUsersDataToFile(vUser);
    }

    //---Add new---
    void _AddDataLineToFile(string line)
    {
        fstream myFile;

        myFile.open("Users.txt", ios::out | ios::app);

        if (myFile.is_open())
        {
            myFile << line << endl;
        }

        myFile.close();
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }

    //---Log in record---
    string _PrepareLoginRecord(string seperator = "#//#") {

        string loginRecord = "";

        loginRecord += clsDate::getSystemDateTimeString() + seperator;
        loginRecord += userName + seperator;
        loginRecord += clsUtil::EncryptText(password) + seperator; // encrypt password
        loginRecord += to_string(permissions);

        return loginRecord;
    }

public:
    
    clsUser(enMode mode, string firstName, string lastName, string email, string phone, string userName, string password, int permissions)
        : clsPerson(firstName, lastName, email, phone)
    {
        _Mode = mode;
         _UserName = userName;
         _Password = password;
         _Permissions = permissions;
    }

    // Permissions
    enum enPermissions {
        pAll = -1, pListClient = 1, pAddNewClient = 2, pDeletClient = 4,
        pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLoginRegister = 128
    };
    bool checkAccessPermission(enPermissions permission) {

        if (this->permissions == enPermissions::pAll)
            return true;
        
        if ((permission & this->permissions) == permission)
            return true;
        else
            return false;
    }

    // Getters & Setters
    void setUserName(string username)
    {
        _UserName = username;
    }
    string getUserName()
    {
        return _UserName;
    }
    __declspec(property(get = getUserName, put = setUserName)) string userName;

    void setPassword(string password)
    {
        _Password = password;
    }
    string getPassword()
    {
        return _Password;
    }
    __declspec(property(get = getPassword, put = setPassword)) string password;

    void setPermissions(int permissions)
    {
        _Permissions = permissions;
    }
    int getPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = getPermissions, put = setPermissions)) int permissions;

    //---Mode---
    bool isEmpty()
    {
        return (_Mode == enMode::emptyMode);
    }

    //---Marked for deletedd---
    bool markedForDeleted() {
        return _MarkForDelete;
    }

    //---Find user---
    static clsUser Find(string username)
    {
        fstream myFile;
        myFile.open("Users.txt", ios::in);

        if (myFile.is_open())
        {
            string line = "";
            while (getline(myFile, line))
            {
                clsUser user = _ConvertLineToUserObject(line);
                if (user.userName == username)
                {
                    myFile.close();
                    return user;
                }
            }
            myFile.close();
        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string username, string password)
    {
        fstream myFile;
        myFile.open("Users.txt", ios::in);

        if (myFile.is_open())
        {
            string line = "";
            while (getline(myFile, line))
            {
                clsUser user = _ConvertLineToUserObject(line);
                if (user.userName == username && user.password == password)
                {
                    myFile.close();
                    return user;
                }
            }
            myFile.close();
        }

        return _GetEmptyUserObject();
    }

    //---Is user exist---
    static bool isUserExist(string username)
    {
        clsUser user = clsUser::Find(username);
        return (!user.isEmpty());
    }

    //---Save---
    enum enSaveResults { svFailedEmptyObj = 0, svSucceded = 1, svFailUsernameExists = 2 };
    enSaveResults Save() {
        switch (_Mode)
        {
        case clsUser::emptyMode:
        {
            return enSaveResults::svFailedEmptyObj;
            break;
        }
        case clsUser::updateMode:
        {
            _Update();
            return enSaveResults::svSucceded;
            break;
        }
        case clsUser::addNewMode:
        {
            if (clsUser::isUserExist(_UserName))
            {
                return enSaveResults::svFailUsernameExists;
            }
            else
            {
                _AddNew();
                _Mode = enMode::updateMode;
                return enSaveResults::svSucceded;
            }
        }

        }
    }

    //---Get add new user object---
    static clsUser GetAddNewUserObject(string username)
    {
        return clsUser(enMode::addNewMode, "", "", "", "", username, "", 0);
    }

    //---Delete user---
    bool Delete() {
        vector <clsUser> vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : vUsers)
        {
            if (U.userName == _UserName)
            {
                U._MarkForDelete = true;
                break;
            }
        }

        _SaveUsersDataToFile(vUsers);

        *this = _GetEmptyUserObject();

        return true;
    }

    //---User list---
    static vector <clsUser> getUsersList() {
        return _LoadUsersDataFromFile();
    }

    //---Register logins in a log file---
    void registerLoginInLogFile() {

        string dataLine = _PrepareLoginRecord();

        fstream myFile;
        myFile.open("logRegisterFile.txt", ios::out | ios::app);

        if (myFile.is_open())
        {
            myFile << dataLine << endl;
            myFile.close();
        }
    }

    //---Register list---
    struct stLoginRegisterRecord
    {
        string dateTime;
        string username;
        string password;
        int permission;
    };

    static vector <stLoginRegisterRecord> getLoginRegisterList() {

        vector <stLoginRegisterRecord> vLoginRegisterRec;

        fstream myFile;
        myFile.open("logRegisterFile.txt", ios::in);

        if (myFile.is_open())
        {
            string line;
            stLoginRegisterRecord loginRegisterRecord;

            while (getline(myFile, line)) 
            {
                loginRegisterRecord = _ConvertLoginRegisterLineToRecord(line);
                vLoginRegisterRec.push_back(loginRegisterRecord);
            }
            
            myFile.close();
        }

        return vLoginRegisterRec;

    }
};