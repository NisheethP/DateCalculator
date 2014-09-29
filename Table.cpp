#include "Table.h"
#include <Windows.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include <string>
#include <sstream>

using TableSpace::Table;
using TableSpace::Global;
using TableSpace::Colour;
using TableSpace::hilight;
using TableSpace::delight;
//==============================
// STATIC CLASS MEMBERS
//==============================

//~~~~TABLE~~~~//
int Table::MAX_ROW = 25;

//~~~~TABLE~~~~//
HANDLE Global::hStdin = GetStdHandle(STD_INPUT_HANDLE);
HANDLE Global::hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

//==============================
// CLASS FUNCTIONS
//==============================

Table::Table(int pRow, Coord pInitCoord, Coord pDeltaCoord) :
row(pRow)
{
	initCoord = new Coord;
	hiCoord = new Coord;
	deltaCoord = new Coord;
	initHiCoord = new Coord;

	if (row > MAX_ROW)
		row = MAX_ROW;

	column = 3;

	*initCoord = pInitCoord;
	*hiCoord = pInitCoord;
	*deltaCoord = pDeltaCoord;
	*initHiCoord = pInitCoord;

	for (int i = 0; i < pRow; ++i)
		tableData.push_back(Date());
}
Table::Table()
{
	Table(1, { 0, 0 }, { 0, 0 });
}
Table::~Table()
{
	delete initCoord;
	delete hiCoord;
	delete deltaCoord;
	delete initHiCoord;
};

//==============================
// SETTING DATA MEMBER
//==============================

void Table::setRow(int pRow)
{
	this->row = pRow;
}
void Table::setCol(int pCol)
{
	this->column = pCol;
}
void Table::setInitCoord(Coord pCoord)
{
	*initCoord = pCoord;
}
void Table::setDeltaCoord(Coord pCoord)
{
	*deltaCoord = pCoord;
}
void Table::setHiCoord(Coord pCoord)
{
	*hiCoord = pCoord;
}
void Table::setInitHiCoord(Coord pCoord)
{
	*initHiCoord = pCoord;
}
void Table::setDate(Date pDate, int pRow)
{
	if (pRow < row && pRow >= 0)
	{
		tableData[pRow] = pDate;
	}
	else
		throw Exceptions::TableRowOutOfBound(row, pRow);
}

//==============================
// GETTING DATA MEMBER
//==============================

int Table::getRow()
{
	return row;
}
int Table::getCol()
{
	return column;
}
Table::Coord Table::getInitCoord()
{
	return *initCoord;
}
Table::Coord Table::getDeltaCoord()
{
	return *deltaCoord;
}
Table::Coord Table::getHiCoord()
{
	return *hiCoord;
}
Table::Coord Table::getInitHiCoord()
{
	return *initHiCoord;
}
Date Table::getDate(int pRow)
{
	if (pRow >= row)
		throw Exceptions::TableRowOutOfBound(row, pRow);

	return tableData[pRow];
}

//=================================
//WINDOW CURSOR FUNCTIONS
//=================================

void Table::gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
		);
}
int Table::wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
		))
		return -1;
	return csbi.dwCursorPosition.Y;
}
int Table::wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
		))
		return -1;
	return csbi.dwCursorPosition.Y;
}

//==============================
// OTHER FUNCTIONS
//==============================

Table::Coord Table::HiToAbs(Coord pCoord)
{
	Coord rCoord = { 0, 0 };

	rCoord.x = pCoord.x - getInitHiCoord().x;
	rCoord.x /= getDeltaCoord().x;

	rCoord.y = pCoord.y - getInitHiCoord().y;
	rCoord.y /= getDeltaCoord().y;

	return rCoord;
}
Table::Coord Table::AbsToHi(Coord pCoord)
{
	Coord rCoord = { 0, 0 };

	rCoord.x = getDeltaCoord().x * pCoord.x + getInitHiCoord().x;

	rCoord.y = getDeltaCoord().y * pCoord.y + getInitHiCoord().y;
	return rCoord;
}

//==============================
// TABLE INTERACTION
//==============================

void Table::drawTable()
{
	int colDividers = column - 1;

	gotoxy(initCoord->x, initCoord->y);
	Coord curCoord = { initCoord->x - deltaCoord->x, initCoord->y };

	/*
	 *This will output the various rows.
	 *Tuple needs to be created to get a variable of
	 *each type in Parameter Pack. The default garbage value is used.
	 */

	int rowDataIter = 0;
	int colDataIter = 0;

	for (int rowIter = 0; rowIter < (row * deltaCoord->y) - 1; ++rowIter)
	{
		for (int colIter = 0; colIter < 2*column - 1 ; ++colIter)
		{
			curCoord = { initCoord->x + 2 * (deltaCoord->x*colIter), initCoord->y + deltaCoord->y*rowIter + 2 };

			boost::gregorian::date tempDate = tableData[rowDataIter].toDate();
			std::string dateStr = boost::gregorian::to_iso_extended_string(tempDate);

			std::string dateYear, dateMonth, dateDate;
			dateYear = dateMonth = dateDate = "";
			
			for (int i = 0; i < 4; ++i)
				dateYear += dateStr[i];					

			for (int i = 8; i < 10; ++i)
				dateDate += dateStr[i];

			const int MonthCoord = (initCoord->x + 5);
			const int YearCoord = (initCoord->x + 5) + 12;

			MonthToStr(tableData[rowDataIter].getMonth(),dateMonth);

			if (colIter%2 != 0)
			{
				if (colIter == 1)
					curCoord.x = initCoord->x + 3;
				else if (colIter == 3)
					curCoord.x = initCoord->x + 15;

				gotoxy(curCoord.x);
				cout << "-";

			}
			else
			{
				switch (colDataIter)
				{
				case 0:
					curCoord.x = initCoord->x;
					gotoxy(curCoord.x);
					cout << dateDate;
					break;
				case 1:
					curCoord.x = MonthCoord;
					gotoxy(curCoord.x);
					cout << dateMonth;
					break;
				case 2:
					curCoord.x = YearCoord;
					gotoxy(curCoord.x);
					cout << dateYear;
					break;
				}

				if (colDataIter < column)
					++colDataIter;
			}		
		}
		if (rowDataIter < row-1)
			++rowDataIter;
	}
}

//==============================
// OTHER FUNCTIONS
//==============================

WORD TableSpace::ColourToFore(Colour colour)
{
	WORD fore;
	switch (colour)
	{
	case 0:
		fore = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
		break;
	case 1:
		fore = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case 2:
		fore = FOREGROUND_RED;
		break;
	case 3:
		fore = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case 4:
		fore = FOREGROUND_BLUE;
		break;
	case 5:
		fore = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case 6:
		fore = FOREGROUND_GREEN;
		break;
	case 7:
		fore = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case 8:
		fore = FOREGROUND_BLUE | FOREGROUND_GREEN;
		break;
	case 9:
		fore = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case 10:
		fore = FOREGROUND_BLUE | FOREGROUND_RED;
		break;
	case 11:
		fore = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case 12:
		fore = FOREGROUND_RED | FOREGROUND_GREEN;
		break;
	case 13:
		fore = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	}

	return fore;
}
WORD TableSpace::ColourToBack(Colour colour)
{
	WORD back;
	switch (colour)
	{
	case 0:
		back = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN;
		break;
	case 1:
		back = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case 2:
		back = BACKGROUND_RED;
		break;
	case 3:
		back = BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case 4:
		back = BACKGROUND_BLUE;
		break;
	case 5:
		back = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case 6:
		back = BACKGROUND_GREEN;
		break;
	case 7:
		back = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case 8:
		back = BACKGROUND_BLUE | BACKGROUND_GREEN;
		break;
	case 9:
		back = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case 10:
		back = BACKGROUND_BLUE | BACKGROUND_RED;
		break;
	case 11:
		back = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case 12:
		back = BACKGROUND_RED | BACKGROUND_GREEN;
		break;
	case 13:
		back = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	}

	return back;
}
void TableSpace::SetDefaultColour(Colour colour)
{
	WORD fore = TableSpace::ColourToFore(colour);
	SetConsoleTextAttribute(Global::hStdout, fore);
}
void TableSpace::hilight(Table::Coord crd, int length, Colour Fore, Colour Back)
{
	COORD cord;
	DWORD wrd;
	cord.X = crd.x;
	cord.Y = crd.y;

	if (Back == TableSpace::Colour::None)
	{
		WORD fore = TableSpace::ColourToFore(Fore);
		FillConsoleOutputAttribute(Global::hStdout, fore, length, cord, &wrd);
	}
	else
	{
		WORD fore = TableSpace::ColourToFore(Fore);
		WORD back = TableSpace::ColourToBack(Back);
		FillConsoleOutputAttribute(Global::hStdout, fore | back, length, cord, &wrd);
	}

	//cout << endl;
	//cout << wrd;
}
void TableSpace::delight(Table::Coord crd, int length, Colour Fore, Colour Back)
{
	COORD cord;
	DWORD wrd;
	cord.X = crd.x;
	cord.Y = crd.y;

	if (Back == TableSpace::Colour::None)
	{
		WORD fore = TableSpace::ColourToFore(Fore);
		FillConsoleOutputAttribute(Global::hStdout, fore, length, cord, &wrd);
	}
	else
	{
		WORD fore = TableSpace::ColourToFore(Fore);
		WORD back = TableSpace::ColourToBack(Back);
		FillConsoleOutputAttribute(Global::hStdout, fore | back, length, cord, &wrd);
	}

	//cout << endl;
	//cout << wrd;
}
