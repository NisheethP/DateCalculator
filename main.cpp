#include "Table.h"
#include "Date.h"
#include <iostream>

using TableSpace::Table;

//==============================
// FUNCTIONS DECLERATION
//==============================

void ReduceDate(boost::gregorian::date &pDate);
void ReduceMonth(boost::gregorian::date &pDate);
void ReduceYear(boost::gregorian::date &pDate);
void ReduceAllDate(boost::gregorian::date &pDate);

void IncreaseDate(boost::gregorian::date &pDate);
void IncreaseMonth(boost::gregorian::date &pDate);
void IncreaseYear(boost::gregorian::date &pDate);
void IncreaseAllDate(boost::gregorian::date &pDate);

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
	 *When in the input handling loop, The date in Date1, Date1_Yesterday and Date1_Morrow to
	 *Should be adjusted simultaneously.
	 */
	
	date1_Yesterday = Date1_Yesterday.getDate(0).toDate();
	date1_Morrow = Date1_Morrow.getDate(0).toDate();

	ReduceAllDate(date1_Yesterday);
	IncreaseAllDate(date1_Morrow);
	IncreaseDate(date1_Morrow);
	
	Date1_Yesterday.setDate(date1_Yesterday,0);
	Date1_Morrow.setDate(date1_Morrow,0);

	Date1_Yesterday.drawTable();
	Date1.drawTable();
	Date1_Morrow.drawTable();

	TableSpace::delight(Date1_Yesterday.getInitCoord(), 25, TableSpace::Gray);
	TableSpace::delight(Date1_Morrow.getInitCoord(), 25, TableSpace::Gray);

	std::cin.get();
	return 0;
}

//==============================
// FUNCTIONS DEFINITION
//==============================

//THE FUNCTIONS TO REDUCE FROM DATE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ReduceDate(boost::gregorian::date &pDate)
{
	pDate -= boost::gregorian::days(1);
}
void ReduceMonth(boost::gregorian::date &pDate)
{
	pDate -= boost::gregorian::months(1);
}
void ReduceYear(boost::gregorian::date &pDate)
{
	pDate -= boost::gregorian::years(1);
}
void ReduceAllDate(boost::gregorian::date &pDate)
{
	ReduceDate(pDate);
	ReduceMonth(pDate);
	ReduceYear(pDate);
}

//INCREASE THE DATE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void IncreaseDate(boost::gregorian::date &pDate)
{
	pDate += boost::gregorian::days(1);
}
void IncreaseMonth(boost::gregorian::date &pDate)
{
	pDate += boost::gregorian::months(1);
}
void IncreaseYear(boost::gregorian::date &pDate)
{
	pDate += boost::gregorian::years(1);
}
void IncreaseAllDate(boost::gregorian::date &pDate)
{
	IncreaseDate(pDate);
	IncreaseMonth(pDate);
	IncreaseYear(pDate);
}