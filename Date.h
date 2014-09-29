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
//CLASS TO HANDLE DATES
//=============================
class Date
{
	typedef unsigned short ushort;
	ushort year;
	Month month;
	ushort date;

public:
	Date(ushort year, Month month, ushort date);
	Date(boost::gregorian::date);
	Date();
	~Date();

	//FUNCTIONS TO GET VALUES
	ushort getYear();
	Month getMonth();
	ushort getDate();

	//FUNCTIONS TO SET VALUES
	void setYear(ushort pYear);
	void setMonth(Month pMonth);
	void setDate(ushort pDate);

	//OPERATOR OVERLOADS
	int operator- (Date date);
	bool operator< (Date date);
	bool operator> (Date date);
	bool operator<=(Date date);
	bool operator>=(Date date);
	bool operator==(Date date);

	//CONVERSION FUNCTION
	boost::gregorian::date toDate();
};

//=============================
//OTHER HELPUL FUNCTIONS
//=============================
bool MonthToStr(Month pMonth, std::string &monthName);
bool GetMonth(std::string monthName, Month &month);
Month ConvMonth(boost::gregorian::greg_month pMonth);

#endif