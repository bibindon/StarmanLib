#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{

// weapon.csvの内容そのまま
class WeaponDef
{

public:

    // ここでのIDはweapon.csvでのID
    std::string GetWeaponId() const;
    void SetWeaponId(const std::string& id);

    std::string GetName() const;
    void SetName(const std::string& name);

    std::string GetDetail() const;
    void SetDetail(const std::string& detail);

    std::string GetXfileName() const;
    void SetXfileName(const std::string& xfileName);

    std::string GetImageName() const;
    void SetImageName(const std::string& imageName);

    double GetWeight() const;
    void SetWeight(double weight);

    int GetVolume() const;
    void SetVolume(int volume);

    double GetAttackRate() const;
    void SetAttackRate(double attackRate);

    double GetAttackRateUp() const;
    void SetAttackRateUp(double attackRateUp);

    int GetReinforceMax() const;
    void SetReinforceMax(int reinforceMax);

    double GetFlightDistance() const;
    void SetFlightDistance(double flightDistance);

    double GetFlightDistanceUp() const;
    void SetFlightDistanceUp(double flightDistanceUp);

    double GetStaminaDown() const;
    void SetStaminaDown(double staminaDown);

    int GetDurability() const;
    void SetDurability(int durability);

    int GetDurabilityUp() const;
    void SetDurabilityUp(int durabilityUp);

    int GetOwnDamage() const;
    void SetOwnDamage(int ownDamage);

    bool GetIsShow() const;
    void SetIsShow(bool isShow);

private:
    std::string m_weaponId;
    std::string m_name;
    std::string m_detail;
    std::string m_xfileName;
    std::string m_imageName;
    double m_weight = 0.f; // 重量
    int m_volume = 0; // 体積
    double m_attackRate = 0.f; // 攻撃力補正
    double m_attackRateUp = 0.f; // 強化時の攻撃力補正の上昇値
    int m_reinforceMax = 0; // 強化可能回数
    double m_flightDistance = 0.f; // 飛距離
    double m_flightDistanceUp = 0.f; // 強化時の飛距離の上昇値
    double m_staminaDown = 0.f; // 消費スタミナ
    int m_durability = 0; // 耐久値（壊れるまでの回数）
    int m_durabilityUp = 0; // 強化時の耐久値の上昇値
    int m_ownDamage = 0; // 使用時の肉体損傷

    bool m_isShow = false; // 表示
};

// WeaponDefの定義では「強化値＋３の石斧の攻撃力」を知りたいとき
// 計算しないと分からない。
// 
// WeaponDefSubでは強化値ごとの攻撃力や飛距離などをあらかじめ計算して保持しておく。
// 
// 最大耐久度は管理するが現在の耐久度はInventoryかStorehouseが管理しているので扱わない。
class WeaponDefSub
{
public:

    std::string GetWeaponId() const;
    void SetWeaponId(const std::string& id);

    int GetItemId() const;
    void SetItemId(const int& id);

    int GetReinforce() const;
    void SetReinforce(int reinforce);

    double GetAttackRate() const;
    void SetAttackRate(double attackRate);

    double GetFlightDistance() const;
    void SetFlightDistance(double flightDistance);

    int GetDurabilityMax() const;
    void SetDurabilityMax(int durabilityMax);

private:

    std::string m_weaponId; // 武器ID（weapon.csv）
    int m_itemId = 0; // アイテムID（item.csv）

    int m_reinforce = 0;
    double m_attackRate = 0.f;
    double m_flightDistance = 0;
    int m_durabilityMax = 0;
};

class WeaponManager
{
public:
    static WeaponManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfilename,
              const std::string& savefilename,
              const bool decrypt = false);

    void Save(const std::string& savefilename,
              const bool encrypt = false);

    std::string GetDetail(const std::string& weaponName) const;
    std::string GetXfilename(const std::string& weaponName) const;
    std::string GetImageName(const std::string& weaponName) const;
    double GetWeight(const std::string& weaponName) const;
    int GetVolume(const std::string& weaponName) const;
    int GetReinforceMax(const std::string& weaponName) const;
    bool GetOwnDamage(const std::string& weaponName) const;
    bool GetIsShow(const std::string& weaponName) const;

    double GetAttackRate(const std::string& weaponName, const int level) const;
    double GetFlightDistance(const std::string& weaponName, const int level) const;
    double GetStaminaDown(const std::string& weaponName, const int level) const;
    int GetDurabilityMax(const std::string& weaponName, const int level) const;

private:


    // シングルトンオブジェクト
    static WeaponManager* obj;

    std::unordered_map<std::string, WeaponDef> m_weaponDefMap;
    std::vector<WeaponDefSub> m_weaponDefSubList;
};
}
