#pragma once

#include <string>
#include <unordered_map>

namespace NSStarmanLib
{
class ItemInfo
{
public:
    enum class ItemType
    {
        // �M�d�i
        VALUABLES,

        // �H��
        FOOD,

        // �f��
        MATERIAL,

        // ���̑�
        OTHERS,
    };

    int GetId() const;
    void SetId(int arg);

    std::string GetName() const;
    void SetName(std::string arg);

    std::string GetDetail() const;
    void SetDetail(std::string arg);

    std::string GetImagePath() const;
    void SetImagePath(std::string arg);

    float GetWeight() const;
    void SetWeight(float arg);

    float GetVolume() const;
    void SetVolume(float arg);

    ItemType GetType() const;
    void SetType(ItemType arg);

    float GetCarbo() const;
    void SetCarbo(float arg);

    float GetProtein() const;
    void SetProtein(float arg);

    float GetLipid() const;
    void SetLipid(float arg);

    float GetVitamin() const;
    void SetVitamin(float arg);

    float GetMineral() const;
    void SetMineral(float arg);

    float GetWater() const;
    void SetWater(float arg);

    float GetBodyStaminaDebuff() const;
    void SetBodyStaminaDebuff(float arg);

    float GetBrainStaminaDebuff() const;
    void SetBrainStaminaDebuff(float arg);

    float GetMuscleDebuff() const;
    void SetMuscleDebuff(float arg);

    bool GetHeadache() const;
    void SetHeadache(bool arg);

    bool GetStomachache() const;
    void SetStomachache(bool arg);

    int GetLevel() const;
    void SetLevel(int arg);

private:
    // ID
    int m_id;

    // ����
    std::string m_name;

    // �ڍ�
    std::string m_detail;

    // �摜�̃t�@�C����
    std::string m_imagePath;

    // �d�ʁikg�j
    float m_weight;

    // �̐ρimL�j
    float m_volume;

    // ���
    ItemType m_eType;

    // ����
    float m_carbo;

    // �^���p�N��
    float m_protein;

    // ����
    float m_lipid;

    // �r�^�~��
    float m_vitamin;

    // �~�l����
    float m_mineral;

    // ����
    // �}�C�i�X�ɂȂ邱�Ƃ�����B
    float m_water;

    // �f�o�t�i�̂̃X�^�~�i�j
    float m_bodyStaminaDebuff;

    // �f�o�t�i�]�̃X�^�~�i�j
    float m_brainStaminaDebuff;

    // �f�o�t�i���̂̏C���x�j
    float m_muscleDebuff;

    // �f�o�t�i���Ɂj
    bool m_headache;

    // �f�o�t�i���Ɂj
    bool m_stomachache;

    // �����l
    int m_level = -1;
};

// �A�C�e�������Ǘ�����N���X
// �u��l���̓A�C�e�������������Ă��邩�H�v��
// Inventory�N���X���S�����邽�߂��̃N���X�͊֌W�Ȃ����Ƃɒ��ӁB
// TODO ����ƃA�C�e���͈Ⴄ�̂��H
class ItemManager
{
public:

    static ItemManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);

    ItemInfo GetItemInfo(const std::string& key, const int level = -1);
    ItemInfo GetItemInfo(const int id);

private:

    // �V���O���g���I�u�W�F�N�g
    static ItemManager* obj;

    std::unordered_map<int, ItemInfo> m_itemInfoMap;
};
}

