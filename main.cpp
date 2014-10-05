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

Date TakeInp(Table& pDate);
//==============================
// MAIN FUNCTION
//==============================

int main()
{
	TableSpace::SetDefaultColour();
	
	 
	Table Date1(1, { 18, 14 }, { 7, 2 });
	Table Date2(1, { 18, 14 }, { 7, 2 });
	
	Date tempDate;
	
	tempDate = TakeInp(Date1);
	Date1.setDate(tempDate, 0);
	
	tempDate = TakeInp(Date2);
	Date2.setDate(tempDate, 0);


	cout << std::endl;
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

//TAKE INPUT FROM THE USER
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Date TakeInp(Table& pDate)
{
	/*
	 *I am keeping 3 Dates (parameter, ad 2 below) to make the UI a bit more fancy.
	 *First date to be shown will be Date1_Yesterday, Date1, Date1_Morrow
	 *The first and third can be in gray text, while the middle one in white to hilight it
	 *further.
	 *The hilight will only be able to move in Date1. Trying to go to any of the other Dates
	 *will just change the 3 dates themselves to seem as if it moved in a dial.
	 */

	//DATE DECLERATION
	Table date_Morrow(pDate);
	Table date_Yesterday(pDate);
	Table date(pDate);

	Table::Coord tempCoord = date.getInitCoord();

	tempCoord.y += 1;
	date_Morrow.setInitCoord(tempCoord);
	tempCoord.y -= 2;
	date_Yesterday.setInitCoord(tempCoord);

	/*
	 *This will make date_Yesterday one day, one month and one year before today.
	 *Similarly for the second one which will go ahead instead.
	 *This is so that the date can be shown in three rows. One will show the options if you
	 *Press UP and another for DOWN.
	 *When in the input handling loop, The date in Date, Date_Yesterday and Date_Morrow
	 *should be adjusted simultaneously.
	 */

	//TEMPORARY DATE TO BE USED IN THE FUNCTION.
	//NECESSARY BECAUSE THE DATE RETURNED BY TABLE CAN'T BE USED. ITS A PASS-BY-VALUE
	Date tempDate = date_Yesterday.getDate(0);
	ReduceAllDate(tempDate);
	date_Yesterday.setDate(tempDate, 0);

	tempDate = date_Morrow.getDate(0);
	IncreaseAllDate(tempDate);
	date_Morrow.setDate(tempDate, 0);

	date_Yesterday.drawTable();
	date.drawTable();
	date_Morrow.drawTable();

	//FOR GETTING OUT OF INPUT LOOP
	bool isLoopGoing = true;

	//INPUT LOOP FOR THE USER.
	//WILL LOOP INDINIFITELY UNTIL USER PRESSES 'ENTER' OR char(13)
	do
	{
		int hiLength = 0;
		std::string tempString;
		MonthToStr(date.getDate(0).getMonth(), tempString);

		switch (date.HiToAbs(date.getHiCoord()).x)
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
		date_Yesterday.drawTable();
		date.drawTable();
		date_Morrow.drawTable();

		TableSpace::delight(date.getHiCoord(), 25);
		TableSpace::hilight(date.getHiCoord(), hiLength);

		TableSpace::delight(date_Yesterday.getInitCoord(), 25, TableSpace::Gray);
		TableSpace::delight(date_Morrow.getInitCoord(), 25, TableSpace::Gray);

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
			if (date.getHiCoord().x != date.AbsToHi({ 2, 0 }).x)
			{
				Table::Coord newCoord = { 0, 0 };
				newCoord = date.HiToAbs(date.getHiCoord());
				newCoord.x += 1;
				date.setHiCoord(date.AbsToHi(newCoord));
			}
			break;

		case 'a':
			if (date.getHiCoord().x != date.AbsToHi({ 0, 0 }).x)
			{
				Table::Coord newCoord = { 0, 0 };
				newCoord = date.HiToAbs(date.getHiCoord());
				newCoord.x -= 1;
				date.setHiCoord(date.AbsToHi(newCoord));
			}
			break;

		case 'w':
			if (date.HiToAbs(date.getHiCoord()).x == 0)
			{
				Date tempDate = date.getDate(0);

				tempDate = date.getDate(0);
				ReduceDate(tempDate);
				date.setDate(tempDate, 0);

				tempDate = date_Yesterday.getDate(0);
				ReduceDate(tempDate);
				date_Yesterday.setDate(tempDate, 0);

				tempDate = date_Morrow.getDate(0);
				ReduceDate(tempDate);
				date_Morrow.setDate(tempDate, 0);

			}

			if (date.HiToAbs(date.getHiCoord()).x == 1)
			{
				Date tempDate = date.getDate(0);
				ReduceMonth(tempDate);
				date.setDate(tempDate, 0);

				tempDate = date_Yesterday.getDate(0);
				ReduceMonth(tempDate);
				date_Yesterday.setDate(tempDate, 0);

				tempDate = date_Morrow.getDate(0);
				ReduceMonth(tempDate);
				date_Morrow.setDate(tempDate, 0);
			}

			if (date.HiToAbs(date.getHiCoord()).x == 2)
			{
				Date tempDate = date_Yesterday.getDate(0);
				if (date_Yesterday.getDate(0).getYear() > MIN_YEAR)
					ReduceYear(tempDate);
				date_Yesterday.setDate(tempDate, 0);

				tempDate = date.getDate(0);
				if (date.getDate(0).getYear() > MIN_YEAR + 1)
					ReduceYear(tempDate);
				date.setDate(tempDate, 0);

				tempDate = date_Morrow.getDate(0);
				if (date_Morrow.getDate(0).getYear() > MIN_YEAR + 2)
					ReduceYear(tempDate);
				date_Morrow.setDate(tempDate, 0);
			}
			break;

		case 's':
			if (date.HiToAbs(date.getHiCoord()).x == 0)
			{
				Date tempDate = date.getDate(0);

				tempDate = date.getDate(0);
				IncreaseDate(tempDate);
				date.setDate(tempDate, 0);

				tempDate = date_Yesterday.getDate(0);
				IncreaseDate(tempDate);
				date_Yesterday.setDate(tempDate, 0);

				tempDate = date_Morrow.getDate(0);
				IncreaseDate(tempDate);
				date_Morrow.setDate(tempDate, 0);

			}

			if (date.HiToAbs(date.getHiCoord()).x == 1)
			{
				Date tempDate = date.getDate(0);
				IncreaseMonth(tempDate);
				date.setDate(tempDate, 0);

				tempDate = date_Yesterday.getDate(0);
				IncreaseMonth(tempDate);
				date_Yesterday.setDate(tempDate, 0);

				tempDate = date_Morrow.getDate(0);
				IncreaseMonth(tempDate);
				date_Morrow.setDate(tempDate, 0);
			}

			if (date.HiToAbs(date.getHiCoord()).x == 2)
			{
				Date tempDate = date_Yesterday.getDate(0);
				if (date_Yesterday.getDate(0).getYear() < MAX_YEAR - 2)
					IncreaseYear(tempDate);
				date_Yesterday.setDate(tempDate, 0);

				tempDate = date.getDate(0);
				if (date.getDate(0).getYear() < MAX_YEAR - 1)
					IncreaseYear(tempDate);
				date.setDate(tempDate, 0);

				tempDate = date_Morrow.getDate(0);
				if (date_Morrow.getDate(0).getYear() < MAX_YEAR)
					IncreaseYear(tempDate);
				date_Morrow.setDate(tempDate, 0);
			}
			break;

		case 13:
			isLoopGoing = false;
			break;

		default:
			break;
		}

	} while (isLoopGoing);

	return date.getDate(0);
}