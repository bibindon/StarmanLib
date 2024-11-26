#include "PowereggDateTime.h"
#include <vector>
#include "HeaderOnlyCsv.hpp"

using namespace NSStarmanLib;

PowereggDateTime* PowereggDateTime::obj = nullptr;

PowereggDateTime* PowereggDateTime::GetObj()
{
    if (obj == nullptr)
    {
        obj = new PowereggDateTime();
    }
    return obj;
}

void PowereggDateTime::Destroy()
{
    delete PowereggDateTime::obj;
    PowereggDateTime::obj = nullptr;
}

void PowereggDateTime::Init(const std::string& csvfile)
{
    std::vector<std::vector<std::string> > vss;
    vss = csv::Read(csvfile);
    m_year = std::stoi(vss.at(0).at(1));
    m_month = std::stoi(vss.at(1).at(1));
    m_day = std::stoi(vss.at(2).at(1));
    m_hour = std::stoi(vss.at(3).at(1));
    m_minute = std::stoi(vss.at(4).at(1));
    m_second = std::stoi(vss.at(5).at(1));
}

void PowereggDateTime::Save(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;
    int work = 0;

    vs.push_back("”N");
    vs.push_back(std::to_string(m_year));
    vss.push_back(vs);
    vs.clear();

    vs.push_back("ŒŽ");
    vs.push_back(std::to_string(m_month));
    vss.push_back(vs);
    vs.clear();

    vs.push_back("“ú");
    vs.push_back(std::to_string(m_day));
    vss.push_back(vs);
    vs.clear();

    vs.push_back("Žž");
    vs.push_back(std::to_string(m_hour));
    vss.push_back(vs);
    vs.clear();

    vs.push_back("•ª");
    vs.push_back(std::to_string(m_minute));
    vss.push_back(vs);
    vs.clear();

    vs.push_back("•b");
    vs.push_back(std::to_string(m_second));
    vss.push_back(vs);
    vs.clear();

    csv::Write(csvfile, vss);
}

void PowereggDateTime::IncreaseDateTime(int month, int day, int hour, int minute, int second)
{
    m_month += month;

    m_day += day;

    m_hour += hour;

    m_minute += minute;

    m_second += second;

    if (m_second >= 60)
    {
        m_second -= 60;
        m_minute++;
    }

    if (m_minute >= 60)
    {
        m_minute -= 60;
        m_hour++;
    }

    if (m_hour >= 24)
    {
        m_hour -= 24;
        m_day++;
    }

    if (m_day >= DAY_OF_MONTH_[m_month])
    {
        m_day -= DAY_OF_MONTH_[m_month];
        m_month++;
    }

    if (m_month >= 12)
    {
        m_month -= 12;
        m_year++;
    }
}

int PowereggDateTime::GetYear()
{
    return m_year;
}

int PowereggDateTime::GetMonth()
{
    return m_month;
}

int PowereggDateTime::GetDay()
{
    return m_day;
}

int PowereggDateTime::GetHour()
{
    return m_hour;
}

int PowereggDateTime::GetMinute()
{
    return m_minute;
}

int PowereggDateTime::GetSecond()
{
    return m_second;
}

int NSStarmanLib::PowereggDateTime::DAY_OF_MONTH(const int arg)
{
    return DAY_OF_MONTH_[arg];
}
