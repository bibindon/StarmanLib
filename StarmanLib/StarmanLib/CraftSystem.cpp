#include "CraftSystem.h"
#include "HeaderOnlyCsv.hpp"
#include "PowereggDateTime.h"
#include "Inventory.h"
#include "ItemManager.h"

using namespace NSStarmanLib;

CraftSystem* CraftSystem::obj { nullptr };

CraftSystem* CraftSystem::GetObj()
{
    if (obj == nullptr)
    {
        obj = new CraftSystem();
    }
    return obj;
}

void CraftSystem::Destroy()
{
    delete CraftSystem::obj;
    CraftSystem::obj = nullptr;
}

void CraftSystem::Init(const std::string& csvfileSkill, const std::string& csvfileQueue)
{
    std::vector<std::vector<std::string> > vss;
    vss = csv::Read(csvfileSkill);
    std::string work;

    for (std::size_t i = 1; i < vss.size(); ++i)
    {
        work = vss.at(i).at(0);
        if (vss.at(i).at(1) == "Åõ")
        {
            m_craftSkillMap[work] = true;
        }
        else
        {
            m_craftSkillMap[work] = false;
        }
    }
}

void NSStarmanLib::CraftSystem::Save(const std::string& csvfileSkill,
                                     const std::string& csvfileQueue)
{
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;

    vs.push_back("ÉNÉâÉtÉgÉAÉCÉeÉÄ");
    vs.push_back("ÉNÉâÉtÉgâ¬î\");
    vss.push_back(vs);
    vs.clear();

    for (auto it = m_craftSkillMap.begin(); it != m_craftSkillMap.end(); ++it)
    {
        vs.push_back(it->first);
        if (it->second)
        {
            vs.push_back("Åõ");
        }
        else
        {
            vs.push_back("");
        }

        vss.push_back(vs);
        vs.clear();
    }
    csv::Write(csvfileSkill, vss);
}

void NSStarmanLib::CraftSystem::SetCraftsmanSkill(const std::string& craftItem)
{
    m_craftSkillMap[craftItem] = true;
}

bool NSStarmanLib::CraftSystem::GetCraftsmanSkill(const std::string& craftItem)
{
    return m_craftSkillMap.at(craftItem);
}

bool NSStarmanLib::CraftSystem::CraftRequest(const std::string& craftItem)
{
    // ó\ñÒÇÕ5âÒÇ‹Ç≈
    if (m_craftingItemList.size() >= 4)
    {
        return false;
    }

    CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
    CraftOutput craftOutput;
    std::size_t index = craftItem.find("Å{");
    if (index != std::string::npos)
    {
        std::string name = craftItem.substr(0, index);
        craftOutput.SetName(name);

        std::string level = craftItem.substr(index);
        if (level == "Å{ÇP")
        {
            craftOutput.SetLevel(1);
        }
        else if (level == "Å{ÇQ")
        {
            craftOutput.SetLevel(2);
        }
        else if (level == "Å{ÇR")
        {
            craftOutput.SetLevel(3);
        }
        else if (level == "Å{ÇS")
        {
            craftOutput.SetLevel(4);
        }
        else if (level == "Å{ÇT")
        {
            craftOutput.SetLevel(5);
        }
        else if (level == "Å{ÇU")
        {
            craftOutput.SetLevel(6);
        }
        else if (level == "Å{ÇV")
        {
            craftOutput.SetLevel(7);
        }
        else if (level == "Å{ÇW")
        {
            craftOutput.SetLevel(8);
        }
        else if (level == "Å{ÇX")
        {
            craftOutput.SetLevel(9);
        }
        else if (level == "Å{ÇPÇO")
        {
            craftOutput.SetLevel(10);
        }
        craftOutput.SetNumber(1);
    }

    CraftInfo craftInfo = craftInfoManager->GetCraftInfo(craftOutput);

    // ëfçﬁÇè¡îÔÇ∑ÇÈ
    // ëfçﬁÇ™ë´ÇËÇ»Ç¢Ç∆Ç´ÇÕfalseÇï‘Ç∑
    ItemManager* itemManager = ItemManager::GetObj();
    std::vector<CraftMaterial> craftMaterialList = craftInfo.GetCraftMaterial();

    Inventory* inventory = Inventory::GetObj();

    for (std::size_t i = 0; i < craftMaterialList.size(); ++i)
    {
        std::string name;
        int materialId = 0;
        int materialNum = 0;
        int materialLevel = 0;

        name = craftMaterialList.at(i).GetName();

        ItemInfo itemInfo = itemManager->GetItemInfo(name);
        materialId = itemInfo.GetId();
        materialNum = craftMaterialList.at(i).GetNumber();

        inventory->RemoveItem(materialId);
    }

    CraftingItem craftingItem;
    craftingItem.SetCraftInfo(craftInfo);

    m_craftingItemList.push_back(craftingItem);

    return true;
}

bool NSStarmanLib::CraftSystem::CancelCraftStart(const int index)
{
    if ((int)m_craftingItemList.size() <= index)
    {
        return false;
    }
    m_craftingItemList.erase(std::next(m_craftingItemList.begin(), index));
    return true;
}

void NSStarmanLib::CraftSystem::UpdateCraftStatus()
{
    PowereggDateTime* obj = PowereggDateTime::GetObj();
}

std::string CraftingItem::GetName() const
{
    return m_name;
}

void CraftingItem::SetName(std::string mname)
{
    m_name = mname;
}

int CraftingItem::GetStartYear() const
{
    return m_startYear;
}

void CraftingItem::SetStartYear(int startYear)
{
    m_startYear = startYear;
}

int CraftingItem::GetStartMonth() const
{
    return m_startMonth;
}

void CraftingItem::SetStartMonth(int startMonth)
{
    m_startMonth = startMonth;
}

int CraftingItem::GetStartDay() const
{
    return m_startDay;
}

void CraftingItem::SetStartDay(int startDay)
{
    m_startDay = startDay;
}

int CraftingItem::GetStartHour() const
{
    return m_startHour;
}

void CraftingItem::SetStartHour(int startHour)
{
    m_startHour = startHour;
}

int CraftingItem::GetStartMinute() const
{
    return m_startMinute;
}

void CraftingItem::SetStartMinute(int startMinute)
{
    m_startMinute = startMinute;
}

int CraftingItem::GetStartSecond() const
{
    return m_startSecond;
}

void CraftingItem::SetStartSecond(int startSecond)
{
    m_startSecond = startSecond;
}

int CraftingItem::GetfinishYear() const
{
    return m_finishYear;
}

void CraftingItem::SetfinishYear(int mfinishYear)
{
    m_finishYear = mfinishYear;
}

int CraftingItem::GetfinishMonth() const
{
    return m_finishMonth;
}

void CraftingItem::SetfinishMonth(int mfinishMonth)
{
    m_finishMonth = mfinishMonth;
}

int CraftingItem::GetfinishDay() const
{
    return m_finishDay;
}

void CraftingItem::SetfinishDay(int mfinishDay)
{
    m_finishDay = mfinishDay;
}

int CraftingItem::GetfinishHour() const
{
    return m_finishHour;
}

void CraftingItem::SetfinishHour(int mfinishHour)
{
    m_finishHour = mfinishHour;
}

int CraftingItem::GetfinishMinute() const
{
    return m_finishMinute;
}

void CraftingItem::SetfinishMinute(int mfinishMinute)
{
    m_finishMinute = mfinishMinute;
}

int CraftingItem::GetfinishSecond() const
{
    return m_finishSecond;
}

void CraftingItem::SetfinishSecond(int mfinishSecond)
{
    m_finishSecond = mfinishSecond;
}

CraftInfo NSStarmanLib::CraftingItem::GetCraftInfo() const
{
    return m_craftInfo;
}

void NSStarmanLib::CraftingItem::SetCraftInfo(const CraftInfo& arg)
{
    m_craftInfo = arg;
}

