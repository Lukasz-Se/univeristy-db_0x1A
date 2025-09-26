#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include "PeselGenerator.h"
#include "Student.h"
#include "Employee.h"

class PersonsGenerator
{
public:
	PersonsGenerator(std::string maleNames = "../../../data/male_names.txt", std::string maleSurnames = "../../../data/male_surnames.txt", 
					 std::string femaleNames = "../../../data/female_names.txt", std::string femaleSurnames = "../../../data/female_surnames.txt", 
					 std::string streets = "../../../data/streets_names.txt", std::string towns_names = "../../../data/towns_names.txt");

	bool Generate(unsigned int numberOfPersons, std::vector<Person*>& output);

	std::vector<std::string> vMaleNames;
	std::vector<std::string> vMaleSurnames;
	std::vector<std::string> vFemaleNames;
	std::vector<std::string> vFemaleSurnames;
	std::vector<std::string> vStreets;
	std::vector<std::string> vCities;
	
	bool LoadFromFile(const std::string& file, std::vector<std::string>& output);
	std::string RandomStringItem(const std::vector<std::string>& input_list);
	int GenerateRandomValue(const unsigned int minValue, const unsigned int maxValue);
};