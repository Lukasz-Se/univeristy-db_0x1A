#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

#include "Student.h"

class db
{
public:
	~db();
	bool addStudent(Student* studentInput);
	bool Search(const std::string& surname) const;
	bool Search(const pesel& pesel) const;
	void SortByPesel();
	void SortBySurname();

	bool removeStudent(unsigned int indexNr);
	
	std::string getStudentsSurnames() const;
	
	void Clear();
	bool saveToFile(std::string file = "db.dat");
	bool readFromFile(std::string file = "db.dat");

private:
	std::vector<Student*> m_Students;

	bool alreadyExist(const pesel pesel) const;

};