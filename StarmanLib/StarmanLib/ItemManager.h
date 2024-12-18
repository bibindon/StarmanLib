#pragma once

#include <string>
#include <unordered_map>
#include <map>

namespace NSStarmanLib
{

// �A�C�e���ɂ͑ϋv�x������A�����A�C�e���ł��ϋv�x���قȂ邱�Ƃ��\�B
// �Ⴆ�΁A�Ε����������Ă��邪�A�Е��͑ϋv�x��100�ŁA
// �����Е��͑ϋv�x��50�Ƃ����͉̂\�ł���B
// ������������邽�߂�ItemInfo��ItemDef�Ƃ����N���X�ɕ�����B
// ItemDef�̓A�C�e���̒�`�AItemInfo�͌X�̃A�C�e���̏�ԂƂ���
// ItemInfo��Inventory�N���X�i�C���x���g���j��Storehouse�N���X�i�q�Ɂj�Ŏg����B
// SubId�ŌX�̃A�C�e���̎��ʂ��s�����A�A�C�e���͍폜�ł���̂ŘA�ԂɂȂ�Ƃ͌���Ȃ�

class ItemInfo
{
public:

    void SetId(const int arg);
    int GetId() const;

    void SetSubId(const int arg);
    int GetSubId() const;

    void SetDurabilityCurrent(const int arg);
    int GetDurabilityCurrent() const;

private:

    int m_id = 0;

    int m_subId = 0;

    int m_durabilityCurrent = 0;
};

class ItemDef
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

        // ����
        WEAPON,

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

    int GetDurabilityMax() const;
    void SetDurabilityMax(int arg);

private:
    // ID
    int m_id = 0;

    // ����
    std::string m_name;

    // �ڍ�
    std::string m_detail;

    // �摜�̃t�@�C����
    std::string m_imagePath;

    // �d�ʁikg�j
    float m_weight = 0.f;

    // �̐ρimL�j
    float m_volume = 0.f;

    // ���
    ItemType m_eType;

    // ����
    float m_carbo = 0.f;

    // �^���p�N��
    float m_protein = 0.f;

    // ����
    float m_lipid = 0.f;

    // �r�^�~��
    float m_vitamin = 0.f;

    // �~�l����
    float m_mineral = 0.f;

    // ����
    // �}�C�i�X�ɂȂ邱�Ƃ�����B
    float m_water = 0.f;

    // �f�o�t�i�̂̃X�^�~�i�j
    float m_bodyStaminaDebuff = 0.f;

    // �f�o�t�i�]�̃X�^�~�i�j
    float m_brainStaminaDebuff = 0.f;

    // �f�o�t�i���̂̏C���x�j
    float m_muscleDebuff = 0.f;

    // �f�o�t�i���Ɂj
    bool m_headache = false;

    // �f�o�t�i���Ɂj
    bool m_stomachache = false;

    // �����l
    int m_level = -1;

    // �ϋv�x
    int m_durabilityMax = -1;
};

// ���[���h�}�b�v��̂ǂ��ɃA�C�e���������Ă��邩�̏��
class ItemPos
{
public:
    void SetItemPosId(const int id);
    int GetItemPosId() const;

    void SetItemDefId(const int id);
    int GetItemDefId() const;

    void SetPos(const float x, const float y, const float z);
    void GetPos(float* x, float* y, float* z);

    void SetObtained(const bool arg);
    bool GetObtained();

private:

    int m_itemPosId = 0;
    int m_itemDefId = 0;
    float m_x = 0.f;
    float m_y = 0.f;
    float m_z = 0.f;
    bool m_obtained = false;
};

// �A�C�e�������Ǘ�����N���X
// �u��l���̓A�C�e�������������Ă��邩�H�v��
// Inventory�N���X���S�����邽�߂��̃N���X�͊֌W�Ȃ����Ƃɒ��ӁB
class ItemManager
{
public:

    static ItemManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile, const std::string& csvfilePos,
              const bool decrypt = false);
    bool Inited();
    void Save(const std::string& csvfilePos,
              const bool encrypt = false);

    std::vector<int> GetItemIdList();
    ItemDef GetItemDef(const std::string& key, const int level = -1);
    ItemDef GetItemDef(const int id);
    std::vector<int> GetItemDef(const ItemDef::ItemType type);
    
    ItemDef GetItemDefByPosID(const int posId);

    // 1���[�g���ȓ��ɂ���A�C�e����������Ԃ�
    ItemPos GetItemPosByPos(const float x, const float y, const float z, const float r = 1.f);
    void SetItemPosObtained(const int itemPosId);

private:

    // �V���O���g���I�u�W�F�N�g
    static ItemManager* obj;

    std::unordered_map<int, ItemDef> m_itemDefMap;

    bool m_inited = false;

    std::map<int, ItemPos> m_itemPosMap;
};
}

