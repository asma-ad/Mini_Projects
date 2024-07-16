#pragma once
#include <iostream>
#include <string>
#include "interfaceCommunication.h"

using namespace std;

class clsPerson : public interfaceCommunication
{
private:
    string _firstName;
    string _lastName;
    string _email;
    string _phone;

public:
    clsPerson(string firstName, string lastName, string email, string phone)
    {
        _firstName = firstName;
        _lastName = lastName;
        _email = email;
        _phone = phone;
    }

    // get & set firstName
    void setFirstName(string firstName)
    {
        _firstName = firstName;
    }
    string getFirstName()
    {
        return _firstName;
    }
    __declspec(property(get = getFirstName, put = setFirstName)) string firstName;

    // get & set lastName
    void setLastName(string lastName)
    {
        _lastName = lastName;
    }
    string getLastName()
    {
        return _lastName;
    }
    __declspec(property(get = getLastName, put = setLastName)) string lastName;

    // get & set email
    void setEmail(string email)
    {
        _email = email;
    }
    string getEmail()
    {
        return _email;
    }
    __declspec(property(get = getEmail, put = setEmail)) string email;

    // get & set phone
    void setPhone(string phone)
    {
        _phone = phone;
    }
    string getPhone()
    {
        return _phone;
    }
    __declspec(property(get = getPhone, put = setPhone)) string phone;

    // get FullName
    string fullName()
    {
        return _firstName + " " + _lastName;
    }

    // interfaceCommunication methods
    void senEmail(string title, string text) {

    }
    void senFax(string title, string text) {

    }
    void senSMS(string title, string text) {

    }

};