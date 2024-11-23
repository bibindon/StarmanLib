#pragma once
#include <string>
#include <unordered_map>

// �����A�^���p�N���A�����A�r�^�~���A�~�l������������ԂɎ���
// �v���C���[�ܑ͌�h�{�f�����ׂ�0�ɂȂ�Ȃ��悤�ɂ���K�v������B
// ������0�ɂȂ�����쎀�A����ȊO��0�ɂȂ�����a������B
// �q�ɂɃ��[�h�u���X������΃��C�l���̌_�������������B

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
};

class NpcStatusManager
{
public:

    static NpcStatusManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);
    void Save(const std::string& csvfile);

    NpcStatus GetNpcStatus(const std::string& name);
    void SetNpcStatus(const std::string& key, const NpcStatus& value);

private:

    // �V���O���g���I�u�W�F�N�g
    static NpcStatusManager* obj;

    std::unordered_map<std::string, NpcStatus> m_NpcStatusMap;

};

