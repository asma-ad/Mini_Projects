#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsUtil.h"
#include "clsString.h"

using namespace std;

class  clsCurrency {

private:

	enum enMode {enEmptyMode = 0, enUpdateMode = 1};
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	//---Convert line to currency object---
	static clsCurrency _ConvertLineToCurrencyObject(string line, string seperator = "#//#") {

		vector <string> vCurency = clsString::Split(line, seperator);

		return clsCurrency(enMode::enUpdateMode, vCurency[0], vCurency[1], vCurency[2], stof(vCurency[3]));

	}

	//---Convert currency object to line---
	static string _ConverCurrencyObjectToLine(clsCurrency currency, string seperator = "#//#")
	{

		string stCurrencyRecord = "";
		stCurrencyRecord += currency.Country() + seperator;
		stCurrencyRecord += currency.currencyCode() + seperator;
		stCurrencyRecord += currency.currencyName() + seperator;
		stCurrencyRecord += to_string(currency.Rate());

		return stCurrencyRecord;

	}

	//---Load currency data from file---
	static vector<clsCurrency> _LoadCurrenciesDataFromFile() {

		vector<clsCurrency> vCurrency;

		fstream myFile;
		myFile.open("Currencies.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			while (getline(myFile, line))
			{
				clsCurrency curreny = _ConvertLineToCurrencyObject(line);
				vCurrency.push_back(curreny);
			}
			myFile.close();
		}
		return vCurrency;
	}

	//---Save currency data to a file---
	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrency)
	{
		fstream myFile;
		myFile.open("Currencies.txt", ios::out);

		string line;
		if (myFile.is_open())
		{
			for (clsCurrency C : vCurrency)
			{
				line = _ConverCurrencyObjectToLine(C);
				myFile << line << endl;
			}
			myFile.close();
		}

	}

	//---Update---
	void _Update() {

		vector <clsCurrency> vCurrency = _LoadCurrenciesDataFromFile();

		for (clsCurrency &currency : vCurrency) {
			
			if (currency.currencyCode() == currencyCode())
			{
				currency = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(vCurrency);
	}

	//---Get empty object---
	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::enEmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode mode, string country, string currencyCode, string currencyName, float rate) {
		
		_Mode = mode;
		_Country = country;
		_CurrencyCode = currencyCode;
		_CurrencyName = currencyName;
		_Rate = rate;
	}

	//---Getters--- (READ ONLY)
	string Country() {
		return _Country;
	}
	string currencyCode() {
		return _CurrencyCode;
	}
	string currencyName() {
		return _CurrencyName;
	}
	float Rate() {
		return _Rate;
	}

	//---Is empty---
	bool isEmpty() {
		return (_Mode == enMode::enEmptyMode);
	}

	///---Update rate---
	void updateRate(float newRate) {
		_Rate = newRate;
		_Update();
	}

	//---Find by code---
	static clsCurrency findByCode(string currencyCode) {

		currencyCode = clsString::upperAllString(currencyCode);

		fstream myFile;
		myFile.open("Currencies.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			while (getline(myFile, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(line);
				if (currency.currencyCode() == currencyCode)
				{
					myFile.close();
					return currency;
				}
			}
			myFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	//---Find by country---
	static clsCurrency findByCountry(string country) {

		country = clsString::upperAllString(country);

		fstream myFile;
		myFile.open("Currencies.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			while (getline(myFile, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(line);
				if (clsString::upperAllString(currency.Country()) == country)
				{
					myFile.close();
					return currency;
				}
			}
		}

		return _GetEmptyCurrencyObject();
	}

	//---Is currency exsits---
	static bool isCurrencyExsit(string currencyCode) {

		clsCurrency Currency = clsCurrency::findByCode(currencyCode);
		return (!Currency.isEmpty());

	}

	//---Get currencies list---
	static vector <clsCurrency> getCurrenciesList() {
		return _LoadCurrenciesDataFromFile();
	}

};