#include <iostream>
#include "Headers/Student.h"
#include "Headers/db.h"

void remove(Student* p)
{
	delete p;
}

int main()
{
	Student* s = new Student;
	db db;
	
	s->m_name = "jas";
	s->m_surname = "kapela";
	s->m_pesel.set("23101212345");

	if (db.addStudent(s))
		std::cout << db.getStudentsSurnames() << std::endl;
	
	db.Clear();

	std::cout << "...";

	std::cout << db.getStudentsSurnames() << std::endl;
	

	return 0;
}