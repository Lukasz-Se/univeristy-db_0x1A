#include "pch.h"
#include "../Headers/pesel.h"
#include "../Headers/db.h"

class peselFixture : public ::testing::Test
{
protected:
	pesel cut;
};

class univeristyDBFixture : public ::testing::Test
{
protected:
	Student* student_1 = new Student;
	Student* student_2 = new Student;
	Student* student_3 = new Student;
	Student* student_4 = new Student;

	Employee* employee_1 = new Employee;
	Employee* employee_2 = new Employee;
	Employee* employee_3 = new Employee;
	Employee* employee_4 = new Employee;

	pesel pesel1, pesel2, pesel3, pesel4, fake;

	db university_db;
};

TEST_F(peselFixture, PeselLength)
{
	// WHEN
	std::string input_1 = "1234";
	std::string input_2 = "123443242343423";
	std::string input_3 = "12344345342342343243243243255435345";
	std::string input_4 = "1234sadasd34234fsadfsd324";

	// THEN
	ASSERT_EQ(cut.set(input_1), pesel_error::WRONG_LENGTH);
	ASSERT_EQ(cut.set(input_2), pesel_error::WRONG_LENGTH);
	ASSERT_EQ(cut.set(input_3), pesel_error::WRONG_LENGTH);
	ASSERT_EQ(cut.set(input_4), pesel_error::WRONG_LENGTH);
}
					 
TEST_F(peselFixture, PeselmproperCharacters)
{
	// WHEN
	std::string input_1 = "1234567891a";
	std::string input_2 = "abfjsuwksox";
	std::string input_3 = "8501245245a";
	std::string input_4 = "55101212f44";
	std::string input_5 = "5510-212f44";
	std::string input_6 = "+55101(2f44";

	// THEN
	EXPECT_EQ(cut.set(input_1), pesel_error::NON_DIGITS);
	EXPECT_EQ(cut.set(input_2), pesel_error::NON_DIGITS);
	EXPECT_EQ(cut.set(input_3), pesel_error::NON_DIGITS);
	EXPECT_EQ(cut.set(input_4), pesel_error::NON_DIGITS);
	EXPECT_EQ(cut.set(input_5), pesel_error::NON_DIGITS);
	EXPECT_EQ(cut.set(input_6), pesel_error::NON_DIGITS);
}
					 
TEST_F(peselFixture, PeselChecksum)
{
	// WHEN
	std::string input_1 = "55101212345";
	std::string input_2 = "72121205599";
	std::string input_3 = "55101212346";
	std::string input_4 = "72121205598";

	// THEN
	EXPECT_EQ(cut.set(input_1), pesel_error::CHECKSUM_ERROR);
	EXPECT_EQ(cut.set(input_2), pesel_error::CHECKSUM_ERROR);
	EXPECT_EQ(cut.set(input_3), pesel_error::OK);
	EXPECT_EQ(cut.set(input_4), pesel_error::OK);
}
					 
TEST_F(peselFixture, PeselBrithDayFormat)
{
	// WHEN
	std::string input_1 = "55101212346";
	std::string input_2 = "72121205598";
	std::string input_3 = "55901212340";
	std::string input_4 = "72921205592";
	std::string input_5 = "72931205598";
	std::string input_6 = "72151205598";
	std::string input_7 = "55103212346";
	std::string input_8 = "72129305598";
	// THEN
	EXPECT_EQ(cut.set(input_1), pesel_error::OK);
	EXPECT_EQ(cut.set(input_2), pesel_error::OK);
	EXPECT_EQ(cut.set(input_3), pesel_error::OK);
	EXPECT_EQ(cut.set(input_4), pesel_error::OK);
	EXPECT_EQ(cut.set(input_5), pesel_error::WRONG_BDAY_FORMAT);
	EXPECT_EQ(cut.set(input_6), pesel_error::WRONG_BDAY_FORMAT);
	EXPECT_EQ(cut.set(input_7), pesel_error::WRONG_BDAY_FORMAT);
	EXPECT_EQ(cut.set(input_8), pesel_error::WRONG_BDAY_FORMAT);
}

TEST_F(univeristyDBFixture, StudentsAdd)
{
	student_1->m_name = "Franek";
	student_1->m_surname = "Dolas";
	student_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	student_1->m_indeks_number = 1001;
	student_1->m_gender = gender::male;
	student_1->m_pesel.set("55101212346");

	student_2->m_name = "Franek";
	student_2->m_surname = "Dolas";
	student_2->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	student_2->m_indeks_number = 1001;
	student_2->m_gender = gender::male;
	student_2->m_pesel.set("55101212346");

	student_3->m_name = "Hans";
	student_3->m_surname = "Kloss";
	student_3->m_address = "Stetinstrasse 77 Berlin";
	student_3->m_indeks_number = 1002;
	student_3->m_gender = gender::male;
	student_3->m_pesel.set("23101212345");

	student_4->m_name = "Aliena";
	student_4->m_surname = "Shire";
	student_4->m_address = "Mainroad 11 Kingsbridge";
	student_4->m_indeks_number = 1005;
	student_4->m_gender = gender::female;
	student_4->m_pesel.set("80012042518");

	EXPECT_TRUE(university_db.addStudent(student_1));
	EXPECT_FALSE(university_db.addStudent(student_2));
	EXPECT_TRUE(university_db.addStudent(student_3));
	EXPECT_FALSE(university_db.addStudent(student_1));
	EXPECT_FALSE(university_db.addStudent(student_3));
	EXPECT_FALSE(university_db.addStudent(student_4));
}

TEST_F(univeristyDBFixture, EmployeeAdd)
{
	employee_1->m_name = "Franek";
	employee_1->m_surname = "Dolas";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("55101212346");

	employee_2->m_name = "Franek";
	employee_2->m_surname = "Dolas";
	employee_2->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_2->m_salary = 2200;
	employee_2->m_gender = gender::male;
	employee_2->m_pesel.set("55101212346");

	employee_3->m_name = "Hans";
	employee_3->m_surname = "Kloss";
	employee_3->m_address = "Stetinstrasse 77 Berlin";
	employee_3->m_salary = 1002;
	employee_3->m_gender = gender::male;
	employee_3->m_pesel.set("23101212345");

	employee_4->m_name = "Aliena";
	employee_4->m_surname = "Shire";
	employee_4->m_address = "Mainroad 11 Kingsbridge";
	employee_4->m_salary = 1005;
	employee_4->m_gender = gender::female;
	employee_4->m_pesel.set("80012042518");

	EXPECT_TRUE(university_db.addEmployee(employee_1));
	EXPECT_FALSE(university_db.addEmployee(employee_2));
	EXPECT_TRUE(university_db.addEmployee(employee_3));
	EXPECT_FALSE(university_db.addEmployee(employee_1));
	EXPECT_FALSE(university_db.addEmployee(employee_2));
	EXPECT_FALSE(university_db.addEmployee(employee_4));
}

TEST_F(univeristyDBFixture, MixingStudentAndEmployeeAdd)
{

	student_1->m_name = "Franek";
	student_1->m_surname = "Dolas";
	student_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	student_1->m_indeks_number = 1001;
	student_1->m_gender = gender::male;
	student_1->m_pesel.set("55101212346");

	student_2->m_name = "Franek";
	student_2->m_surname = "Dolas";
	student_2->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	student_2->m_indeks_number = 1001;
	student_2->m_gender = gender::male;
	student_2->m_pesel.set("55101212346");

	student_3->m_name = "Hans";
	student_3->m_surname = "Kloss";
	student_3->m_address = "Stetinstrasse 77 Berlin";
	student_3->m_indeks_number = 1002;
	student_3->m_gender = gender::male;
	student_3->m_pesel.set("23101212345");

	student_4->m_name = "Aliena";
	student_4->m_surname = "Shire";
	student_4->m_address = "Mainroad 11 Kingsbridge";
	student_4->m_indeks_number = 1005;
	student_4->m_gender = gender::female;
	student_4->m_pesel.set("80012042518");

	employee_1->m_name = "Franek";
	employee_1->m_surname = "Dolas";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("61012658203");

	employee_2->m_name = "Franek";
	employee_2->m_surname = "Dolas";
	employee_2->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_2->m_salary = 2200;
	employee_2->m_gender = gender::male;
	employee_2->m_pesel.set("61012658203");

	employee_3->m_name = "Hans";
	employee_3->m_surname = "Kloss";
	employee_3->m_address = "Stetinstrasse 77 Berlin";
	employee_3->m_salary = 1002;
	employee_3->m_gender = gender::male;
	employee_3->m_pesel.set("26110479026");

	employee_4->m_name = "Aliena";
	employee_4->m_surname = "Shire";
	employee_4->m_address = "Mainroad 11 Kingsbridge";
	employee_4->m_salary = 0;
	employee_4->m_gender = gender::female;
	employee_4->m_pesel.set("19291285511");

	EXPECT_TRUE(university_db.addEmployee(employee_1));
	EXPECT_FALSE(university_db.addEmployee(employee_2));
	EXPECT_TRUE(university_db.addEmployee(employee_3));
	EXPECT_FALSE(university_db.addEmployee(employee_1));
	EXPECT_FALSE(university_db.addEmployee(employee_2));
	EXPECT_FALSE(university_db.addEmployee(employee_4));

	EXPECT_TRUE(university_db.addStudent(student_1));
	EXPECT_FALSE(university_db.addStudent(student_2));
	EXPECT_TRUE(university_db.addStudent(student_3));
	EXPECT_FALSE(university_db.addStudent(student_1));
	EXPECT_FALSE(university_db.addStudent(student_3));
	EXPECT_FALSE(university_db.addStudent(student_4));
}

TEST_F(univeristyDBFixture, MixingSearchStudentAndEmployeeBySurname)
{
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

	employee_1->m_name = "Zenek";
	employee_1->m_surname = "Duda";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("61012658203");

	employee_2->m_name = "Patryk";
	employee_2->m_surname = "Nijaki";
	employee_2->m_address = "Stetinstrasse 77 Berlin";
	employee_2->m_salary = 1002;
	employee_2->m_gender = gender::male;
	employee_2->m_pesel.set("26110479026");

	university_db.addStudent(student_1);
	university_db.addEmployee(employee_1);
	university_db.addStudent(student_2);
	university_db.addEmployee(employee_2);

	EXPECT_EQ(true, university_db.Search("Dolas"));
	EXPECT_EQ(true, university_db.Search("Nijaki"));
	EXPECT_NE(true, university_db.Search("Dolar"));
	EXPECT_EQ(true, university_db.Search("Kloss"));
	EXPECT_EQ(true, university_db.Search("Duda"));
}

TEST_F(univeristyDBFixture, MixingSearchStudentAndEmployeeByPesel)
{
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

	employee_1->m_name = "Zenek";
	employee_1->m_surname = "Duda";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("61012658203");

	employee_2->m_name = "Patryk";
	employee_2->m_surname = "Nijaki";
	employee_2->m_address = "Stetinstrasse 77 Berlin";
	employee_2->m_salary = 1002;
	employee_2->m_gender = gender::male;
	employee_2->m_pesel.set("26110479026");

	university_db.addStudent(student_1);
	university_db.addEmployee(employee_1);
	university_db.addStudent(student_2);
	university_db.addEmployee(employee_2);

	pesel1.set(student_1->m_pesel.getPesel());
	pesel2.set(student_2->m_pesel.getPesel());
	fake.set("791204054565");


	EXPECT_EQ(true, university_db.Search(pesel1));
	EXPECT_EQ(true, university_db.Search(pesel2));
	EXPECT_NE(true, university_db.Search(fake));

	pesel1.set(employee_1->m_pesel.getPesel());
	pesel2.set(employee_2->m_pesel.getPesel());

	EXPECT_EQ(true, university_db.Search(pesel1));
	EXPECT_EQ(true, university_db.Search(pesel2));

}

TEST_F(univeristyDBFixture, RemoveStudendByIndexNumber)
{
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

	university_db.addStudent(student_1);
	university_db.addStudent(student_2);

	EXPECT_FALSE(university_db.removeStudent(1005));
	EXPECT_TRUE(university_db.removeStudent(student_1->m_indeks_number));
	EXPECT_FALSE(university_db.Search("Dolas"));
}

TEST_F(univeristyDBFixture, DeletePersonByPesel)
{
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

	employee_1->m_name = "Zenek";
	employee_1->m_surname = "Duda";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("61012658203");

	employee_2->m_name = "Patryk";
	employee_2->m_surname = "Nijaki";
	employee_2->m_address = "Stetinstrasse 77 Berlin";
	employee_2->m_salary = 1002;
	employee_2->m_gender = gender::male;
	employee_2->m_pesel.set("26110479026");

	university_db.addStudent(student_1);
	university_db.addEmployee(employee_1);
	university_db.addStudent(student_2);
	university_db.addEmployee(employee_2);

	EXPECT_FALSE(university_db.Search("Dolas"));
}

TEST_F(univeristyDBFixture, DB)
{
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

	university_db.addStudent(student_1);
	university_db.addStudent(student_2);

	std::string expected = "Franek;Dolas;\nHans;Kloss;\n";

	EXPECT_EQ(university_db.getDB(), expected);
}

TEST_F(univeristyDBFixture, SortByPesel)
{
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

	employee_1->m_name = "Zenek";
	employee_1->m_surname = "Duda";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("61012658203");

	employee_2->m_name = "Patryk";
	employee_2->m_surname = "Nijaki";
	employee_2->m_address = "Stetinstrasse 77 Berlin";
	employee_2->m_salary = 1002;
	employee_2->m_gender = gender::male;
	employee_2->m_pesel.set("26110479026");

	university_db.addStudent(student_1);
	university_db.addStudent(student_2);
	university_db.addStudent(student_3);
	university_db.addEmployee(employee_1);
	university_db.addEmployee(employee_2);

	university_db.SortByPesel();
	EXPECT_EQ("Kloss;Nijaki;Dolas;Duda;Brunner;", university_db.getBySurnames());
}

TEST_F(univeristyDBFixture, SortBySurname)
{
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

	employee_1->m_name = "Zenek";
	employee_1->m_surname = "Duda";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("61012658203");

	employee_2->m_name = "Patryk";
	employee_2->m_surname = "Nijaki";
	employee_2->m_address = "Stetinstrasse 77 Berlin";
	employee_2->m_salary = 1002;
	employee_2->m_gender = gender::male;
	employee_2->m_pesel.set("26110479026");

	employee_3->m_name = "Hans";
	employee_3->m_surname = "Kloss";
	employee_3->m_address = "Stetinstrasse 77 Berlin";
	employee_3->m_salary = 15000;
	employee_3->m_gender = gender::male;
	employee_3->m_pesel.set("96052512556");

	university_db.addStudent(student_2);
	university_db.addStudent(student_1);
	university_db.addStudent(student_3);
	university_db.addEmployee(employee_1);
	university_db.addEmployee(employee_2);
	university_db.addEmployee(employee_3);

	university_db.SortBySurname();
	
	EXPECT_EQ("Brunner;Dolas;Duda;Kloss;Kloss;Nijaki;", university_db.getBySurnames());
}

TEST_F(univeristyDBFixture, SortBySalary)
{
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

	employee_1->m_name = "Zenek";
	employee_1->m_surname = "Duda";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("61012658203");

	employee_2->m_name = "Patryk";
	employee_2->m_surname = "Nijaki";
	employee_2->m_address = "Stetinstrasse 77 Berlin";
	employee_2->m_salary = 1002;
	employee_2->m_gender = gender::male;
	employee_2->m_pesel.set("26110479026");

	employee_3->m_name = "Hans";
	employee_3->m_surname = "Kloss";
	employee_3->m_address = "Stetinstrasse 77 Berlin";
	employee_3->m_salary = 15000;
	employee_3->m_gender = gender::male;
	employee_3->m_pesel.set("96052512556");

	university_db.addStudent(student_2);
	university_db.addStudent(student_1);
	university_db.addStudent(student_3);
	university_db.addEmployee(employee_1);
	university_db.addEmployee(employee_2);
	university_db.addEmployee(employee_3);

	university_db.SortBySalary();
	
	EXPECT_EQ("Kloss;Dolas;Brunner;Nijaki;Duda;Kloss;", university_db.getBySurnames());
}

TEST_F(univeristyDBFixture, ClearDB)
{
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

	employee_1->m_name = "Zenek";
	employee_1->m_surname = "Duda";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("61012658203");

	employee_2->m_name = "Patryk";
	employee_2->m_surname = "Nijaki";
	employee_2->m_address = "Stetinstrasse 77 Berlin";
	employee_2->m_salary = 1002;
	employee_2->m_gender = gender::male;
	employee_2->m_pesel.set("26110479026");

	university_db.addStudent(student_2);
	university_db.addStudent(student_1);
	university_db.addEmployee(employee_1);
	university_db.addEmployee(employee_2);

	pesel1 = student_1->m_pesel;
	pesel2 = student_2->m_pesel;
	pesel3 = employee_1->m_pesel;
	pesel4 = employee_2->m_pesel;

	EXPECT_TRUE(university_db.Search(pesel1));
	EXPECT_TRUE(university_db.Search(pesel2));
	EXPECT_TRUE(university_db.Search(pesel3));
	EXPECT_TRUE(university_db.Search(pesel4));

	university_db.Clear();

	EXPECT_FALSE(university_db.Search(pesel1));
	EXPECT_FALSE(university_db.Search(pesel2));
	EXPECT_FALSE(university_db.Search(pesel3));
	EXPECT_FALSE(university_db.Search(pesel4));

	fake.set("791204054565");
	EXPECT_FALSE(university_db.Search(fake));
}

TEST_F(univeristyDBFixture, LoadFromFile)
{
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

	university_db.addStudent(student_2);
	university_db.addStudent(student_1);
	university_db.addStudent(student_3);

	std::string before = university_db.getBySurnames();

	university_db.saveToFile();

	university_db.Clear();

	EXPECT_TRUE(university_db.readFromFile());
	EXPECT_TRUE(true, university_db.Search("Brunner"));
	EXPECT_TRUE(true, university_db.Search("Kloss"));
	EXPECT_TRUE(true, university_db.Search("Dolas"));

	std::string after = university_db.getBySurnames();

	EXPECT_EQ(before, after);
}

TEST_F(univeristyDBFixture, SaveTOFile)
{
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

	employee_1->m_name = "Franek";
	employee_1->m_surname = "Duda";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("61012658203");

	employee_3->m_name = "Hans";
	employee_3->m_surname = "Blok";
	employee_3->m_address = "Stetinstrasse 77 Berlin";
	employee_3->m_salary = 1002;
	employee_3->m_gender = gender::male;
	employee_3->m_pesel.set("26110479026");

	employee_4->m_name = "Aliena";
	employee_4->m_surname = "Shire";
	employee_4->m_address = "Mainroad 11 Kingsbridge";
	employee_4->m_salary = 0;
	employee_4->m_gender = gender::female;
	employee_4->m_pesel.set("19291285511");

	university_db.addStudent(student_2);
	university_db.addStudent(student_1);
	university_db.addStudent(student_3);
	university_db.addEmployee(employee_1);
	university_db.addEmployee(employee_3);
	university_db.addEmployee(employee_4);

	EXPECT_TRUE(university_db.saveToFile());
}