#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{
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

// �}�C���N���t�g�Ŗ؂̕��������Ƃ��ł���悤�ɓ�������𕡐������Ƃ��ł���B
// Weapon�N���X�͓�������𕡐������߂ɒ�`���ꂽ�N���X�B
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

    std::string m_id; // ����ID
    int m_idSub = 0; // ����ID�T�u�B��������𕡐����Ă�悤�ɂ��邽�߂̎��ʎq
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
              const std::string& subSavefilename,
              const bool decrypt = false);

    std::unordered_map<std::string, WeaponType> GetWeaponTypeMap();
    void SetWeaponTypeMap(const std::unordered_map<std::string, WeaponType>& arg);

    std::unordered_map<std::string, std::vector<Weapon>> GetWeaponMap();
    void SetWeaponMap(const std::unordered_map<std::string, std::vector<Weapon>>& arg);

    void Save(const std::string& savefilename,
              const std::string& subSavefilename,
              const bool encrypt = false);

    // TODO �����l���X�V���A�U���́A�򋗗��A�ϋv�x���X�V����
    void SetReinforce(const std::string& name, const int subId, const int reinforce);

private:

    // �V���O���g���I�u�W�F�N�g
    static WeaponManager* obj;

    // ���̃Q�[���ɂ̓C���x���g���Ƒq�ɂ�����B
    // �ȉ��̕��킪�ǂ���ɂ��邩�́A�C���x���g���N���X�A�q�ɃN���X�ɖ₢���킹��΂悭
    // ���̕���Ǘ��N���X�͊֗^���Ȃ��B
    std::unordered_map<std::string, WeaponType> m_weaponTypeMap;
    std::unordered_map<std::string, std::vector<Weapon>> m_weaponMap;
};
}
