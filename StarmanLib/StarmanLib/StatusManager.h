#pragma once

#include <string>
#include "ItemManager.h"

// ��ʓI�ɁA�u�U�����󂯂��Ƃ��A�ŏI�I�ɕ����_���[�W�������ɂȂ邩�v��
// ����Ȃ�ɕ��G�ȃR�[�h�ɂȂ�B
// �Q�[���{�̂ɂ��̕��G�����������܂Ȃ��Ă悢�悤�ɂ������B

// ����𑕔����Ă��Ȃ��ꍇ�A�A�C�e��ID��-1�������Ă���B

namespace NSStarmanLib
{
enum class eMagicType
{
    None,
    Fire,
    Ice,
    Dark,
};

enum class eBagPos
{
    None,
    Back1,
    Back2,
    Front,
    Left,
    Right,
};

// Player�̃X�e�[�^�X��NPC�̃X�e�[�^�X�͕ʂ̂��̂Ƃ��ėp�ӂ���B
// �����ň����X�e�[�^�X�̓v���C���[��Status�B

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

    float GetSatiety() const;
    void SetSatiety(const float arg);

    float GetX() const;
    void SetX(const float arg);

    float GetY() const;
    void SetY(const float arg);

    float GetZ() const;
    void SetZ(const float arg);

private:

    // �̂̃X�^�~�i�i���ݒl�j
    float m_bodyStaminaCurrent { 0.f };

    // �̂̃X�^�~�i�i�ő�l�j
    float m_bodyStaminaMax { 0.f };

    // �̂̃X�^�~�i�i�񕜉\�l�j
    // �������E�ł͑�������A����Ƃ�����x�̗͂��񕜂ł��邪
    // �ǂꂾ�����葱���Ă��S������킯�ł͂Ȃ��B
    // ���̂Ƃ��́A�񕜂ł���ő��\���l�B
    float m_bodyStaminaMaxSub { 0.f };

    // �]�̃X�^�~�i�i���ݒl�j
    float m_brainStaminaCurrent { 0.f };

    // �]�̃X�^�~�i�i�ő�l�j
    float m_brainStaminaMax { 0.f };

    // �]�̃X�^�~�i�i�񕜉\�l�j
    // �������E�ł͓����g������A�{�[���Ƃ���΂�����x�A�]�̗̑͂��񕜂ł��邪
    // �ǂꂾ���x�ݑ����Ă��S������킯�ł͂Ȃ��B
    // ���̂Ƃ��́A�񕜂ł���ő��\���l�B
    float m_brainStaminaMaxSub { 0.f };

    // �u����
    // ���؂̑���
    float m_explosivePower { 0.f };

    // ���̂̏C���x�i���ݒl�j
    // �����E��J�ɂ���Ēቺ����
    // ���l���傫���قǁA�����E��J���Ă��Ȃ�
    float m_muscleCurrent { 0.f };

    // ���̂̏C���x�i�ő�l�j
    // �����E��J�ɂ���Ēቺ����B
    float m_muscleMax { 0.f };

    // �����i���ݒl�j
    float m_carboCurrent { 0.f };

    // �����i�ő�l�j
    float m_carboMax { 0.f };

    // �^���p�N���i���ݒl�j
    float m_proteinCurrent { 0.f };

    // �^���p�N���i�ő�l�j
    float m_proteinMax { 0.f };

    // �����i���ݒl�j
    float m_lipidCurrent { 0.f };

    // �����i�ő�l�j
    float m_lipidMax { 0.f };

    // �r�^�~���i���ݒl�j
    float m_vitaminCurrent { 0.f };

    // �r�^�~���i�ő�l�j
    float m_vitaminMax { 0.f };

    // �~�l�����i���ݒl�j
    float m_mineralCurrent { 0.f };

    // �~�l�����i�ő�l�j
    float m_mineralMax { 0.f };

    // �����i���ݒl�j
    float m_waterCurrent { 0.f };

    // �����i�ő�l�j
    float m_waterMax { 0.f };

    // �r����
    bool m_fractureArm { false };

    // ������
    bool m_fractureLeg { false };

    // ����
    bool m_headache { false };

    // ����
    bool m_cold { false };

    // ����
    bool m_stomachache { false };

    // ����
    bool m_sleep { false };

    // �E���Ǐ�
    bool m_dehydration { false };

    // �����s��
    bool m_lackOfSleep { false };

    // ���S
    bool m_dead = false;

    // �����x
    float m_satiety = 0.f;

    float m_x = 0.f;
    float m_y = 0.f;
    float m_z = 0.f;

};

enum class eDeadReason
{
    NONE,

    // ���̂̏C���x��0�ɂȂ����B�S�g�Ŗo�I��
    MUSCLE_ZERO,

    // �̓��̐�����90���ȉ��ɂȂ���
    WATER_90,

    // �����Ǝ������[���ɂȂ����B�쎀
    STARVATION,

    // �̂̃X�^�~�i���[���ɂȂ����B
    KAROSHI,

    // ���C�l���̌_���1�N�o�߂����B
    RYNEN_1_YEAR,
};

class StatusManager
{
public:

    enum class PlayerState
    {
        // ������Ԃƕ�����Ԃ͓������炢����ׂ�
        // �������
        STAND,

        // �������
        WALK,

        // ������
        SIT,

        // �Q���ׂ�
        LYING_DOWN,

        // �W���M���O
        JOGGING,

        // �S�͎���
        SPRINTING,

        // �����ŐÎ~
        IDLE_WATER,

        // �j�����
        SWIM,
    };

    static StatusManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile,
              const bool decrypt = false);

    // 1�b�Ɉ�x�Ă΂��z��
    void Update();

    void Save(const std::string& csvfile,
              const float player_x,
              const float player_y,
              const float player_z,
              const bool encrypt = false);

    // ���s���x�B�d�ʂ⌒�N�x�A�ؗ͂Ȃǂ���Ƃ�����p�����[�^�[���e������
    float GetWalkSpeed();

    // �U���́B�d�ʂ⌒�N�x�A�ؗ͂Ȃǂ���Ƃ�����p�����[�^�[���e������
    float GetAttackPower();

    // �U�������Ƃ��ɃX�^�~�i�═��̑ϋv�x�Ȃǂ����炷
    void ConsumeAttackCost();

    // �h��́B�d�ʂ⌒�N�x�A�ؗ͂Ȃǂ���Ƃ�����p�����[�^�[���e������
    float GetDefensePower();

    // �H�ނ�H�ׂ�
    bool Eat(const ItemDef& food);

    // �Q��
    bool Sleep();

    // 3���ԋx�e
    bool Rest3Hours();

    // ��b����
    // ��b������]�̗̑͂�����B
    void Talk();

    // ���@���g��
    // ���@���g������]�̗̑͂�����
    void UseMagic();

    void DrinkWordBress(const float playerX,
                        const float playerY,
                        const float playerZ);

    // �؂̔���
    void CutTree(const std::string& weapon, const int level);

    // �A���̎�
    void PickPlant();

    // �I�[���𑆂�
    void PullOar();

    // ���E�̃I�[���𑆂�
    void PullOarBoth();

    // 3���ԁA�����q�C���s��
    void Voyage3Hours();

    //-------------------------------------------------------
    // Status�N���X�̓����̊֐����Ă�
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

    // ��������
    ItemInfo GetEquipWeapon() const;
    void SetEquipWeapon(const ItemInfo& arg);

    // �܂𑕔��B�߂�l�Ƃ��Ăǂ̌��ɑ������ꂽ�����Ԃ����B
    eBagPos EquipBag(const ItemInfo& bag);

    // �܂��O���B
    void UnequipBag(const eBagPos bagPos);
    void UnequipBag(const int id, const int subId);

    // �܂��擾
    ItemInfo GetBag(const eBagPos bagPos) const;
    eBagPos GetBag(const int id, const int subId) const;
    std::vector<ItemInfo> GetAllBag();

    // �܂̑�����
    std::vector<eBagPos> GetBagState();

    void UpdateBagDurability();

    // �������_�X�g���X
    void SetSuperStress();

    void GetXYZ(float* x, float* y, float* z);

    void SetMagicType(const eMagicType magicType);
    eMagicType GetMagicType() const;

    bool GetLevelUpFire();
    bool GetLevelUpIce();
    bool GetLevelUpDark();

    bool GetLevelDownFire();
    bool GetLevelDownIce();
    bool GetLevelDownDark();

    int GetLevelFire() const;
    int GetLevelIce() const;
    int GetLevelDark() const;

    void SetDeadReason(const eDeadReason reason);
    eDeadReason GetDeadReason() const;

private:

    eDeadReason m_eDeadReason = eDeadReason::NONE;

    // �V���O���g���I�u�W�F�N�g
    static StatusManager* obj;

    Status m_status;

    PlayerState m_playerState { PlayerState::STAND };

    // �̂̃X�^�~�i��70���ȉ��ɂȂ������Ƃ������1�x�ł�������
    bool m_training = false;

    // �O��������`�F�b�N�������̓�
    int m_previousDay = 0;

    // �O��������`�F�b�N�������̎���
    int m_previousHour = 0;

    // ��8�����܂�����
    bool m_over8clock = false;

    // ��������
    ItemInfo m_EquipWeapon;

    // ��
    std::unordered_map<eBagPos, ItemInfo> m_BagMap;

    // ���ׂ̊����ɂ�����b��
    // �����l��5���B�g�̂𓮂����ƈ�������
    int m_remainColdCure = 0;

    // �r���܂̊����ɂ�����b��
    // �����l��90���B�ܑ�h�{�f�������ȉ��̎��͉񕜂��~�܂�
    int m_remainArmFracCure = 0;

    // �����܂̊����ɂ�����b��
    // �����l��90���B�ܑ�h�{�f�������ȉ��̎��͉񕜂��~�܂�
    int m_remainLegFracCure = 0;

    // ���ɂ̊����ɂ�����b��
    // 1���i��24���ԁj�B�������ނƈ�������
    int m_remainHeadacheCure = 0;

    // ���ɂ̊����ɂ�����b��
    // 1���i��24���ԁj�B�H�ׂ�ƈ�������
    int m_remainStomachacheCure = 0;

    // �E���Ǐ�̊����ɂ�����b��
    // 1���i��24���ԁj�B�ܑ�h�{�f�E�����s������Ɖ񕜂��~�܂�
    int m_remainDehydration = 0;

    // �������̖��@
    eMagicType m_eMagicType = eMagicType::None;

    // ���@�̏n���x
    // �E0~10�܂ł�11�i�K
    // �E100��g�����疂�@�̃��x�����オ��B
    // �E���@�̃��x����100��g��������ł͂Ȃ�100��g������ɐQ��ƃ��x���A�b�v����
    // �E�o���l�͖���-10�����B�܂�A10�����@���g��Ȃ������烌�x����������Ƃ������ƁB
    int m_levelFire = 0;
    int m_levelIce = 0;
    int m_levelDark = 0;
    int m_experienceFire = 0;
    int m_experienceIce = 0;
    int m_experienceDark = 0;

    bool m_levelUpFire = false;
    bool m_levelUpIce = false;
    bool m_levelUpDark = false;

    bool m_levelDownFire = false;
    bool m_levelDownIce = false;
    bool m_levelDownDark = false;
};
}

