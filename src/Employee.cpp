#include "Headers/Employee.h"

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
    output << "e;" << Person::getData() << std::to_string(m_salary) << ";";

    return output.str();
}
