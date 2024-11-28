#include "ItemManager.h"
#include <vector>
#include "HeaderOnlyCsv.hpp"

using namespace NSStarmanLib;

ItemManager* ItemManager::obj { nullptr };

int ItemDef::GetId() const
{
    return m_id;
}

void ItemDef::SetId(int arg)
{
    m_id = arg;
}

std::string ItemDef::GetName() const
{
    return m_name;
}

void ItemDef::SetName(std::string arg)
{
    m_name = arg;
}

std::string ItemDef::GetDetail() const
{
    return m_detail;
}

void ItemDef::SetDetail(std::string arg)
{
    m_detail = arg;
}

std::string ItemDef::GetImagePath() const
{
    return m_imagePath;
}

void ItemDef::SetImagePath(std::string arg)
{
    m_imagePath = arg;
}

float ItemDef::GetWeight() const
{
    return m_weight;
}

void ItemDef::SetWeight(float arg)
{
    m_weight = arg;
}

float ItemDef::GetVolume() const
{
    return m_volume;
}

void ItemDef::SetVolume(float arg)
{
    m_volume = arg;
}

ItemDef::ItemType ItemDef::GetType() const
{
    return m_eType;
}

void ItemDef::SetType(ItemType arg)
{
    m_eType = arg;
}

float ItemDef::GetCarbo() const
{
    return m_carbo;
}

void ItemDef::SetCarbo(float arg)
{
    m_carbo = arg;
}

float ItemDef::GetProtein() const
{
    return m_protein;
}

void ItemDef::SetProtein(float arg)
{
    m_protein = arg;
}

float ItemDef::GetLipid() const
{
    return m_lipid;
}

void ItemDef::SetLipid(float arg)
{
    m_lipid = arg;
}

float ItemDef::GetVitamin() const
{
    return m_vitamin;
}

void ItemDef::SetVitamin(float arg)
{
    m_vitamin = arg;
}

float ItemDef::GetMineral() const
{
    return m_mineral;
}

void ItemDef::SetMineral(float arg)
{
    m_mineral = arg;
}

float ItemDef::GetWater() const
{
    return m_water;
}

void ItemDef::SetWater(float arg)
{
    m_water = arg;
}

float ItemDef::GetBodyStaminaDebuff() const
{
    return m_bodyStaminaDebuff;
}

void ItemDef::SetBodyStaminaDebuff(float arg)
{
    m_bodyStaminaDebuff = arg;
}

float ItemDef::GetBrainStaminaDebuff() const
{
    return m_brainStaminaDebuff;
}

void ItemDef::SetBrainStaminaDebuff(float arg)
{
    m_brainStaminaDebuff = arg;
}

float ItemDef::GetMuscleDebuff() const
{
    return m_muscleDebuff;
}

void ItemDef::SetMuscleDebuff(float arg)
{
    m_muscleDebuff = arg;
}

bool ItemDef::GetHeadache() const
{
    return m_headache;
}

void ItemDef::SetHeadache(bool arg)
{
    m_headache = arg;
}

bool ItemDef::GetStomachache() const
{
    return m_stomachache;
}

void ItemDef::SetStomachache(bool arg)
{
    m_stomachache = arg;
}

int ItemDef::GetLevel() const
{
    return m_level;
}

void ItemDef::SetLevel(const int arg)
{
    m_level = arg;
}

int NSStarmanLib::ItemDef::GetDurabilityMax() const
{
    return m_durabilityMax;
}

void NSStarmanLib::ItemDef::SetDurabilityMax(int arg)
{
    m_durabilityMax = arg;
}

ItemManager* ItemManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new ItemManager();
    }
    return obj;
}

void ItemManager::Destroy()
{
    delete ItemManager::obj;
    ItemManager::obj = nullptr;
}

void ItemManager::Init(const std::string& csvfile)
{
    std::vector<std::vector<std::string> > vss;
    vss = csv::Read(csvfile);
    for (std::size_t i = 1; i < vss.size(); ++i)
    {
        int work_i = 0;
        float work_f = 0.f;

        ItemDef itemDef;

        work_i = std::stoi(vss.at(i).at(0));
        itemDef.SetId(work_i);

        itemDef.SetName(vss.at(i).at(1));

        itemDef.SetDetail(vss.at(i).at(2));

        itemDef.SetImagePath(vss.at(i).at(3));

        work_f = std::stof(vss.at(i).at(4));
        itemDef.SetWeight(work_f);

        work_f = std::stof(vss.at(i).at(5));
        itemDef.SetVolume(work_f);

        if (vss.at(i).at(6) == "ãMèdïi")
        {
            itemDef.SetType(ItemDef::ItemType::VALUABLES);
        }
        else if (vss.at(i).at(6) == "ëfçﬁ")
        {
            itemDef.SetType(ItemDef::ItemType::MATERIAL);
        }
        else if (vss.at(i).at(6) == "êHçﬁ")
        {
            itemDef.SetType(ItemDef::ItemType::FOOD);
        }
        else if (vss.at(i).at(6) == "ïêäÌ")
        {
            itemDef.SetType(ItemDef::ItemType::WEAPON);
        }
        else if (vss.at(i).at(6) == "ÇªÇÃëº")
        {
            itemDef.SetType(ItemDef::ItemType::OTHERS);
        }

        if (itemDef.GetType() == ItemDef::ItemType::FOOD)
        {
            work_f = std::stof(vss.at(i).at(7));
            itemDef.SetCarbo(work_f);

            work_f = std::stof(vss.at(i).at(8));
            itemDef.SetProtein(work_f);

            work_f = std::stof(vss.at(i).at(9));
            itemDef.SetLipid(work_f);

            work_f = std::stof(vss.at(i).at(10));
            itemDef.SetVitamin(work_f);

            work_f = std::stof(vss.at(i).at(11));
            itemDef.SetMineral(work_f);

            work_f = std::stof(vss.at(i).at(12));
            itemDef.SetWater(work_f);

            work_f = std::stof(vss.at(i).at(13));
            itemDef.SetBodyStaminaDebuff(work_f);

            work_f = std::stof(vss.at(i).at(14));
            itemDef.SetBrainStaminaDebuff(work_f);

            work_f = std::stof(vss.at(i).at(15));
            itemDef.SetMuscleDebuff(work_f);

            if (vss.at(i).at(16) == "ÅZ")
            {
                itemDef.SetHeadache(true);
            }
            else
            {
                itemDef.SetHeadache(false);
            }

            if (vss.at(i).at(17) == "ÅZ")
            {
                itemDef.SetStomachache(true);
            }
            else
            {
                itemDef.SetStomachache(false);
            }
        }

        // ã≠âªíl
        if (vss.at(i).at(18).empty())
        {
            work_i = -1;
        }
        else
        {
            work_i = std::stoi(vss.at(i).at(18));
        }

        itemDef.SetLevel(work_i);

        // ëœãvìxÇÃç≈ëÂílÅiÅÅèâä˙ílÅj
        if (vss.at(i).at(19).empty())
        {
            work_i = -1;
        }
        else
        {
            work_i = std::stoi(vss.at(i).at(19));
        }

        itemDef.SetDurabilityMax(work_i);
        m_itemDefMap[(int)i] = itemDef;
    }
    m_inited = true;
}

bool NSStarmanLib::ItemManager::Inited()
{
    return m_inited;
}

ItemDef ItemManager::GetItemDef(const std::string& key, const int level)
{
    ItemDef itemDef;
    for (auto it = m_itemDefMap.begin(); it != m_itemDefMap.end(); ++it)
    {
        if (it->second.GetName() == key && it->second.GetLevel() == level)
        {
            itemDef = it->second;
            break;
        }
    }
    return itemDef;
}

ItemDef ItemManager::GetItemDef(const int id)
{
    ItemDef itemDef;
    for (auto it = m_itemDefMap.begin(); it != m_itemDefMap.end(); ++it)
    {
        if (it->second.GetId() == id)
        {
            itemDef = it->second;
            break;
        }
    }
    if (itemDef.GetId() == 0)
    {
        // ë∂ç›ÇµÇ»Ç¢IDÇéÊìæÇµÇÊÇ§Ç∆ÇµÇΩÅB
        throw std::exception();
    }
    return itemDef;
}

void NSStarmanLib::ItemInfo::SetId(const int arg)
{
    m_id = arg;
}

int NSStarmanLib::ItemInfo::GetId() const
{
    return m_id;
}

void NSStarmanLib::ItemInfo::SetSubId(const int arg)
{
    m_subId = arg;
}

int NSStarmanLib::ItemInfo::GetSubId() const
{
    return m_subId;
}

void NSStarmanLib::ItemInfo::SetDurabilityCurrent(const int arg)
{
    m_durabilityCurrent = arg;
}

int NSStarmanLib::ItemInfo::GetDurabilityCurrent() const
{
    return m_durabilityCurrent;
}

