#pragma once

#ifndef _DATE_H_
#define _DATE_H_


enum Month
{
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

#endif