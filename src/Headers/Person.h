#pragma once
#include "pesel.h"
#include <sstream>

enum class gender
{
    male,
    female,
};

class Person
{
public:
    Person() = default;
    Person(const std::vector<std::string>& inputData);
    virtual std::string getData();

    std::string m_name;
    std::string m_surname;
    std::string m_address;
    pesel m_pesel;
    gender m_gender;    
};