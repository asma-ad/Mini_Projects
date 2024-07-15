#pragma warning(disable : 4996)
#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
using namespace std;

class clsDate
{

private:
	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

public:
	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}
	clsDate(string sDate)
	{
		vector<string> vDate;
		vDate = clsString::Split(sDate, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	clsDate(short day, short month, short year)
	{
		_Day = day;
		_Month = month;
		_Year = year;
	}
	clsDate(short dateOrderInYear, short year)
	{
		clsDate date = getDateFromDayOrderInYear(dateOrderInYear, year);
		_Day = date.day;
		_Month = date.month;
		_Year = date.year;
	}

	//---getters & setters---
	void setDay(short day)
	{
		_Day = day;
	}
	short getDay()
	{
		return _Day;
	}
	__declspec(property(get = getDay, put = setDay)) short day;

	void setMonth(short month)
	{
		_Month = month;
	}
	short getMonth()
	{
		return _Month;
	}
	__declspec(property(get = getMonth, put = setMonth)) short month;

	void setYear(short year)
	{
		_Year = year;
	}
	short getYear()
	{
		return _Year;
	}
	__declspec(property(get = getYear, put = setYear)) short year;

	//---Print---
	void Print()
	{
		cout << dateToString() << endl;
	}

	//---Get system date---
	static clsDate getSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short day, month, year;

		year = now->tm_year + 1900;
		month = now->tm_mon + 1;
		day = now->tm_mday;

		return clsDate(day, month, year);
	}

	//---Get system date time---
	static string getSystemDateTimeString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short day, month, year, hour, minute, second;

		year = now->tm_year + 1900;
		month = now->tm_mon + 1;
		day = now->tm_mday;

		hour = now->tm_hour;
		minute = now->tm_min;
		second = now->tm_sec;

		return to_string(day) + "/" + to_string(month) + "/" + to_string(year) + " - " +
			to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
	}

	//---Date to string---
	static string dateToString(clsDate date)
	{
		return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
	}
	string dateToString()
	{
		// Call the overloaded dateToString function, passing the current object as a reference.
		return dateToString(*this); // (*this) == current object
	}

	//---Is leap year---
	static bool isLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}
	bool isLeapYear()
	{
		isLeapYear(_Year);
	}

	//---Is validDate---
	static bool isValidDate(clsDate date)
	{
		//  check for days
		if (date.day < 1 || date.day > 31)
			return false;

		// check for months
		if (date.month < 1 || date.month > 12)
			return false;
		if (date.month == 2)
		{
			if (isLeapYear(date.year))
			{
				if (date.day > 29)
					return false;
			}
			else
			{
				if (date.day > 28)
					return false;
			}
		}

		short daysInMonth = numberOfDaysInAMonth(date.month, date.year);
		if (date.day > daysInMonth)
			return false;

		// otherwise, it's valid
		return true;
	}
	bool isValidDate()
	{
		return isValidDate(*this);
	}

	//---Number of days in a year---
	static short numberOfDaysInAYear(short year)
	{
		return isLeapYear(year) ? 365 : 364;
	}
	short numberOfDaysInAYear()
	{
		return numberOfDaysInAYear(_Year);
	}

	//---Number of hours in a year---
	static short numberOfHoursInAYear(short year)
	{
		return numberOfDaysInAYear(year) * 24;
	}
	short numberOfHoursInAYear()
	{
		return numberOfHoursInAYear(_Year);
	}

	//---Number of minutes in a year---
	static int numberOfMinutesInAYear(short year)
	{
		return numberOfHoursInAYear(year) * 60;
	}
	int numberOfMinutesInAYear()
	{
		return numberOfMinutesInAYear(_Year);
	}

	//---Number of seconds in a year---
	static int numberOfSecondsInAYear(short year)
	{
		return numberOfMinutesInAYear(year) * 60;
	}
	int numberOfSecondsInAYear()
	{
		return numberOfSecondsInAYear(_Year);
	}

	//---Number of days in a month---
	static short numberOfDaysInAMonth(short month, short year)
	{
		if (month < 1 || month > 12)
			return 0;

		int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (month == 2) ? (isLeapYear(year) ? 29 : 28) : days[month - 1];
	}
	short numberOfDaysInAMonth()
	{
		return numberOfDaysInAMonth(_Month, _Year);
	}

	//---Number of hours in a month---
	static short numberOfHoursInAMonth(short month, short year)
	{
		return numberOfDaysInAMonth(month, year) * 24;
	}
	short numberOfHoursInAMonth()
	{
		return numberOfDaysInAMonth(_Month, _Year) * 24;
	}

	//---Number of minutes in a month---
	static int numberOfMinutesInAMonth(short month, short year)
	{
		return numberOfHoursInAMonth(month, year) * 60;
	}
	int numberOfMinutesInAMonth()
	{
		return numberOfHoursInAMonth(_Month, _Year) * 60;
	}

	//---Number of seconds in a month---
	static int numberOfSecondsInAMonth(short month, short year)
	{
		return numberOfMinutesInAMonth(month, year) * 60;
	}
	int numberOfSecondsInAMonth()
	{
		return numberOfMinutesInAMonth(_Month, _Year) * 60;
	}

	//---Get date from day order in a year---
	static clsDate getDateFromDayOrderInYear(short dateOrderInYear, short year)
	{
		clsDate date;
		short remainingDays = dateOrderInYear;
		short monthDays = 0;

		date.year = year;
		date.month = 1;

		while (true)
		{
			monthDays = numberOfDaysInAMonth(date.month, year);

			if (remainingDays > monthDays)
			{
				remainingDays -= monthDays;
				date.month++;
			}
			else
			{
				date.day = remainingDays;
				break;
			}
		}

		return date;
	}

	//---Day of week order---
	static short dayOfWeekOrder(short day, short month, short year)
	{
		short a = (14 - month) / 12;
		short y = year - a;
		short m = month + (12 * a) - 2;

		return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short dayOfWeekOrder()
	{
		return dayOfWeekOrder(_Day, _Month, _Year);
	}

	//---Day short name---
	static string dayShortName(short dayOfWeekOrder)
	{
		string arrDayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		return arrDayNames[dayOfWeekOrder];
	}
	static string dayShortName(short day, short month, short year)
	{
		string arrDayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		return arrDayNames[dayOfWeekOrder(day, month, year)];
	}
	string dayShortName()
	{
		string arrDayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return arrDayNames[dayOfWeekOrder(_Day, _Month, _Year)];
	}

	//---Month short name---
	static string monthShortName(short monthNumber)
	{
		string arrMonths[12] = { "Jan", "Feb", "Mar",
								"Apr", "May", "Jun",
								"Jul", "Aug", "Sep",
								"Oct", "Nov", "Dec" };

		return (arrMonths[monthNumber - 1]);
	}
	string monthShortName()
	{
		return monthShortName(_Month);
	}

	//---Print a month calendar---
	static void printMonthCalendar(short month, short year)
	{

		// Index of the day from 0 to 6
		int current = dayOfWeekOrder(1, month, year);

		int numberOfDays = numberOfDaysInAMonth(month, year);

		// Print the current month name
		printf("\n  _______________%s_______________\n\n",
			monthShortName(month).c_str());

		// Print the columns
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		// Print appropriate spaces
		int i;
		for (i = 0; i < current; i++)
			printf("     ");

		// print days N
		for (int j = 1; j <= numberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n  _________________________________\n");
	}
	void printMonthCalendar()
	{
		printMonthCalendar(_Month, _Year);
	}

	//---Print a year calendar---
	static void printYearCalendar(int year)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", year);
		printf("  _________________________________\n");

		for (int i = 1; i <= 12; i++)
		{
			printMonthCalendar(i, year);
		}
	}
	void printYearCalendar()
	{
		printYearCalendar(_Year);
	}

	//---Days from the beginning of the year---
	static short daysFromTheBeginingOfTheYear(short day, short month, short year)
	{
		short totalDays = 0;

		for (int i = 1; i <= month - 1; i++)
		{
			totalDays += numberOfDaysInAMonth(i, year);
		}
		totalDays += day;

		return totalDays;
	}
	short daysFromTheBeginingOfTheYear()
	{
		short totalDays = 0;

		for (int i = 1; i <= _Month - 1; i++)
		{
			totalDays += numberOfDaysInAMonth(i, _Year);
		}
		totalDays += _Day;

		return totalDays;
	}

	//---Add days---
	void AddDays(short days)
	{

		short remainingDays = days + daysFromTheBeginingOfTheYear(_Day, _Month, _Year);
		short monthDays = 0;
		_Month = 1;

		while (true)
		{
			monthDays = numberOfDaysInAMonth(_Month, _Year);

			if (remainingDays > monthDays)
			{
				remainingDays -= monthDays;
				_Month++;

				if (_Month > 12)
				{
					_Month = 1;
					_Year++;
				}
			}
			else
			{
				_Day = remainingDays;
				break;
			}
		}
	}

	//---Is date_1 before date_2---
	static bool isDate1BeforeDate2(clsDate date_1, clsDate date_2)
	{
		return (date_1.year < date_2.year) ? true : ((date_1.year == date_2.year) ? (date_1.month < date_2.month ? true : (date_1.month == date_2.month ? date_1.day < date_2.day : false)) : false);
	}
	bool isDate1BeforeDate2(clsDate date_2)
	{
		// *this sends the current object :-)
		return isDate1BeforeDate2(*this, date_2);
	}

	//---Is date_1 equal date_2---
	static bool isDate1EqualDate2(clsDate date_1, clsDate date_2)
	{
		return (date_1.year == date_2.year) ? ((date_1.month == date_2.month) ? ((date_1.day == date_2.day) ? true : false) : false) : false;
	}
	bool isDate1EqualDate2(clsDate date_2)
	{
		return isDate1EqualDate2(*this, date_2);
	}

	//---Is date_1 after date_2---
	static bool isDate1AfterDate2(clsDate date_1, clsDate Date_2)
	{
		return (!isDate1BeforeDate2(date_1, Date_2) && !isDate1EqualDate2(date_1, Date_2));
	}
	bool isDate1AfterDate2(clsDate date_2)
	{
		return isDate1AfterDate2(*this, date_2);
	}

	//---Compare dates---
	enum enDateCompare
	{
		Before = -1,
		Equal = 0,
		After = 1
	};
	static enDateCompare compareDates(clsDate Date_1, clsDate Date_2)
	{
		if (isDate1BeforeDate2(Date_1, Date_2))
			return enDateCompare::Before;

		if (isDate1EqualDate2(Date_1, Date_2))
			return enDateCompare::Equal;

		/* if (IsDate1AfterDate2(Date1,Date2))
			 return enDateCompare::After;*/

			 // this is faster
		return enDateCompare::After;
	}
	enDateCompare compareDates(clsDate Date_2)
	{
		compareDates(*this, Date_2);
	}

	//---Is last day in a month---
	static bool
		isLastDayInMonth(clsDate date)
	{
		return (date.day == numberOfDaysInAMonth(date.month, date.year));
	}
	bool isLastDayInMonth()
	{
		return isLastDayInMonth(*this);
	}

	//---Is last month in a year---
	static bool isLastMonthInYear(short month)
	{
		return (month == 12);
	}
	bool isLastMonthInYear()
	{
		return (_Month == 12);
	}

	//---Swap dates---
	static void swapDates(clsDate& date_1, clsDate& date_2)
	{
		clsDate temp;
		temp = date_1;
		date_1 = date_2;
		date_2 = temp;
	}

	//---Get differnce in days---
	static int getDifferenceInDays(clsDate date_1, clsDate date_2, bool includeEndDay = false)
	{
		int days = 0;
		short sawpFlagValue = 1;

		if (!isDate1BeforeDate2(date_1, date_2))
		{
			swapDates(date_1, date_2);
			sawpFlagValue = -1;
		}

		while (isDate1BeforeDate2(date_1, date_2))
		{
			days++;
			date_1 = addOneDay(date_1);
		}

		return includeEndDay ? ++days * sawpFlagValue : days * sawpFlagValue;
	}
	int getDifferenceInDays(clsDate date_2, bool includeEndDay)
	{
		return getDifferenceInDays(*this, date_2, includeEndDay);
	}

	//---Calculate age in days---
	static short calculateMyAgeInDays(clsDate DateOfBirth)
	{
		return getDifferenceInDays(DateOfBirth, clsDate::getSystemDate(), true);
	}

	//---Add one day---
	static clsDate addOneDay(clsDate date)
	{
		if (isLastDayInMonth(date))
		{
			if (isLastMonthInYear(date.month))
			{
				date.month = 1;
				date.day = 1;
				date.year++;
			}
			else
			{
				date.day = 1;
				date.month++;
			}
		}
		else
		{
			date.day++;
		}

		return date;
	}
	void addOneDay()
	{
		*this = addOneDay(*this);
	}

	//---Increase date by X days---
	static clsDate increaseDateByXDays(short days, clsDate& date)
	{
		for (short i = 1; i <= days; i++)
		{
			date = addOneDay(date);
		}
		return date;
	}
	void increaseDateByXDays(short days)
	{
		increaseDateByXDays(days, *this);
	}

	//---Increase date by one week---
	static clsDate
		increaseDateByOneWeek(clsDate& date)
	{
		for (int i = 1; i <= 7; i++)
		{
			date = addOneDay(date);
		}
		return date;
	}
	void increaseDateByOneWeek()
	{
		increaseDateByOneWeek(*this);
	}

	//---Increase date by X weeks---
	clsDate increaseDateByXWeeks(short weeks, clsDate& date)
	{
		for (short i = 1; i <= weeks; i++)
		{
			date = increaseDateByOneWeek(date);
		}
		return date;
	}
	void increaseDateByXWeeks(short Weeks)
	{
		increaseDateByXWeeks(Weeks, *this);
	}

	//---Increase date by one month---
	static clsDate increaseDateByOneMonth(clsDate& date)
	{
		if (date.month == 12)
		{
			date.month = 1;
			date.year++;
		}
		else
		{
			date.month++;
		}

		short numberOfDaysInCurrentMonth = numberOfDaysInAMonth(date.month, date.year);
		if (date.day > numberOfDaysInCurrentMonth)
		{
			date.day = numberOfDaysInCurrentMonth;
		}

		return date;
	}
	void increaseDateByOneMonth()
	{
		increaseDateByOneMonth(*this);
	}

	//---Increase date by X months---
	static clsDate increaseDateByXMonths(short months, clsDate& date)
	{
		for (short i = 1; i <= months; i++)
		{
			date = increaseDateByOneMonth(date);
		}
		return date;
	}
	void increaseDateByXMonths(short months)
	{
		increaseDateByXMonths(months, *this);
	}

	//---Increase date by one year---
	static clsDate increaseDateByOneYear(clsDate& date)
	{
		date.year++;
		return date;
	}
	void increaseDateByOneYear()
	{
		increaseDateByOneYear(*this);
	}

	//---Increase date by X years---
	static clsDate increaseDateByXYear(short years, clsDate& date)
	{
		date.year += years;
		return date;
	}
	void increaseDateByXYear(short years)
	{
		increaseDateByXYear(years, *this);
	}

	//---Increase date by one decade---
	static clsDate increaseDateByOneDecade(clsDate& date)
	{
		date.year += 10;
		return date;
	}
	void increaseDateByOneDecade()
	{
		increaseDateByOneDecade(*this);
	}

	//---Increase date by X decades---
	static clsDate increaseDateByXDecade(short decades, clsDate& date)
	{
		date.year += decades * 10;
		return date;
	}
	void increaseDateByXDecade(short decades)
	{
		increaseDateByXDecade(decades, *this);
	}

	//---Increase date by One centruty---
	static clsDate increaseDateByOneCentury(clsDate& date)
	{
		date.year += 100;
		return date;
	}
	void increaseDateByOneCentury()
	{
		increaseDateByOneCentury(*this);
	}

	//---Increase date by One centruty---
	static clsDate increaseDateByOneMillennium(clsDate& date)
	{
		date.year += 1000;
		return date;
	}
	void increaseDateByOneMillennium()
	{
		increaseDateByOneMillennium(*this);
	}

	//---Decrease date by One day---
	static clsDate decreaseDateByOneDay(clsDate date)
	{
		if (date.day == 1)
		{
			if (date.month == 1)
			{
				date.month = 12;
				date.day = 31;
				date.year--;
			}
			else
			{

				date.month--;
				date.day = numberOfDaysInAMonth(date.month, date.year);
			}
		}
		else
		{
			date.day--;
		}

		return date;
	}
	void decreaseDateByOneDay()
	{
		decreaseDateByOneDay(*this);
	}

	//---Decrease date by X days---
	static clsDate decreaseDateByXDays(short days, clsDate& date)
	{
		for (int i = 1; i <= days; i++)
		{
			date = decreaseDateByOneDay(date);
		}
		return date;
	}
	void decreaseDateByXDays(short days)
	{
		decreaseDateByXDays(days, *this);
	}

	//---Decrease date by One week---
	static clsDate
		decreaseDateByOneWeek(clsDate& date)
	{
		for (int i = 1; i <= 7; i++)
		{
			date = decreaseDateByOneDay(date);
		}

		return date;
	}
	void decreaseDateByOneWeek()
	{
		decreaseDateByOneWeek(*this);
	}

	//---Decrease date by X weeks---
	static clsDate decreaseDateByXWeeks(short weeks, clsDate& date)
	{
		for (int i = 1; i <= weeks; i++)
		{
			date = decreaseDateByOneDay(date);
		}

		return date;
	}
	void decreaseDateByXWeeks(short weeks)
	{
		decreaseDateByXWeeks(weeks, *this);
	}

	//---Decrease date by one month---
	static clsDate decreaseDateByOneMonth(clsDate& date)
	{
		if (date.month == 1)
		{
			date.month = 12;
			date.year--;
		}
		else
			date.month--;

		short NumberOfDaysInCurrentMonth = numberOfDaysInAMonth(date.month, date.year--);

		if (date.day > NumberOfDaysInCurrentMonth)
		{
			date.day = NumberOfDaysInCurrentMonth;
		}

		return date;
	}
	void decreaseDateByOneMonth()
	{
		decreaseDateByOneMonth(*this);
	}

	//---Decrease date by X months---
	static clsDate decreaseDateByXMonths(short months, clsDate& date)
	{
		for (int i = 1; i <= months; i++)
		{
			date = decreaseDateByOneMonth(date);
		}

		return date;
	}
	void decreaseDateByXMonths(short months)
	{
		decreaseDateByXMonths(months, *this);
	}

	//---Decrease date by one year---
	static clsDate decreaseDateByOneYear(clsDate& date)
	{
		date.year--;
		return date;
	}
	void decreaseDateByOneYear()
	{
		decreaseDateByOneYear(*this);
	}

	//---Decrease date by X years---
	static clsDate decreaseDateByXYears(short years, clsDate& date)
	{
		date.year -= years;
		return date;
	}
	void decreaseDateByXYears(short years)
	{
		decreaseDateByXYears(years, *this);
	}

	//---Decrease date by one decade---
	static clsDate decreaseDateByOneDecade(clsDate& date)
	{
		date.year -= 10;
		return date;
	}
	void decreaseDateByOneDecade()
	{
		decreaseDateByOneDecade(*this);
	}

	//---Decrease date by X decades---
	static clsDate decreaseDateByXDecades(short decades, clsDate& date)
	{
		date.year -= decades * 10;
		return date;
	}
	void decreaseDateByXDecades(short decades)
	{
		decreaseDateByXDecades(decades, *this);
	}

	//---Decrease date by One centruty---
	static clsDate decreaseDateByOneCentury(clsDate& date)
	{
		date.year -= 100;
		return date;
	}
	void decreaseDateByOneCentury()
	{
		decreaseDateByOneCentury(*this);
	}

	//---Decrease date by One centruty---
	static clsDate decreaseDateByOneMillennium(clsDate& date)
	{
		date.year -= 1000;
		return date;
	}
	void decreaseDateByOneMillennium()
	{
		decreaseDateByOneMillennium(*this);
	}

	//---Is end of week---
	static short isEndOfWeek(clsDate date)
	{
		// the week starts from 0 to 6
		return dayOfWeekOrder(date.day, date.month, date.year) == 6;
	}
	short isEndOfWeek()
	{
		return isEndOfWeek(*this);
	}

	//---Is week end---
	static bool isWeekEnd(clsDate date)
	{
		// Weekends are Fri and Sat
		short dayIndex = dayOfWeekOrder(date.day, date.month, date.year);
		return (dayIndex == 5 || dayIndex == 6);
	}
	bool isWeekEnd()
	{
		return isWeekEnd(*this);
	}

	//---Is business day---
	static bool isBusinessDay(clsDate date)
	{
		// business days are Sun,Mon,Tue,Wed and Thur
		return !isWeekEnd(date);

		/*
		 short dayIndex = dayOfWeekOrder(date.day, date.month, date.year);
		 return  (dayIndex >= 5 && dayIndex <= 4);
		*/
	}
	bool isBusinessDay()
	{
		isBusinessDay(*this);
	}

	//---Days until the tnd of the week---
	static short daysUntilTheEndOfWeek(clsDate date)
	{
		return 6 - dayOfWeekOrder(date.day, date.month, date.year);
	}
	short daysUntilTheEndOfWeek()
	{
		daysUntilTheEndOfWeek(*this);
	}

	//---Days until the tnd of the month---
	static short daysUntilTheEndOfMonth(clsDate date)
	{
		clsDate endOfMonthDate;

		endOfMonthDate.day = numberOfDaysInAMonth(date.month, date.year);
		endOfMonthDate.month = date.month;
		endOfMonthDate.year = date.year;

		return getDifferenceInDays(date, endOfMonthDate, true);
	}
	short daysUntilTheEndOfMonth()
	{
		return daysUntilTheEndOfMonth(*this);
	}

	//---Days until the tnd of the yeat---
	static short daysUntilTheEndOfYear(clsDate date)
	{
		clsDate endOfYearDate;

		endOfYearDate.day = 31;
		endOfYearDate.month = 12;
		endOfYearDate.year = date.year;

		return getDifferenceInDays(date, endOfYearDate, true);
	}
	short daysUntilTheEndOfYear()
	{
		return daysUntilTheEndOfYear(*this);
	}

	//=======================================================//

	static short calculateBusinessDays(clsDate dateFrom, clsDate dateTo)
	{
		short days = 0;
		while (isDate1BeforeDate2(dateFrom, dateTo))
		{
			if (isBusinessDay(dateFrom))
				days++;

			dateFrom = addOneDay(dateFrom);
		}
		return days;
	}

	static short calculateVacationDays(clsDate dateFrom, clsDate dateTo)
	{
		return calculateBusinessDays(dateFrom, dateTo);
	}

	static clsDate calculateVacationReturnDate(clsDate dateFrom, short vacationDays)
	{
		short weekEndCounter = 0;

		for (short i = 1; i <= vacationDays; i++)
		{
			if (isWeekEnd(dateFrom))
				weekEndCounter++;

			dateFrom = addOneDay(dateFrom);
		}
		// to add weekends
		for (short i = 1; i <= weekEndCounter; i++)
			dateFrom = addOneDay(dateFrom);

		return dateFrom;
	}
};