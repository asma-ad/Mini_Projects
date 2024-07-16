#pragma once
#include <iostream>
#include <string>

using namespace std;

class interfaceCommunication {

public:

	virtual void senEmail(string title, string text) = 0;
	virtual void senFax(string title, string text) = 0;
	virtual void senSMS(string title, string text) = 0;

};