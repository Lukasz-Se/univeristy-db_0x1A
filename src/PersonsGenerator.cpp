#include "Headers/PersonsGenerator.h"

//PersonsGenerator::PersonsGenerator(std::string maleNames, std::string maleSurnames, std::string femaleNames, std::string femaleSurnames, std::string streets)
//{
//
//}

std::vector<Person*> PersonsGenerator::Generate(unsigned int numberOfPersons)
{
	return std::vector<Person*>();
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
