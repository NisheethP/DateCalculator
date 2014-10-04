#include "Table.h"
#include "Date.h"
#include <iostream>
#include <conio.h>

using TableSpace::Table;
typedef boost::gregorian::date bDate;

const unsigned short MIN_YEAR = 1400;
const unsigned short MAX_YEAR = 10000;
//==============================
// FUNCTIONS DECLERATION
//==============================

void ReduceDate(Date &pDate);
void ReduceMonth(Date &pDate);
void ReduceYear(Date &pDate);
void ReduceAllDate(Date &pDate);

void IncreaseDate(Date &pDate);
void IncreaseMonth(Date &pDate);
void IncreaseYear(Date &pDate);
void IncreaseAllDate(Date &pDate);

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
	
	/*
	 *This will make date1_Yesterday one day, one month and one year before today.
	 *Similarly for the second one which will go ahead instead.
	 *This is so that the date can be shown in three rows. One will show the options if you
	 *Press UP and another for DOWN.
	 *When in the input handling loop, The date in Date1, Date1_Yesterday and Date1_Morrow
	 *should be adjusted simultaneously.
	 */
	Date tempDate = Date1_Yesterday.getDate(0);
	ReduceAllDate(tempDate);
	Date1_Yesterday.setDate(tempDate, 0);
	
	tempDate = Date1_Morrow.getDate(0);
	IncreaseAllDate(tempDate);

	Date1_Morrow.setDate(tempDate, 0);
	
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

		TableSpace::delight(Date1_Yesterday.getInitCoord(), 25, TableSpace::Gray);
		TableSpace::delight(Date1_Morrow.getInitCoord(), 25, TableSpace::Gray);

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
			if (Date1.getHiCoord().x != Date1.AbsToHi({ 2, 0 }).x)
			{
				Table::Coord newCoord = { 0, 0 };
				newCoord = Date1.HiToAbs(Date1.getHiCoord());
				newCoord.x += 1;
				Date1.setHiCoord(Date1.AbsToHi(newCoord));
			}
			break;

		case 'a':
			if (Date1.getHiCoord().x != Date1.AbsToHi({ 0, 0 }).x)
			{
				Table::Coord newCoord = { 0, 0 };
				newCoord = Date1.HiToAbs(Date1.getHiCoord());
				newCoord.x -= 1;
				Date1.setHiCoord(Date1.AbsToHi(newCoord));
			}
			break;

		case 'w':
			if (Date1.HiToAbs(Date1.getHiCoord()).x == 0)
			{
				Date tempDate = Date1.getDate(0);
				
				tempDate = Date1.getDate(0);
				ReduceDate(tempDate);
				Date1.setDate(tempDate,0);

				tempDate = Date1_Yesterday.getDate(0);
				ReduceDate(tempDate);
				Date1_Yesterday.setDate(tempDate, 0);

				tempDate = Date1_Morrow.getDate(0);
				ReduceDate(tempDate);
				Date1_Morrow.setDate(tempDate, 0);

			}

			if (Date1.HiToAbs(Date1.getHiCoord()).x == 1)
			{
				Date tempDate = Date1.getDate(0);
				ReduceMonth(tempDate);
				Date1.setDate(tempDate, 0);

				tempDate = Date1_Yesterday.getDate(0);
				ReduceMonth(tempDate);
				Date1_Yesterday.setDate(tempDate, 0);

				tempDate = Date1_Morrow.getDate(0);
				ReduceMonth(tempDate);
				Date1_Morrow.setDate(tempDate, 0);
			}

			if (Date1.HiToAbs(Date1.getHiCoord()).x == 2)
			{
				Date tempDate = Date1_Yesterday.getDate(0);
				if (Date1_Yesterday.getDate(0).getYear() > MIN_YEAR)
					ReduceYear(tempDate);
				Date1_Yesterday.setDate(tempDate, 0);

				tempDate = Date1.getDate(0);
				if (Date1.getDate(0).getYear() > MIN_YEAR + 1)
					ReduceYear(tempDate);
				Date1.setDate(tempDate, 0);

				tempDate = Date1_Morrow.getDate(0);
				if (Date1_Morrow.getDate(0).getYear() > MIN_YEAR + 2)
					ReduceYear(tempDate);
				Date1_Morrow.setDate(tempDate, 0);
			}
			break;

		case 's':
			if (Date1.HiToAbs(Date1.getHiCoord()).x == 0)
			{
				Date tempDate = Date1.getDate(0);

				tempDate = Date1.getDate(0);
				IncreaseDate(tempDate);
				Date1.setDate(tempDate, 0);

				tempDate = Date1_Yesterday.getDate(0);
				IncreaseDate(tempDate);
				Date1_Yesterday.setDate(tempDate, 0);

				tempDate = Date1_Morrow.getDate(0);
				IncreaseDate(tempDate);
				Date1_Morrow.setDate(tempDate, 0);

			}

			if (Date1.HiToAbs(Date1.getHiCoord()).x == 1)
			{
				Date tempDate = Date1.getDate(0);
				IncreaseMonth(tempDate);
				Date1.setDate(tempDate, 0);

				tempDate = Date1_Yesterday.getDate(0);
				IncreaseMonth(tempDate);
				Date1_Yesterday.setDate(tempDate, 0);

				tempDate = Date1_Morrow.getDate(0);
				IncreaseMonth(tempDate);
				Date1_Morrow.setDate(tempDate, 0);
			}

			if (Date1.HiToAbs(Date1.getHiCoord()).x == 2)
			{
				Date tempDate = Date1_Yesterday.getDate(0);
				if (Date1_Yesterday.getDate(0).getYear() < MAX_YEAR - 2)
					IncreaseYear(tempDate);
				Date1_Yesterday.setDate(tempDate, 0);

				tempDate = Date1.getDate(0);
				if (Date1.getDate(0).getYear() < MAX_YEAR - 1)
					IncreaseYear(tempDate);
				Date1.setDate(tempDate, 0);

				tempDate = Date1_Morrow.getDate(0);
				if (Date1_Morrow.getDate(0).getYear() < MAX_YEAR)
					IncreaseYear(tempDate);
				Date1_Morrow.setDate(tempDate, 0);
			}
			break;

		case 13:
			isLoopGoing = false;
			break;

		default:
			break;
		}

	} while (isLoopGoing);

	return 0;
}

//==============================
// FUNCTIONS DEFINITION
//==============================

//THE FUNCTIONS TO REDUCE FROM DATE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ReduceDate(Date &pDate)
{
	if (pDate.getDate() == 1)
	{
		pDate.setDate(31);
	}
	else
		pDate.setDate(pDate.getDate() - 1);
}
void ReduceMonth(Date &pDate)
{
	if (pDate.getMonth() == Month::January)
	{
		pDate.setMonth(Month::December);
	}
	else
		pDate.setMonth((Month)(pDate.getMonth()-1));

}
void ReduceYear(Date &pDate)
{
	pDate.setYear(pDate.getYear() -1);
}
void ReduceAllDate(Date &pDate)
{
	ReduceDate(pDate);
	ReduceMonth(pDate);
	ReduceYear(pDate);
}

//INCREASE THE DATE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void IncreaseDate(Date &pDate)
{
	if (pDate.getDate() == 31)
	{
		pDate.setDate(1);
	}
	else
		pDate.setDate(pDate.getDate() + 1);

}
void IncreaseMonth(Date &pDate)
{
	if (pDate.getMonth() == Month::December)
	{
		pDate.setMonth(Month::January);
	}
	else
		pDate.setMonth((Month)(pDate.getMonth() + 1));
}
void IncreaseYear(Date &pDate)
{
	pDate.setYear(pDate.getYear() + 1);
}
void IncreaseAllDate(Date &pDate)
{
	IncreaseDate(pDate);
	IncreaseMonth(pDate);
	IncreaseYear(pDate);
}