#include "WeaponManager.h"
#include "HeaderOnlyCsv.hpp"


void WeaponManager::Init(const std::string& csvfilename,
    const std::string& savefilename, const std::string& subSavefilename, const bool decrypt)
{
    // 武器データを読む
    {
        // TODO 暗号化・復号化
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
            weaponType.SetOwnDamage(atoi(vss.at(i).at(15).c_str()));

            m_weaponTypeMap[weaponType.GetId()] = weaponType;
        }
    }
    // 保存された武器の情報を読み込む
    {
        std::vector<std::vector<std::string>> vss = csv::Read(savefilename);
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
    // 武器一つごとのセーブデータを読み込む
    {
        std::vector<std::vector<std::string>> vss = csv::Read(subSavefilename);

        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            Weapon weapon;
            weapon.SetId(vss.at(i).at(0));
            weapon.SetIdSub(atoi(vss.at(i).at(1).c_str()));
            weapon.SetReinforce(atoi(vss.at(i).at(2).c_str()));
            weapon.SetAttackRate(atof(vss.at(i).at(3).c_str()));
            weapon.SetFlightDistance(atoi(vss.at(i).at(4).c_str()));
            weapon.SetDurabilityMax(atoi(vss.at(i).at(5).c_str()));
            weapon.SetDurability(atoi(vss.at(i).at(6).c_str()));
            m_weaponMap[vss.at(i).at(0)].push_back(weapon);
        }
    }
}

std::unordered_map<std::string, WeaponType> WeaponManager::GetWeaponTypeMap()
{
    return m_weaponTypeMap;
}

void WeaponManager::SetWeaponTypeMap(const std::unordered_map<std::string, WeaponType>& arg)
{
    m_weaponTypeMap = arg;
}

std::unordered_map<std::string, std::vector<Weapon>> WeaponManager::GetWeaponMap()
{
    return m_weaponMap;
}

void WeaponManager::SetWeaponMap(const std::unordered_map<std::string, std::vector<Weapon>>& arg)
{
    m_weaponMap = arg;
}

void WeaponManager::Save(
    const std::string& savefilename, const std::string& subSavefilename, const bool encrypt)
{
    {
        std::vector<std::vector<std::string>> vss;
        std::vector<std::string> vs;
        vs.push_back("ID");
        vs.push_back("表示・非表示");
        vss.push_back(vs);
        vs.clear();
        std::unordered_map<std::string, WeaponType>::iterator itBegin = m_weaponTypeMap.begin();
        std::unordered_map<std::string, WeaponType>::iterator itEnd = m_weaponTypeMap.end();
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
        csv::Write(savefilename, vss);
    }

    {
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
        std::unordered_map<std::string, std::vector<Weapon>>::iterator itBegin = m_weaponMap.begin();
        std::unordered_map<std::string, std::vector<Weapon>>::iterator itEnd = m_weaponMap.end();
        for (;itBegin != itEnd; ++itBegin)
        {
            for (std::size_t i = 0; i < itBegin->second.size(); ++i)
            {
                vs.push_back(itBegin->second.at(i).GetId());
                vs.push_back(std::to_string(itBegin->second.at(i).GetIdSub()));
                vs.push_back(std::to_string(itBegin->second.at(i).GetReinforce()));
                vs.push_back(std::to_string(itBegin->second.at(i).GetAttackRate()));
                vs.push_back(std::to_string(itBegin->second.at(i).GetFlightDistance()));
                vs.push_back(std::to_string(itBegin->second.at(i).GetDurabilityMax()));
                vs.push_back(std::to_string(itBegin->second.at(i).GetDurability()));
                vss.push_back(vs);
                vs.clear();
            }
        }
        csv::Write(subSavefilename, vss);
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

