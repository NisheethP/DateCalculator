#pragma once

#ifndef _DATE_H_
#define _DATE_H_

#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>

enum Month
{
	Error = 0,
	January = 1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

//=============================
//STRUCT FOR DATE DIFFERENCE
//=============================
struct DateDiff
{
	int years;
	int months;
	int days;
};

//=============================
//CLASS TO HANDLE DATES
//=============================
class Date
{
	int year;
	Month month;
	int date;

public:
	Date(int year, Month month, int date);
	Date();
	~Date();

	//FUNCTIONS TO GET VALUES
	int getYear();
	Month getMonth();
	int getDate();

	//FUNCTIONS TO SET VALUES
	void setYear(int pYear);
	void setMonth(Month pMonth);
	void setDate(int pDate);

	//FUNCTIONS TO INTERACT WITH DATES
};



//=============================
//OTHER HELPUL FUNCTIONS
//=============================
bool MonthToStr(Month pMonth, std::string &monthName);
bool GetMonth(std::string monthName, Month &month);
Month ConvMonth(boost::gregorian::date pDate);

#endif