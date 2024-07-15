#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsString.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen {

private:

	enum enOption {enCode = 1, enCountry = 2};

	static void _PrintCuurency(clsCurrency currency) {

		cout << "\n=================================================";
		cout << "\nCurrency card:";
		cout << "\n=================================================";
		cout << "\nCountry	: " << currency.Country();
		cout << "\nCode 	: " << currency.currencyCode();
		cout << "\nName 	: " << currency.currencyName();
		cout << "\nRate(1$) : " << currency.Rate();
		cout << "\n=================================================\n";
		
	}

	static void _ShowResult(clsCurrency currency) {

		if (!currency.isEmpty())
		{
			cout << "\nFound!\n";
			_PrintCuurency(currency);
		}
		else
		{
			cout << "\nNot found!\n";
		}
	}

public:

	static void showFindCurrencyScreen() {
		
		// print the main header
		system("cls");
		_DrawScreenHeader("\t\tFind curreny screen.");

		// Read find option
		short userOption;
		cout  << "\nFind by: Code [1] , Country [2] ? ";
		userOption = clsInputValidate::readShortNumberBetween(1, 2, "Invalid number! Please enter 1 or 2: ");

		// Find by code
		 if (enOption::enCode == (enOption)userOption)
		 {
			 string code;
			 cout << "\nPlease enter currency code: ";
			 code = clsInputValidate::readString();
			 clsCurrency currencyByCode = clsCurrency::findByCode(code);
			 _ShowResult(currencyByCode);
		 }

		 // Find by country
		 else
		 {
			 string country;
			 cout << "\nPlease enter country name: ";
			 country = clsInputValidate::readString();
			 clsCurrency currencyByCountry = clsCurrency::findByCountry(country);
			 _ShowResult(currencyByCountry);
		 }
	}

};