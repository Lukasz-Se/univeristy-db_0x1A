#include "Headers/Employee.h"
#include <sstream>

Employee::Employee(const std::string& name, const std::string& surname, const std::string& address, const gender& gender, const pesel& pesel, unsigned short int salary) :
    Person(std::vector<std::string>{name, surname, address, (gender == gender::male)? "male" : "female", pesel.getPesel()})
{
    m_salary = salary;
}

Employee::Employee(const std::vector<std::string>& inputData) : Person(inputData)
{
    m_salary = stoi(inputData[6]);
}

std::string Employee::getData()
{
    std::stringstream output;
    std::string gender_str;
    if (m_gender == gender::male)
        gender_str = "male";
    else
        gender_str = "female";

    output << "e;" << m_name << ";" << m_surname << ";" << m_address << ";" << gender_str << ";" << m_pesel.getPesel() << ";" << m_salary << ";";

    return output.str();
}
