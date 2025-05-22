#pragma once
#include <iostream>
#include <vector>
#include "Student.h"

class db
{
public:
	~db();
	bool addStudent(Student* studentInput);
	bool Search(std::string surname);
	bool Search(pesel pesel);
	void SortByPesel();
	void SortBySurname();

	bool removeStudent(unsigned int indexNr);
	
	std::string getStudentsSurnames();

private:
	std::vector<Student*> m_Students;

	bool alreadyExist(pesel pesel);
};