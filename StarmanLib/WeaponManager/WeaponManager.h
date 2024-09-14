#pragma once
#include <string>
#include <vector>

class Weapon
{
public:
    int GetId() const;
    const std::string& GetName() const;
    const std::string& GetDetail() const;
    const std::string& GetImageName() const;
    int GetNum() const;
    bool IsShow() const;

    void SetId(int id);
    void SetName(const std::string& name);
    void SetDetail(const std::string& detail);
    void SetImageName(const std::string& imageName);
    void SetNum(int num);
    void SetIsShow(bool isShow);
private:
    int m_id = 0;
    std::string m_name;
    std::string m_detail;
    std::string m_imageName;
    int m_num = 0;
    bool m_isShow = false;
};

class WeaponManager
{
public:
    void Init(const std::string& csvfilename);
    std::vector<Weapon> GetWeaponList();
    void Save();
    Weapon GetByName(const std::string& name);
    void Update(const Weapon& weapon);

private:
    std::vector<Weapon> m_vecWeapon;
};

