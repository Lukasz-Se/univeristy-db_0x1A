#include "Headers/db.h"

db::~db()
{
	Clear();
}

bool db::addStudent(Student* studentInput)
{

	if (alreadyExist(studentInput->m_pesel) || studentInput->m_pesel.getPesel() == "")
		return false;

	m_Persons.push_back(studentInput);
	return true;
}

bool db::addEmployee(Employee* employeeInput)
{
	if (alreadyExist(employeeInput->m_pesel) || employeeInput->m_pesel.getPesel() == "" || employeeInput->m_salary == 0)
		return false;

	m_Persons.push_back(employeeInput);
	return true;
}

bool db::Search(const std::string& surname) const
{	
	auto result = std::find_if(begin(m_Persons), end(m_Persons), [surname](Person* student) {return student->m_surname == surname; });
	if (result != m_Persons.end())
		return true;

	return false;
}

bool db::Search(const pesel& pesel) const
{
	return alreadyExist(pesel);
}

void db::SortByPesel()
{
	std::sort(begin(m_Persons), end(m_Persons), [](Person* first, Person* second) {return first->m_pesel.getPesel() < second->m_pesel.getPesel(); });
}

void db::SortBySurname()
{
	std::sort(begin(m_Persons), end(m_Persons), [](Person* first, Person* second) {return first->m_surname < second->m_surname; });
}

bool db::removeStudent(unsigned int indexNr)
{
	Student* p_tempStudentPtr = nullptr;
	auto result = std::find_if(begin(m_Persons), end(m_Persons), [indexNr, p_tempStudentPtr](Person* student) mutable{
		p_tempStudentPtr = dynamic_cast<Student*>(student);
		return p_tempStudentPtr->m_indeks_number == indexNr; }
	);
	
	if (result != m_Persons.end())
	{
		delete p_tempStudentPtr;
		m_Persons.erase(result);
		return true;
	}

	return false;
}

std::string db::getStudentsSurnames() const
{
	std::string output;
	for (auto student : m_Persons)
		output.append(student->m_surname + ';');

	return output;
}

std::string db::getDB()
{
	std::string output;
	
	for (int i = 0; i < m_Persons.size(); i++)
	{
		output.append(m_Persons[i]->m_name + ';' + m_Persons[i]->m_surname + ";\n");
	}

	return output;
}

bool db::alreadyExist(const pesel pesel) const 
{
	if (pesel.getPesel() != "")
		if (std::any_of(begin(m_Persons), end(m_Persons), [pesel](Person* pPerson) {return pPerson->m_pesel.getPesel() == pesel.getPesel(); }))
			return true;
	return false;
}
void db::Clear()
{
	std::for_each(begin(m_Persons), end(m_Persons), [](Person* pPerson) {
		delete pPerson;
		});

	m_Persons.clear();
}

bool db::saveToFile(std::string file)
{
	std::ofstream fd(file, std::ios::out | std::ios::trunc);
	if (fd)
	{
		for (auto pearson : m_Persons)
		{
		
			fd << pearson->m_name << "\n";
			fd << pearson->m_surname << "\n";
			fd << pearson->m_address << "\n";
			fd << pearson->m_pesel.getPesel() << "\n";
			//if (dynamic_cast<Student*>(pearson))
		}
		return true;
	}
	return false;
}

bool db::readFromFile(std::string file)
{
	std::ifstream fd(file, std::ios::in);
	
	if (fd.is_open())
	{
		std::string buffor;
		Student* pTempStudent = new Student;

		int value = 0;
		while (!std::getline(fd, buffor, '\n').eof())
		{
			if (value == 0)
				pTempStudent->m_name = buffor;
			else if (value == 1)
				pTempStudent->m_surname = buffor;
			else if (value == 2)
				pTempStudent->m_address = buffor;
			else if (value == 3)
				pTempStudent->m_pesel.set(buffor);
			else if (value == 4)
				pTempStudent->m_indeks_number = stoi(buffor);

			value++;

			if (value > 4)
			{
				value = 0;
				addStudent(pTempStudent);
				pTempStudent = new Student;
			}
		}
		return true;
	}
	return false;
}
