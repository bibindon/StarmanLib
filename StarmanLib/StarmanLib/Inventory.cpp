#include "Inventory.h"
#include "ItemManager.h"
#include "Storehouse.h"

#include <algorithm>
#include "Util.h"

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

void Inventory::Init(const std::string& csvfile,
                     const bool decrypt)
{
    // ItemManager��Init�֐�����ɌĂ΂�Ă���K�v������B
    {
        if (ItemManager::GetObj()->Inited() == false)
        {
            throw std::exception();
        }
    }

    std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvfile, decrypt);

    for (std::size_t i = 1; i < vvs.size(); ++i)
    {
        ItemInfo itemInfo;
        int id = 0;
        int subId = 0;
        int durability = 0;

        id = std::stoi(vvs.at(i).at(0));
        itemInfo.SetId(id);

        subId = std::stoi(vvs.at(i).at(2));
        itemInfo.SetSubId(subId);

        durability = std::stoi(vvs.at(i).at(3));
        itemInfo.SetDurabilityCurrent(durability);

        m_itemInfoList.push_back(itemInfo);
    }

    m_weight = CalcWeight();
    m_volumeCurrent = CalcVolume();
    m_inited = true;
}

bool NSStarmanLib::Inventory::Inited()
{
    return m_inited;
}

void Inventory::Save(const std::string& csvfile,
                     const bool encrypt)
{
    std::vector<std::vector<std::string>> vvs;
    std::vector<std::string> vs;
    vs.push_back("ID");
    vs.push_back("�A�C�e����");
    vs.push_back("SubID");
    vs.push_back("�ϋv�x");
    vvs.push_back(vs);
    vs.clear();

    ItemManager* itemManager = ItemManager::GetObj();

    for (auto it = m_itemInfoList.begin(); it != m_itemInfoList.end(); ++it)
    {
        vs.push_back(std::to_string(it->GetId()));

        ItemDef itemDef = itemManager->GetItemDef(it->GetId());
        vs.push_back(itemDef.GetName());

        vs.push_back(std::to_string(it->GetSubId()));
        vs.push_back(std::to_string(it->GetDurabilityCurrent()));
        vvs.push_back(vs);
        vs.clear();
    }

    Util::WriteToCsv(csvfile, vvs, encrypt);
}

int Inventory::AddItem(const int id, const int durability)
{
    int subId = 0;

    // �V����SubID���擾�B�A�C�e���͍폜�ł���̂�SubID���A�ԂɂȂ�Ƃ͌���Ȃ��B
    // SubID�� 0�ł͂Ȃ�1����X�^�[�g����
    // SubID�� 1,2,3,5�ƂȂ��Ă�����SubID��4�̃A�C�e����ǉ�����
    // SubID�� 1,2,5�ƂȂ��Ă�����SubID��3�̃A�C�e����ǉ�����i4�ɒǉ�����킯�ł͂Ȃ��j
    // SubID�� 1,2,3,4�ƂȂ��Ă�����SubID��5�̃A�C�e����ǉ�����
    // �A�C�e�����Ȃ�������SubID��1�̃A�C�e����ǉ�����
    // 
    // �C���x���g���Ƒq�ɂ�SubId�����Ȃ��悤�ɂ���

    // ���ԂƂȂ��Ă���SubID��T��

    // subId�̃��X�g
    std::vector<int> subIdList = GetSubIdList(id);

    // �q�ɂ�SubID
    Storehouse* storehouse = Storehouse::GetObj();

    std::vector<int> subIdList2 = storehouse->GetSubIdList(id);

    // �C���x���g���Ƒq�ɂŔ���Ă���SubID������Ȃ�ُ�I��������
    {
        std::vector<int> intersection;

        // ��̃��X�g�̐ϏW�������
        std::set_intersection(subIdList.begin(), subIdList.end(),
                              subIdList2.begin(), subIdList2.end(),
                              std::back_inserter(intersection));

        if (intersection.empty() == false)
        {
            throw std::exception();
        }
    }

    subIdList.insert(subIdList.end(), subIdList2.begin(), subIdList2.end());
    std::sort(subIdList.begin(), subIdList.end());

    int work = 1;
    int missingSubId = -1;
    for (auto it = subIdList.begin(); it != subIdList.end(); ++it)
    {
        // work��SubID����v����Ȃ玟��SubID�����ɍs��
        if (work == *it)
        {
            ++work;
        }
        // work��SubID���قȂ遁���ԂƂȂ��Ă���SubID
        else
        {
            missingSubId = work;
            break;
        }
    }

    int newSubId = -1;

    // ���ԂƂȂ��Ă���SubID����������V�KSubID�Ƃ���
    if (missingSubId != -1)
    {
        newSubId = missingSubId;
    }
    // ���ԂƂȂ��Ă���SubID���Ȃ������i���A�Ԃ������j�Ȃ疖���ɒǉ�����
    else
    {
        newSubId = subIdList.size() + 1;
    }

    ItemInfo itemInfo;
    itemInfo.SetId(id);
    itemInfo.SetSubId(newSubId);
    itemInfo.SetDurabilityCurrent(durability);
    m_itemInfoList.push_back(itemInfo);
    Sort();

    m_weight = CalcWeight();
    m_volumeCurrent = CalcVolume();
    return newSubId;
}

int NSStarmanLib::Inventory::AddItem(const std::string name,
                                     const int level,
                                     const int durability)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemDef itemDef = itemManager->GetItemDef(name, level);
    int materialId = itemDef.GetId();
    return AddItem(materialId, durability);
}

void NSStarmanLib::Inventory::AddItemWithSubID(const int id, const int subId, const int durability)
{
    ItemInfo itemInfo;
    itemInfo.SetId(id);
    itemInfo.SetSubId(subId);
    itemInfo.SetDurabilityCurrent(durability);
    m_itemInfoList.push_back(itemInfo);

    Sort();

    m_weight = CalcWeight();
    m_volumeCurrent = CalcVolume();
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
    m_volumeCurrent = CalcVolume();
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

bool NSStarmanLib::Inventory::ExistItem(const int id, const int subId)
{
    bool result = false;

    for (auto it = m_itemInfoList.begin(); it != m_itemInfoList.end(); ++it)
    {
        if (it->GetId() == id && it->GetSubId() == subId)
        {
            result = true;
            break;
        }
    }
    return result;
}

ItemInfo NSStarmanLib::Inventory::GetItemInfo(const int id, const int subId)
{
    if (ExistItem(id, subId) == false)
    {
        throw std::exception();
    }

    ItemInfo result;

    for (auto it = m_itemInfoList.begin(); it != m_itemInfoList.end(); ++it)
    {
        if (it->GetId() == id && it->GetSubId() == subId)
        {
            result = *it;
            break;
        }
    }
    return result;
}

// SubID�����X�g�Ŏ󂯎��
std::vector<int> NSStarmanLib::Inventory::GetSubIdList(const int id)
{
    std::vector<int> result;
    for (auto it = m_itemInfoList.begin(); it != m_itemInfoList.end(); ++it)
    {
        if (it->GetId() == id)
        {
            result.push_back(it->GetSubId());
        }
    }

    return result;
}


// �ϋv�x�𖳎����Č��𐔂���
// ���������āA�ϋv�x�̉��������A�C�e�����N���t�g�̑f�ނƂ��Ďg�p�o���ėǂ��Ƃ������Ƃɂ���
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

std::list<ItemInfo> NSStarmanLib::Inventory::GetAllItem()
{
    return m_itemInfoList;
}

float NSStarmanLib::Inventory::CalcVolume()
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
        result += itemDef.GetVolume();
    }

    m_volumeCurrent = result;
    return result;
}

float NSStarmanLib::Inventory::GetVolume() const
{
    return m_volumeCurrent;
}

void NSStarmanLib::Inventory::UpdateVolumeMax(const std::vector<ItemInfo>& bagMap)
{
    // �����l0�̑܁��ύڗ�3000mL
    // �����l1�̑܁��ύڗ�4000mL
    // �����l2�̑܁��ύڗ�5000mL
    // �����l3�̑܁��ύڗ�6000mL
    // �����l4�̑܁��ύڗ�7000mL
    // �����l5�̑܁��ύڗ�8000mL

    m_volumeMax = 5000.f; // �܂��Ȃ��Ă�5���b�g���܂ł͎��Ă�

    for (auto it = bagMap.begin(); it != bagMap.end(); ++it)
    {
        if (it->GetId() == -1)
        {
            continue;
        }

        if (it->GetDurabilityCurrent() <= 0)
        {
            continue;
        }

        if (it->GetItemDef().GetLevel() == -1)
        {
            m_volumeMax += 3000;
        }
        else if (it->GetItemDef().GetLevel() == 1)
        {
            m_volumeMax += 4000;
        }
        else if (it->GetItemDef().GetLevel() == 2)
        {
            m_volumeMax += 5000;
        }
        else if (it->GetItemDef().GetLevel() == 3)
        {
            m_volumeMax += 6000;
        }
        else if (it->GetItemDef().GetLevel() == 4)
        {
            m_volumeMax += 7000;
        }
        else if (it->GetItemDef().GetLevel() == 5)
        {
            m_volumeMax += 8000;
        }
    }
}

float NSStarmanLib::Inventory::GetVolumeMax() const
{
    return m_volumeMax;
}

void NSStarmanLib::Inventory::ReduceEquipBagDurability()
{
    auto allBag = StatusManager::GetObj()->GetAllBag();

    for (auto it = allBag.begin(); it != allBag.end(); ++it)
    {
        for (auto it2 = m_itemInfoList.begin(); it2 != m_itemInfoList.end(); ++it2)
        {
            if (it->GetId() == it2->GetId() && it->GetSubId() == it2->GetSubId())
            {
                auto dura = it2->GetDurabilityCurrent();
                if (dura >= 1)
                {
                    it2->SetDurabilityCurrent(dura - 1);
                    it->SetDurabilityCurrent(dura - 1);
                }
                break;
            }
        }
    }
    UpdateVolumeMax(allBag);

    StatusManager::GetObj()->UpdateBagDurability();
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

