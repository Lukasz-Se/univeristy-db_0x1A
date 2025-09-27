#include <iostream>
#include "Headers/Student.h"
#include "Headers/db.h"

int main()
{
	db db(true, 100);
	std::cout << db.getFullDB() << std::endl;
	db.SaveToFile();
}