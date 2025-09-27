#pragma once

#include <random>
#include <chrono>
#include "pesel.h"

class PeselGenerator
{
public:
	std::string GeneratePesel(unsigned short int start_day = 1, unsigned short int start_month = 1, unsigned short int start_year = 1901,
		unsigned short int end_day = 31, unsigned short int end_month = 12, unsigned short int end_year = 2024, int sex = 99);

private:
	int GenerateRandomValue(int maxValue);
	std::string ParseBDate(std::chrono::year_month_day bDate);
	std::string ComplementDigitsTo(int serial, int complementTo = 3, char complementWith = '0');

	const unsigned short int default_start_day = 1;
	const unsigned short int default_start_month = 1;
	const unsigned short int default_start_year = 1901;
	const unsigned short int default_end_day = 31;
	const unsigned short int default_end_month = 12;
	const unsigned short int default_end_year = 2024;
};

