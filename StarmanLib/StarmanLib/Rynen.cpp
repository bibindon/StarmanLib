#include "Rynen.h"
#include <vector>
#include "Util.h"

using namespace NSStarmanLib;

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

void Rynen::SetContractDate(const int year, const int month, const int day)
{
    m_year = year;
    m_month = month;
    m_day = day;
}

void Rynen::GetContractDate(int* year, int* month, int* day)
{
    *year = m_year;
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

void Rynen::Init(const std::string& csvfile,
                 const bool decrypt)
{
    std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvfile, decrypt);

    if (vvs.at(0).at(1) == "��")
    {
        m_contracted = true;
    }
    else
    {
        m_contracted = false;
    }

    if (vvs.at(1).at(1) == "��")
    {
        m_reviveEnable = true;
    }
    else
    {
        m_reviveEnable = false;
    }

    float work_f = 0.f;
    work_f = std::stof(vvs.at(2).at(1));
    m_x = work_f;

    work_f = std::stof(vvs.at(3).at(1));
    m_y = work_f;

    work_f = std::stof(vvs.at(4).at(1));
    m_z = work_f;

    int work_i = 0;
    work_i = std::stoi(vvs.at(5).at(1));
    m_month = work_i;

    work_i = std::stoi(vvs.at(6).at(1));
    m_day = work_i;
}

void Rynen::Save(const std::string& csvfile,
                 const bool encrypt)
{
    std::vector<std::vector<std::string>> vvs;
    std::vector<std::string> vs;
    std::string work;

    vs.push_back("�_��ς݃t���O");
    if (m_contracted)
    {
        vs.push_back("��");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);
    vs.clear();

    vs.push_back("�����\�t���O");
    if (m_reviveEnable)
    {
        vs.push_back("��");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);
    vs.clear();

    vs.push_back("x");
    work = std::to_string(m_x);
    vs.push_back(work);
    vvs.push_back(vs);
    vs.clear();

    vs.push_back("y");
    work = std::to_string(m_y);
    vs.push_back(work);
    vvs.push_back(vs);
    vs.clear();

    vs.push_back("z");
    work = std::to_string(m_z);
    vs.push_back(work);
    vvs.push_back(vs);
    vs.clear();

    vs.push_back("�_����i���j");
    work = std::to_string(m_month);
    vs.push_back(work);
    vvs.push_back(vs);
    vs.clear();

    vs.push_back("�_����i���j");
    work = std::to_string(m_day);
    vs.push_back(work);
    vvs.push_back(vs);
    vs.clear();

    Util::WriteToCsv(csvfile, vvs, encrypt);
}

void Rynen::SetContracted(const bool arg)
{
    m_contracted = arg;
}

bool Rynen::GetContracted()
{
    return m_contracted;
}

