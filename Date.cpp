#include "Date.h"
#include <ctime>
#include <string>

Date::Date()
{
	std::time_t EpcTime;
	std::time(&EpcTime);
	std::tm LocTime;
	LocTime = *(std::localtime(&EpcTime));

	//std::string DateStr = LocTime;
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
