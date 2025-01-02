#pragma once
#include <string>
#include <unordered_map>

namespace NSStarmanLib
{
// �����A�^���p�N���A�����A�r�^�~���A�~�l������������ԂɎ���
// �v���C���[�ܑ͌�h�{�f�����ׂ�0�ɂȂ�Ȃ��悤�ɂ���K�v������B
// ������0�ɂȂ�����쎀�A����ȊO��0�ɂȂ�����a������B
// �q�ɂɃ��[�h�u���X������΃��C�l���̌_�������������B

enum class eNpcFeature
{
    STOREHOUSE,
    CRAFTMAN,
    NONE,
};

class NpcStatus
{
public:

    void SetName(const std::string& arg);
    std::string GetName();

    void SetCarbo(const float arg);
    float GetCarbo();

    void SetProtein(const float arg);
    float GetProtein();

    void SetLipid(const float arg);
    float GetLipid();

    void SetVitamin(const float arg);
    float GetVitamin();

    void SetMineral(const float arg);
    float GetMineral();

    void SetRynenContract();
    float GetRynenContract();

    void SetDrinkWordbress(const bool arg);
    bool GetDrinkWordbress();

    void SetDead();
    bool GetDead();

    void SetX(const float arg);
    float GetX() const;

    void SetY(const float arg);
    float GetY() const;

    void SetZ(const float arg);
    float GetZ() const;

    void SetRotY(const float arg);
    float GetRotY() const;

    void SetHasTalk(const bool arg);
    bool GetHasTalk() const;

    void SetTalkCsv(const std::string& arg);
    std::string GetTalkCsv() const;

    void SetFeatureEnable(const bool arg);
    bool GetFeatureEnable() const;

    void SetNpcFeature(const eNpcFeature arg);
    eNpcFeature GetNpcFeature() const;

    void SetMenuShow(const bool arg);
    bool GetMenuShow() const;

private:

    // ���O
    std::string m_name;

    // ����
    float m_carbo { 0.f };

    // �^���p�N��
    float m_protein { 0.f };

    // ����
    float m_lipid { 0.f };

    // �r�^�~��
    float m_vitamin { 0.f };

    // �~�l����
    float m_mineral { 0.f };

    // ���C�l���̌_������Ă��邩�ۂ�
    bool m_rynenContract { false };

    // ���[�h�u���X������ł��邩�ۂ�
    bool m_bDrinkWordbress { false };

    // ����ł��邩�ۂ�
    bool m_dead { false };

    float m_x = 0.f;

    float m_y = 0.f;

    float m_z = 0.f;

    float m_rotY = 0.f;

    // ��b���ׂ����������邩�H
    // �ENPC�̉�b�͉ו��Ԃ�b�艮�̋@�\��\������O�ɕ\������
    bool m_bHasTalk = false;

    // ��b���ׂ�����
    // m_talkCsv�̓��e���g���ė��p�҂ɉ�b���Ă��炤�B
    std::string m_talkCsv;

    // �ו��Ԃ�b�艮�̋@�\�����ւ���Ă��邩�B
    bool m_bFeatureEnable = false;

    eNpcFeature m_eNpcFeature = eNpcFeature::NONE;

    // NPC�����j���[��ʂŕ\�����邩
    bool m_bMenuShow = false;
};



class NpcStatusManager
{
public:

    static NpcStatusManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile,
              const bool decrypt = false);
    void Save(const std::string& csvfile,
              const bool encrypt = false);

    NpcStatus GetNpcStatus(const std::string& name);
    void SetNpcStatus(const std::string& key, const NpcStatus& value);

    std::vector<std::string> GetNameList();

private:

    // �V���O���g���I�u�W�F�N�g
    static NpcStatusManager* obj;

    std::unordered_map<std::string, NpcStatus> m_NpcStatusMap;

};
}

