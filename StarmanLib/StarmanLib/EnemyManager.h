#pragma once

#include <string>
#include <unordered_map>

// �G�Ǘ��N���X�B
// CSV�t�@�C���ɋL�ڂ��ꂽ�G�̍��W��HP�Ȃǂ�񋟂���݂̂ł���B
// �G�̍s���p�^�[�����Ƃ��Փ˔���A�W�����v�̋O���ȂǏڍׂȂ��Ƃ͂����ł͂��Ȃ��B
// �i���C�u�����̎g�p�҂��Q�[�����œƎ��̎������s���ׂ��j

class EnemyInfo
{
public:

    void SetID(const int arg);
    int GetID();

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

    int m_id { 0 };

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

class EnemyManager
{
public:

    static EnemyManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);

    void Save(const std::string& csvfile);

    // �����Ŏ������W�Ɣ��a�̓����ɂ���G���擾
    std::vector<EnemyInfo> GetEnemyInfo(const float x, const float y, const float z, const float r);

    void UpdateEnemyInfo(const int id, const EnemyInfo& enemyInfo);

private:

    // �V���O���g���I�u�W�F�N�g
    static EnemyManager* obj;

    std::unordered_map<int, EnemyInfo> m_enemyInfoMap;

};

