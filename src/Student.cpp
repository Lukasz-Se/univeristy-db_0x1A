#include "Headers/Student.h"

Student::Student(const std::string& name, const std::string& surname, const std::string& address, const gender& gender, const pesel& pesel, unsigned short int indexNumber) :
    Person(std::vector<std::string>{name, surname, address, (gender == gender::male) ? "male" : "female", pesel.getPesel()})
{
    m_indeks_number = indexNumber;
}

Student::Student(std::vector<std::string> inputData) : Person(inputData)
{
    m_indeks_number = stoi(inputData[6]);
}

std::string Student::getData()
{
    std::stringstream output;
    output << "s;" << Person::getData() << std::to_string(m_indeks_number) << ";";
 
    return output.str();
}