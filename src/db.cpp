#include "Headers/db.h"

db::~db()
{
	Clear();
}

bool db::addStudent(Student* studentInput)
{

	if (alreadyExist(studentInput->m_pesel) || studentInput->m_pesel.getPesel() == "")
		return false;

	m_Students.push_back(studentInput);
	return true;
}

bool db::Search(const std::string& surname) const
{	
	auto result = std::find_if(begin(m_Students), end(m_Students), [surname](Student* student) {return student->m_surname == surname; });
	if (result != m_Students.end())
		return true;

	return false;
}

bool db::Search(const pesel& pesel) const
{
	return alreadyExist(pesel);
}

void db::SortByPesel()
{
	std::sort(begin(m_Students), end(m_Students), [](Student* first, Student* second) {return first->m_pesel.getPesel() < second->m_pesel.getPesel(); });
}

void db::SortBySurname()
{
	std::sort(begin(m_Students), end(m_Students), [](Student* first, Student* second) {return first->m_surname < second->m_surname; });
}

bool db::removeStudent(unsigned int indexNr)
{
	Student* p_tempStudentPtr = nullptr;
	auto result = std::find_if(begin(m_Students), end(m_Students), [indexNr, p_tempStudentPtr](Student* student) mutable{
		p_tempStudentPtr = student;
		return student->m_indeks_number == indexNr; }
	);

	if (result != m_Students.end())
	{
		delete p_tempStudentPtr;
		m_Students.erase(result);
		return true;
	}

	return false;
}

std::string db::getStudentsSurnames() const
{
	std::string output;
	for (auto student : m_Students)
		output.append(student->m_surname + ';');

	return output;
}

bool db::alreadyExist(const pesel pesel) const 
{
	if (pesel.getPesel() != "")
		if (std::any_of(begin(m_Students), end(m_Students), [pesel](Student* student) {return student->m_pesel.getPesel() == pesel.getPesel(); }))
			return true;
	return false;
}
void db::Clear()
{
	std::for_each(begin(m_Students), end(m_Students), [](Student* pStudent) {
		delete pStudent;
		});

	m_Students.clear();
}

bool db::saveToFile(std::string file)
{
	std::ofstream fd(file, std::ios::out | std::ios::trunc);
	if (fd)
	{
		for (auto student : m_Students)
		{
		
			fd << student->m_name << "\n";
			fd << student->m_surname << "\n";
			fd << student->m_address << "\n";
			fd << student->m_pesel.getPesel() << "\n";
			fd << student->m_indeks_number << "\n";
		}
		return true;
	}
	return false;
}

bool db::readFromFile(std::string file)
{
	std::ifstream fd(file, std::ios::in);
	Student* pTempStudent = new Student;
	std::string mPesel;
	std::string mIndeksNumber;
	
	std::array<std::string*, 5> fileds = { &pTempStudent->m_name, &pTempStudent->m_surname, &pTempStudent->m_address, &mPesel, &mIndeksNumber };

	if (fd.is_open())
	{
		std::string buffor;
		Student* pTempStudent = new Student;

		int value = 0;
		while (!std::getline(fd, buffor, '\n').eof())
		{
			*fileds.at(value) = buffor;
			value++;
			if (value > 4)
				value = 0;
		}
		return true;
	}
	return false;
}
