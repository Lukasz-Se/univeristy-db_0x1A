#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <set>

class peselBirthDateParser
{
public:
	peselBirthDateParser();
	bool verifyBrirthDateFormat(const std::string& birthdate);

private:
	std::set<int> m_months;

	bool verifyBirthMonth(unsigned short int month);
	bool verifyBirthDay(unsigned short int day);
};

