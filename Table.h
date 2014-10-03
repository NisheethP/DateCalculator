#pragma once

#ifndef _TABLE_H_
#define _TABLE_H_

#include <Windows.h>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <type_traits>
#include <boost\utility\value_init.hpp>
#include <boost\any.hpp>
#include "Date.h"

using std::string;
using std::vector;
using std::tuple;
using std::cout;

namespace TableSpace
{
	enum Colour
	{
		Gray,
		White,
		DarkRed, 
		Red,
		DarkBlue,
		Blue,
		DarkGreen,
		Green,
		DarkCyan,
		Cyan,
		DarkMagenta,
		Magenta, 
		DarkYellow, 
		Yellow, 
		None
	};
	struct Global
	{
		static HANDLE hStdin;
		static HANDLE hStdout;
	};

	//==============================
	// CLASS DECLERATION
	//==============================
	class Table
	{
	public:
		class Coord;

	private:
		//Defining of data types
		typedef vector<Date> DateVector;

		static int MAX_ROW;
		int row;
		int column;

		DateVector tableData;

		Coord *initCoord;
		Coord *initHiCoord;
		Coord *hiCoord;
		Coord *deltaCoord;

		Coord static ConvCoord(Coord);

		void gotoxy(int column = wherex(), int line = wherey());
		int static wherex();
		int static wherey();
		bool isOdd(int x) { return (x % 2) ? true : false; }

	public:
		Table();
		Table(int pRow, Coord pInitCoord, Coord pDeltaCoord);

		class Coord
		{
		public:
			int x;
			int y;

			Coord()
			{
				x = 0;
				y = 0;
			};

			Coord(int X, int Y)
			{
				x = X;
				y = Y;
			}

			bool operator== (Coord p_Coord)
			{
				return (p_Coord.x == this->x) && (p_Coord.y == this->y);
			}

			bool operator!= (Coord p_Coord)
			{
				return (p_Coord.x != this->x) && (p_Coord.y != this->y);
			}
		};

		void setRow(int);
		void setCol(int);
		void setInitCoord(Coord);
		void setDeltaCoord(Coord);
		void setHiCoord(Coord);
		void setInitHiCoord(Coord);
		void setDate(Date pDate, int pRow);

		int getRow();
		int getCol();
		Coord getInitCoord();
		Coord getDeltaCoord();
		Coord getHiCoord();
		Coord getInitHiCoord();
		Date getDate(int pRow);

		void drawTable();

		Coord HiToAbs(Coord);
		Coord AbsToHi(Coord);

		~Table();
	};


	WORD ColourToFore(Colour);
	WORD ColourToBack(Colour);
	
	void SetDefaultColour(Colour colour = TableSpace::Colour::White);

	void hilight(Table::Coord crd, int length, Colour fore = Colour::DarkBlue, Colour back = Colour::White);
	void delight(Table::Coord crd, int length, Colour fore = Colour::White, Colour back = Colour::None);
}
#endif