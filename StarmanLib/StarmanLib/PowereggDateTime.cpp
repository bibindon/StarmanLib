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

    vs.push_back("Œ");
    vs.push_back(std::to_string(m_month));
    vss.push_back(vs);
    vs.clear();

    vs.push_back("“ú");
    vs.push_back(std::to_string(m_day));
    vss.push_back(vs);
    vs.clear();

    vs.push_back("");
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

// “ú•t“¯m‚Ì”äŠr
// 1”N2Œ3“ú45•ª6•b‚Æ6”N5Œ4“ú32•ª1•b‚Ì‚Ç‚¿‚ç‚ª–¢—ˆE‰ß‹‚©‚ğ”»’è‚·‚é‚É‚Í
// 010203040506 ‚Æ 060504030201 ‚Æ‚¢‚¤12Œ…‚Ì”’l‚ÆŒ©‚È‚µ‚Ä12Œ…‚Ì”’l“¯m‚Ì”äŠr‚ğs‚¦‚Î‚æ‚¢
bool NSStarmanLib::PowereggDateTime::FromPastToFuture(int year1, int month1, int day1,
                                                      int hour1, int minute1, int second1,
                                                      int year2, int month2, int day2,
                                                      int hour2, int minute2, int second2)
{
    long long leftDateTime = 0;
    leftDateTime += (long long)year1   * 10000000000;
    leftDateTime += (long long)month1  * 100000000;
    leftDateTime += (long long)day1    * 1000000;
    leftDateTime += (long long)hour1   * 10000;
    leftDateTime += (long long)minute1 * 100;
    leftDateTime += (long long)second1 * 1;

    long long rightDateTime = 0;
    rightDateTime += (long long)year2   * 10000000000;
    rightDateTime += (long long)month2  * 100000000;
    rightDateTime += (long long)day2    * 1000000;
    rightDateTime += (long long)hour2   * 10000;
    rightDateTime += (long long)minute2 * 100;
    rightDateTime += (long long)second2 * 1;

    return leftDateTime < rightDateTime;
}
