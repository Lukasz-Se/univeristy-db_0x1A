#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "Student.h"
#include "Employee.h"

class PersonsGenerator
{
public:
	//PersonsGenerator(std::string maleNames = "../../data/male_names.txt", std::string maleSurnames = "../../data/male_surnames.txt", 
	//				 std::string femaleNames = "../../data/female_names.txt", std::string femaleSurnames = "../../data/female_surnames.txt", 
	//				 std::string streets = "../../data/streets_names.txt", std::string cities = "../../data/cities.txt");

	std::vector<Person*> Generate(unsigned int numberOfPersons);

	std::vector<std::string> maleNames;
	std::vector<std::string> maleSurnames;
	std::vector<std::string> femaleNames;
	std::vector<std::string> femaleSurnames;
	std::vector<std::string> streets;
	std::vector<std::string> cities;

	bool LoadFromFile(const std::string& file, std::vector<std::string>& output);
};