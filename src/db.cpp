#include "Headers/db.h"

std::vector<Person*> db::m_Persons;

db::~db()
{
	ClearDB();
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

bool db::Search(const std::string& surname, std::vector<Person*>::iterator& returnValue)
{
	auto result = std::find_if(begin(m_Persons), end(m_Persons), [surname](Person* person){
		return person->m_surname == surname;
		});

	if (result != m_Persons.end())
	{
		returnValue = result;
		return true;
	}

	return false;
}

bool db::Search(const pesel& pesel, std::vector<Person*>::iterator& returnValue)
{
	if (pesel.getPesel() != "")
	{
		auto result = std::find_if(begin(m_Persons), end(m_Persons), [pesel](Person* pPerson) {
			return pPerson->m_pesel.getPesel() == pesel.getPesel();
			});

		if (result != m_Persons.end())
		{
			returnValue = result;
			return true;
		}
	}
	return false;
}

void db::SortByPesel()
{
	std::sort(begin(m_Persons), end(m_Persons), [](Person* first, Person* second) {return first->m_pesel.getPesel() < second->m_pesel.getPesel(); });
}

void db::SortBySurname()
{
	std::sort(begin(m_Persons), end(m_Persons), [](Person* first, Person* second) {return first->m_surname < second->m_surname; });
}

void db::SortBySalary()
{
	std::sort(begin(m_Persons), end(m_Persons), [](Person* first, Person* second) 
		{
			if (dynamic_cast<Employee*>(first) && dynamic_cast<Employee*>(second)) 
				return static_cast<Employee*>(first)->m_salary < static_cast<Employee*>(second)->m_salary; 
		});
}

bool db::ChangeSalary(const pesel& pesel, unsigned int new_salary)
{
	std::vector<Person*>::iterator it;
	if (Search(pesel, it) && dynamic_cast<Employee*>(it.operator*()))
	{
		dynamic_cast<Employee*>(it.operator*())->m_salary = new_salary;
		return true;
	}
	
	return false;
}

bool db::RemovePerson(unsigned int indexNr)
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

bool db::RemovePerson(pesel& pesel)
{
	Person* p_tempPersonPtr = nullptr;
	auto result = std::find_if(begin(m_Persons), end(m_Persons), [pesel, p_tempPersonPtr](Person* person) mutable {
		p_tempPersonPtr = person;
		return p_tempPersonPtr->m_pesel.getPesel() == pesel.getPesel(); }
	);

	if (result != m_Persons.end())
	{
		delete p_tempPersonPtr;
		m_Persons.erase(result);
		return true;
	}

	return false;
}

std::string db::getBySurnames() const
{
	std::string output;
	for (auto student : m_Persons)
		output.append(student->m_surname + ';');

	return output;
}

std::string db::getDB() const
{
	std::string output;
	
	for (int i = 0; i < m_Persons.size(); i++)
	{
		output.append(m_Persons[i]->m_name + ';' + m_Persons[i]->m_surname + ";\n");
	}

	return output;
}

void db::ClearDB()
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
			fd << pearson->getData();
			fd << "\n";
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
		std::string buffor, line;
		std::vector <std::string> properties;
	
		while (std::getline(fd, buffor, '\n'))
		{		
			std::stringstream ss(buffor);
			while (std::getline(ss, line, ';'))
			{
				properties.push_back(line);
			}

			if (properties[0] == "s")
			{
				Student* temp = new Student;
				CreatePersonObject(temp, properties);
			}
			if (properties[0] == "e")
			{
				Employee* temp = new Employee;
				CreatePersonObject(temp, properties);
			}

			properties.clear();
		}
		
		return true;
	}
	return false;
}

bool db::alreadyExist(const pesel& pesel) const
{
	if (pesel.getPesel() != "")
		if (std::any_of(begin(m_Persons), end(m_Persons), [pesel](Person* pPerson) {return pPerson->m_pesel.getPesel() == pesel.getPesel(); }))
			return true;
	return false;
}

void db::CreatePersonObject(Person* pPerson, std::vector<std::string> data)
{
	pPerson->m_name = data[1];
	pPerson->m_surname = data[2];
	pPerson->m_address = data[3];

	if (data[4] == "male")
		pPerson->m_gender = gender::male;
	else if (data[4] == "female")
		pPerson->m_gender = gender::female;

	pPerson->m_pesel.set(data[5]);

	if (data[0] == "s")
	{
		dynamic_cast<Student*>(pPerson)->m_indeks_number = std::stoi(data[6]);
		m_Persons.push_back(dynamic_cast<Student*>(pPerson));
	}
	else if (data[0] == "e")
	{
		dynamic_cast<Employee*>(pPerson)->m_salary = std::stoi(data[6]);
		m_Persons.push_back(dynamic_cast<Employee*>(pPerson));
	}
}