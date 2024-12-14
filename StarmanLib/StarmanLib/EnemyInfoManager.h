#pragma once

#include <string>
#include <unordered_map>

namespace NSStarmanLib
{

// �G�̒�`���
// �G���ނɂ��A1�C���X�^���X
class EnemyDef
{
public:

    void SetIDDef(const int arg);
    int GetIDDef();

    void SetName(const std::string& arg);
    std::string GetName();

    void SetDetail(const std::string& arg);
    std::string GetDetail();

    void SetImagePath(const std::string& arg);
    std::string GetImagePath();

    void SetVisible(const bool arg);
    bool GetVisible();

private:

    // �G���ނ��ƂɊ���U����ID
    int m_idDef = 0;

    // ������
    std::string m_name;

    // ������
    std::string m_detail;

    // �t�@�C���p�X
    std::string m_imagePath;

    // ���j���[�ł̕\���E��\��
    bool m_visible;
};

// �G�Ǘ��N���X�B
// �G1�̂ɂ��A1�C���X�^���X
// CSV�t�@�C���ɋL�ڂ��ꂽ�G�̍��W��HP�Ȃǂ�񋟂���݂̂ł���B
// �G�̍s���p�^�[�����Ƃ��Փ˔���A�W�����v�̋O���ȂǏڍׂȂ��Ƃ͂����ł͂��Ȃ��B
// �i���C�u�����̎g�p�҂��Q�[�����œƎ��̎������s���ׂ��j
class EnemyInfo
{
public:

    void SetID(const int arg);
    int GetID();

    void SetIDDef(const int arg);
    int GetIDDef();

    void SetBreed(const std::string& breed);
    std::string GetBreed();

    void SetX(const float arg);
    float GetX();

    void SetY(const float arg);
    float GetY();

    void SetZ(const float arg);
    float GetZ();

    void SetRotX(const float arg);
    float GetRotX();

    void SetRotY(const float arg);
    float GetRotY();

    void SetRotZ(const float arg);
    float GetRotZ();

    void SetHP(const int arg);
    int GetHP();

    void SetDefeated(const bool arg);
    bool GetDefeated();

private:

    // �G��̂��ƂɊ���U����ID
    int m_id = 0;

    // �G���ނ��ƂɊ���U����ID
    int m_idDef = 0;

    // �����X�^�[�̎푰
    std::string m_breed;

    float m_x { 0.f };
    float m_y { 0.f };
    float m_z { 0.f };

    float m_rotX { 0.f };
    float m_rotY { 0.f };
    float m_rotZ { 0.f };

    // �c��HP
    int m_HP { 0 };
    bool m_bDefeated { false };

};

class EnemyInfoManager
{
public:

    static EnemyInfoManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvEnemyDef,
              const std::string& csvEnemyInfo,
              const std::string& csvEnemyVisible);

    void Save(const std::string& csvEnemyInfo,
              const std::string& csvEnemyVisible);

    // �����Ŏ������W�Ɣ��a�̓����ɂ���G���擾
    std::vector<EnemyInfo> GetEnemyInfo(const float x, const float y, const float z, const float r);

    void UpdateEnemyInfo(const int id, const EnemyInfo& enemyInfo);

    std::vector<std::string> GetEnemyNameList();

    EnemyDef GetEnemyDef(const std::string name);
    void SetEnemyVisible(const std::string name, const bool visible);

private:

    // �V���O���g���I�u�W�F�N�g
    static EnemyInfoManager* obj;

    std::unordered_map<int, EnemyDef> m_enemyDefMap;
    std::unordered_map<int, EnemyInfo> m_enemyInfoMap;

};
}

