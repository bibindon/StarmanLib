#include "Rynen.h"
#include <vector>
#include "HeaderOnlyCsv.hpp"

Rynen* Rynen::obj { nullptr };

void Rynen::SetReviveEnable(const bool arg)
{
    m_reviveEnable = arg;
}

bool Rynen::GetReviveEnable()
{
    return m_reviveEnable;
}

void Rynen::SetRevivePos(const float x, const float y, const float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void Rynen::GetRevivePos(float* x, float* y, float* z)
{
    *x = m_x;
    *y = m_y;
    *z = m_z;
}

void Rynen::SetContractDate(const int month, const int day)
{
    m_month = month;
    m_day = day;
}

void Rynen::GetContractDate(int* month, int* day)
{
    *month = m_month;
    *day = m_day;
}

Rynen* Rynen::GetObj()
{
    if (obj == nullptr)
    {
        obj = new Rynen();
    }
    return obj;
}

void Rynen::Destroy()
{
    delete Rynen::obj;
    Rynen::obj = nullptr;
}

void Rynen::Init(const std::string& csvfile)
{
    std::vector<std::vector<std::string> > vss;
    vss = csv::Read(csvfile);

    if (vss.at(0).at(1) == "○")
    {
        m_contracted = true;
    }
    else
    {
        m_contracted = false;
    }

    if (vss.at(1).at(1) == "○")
    {
        m_reviveEnable = true;
    }
    else
    {
        m_reviveEnable = false;
    }

    float work_f = 0.f;
    work_f = std::stof(vss.at(2).at(1));
    m_x = work_f;

    work_f = std::stof(vss.at(3).at(1));
    m_y = work_f;

    work_f = std::stof(vss.at(4).at(1));
    m_z = work_f;

    int work_i = 0;
    work_i = std::stoi(vss.at(5).at(1));
    m_month = work_i;

    work_i = std::stoi(vss.at(6).at(1));
    m_day = work_i;
}

void Rynen::Save(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;
    std::string work;

    vs.push_back("契約済みフラグ");
    if (m_contracted)
    {
        vs.push_back("○");
    }
    else
    {
        vs.push_back("");
    }
    vss.push_back(vs);
    vs.clear();

    vs.push_back("復活可能フラグ");
    if (m_reviveEnable)
    {
        vs.push_back("○");
    }
    else
    {
        vs.push_back("");
    }
    vss.push_back(vs);
    vs.clear();

    vs.push_back("x");
    work = std::to_string(m_x);
    vs.push_back(work);
    vss.push_back(vs);
    vs.clear();

    vs.push_back("y");
    work = std::to_string(m_y);
    vs.push_back(work);
    vss.push_back(vs);
    vs.clear();

    vs.push_back("z");
    work = std::to_string(m_z);
    vs.push_back(work);
    vss.push_back(vs);
    vs.clear();

    vs.push_back("契約日（月）");
    work = std::to_string(m_month);
    vs.push_back(work);
    vss.push_back(vs);
    vs.clear();

    vs.push_back("契約日（日）");
    work = std::to_string(m_day);
    vs.push_back(work);
    vss.push_back(vs);
    vs.clear();

    csv::Write(csvfile, vss);
}

void Rynen::SetContracted(const bool arg)
{
    m_contracted = arg;
}

bool Rynen::GetContracted()
{
    return m_contracted;
}

