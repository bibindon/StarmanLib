#pragma once

#include <string>
#include "ItemManager.h"

// ��ʓI�ɁA�u�U�����󂯂��Ƃ��A�ŏI�I�ɕ����_���[�W�������ɂȂ邩�v��
// ����Ȃ�ɕ��G�ȃR�[�h�ɂȂ�B
// �Q�[���{�̂ɂ��̕��G�����������܂Ȃ��Ă悢�悤�ɂ������B

namespace NSStarmanLib
{
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
    };

    static StatusManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);

    // 1�b�Ɉ�x�Ă΂��z��
    void Update();

    void Save(const std::string& csvfile);

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

    // ��b����
    // ��b������]�̗̑͂�����B
    void Talk();

    // ���@���g��
    // ���@���g������]�̗̑͂�����
    void UseMagic();

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

    // �������_�X�g���X
    void SetSuperStress();

private:

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

    // ���ׂ̊����ɂ��������
    // �����l��5���B�g�̂𓮂����ƈ�������
    int m_remainColdCure = 0;

    // �r���܂̊����ɂ��������
    // �����l��90���B�ܑ�h�{�f�������ȉ��̎��͉񕜂��~�܂�
    int m_remainArmFracCure = 0;

    // �����܂̊����ɂ��������
    // �����l��90���B�ܑ�h�{�f�������ȉ��̎��͉񕜂��~�܂�
    int m_remainLegFracCure = 0;

    // ���ɂ̊����ɂ��������
    // 1���i��24���ԁj�B�������ނƈ�������
    int m_remainHeadacheCure = 0;

    // ���ɂ̊����ɂ��������
    // 1���i��24���ԁj�B�H�ׂ�ƈ�������
    int m_remainStomachacheCure = 0;

    // �E���Ǐ�̊����ɂ��������
    // 1���i��24���ԁj�B�ܑ�h�{�f�E�����s������Ɖ񕜂��~�܂�
    int m_remainDehydration = 0;
};
}

