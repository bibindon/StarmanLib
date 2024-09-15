#include "WeaponManager.h"
#include "HeaderOnlyCsv.hpp"

const std::string& Weapon::GetId() const
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

void Weapon::SetId(const std::string& id)
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

void WeaponManager::Init(const std::string& csvfilename, const std::string& savefilename)
{
    // 武器データを読む
    {
        std::vector<std::vector<std::string>> vss = csv::Read(csvfilename);

        // 先頭行は無視
        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            Weapon weapon;
            weapon.SetId(vss.at(i).at(0));
            weapon.SetName(vss.at(i).at(1));
            weapon.SetDetail(vss.at(i).at(2));
            weapon.SetImageName(vss.at(i).at(3));
            m_vecWeapon.push_back(weapon);
        }
    }
    // セーブデータを読み込む
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

std::vector<Weapon> WeaponManager::GetWeaponList()
{
    return m_vecWeapon;
}

void WeaponManager::Save(const std::string& savefilename)
{
    // ID、アイテム数、表示・非表示を出力
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;
    for (std::size_t i = 0; i < m_vecWeapon.size(); ++i)
    {
        vs.push_back(m_vecWeapon.at(i).GetId());
        vs.push_back(std::to_string(m_vecWeapon.at(i).GetNum()));
        if (m_vecWeapon.at(i).IsShow())
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
