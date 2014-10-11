#include "Date.h"
#include "Table.h"
#include <cctype>
#include <algorithm>

using std::string;

//=============================
//=============================
//CLASS FUNCTIONS
//=============================
//=============================

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//CONSTRUCTORS & DESTRUCTORS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Date::Date()
{
	boost::gregorian::date Today(boost::gregorian::day_clock::local_day());
	
	year = Today.year();
	month = ConvMonth(Today.month());
	date = Today.day();
}
Date::Date(ushort pDate, Month pMonth, ushort pYear)
{
	date = pDate;
	month = pMonth;
	year = pYear;
}
Date::Date(boost::gregorian::date pDate)
{
	date = pDate.day();
	month = (Month)pDate.month().as_enum();
	year = pDate.year();
}
Date::~Date()
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//CLASS SETTING FUNCTIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Date::setDate(ushort pDate)
{
	date = pDate;
}
void Date::setMonth(Month pMonth)
{
	month = pMonth;
}
void Date::setYear(ushort pYear)
{
	year = pYear;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//CLASS GETTING FUNCTIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Date::ushort Date::getDate()
{
	return date;
}
Month Date::getMonth()
{
	return month;
}
Date::ushort Date::getYear()
{
	return year;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//CLASS OPERATOR OVERLOADS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int  Date::operator- (Date date)
{
	if (month != Error)
	{
		boost::gregorian::date_duration DateGap = this->toDate() - date.toDate();
		return DateGap.days();
	}
	else
	{
		return 0;
	}
}
bool Date::operator< (Date date)
{
	if (this->year < date.year)
	{
		if (this->month < date.month)
		{
			if (this->date < date.date)
			{
				return true;
			}
		}
	}
	return false;
}
bool Date::operator>(Date date)
{
	if (this->year > date.year)
	{
		if (this->month > date.month)
		{
			if (this->date > date.date)
			{
				return true;
			}
		}
	}

	return false;
}
bool Date::operator<=(Date date)
{
	if (this->year <= date.year)
	{
		if (this->month <= date.month)
		{
			if (this->date <= date.date)
			{
				return true;
			}
		}
	}
	return false;
}
bool Date::operator>=(Date date)
{
	if (this->year >= date.year)
	{
		if (this->month >= date.month)
		{
			if (this->date >= date.date)
			{
				return true;
			}
		}
	}

	return false;
}
bool Date::operator==(Date date)
{
	if (this->year == date.year)
	{
		if (this->month == date.month)
		{
			if (this->date == date.date)
			{
				return true;
			}
		}
	}
	
	return false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//CONVERSION FUNCTIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
boost::gregorian::date Date::toDate()
{
	boost::gregorian::months_of_year enumMonth = (boost::gregorian::months_of_year)month;

	boost::gregorian::date tempDate(1400,enumMonth, 1);
	int maxDate = tempDate.end_of_month().day();

	boost::gregorian::date tDate;
	if (date > maxDate)
	{
		boost::gregorian::greg_month gMonth(enumMonth);
		boost::gregorian::greg_day gDay(maxDate);
		boost::gregorian::greg_year gYear(year);

		tDate = boost::gregorian::date(gYear, gMonth, gDay);
	}
	else
	{
		boost::gregorian::greg_month gMonth(enumMonth);
		boost::gregorian::greg_day gDay(date);
		boost::gregorian::greg_year gYear(year);

		tDate = boost::gregorian::date(gYear, gMonth, gDay);
	}
	
	return tDate;
}

//=============================
//=============================
//OTHER FUNCTIONS
//=============================
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

struct to_lower
{
	int operator() (int ch)
	{
		return std::tolower(ch);
	}
};

std::string Lowerize(std::string str)
{
	std::string tempString = str;
	std::transform(str.begin(), str.end(), tempString.begin(), to_lower());
	return tempString;
}

Month StrToMonth(std::string str)
{
	Month month;
	
	Lowerize(str);

	if (str == "january")
		month = January;
	else if (str == "february")
		month = February;
	else if (str == "march")
		month = March;
	else if (str == "april")
		month = April;
	else if (str == "may")
		month = May;
	else if (str == "june")
		month= June;
	else if (str == "july")
		month = July;
	else if (str == "august")
		month = August;
	else if (str == "september")
		month = September;
	else if (str == "october")
		month = October;
	else if (str == "november")
		month = November;
	else if (str == "december")
		month = December;
	else
		month = Error;

	return month;
}