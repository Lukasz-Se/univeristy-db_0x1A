#include "Headers/peselBirthDateParser.h"

peselBirthDateParser::peselBirthDateParser()
{
    int m_counter = 0;
    for (int i = 1; i <= 92; i++)
    {
        m_months.emplace(i);
        m_counter++;
        if (m_counter == 12)
        {
            m_counter = 0;
            i += 8;
        }
    }
}

bool peselBirthDateParser::verifyBrirthDateFormat(const std::string& birthdate)
{
    std::string m_temp;
    std::copy_n(begin(birthdate) + 2, 2, std::back_inserter(m_temp));
    int m_month = stoi(m_temp);

    m_temp.clear();
    std::copy_n(begin(birthdate) + 4, 2, std::back_inserter(m_temp));
    int m_day = stoi(m_temp);

    if (verifyBirthMonth(m_month) && verifyBirthDay(m_day))
        return true;

    return false;
}

bool peselBirthDateParser::verifyBirthMonth(unsigned short int month)
{
    if (m_months.find(month) != m_months.end())
        return true;

    return false;
}

bool peselBirthDateParser::verifyBirthDay(unsigned short int day)
{
    if (day > 0 && day < 32)
        return true;

    return false;
}