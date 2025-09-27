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
