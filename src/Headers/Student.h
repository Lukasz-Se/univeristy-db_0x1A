#pragma once
#include <iostream>
#include "pesel.h"

enum class gender
{
    male,
    female
};

struct Student
{
    std::string m_name;
    std::string m_surname;
    std::string m_address;
    unsigned short int m_indeks_number;
    pesel m_pesel;
    gender m_gender;
};

