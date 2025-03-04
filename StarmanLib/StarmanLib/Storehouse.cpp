#include "ItemManager.h"
#include "Storehouse.h"

#include <algorithm>
#include "Inventory.h"

#include "Util.h"

using namespace NSStarmanLib;

void Storehouse::Init(const std::string& csvfile,
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

    // �ۑ�����Ƃ��̂��߂Ƀt�@�C������ۑ�
    size_t pos = csvfile.find_last_of("/\\");

    if (pos == std::string::npos)
    {
        m_csvfilename = csvfile;
    }
    else
    {
        m_csvfilename = csvfile.substr(pos + 1);
    }
}

void Storehouse::Save(const std::string& csvfile,
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

void Storehouse::AddItem(const int id, const int durability)
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
    Inventory* inventory = Inventory::GetObj();

    std::vector<int> subIdList2 = inventory->GetSubIdList(id);

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
}

void NSStarmanLib::Storehouse::AddItem(const std::string name,
                                      const int level,
                                      const int durability)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemDef itemDef = itemManager->GetItemDef(name, level);
    int materialId = itemDef.GetId();
    AddItem(materialId, durability);
}

void NSStarmanLib::Storehouse::AddItemWithSubID(const int id, const int subId, const int durability)
{
    ItemInfo itemInfo;
    itemInfo.SetId(id);
    itemInfo.SetSubId(subId);
    itemInfo.SetDurabilityCurrent(durability);
    m_itemInfoList.push_back(itemInfo);

    Sort();
    m_weight = CalcWeight();
}

void Storehouse::RemoveItem(const int id, const int subId)
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

void NSStarmanLib::Storehouse::RemoveItem(const std::string name,
                                         const int subId,
                                         const int level)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemDef itemDef = itemManager->GetItemDef(name, level);
    int materialId = itemDef.GetId();
    RemoveItem(materialId, subId);
}

void NSStarmanLib::Storehouse::SetItemDurability(const int id,
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

bool NSStarmanLib::Storehouse::ExistItem(const int id, const int subId)
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

ItemInfo NSStarmanLib::Storehouse::GetItemInfo(const int id, const int subId)
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
std::vector<int> NSStarmanLib::Storehouse::GetSubIdList(const int id)
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
int Storehouse::CountItem(const int id)
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

int NSStarmanLib::Storehouse::CountItem(const std::string name, const int level)
{
    ItemManager* itemManager = ItemManager::GetObj();
    ItemDef itemDef = itemManager->GetItemDef(name, level);
    int materialId = itemDef.GetId();
    return CountItem(materialId);
}

float Storehouse::GetWeight()
{
    return m_weight;
}

std::list<ItemInfo> NSStarmanLib::Storehouse::GetAllItem()
{
    return m_itemInfoList;
}

void NSStarmanLib::Storehouse::SetXYZ(const float x, const float y, const float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void NSStarmanLib::Storehouse::GetXYZ(float* x, float* y, float* z)
{
    *x = m_x;
    *y = m_y;
    *z = m_z;
}

void NSStarmanLib::Storehouse::SetIsRaft(const bool arg)
{
    m_bRaft = arg;
}

bool NSStarmanLib::Storehouse::GetIsRaft() const
{
    return m_bRaft;
}

void NSStarmanLib::Storehouse::SetCsvFileName(const std::string arg)
{
    m_csvfilename = arg;
}

std::string NSStarmanLib::Storehouse::GetCsvFileName() const
{
    return m_csvfilename;
}

float Storehouse::CalcWeight()
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

void NSStarmanLib::Storehouse::Sort()
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

StorehouseManager* NSStarmanLib::StorehouseManager::m_obj = nullptr;

StorehouseManager* NSStarmanLib::StorehouseManager::Get()
{
    if (m_obj == nullptr)
    {
        m_obj = new StorehouseManager();
    }
    return m_obj;
}

void NSStarmanLib::StorehouseManager::Destroy()
{
    delete StorehouseManager::m_obj;
    StorehouseManager::m_obj = nullptr;
}

void NSStarmanLib::StorehouseManager::Init(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvfile, false);

    int work_i = 0;
    float work_f1 = 0;
    float work_f2 = 0;
    float work_f3 = 0;

    for (size_t i = 1; i < vvs.size(); ++i)
    {
        Storehouse storehouse;
        storehouse.Init(vvs.at(i).at(1));

        if (vvs.at(i).at(5) == "y")
        {
            storehouse.SetIsRaft(true);
        }
        else if (vvs.at(i).at(5) == "n")
        {
            storehouse.SetIsRaft(false);

            work_f1 = std::stof(vvs.at(i).at(2));
            work_f2 = std::stof(vvs.at(i).at(3));
            work_f3 = std::stof(vvs.at(i).at(4));

            storehouse.SetXYZ(work_f1, work_f2, work_f3);
        }
        else
        {
            throw std::exception();
        }

        work_i = std::stoi(vvs.at(i).at(0));
        m_StorehouseMap[work_i] = storehouse;
    }

    m_inited = true;
}

bool NSStarmanLib::StorehouseManager::Inited()
{
    return m_inited;
}

void NSStarmanLib::StorehouseManager::Save(const std::string& managerFile,
                                           const std::string& csvDir)
{
    std::vector<std::vector<std::string>> vvs;
    std::vector<std::string> vs;

    vs.push_back("ID");
    vs.push_back("�q�Ƀt�@�C��");
    vs.push_back("x");
    vs.push_back("y");
    vs.push_back("z");
    vs.push_back("�C�J�_");

    vvs.push_back(vs);
    vs.clear();

    for (auto it = m_StorehouseMap.begin(); it != m_StorehouseMap.end(); ++it)
    {
        vs.clear();

        vs.push_back(std::to_string(it->first));

        std::string work;
        work = csvDir;
        work += "/" + it->second.GetCsvFileName();

        vs.push_back(work);

        float x, y, z;

        it->second.GetXYZ(&x, &y, &z);

        vs.push_back(std::to_string(x));
        vs.push_back(std::to_string(y));
        vs.push_back(std::to_string(z));

        if (it->second.GetIsRaft())
        {
            vs.push_back("y");
        }
        else
        {
            vs.push_back("n");
        }
        vvs.push_back(vs);
    }

    Util::WriteToCsv(managerFile, vvs, false);

    for (auto it = m_StorehouseMap.begin(); it != m_StorehouseMap.end(); ++it)
    {
        std::string work;
        work = csvDir;
        work += "/" + it->second.GetCsvFileName();

        it->second.Save(work);
    }
}

std::vector<int> NSStarmanLib::StorehouseManager::GetStorehouseIdList()
{
    std::vector<int> vi;
    for (auto it = m_StorehouseMap.begin(); it != m_StorehouseMap.end(); ++it)
    {
        vi.push_back(it->first);
    }

    return vi;
}

Storehouse* NSStarmanLib::StorehouseManager::GetStorehouse(const int id)
{
    return &m_StorehouseMap.at(id);
}

Storehouse* NSStarmanLib::StorehouseManager::GetNearStorehouse(const float x, const float z)
{
    Storehouse* result = nullptr;
    for (auto it = m_StorehouseMap.begin(); it != m_StorehouseMap.end(); ++it)
    {
        float x2, y2, z2;

        it->second.GetXYZ(&x2, &y2, &z2);

        auto hit = Util::HitByBoundingBoxWithoutY(x, z, x2, z2, 3.f);
        if (hit)
        {
            result = &it->second;
            break;
        }
    }

    return result;
}

std::vector<int> NSStarmanLib::StorehouseManager::GetSubIdListFromAllStorehouse(const int id)
{
    std::vector<int> vi;

    for (auto it = m_StorehouseMap.begin(); it != m_StorehouseMap.end(); ++it)
    {
        auto work = it->second.GetSubIdList(id);
        vi.insert(vi.end(), work.begin(), work.end());
    }

    std::sort(vi.begin(), vi.end());

    return vi;
}

void NSStarmanLib::StorehouseManager::AddStorehouse()
{
    Storehouse storehouse;

    storehouse.SetIsRaft(true);

    // "storehouseRaft1.csv"�̂悤�ȃt�@�C���������
    std::string work;

    int RaftNum = 0;
    for (auto it = m_StorehouseMap.begin(); it != m_StorehouseMap.end(); ++it)
    {
        if (it->second.GetIsRaft())
        {
            ++RaftNum;
        }
    }

    work = "storehouseRaft" + std::to_string(RaftNum+1) + ".csv";

    storehouse.SetCsvFileName(work);

    size_t size_ = m_StorehouseMap.size();
    m_StorehouseMap[size_] = storehouse;
}

