#pragma once
#include "pesel.h"

enum class gender
{
    male,
    female,
};

class Person
{
public:
    Person(const std::vector<std::string>& inputData);
    virtual std::string getData() = 0;

    std::string m_name;
    std::string m_surname;
    std::string m_address;
    pesel m_pesel;
    gender m_gender;    
};