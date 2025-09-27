#include "Headers/Person.h"

Person::Person(const std::vector<std::string>& inputData)
{
    m_name = inputData[1];
    m_surname = inputData[2];
    m_address = inputData[3];

    if (inputData[4] == "male")
        m_gender = gender::male;
    else if (inputData[4] == "female")
        m_gender = gender::female;

    m_pesel.set(inputData[5]);
}

std::string Person::getData()
{
    std::stringstream output;
    std::string gender_str;
    if (m_gender == gender::male)
        gender_str = "male";
    else
        gender_str = "female";

    output << m_name << ";" << m_surname << ";" << m_address << ";" << gender_str << ";" << m_pesel.getPesel() << ";";

    return output.str();
}