#include "WeaponManager.h"
#include "HeaderOnlyCsv.hpp"
#include "CaesarCipher.h"

#include "ItemManager.h"

#include <iomanip>
#include "Inventory.h"
#include "Storehouse.h"

using namespace NSStarmanLib;

WeaponManager* WeaponManager::obj;

WeaponManager* NSStarmanLib::WeaponManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new WeaponManager();
    }
    return obj;
}

void NSStarmanLib::WeaponManager::Destroy()
{
    delete WeaponManager::obj;
    WeaponManager::obj = nullptr;
}

void WeaponManager::Init(const std::string& csvfilename,
                         const std::string& savefilename,
                         const bool decrypt)
{
    // ItemManagerクラスのInit関数が先に呼ばれている必要がある
    {
        if (ItemManager::GetObj()->Inited() == false)
        {
            throw std::exception();
        }
    }

    // 武器データを読む
    {
        std::vector<std::vector<std::string>> vss;
        // 暗号化されたファイルを復号化するか
        if (decrypt == false)
        {
            vss = csv::Read(csvfilename);
        }
        else
        {
            std::string work = CaesarCipher::DecryptFromFile(csvfilename);
            vss = csv::ReadFromString(work);
        }

        // 先頭行は無視
        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            WeaponDef weaponDef;
            weaponDef.SetWeaponId(vss.at(i).at(0));
            weaponDef.SetName(vss.at(i).at(1));
            weaponDef.SetDetail(vss.at(i).at(2));
            weaponDef.SetXfileName(vss.at(i).at(3));
            weaponDef.SetImageName(vss.at(i).at(4));
            weaponDef.SetWeight(atof(vss.at(i).at(5).c_str()));
            weaponDef.SetVolume(atoi(vss.at(i).at(6).c_str()));
            weaponDef.SetAttackRate(atof(vss.at(i).at(7).c_str()));
            weaponDef.SetAttackRateUp(atof(vss.at(i).at(8).c_str()));
            weaponDef.SetReinforceMax(atoi(vss.at(i).at(9).c_str()));

            weaponDef.SetFlightDistance(atof(vss.at(i).at(10).c_str()));
            weaponDef.SetFlightDistanceUp(atof(vss.at(i).at(11).c_str()));
            weaponDef.SetStaminaDown(atof(vss.at(i).at(12).c_str()));
            weaponDef.SetDurability(atoi(vss.at(i).at(13).c_str()));
            weaponDef.SetDurabilityUp(atoi(vss.at(i).at(14).c_str()));
            weaponDef.SetOwnDamage(atoi(vss.at(i).at(15).c_str()));

            m_weaponDefMap[weaponDef.GetWeaponId()] = weaponDef;
        }
    }
    // 保存された武器の情報を読み込む
    {
        std::vector<std::vector<std::string>> vss;
        // 暗号化されたファイルを復号化するか
        if (decrypt == false)
        {
            vss = csv::Read(savefilename);
        }
        else
        {
            std::string work = CaesarCipher::DecryptFromFile(savefilename);
            vss = csv::ReadFromString(work);
        }

        // 先頭行は無視
        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            std::string id = vss.at(i).at(0);
            std::string isShow = vss.at(i).at(1);
            if (isShow == "true")
            {
                m_weaponDefMap[id].SetIsShow(true);
            }
            else
            {
                m_weaponDefMap[id].SetIsShow(false);
            }
        }
    }
    // ItemManager, Inventory, Storehouseを利用して
    // 武器一つごとのセーブデータを読み込む
    {
        // Inventoryの武器をクラス内に保存
        ItemManager* itemManager = ItemManager::GetObj();

        std::vector<int> idList = itemManager->GetItemDef(ItemDef::ItemType::WEAPON);
        for (std::size_t i = 0; i < idList.size(); ++i)
        {
            int itemId = idList.at(i);
            ItemDef itemDef = itemManager->GetItemDef(itemId);
            std::string weaponId;

            for (auto it = m_weaponDefMap.begin(); it != m_weaponDefMap.end(); ++it)
            {
                if (it->second.GetName() == itemDef.GetName())
                {
                    weaponId = it->first;
                }
            }

            if (weaponId.empty())
            {
                throw std::exception();
            }

            // Inventory
            {
                Inventory* inventory = Inventory::GetObj();
                std::vector<int> subIdList = inventory->GetSubIdList(itemId);

                for (std::size_t j = 0; j < subIdList.size(); ++j)
                {
                    Weapon weapon;
                    weapon.SetWeaponId(weaponId);
                    weapon.SetItemId(itemId);
                    weapon.SetIdSub(subIdList.at(j));
                    weapon.SetReinforce(itemDef.GetLevel());
                    weapon = GetReinforcedWeapon(weapon, weaponId, subIdList.at(j), itemDef.GetLevel());
                    m_weaponMap[weaponId].push_back(weapon);
                }
            }

            // Storehouse
            {
                Storehouse* storehouse = Storehouse::GetObj();
                std::vector<int> subIdList = storehouse->GetSubIdList(itemId);

                for (std::size_t j = 0; j < subIdList.size(); ++j)
                {
                    Weapon weapon;
                    weapon.SetWeaponId(weaponId);
                    weapon.SetItemId(itemId);
                    weapon.SetIdSub(subIdList.at(j));
                    weapon.SetReinforce(itemDef.GetLevel());
                    weapon = GetReinforcedWeapon(weapon, weaponId, subIdList.at(j), itemDef.GetLevel());
                    m_weaponMap[weaponId].push_back(weapon);
                }
            }
        }
    }
}

WeaponDef WeaponManager::GetWeaponDef(const std::string& key) const
{
    return m_weaponDefMap.at(key);
}

bool NSStarmanLib::WeaponManager::ExistWeapon(const std::string& id, const int subId) const
{
    std::list<Weapon> weaponList = m_weaponMap.at(id);

    auto it = std::find_if(weaponList.begin(), weaponList.end(),
                           [&](const Weapon& x)
                           {
                               return x.GetIdSub() == subId;
                           });

    if (it != weaponList.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

Weapon WeaponManager::GetWeapon(const std::string& id, const int subId) const
{
    std::list<Weapon> weaponList = m_weaponMap.at(id);

    auto it = std::find_if(weaponList.begin(), weaponList.end(),
                           [&](const Weapon& x)
                           {
                               return x.GetIdSub() == subId;
                           });

    if (it == weaponList.end())
    {
        throw std::exception();
    }

    return *it;
}

void WeaponManager::AddWeapon(const std::string& id, const Weapon& arg)
{
    // SubIDが一致する武器が存在しているなら異常終了
    std::list<Weapon> weaponList = m_weaponMap.at(id);

    auto it = std::find_if(weaponList.begin(), weaponList.end(),
                           [&](const Weapon& x)
                           {
                               return x.GetIdSub() == arg.GetIdSub();
                           });

    if (it != weaponList.end())
    {
        throw std::exception();
    }

    m_weaponMap.at(id).push_back(arg);
}

void WeaponManager::UpdateWeapon(const std::string& id, const Weapon& arg)
{
    // SubIDが一致する武器が存在していないなら異常終了
    std::list<Weapon> weaponList = m_weaponMap.at(id);

    auto it = std::find_if(weaponList.begin(), weaponList.end(),
                           [&](const Weapon& x)
                           {
                               return x.GetIdSub() == arg.GetIdSub();
                           });

    if (it == weaponList.end())
    {
        throw std::exception();
    }

    *it = arg;
}

void NSStarmanLib::WeaponManager::RemoveWeapon(const std::string& id, const int subId)
{
}

void WeaponManager::Save(const std::string& savefilename,
                         const bool encrypt)
{
    {
        std::vector<std::vector<std::string>> vss;
        std::vector<std::string> vs;
        vs.push_back("ID");
        vs.push_back("表示・非表示");
        vss.push_back(vs);
        vs.clear();
        auto itBegin = m_weaponDefMap.begin();
        auto itEnd = m_weaponDefMap.end();
        for (;itBegin != itEnd; ++itBegin)
        {
            vs.push_back(itBegin->second.GetWeaponId());
            if (itBegin->second.GetIsShow())
            {
                vs.push_back("true");
            }
            else
            {
                vs.push_back("false");
            }
            vss.push_back(vs);
            vs.clear();
        }

        if (encrypt == false)
        {
            csv::Write(savefilename, vss);
        }
        else
        {
            std::stringstream ss;
            for (std::size_t i = 0; i < vss.size(); ++i)
            {
                for (std::size_t j = 0; j < vss.at(i).size(); ++j)
                {
                    ss << vss.at(i).at(j);
                    if (j != vss.at(i).size() - 1)
                    {
                        ss << ",";
                    }
                }
                ss << "\n";
            }
            CaesarCipher::EncryptToFile(ss.str(), savefilename);
        }
    }
}

void NSStarmanLib::WeaponManager::SetReinforceAndUpdateParam(const std::string& weaponId,
                                                             const int subId,
                                                             const int reinforce)
{
    // weapon.csvの定義を元に武器のステータスを設定する
    WeaponDef weaponDef = m_weaponDefMap.at(weaponId);

    std::list<Weapon> weaponList = m_weaponMap.at(weaponId);

    auto weapon = weaponList.end();
    for (auto it = weaponList.begin(); it != weaponList.end(); ++it)
    {
        if (it->GetIdSub() == subId)
        {
            weapon = it;
            break;
        }
    }

    if (weapon == weaponList.end())
    {
        throw std::exception();
    }

    // 新しい強化値
    weapon->SetReinforce(reinforce);

    double temp = 0.0;
    int temp_i = 0;

    // 新しい攻撃力補正値
    temp = weaponDef.GetAttackRate() + (weaponDef.GetAttackRateUp() * reinforce);
    weapon->SetAttackRate(temp);

    // 新しい飛距離
    temp = weaponDef.GetFlightDistance() + (weaponDef.GetFlightDistanceUp() * reinforce);
    weapon->SetFlightDistance(temp_i);

    // 新しい耐久力
    temp_i = weaponDef.GetDurability() + (weaponDef.GetDurabilityUp() * reinforce);
    weapon->SetDurabilityMax(temp_i);

    // 現在の耐久力を最大に回復。
    weapon->SetDurability(temp_i);
}

Weapon NSStarmanLib::WeaponManager::GetReinforcedWeapon(const Weapon& weapon,
                                                        const std::string& weaponId,
                                                        const int subId,
                                                        const int reinforce)
{
    return Weapon();
}

std::string WeaponDef::GetWeaponId() const
{
    return m_weaponId;
}

void WeaponDef::SetWeaponId(const std::string& id)
{
    m_weaponId = id;
}

std::string WeaponDef::GetName() const
{
    return m_name;
}

void WeaponDef::SetName(const std::string& name)
{
    m_name = name;
}

std::string WeaponDef::GetDetail() const
{
    return m_detail;
}

void WeaponDef::SetDetail(const std::string& detail)
{
    m_detail = detail;
}

std::string WeaponDef::GetXfileName() const
{
    return m_xfileName;
}

void WeaponDef::SetXfileName(const std::string& xfileName)
{
    m_xfileName = xfileName;
}

std::string WeaponDef::GetImageName() const
{
    return m_imageName;
}

void WeaponDef::SetImageName(const std::string& imageName)
{
    m_imageName = imageName;
}

double WeaponDef::GetWeight() const
{
    return m_weight;
}

void WeaponDef::SetWeight(double weight)
{
    m_weight = weight;
}

int WeaponDef::GetVolume() const
{
    return m_volume;
}

void WeaponDef::SetVolume(int volume)
{
    m_volume = volume;
}

double WeaponDef::GetAttackRate() const
{
    return m_attackRate;
}

void WeaponDef::SetAttackRate(double attackRate)
{
    m_attackRate = attackRate;
}

double WeaponDef::GetAttackRateUp() const
{
    return m_attackRateUp;
}

void WeaponDef::SetAttackRateUp(double attackRateUp)
{
    m_attackRateUp = attackRateUp;
}

int WeaponDef::GetReinforceMax() const
{
    return m_reinforceMax;
}

void WeaponDef::SetReinforceMax(int reinforceMax)
{
    m_reinforceMax = reinforceMax;
}

double WeaponDef::GetFlightDistance() const
{
    return m_flightDistance;
}

void WeaponDef::SetFlightDistance(double flightDistance)
{
    m_flightDistance = flightDistance;
}

double WeaponDef::GetFlightDistanceUp() const
{
    return m_flightDistanceUp;
}

void WeaponDef::SetFlightDistanceUp(double flightDistanceUp)
{
    m_flightDistanceUp = flightDistanceUp;
}

double WeaponDef::GetStaminaDown() const
{
    return m_staminaDown;
}

void WeaponDef::SetStaminaDown(double staminaDown)
{
    m_staminaDown = staminaDown;
}

int WeaponDef::GetDurability() const
{
    return m_durability;
}

void WeaponDef::SetDurability(int durability)
{
    m_durability = durability;
}

int WeaponDef::GetDurabilityUp() const
{
    return m_durabilityUp;
}

void WeaponDef::SetDurabilityUp(int durabilityUp)
{
    m_durabilityUp = durabilityUp;
}

int WeaponDef::GetOwnDamage() const
{
    return m_ownDamage;
}

void WeaponDef::SetOwnDamage(int ownDamage)
{
    m_ownDamage = ownDamage;
}

bool WeaponDef::GetIsShow() const
{
    return m_isShow;
}

void WeaponDef::SetIsShow(bool isShow)
{
    m_isShow = isShow;
}

std::string Weapon::GetWeaponId() const
{
    return m_weaponId;
}

void Weapon::SetWeaponId(const std::string& id)
{
    m_weaponId = id;
}

int NSStarmanLib::Weapon::GetItemId() const
{
    return m_itemId;
}

void NSStarmanLib::Weapon::SetItemId(const int& id)
{
    m_itemId = id;
}

int Weapon::GetIdSub() const
{
    return m_idSub;
}

void Weapon::SetIdSub(int idSub)
{
    m_idSub = idSub;
}

int Weapon::GetReinforce() const
{
    return m_reinforce;
}

void Weapon::SetReinforce(int reinforce)
{
    m_reinforce = reinforce;
}

double Weapon::GetAttackRate() const
{
    return m_attackRate;
}

void Weapon::SetAttackRate(double attackRate)
{
    m_attackRate = attackRate;
}

double Weapon::GetFlightDistance() const
{
    return m_flightDistance;
}

void Weapon::SetFlightDistance(double flightDistance)
{
    m_flightDistance = flightDistance;
}

int Weapon::GetDurabilityMax() const
{
    return m_durabilityMax;
}

void Weapon::SetDurabilityMax(int durabilityMax)
{
    m_durabilityMax = durabilityMax;
}

int Weapon::GetDurability() const
{
    return m_durability;
}

void Weapon::SetDurability(int durability)
{
    m_durability = durability;
}

