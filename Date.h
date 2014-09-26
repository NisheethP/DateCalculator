#pragma once

#ifndef _DATE_H_
#define _DATE_H_


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
	int month;
	int date;

public:
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
	Date();
	~Date();
};

#endif