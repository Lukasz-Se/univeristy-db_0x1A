#include "Headers/PersonsGenerator.h"

PersonsGenerator::PersonsGenerator(const std::string& maleNames, const std::string& maleSurnames, const std::string& femaleNames, 
	const std::string& femaleSurnames, const std::string& streets, const std::string& towns_names)
{
	LoadFromFile(maleNames, vMaleNames);
	LoadFromFile(maleSurnames, vMaleSurnames);
	LoadFromFile(femaleNames, vFemaleNames);
	LoadFromFile(femaleSurnames, vFemaleSurnames);
	LoadFromFile(streets, vStreets);
	LoadFromFile(towns_names, vCities);
}

bool PersonsGenerator::Generate(unsigned int numberOfPersons, std::vector<Person*>& output)
{
	for (unsigned int i = 0; i < numberOfPersons; i++)
	{
		PeselGenerator pg;

		unsigned short int type = GenerateRandomValue(1, 3);
		Person* pPerson;

		if (type == 1)
		{
			pPerson = new Employee;
			dynamic_cast<Employee*>(pPerson)->m_salary = GenerateRandomValue(1000, 15000);
		}
		else if (type > 1)
		{
			pPerson = new Student;
			dynamic_cast<Student*>(pPerson)->m_indeks_number = GenerateRandomValue(1, 9999);
		}

		unsigned short int sex = GenerateRandomValue(0,2);
		if (sex == 0)
		{
			pPerson->m_name = RandomStringItem(vFemaleNames);
			pPerson->m_surname = RandomStringItem(vFemaleSurnames);
			pPerson->m_gender = gender::female;
		}
		else if (sex != 0)
		{
			pPerson->m_name = RandomStringItem(vMaleNames);
			pPerson->m_surname = RandomStringItem(vMaleSurnames);
			pPerson->m_gender = gender::male;
		}

		pPerson->m_address = RandomStringItem(vStreets) + " " + std::to_string(GenerateRandomValue(1, 199)) + " " + RandomStringItem(vCities);
		pPerson->m_pesel.set(pg.GeneratePesel(1, 1, 1945, 31, 12, 2024, sex));

		output.push_back(pPerson);		
	}
	return true;
}

bool PersonsGenerator::LoadFromFile(const std::string& file, std::vector<std::string>& output)
{
	std::ifstream fd(file, std::ios::in);

	if (fd.is_open())
	{
		std::string buffor;

		while (std::getline(fd, buffor, '\n'))
			output.push_back(buffor);

		return true;
	}
	return false;
}

std::string PersonsGenerator::RandomStringItem(const std::vector<std::string>& input_list)
{
	return input_list.at(GenerateRandomValue(0, input_list.size() - 1));
}

int PersonsGenerator::GenerateRandomValue(const unsigned int minValue, const unsigned int maxValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(minValue, maxValue);

	return dis(gen);
}