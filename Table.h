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
		typedef vector<string> StrVector;

		static int MAX_ROW;
		int row;
		int column;

		StrVector colNames;
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
		int strMid(string);

	public:
		Table();
		Table(int pRow, Coord pInitCoord, Coord pInitHiCoord, Coord pDeltaCoord);

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

		void hilight(Coord, int);
		void delight(Coord, int);

		void setRow(int);
		void setCol(int);
		void setInitCoord(Coord);
		void setDeltaCoord(Coord);
		void setHiCoord(Coord);
		void setInitHiCoord(Coord);
		void setColNames(StrVector);
		boost::any getTupleTerm(int row, int col);


		int getRow();
		int getCol();
		Coord getInitCoord();
		Coord getDeltaCoord();
		Coord getHiCoord();
		Coord getInitHiCoord();
		StrVector getColNames();

		void drawTable();

		Coord HiToAbs(Coord);
		Coord AbsToHi(Coord);

		~Table();
	};
}
#endif
