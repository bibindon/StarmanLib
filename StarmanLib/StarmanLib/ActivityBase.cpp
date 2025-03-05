#include "ActivityBase.h"
#include <vector>
#include "Util.h"

NSStarmanLib::ActivityBase* NSStarmanLib::ActivityBase::m_obj = nullptr;

NSStarmanLib::ActivityBase* NSStarmanLib::ActivityBase::Get()
{
    if (m_obj == nullptr)
    {
        m_obj = new ActivityBase();
    }

    return nullptr;
}

void NSStarmanLib::ActivityBase::Init(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvfile, false);

    if (vvs.at(0).at(1) == "Precision")
    {
        m_eBaseType = eBaseType::Precision;
    }
    else if (vvs.at(0).at(1) == "Precision")
    {
        m_eBaseType = eBaseType::DirectNex;
    }
}

void NSStarmanLib::ActivityBase::Save(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vvs;
    std::vector<std::string> vs;
    vs.push_back("åªç›ÇÃäàìÆãíì_");

    if (m_eBaseType == eBaseType::Precision)
    {
        vs.push_back("Precision");
    }
    else if (m_eBaseType == eBaseType::DirectNex)
    {
        vs.push_back("DirectNex");
    }

    vvs.push_back(vs);

    Util::WriteToCsv(csvfile, vvs, false);
}

void NSStarmanLib::ActivityBase::SetBaseType(const eBaseType arg)
{
        m_eBaseType = arg;
}

NSStarmanLib::eBaseType NSStarmanLib::ActivityBase::GetBaseType() const
{
    return m_eBaseType;
}

void NSStarmanLib::ActivityBase::Finalize()
{
    delete ActivityBase::m_obj;
    ActivityBase::m_obj = nullptr;
}

