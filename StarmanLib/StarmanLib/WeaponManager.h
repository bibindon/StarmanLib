#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{
class WeaponType
{

public:

    // ここでのIDはweapon.csvでのID
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
    std::string m_id;
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

// 同じ武器を複数持つために定義された武器クラス。
// マインクラフトでは耐久度の高い木の斧と耐久度の低い木の斧の二つ持つことができるように
// このゲームでも同じ武器を複数持つことができる。
class Weapon
{
public:

    std::string GetId() const;
    void SetId(const std::string& id);

    int GetIdSub() const;
    void SetIdSub(int idSub);

    int GetReinforce() const;
    void SetReinforce(int reinforce);

    double GetAttackRate() const;
    void SetAttackRate(double attackRate);

    int GetFlightDistance() const;
    void SetFlightDistance(int flightDistance);

    int GetDurabilityMax() const;
    void SetDurabilityMax(int durabilityMax);

    int GetDurability() const;
    void SetDurability(int durability);

private:

    std::string m_id; // 武器ID
    int m_idSub = 0; // 武器IDサブ。同じ武器を複数持てるようにするための識別子
    int m_reinforce = 0;
    double m_attackRate = 0.f;
    int m_flightDistance = 0;
    int m_durabilityMax = 0;
    int m_durability = 0;
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

    WeaponType GetWeaponType(const std::string& key) const;

    // 武器の削除ができることからSubIdは連番とは限らないことに注意
    bool ExistWeapon(const std::string& id, const int subId) const;
    Weapon GetWeapon(const std::string& id, const int subId) const;
    void AddWeapon(const std::string& id, const Weapon& arg);
    void UpdateWeapon(const std::string& id, const Weapon& arg);
    void RemoveWeapon(const std::string& id, const int subId);

    // TODO 強化値を更新し、攻撃力、飛距離、耐久度を更新する
    void SetReinforce(const std::string& name, const int subId, const int reinforce);

private:

    // シングルトンオブジェクト
    static WeaponManager* obj;

    // このゲームにはインベントリと倉庫がある。
    // インベントリにある武器も、倉庫にある武器も区別なくm_weaponMapに保存する。
    std::unordered_map<std::string, WeaponType> m_weaponTypeMap;
    std::unordered_map<std::string, std::list<Weapon>> m_weaponMap;
};
}
