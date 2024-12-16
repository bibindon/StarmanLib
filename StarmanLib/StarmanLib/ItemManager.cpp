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

void ItemManager::Init(const std::string& csvfile, const std::string& csvfilePos)
{
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

			if (vss.at(i).at(6) == "貴重品")
			{
				itemDef.SetType(ItemDef::ItemType::VALUABLES);
			}
			else if (vss.at(i).at(6) == "素材")
			{
				itemDef.SetType(ItemDef::ItemType::MATERIAL);
			}
			else if (vss.at(i).at(6) == "食材")
			{
				itemDef.SetType(ItemDef::ItemType::FOOD);
			}
			else if (vss.at(i).at(6) == "武器")
			{
				itemDef.SetType(ItemDef::ItemType::WEAPON);
			}
			else if (vss.at(i).at(6) == "その他")
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

				if (vss.at(i).at(16) == "○")
				{
					itemDef.SetHeadache(true);
				}
				else
				{
					itemDef.SetHeadache(false);
				}

				if (vss.at(i).at(17) == "○")
				{
					itemDef.SetStomachache(true);
				}
				else
				{
					itemDef.SetStomachache(false);
				}
			}

			// 強化値
			if (vss.at(i).at(18).empty())
			{
				work_i = -1;
			}
			else
			{
				work_i = std::stoi(vss.at(i).at(18));
			}

			itemDef.SetLevel(work_i);

			// 耐久度の最大値（＝初期値）
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
    }
    {
		std::vector<std::vector<std::string> > vss;
		vss = csv::Read(csvfilePos);
		for (std::size_t i = 1; i < vss.size(); ++i)
		{
			int posId = 0;
			int itemDefId = 0;
			float x = 0.f;
			float y = 0.f;
			float z = 0.f;

			ItemPos itemPos;

			posId = std::stoi(vss.at(i).at(0));

			itemDefId = std::stoi(vss.at(i).at(1));
			itemPos.SetItemDefId(itemDefId);

			x = std::stof(vss.at(i).at(2));
			y = std::stof(vss.at(i).at(3));
			z = std::stof(vss.at(i).at(4));
			itemPos.SetPos(x, y, z);

			if (vss.at(i).at(5) == "○")
			{
				itemPos.SetObtained(true);
			}
			else if (vss.at(i).at(5) == "")
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

void NSStarmanLib::ItemManager::Save(const std::string& csvfilePos)
{
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;
    vs.push_back("ID");
    vs.push_back("アイテムID");
    vs.push_back("X");
    vs.push_back("Y");
    vs.push_back("Z");
    vs.push_back("取得済み");
    vss.push_back(vs);
    vs.clear();

    ItemManager* itemManager = ItemManager::GetObj();

    for (auto it = m_itemPosMap.begin(); it != m_itemPosMap.end(); ++it)
    {
        vs.push_back(std::to_string(it->first));
        vs.push_back(std::to_string(it->second.GetItemDefId()));

        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
        it->second.GetPos(&x, &y, &z);

        vs.push_back(std::to_string(x));
        vs.push_back(std::to_string(y));
        vs.push_back(std::to_string(z));

        if (it->second.GetObtained())
        {
            vs.push_back("○");
        }
        else
        {
            vs.push_back("");
        }

        vss.push_back(vs);
        vs.clear();
    }

    csv::Write(csvfilePos, vss);
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

ItemDef ItemManager::GetItemDef(const std::string& key, const int level)
{
    ItemDef itemDef;
    bool exist = false;
    for (auto it = m_itemDefMap.begin(); it != m_itemDefMap.end(); ++it)
    {
        if (it->second.GetName() == key && it->second.GetLevel() == level)
        {
            itemDef = it->second;
            exist = true;
            break;
        }
    }

    if (exist == false)
    {
        throw std::exception();
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
// GetItemDefIdが-1だったらアイテムがない。
ItemPos NSStarmanLib::ItemManager::GetItemPosByPos(const float x,
                                                       const float y,
                                                       const float z,
                                                       const float r)
{
    ItemPos itemPos;
    itemPos.SetItemDefId(-1);

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
