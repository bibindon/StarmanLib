﻿#include "ItemManager.h"
#include <vector>
#include "Util.h"
#include "WeaponManager.h"

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

std::wstring ItemDef::GetName() const
{
    return m_name;
}

void ItemDef::SetName(std::wstring arg)
{
    m_name = arg;
}

std::wstring ItemDef::GetDetail() const
{
    return m_detail;
}

void ItemDef::SetDetail(std::wstring arg)
{
    m_detail = arg;
}

std::wstring ItemDef::GetImagePath() const
{
    if (m_eType != ItemType::WEAPON)
    {
        return m_imagePath;
    }
    else
    {
        auto weaponM = WeaponManager::GetObj();

        return weaponM->GetImageName2(m_weaponId);
    }
}

void ItemDef::SetImagePath(std::wstring arg)
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

std::wstring NSStarmanLib::ItemDef::GetWeaponId() const
{
    return m_weaponId;
}

void NSStarmanLib::ItemDef::SetWeaponId(const std::wstring& arg)
{
    m_weaponId = arg;
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

void ItemManager::Init(const std::wstring& csvfile, const std::wstring& csvfilePos,
                       const bool decrypt)
{
    {
        std::vector<std::vector<std::wstring>> vvs = Util::ReadFromCsv(csvfile, decrypt);

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            int work_i = 0;
            float work_f = 0.f;

            ItemDef itemDef;

            work_i = std::stoi(vvs.at(i).at(0));
            itemDef.SetId(work_i);

            itemDef.SetName(vvs.at(i).at(1));

            itemDef.SetDetail(vvs.at(i).at(2));

            itemDef.SetImagePath(vvs.at(i).at(3));

            work_f = std::stof(vvs.at(i).at(4));
            itemDef.SetWeight(work_f);

            work_f = std::stof(vvs.at(i).at(5));
            itemDef.SetVolume(work_f);

            if (vvs.at(i).at(6) == _T("貴重品"))
            {
                itemDef.SetType(ItemDef::ItemType::VALUABLES);
            }
            else if (vvs.at(i).at(6) == _T("素材"))
            {
                itemDef.SetType(ItemDef::ItemType::MATERIAL);
            }
            else if (vvs.at(i).at(6) == _T("食材"))
            {
                itemDef.SetType(ItemDef::ItemType::FOOD);
            }
            else if (vvs.at(i).at(6) == _T("武器"))
            {
                itemDef.SetType(ItemDef::ItemType::WEAPON);
            }
            else if (vvs.at(i).at(6) == _T("その他"))
            {
                itemDef.SetType(ItemDef::ItemType::OTHERS);
            }

            if (itemDef.GetType() == ItemDef::ItemType::FOOD)
            {
                work_f = std::stof(vvs.at(i).at(7));
                itemDef.SetCarbo(work_f);

                work_f = std::stof(vvs.at(i).at(8));
                itemDef.SetProtein(work_f);

                work_f = std::stof(vvs.at(i).at(9));
                itemDef.SetLipid(work_f);

                work_f = std::stof(vvs.at(i).at(10));
                itemDef.SetVitamin(work_f);

                work_f = std::stof(vvs.at(i).at(11));
                itemDef.SetMineral(work_f);

                work_f = std::stof(vvs.at(i).at(12));
                itemDef.SetWater(work_f);

                work_f = std::stof(vvs.at(i).at(13));
                itemDef.SetBodyStaminaDebuff(work_f);

                work_f = std::stof(vvs.at(i).at(14));
                itemDef.SetBrainStaminaDebuff(work_f);

                work_f = std::stof(vvs.at(i).at(15));
                itemDef.SetMuscleDebuff(work_f);

                if (vvs.at(i).at(16) == _T("○"))
                {
                    itemDef.SetHeadache(true);
                }
                else
                {
                    itemDef.SetHeadache(false);
                }

                if (vvs.at(i).at(17) == _T("○"))
                {
                    itemDef.SetStomachache(true);
                }
                else
                {
                    itemDef.SetStomachache(false);
                }
            }

            // 強化値
            if (vvs.at(i).at(18).empty())
            {
                work_i = -1;
            }
            else
            {
                work_i = std::stoi(vvs.at(i).at(18));
            }

            itemDef.SetLevel(work_i);

            // 耐久度の最大値（＝初期値）
            if (vvs.at(i).at(19).empty())
            {
                work_i = -1;
            }
            else
            {
                work_i = std::stoi(vvs.at(i).at(19));
            }

            itemDef.SetDurabilityMax(work_i);

            // 武器ID
            itemDef.SetWeaponId(vvs.at(i).at(20));

            m_itemDefMap[(int)i] = itemDef;
        }
    }
    {
        std::vector<std::vector<std::wstring>> vvs = Util::ReadFromCsv(csvfilePos, decrypt);

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            int posId = 0;
            int itemDefId = 0;
            float x = 0.f;
            float y = 0.f;
            float z = 0.f;

            ItemPos itemPos;

            posId = std::stoi(vvs.at(i).at(0));
            itemPos.SetItemPosId(posId);

            itemDefId = std::stoi(vvs.at(i).at(1));
            itemPos.SetItemDefId(itemDefId);

            x = std::stof(vvs.at(i).at(2));
            y = std::stof(vvs.at(i).at(3));
            z = std::stof(vvs.at(i).at(4));
            itemPos.SetPos(x, y, z);

            if (vvs.at(i).at(5) == _T("○"))
            {
                itemPos.SetObtained(true);
            }
            else if (vvs.at(i).at(5) == _T(""))
            {
                itemPos.SetObtained(false);
            }
            else
            {
                throw std::exception();
            }
            m_itemPosMap[posId] = itemPos;
        }
    }
    m_inited = true;
}

bool NSStarmanLib::ItemManager::Inited()
{
    return m_inited;
}

void NSStarmanLib::ItemManager::Save(const std::wstring& csvfilePos,
                                     const bool encrypt)
{
    std::vector<std::vector<std::wstring>> vvs;
    std::vector<std::wstring> vs;
    vs.push_back(_T("ID"));
    vs.push_back(_T("アイテムID"));
    vs.push_back(_T("X"));
    vs.push_back(_T("Y"));
    vs.push_back(_T("Z"));
    vs.push_back(_T("取得済み"));
    vvs.push_back(vs);
    vs.clear();

    ItemManager* itemManager = ItemManager::GetObj();

    for (auto it = m_itemPosMap.begin(); it != m_itemPosMap.end(); ++it)
    {
        vs.push_back(std::to_wstring(it->first));
        vs.push_back(std::to_wstring(it->second.GetItemDefId()));

        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
        it->second.GetPos(&x, &y, &z);

        vs.push_back(std::to_wstring(x));
        vs.push_back(std::to_wstring(y));
        vs.push_back(std::to_wstring(z));

        if (it->second.GetObtained())
        {
            vs.push_back(_T("○"));
        }
        else
        {
            vs.push_back(_T(""));
        }

        vvs.push_back(vs);
        vs.clear();
    }

    Util::WriteToCsv(csvfilePos, vvs, encrypt);
}

std::vector<int> NSStarmanLib::ItemManager::GetItemIdList()
{
    std::vector<int> idList;

    for (auto it = m_itemDefMap.begin(); it != m_itemDefMap.end(); ++it)
    {
        idList.push_back(it->second.GetId());
    }

    return idList;
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
        // 存在しないIDを取得しようとした。
        throw std::exception();
    }

    return itemDef;
}

ItemDef NSStarmanLib::ItemManager::GetItemDefByWeaponId(const std::wstring& weaponId, const int level)
{
    ItemDef itemDef;
    for (auto it = m_itemDefMap.begin(); it != m_itemDefMap.end(); ++it)
    {
        if (it->second.GetWeaponId() == weaponId)
        {
            if (it->second.GetLevel() == level)
            {
                itemDef = it->second;
                break;
            }
        }
    }

    if (itemDef.GetId() == 0)
    {
        // 存在しないIDを取得しようとした。
        throw std::exception();
    }

    return itemDef;
}

std::vector<int> NSStarmanLib::ItemManager::GetItemDef(const ItemDef::ItemType type)
{
    std::vector<int> idList;

    for (auto it = m_itemDefMap.begin(); it != m_itemDefMap.end(); ++it)
    {
        if (it->second.GetType() == type)
        {
            idList.push_back(it->second.GetId());
        }
    }

    return idList;
}

ItemDef NSStarmanLib::ItemManager::GetItemDefByPosID(const int posId)
{
    if (m_itemPosMap.find(posId) == m_itemPosMap.end())
    {
        throw std::exception();
    }

    int itemDefId = m_itemPosMap[posId].GetItemDefId();

    if (m_itemDefMap.find(itemDefId) == m_itemDefMap.end())
    {
        throw std::exception();
    }

    return m_itemDefMap[itemDefId];
}

// 引数で指定した座標に存在するアイテムを取得
// GetItemPosIdが-1だったらアイテムがない。
ItemPos NSStarmanLib::ItemManager::GetItemPosByPos(const float x,
                                                       const float y,
                                                       const float z,
                                                       const float r)
{
    ItemPos itemPos;
    itemPos.SetItemPosId(-1);

    // 球で距離を測るより立方体で測ったほうが速そう
    for (auto it = m_itemPosMap.begin(); it != m_itemPosMap.end(); ++it)
    {
        float x2 = 0.f;
        float y2 = 0.f;
        float z2 = 0.f;
        it->second.GetPos(&x2, &y2, &z2);

        if ((x2 - r) <= x && x <= (x2 + r))
        {
            if ((y2 - r) <= y && y <= (y2 + r))
            {
                if ((z2 - r) <= z && z <= (z2 + r))
                {
                    if (it->second.GetObtained() == false)
                    {
                        itemPos = it->second;
                    }
                }
            }
        }
    }
    return itemPos;
}

void NSStarmanLib::ItemManager::SetItemPosObtained(const int itemPosId)
{
    if (m_itemPosMap.find(itemPosId) == m_itemPosMap.end())
    {
        throw std::exception();
    }
    m_itemPosMap[itemPosId].SetObtained(true);
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

ItemDef NSStarmanLib::ItemInfo::GetItemDef() const
{
    return ItemManager::GetObj()->GetItemDef(m_id);
}

void NSStarmanLib::ItemPos::SetItemPosId(const int id)
{
    m_itemPosId = id;
}

int NSStarmanLib::ItemPos::GetItemPosId() const
{
    return m_itemPosId;
}

void NSStarmanLib::ItemPos::SetItemDefId(const int id)
{
    m_itemDefId = id;
}

int NSStarmanLib::ItemPos::GetItemDefId() const
{
    return m_itemDefId;
}

void NSStarmanLib::ItemPos::SetPos(const float x, const float y, const float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void NSStarmanLib::ItemPos::GetPos(float* x, float* y, float* z)
{
    *x = m_x;
    *y = m_y;
    *z = m_z;
}

void NSStarmanLib::ItemPos::SetObtained(const bool arg)
{
    m_obtained = arg;
}

bool NSStarmanLib::ItemPos::GetObtained()
{
    return m_obtained;
}
