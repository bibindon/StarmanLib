#include "Inventory.h"
#include "ItemManager.h"

#include <algorithm>

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
    // ItemManagerのInit関数が先に呼ばれている必要がある。
    {
        if (ItemManager::GetObj()->Inited() == false)
        {
            throw std::exception();
        }
    }

    std::vector<std::vector<std::string> > vss;
    vss = csv::Read(csvfile);
    for (std::size_t i = 1; i < vss.size(); ++i)
    {
        ItemInfo itemInfo;
        int id = 0;
        int subId = 0;
        int durability = 0;

        id = std::stoi(vss.at(i).at(0));
        itemInfo.SetId(id);

        subId = std::stoi(vss.at(i).at(1));
        itemInfo.SetSubId(subId);

        durability = std::stoi(vss.at(i).at(2));
        itemInfo.SetDurabilityCurrent(durability);

        m_itemInfoList.push_back(itemInfo);
    }

    m_weight = CalcWeight();
    m_inited = true;
}

bool NSStarmanLib::Inventory::Inited()
{
    return m_inited;
}

void Inventory::Save(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;
    vs.push_back("ID");
    vs.push_back("SubID");
    vs.push_back("耐久度");
    vss.push_back(vs);
    vs.clear();

    for (auto it = m_itemInfoList.begin(); it != m_itemInfoList.end(); ++it)
    {
        vs.push_back(std::to_string(it->GetId()));
        vs.push_back(std::to_string(it->GetSubId()));
        vs.push_back(std::to_string(it->GetDurabilityCurrent()));
        vss.push_back(vs);
        vs.clear();
    }

    csv::Write(csvfile, vss);
}

void Inventory::AddItem(const int id, const int durability)
{
    int subId = 0;

    // 新しいSubIDを取得。同じアイテムを複数持てるので連番を割り当てる。その連番がSubID
    std::size_t subSum = std::count_if(m_itemInfoList.begin(), m_itemInfoList.end(),
                                       [&](const ItemInfo& x)
                                       {
                                           return x.GetId() == id;
                                       });

    ItemInfo itemInfo;
    itemInfo.SetId(id);

    // SubIdは0スタートではなく1スタート
    itemInfo.SetSubId(subSum+1);

    itemInfo.SetDurabilityCurrent(durability);

    for (auto it = m_itemInfoList.begin(); it != m_itemInfoList.end(); ++it)
    {
        if (it->GetId() == id && it->GetSubId() == subSum)
        {
            m_itemInfoList.push_back(itemInfo);
            break;
        }
    }

    m_weight = CalcWeight();
}

void NSStarmanLib::Inventory::AddItem(const std::string name,
                                      const int level,
                                      const int durability)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemDef itemDef = itemManager->GetItemDef(name, level);
    int materialId = itemDef.GetId();
    AddItem(materialId, durability);
}

void Inventory::RemoveItem(const int id, const int subId)
{
    for (auto it = m_itemInfoList.begin(); it != m_itemInfoList.end(); ++it)
    {
        if (it->GetId() == id && it->GetSubId() == subId)
        {
            m_itemInfoList.erase(it);
            break;
        }
    }
    m_weight = CalcWeight();
}

void NSStarmanLib::Inventory::RemoveItem(const std::string name,
                                         const int subId,
                                         const int level)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemDef itemDef = itemManager->GetItemDef(name, level);
    int materialId = itemDef.GetId();
    RemoveItem(materialId, subId);
}

void NSStarmanLib::Inventory::SetItemDurability(const int id,
                                                const int subId,
                                                const int durability)
{
    for (auto it = m_itemInfoList.begin(); it != m_itemInfoList.end(); ++it)
    {
        if (it->GetId() == id && it->GetSubId() == subId)
        {
            it->SetDurabilityCurrent(durability);
            break;
        }
    }
}

// 耐久度を無視して個数を数える
// したがって、耐久度の下がったアイテムをクラフトの素材として使用出来て良いということにする
int Inventory::CountItem(const int id)
{
    int num = 0;
    for (auto it = m_itemInfoList.begin(); it != m_itemInfoList.end(); ++it)
    {
        if (it->GetId() == id)
        {
            num++;
        }
    }

    return num;
}

int NSStarmanLib::Inventory::CountItem(const std::string name, const int level)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemDef itemDef = itemManager->GetItemDef(name, level);
    int materialId = itemDef.GetId();
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
    for (auto it = m_itemInfoList.begin(); it != m_itemInfoList.end(); ++it)
    {
        int id = it->GetId();
        ItemDef itemDef = itemManager->GetItemDef(id);
        if (itemDef.GetId() == 0)
        {
            continue;
        }
        result += itemDef.GetWeight();
    }
    return result;
}

void NSStarmanLib::Inventory::Sort()
{
    m_itemInfoList.sort([](const ItemInfo& lhs, const ItemInfo& rhs)
                        {
                            if (lhs.GetId() < rhs.GetId())
                            {
                                return true;
                            }
                            else if (lhs.GetId() == rhs.GetId())
                            {
                                if (lhs.GetSubId() < rhs.GetSubId())
                                {
                                    return true;
                                }
                            }
                            return false;
                        });
}

