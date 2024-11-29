#include "WeaponManager.h"
#include "HeaderOnlyCsv.hpp"
#include "CaesarCipher.h"

#include "ItemManager.h"

#include <iomanip>

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
            WeaponType weaponType;
            weaponType.SetId(vss.at(i).at(0));
            weaponType.SetName(vss.at(i).at(1));
            weaponType.SetDetail(vss.at(i).at(2));
            weaponType.SetXfileName(vss.at(i).at(3));
            weaponType.SetImageName(vss.at(i).at(4));
            weaponType.SetWeight(atof(vss.at(i).at(5).c_str()));
            weaponType.SetVolume(atoi(vss.at(i).at(6).c_str()));
            weaponType.SetAttackRate(atof(vss.at(i).at(7).c_str()));
            weaponType.SetAttackRateUp(atof(vss.at(i).at(8).c_str()));
            weaponType.SetReinforceMax(atoi(vss.at(i).at(9).c_str()));

            weaponType.SetFlightDistance(atof(vss.at(i).at(10).c_str()));
            weaponType.SetFlightDistanceUp(atof(vss.at(i).at(11).c_str()));
            weaponType.SetStaminaDown(atof(vss.at(i).at(12).c_str()));
            weaponType.SetDurability(atoi(vss.at(i).at(13).c_str()));
            weaponType.SetDurabilityUp(atoi(vss.at(i).at(14).c_str()));
            weaponType.SetOwnDamage(atoi(vss.at(i).at(15).c_str()));

            m_weaponTypeMap[weaponType.GetId()] = weaponType;
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
                m_weaponTypeMap[id].SetIsShow(true);
            }
            else
            {
                m_weaponTypeMap[id].SetIsShow(false);
            }
        }
    }
    // ItemManager, Inventory, Storehouseを利用して
    // 武器一つごとのセーブデータを読み込む
    {
        std::vector<std::vector<std::string>> vss;
        // 暗号化されたファイルを復号化するか
        if (decrypt == false)
        {
            vss = csv::Read(subSavefilename);
        }
        else
        {
            std::string work = CaesarCipher::DecryptFromFile(subSavefilename);
            vss = csv::ReadFromString(work);
        }

        ItemManager* itemManager = ItemManager::GetObj();

        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            Weapon weapon;
            weapon.SetId(vss.at(i).at(0));
            weapon.SetIdSub(atoi(vss.at(i).at(1).c_str()));
            weapon.SetReinforce(atoi(vss.at(i).at(2).c_str()));
            weapon.SetAttackRate(atof(vss.at(i).at(3).c_str()));
            weapon.SetFlightDistance(atoi(vss.at(i).at(4).c_str()));

            ItemDef itemDef = itemManager->GetItemDef(weapon.GetId());
            weapon.SetDurabilityMax(itemDef.GetDurabilityMax());

            weapon.SetDurability(atoi(vss.at(i).at(5).c_str()));
            m_weaponMap[vss.at(i).at(0)].push_back(weapon);
        }
    }
}

WeaponType WeaponManager::GetWeaponType(const std::string& key) const
{
    return m_weaponTypeMap.at(key);
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
        auto itBegin = m_weaponTypeMap.begin();
        auto itEnd = m_weaponTypeMap.end();
        for (;itBegin != itEnd; ++itBegin)
        {
            vs.push_back(itBegin->second.GetId());
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

void NSStarmanLib::WeaponManager::SetReinforce(const std::string& name,
                                               const int subId,
                                               const int reinforce)
{
}

std::string WeaponType::GetId() const
{
    return m_id;
}

void WeaponType::SetId(const std::string& id)
{
    m_id = id;
}

std::string WeaponType::GetName() const
{
    return m_name;
}

void WeaponType::SetName(const std::string& name)
{
    m_name = name;
}

std::string WeaponType::GetDetail() const
{
    return m_detail;
}

void WeaponType::SetDetail(const std::string& detail)
{
    m_detail = detail;
}

std::string WeaponType::GetXfileName() const
{
    return m_xfileName;
}

void WeaponType::SetXfileName(const std::string& xfileName)
{
    m_xfileName = xfileName;
}

std::string WeaponType::GetImageName() const
{
    return m_imageName;
}

void WeaponType::SetImageName(const std::string& imageName)
{
    m_imageName = imageName;
}

double WeaponType::GetWeight() const
{
    return m_weight;
}

void WeaponType::SetWeight(double weight)
{
    m_weight = weight;
}

int WeaponType::GetVolume() const
{
    return m_volume;
}

void WeaponType::SetVolume(int volume)
{
    m_volume = volume;
}

double WeaponType::GetAttackRate() const
{
    return m_attackRate;
}

void WeaponType::SetAttackRate(double attackRate)
{
    m_attackRate = attackRate;
}

double WeaponType::GetAttackRateUp() const
{
    return m_attackRateUp;
}

void WeaponType::SetAttackRateUp(double attackRateUp)
{
    m_attackRateUp = attackRateUp;
}

int WeaponType::GetReinforceMax() const
{
    return m_reinforceMax;
}

void WeaponType::SetReinforceMax(int reinforceMax)
{
    m_reinforceMax = reinforceMax;
}

double WeaponType::GetFlightDistance() const
{
    return m_flightDistance;
}

void WeaponType::SetFlightDistance(double flightDistance)
{
    m_flightDistance = flightDistance;
}

double WeaponType::GetFlightDistanceUp() const
{
    return m_flightDistanceUp;
}

void WeaponType::SetFlightDistanceUp(double flightDistanceUp)
{
    m_flightDistanceUp = flightDistanceUp;
}

double WeaponType::GetStaminaDown() const
{
    return m_staminaDown;
}

void WeaponType::SetStaminaDown(double staminaDown)
{
    m_staminaDown = staminaDown;
}

int WeaponType::GetDurability() const
{
    return m_durability;
}

void WeaponType::SetDurability(int durability)
{
    m_durability = durability;
}

int WeaponType::GetDurabilityUp() const
{
    return m_durabilityUp;
}

void WeaponType::SetDurabilityUp(int durabilityUp)
{
    m_durabilityUp = durabilityUp;
}

int WeaponType::GetOwnDamage() const
{
    return m_ownDamage;
}

void WeaponType::SetOwnDamage(int ownDamage)
{
    m_ownDamage = ownDamage;
}

bool WeaponType::GetIsShow() const
{
    return m_isShow;
}

void WeaponType::SetIsShow(bool isShow)
{
    m_isShow = isShow;
}

std::string Weapon::GetId() const
{
    return m_id;
}

void Weapon::SetId(const std::string& id)
{
    m_id = id;
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

int Weapon::GetFlightDistance() const
{
    return m_flightDistance;
}

void Weapon::SetFlightDistance(int flightDistance)
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

