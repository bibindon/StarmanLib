#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{
class WeaponDef
{

public:

    // �����ł�ID��weapon.csv�ł�ID
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
    double m_weight = 0.f; // �d��
    int m_volume = 0; // �̐�
    double m_attackRate = 0.f; // �U���͕␳
    double m_attackRateUp = 0.f; // �������̍U���͕␳�̏㏸�l
    int m_reinforceMax = 0; // �����\��
    double m_flightDistance = 0.f; // �򋗗�
    double m_flightDistanceUp = 0.f; // �������̔򋗗��̏㏸�l
    double m_staminaDown = 0.f; // ����X�^�~�i
    int m_durability = 0; // �ϋv�l�i����܂ł̉񐔁j
    int m_durabilityUp = 0; // �������̑ϋv�l�̏㏸�l
    int m_ownDamage = 0; // �g�p���̓��̑���

    bool m_isShow = false; // �\��
};

// ItemManger��Inentory, Storehouse����͎擾�ł��Ȃ���񂪂���B
// �U���͂�򋗗��A�ő�ϋv�x�Ȃ�
// �ϋv�x��Inventory��Storehouse���Ǘ����Ă���̂ň���Ȃ��B
// TODO ������ɑ΂��Ă��̃N���X�����K�v���Ȃ��C������
// +1�̐Ε���+2�̐Ε���5���������ꍇ�A10��Weapon������Ă��܂���
// 2�łŗǂ��C������B���g�S���ꏏ�����B
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

    std::string m_weaponId; // ����ID�iweapon.csv�j
    int m_itemId = 0; // �A�C�e��ID�iitem.csv�j

    int m_idSub = 0; // ����ID�T�u�B��������𕡐����Ă�悤�ɂ��邽�߂̎��ʎq
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

    // ����̍폜���ł��邱�Ƃ���SubId�͘A�ԂƂ͌���Ȃ����Ƃɒ���
    bool ExistWeapon(const std::string& weaponId, const int subId, const int level = -1) const;
    Weapon GetWeapon(const std::string& weaponId, const int subId, const int level = -1) const;
    void AddWeapon(const std::string& weaponId, const Weapon& arg);
    void UpdateWeapon(const std::string& weaponId, const Weapon& arg);
    void RemoveWeapon(const std::string& weaponId, const int subId, const int level = -1);

    // �����l���X�V���A�U���́A�򋗗��A�ϋv�x���X�V����
    void SetReinforceAndUpdateParam(const std::string& weaponId,
                                    const int subId,
                                    const int reinforce);

private:

    Weapon GetReinforcedWeapon(const Weapon& weapon,
                               const std::string& weaponId,
                               const int subId,
                               const int reinforce);

    // �V���O���g���I�u�W�F�N�g
    static WeaponManager* obj;

    // ���̃Q�[���ɂ̓C���x���g���Ƒq�ɂ�����B
    // �C���x���g���Ƒq�ɂ�SubID����邱�Ƃ͂Ȃ��B
    // �C���x���g���ɂ��镐����A�q�ɂɂ��镐�����ʂȂ�m_weaponMap�ɕۑ�����B
    std::unordered_map<std::string, WeaponDef> m_weaponDefMap;
    std::unordered_map<std::string, std::list<Weapon>> m_weaponMap;
};
}
