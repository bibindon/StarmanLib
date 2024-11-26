#include "Inventory.h"
#include "ItemManager.h"

using namespace NSStarmanLib;

Inventory* Inventory::obj { nullptr };

Inventory* Inventory::GetObj()
{
    if (obj == nullptr)
    {
        obj = new Inventory();
    }
    return obj;
}

void Inventory::Destroy()
{
    delete Inventory::obj;
    Inventory::obj = nullptr;
}

void Inventory::Init(const std::string& csvfile)
{
    std::vector<std::vector<std::string> > vss;
    vss = csv::Read(csvfile);
    for (std::size_t i = 1; i < vss.size(); ++i)
    {
        int workId = 0;
        int workCount = 0;

        workId = std::stoi(vss.at(i).at(0));
        workCount = std::stoi(vss.at(i).at(1));
        m_itemMap[workId] = workCount;
    }

    m_weight = CalcWeight();
}

void Inventory::Save(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;
    vs.push_back("ID");
    vs.push_back("ŒÂ”");
    vss.push_back(vs);
    vs.clear();

    for (auto it = m_itemMap.begin(); it != m_itemMap.end(); ++it)
    {
        vs.push_back(std::to_string(it->first));
        vs.push_back(std::to_string(it->second));
        vss.push_back(vs);
        vs.clear();
    }

    csv::Write(csvfile, vss);
}

void Inventory::AddItem(const int id)
{
    m_itemMap[id] = m_itemMap[id] + 1;
    m_weight = CalcWeight();
}

void NSStarmanLib::Inventory::AddItem(const std::string name, const int level)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemInfo itemInfo = itemManager->GetItemInfo(name, level);
    int materialId = itemInfo.GetId();
    AddItem(materialId);
}

void Inventory::RemoveItem(const int id)
{
    if (m_itemMap[id] >= 1)
    {
        m_itemMap[id] = m_itemMap[id] - 1;
        m_weight = CalcWeight();
    }
}

void NSStarmanLib::Inventory::RemoveItem(const std::string name, const int level)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemInfo itemInfo = itemManager->GetItemInfo(name, level);
    int materialId = itemInfo.GetId();
    RemoveItem(materialId);
}

int Inventory::CountItem(const int id)
{
    return m_itemMap[id];
}

int NSStarmanLib::Inventory::CountItem(const std::string name, const int level)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemInfo itemInfo = itemManager->GetItemInfo(name, level);
    int materialId = itemInfo.GetId();
    return CountItem(materialId);
}

float Inventory::GetWeight()
{
    return m_weight;
}

float Inventory::CalcWeight()
{
    float result = 0.f;
    ItemManager* itemManager = ItemManager::GetObj();
    for (auto it = m_itemMap.begin(); it != m_itemMap.end(); ++it)
    {
        int id = it->first;
        int count = it->second;
        ItemInfo itemInfo = itemManager->GetItemInfo(id);
        if (itemInfo.GetId() == 0)
        {
            continue;
        }
        result += itemInfo.GetWeight() * count;
    }
    return result;
}

