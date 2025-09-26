#include "Headers/PeselGenerator.h"

std::string PeselGenerator::GeneratePesel(unsigned short int start_day, unsigned short int start_month, unsigned short int start_year, 
    unsigned short int end_day, unsigned short int end_month, unsigned short int end_year, int sex)
{
	std::chrono::year_month_day start_date{ std::chrono::year{start_year}, std::chrono::month{start_month}, std::chrono::day{start_day} };
	std::chrono::year_month_day end_date{ std::chrono::year{end_year}, std::chrono::month{end_month}, std::chrono::day{end_day} };

	if (start_date.ok() && end_date.ok())
		if (start_date < end_date)
		{
            auto m_DaysBetween = std::chrono::sys_days(end_date) - std::chrono::sys_days(start_date);

            int m_Offset = GenerateRandomValue(m_DaysBetween.count());
            auto m_GeneratedBDayDate = std::chrono::year_month_day(std::chrono::sys_days(start_date) + std::chrono::days(m_Offset));
            std::string m_FormatedBDate = ParseBDate(m_GeneratedBDayDate);
            
            std::string m_serial = ComplementDigitsTo(GenerateRandomValue(999));

            int m_sex;
            if (sex == 99)
                m_sex = GenerateRandomValue(9);
            else
                m_sex = sex;            

            std::vector<int> m_pesel_checksum_multipliers = { 1,3,7,9,1,3,7,9,1,3 };

            std::string m_pesel;

            m_pesel = m_FormatedBDate + m_serial + std::to_string(m_sex);

            std::transform(begin(m_pesel_checksum_multipliers), end(m_pesel_checksum_multipliers), begin(m_pesel_checksum_multipliers), [&m_pesel, counter = 0](int multiplier) mutable {
                int m_temp_value = m_pesel.at(counter) - '0';
                counter++;
                return multiplier * m_temp_value;
                });

            int m_mod_sum = (std::accumulate(begin(m_pesel_checksum_multipliers), end(m_pesel_checksum_multipliers), 0)) % 10;

            if (m_mod_sum != 0)
                m_mod_sum = 10 - m_mod_sum;

            return m_pesel + std::to_string(m_mod_sum);
		}

	return "00000000000";
}

int PeselGenerator::GenerateRandomValue(int maxValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, maxValue);

	return dis(gen);
}

std::string PeselGenerator::ParseBDate(std::chrono::year_month_day bDate)
{
    std::stringstream ss;
    ss << bDate;
    std::string s_temp = ss.str();
    std::string yy, mm, dd;
    yy.resize(2);
    mm.resize(2);
    dd.resize(2);
    
    int batch = 0;
    std::string date_prefix("0", 2);
    date_prefix[0] = s_temp[0];
    date_prefix[1] = s_temp[1];
    if (date_prefix == "19")
        batch = 0;
    else if (date_prefix == "20")
        batch = 20;
    else if (date_prefix == "21")
        batch = 40;
    else if (date_prefix == "22")
        batch = 60;

    yy[0] = s_temp[2];
    yy[1] = s_temp[3];

    mm[0] = s_temp[5];
    mm[1] = s_temp[6];

    int t_month = stoi(mm) + batch;
    mm = ComplementDigitsTo(t_month, 2);

    dd[0] = s_temp[8];
    dd[1] = s_temp[9];

    return yy+mm+dd;
}

std::string PeselGenerator::ComplementDigitsTo(int serial, int complementTo, char complementWith)
{
    std::string str_serial = std::to_string(serial);
    int size = str_serial.length();
    if (size < complementTo)
    {
        std::string buffer(complementTo, complementWith);

        for (int i = complementTo - size, j = 0; i < complementTo; i++)
        {
            buffer[i] = str_serial[j];
            j++;
        }

        str_serial.resize(complementTo);
        str_serial = buffer;
    }

    return str_serial;
}