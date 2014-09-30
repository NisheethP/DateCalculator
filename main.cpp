#include "Table.h"
#include "Date.h"
#include <iostream>
#include <conio.h>

using TableSpace::Table;
typedef boost::gregorian::date bDate;
//==============================
// FUNCTIONS DECLERATION
//==============================

void ReduceDate(bDate &pDate, bDate pCurDate);
void ReduceMonth(bDate &pDate, bDate pCurDate);
void ReduceYear(bDate &pDate);
void ReduceAllDate(bDate &pDate, bDate pCurDate);

void IncreaseDate(bDate &pDate, bDate pCurDate);
void IncreaseMonth(bDate &pDate, bDate pCurDate);
void IncreaseYear(bDate &pDate);
void IncreaseAllDate(bDate &pDate, bDate pCurDate);

//==============================
// MAIN FUNCTION
//==============================

int main()
{
	TableSpace::SetDefaultColour();
	/*
	 *I am keeping 3 Dates to make the UI a bit more fancy.
	 *First date to be shown will be Date1_Yesterday, Date1, Date1_Morrow
	 *The first and third can be in gray text, while the middle one in white to hilight it
	 *further.
	 *The hilight will only be able to move in Date1. Trying to go to any of the other Dates
	 *will just change the 3 dates themselves to seem as if it moved in a dial.
	 */
	 
	Table Date1_Yesterday	(1, { 7, 4 }, { 7, 2 });
	Table Date1				(1, { 7, 5 }, { 7, 2 });
	Table Date1_Morrow		(1, { 7, 6 }, { 7, 2 });
	
	boost::gregorian::date date1_Yesterday, date1_Morrow;

	/*
	 *This will make date1_Yesterday one day, one month and one year before today.
	 *Similarly for the second one which will go ahead instead.
	 *This is so that the date can be shown in three rows. One will show the options if you
	 *Press UP and another for DOWN.
	 *When in the input handling loop, The date in Date1, Date1_Yesterday and Date1_Morrow
	 *should be adjusted simultaneously.
	 */
	
	date1_Yesterday = Date1_Yesterday.getDate(0).toDate();
	date1_Morrow = Date1_Morrow.getDate(0).toDate();

	ReduceAllDate(date1_Yesterday, Date1.getDate(0).toDate());
	IncreaseAllDate(date1_Morrow, Date1.getDate(0).toDate());
	
	Date1_Yesterday.setDate(date1_Yesterday,0);
	Date1_Morrow.setDate(date1_Morrow,0);

	Date1_Yesterday.drawTable();
	Date1.drawTable();
	Date1_Morrow.drawTable();

	TableSpace::delight(Date1_Yesterday.getInitCoord(), 25, TableSpace::Gray);
	TableSpace::delight(Date1_Morrow.getInitCoord(), 25, TableSpace::Gray);
	
	TableSpace::hilight(Date1.getInitHiCoord(), 2);
		
	bool isLoopGoing = true;
	do
	{
		int hiLength = 0;
		std::string tempString;
		MonthToStr(Date1.getDate(0).getMonth(), tempString);
		
		switch (Date1.HiToAbs(Date1.getHiCoord()).x)
		{
		case 0:
			hiLength = 2;
			break;
		case 1:
			hiLength = tempString.length();
			break;
		case 2:
			hiLength = 4;
			break;
		}
		Date1_Yesterday.drawTable();
		Date1.drawTable();
		Date1_Morrow.drawTable();

		TableSpace::delight(Date1.getHiCoord(), 25);
		TableSpace::hilight(Date1.getHiCoord(), hiLength);

		char userInp = _getch();
		/*
		 *This do-While Loop is to take input from the user dynamically.
		 *I use _getch to get unbuffered input (WINDOWS only funciton) from the user.
		 *After getting the input, it will check if it is one of the W-S-A-D keys and
		 *treat them as ARROW keys in same arrangement. The cases will check if the HILIGHT
		 *is not already at the edge, and if not, move it in that direction
		 *The Table::hiCoord needs to be adjusted for each case.
		 * char(13) is ENTER KEY
		 */
		switch (userInp)
		{
		case 'd':
			if (Date1.HiToAbs(Date1.getHiCoord()).x != Date1.AbsToHi({ 3, 0 }).x)
			{
				Table::Coord newCoord = { 0, 0 };
				newCoord = Date1.HiToAbs({Date1.getHiCoord().x, Date1.getHiCoord().y});
				newCoord.x += 1;
				Date1.setHiCoord(Date1.AbsToHi(newCoord));
			}
			break;

		case 'a':
			break;

		case 'w':
			break;

		case 's':
			break;

		case 13:
			isLoopGoing = false;
			break;

		default:
			break;
		}

	} while (isLoopGoing);

	std::cin.get();
	return 0;
}

//==============================
// FUNCTIONS DEFINITION
//==============================

//THE FUNCTIONS TO REDUCE FROM DATE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ReduceDate(bDate &pDate, bDate pCurDate)
{
	int maxCurDate = pCurDate.end_of_month().day();
	if (pDate.day() == 1)
	{
		pDate = Date(maxCurDate, (Month)pDate.month().as_enum(), pDate.year()).toDate();
	}
	else
		pDate = Date(pDate.day() - 1, (Month)pDate.month().as_enum(), pDate.year()).toDate();
}
void ReduceMonth(bDate &pDate, bDate pCurDate)
{
	if (pDate.month().as_enum() == Month::January)
	{
		pDate = Date(pDate.day(), Month::December, pDate.year()).toDate();
	}
	else
		pDate = Date(pDate.day(), (Month)(pDate.month().as_enum() - 1), pDate.year()).toDate();

}
void ReduceYear(bDate &pDate)
{
	pDate -= boost::gregorian::years(1);
}
void ReduceAllDate(bDate &pDate, bDate pCurDate)
{
	ReduceDate(pDate, pCurDate);
	ReduceMonth(pDate, pCurDate);
	ReduceYear(pDate);
}

//INCREASE THE DATE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void IncreaseDate(bDate &pDate, bDate pCurDate)
{
	int maxCurDate = pCurDate.end_of_month().day();
	if (pDate.day() == maxCurDate)
	{
		pDate = Date(1, (Month)pDate.month().as_enum(), pDate.year()).toDate();
		ReduceMonth(pDate, pCurDate);
	}
	else
		pDate = Date(pDate.day() + 1, (Month)pDate.month().as_enum(), pDate.year()).toDate();

}
void IncreaseMonth(bDate &pDate, bDate pCurDate)
{
	if ((Month)pDate.month().as_enum() == Month::December)
	{
		pDate = Date(pDate.day(), Month::January, pDate.year()).toDate();
	}
	else
		pDate = Date(pDate.day(), (Month)(pDate.month().as_enum() + 1), pDate.year()).toDate();
}
void IncreaseYear(bDate &pDate)
{
	pDate += boost::gregorian::years(1);
}
void IncreaseAllDate(bDate &pDate, bDate pCurDate)
{
	IncreaseDate(pDate, pCurDate);
	IncreaseMonth(pDate, pCurDate);
	IncreaseYear(pDate);
}