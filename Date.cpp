#include "Date.h"

using std::string;

//=============================
//CLASS FUNCTIONS
//=============================
Date::Date()
{
	boost::gregorian::date Today(boost::gregorian::day_clock::local_day());
	
	year = Today.year();
	month = ConvMonth(Today.month());
	date = Today.day();
}

Date::Date(int pDate, Month pMonth, int pYear)
{
	date = pDate;
	month = pMonth;
	year = pYear;
}

Date::~Date()
{
}

//=============================
//CLASS SETTING FUNCTIONS
//=============================
void Date::setDate(int pDate)
{
	date = pDate;
}

void Date::setMonth(Month pMonth)
{
	month = pMonth;
}

void Date::setYear(int pYear)
{
	year = pYear;
}


//=============================
//CLASS GETTING FUNCTIONS
//=============================
int Date::getDate()
{
	return date;
}

Month Date::getMonth()
{
	return month;
}

int Date::getYear()
{
	return year;
}


//=============================
//OTHER FUNCTIONS
//=============================

bool MonthToStr(Month pMonth, string &monthName)
{
	switch (pMonth)
	{
	case January:
		monthName = "January";
		return true;
	case February:
		monthName = "February";
		return true;
	case March:
		monthName = "March";
		return true;
	case April:
		monthName = "April";
		return true;
	case May:
		monthName = "May";
		return true;
	case June:
		monthName = "June";
		return true;
	case July:
		monthName = "July";
		return true;
	case August:
		monthName = "August";
		return true;
	case September:
		monthName = "September";
		return true;
	case October:
		monthName = "October";
		return true;
	case November:
		monthName = "November";
		return true;
	case December:
		monthName = "December";
		return true;
	default:
		monthName = "Invalid Month";
		return false;
	}
}
bool GetMonth(string monthName, Month &month)
{
	if (monthName == "Jan")
		month = January;
	else if (monthName == "Feb")
		month = February;
	else if (monthName == "Mar")
		month = March;
	else if (monthName == "Apr")
		month = April;
	else if (monthName == "May")
		month = May;
	else if (monthName == "Jun")
		month = June;
	else if (monthName == "Jul")
		month = July;
	else if (monthName == "Aug")
		month = August;
	else if (monthName == "Sep")
		month = September;
	else if (monthName == "Oct")
		month = October;
	else if (monthName == "Nov")
		month = November;
	else if (monthName == "Dec")
		month = December;
	else
		month = Error;

	if (month == Error)
		return false;
	else
		return true;
}
Month ConvMonth(boost::gregorian::greg_month pMonth)
{
	switch (pMonth.as_enum())
	{
	case 1:
		return January;
	case 2:
		return February;
	case 3:
		return March;
	case 4:
		return April;
	case 5:
		return May;
	case 6:
		return June;
	case 7:
		return July;
	case 8:
		return August;
	case 9:
		return September;
	case 10:
		return October;
	case 11:
		return November;
	case 12:
		return December;
	default:
		return Error;
	}	
}