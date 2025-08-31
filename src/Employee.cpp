#include "Headers/Employee.h"
#include <sstream>

std::string Employee::getData()
{
    std::stringstream output;
    std::string gender_str;
    if (m_gender == gender::male)
        gender_str = "male";
    else
        gender_str = "female";

    output << m_name << ";" << m_surname << ";" << m_address << ";" << gender_str << ";" << m_pesel.getPesel() << ";" << m_salary << ";";

    return output.str();
}
