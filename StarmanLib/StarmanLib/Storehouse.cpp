#include "Storehouse.h"
#include "ItemManager.h"

using namespace NSStarmanLib;

Storehouse* Storehouse::obj { nullptr };

Storehouse* Storehouse::GetObj()
{
    if (obj == nullptr)
    {
        obj = new Storehouse();
    }
    return obj;
}

void Storehouse::Destroy()
{
    delete Storehouse::obj;
    Storehouse::obj = nullptr;
}

void Storehouse::Init(const std::string& csvfile)
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
    m_inited = true;
}

bool NSStarmanLib::Storehouse::Inited()
{
    return m_inited;
}

void Storehouse::Save(const std::string& csvfile)
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

void Storehouse::AddItem(const int id)
{
    m_itemMap[id] = m_itemMap[id] + 1;
}

void NSStarmanLib::Storehouse::AddItem(const std::string& name, const int level)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemDef itemDef = itemManager->GetItemDef(name, level);
    int materialId = itemDef.GetId();
    AddItem(materialId);
}

void Storehouse::RemoveItem(const int id)
{
    if (m_itemMap[id] >= 1)
    {
        m_itemMap[id] = m_itemMap[id] - 1;
    }
}

void NSStarmanLib::Storehouse::RemoveItem(const std::string& name, const int level)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemDef itemDef = itemManager->GetItemDef(name, level);
    int materialId = itemDef.GetId();
    RemoveItem(materialId);
}

int Storehouse::CountItem(const int id)
{
    return m_itemMap.at(id);
}

int NSStarmanLib::Storehouse::CountItem(const std::string& name, const int level)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemDef itemDef = itemManager->GetItemDef(name, level);
    int materialId = itemDef.GetId();
    return CountItem(materialId);
}


