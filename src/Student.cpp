#include "Headers/Student.h"
#include <sstream>

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
    std::string gender_str;
    if (m_gender == gender::male)
        gender_str = "male";
    else
        gender_str = "female";

    output << "s;" << m_name << ";" << m_surname << ";" << m_address << ";" << gender_str << ";" << m_pesel.getPesel() << ";" << m_indeks_number << ";";

    return output.str();
}