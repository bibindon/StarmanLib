#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{

// weapon.csv�̓��e���̂܂�
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

// WeaponDef�̒�`�ł́u�����l�{�R�̐Ε��̍U���́v��m�肽���Ƃ�
// �v�Z���Ȃ��ƕ�����Ȃ��B
// 
// WeaponDefSub�ł͋����l���Ƃ̍U���͂�򋗗��Ȃǂ����炩���ߌv�Z���ĕێ����Ă����B
// 
// �ő�ϋv�x�͊Ǘ����邪���݂̑ϋv�x��Inventory��Storehouse���Ǘ����Ă���̂ň���Ȃ��B
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

    std::string m_weaponId; // ����ID�iweapon.csv�j
    int m_itemId = 0; // �A�C�e��ID�iitem.csv�j

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


    // �V���O���g���I�u�W�F�N�g
    static WeaponManager* obj;

    std::unordered_map<std::string, WeaponDef> m_weaponDefMap;
    std::vector<WeaponDefSub> m_weaponDefSubList;
};
}
