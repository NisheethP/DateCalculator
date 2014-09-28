#include "Table.h"
#include "Date.h"
#include <iostream>

int main()
{
	Date date1 (2014, January, 10);
	Date date2(2014, January, 20);

	date1 - date2;
	std::cin.get();
	return 0;
}