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

bool db::Search(std::string surname)
{	
	auto result = std::find_if(begin(m_Students), end(m_Students), [surname](Student* student) {return student->m_surname == surname; });
	if (result != m_Students.end())
		return true;

	return false;
}

bool db::Search(pesel pesel)
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

std::string db::getStudentsSurnames()
{
	std::string output;
	for (auto student : m_Students)
		output.append(student->m_surname + ';');

	return output;
}

bool db::alreadyExist(pesel pesel)
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
	std::ofstream fd(file, std::ios::out | std::ios::binary);
	if (fd)
	{
		for (auto student : m_Students)
		{
			fd.write((char*)&student->m_name, sizeof(student->m_name));
			fd.write((char*)&student->m_surname, sizeof(student->m_surname));
			fd.write((char*)&student->m_address, sizeof(student->m_address));
			fd.write((char*)&student->m_pesel.getPesel(), sizeof(student->m_pesel.getPesel()));
			fd.write((char*)&student->m_gender, sizeof(student->m_gender));
			fd.write((char*)&student->m_indeks_number, sizeof(student->m_indeks_number));
		}
		fd.close();

		return true;
	}

	return false;
}

bool db::readFromFile(std::string file)
{
	return false;
}
