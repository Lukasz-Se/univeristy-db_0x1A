#include "pch.h"
#include "../Headers/pesel.h"
#include "../Headers/db.h"
#include "../Headers/PersonsGenerator.h"

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

	db cut;
};

class PersonsGeneratorFixture : public ::testing::Test
{
protected:
	std::string maleNames = "../../../data/male_names.txt";
	std::string maleSurnames = "../../../data/male_surnames.txt";
	std::string femaleNames = "../../../data/female_names.txt";
	std::string femaleSurnames = "../../../data/female_surnames.txt";
	std::string streets = "../../../data/streets_names.txt";
	std::string cities = "../../../data/towns_names.txt";

	PersonsGenerator cut;
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

	EXPECT_TRUE(cut.addStudent(student_1));
	EXPECT_FALSE(cut.addStudent(student_2));
	EXPECT_TRUE(cut.addStudent(student_3));
	EXPECT_FALSE(cut.addStudent(student_1));
	EXPECT_FALSE(cut.addStudent(student_3));
	EXPECT_FALSE(cut.addStudent(student_4));
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

	EXPECT_TRUE(cut.addEmployee(employee_1));
	EXPECT_FALSE(cut.addEmployee(employee_2));
	EXPECT_TRUE(cut.addEmployee(employee_3));
	EXPECT_FALSE(cut.addEmployee(employee_1));
	EXPECT_FALSE(cut.addEmployee(employee_2));
	EXPECT_FALSE(cut.addEmployee(employee_4));
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

	EXPECT_TRUE(cut.addEmployee(employee_1));
	EXPECT_FALSE(cut.addEmployee(employee_2));
	EXPECT_TRUE(cut.addEmployee(employee_3));
	EXPECT_FALSE(cut.addEmployee(employee_1));
	EXPECT_FALSE(cut.addEmployee(employee_2));
	EXPECT_FALSE(cut.addEmployee(employee_4));

	EXPECT_TRUE(cut.addStudent(student_1));
	EXPECT_FALSE(cut.addStudent(student_2));
	EXPECT_TRUE(cut.addStudent(student_3));
	EXPECT_FALSE(cut.addStudent(student_1));
	EXPECT_FALSE(cut.addStudent(student_3));
	EXPECT_FALSE(cut.addStudent(student_4));
}

TEST_F(univeristyDBFixture, SearchPersonByPesel)
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

	cut.addStudent(student_1);
	cut.addEmployee(employee_1);
	cut.addStudent(student_2);
	cut.addEmployee(employee_2);

	pesel1.set(student_1->m_pesel.getPesel());
	pesel2.set(student_2->m_pesel.getPesel());
	pesel3.set(employee_1->m_pesel.getPesel());
	pesel4.set(employee_2->m_pesel.getPesel());
	fake.set("791204054565");

	EXPECT_EQ(true, cut.Search(pesel1));
	EXPECT_EQ(true, cut.Search(pesel2));
	EXPECT_NE(true, cut.Search(fake));
	EXPECT_EQ(true, cut.Search(pesel3));
	EXPECT_EQ(true, cut.Search(pesel4));
}

TEST_F(univeristyDBFixture, SearchPersonBySurname)
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

	cut.addStudent(student_1);
	cut.addEmployee(employee_1);
	cut.addStudent(student_2);
	cut.addEmployee(employee_2);

	EXPECT_EQ(true, cut.Search("Dolas"));
	EXPECT_EQ(true, cut.Search("Nijaki"));
	EXPECT_NE(true, cut.Search("Dolar"));
	EXPECT_EQ(true, cut.Search("Kloss"));
	EXPECT_EQ(true, cut.Search("Duda"));
}

TEST_F(univeristyDBFixture, SearchPersonByPeselWithIterator)
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

	cut.addStudent(student_1);
	cut.addEmployee(employee_1);
	cut.addStudent(student_2);
	cut.addEmployee(employee_2);

	pesel1.set(student_1->m_pesel.getPesel());
	pesel2.set(student_2->m_pesel.getPesel());
	pesel3.set(employee_1->m_pesel.getPesel());
	fake.set("791204054565");

	std::vector<Person*>::iterator it;

	cut.Search(pesel1, it);
	EXPECT_EQ(it.operator*()->m_surname, "Dolas");

	cut.Search(pesel3, it);
	EXPECT_EQ(it.operator*()->m_surname, "Duda");
	EXPECT_NE(it.operator*()->m_surname, "Duda2");
}

TEST_F(univeristyDBFixture, SearchPersonBySurameWithIterator)
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

	cut.addStudent(student_1);
	cut.addEmployee(employee_1);
	cut.addStudent(student_2);
	cut.addEmployee(employee_2);

	std::vector<Person*>::iterator it;

	cut.Search("Dolas", it);
	EXPECT_EQ(it.operator*()->m_surname, "Dolas");

	cut.Search("Duda", it);
	EXPECT_EQ(it.operator*()->m_surname, "Duda");
	EXPECT_NE(it.operator*()->m_surname, "Duda2");

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

	cut.addStudent(student_1);
	cut.addStudent(student_2);

	EXPECT_FALSE(cut.RemovePerson(1005));
	EXPECT_TRUE(cut.RemovePerson(student_1->m_indeks_number));
	EXPECT_FALSE(cut.Search("Dolas"));
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

	cut.addStudent(student_1);
	cut.addEmployee(employee_1);
	cut.addStudent(student_2);
	cut.addEmployee(employee_2);

	cut.RemovePerson(student_1->m_pesel);
	cut.RemovePerson(employee_2->m_pesel);
	EXPECT_FALSE(cut.Search("Dolas"));
	EXPECT_FALSE(cut.Search("Nijaki"));
}

TEST_F(univeristyDBFixture, PrintDB)
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

	cut.addStudent(student_1);
	cut.addStudent(student_2);

	std::string expected = "Franek;Dolas;\nHans;Kloss;\n";

	EXPECT_EQ(cut.getDB(), expected);
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

	cut.addStudent(student_1);
	cut.addStudent(student_2);
	cut.addStudent(student_3);
	cut.addEmployee(employee_1);
	cut.addEmployee(employee_2);

	cut.SortByPesel();
	EXPECT_EQ("Kloss;Nijaki;Dolas;Duda;Brunner;", cut.getBySurnames());
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

	cut.addStudent(student_2);
	cut.addStudent(student_1);
	cut.addStudent(student_3);
	cut.addEmployee(employee_1);
	cut.addEmployee(employee_2);
	cut.addEmployee(employee_3);

	cut.SortBySurname();
	
	EXPECT_EQ("Brunner;Dolas;Duda;Kloss;Kloss;Nijaki;", cut.getBySurnames());
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

	cut.addStudent(student_2);
	cut.addStudent(student_1);
	cut.addStudent(student_3);
	cut.addEmployee(employee_1);
	cut.addEmployee(employee_2);
	cut.addEmployee(employee_3);

	cut.SortBySalary();
	
	EXPECT_EQ("Kloss;Dolas;Brunner;Nijaki;Duda;Kloss;", cut.getBySurnames());
}

//TEST_F(univeristyDBFixture, FillDBWithArtificalData)
//{
//	EXPECT_STRNE("", university_db.getBySurnames().c_str());
//}

TEST_F(univeristyDBFixture, ModyfiEarnings)
{
	employee_1->m_name = "Zenek";
	employee_1->m_surname = "Duda";
	employee_1->m_address = "Chsz¹szcze Rzewoszyce pow. £êko³ody 50-500 Stalowa Wola";
	employee_1->m_salary = 1500;
	employee_1->m_gender = gender::male;
	employee_1->m_pesel.set("61012658203");

	cut.addEmployee(employee_1);

	cut.ChangeSalary(employee_1->m_pesel, 2200);

	std::vector<Person*>::iterator it;
	cut.Search("Duda", it);
	
	auto cut = dynamic_cast<Employee*>(it.operator*());
	EXPECT_EQ(cut->m_salary, 2200);
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

	cut.addStudent(student_2);
	cut.addStudent(student_1);
	cut.addEmployee(employee_1);
	cut.addEmployee(employee_2);

	pesel1 = student_1->m_pesel;
	pesel2 = student_2->m_pesel;
	pesel3 = employee_1->m_pesel;
	pesel4 = employee_2->m_pesel;

	EXPECT_TRUE(cut.Search(pesel1));
	EXPECT_TRUE(cut.Search(pesel2));
	EXPECT_TRUE(cut.Search(pesel3));
	EXPECT_TRUE(cut.Search(pesel4));

	cut.ClearDB();

	EXPECT_FALSE(cut.Search(pesel1));
	EXPECT_FALSE(cut.Search(pesel2));
	EXPECT_FALSE(cut.Search(pesel3));
	EXPECT_FALSE(cut.Search(pesel4));

	fake.set("791204054565");
	EXPECT_FALSE(cut.Search(fake));
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

	cut.addStudent(student_2);
	cut.addStudent(student_1);
	cut.addStudent(student_3);
	cut.addEmployee(employee_1);
	cut.addEmployee(employee_2);

	std::string before = cut.getBySurnames();

	cut.saveToFile();

	cut.ClearDB();

	EXPECT_TRUE(cut.readFromFile());
	EXPECT_TRUE(cut.Search("Brunner"));
	EXPECT_TRUE(cut.Search("Kloss"));
	EXPECT_TRUE(cut.Search("Dolas"));
	EXPECT_TRUE(cut.Search("Duda"));
	EXPECT_TRUE(cut.Search("Nijaki"));
	EXPECT_FALSE(cut.Search("Kierwinski"));

	std::string after = cut.getBySurnames();

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

	cut.addStudent(student_2);
	cut.addStudent(student_1);
	cut.addStudent(student_3);
	cut.addEmployee(employee_1);
	cut.addEmployee(employee_3);
	cut.addEmployee(employee_4);

	EXPECT_TRUE(cut.saveToFile());
}

TEST_F(PersonsGeneratorFixture, OpenFile)
{
	std::vector<std::string> buffer;
	EXPECT_TRUE(cut.LoadFromFile(maleNames, buffer));
}

TEST_F(PersonsGeneratorFixture, ValidationOfLoadSize)
{
	std::vector<std::string> buffer;
	cut.LoadFromFile(maleNames, buffer);
	EXPECT_EQ(buffer.size(), 188);
}

TEST_F(PersonsGeneratorFixture, ValidationOfLoadContent)
{
	std::vector<std::string> buffer;
	cut.LoadFromFile(maleNames, buffer);
	EXPECT_EQ(buffer[0], "Abraham");
	EXPECT_EQ(buffer[1], "Adam");
	EXPECT_EQ(buffer[95], "Kajetan");
	EXPECT_EQ(buffer[186], "Zygmunt");
}