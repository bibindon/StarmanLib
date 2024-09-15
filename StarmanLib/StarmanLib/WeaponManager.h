#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class WeaponType
{

public:
    std::string GetId() const;
    void SetId(const std::string& id);

    std::string GetName() const;
    void SetName(const std::string& name);

    std::string GetDetail() const;
    void SetDetail(const std::string& detail);

    std::string GetXfileName() const;
    void SetXfileName(const std::string& xfileName);

    std::string GetImageName() const;
    void SetImageName(const std::string& imageName);

    float GetWeight() const;
    void SetWeight(float weight);

    int GetVolume() const;
    void SetVolume(int volume);

    float GetAttackRate() const;
    void SetAttackRate(float attackRate);

    float GetAttackRateUp() const;
    void SetAttackRateUp(float attackRateUp);

    int GetReinforceMax() const;
    void SetReinforceMax(int reinforceMax);

    float GetFlightDistance() const;
    void SetFlightDistance(float flightDistance);

    float GetFlightDistanceUp() const;
    void SetFlightDistanceUp(float flightDistanceUp);

    float GetStaminaDown() const;
    void SetStaminaDown(float staminaDown);

    int GetDurability() const;
    void SetDurability(int durability);

    int GetDurabilityUp() const;
    void SetDurabilityUp(int durabilityUp);

    float GetOwnDamage() const;
    void SetOwnDamage(float ownDamage);

    bool GetIsShow() const;
    void SetIsShow(bool isShow);

private:
    std::string m_id;
    std::string m_name;
    std::string m_detail;
    std::string m_xfileName;
    std::string m_imageName;
    float m_weight = 0.f; // 重量
    int m_volume = 0; // 体積
    float m_attackRate = 0.f; // 攻撃力補正
    float m_attackRateUp = 0.f; // 強化時の攻撃力補正の上昇値
    int m_reinforceMax = 0; // 強化可能回数
    float m_flightDistance = 0.f; // 飛距離
    float m_flightDistanceUp = 0.f; // 強化時の飛距離の上昇値
    float m_staminaDown = 0.f; // 消費スタミナ
    int m_durability = 0; // 耐久値（壊れるまでの回数）
    int m_durabilityUp = 0; // 強化時の耐久値の上昇値
    float m_ownDamage = 0.f; // 使用時の肉体損傷

    bool m_isShow = false; // 表示
};

// マインクラフトで木の斧を二つ持つことができるように同じ武器を複数持つことができる。
class Weapon
{
public:

    std::string GetId() const;
    void SetId(const std::string& id);

    int GetIdSub() const;
    void SetIdSub(int idSub);

    int GetReinforce() const;
    void SetReinforce(int reinforce);

    float GetAttackRate() const;
    void SetAttackRate(float attackRate);

    float GetFlightDistance() const;
    void SetFlightDistance(float flightDistance);

    int GetDurabilityMax() const;
    void SetDurabilityMax(int durabilityMax);

    int GetDurability() const;
    void SetDurability(int durability);


private:
    std::string m_id; // 武器ID
    int m_idSub = 0; // 武器IDサブ。同じ武器を複数持てるようにするための識別子
    int m_reinforce = 0;
    float m_attackRate = 0.f;
    float m_flightDistance = 0.f;
    int m_durabilityMax = 0;
    int m_durability = 0;

};

class WeaponManager
{
public:
    void Init(const std::string& csvfilename, const std::string& savefilename);
    std::unordered_map<std::string, WeaponType> GetWeaponTypeMap();
    void Save(const std::string& savefilename);
//    std::vector<Weapon> GetByName(const std::string& name);
//    void Update(const Weapon& weapon);

private:
    std::unordered_map<std::string, WeaponType> m_weaponTypeMap;
    std::unordered_map<std::string, std::vector<Weapon>> m_WeaponMap;
};

