#include "WeaponManager.h"
#include "HeaderOnlyCsv.hpp"
#include "CaesarCipher.h"

#include "ItemManager.h"

#include <iomanip>
#include "Inventory.h"
#include "Storehouse.h"

using namespace NSStarmanLib;

WeaponManager* WeaponManager::obj;

WeaponManager* WeaponManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new WeaponManager();
    }
    return obj;
}

void WeaponManager::Destroy()
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
            weaponDef.SetReinforceMax(atoi(vss.at(i).at(7).c_str()));
            weaponDef.SetAttackRate(atof(vss.at(i).at(8).c_str()));
            weaponDef.SetAttackRateUp(atof(vss.at(i).at(9).c_str()));

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

            if (m_weaponDefMap.find(id) == m_weaponDefMap.end())
            {
                throw std::exception();
            }

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
    // m_weaponDefSubListを作る
    // 強化値ごとに武器情報をもつ配列
    for (auto it = m_weaponDefMap.begin(); it != m_weaponDefMap.end(); ++it)
    {
        WeaponDef weaponDef = it->second;

        // 強化値の数だけループする
        //
        // 最大強化値が-1の時は強化無し。
        // つまりWeaponDefSubは1つ必要になる
        // 
        // 最大強化値が1のときは1度は強化できる。
        // つまりWeaponDefSubは2つ必要になる
        int loopNum = 0;
        if (weaponDef.GetReinforceMax() == -1)
        {
            loopNum = 1;
        }
        else
        {
            loopNum = weaponDef.GetReinforceMax()+1;
        }

        for (int i = 0; i < loopNum; ++i)
        {
            // 強化値は0,1,2,3,4というようにはならず
            // -1,1,2,3,4,5という感じになる
            int level = 0;
            if (i == 0)
            {
                level = -1;
            }
            else
            {
                level = i;
            }

            WeaponDefSub weaponDefSub;
            weaponDefSub.SetWeaponId(weaponDef.GetWeaponId());

            ItemManager* itemManager = ItemManager::GetObj();
            ItemDef itemDef = itemManager->GetItemDef(weaponDef.GetName(), level);

            weaponDefSub.SetItemId(itemDef.GetId());

            weaponDefSub.SetReinforce(level);

            double temp = 0.0;
            int temp_i = 0;

            // 攻撃力補正値
            temp = weaponDef.GetAttackRate() + (weaponDef.GetAttackRateUp() * level);
            weaponDefSub.SetAttackRate(temp);

            // 飛距離
            temp = weaponDef.GetFlightDistance() + (weaponDef.GetFlightDistanceUp() * level);
            weaponDefSub.SetFlightDistance(temp);

            // 耐久力
            temp_i = weaponDef.GetDurability() + (weaponDef.GetDurabilityUp() * level);
            weaponDefSub.SetDurabilityMax(temp_i);

            m_weaponDefSubList.push_back(weaponDefSub);
        }
    }
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

std::string WeaponManager::GetDetail(const std::string& weaponName) const
{
    auto it = std::find_if(m_weaponDefMap.begin(), m_weaponDefMap.end(),
                           [&](const auto x)
                           {
                               return x.second.GetName() == weaponName;
                           });
    return it->second.GetDetail();
}

std::string WeaponManager::GetXfilename(const std::string& weaponName) const
{
    auto it = std::find_if(m_weaponDefMap.begin(), m_weaponDefMap.end(),
                           [&](const auto x)
                           {
                               return x.second.GetName() == weaponName;
                           });
    return it->second.GetXfileName();
}

std::string WeaponManager::GetImageName(const std::string& weaponName) const
{
    auto it = std::find_if(m_weaponDefMap.begin(), m_weaponDefMap.end(),
                           [&](const auto x)
                           {
                               return x.second.GetName() == weaponName;
                           });
    return it->second.GetImageName();
}

double WeaponManager::GetWeight(const std::string& weaponName) const
{
    auto it = std::find_if(m_weaponDefMap.begin(), m_weaponDefMap.end(),
                           [&](const auto x)
                           {
                               return x.second.GetName() == weaponName;
                           });
    return it->second.GetWeight();
}

int WeaponManager::GetVolume(const std::string& weaponName) const
{
    auto it = std::find_if(m_weaponDefMap.begin(), m_weaponDefMap.end(),
                           [&](const auto x)
                           {
                               return x.second.GetName() == weaponName;
                           });
    return it->second.GetVolume();
}

int WeaponManager::GetReinforceMax(const std::string& weaponName) const
{
    auto it = std::find_if(m_weaponDefMap.begin(), m_weaponDefMap.end(),
                           [&](const auto x)
                           {
                               return x.second.GetName() == weaponName;
                           });
    return it->second.GetReinforceMax();
}

int WeaponManager::GetOwnDamage(const std::string& weaponName) const
{
    auto it = std::find_if(m_weaponDefMap.begin(), m_weaponDefMap.end(),
                           [&](const auto x)
                           {
                               return x.second.GetName() == weaponName;
                           });
    return it->second.GetOwnDamage();
}

bool WeaponManager::GetIsShow(const std::string& weaponName) const
{
    auto it = std::find_if(m_weaponDefMap.begin(), m_weaponDefMap.end(),
                           [&](const auto x)
                           {
                               return x.second.GetName() == weaponName;
                           });
    return it->second.GetIsShow();
}

double WeaponManager::GetAttackRate(const std::string& weaponName, const int level) const
{
    std::string weaponId = GetItemName(weaponName);

    auto it = std::find_if(m_weaponDefSubList.begin(), m_weaponDefSubList.end(),
                           [&](const WeaponDefSub& x)
                           {
                               return x.GetWeaponId() == weaponId && x.GetReinforce() == level;
                           });

    if (it == m_weaponDefSubList.end())
    {
        throw std::exception();
    }

    return it->GetAttackRate();
}

double WeaponManager::GetFlightDistance(const std::string& weaponName, const int level) const
{
    std::string weaponId = GetItemName(weaponName);

    auto it = std::find_if(m_weaponDefSubList.begin(), m_weaponDefSubList.end(),
                           [&](const WeaponDefSub& x)
                           {
                               return x.GetWeaponId() == weaponId && x.GetReinforce() == level;
                           });

    return it->GetFlightDistance();
}

double WeaponManager::GetStaminaDown(const std::string& weaponName) const
{
    auto it = std::find_if(m_weaponDefMap.begin(), m_weaponDefMap.end(),
                           [&](const auto x)
                           {
                               return x.second.GetName() == weaponName;
                           });
    return it->second.GetStaminaDown();
}

int WeaponManager::GetDurabilityMax(const std::string& weaponName, const int level) const
{
    std::string weaponId = GetItemName(weaponName);

    auto it = std::find_if(m_weaponDefSubList.begin(), m_weaponDefSubList.end(),
                           [&](const WeaponDefSub& x)
                           {
                               return x.GetWeaponId() == weaponId && x.GetReinforce() == level;
                           });

    return it->GetDurabilityMax();
}

std::string NSStarmanLib::WeaponManager::GetItemName(const std::string& weaponName) const
{
    auto it = std::find_if(m_weaponDefMap.begin(), m_weaponDefMap.end(),
                           [&](const auto x)
                           {
                               return x.second.GetName() == weaponName;
                           });

    return it->second.GetWeaponId();
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

std::string WeaponDefSub::GetWeaponId() const
{
    return m_weaponId;
}

void WeaponDefSub::SetWeaponId(const std::string& id)
{
    m_weaponId = id;
}

int WeaponDefSub::GetItemId() const
{
    return m_itemId;
}

void WeaponDefSub::SetItemId(const int& id)
{
    m_itemId = id;
}

int WeaponDefSub::GetReinforce() const
{
    return m_reinforce;
}

void WeaponDefSub::SetReinforce(int reinforce)
{
    m_reinforce = reinforce;
}

double WeaponDefSub::GetAttackRate() const
{
    return m_attackRate;
}

void WeaponDefSub::SetAttackRate(double attackRate)
{
    m_attackRate = attackRate;
}

double WeaponDefSub::GetFlightDistance() const
{
    return m_flightDistance;
}

void WeaponDefSub::SetFlightDistance(double flightDistance)
{
    m_flightDistance = flightDistance;
}

int WeaponDefSub::GetDurabilityMax() const
{
    return m_durabilityMax;
}

void WeaponDefSub::SetDurabilityMax(int durabilityMax)
{
    m_durabilityMax = durabilityMax;
}

