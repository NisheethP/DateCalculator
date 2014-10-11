#include "Table.h"
#include "Date.h"
#include <iostream>
#include <conio.h>
#include <cmath>
#include <tuple>
#include <cctype>

using TableSpace::Table;
using std::string;
typedef boost::gregorian::date bDate;
typedef std::tuple<int, bool, int> arrowInput;

enum KeyPress 
{
	Up,
	Down,
	Left,
	Right,
	Enter,
	E,
	BackSpace,
	Other
};

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
int numDigits(long int);
arrowInput getArrowInput();
string getDynamicInput(Table::Coord crd);
string truncateString(string str, const int MAX_STR_LENGTH);

//==============================
// MAIN FUNCTION
//==============================

int main()
{
	StrToMonth("JaNuary");
	TableSpace::SetDefaultColour();
	
	Table Date1(1, { 18, 14 }, { 7, 2 });
	Table Date2(1, { 18, 14 }, { 7, 2 });
	
	Date tempDate;
	
	Date1.gotoxy(Date1.getInitCoord().x, Date1.getInitCoord().y - 3);
	TableSpace::hilight({ Date1.getInitCoord().x-8, Date1.getInitCoord().y - 3 }, 70, TableSpace::Colour::Magenta, TableSpace::Colour::None);
	cout <<"Enter first Date: ";
	tempDate = TakeInp(Date1);
	Date1.setDate(tempDate, 0);
	
	Date2.gotoxy(Date2.getInitCoord().x, Date2.getInitCoord().y - 3);
	TableSpace::hilight({ Date2.getInitCoord().x, Date2.getInitCoord().y - 3 }, 25,TableSpace::Colour::Magenta,TableSpace::Colour::None);
	cout << "Enter Second Date: ";
	tempDate = TakeInp(Date2);
	Date2.setDate(tempDate, 0);

	int days = Date1.getDate(0) - Date2.getDate(0);
	Date1.gotoxy(0, 0);
	for (int i = 0; i < 80 * 16; ++i)
		cout << " ";

	Table::Coord curCoord = {10,15};
	Date1.gotoxy(curCoord.x, curCoord.y);
	
	if (days != 0)
	{

		int POS_DAYS = ((days>0) ? days : -days);

		cout << boost::gregorian::to_simple_string(Date2.getDate(0).toDate()) << " is ";
		TableSpace::hilight(curCoord, 11, TableSpace::Colour::Cyan, TableSpace::Colour::None);
		curCoord.x += 15;

		cout << POS_DAYS << " DAY";
		
		if (POS_DAYS != 1)
			cout << "S";
		
		cout << ((days > 0) ? " before " : " after ");
		
		//THIS IS LENGTH OF THE MIDDLE HILIGHT
		//THIS IS NUMBER OF DIGITS IN THE DURATION + CHARACTERS IN "DAY"/"DAYS" + CHARACTERS IN "BEFORE"/"AFTER"
		short hiLen = (numDigits(POS_DAYS) + ((POS_DAYS == 1) ? 5 : 6) + ((days > 0) ? 7 : 6));
		
		TableSpace::hilight(curCoord, hiLen, TableSpace::Colour::Red, TableSpace::Colour::None);
		curCoord.x += hiLen;
		cout << boost::gregorian::to_simple_string(Date1.getDate(0).toDate());

		TableSpace::hilight(curCoord, 11, TableSpace::Colour::Cyan, TableSpace::Colour::None);
	}
	else if (days == 0)
	{
		cout << "The two dates :: " << boost::gregorian::to_simple_string(Date1.getDate(0).toDate()) << " :: are same.";
		curCoord.x += sizeof("The two dates :: ") -1;
		TableSpace::hilight(curCoord, 11 ,TableSpace::Colour::Cyan, TableSpace::Colour::None);
	}

	std::cin.get();

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

		arrowInput userInp(getArrowInput());
		KeyPress keyPress;
		if (std::get<1>(userInp))
		{
			switch (std::get<0>(userInp))
			{
			case 72 /*UP*/:
				keyPress = KeyPress::Up;
				break;
			case 75 /*LEFT*/:
				keyPress = KeyPress::Left;
				break;
			case 77 /*RIGHT*/:
				keyPress = KeyPress::Right;
				break;
			case 80 /*DOWN*/:
				keyPress = KeyPress::Down;
				break;
			default:
				keyPress = KeyPress::Other;
			}
		}
		else
		{
			switch (std::get<2>(userInp))
			{
			case 13 /*ENTER*/:
				keyPress = KeyPress::Enter;
				break;
			case 'E':
			case 'e':
				keyPress = KeyPress::E;
				break;
			default:
				keyPress = KeyPress::Other;
				break;
			}
		}

		/*
		 *This do-While Loop is to take input from the user dynamically.
		 *I use _getch to get unbuffered input (WINDOWS only funciton) from the user.
		 *The cases will check if the HILIGHT is not already at the edge, and if not, 
		 *move it in that direction
		 *The Table::hiCoord needs to be adjusted for each case.
		 *char(13) is ENTER KEY
		 */

		switch (keyPress)
		{
		case KeyPress::Right:
			if (date.getHiCoord().x != date.AbsToHi({ 2, 0 }).x)
			{
				Table::Coord newCoord = { 0, 0 };
				newCoord = date.HiToAbs(date.getHiCoord());
				newCoord.x += 1;
				date.setHiCoord(date.AbsToHi(newCoord));
			}
			break;

		case KeyPress::Left:
			if (date.getHiCoord().x != date.AbsToHi({ 0, 0 }).x)
			{
				Table::Coord newCoord = { 0, 0 };
				newCoord = date.HiToAbs(date.getHiCoord());
				newCoord.x -= 1;
				date.setHiCoord(date.AbsToHi(newCoord));
			}
			break;

		case KeyPress::Down:
			if (date.HiToAbs(date.getHiCoord()).x == 0)
			{
				tempDate = date.getDate(0);

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
				tempDate = date.getDate(0);
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
				tempDate = date_Yesterday.getDate(0);
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

		case KeyPress::Up:
			if (date.HiToAbs(date.getHiCoord()).x == 0)
			{
				tempDate = date.getDate(0);

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
				tempDate = date.getDate(0);
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
				tempDate = date_Yesterday.getDate(0);
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

		case KeyPress::Enter:
			isLoopGoing = false;
			break;
		case KeyPress::E:
			date_Morrow.gotoxy(date_Morrow.getInitCoord().x, date_Morrow.getInitCoord().y + 3);
			
			if (date.HiToAbs(date.getHiCoord()).x == 0)
			{
				Table::Coord tempCoord = date_Morrow.getInitCoord();
				tempCoord.y += 3;
				
				unsigned short x = 0;
				std::cin >> x;

				if (x <= 0)
					x = 1;
				else if (x > 31)
					x = 31;

				tempDate = date.getDate(0);
				tempDate.setDate(x);
				date.setDate(tempDate, 0);

				ReduceAllDate(tempDate);			//NEEDS TO BE CANCEELED OUT. INCREEASE TWICE
				date_Yesterday.setDate(tempDate, 0);

				IncreaseAllDate(tempDate);
				IncreaseAllDate(tempDate);			//TWICE TO CANCEL THE REDUCTION ABOVE
				date_Morrow.setDate(tempDate, 0);
			}

			if (date.HiToAbs(date.getHiCoord()).x == 1)
			{
				Table::Coord tempCoord = date_Morrow.getInitCoord();
				tempCoord.y += 3;
				
				string month = getDynamicInput(tempCoord);
				Month curMonth = StrToMonth(month);

				if(curMonth != Month::Error)
				{
					tempDate = date.getDate(0);
					tempDate.setMonth(curMonth);
					date.setDate(tempDate, 0);

					ReduceAllDate(tempDate);			//NEEDS TO BE CANCEELED OUT. INCREEASE TWICE
					date_Yesterday.setDate(tempDate, 0);

					IncreaseAllDate(tempDate);
					IncreaseAllDate(tempDate);			//TWICE TO CANCEL THE REDUCTION ABOVE
					date_Morrow.setDate(tempDate, 0);
				}
			}

			if (date.HiToAbs(date.getHiCoord()).x == 2)
			{
				Table::Coord tempCoord = date_Morrow.getInitCoord();
				tempCoord.y += 3;
				
				unsigned int x = 0;
				std::cin >> x;

				if (x <= 1400)
					x = 1401;
				else if (x >= 10000)
					x = 9999;

				tempDate = date.getDate(0);
				tempDate.setYear(x);
				date.setDate(tempDate, 0);
				date_Yesterday.setDate(tempDate, 0);
				date_Morrow.setDate(tempDate, 0);
				
				//tempDate = date_Yesterday.getDate(0);
				if (tempDate.getYear() > MIN_YEAR)
					ReduceAllDate(tempDate);				//NEEDS TO BE CANCEELED OUT. INCREEASE TWICE
				date_Yesterday.setDate(tempDate, 0);

				//tempDate = date_Morrow.getDate(0);
				if (tempDate.getYear() < MAX_YEAR-1)		// MAX_YEAR - 1  AS tempDate IS ALREADY REDUCED ONCE
				{
					IncreaseAllDate(tempDate);
					IncreaseAllDate(tempDate);				//TWICE TO CANCEL THE REDUCTION ABOVE
				}
				date_Morrow.setDate(tempDate, 0);
			}

			date_Morrow.gotoxy(date_Morrow.getInitCoord().x, date_Morrow.getInitCoord().y + 3);
			for (int i = 0; i < 20; i++)
				cout << " ";
			break;
		case Other:
			break;
		default:
			break;
		}

	} while (isLoopGoing);

	return date.getDate(0);
}

//RETURN NUMBER OF DIGITS IN PARAMETER
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int numDigits(long int pNum)
{
	string s = std::to_string(pNum);
	return s.length();
}

//TAKE KEY PRESS INPUT: ALSO HANDLE ARROWKEYS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
arrowInput getArrowInput()
{
	char x = _getch();
	char y;
	bool isArrow = false;

	//_getch() puts two numbers in the buffer if one of the arrow keys is pressed. One of them is constant
	//char(224) is the constant part identifying it as an ARROW KEY
	//The second _getch() won't ever trigger as the number in the buffer will simply be returned to y.
	if (x == (char)224)
	{
		y = _getch();
		isArrow = true;
	}
	else
		y = 1;

	return arrowInput(y, isArrow, x);
}

//GET INPUT DYNAMICALLY
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string getDynamicInput(Table::Coord crd)
{
	string months[13] ={"january", "february", "march", "april",
						"may", "june", "july", "august", "september",
						"october", "november", "december", "ERROR_MONTH_ллллллллллллллллллллллл"
						/*л is a place holder to make it larger than most possible inputs from user. 
						 *Using ERROR only crashed it at any thing longer than 5 letters.
						 */
						};

	const int MAX_STR_LENGTH = 100;
	bool isLoopGoing = true;
	Table::Coord tempCoord = crd, rowCoord = crd;
	string dynString = "", tempString = "";
	std::vector<string> otherMonths;
		
	for (int i = 0; i < MAX_STR_LENGTH; i++)
		dynString += ' ';
	
	Table tempTable;
	tempTable.gotoxy(tempCoord.x, tempCoord.y);
	int curLength = 0;
	int monthNum = 0;
	int predictionRow = 1;
	do
	{
		otherMonths.clear();
		monthNum = 12;
		arrowInput userInp(getArrowInput());
		if (!(std::get<1>(userInp)))
		{
			switch (std::get<2>(userInp))
			{
			case 13 /*ENTER*/:
				//IN CASE OF ENTER, TERMINATE LOOP
				isLoopGoing = false;
				break;
			case 8 /*BACKSPACE*/:
				//IN CASE OF BACKSPACE, MOVE ONE BACK ON DISPLAY & ALSO EDIT STRING
				if (tempCoord.x > crd.x)
				{
					tempCoord.x -= 1;
					tempTable.gotoxy(tempCoord.x, tempCoord.y);
					cout << " ";
					curLength--;
					dynString[curLength] = ' ';
				}
				break;
			default:
				//IN CASE OF ANY KEY PRESS, OUTPUT ON SCREEN AND ADD TO STRING
				cout << (char)std::get<2>(userInp);
				dynString[curLength] = (char)std::get<2>(userInp);
				tempCoord.x++;
				curLength++;
				break;
			}
		}
		tempString = truncateString(dynString, dynString.length());
			
		for (int monthsIter = 0; monthsIter < 12; ++monthsIter)
		{
			string tMonth;
			tMonth = months[monthsIter];
			tMonth.resize(curLength);
			if (curLength != 0)
			{

				if (Lowerize(tMonth) == Lowerize(tempString))
				{
					monthNum = monthsIter;
					break;
				}
			}
		}

		/*This loop will iterate through all the months and put in an array all those months
			*that have the same letter as the first one apart fromt the one set above
			*This can then list all those months.
			*/
		for (int monthsIter = 0; monthsIter < 12; ++monthsIter)
		{
			string tMonth;
			tMonth = months[monthsIter];
			tMonth.resize(curLength);
			if (curLength != 0)
			{
				if (Lowerize(tMonth) == Lowerize(tempString))
				{
					if (monthsIter != monthNum)
						otherMonths.push_back(months[monthsIter]);
				}
			}
		}
			
		tempTable.gotoxy(rowCoord.x, rowCoord.y);
			
		for (int i = 0; i < 40; i++)
			cout << ' ';

		tempTable.gotoxy(rowCoord.x, rowCoord.y);
		string tempMonth = months[monthNum];
		string outputMonth = "                                        ";
			
		for (int i = 0; i < tempMonth.length() - curLength; i++)
		{
			outputMonth[i] = tempMonth[i + curLength];
		}

		outputMonth = truncateString(outputMonth, outputMonth.length());
		if (monthNum == 12)
			outputMonth.clear();
		cout << tempString << outputMonth;
		TableSpace::delight(rowCoord, curLength, TableSpace::Colour::Red);
		TableSpace::delight({ rowCoord.x + curLength, rowCoord.y }, months[monthNum].length() - curLength, TableSpace::Colour::DarkMagenta);
			
		for (int i = 0; i < 12; ++i)
		{
			if (i != monthNum)
			{
				tempTable.gotoxy(crd.x, crd.y + 1 + i);
				for (int i = 0; i < 40; i++)
					cout << " ";
			}
		}
			
		for (int i = 1; i < otherMonths.size()+1; ++i)
		{
			tempTable.gotoxy(crd.x, crd.y + i);
			cout << otherMonths[i-1];

			TableSpace::delight({ crd.x, crd.y + i }, otherMonths[i-1].length(), TableSpace::Colour::DarkMagenta);
		}

		KeyPress keyPress;
		if (std::get<1>(userInp))
		{
			switch (std::get<0>(userInp))
			{
			case 72 /*UP*/:
				keyPress = KeyPress::Up;
				break;
			case 80 /*DOWN*/:
				keyPress = KeyPress::Down;
				break;
			default:
				keyPress = KeyPress::Other;
			}
		}

		switch (keyPress)
		{
		case Up:
			if (predictionRow > 1)
			{
				rowCoord.y--;
			}
			break;
		case Down:
			if (predictionRow < 1)
			{
				rowCoord.y++;
			}
			break;
		}

		if (monthNum != 12 && !isLoopGoing)
		{
			dynString = tempMonth;
		}
		tempTable.gotoxy(tempCoord.x, tempCoord.y);
	} while (isLoopGoing);

	for (int i = 0; i < 12; ++i)
	{
		tempTable.gotoxy(crd.x, crd.y + 1 + i);
		for (int i = 0; i < 40; i++)
			cout << " ";
	}

	tempTable.gotoxy(tempCoord.x, tempCoord.y);
	
	dynString = truncateString(dynString, dynString.length());
	
	return dynString;
}

//TRUNCATE STRING TO REMOVE SPACE BARS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string truncateString(string str, const int MAX_STR_LENGTH)
{
	for (int i = MAX_STR_LENGTH - 1; i >= 0; --i)
	{
		if (str[i] == ' ')
		{
			str.pop_back();
		}
		else
			break;
	}

	return str;
}