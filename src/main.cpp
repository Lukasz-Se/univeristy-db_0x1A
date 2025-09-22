#include <iostream>
#include "Headers/Student.h"
#include "Headers/db.h"

int main()
{
	Student* student_1 = new Student;
	Student* student_2 = new Student;
	Student* student_3 = new Student;
	Student* student_4 = new Student;
	Employee* employee_1 = new Employee;
	Employee* employee_2 = new Employee;

	pesel pesel1, pesel2, pesel3, fake;

	db university_db;

	student_1->m_name = "Franek";
	student_1->m_surname = "Dolas";
	student_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	student_1->m_indeks_number = 1001;
	student_1->m_gender = gender::male;
	student_1->m_pesel.set("55101212346");

	student_2->m_name = "Hans";
	student_2->m_surname = "Kloss";
	student_2->m_address = "Stetinstrasse 77 Berlin";
	student_2->m_indeks_number = 1002;
	student_2->m_gender = gender::male;
	student_2->m_pesel.set("23101212345");

	student_3->m_name = "Hermann";
	student_3->m_surname = "Brunner";
	student_3->m_address = "Warszawsk 15 Olsztyn";
	student_3->m_indeks_number = 1003;
	student_3->m_gender = gender::male;
	student_3->m_pesel.set("79120405455");

	student_4->m_name = "Adrian";
	student_4->m_surname = "Zandberg";
	student_4->m_address = "Humpelstrassse 22, Kopenhagen";
	student_4->m_indeks_number = 1004;
	student_4->m_gender = gender::male;
	student_4->m_pesel.set("79120405455");

	employee_1->m_name = "Franek";
	employee_1->m_surname = "Duda";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("61012658203");

	employee_2->m_name = "Hans";
	employee_2->m_surname = "Blok";
	employee_2->m_address = "Stetinstrasse 77 Berlin";
	employee_2->m_salary = 1002;
	employee_2->m_gender = gender::male;
	employee_2->m_pesel.set("26110479026");

	university_db.addStudent(student_1);
	university_db.addStudent(student_2);
	university_db.addStudent(student_3);
	university_db.addStudent(student_4);
	university_db.addEmployee(employee_1);
	university_db.addEmployee(employee_2);

	university_db.saveToFile();
	std::cout << "Lista:" << university_db.getBySurnames() << std::endl;

	university_db.ClearDB();

	std::cout << "Lista (po wyczyszczeniu):" << university_db.getBySurnames() << std::endl;

	university_db.readFromFile();

	std::cout << "Lista (po wczytaniu):" << university_db.getBySurnames() << std::endl;

	std::cout << std::endl << university_db.getDB() << std::endl;

	std::string expected = "Franek;Dolas;\nHans;Kloss;\nHermann;Brunner;\nFranek;Duda;\nHans;Blok;\n";
	
	if (expected == university_db.getDB())
		std::cout << "Result: OK" << std::endl;
	else
		std::cout << "Result: None OK" << std::endl;

	std::cout << university_db.Search("Witkacy") << std::endl;
}