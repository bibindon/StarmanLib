#include "ActivityBase.h"
#include <vector>
#include "Util.h"
#include "Voyage.h"

NSStarmanLib::ActivityBase* NSStarmanLib::ActivityBase::m_obj = nullptr;

NSStarmanLib::ActivityBase* NSStarmanLib::ActivityBase::Get()
{
    if (m_obj == nullptr)
    {
        m_obj = new ActivityBase();
    }

    return m_obj;
}

NSStarmanLib::ActivityBase::ActivityBase()
{
}

void NSStarmanLib::ActivityBase::Init(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvfile, false);

    if (vvs.at(0).at(1) == "Precision")
    {
        m_eBaseType = eBaseType::Precision;
    }
    else if (vvs.at(0).at(1) == "DirectNex")
    {
        m_eBaseType = eBaseType::DirectNex;
    }
}

void NSStarmanLib::ActivityBase::Save(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vvs;
    std::vector<std::string> vs;
    vs.push_back("Œ»Ý‚ÌŠˆ“®‹’“_");

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

void NSStarmanLib::ActivityBase::GetPierPos(const eBaseType baseType, float* x, float* y, float* z)
{
    if (baseType == eBaseType::Precision)
    {
        *x = -305.f;
        *y = 11.f;
        *z = 540.f;
    }
    else if (baseType == eBaseType::DirectNex)
    {
        // TODO ³‚µ‚¢À•W
        *x = -305.f;
        *y = 11.f;
        *z = 540.f;
    }
}

bool NSStarmanLib::ActivityBase::CheckRaftNearPier(const float x, const float y, const float z)
{
    float x2, y2, z2;
    GetPierPos(m_eBaseType, &x2, &y2, &z2);

    return Util::HitByBoundingBox(x, y, z, x2, y2, z2, 5.f);
}

bool NSStarmanLib::ActivityBase::CheckRaftExist()
{
    auto raftList = Voyage::Get()->GetRaftList();

    bool bExist = false;

    for (auto& raft : raftList)
    {
        float x, y, z;
        raft.GetXYZ(&x, &y, &z);

        bExist = CheckRaftNearPier(x, y, z);
        if (bExist)
        {
            break;
        }
    }

    return bExist;
}

