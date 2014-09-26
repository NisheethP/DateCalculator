#include "Table.h"

//=============================
//STRUCT FOR DATE DIFFERENCE
//=============================
struct DateDiff
{
	int Years;
	int Months;
	int Days;
};

//=============================
//CLASS TO HANDLE DATES
//=============================
class Date
{
	int Year;
	int Month;
	int Date;

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
};