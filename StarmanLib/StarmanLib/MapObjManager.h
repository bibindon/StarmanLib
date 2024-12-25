#pragma once

#include <string>
#include <vector>
#include <unordered_map>

// ���悻100���[�g���ȓ���3D���f���̏���Ԃ��B
// 1�b�Ɉ�񂭂炢�Ă΂��z��
namespace NSStarmanLib
{


class MapObj
{
public:

    void SetId(const int id);
    int GetId() const;

    void SetFrameX(const int x);
    int GetFrameX() const;

    void SetFrameZ(const int z);
    int GetFrameZ() const;

    void SetModelId(const int arg);
    int GetModelId() const;

    void SetX(const float arg);
    float GetX() const;

    void SetY(const float arg);
    float GetY() const;

    void SetZ(const float arg);
    float GetZ() const;

    void SetRotY(const float arg);
    float GetRotY() const;

    void SetScale(const float arg);
    float GetScale() const;

    // 100���[�g���ȏ㗣�ꂽ���\���ɂ��邪�A����Ƃ͕ʂɁA�؂�؂�����A�؂����؂��\���ɂ������B
    // Show/Hide, Visible/Disable�Ō��t���g�������邱�Ƃɂ���
    void SetShow(const bool arg);
    bool GetShow() const;

    void SetVisible(const bool arg);
    bool GetVisible() const;
private:

    int m_id = 0;

    int m_frameX = 0;
    int m_frameZ = 0;

    int m_modelId;

    float m_x = 0.f;
    float m_y = 0.f;
    float m_z = 0.f;

    float m_yRot = 0.f;

    float m_scale = 0.f;

    bool m_show = false;
    bool m_visible = false;
};

// MapObj����ʂɕK�v�ƂȂ邽�ߍ\���̂��g�����������v��
struct stMapObj
{
    int m_id = 0;

    int m_frameX = 0;
    int m_frameZ = 0;

    int m_modelId;

    float m_x = 0.f;
    float m_y = 0.f;
    float m_z = 0.f;

    float m_yRot = 0.f;

    float m_scale = 0.f;

    bool m_show = false;
    bool m_visible = false;
};

// �S�����ׂ����ϕ��ׂ��d���Ȃ�̂�100���[�g�����Ƃ̊i�q���l����B
// �}�b�v��100���[�g�����Ƃ̊i�q�ŕ������A����������i�q�Ƃ��̎����8�̊i�q��������������
//
// 100���[�g���ȏ㗣�ꂽ���\���ɂ��邪�A����Ƃ͕ʂɁA�؂�؂�����A�؂����؂��\���ɂ������B
// Show/Hide, Visible/Disable�Ō��t���g�������邱�Ƃɂ���
class MapObjManager
{
public:

    static MapObjManager* GetObj();

    void Init(const std::string& csvfile,
              const std::string& csvModelId,
              const bool decrypt = false);

    // �o�C�i���t�@�C���œǂݏ�������
    void InitWithBinary(const std::string& binfile,
                        const std::string& csvModelId,
                        const bool decrypt = false);

    void Save(const std::string& csvfile,
              const bool encrypt = false);

    static void Destroy();

    // �\�����ׂ��I�u�W�F�N�g��Ԃ�
    std::vector<MapObj> GetMapObjList(const float playerX, const float playerZ);

    // ���ar�ȓ��̃I�u�W�F�N�g��Ԃ��B
    std::vector<MapObj> GetMapObjListR(const float playerX, const float playerZ, const float r);

    // �\�����ׂ��Ȃ̂ɕ\������Ă��Ȃ��I�u�W�F�N�g��Ԃ�
    void GetMapObjListShow(const float playerX,
                           const float playerZ,
                           std::vector<MapObj>* needShow);

    // �\�����ׂ��łȂ��̂ɕ\������Ă���I�u�W�F�N�g��Ԃ�
    void GetMapObjListHide(const float playerX,
                           const float playerZ,
                           std::vector<MapObj>* needHide);

    // 100���[�g���ȏ㗣�ꂽ���\���ɂ��邪�A����Ƃ͕ʂɁA�؂�؂�����A�؂����؂��\���ɂ������B
    // Show/Hide, Visible/Disable�Ō��t���g�������邱�Ƃɂ���
    void SetShow(const int frame_x, const int frame_z, const int id, const bool show);

    void SetVisible(const int frame_x, const int frame_z, const int id, const bool visible);

    std::string GetModelName(const int id);

private:

    static MapObjManager* obj;

    // m_mapObjMap[10][20] �����1000m ~ 1100m, 2000m ~ 2100m�͈̔͂�3�c���f���̃��X�g���Ӗ�����
    std::unordered_map<int, std::unordered_map<int, std::vector<MapObj>>> m_mapObjMap;

    std::unordered_map<int, std::unordered_map<int, std::vector<stMapObj>>> m_stMapObjMap;

    // ���f���̔z�u���͋���Ȃ��߃t�@�C���������̂܂܈����ƂƂĂ��Ȃ�����ɂȂ��Ă��܂��B
    // tree.x -> 1
    // rock.x -> 2
    // �̂悤�Ȏ��ʎq��^����悤�ɂ���
    std::unordered_map<int, std::string> m_XnameMap;

    bool m_bBinData = false;
};

}

