#pragma once

#include "HeaderOnlyCsv.hpp"
#include "ItemManager.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{
// �v���C���[�̏����i���Ǘ�����N���X�B
// �A�C�e���̒�`��ItemManager���Ǘ����Ă���B
// ����ɂ��Ă�WeaponManager���������܂ŊǗ����Ă���̂�
// Storehouse�N���X�ɏo�Ԃ͂Ȃ��\��

class Storehouse
{
public:

    void Init(const std::string& csvfile,
              const bool decrypt = false);

    void Save(const std::string& csvfile,
              const bool encrypt = false);

    // ��������������o���Ȃ��z��
    void AddItem(const int id, const int durability = -1);
    void AddItem(const std::string name, const int level = -1, const int durability = -1);

    // SubID���w�肵�ăA�C�e����ǉ��i�C���x���g������q�ɂփA�C�e�����ړ�����Ƃ��Ɏg���j
    // �C���x���g���ŃA�C�e�����폜���Ă���ǉ�����K�v������B
    // �C���x���g���ŃA�C�e�����폜���Ă��Ȃ���
    // �u���łɂ���SubID�͎g���Ă���v�Ƃ������ƂŃG���[�ɂȂ�
    void AddItemWithSubID(const int id, const int subId, const int durability = -1);

    // subId�E�E�E�ϋv�l��50�̐Ε��Ƒϋv�l��100�̐Ε����������邱�Ƃ��ł���
    // ���̂��߁A�A�C�e���ɂ�subId���U����B�A�C�e�����폜����ɂ�subId���Ȃ��Ƃł��Ȃ�
    // �A�C�e���͍폜�ł���̂�SubID���A�ԂɂȂ�Ƃ͌���Ȃ�
    void RemoveItem(const int id, const int subId);
    void RemoveItem(const std::string name, const int subId, const int level = -1);

    void SetItemDurability(const int id, const int subId, const int durability);

    bool ExistItem(const int id, const int subId);
    ItemInfo GetItemInfo(const int id, const int subId);

    std::vector<int> GetSubIdList(const int id);

    int CountItem(const int id);
    int CountItem(const std::string name, const int level = -1);

    float GetWeight();

    std::list<ItemInfo> GetAllItem();

    void SetXYZ(const float x, const float y, const float z);
    void GetXYZ(float* x, float* y, float* z);

    void SetIsRaft(const bool arg);
    bool GetIsRaft() const;

    void SetCsvFileName(const std::string arg);
    std::string GetCsvFileName() const;

private:

    float CalcWeight();

    void Sort();

    // �����i�̏d�ʁi����͊܂߂Ȃ��j
    float m_weight;

    // �����i���X�g
    // �����A�C�e���𕡐������ł��邱�Ƃɒ���
    std::list<ItemInfo> m_itemInfoList;

    float m_x = 0.f;
    float m_y = 0.f;
    float m_z = 0.f;

    // �C�J�_�̏�ɔz�u���ꂽ�q�ɂ��ۂ��B
    bool m_bRaft = false;

    // �f�B���N�g�����������A�t�@�C�����B
    std::string m_csvfilename;
};

// �q�ɊǗ��N���X
// �q�ɂ͕��������Ƃ��ł���
// �C�J�_�����Ƒq�ɂ͑�����
class StorehouseManager
{
public:

    static StorehouseManager* Get();
    static void Destroy();

    void Init(const std::string& csvfile);
    bool Inited();

    void Save(const std::string& managerFile,
              const std::string& csvDir);

    std::vector<int> GetStorehouseIdList();

    Storehouse* GetStorehouse(const int id);

    // 3���[�g���ȓ��̑q�ɂ��擾�B
    // �Ȃ����NULL
    Storehouse* GetNearStorehouse(const float x, const float z);

    // ���݂̊������_�̑q��
    Storehouse* GetCurrentActiveStorehouse();

    // �T�uID�����ׂĂ̑q�ɂ���擾����
    std::vector<int> GetSubIdListFromAllStorehouse(const int id);

    // �q�ɂ𑝂₷
    // �C�J�_�ɏ悹��q�ɂɂ��Ă̂ݑ��₷���Ƃ��ł���
    void AddStorehouse();

private:

    // �V���O���g���I�u�W�F�N�g
    static StorehouseManager* m_obj;

    std::map<int, Storehouse> m_StorehouseMap;

    bool m_inited = false;
};

}

