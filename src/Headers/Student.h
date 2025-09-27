#pragma once
#include "Person.h"


class Student : public Person
{   
public:
    Student(const std::string& name, const std::string& surname, const std::string& address, const gender& gender, const pesel& pesel, unsigned short int indexNumber);
    Student(std::vector <std::string> inputData);
    unsigned short int m_indeks_number;

    virtual std::string getData();
};

