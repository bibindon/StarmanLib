#pragma once
#include <vector>
#include <string>

// �C�J�_
class Raft
{
public:

    enum class ePosType
    {
        Sea,
        River,
    };

    void SetId(const int arg);
    int GetId() const;

    void SetSail(const bool arg);
    bool GetSail() const;

    void SetXYZ(const float x, const float y, const float z);
    void GetXYZ(float* x, float* y, float* z);

    void SetDurability(const int arg);
    int GetDurability() const;

    void SetLevel(const int arg);
    int GetLevel() const;

    void SetPosType(const ePosType arg);
    ePosType GetPosType() const;

    void SetStorehouseId(const int arg);
    int GetStorehouseId() const;

    float GetStorehouseWeight() const;

private:

    int m_id = -1;

    // �����W�J����Ă��邩�A��܂�Ă��邩�B
    bool m_bSail = false;

    float m_x = 0.f;
    float m_y = 0.f;
    float m_z = 0.f;

    // �ϋv�x
    // �C�J�_�͑q�ɂɂ��C���x���g���ɂ�����Ȃ��̂�
    // Inventory�N���X��Storehouse�N���X�̂��Ƃ��l����K�v�͂Ȃ��B
    int m_durability = 0;

    // �����l
    int m_level = 0;

    // �삩�C��
    ePosType m_ePosType = ePosType::River;

    // �q�ɂ�ID
    int m_storehouseId = -1;
};

// �q�C�@�\
class Voyage
{
public:

    static Voyage* Get();

    void Init(const std::string& csvFile);
    void Save(const std::string& csvFile);

    // ���t���[���Ă΂��z��
    void Update();

    void SetRaftMode(const bool arg);
    bool GetRaftMode() const;

    void AddRaft(const Raft& arg);
    std::vector<Raft> GetRaftList();

    // ��D���̃C�J�_
    // �Ȃ��Ƃ���ID��-1
    Raft GetRaftCurrent();

    // �E�̃I�[��������
    // �Փ˔���̓��C�u�������ł͂ł��Ȃ��̂�
    // �C�J�_��i�߂鏈�������C�u�������ōs�����Ƃ͂ł��Ȃ��B
    void PullRightOar();

    // ���̃I�[��������
    // �Փ˔���̓��C�u�������ł͂ł��Ȃ��̂�
    // �C�J�_��i�߂鏈�������C�u�������ōs�����Ƃ͂ł��Ȃ��B
    void PullLeftOar();

    // �����̃I�[��������
    // �Փ˔���̓��C�u�������ł͂ł��Ȃ��̂�
    // �C�J�_��i�߂鏈�������C�u�������ōs�����Ƃ͂ł��Ȃ��B
    void PullBothOar();

    // �Փ˔���̓��C�u�������ł͂ł��Ȃ��̂�
    // �C�J�_��i�߂鏈�������C�u�������ōs�����Ƃ͂ł��Ȃ��B
    void SetCurrentRaftCoord(const float x, const float y, const float z);
    void GetCurrentRaftCoord(float* x, float* y, float* z);

    // ���݂̕����Ɍ�������3���ԑ���
    void Set3HoursAuto();

    // ���ݏ���Ă���C�J�_�̔��̏�Ԃ��擾
    void SetSailCurrentRaft(const bool arg);
    bool GetSailCurrentRaft() const;

    // ���ݏ���Ă���C�J�_������̂͐삩�C��
    void SetPosTypeCurrentRaft(const Raft::ePosType arg);
    Raft::ePosType GetPosTypeCurrentRaft() const;

    void GetTideXZ(float* x, float* z);

    void GetWindXZ(float* x, float* z);

private:

    // GetRaftCurrent�ƈႢ�A������̓|�C���^���g���B
    // ���������p
    Raft* GetRaftCurrentPriv() const;

    static Voyage* m_single;

    bool m_bRaftMode = false;

    int m_currentRaftId = -1;

    std::vector<Raft> m_raftList;

    // ���̌����Ƌ���
    // 1���Ԃ����ɕς��
    // �������s���͕ς��Ȃ�
    float m_windX = 0.f;
    float m_windZ = 0.f;

    // ���̌����Ƌ���
    // 1���Ԃ����ɕς��
    // �������s���͕ς��Ȃ�
    float m_tideX = 0.f;
    float m_tideZ = 0.f;
};
