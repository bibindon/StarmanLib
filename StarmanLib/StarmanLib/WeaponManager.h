#pragma once
#include <string>
#include <vector>

class Weapon
{
public:
    const std::string& GetId() const;
    const std::string& GetName() const;
    const std::string& GetDetail() const;
    const std::string& GetImageName() const;
    int GetNum() const;
    bool IsShow() const;

    void SetId(const std::string& id);
    void SetName(const std::string& name);
    void SetDetail(const std::string& detail);
    void SetImageName(const std::string& imageName);
    void SetNum(int num);
    void SetIsShow(bool isShow);
private:
    std::string m_id;
    std::string m_name;
    std::string m_detail;
    std::string m_imageName;
    int m_num = 0;
    bool m_isShow = false;
};

class WeaponManager
{
public:
    void Init(const std::string& csvfilename, const std::string& savefilename);
    std::vector<Weapon> GetWeaponList();
    void Save(const std::string& savefilename);
    Weapon GetByName(const std::string& name);
    void Update(const Weapon& weapon);

private:
    std::vector<Weapon> m_vecWeapon;
};

