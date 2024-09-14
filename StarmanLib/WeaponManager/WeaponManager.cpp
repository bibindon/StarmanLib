#include "WeaponManager.h"

int Weapon::GetId() const
{
    return m_id;
}

const std::string& Weapon::GetName() const
{
    return m_name;
}

const std::string& Weapon::GetDetail() const
{
    return m_detail;
}

const std::string& Weapon::GetImageName() const
{
    return m_imageName;
}

int Weapon::GetNum() const
{
    return m_num;
}

bool Weapon::IsShow() const
{
    return m_isShow;
}

void Weapon::SetId(int id)
{
    m_id = id;
}

void Weapon::SetName(const std::string& name)
{
    m_name = name;
}

void Weapon::SetDetail(const std::string& detail)
{
    m_detail = detail;
}

void Weapon::SetImageName(const std::string& imageName)
{
    m_imageName = imageName;
}

void Weapon::SetNum(int num)
{
    m_num = num;
}

void Weapon::SetIsShow(bool isShow)
{
    m_isShow = isShow;
}

void WeaponManager::Init(const std::string& csvfilename)
{
    // TODO
    // weapon.csvを読む
    // TODO
    // weaponSaveData.csvを読む
    // 
}

std::vector<Weapon> WeaponManager::GetWeaponList()
{
    return m_vecWeapon;
}

void WeaponManager::Save()
{
    // TODO
    // ID、アイテム数、表示・非表示を出力
    // weaponSaveData.csv
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
