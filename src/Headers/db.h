#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <sstream>

#include "Student.h"
#include "Employee.h"

class db
{
public:
	~db();
	bool addStudent(Student* studentInput);
	bool addEmployee(Employee* employeeInput);
	bool Search(const std::string& surname) const;
	bool Search(const pesel& pesel) const;
	void SortByPesel();
	void SortBySurname();
	void SortBySalary();

	bool removeStudent(unsigned int indexNr);
	
	std::string getBySurnames() const;
	std::string getDB();
	
	void Clear();
	bool saveToFile(std::string file = "db.dat");
	bool readFromFile(std::string file = "db.dat");

private:
	std::vector<Person*> m_Persons;

	bool alreadyExist(const pesel pesel) const;

};