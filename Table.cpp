#include "Table.h"
#include <Windows.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include <string>
#include <sstream>

using TableSpace::Table;
using TableSpace::Global;

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

Table::Table(int pRow, Coord pInitCoord, Coord pInitHiCoord, Coord pDeltaCoord) :
row(pRow)
{
	initCoord = new Coord;
	hiCoord = new Coord;
	deltaCoord = new Coord;
	initHiCoord = new Coord;

	if (row > MAX_ROW)
		row = MAX_ROW;

	column = 3;
	for (int i = 0; i < column; ++i)
		colNames.push_back("");

	*initCoord = pInitCoord;
	*hiCoord = pInitHiCoord;
	*deltaCoord = pDeltaCoord;
	*initHiCoord = pInitHiCoord;

}
Table::Table()
{
	Table(1, { 0, 0 }, { 0, 0 }, { 0, 0 });
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
void Table::setColNames(StrVector pColNames)
{
	colNames = pColNames;
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
Table::StrVector Table::getColNames()
{
	return colNames;
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
void Table::hilight(Coord crd, int length)
{
	WORD fore = FOREGROUND_BLUE;
	WORD back = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;

	COORD cord;
	DWORD wrd;
	cord.X = crd.x;
	cord.Y = crd.y;

	FillConsoleOutputAttribute(Global::hStdout, fore | back, length, cord, &wrd);

	//cout << endl;
	//cout << wrd;
}
void Table::delight(Coord crd, int length)
{
	WORD fore = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	COORD cord;
	DWORD wrd;
	cord.X = crd.x;
	cord.Y = crd.y;

	FillConsoleOutputAttribute(Global::hStdout, fore, length, cord, &wrd);

	//cout << endl;
	//cout << wrd;
}
int Table::strMid(string str)
{
	return (int)(str.length()) * 0.5f;
}


//==============================
// TABLE INTERACTION
//==============================

void Table::drawTable()
{
	int colDividers = column - 1;

	gotoxy(initCoord->x, initCoord->y);
	Coord curCoord = { initCoord->x - deltaCoord->x, initCoord->y };

	//gotoxy(curCoord.x, curCoord.y);
	//cout << "|";

	/*
	*This will output the various rows.
	*Tuple needs to be created to get a variable of
	*each type in Parameter Pack. The default garbage value is used.
	*/

	int rowDataIter = 0;
	int colDataIter = 0;

	for (int rowIter = 0; rowIter < row * deltaCoord->y; ++rowIter)
	{
		for (int colIter = 0; colIter < column * deltaCoord->x; ++colIter)
		{
			curCoord = { initCoord->x + 2 * (deltaCoord->x*colIter), initCoord->y + deltaCoord->y*rowIter + 2 };

			gotoxy(curCoord.x - 2 * deltaCoord->x + 2, curCoord.y);
			if (colIter == 0)
				cout << rowIter + 1;
			else if (colIter % (2 * deltaCoord->x) == 0)
				cout << "|";
			else
			{
				std::string dateStr = boost::gregorian::to_iso_extended_string(tableData[row].toDate());

				std::string dateYear, dateMonth, dateDate;
				dateYear = dateMonth = dateDate = "";

				for (int i = 0; i < 4; ++i)
					dateYear += dateStr[i];

				for (int i = 5; i < 7; ++i)
					dateMonth += dateStr[i];

				for (int i = 8; i < 10; ++i)
					dateDate += dateStr[i];

				switch (colDataIter)
				{
				case 0:
					cout << dateDate;
					break;
				case 1:
					cout << dateMonth;
					break;
				case 2:
					cout << dateYear;
					break;
				}

				if (colDataIter < column)
					++colDataIter;
			}
		}
		if (rowDataIter < row)
			++rowDataIter;
	}
}