#include "Headers/pesel.h"

pesel_error pesel::set(const std::string& pesel)
{
    pesel_error result = verify(pesel);
    if (result == pesel_error::OK)
        m_pesel = pesel;

    m_lastError = result;

    return result;
}

std::string pesel::getPesel() const
{
    return m_pesel;
}

pesel_error pesel::getLastError()
{
    return m_lastError;
}

pesel_error pesel::verify(const std::string& pesel)
{
    if (pesel.length() != 11)
        return pesel_error::WRONG_LENGTH;

    if (!std::all_of(begin(pesel), end(pesel), [](unsigned char c) {return isdigit(c); }))
        return pesel_error::NON_DIGITS;

    if (!BirthDateParser.verifyBrirthDateFormat(pesel))
        return pesel_error::WRONG_BDAY_FORMAT;

    std::vector<int> pesel_multiplier = { 1,3,7,9,1,3,7,9,1,3,1 };

    std::transform(begin(pesel_multiplier), end(pesel_multiplier), begin(pesel_multiplier), [&pesel, counter = 0](int multiplier) mutable {
        int temp_value = pesel.at(counter) - '0';
        counter++;
        return multiplier * temp_value;
        });

    int mod_sum = (std::accumulate(begin(pesel_multiplier), end(pesel_multiplier) - 1, 0)) % 10;

    if (mod_sum != 0)
        mod_sum = 10 - mod_sum;

    int cecksum_value = pesel.at(10) - '0';
    if (cecksum_value == mod_sum)
        return pesel_error::OK;

    return pesel_error::CHECKSUM_ERROR;
}
