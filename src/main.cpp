#include <iostream>
#include "Headers/Student.h"
#include "Headers/db.h"

int main()
{
	Student* student_1 = new Student;
	Student* student_2 = new Student;
	Student* student_3 = new Student;
	Student* student_4 = new Student;

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

	//student_4->m_name = "Adrian";
	//student_4->m_surname = "Zandberg";
	//student_4->m_address = "Humpelstrassse 22, Kopenhagen";
	//student_4->m_indeks_number = 1004;
	//student_4->m_gender = gender::male;
	//student_4->m_pesel.set("79120405455");

	university_db.addStudent(student_1);
	university_db.addStudent(student_2);
	university_db.addStudent(student_3);
	//university_db.addStudent(student_4);

	university_db.saveToFile();
	std::cout << "Lista studentow:" << university_db.getStudentsSurnames() << std::endl;

	university_db.Clear();

	std::cout << "Lista studentow:" << university_db.getStudentsSurnames() << std::endl;

	university_db.readFromFile();

	std::cout << "Lista studentow:" << university_db.getStudentsSurnames() << std::endl;
}