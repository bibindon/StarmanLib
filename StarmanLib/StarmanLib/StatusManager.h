#pragma once

#include <string>
#include "ItemManager.h"

// 一般的に、「攻撃を受けたとき、最終的に負うダメージがいくつになるか」は
// それなりに複雑なコードになる。
// ゲーム本体にその複雑さを持ち込まなくてよいようにしたい。

namespace NSStarmanLib
{
// PlayerのステータスとNPCのステータスは別のものとして用意する。
// ここで扱うステータスはプレイヤーのStatus。

class Status
{
public:

    float GetBodyStaminaCurrent() const;
    void SetBodyStaminaCurrent(float mbodyStaminaCurrent);

    float GetBodyStaminaMax() const;
    void SetBodyStaminaMax(float mbodyStaminaMax);

    float GetBodyStaminaMaxSub() const;
    void SetBodyStaminaMaxSub(float mbodyStaminaMaxSub);

    float GetBrainStaminaCurrent() const;
    void SetBrainStaminaCurrent(float mbrainStaminaCurrent);

    float GetBrainStaminaMax() const;
    void SetBrainStaminaMax(float mbrainStaminaMax);

    float GetBrainStaminaMaxSub() const;
    void SetBrainStaminaMaxSub(float mbrainStaminaMaxSub);

    float GetExplosivePower() const;
    void SetExplosivePower(float mexplosivePower);

    float GetMuscleCurrent() const;
    void SetMuscleCurrent(float mmuscleCurrent);

    float GetMuscleMax() const;
    void SetMuscleMax(float mmuscleMax);

    float GetCarboCurrent() const;
    void SetCarboCurrent(float mcarbo);

    float GetCarboMax() const;
    void SetCarboMax(float mcarbo);

    float GetProteinCurrent() const;
    void SetProteinCurrent(float mprotein);

    float GetProteinMax() const;
    void SetProteinMax(float mprotein);

    float GetLipidCurrent() const;
    void SetLipidCurrent(float mlipid);

    float GetLipidMax() const;
    void SetLipidMax(float mlipid);

    float GetVitaminCurrent() const;
    void SetVitaminCurrent(float mvitamin);

    float GetVitaminMax() const;
    void SetVitaminMax(float mvitamin);

    float GetMineralCurrent() const;
    void SetMineralCurrent(float mmineral);

    float GetMineralMax() const;
    void SetMineralMax(float mmineral);

    float GetWaterCurrent() const;
    void SetWaterCurrent(float mwater);

    float GetWaterMax() const;
    void SetWaterMax(float mwater);

    bool GetFractureArm() const;
    void SetFractureArm(bool mfractureArm);

    bool GetFractureLeg() const;
    void SetFractureLeg(bool mfractureLeg);

    bool GetHeadache() const;
    void SetHeadache(bool mheadache);

    bool GetCold() const;
    void SetCold(bool mcold);

    bool GetStomachache() const;
    void SetStomachache(bool mstomachache);

    bool GetSleep() const;
    void SetSleep(bool msleep);

    bool GetDehydration() const;
    void SetDehydration(bool mdehydration);

    bool GetLackOfSleep() const;
    void SetLackOfSleep(bool mlackOfSleep);

    bool GetDead() const;
    void SetDead(const bool arg);

private:

    // 体のスタミナ（現在値）
    float m_bodyStaminaCurrent { 0.f };

    // 体のスタミナ（最大値）
    float m_bodyStaminaMax { 0.f };

    // 体のスタミナ（回復可能値）
    // 現実世界では走った後、座るとある程度体力を回復できるが
    // どれだけ座り続けても全快するわけではない。
    // このときの、回復できる最大を表す値。
    float m_bodyStaminaMaxSub { 0.f };

    // 脳のスタミナ（現在値）
    float m_brainStaminaCurrent { 0.f };

    // 脳のスタミナ（最大値）
    float m_brainStaminaMax { 0.f };

    // 脳のスタミナ（回復可能値）
    // 現実世界では頭を使った後、ボーっとすればある程度、脳の体力を回復できるが
    // どれだけ休み続けても全快するわけではない。
    // このときの、回復できる最大を表す値。
    float m_brainStaminaMaxSub { 0.f };

    // 瞬発力
    // 速筋の太さ
    float m_explosivePower { 0.f };

    // 肉体の修復度（現在値）
    // 損傷・疲労によって低下する
    // 数値が大きいほど、損傷・疲労していない
    float m_muscleCurrent { 0.f };

    // 肉体の修復度（最大値）
    // 損傷・疲労によって低下する。
    float m_muscleMax { 0.f };

    // 糖質（現在値）
    float m_carboCurrent { 0.f };

    // 糖質（最大値）
    float m_carboMax { 0.f };

    // タンパク質（現在値）
    float m_proteinCurrent { 0.f };

    // タンパク質（最大値）
    float m_proteinMax { 0.f };

    // 脂質（現在値）
    float m_lipidCurrent { 0.f };

    // 脂質（最大値）
    float m_lipidMax { 0.f };

    // ビタミン（現在値）
    float m_vitaminCurrent { 0.f };

    // ビタミン（最大値）
    float m_vitaminMax { 0.f };

    // ミネラル（現在値）
    float m_mineralCurrent { 0.f };

    // ミネラル（最大値）
    float m_mineralMax { 0.f };

    // 水分（現在値）
    float m_waterCurrent { 0.f };

    // 水分（最大値）
    float m_waterMax { 0.f };

    // 腕骨折
    bool m_fractureArm { false };

    // 足骨折
    bool m_fractureLeg { false };

    // 頭痛
    bool m_headache { false };

    // 風邪
    bool m_cold { false };

    // 腹痛
    bool m_stomachache { false };

    // 睡眠
    bool m_sleep { false };

    // 脱水症状
    bool m_dehydration { false };

    // 睡眠不足
    bool m_lackOfSleep { false };

    // 死亡
    bool m_dead = false;
};

class StatusManager
{
public:

    enum class PlayerState
    {
        // 立ち状態と歩き状態は同じくらい疲れるべき
        // 立ち状態
        STAND,

        // 歩き状態
        WALK,

        // 座り状態
        SIT,

        // 寝そべり
        LYING_DOWN,

        // ジョギング
        JOGGING,

        // 全力疾走
        SPRINTING,
    };

    static StatusManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);

    // 1秒に一度呼ばれる想定
    void Update();

    void Save(const std::string& csvfile);

    // 歩行速度。重量や健康度、筋力などありとあらゆるパラメーターが影響する
    float GetWalkSpeed();

    // 攻撃力。重量や健康度、筋力などありとあらゆるパラメーターが影響する
    float GetAttackPower();

    // 防御力。重量や健康度、筋力などありとあらゆるパラメーターが影響する
    float GetDefensePower();

    // 食材を食べる
    void Eat(const ItemDef& food);

    // 寝る
    bool Sleep();

    // 会話する
    // 会話したら脳の体力が減る。
    void Talk();

    // 魔法を使う
    // 魔法を使ったら脳の体力が減る
    void UseMagic();

    //-------------------------------------------------------
    // Statusクラスの同名の関数を呼ぶ
    //-------------------------------------------------------

    float GetBodyStaminaCurrent() const;
    void SetBodyStaminaCurrent(float mbodyStaminaCurrent);

    float GetBodyStaminaMax() const;
    void SetBodyStaminaMax(float mbodyStaminaMax);

    float GetBodyStaminaMaxSub() const;
    void SetBodyStaminaMaxSub(float mbodyStaminaMaxSub);

    float GetBrainStaminaCurrent() const;
    void SetBrainStaminaCurrent(float mbrainStaminaCurrent);

    float GetBrainStaminaMax() const;
    void SetBrainStaminaMax(float mbrainStaminaMax);

    float GetBrainStaminaMaxSub() const;
    void SetBrainStaminaMaxSub(float mbrainStaminaMaxSub);

    float GetExplosivePower() const;
    void SetExplosivePower(float mexplosivePower);

    float GetMuscleCurrent() const;
    void SetMuscleCurrent(float mmuscleCurrent);

    float GetMuscleMax() const;
    void SetMuscleMax(float mmuscleMax);

    float GetCarboCurrent() const;
    void SetCarboCurrent(float mcarbo);

    float GetCarboMax() const;
    void SetCarboMax(float mcarbo);

    float GetProteinCurrent() const;
    void SetProteinCurrent(float mprotein);

    float GetProteinMax() const;
    void SetProteinMax(float mprotein);

    float GetLipidCurrent() const;
    void SetLipidCurrent(float mlipid);

    float GetLipidMax() const;
    void SetLipidMax(float mlipid);

    float GetVitaminCurrent() const;
    void SetVitaminCurrent(float mvitamin);

    float GetVitaminMax() const;
    void SetVitaminMax(float mvitamin);

    float GetMineralCurrent() const;
    void SetMineralCurrent(float mmineral);

    float GetMineralMax() const;
    void SetMineralMax(float mmineral);

    float GetWaterCurrent() const;
    void SetWaterCurrent(float mwater);

    float GetWaterMax() const;
    void SetWaterMax(float mwater);

    bool GetFractureArm() const;
    void SetFractureArm(bool mfractureArm);

    bool GetFractureLeg() const;
    void SetFractureLeg(bool mfractureLeg);

    bool GetHeadache() const;
    void SetHeadache(bool mheadache);

    bool GetCold() const;
    void SetCold(bool mcold);

    bool GetStomachache() const;
    void SetStomachache(bool mstomachache);

    bool GetSleep() const;
    void SetSleep(bool msleep);

    bool GetDehydration() const;
    void SetDehydration(bool mdehydration);

    bool GetLackOfSleep() const;
    void SetLackOfSleep(bool mlackOfSleep);

    void SetPlayerAction(const PlayerState arg);

    bool GetDead() const;
    void SetDead(const bool arg);

    // 装備武器
    ItemInfo GetEquipWeapon() const;
    void SetEquipWeapon(const ItemInfo& arg);

    // 強い精神ストレス
    void SetSuperStress();

private:

    // シングルトンオブジェクト
    static StatusManager* obj;

    Status m_status;

    PlayerState m_playerState { PlayerState::STAND };

    // 体のスタミナが70％以下になったことが一日に1度でもあった
    bool m_training = false;

    // 前回日時をチェックした時の日
    int m_previousDay = 0;

    // 前回日時をチェックした時の時刻
    int m_previousHour = 0;

    // 朝8時をまたいだ
    bool m_over8clock = false;

    // 装備武器
    ItemInfo m_EquipWeapon;
};
}

