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
    vs.push_back("��");
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

void Inventory::RemoveItem(const int id)
{
    if (m_itemMap[id] >= 1)
    {
        m_itemMap[id] = m_itemMap[id] - 1;
        m_weight = CalcWeight();
    }
}

int Inventory::CountItem(const int id)
{
    return m_itemMap[id];
}

float Inventory::GetWeight()
{
    return m_weight;
}

float Inventory::CalcWeight()
{
    float result = 0.f;
    ItemManager* itemManger = ItemManager::GetObj();
    for (auto it = m_itemMap.begin(); it != m_itemMap.end(); ++it)
    {
        int id = it->first;
        int count = it->second;
        ItemInfo itemInfo = itemManger->GetItemInfo(id);
        if (itemInfo.GetId() == 0)
        {
            continue;
        }
        result += itemInfo.GetWeight() * count;
    }
    return result;
}

