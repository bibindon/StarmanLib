#include "ItemManager.h"
#include <vector>
#include "HeaderOnlyCsv.hpp"

using namespace NSStarmanLib;

ItemManager* ItemManager::obj { nullptr };

int ItemInfo::GetId() const
{
    return m_id;
}

void ItemInfo::SetId(int arg)
{
    m_id = arg;
}

std::string ItemInfo::GetName() const
{
    return m_name;
}

void ItemInfo::SetName(std::string arg)
{
    m_name = arg;
}

std::string ItemInfo::GetDetail() const
{
    return m_detail;
}

void ItemInfo::SetDetail(std::string arg)
{
    m_detail = arg;
}

std::string ItemInfo::GetImagePath() const
{
    return m_imagePath;
}

void ItemInfo::SetImagePath(std::string arg)
{
    m_imagePath = arg;
}

float ItemInfo::GetWeight() const
{
    return m_weight;
}

void ItemInfo::SetWeight(float arg)
{
    m_weight = arg;
}

float ItemInfo::GetVolume() const
{
    return m_volume;
}

void ItemInfo::SetVolume(float arg)
{
    m_volume = arg;
}

ItemInfo::ItemType ItemInfo::GetType() const
{
    return m_eType;
}

void ItemInfo::SetType(ItemType arg)
{
    m_eType = arg;
}

float ItemInfo::GetCarbo() const
{
    return m_carbo;
}

void ItemInfo::SetCarbo(float arg)
{
    m_carbo = arg;
}

float ItemInfo::GetProtein() const
{
    return m_protein;
}

void ItemInfo::SetProtein(float arg)
{
    m_protein = arg;
}

float ItemInfo::GetLipid() const
{
    return m_lipid;
}

void ItemInfo::SetLipid(float arg)
{
    m_lipid = arg;
}

float ItemInfo::GetVitamin() const
{
    return m_vitamin;
}

void ItemInfo::SetVitamin(float arg)
{
    m_vitamin = arg;
}

float ItemInfo::GetMineral() const
{
    return m_mineral;
}

void ItemInfo::SetMineral(float arg)
{
    m_mineral = arg;
}

float ItemInfo::GetWater() const
{
    return m_water;
}

void ItemInfo::SetWater(float arg)
{
    m_water = arg;
}

float ItemInfo::GetBodyStaminaDebuff() const
{
    return m_bodyStaminaDebuff;
}

void ItemInfo::SetBodyStaminaDebuff(float arg)
{
    m_bodyStaminaDebuff = arg;
}

float ItemInfo::GetBrainStaminaDebuff() const
{
    return m_brainStaminaDebuff;
}

void ItemInfo::SetBrainStaminaDebuff(float arg)
{
    m_brainStaminaDebuff = arg;
}

float ItemInfo::GetMuscleDebuff() const
{
    return m_muscleDebuff;
}

void ItemInfo::SetMuscleDebuff(float arg)
{
    m_muscleDebuff = arg;
}

bool ItemInfo::GetHeadache() const
{
    return m_headache;
}

void ItemInfo::SetHeadache(bool arg)
{
    m_headache = arg;
}

bool ItemInfo::GetStomachache() const
{
    return m_stomachache;
}

void ItemInfo::SetStomachache(bool arg)
{
    m_stomachache = arg;
}

int ItemInfo::GetLevel() const
{
    return m_level;
}

void ItemInfo::SetLevel(const int arg)
{
    m_level = arg;
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

        ItemInfo itemInfo;

        work_i = std::stoi(vss.at(i).at(0));
        itemInfo.SetId(work_i);

        itemInfo.SetName(vss.at(i).at(1));

        itemInfo.SetDetail(vss.at(i).at(2));

        itemInfo.SetImagePath(vss.at(i).at(3));

        work_f = std::stof(vss.at(i).at(4));
        itemInfo.SetWeight(work_f);

        work_f = std::stof(vss.at(i).at(5));
        itemInfo.SetVolume(work_f);

        if (vss.at(i).at(6) == "ãMèdïi")
        {
            itemInfo.SetType(ItemInfo::ItemType::VALUABLES);
        }
        else if (vss.at(i).at(6) == "ëfçﬁ")
        {
            itemInfo.SetType(ItemInfo::ItemType::MATERIAL);
        }
        else if (vss.at(i).at(6) == "êHçﬁ")
        {
            itemInfo.SetType(ItemInfo::ItemType::FOOD);
        }
        else if (vss.at(i).at(6) == "ÇªÇÃëº")
        {
            itemInfo.SetType(ItemInfo::ItemType::OTHERS);
        }

        if (itemInfo.GetType() == ItemInfo::ItemType::FOOD)
        {
            work_f = std::stof(vss.at(i).at(7));
            itemInfo.SetCarbo(work_f);

            work_f = std::stof(vss.at(i).at(8));
            itemInfo.SetProtein(work_f);

            work_f = std::stof(vss.at(i).at(9));
            itemInfo.SetLipid(work_f);

            work_f = std::stof(vss.at(i).at(10));
            itemInfo.SetVitamin(work_f);

            work_f = std::stof(vss.at(i).at(11));
            itemInfo.SetMineral(work_f);

            work_f = std::stof(vss.at(i).at(12));
            itemInfo.SetWater(work_f);

            work_f = std::stof(vss.at(i).at(13));
            itemInfo.SetBodyStaminaDebuff(work_f);

            work_f = std::stof(vss.at(i).at(14));
            itemInfo.SetBrainStaminaDebuff(work_f);

            work_f = std::stof(vss.at(i).at(15));
            itemInfo.SetMuscleDebuff(work_f);

            if (vss.at(i).at(16) == "ÅZ")
            {
                itemInfo.SetHeadache(true);
            }
            else
            {
                itemInfo.SetHeadache(false);
            }

            if (vss.at(i).at(17) == "ÅZ")
            {
                itemInfo.SetStomachache(true);
            }
            else
            {
                itemInfo.SetStomachache(false);
            }

            if (vss.at(i).at(18).empty())
            {
                work_i = -1;
            }
            else
            {
                work_i = std::stoi(vss.at(i).at(18));
            }

            itemInfo.SetLevel(work_i);
        }
        m_itemInfoMap[(int)i] = itemInfo;
    }
}

ItemInfo ItemManager::GetItemInfo(const std::string& key, const int level)
{
    ItemInfo itemInfo;
    for (auto it = m_itemInfoMap.begin(); it != m_itemInfoMap.end(); ++it)
    {
        if (it->second.GetName() == key && it->second.GetLevel() == level)
        {
            itemInfo = it->second;
            break;
        }
    }
    return itemInfo;
}

ItemInfo ItemManager::GetItemInfo(const int id)
{
    ItemInfo itemInfo;
    for (auto it = m_itemInfoMap.begin(); it != m_itemInfoMap.end(); ++it)
    {
        if (it->second.GetId() == id)
        {
            itemInfo = it->second;
            break;
        }
    }
    if (itemInfo.GetId() == 0)
    {
        // ë∂ç›ÇµÇ»Ç¢IDÇéÊìæÇµÇÊÇ§Ç∆ÇµÇΩÅB
        abort();
    }
    return itemInfo;
}

