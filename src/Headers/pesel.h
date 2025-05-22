#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <set>

#include "peselBirthDateParser.h"

enum class pesel_error {
	OK = 0,
	WRONG_LENGTH,
	WRONG_BDAY_FORMAT,
	NON_DIGITS,
	CHECKSUM_ERROR
};

class pesel
{
public:
	pesel_error set(const std::string& pesel);
	std::string getPesel() const;
	
	
protected:
	std::string m_pesel;
	peselBirthDateParser BirthDateParser;

	pesel_error verify(const std::string& pesel);
};

