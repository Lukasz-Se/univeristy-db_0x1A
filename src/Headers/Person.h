#pragma once
#include "pesel.h"

enum class gender
{
    male,
    female
};

class Person
{
public:
    std::string m_name;
    std::string m_surname;
    std::string m_address;
    pesel m_pesel;
    gender m_gender;

    virtual std::string getData() = 0;
};