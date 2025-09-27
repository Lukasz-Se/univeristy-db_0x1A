#pragma once

#include "Person.h"

class Employee : public Person
{
public:
    Employee() = default;
    Employee(const std::string& name, const std::string& surname, const std::string& address, const gender& gender, const pesel& pesel, unsigned short int salary);
    Employee(const std::vector<std::string>& inputData);
    virtual std::string getData();

    unsigned short int m_salary;
};