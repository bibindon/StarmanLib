#include "WeaponManager.h"
#include "HeaderOnlyCsv.hpp"


void WeaponManager::Init(const std::string& csvfilename, const std::string& savefilename)
{
    // 武器データを読む
    {
        std::vector<std::vector<std::string>> vss = csv::Read(csvfilename);

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
            weaponType.SetOwnDamage(atof(vss.at(i).at(15).c_str()));
            if (vss.at(i).at(16) == "true")
            {
                weaponType.SetOwnDamage(true);
            }
            else
            {
                weaponType.SetOwnDamage(false);
            }

            m_WeaponMap[weaponType.GetId()] = weaponType;
        }
    }
    // TODO セーブデータを読み込む
    {
        std::vector<std::vector<std::string>> vss = csv::Read(savefilename);

        for (std::size_t i = 0; i < vss.size(); ++i)
        {
            for (std::size_t j = 0; j < m_vecWeapon.size(); ++j)
            {
                if (vss.at(i).at(0) == m_vecWeapon.at(j).GetId())
                {
                    int num = std::atoi(vss.at(i).at(1).c_str());
                    m_vecWeapon.at(j).SetNum(num);
                    if (vss.at(i).at(2) == "true")
                    {
                        m_vecWeapon.at(j).SetIsShow(true);
                    }
                    else
                    {
                        m_vecWeapon.at(j).SetIsShow(false);
                    }
                }
            }
        }
    }
}

std::unordered_map<std::string, WeaponType> WeaponManager::GetWeaponTypeMap()
{
    return m_weaponTypeMap;
}

void WeaponManager::Save(const std::string& savefilename)
{
    // ID、アイテム数、表示・非表示を出力
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;
    vs.push_back("ID");
    vs.push_back("サブID");
    vs.push_back("強化値");
    vs.push_back("攻撃力補正の上昇値");
    vs.push_back("飛距離の上昇値");
    vs.push_back("耐久値の初期値");
    vs.push_back("現在の耐久値");
    vss.push_back(vs);
    vs.clear();
    std::unordered_map<std::string, std::vector<Weapon>>::iterator itBegin = m_WeaponMap.begin();
    std::unordered_map<std::string, std::vector<Weapon>>::iterator itEnd = m_WeaponMap.end();
    for (;itBegin != itEnd; ++itBegin)
    {
        for (int i = 0; i < itBegin->second.size(); ++i)
        {
            vs.push_back(itBegin->second.at(i).GetId());
            vs.push_back(std::to_string(itBegin->second.at(i).GetIdSub()));
            vs.push_back(std::to_string(itBegin->second.at(i).GetReinforce()));
            vs.push_back(std::to_string(itBegin->second.at(i).GetAttackRate()));
            vs.push_back(std::to_string(itBegin->second.at(i).GetFlightDistance()));
            vs.push_back(std::to_string(itBegin->second.at(i).GetDurabilityMax()));
            vs.push_back(std::to_string(itBegin->second.at(i).GetDurability()));
        }
        vss.push_back(vs);
        vs.clear();
    }
    csv::Write(savefilename, vss);
}

Weapon WeaponManager::GetByName(const std::string& name)
{
    std::vector<Weapon>::iterator it = std::find_if( m_vecWeapon.begin(), m_vecWeapon.end(),
        [&] (Weapon& weapon)
        {
            return weapon.GetName() == name;
        }
    );
    return *it;
}

void WeaponManager::Update(const Weapon& weapon)
{
    for (std::size_t i = 0; i < m_vecWeapon.size(); ++i)
    {
        if (weapon.GetId() == m_vecWeapon.at(i).GetId())
        {
            m_vecWeapon.at(i).SetName(weapon.GetName());
            m_vecWeapon.at(i).SetDetail(weapon.GetDetail());
            m_vecWeapon.at(i).SetImageName(weapon.GetImageName());
            m_vecWeapon.at(i).SetNum(weapon.GetNum());
            m_vecWeapon.at(i).SetIsShow(weapon.IsShow());
        }
    }
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

float WeaponType::GetWeight() const
{
    return m_weight;
}

void WeaponType::SetWeight(float weight)
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

float WeaponType::GetAttackRate() const
{
    return m_attackRate;
}

void WeaponType::SetAttackRate(float attackRate)
{
    m_attackRate = attackRate;
}

float WeaponType::GetAttackRateUp() const
{
    return m_attackRateUp;
}

void WeaponType::SetAttackRateUp(float attackRateUp)
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

float WeaponType::GetFlightDistance() const
{
    return m_flightDistance;
}

void WeaponType::SetFlightDistance(float flightDistance)
{
    m_flightDistance = flightDistance;
}

float WeaponType::GetFlightDistanceUp() const
{
    return m_flightDistanceUp;
}

void WeaponType::SetFlightDistanceUp(float flightDistanceUp)
{
    m_flightDistanceUp = flightDistanceUp;
}

float WeaponType::GetStaminaDown() const
{
    return m_staminaDown;
}

void WeaponType::SetStaminaDown(float staminaDown)
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

float WeaponType::GetOwnDamage() const
{
    return m_ownDamage;
}

void WeaponType::SetOwnDamage(float ownDamage)
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

float Weapon::GetAttackRate() const
{
    return m_attackRate;
}

void Weapon::SetAttackRate(float attackRate)
{
    m_attackRate = attackRate;
}

float Weapon::GetFlightDistance() const
{
    return m_flightDistance;
}

void Weapon::SetFlightDistance(float flightDistance)
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

