#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{
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

// ItemMangerやInentory, Storehouseからは取得できない情報がある。
// 攻撃力や飛距離、最大耐久度など
// 耐久度はInventoryかStorehouseが管理しているので扱わない。
// TODO 武器一つ一つに対してこのクラスを持つ必要がない気がする
// +1の石斧と+2の石斧が5個ずつあった場合、10個Weaponが作られてしまうが
// 2個でで良い気がする。中身全部一緒だし。
class Weapon
{
public:

    std::string GetWeaponId() const;
    void SetWeaponId(const std::string& id);

    int GetItemId() const;
    void SetItemId(const int& id);

    int GetIdSub() const;
    void SetIdSub(int idSub);

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

    int m_idSub = 0; // 武器IDサブ。同じ武器を複数持てるようにするための識別子
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

    WeaponDef GetWeaponDef(const std::string& itemName) const;

    // 武器の削除ができることからSubIdは連番とは限らないことに注意
    bool ExistWeapon(const std::string& weaponId, const int subId, const int level = -1) const;
    Weapon GetWeapon(const std::string& weaponId, const int subId, const int level = -1) const;
    void AddWeapon(const std::string& weaponId, const Weapon& arg);
    void UpdateWeapon(const std::string& weaponId, const Weapon& arg);
    void RemoveWeapon(const std::string& weaponId, const int subId, const int level = -1);

    // 強化値を更新し、攻撃力、飛距離、耐久度を更新する
    void SetReinforceAndUpdateParam(const std::string& weaponId,
                                    const int subId,
                                    const int reinforce);

private:

    Weapon GetReinforcedWeapon(const Weapon& weapon,
                               const std::string& weaponId,
                               const int subId,
                               const int reinforce);

    // シングルトンオブジェクト
    static WeaponManager* obj;

    // このゲームにはインベントリと倉庫がある。
    // インベントリと倉庫でSubIDが被ることはない。
    // インベントリにある武器も、倉庫にある武器も区別なくm_weaponMapに保存する。
    std::unordered_map<std::string, WeaponDef> m_weaponDefMap;
    std::unordered_map<std::string, std::list<Weapon>> m_weaponMap;
};
}
