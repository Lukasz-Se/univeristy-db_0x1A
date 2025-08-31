#pragma once

#include "Person.h"

class Employee : public Person
{
public:
    unsigned short int m_salary;

    virtual std::string getData();
};