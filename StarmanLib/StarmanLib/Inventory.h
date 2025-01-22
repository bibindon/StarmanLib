// TODO �ő�ύڗ�
#pragma once

#include "HeaderOnlyCsv.hpp"
#include "ItemManager.h"

#include <string>
#include <vector>
#include <unordered_map>
#include "StatusManager.h"

namespace NSStarmanLib
{
// �v���C���[�̏����i���Ǘ�����N���X�B
// �A�C�e���̒�`��ItemManager���Ǘ����Ă���B
// ����ɂ��Ă�WeaponManager���������܂ŊǗ����Ă���̂�
// Inventory�N���X�ɏo�Ԃ͂Ȃ��\��

class Inventory
{
public:

    static Inventory* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile,
              const bool decrypt = false);
    bool Inited();
    void Save(const std::string& csvfile,
              const bool encrypt = false);

    // ��������������o���Ȃ��z��
    // �V����SubID�����蓖�Ă�
    // �V���Ɋ��蓖�Ă�SubID��Ԃ�
    int AddItem(const int id, const int durability = -1);
    int AddItem(const std::string name, const int level = -1, const int durability = -1);

    // SubID���w�肵�ăA�C�e����ǉ��i�q�ɂ���C���x���g���փA�C�e�����ړ�����Ƃ��Ɏg���j
    // �q�ɂŃA�C�e�����폜���Ă���ǉ�����K�v������B
    // �q�ɂŃA�C�e�����폜���Ă��Ȃ��Ɓu���łɂ���SubID�͎g���Ă���v�Ƃ������ƂŃG���[�ɂȂ�
    void AddItemWithSubID(const int id, const int subId, const int durability = -1);

    // subId�E�E�E�ϋv�l��50�̐Ε��Ƒϋv�l��100�̐Ε����������邱�Ƃ��ł���
    // ���̂��߁A�A�C�e���ɂ�subId���U����B�A�C�e�����폜����ɂ�subId���Ȃ��Ƃł��Ȃ�
    // �A�C�e���͍폜�ł���̂�SubID���A�ԂɂȂ�Ƃ͌���Ȃ�
    void RemoveItem(const int id, const int subId);
    void RemoveItem(const std::string name, const int subId, const int level = -1);

    void SetItemDurability(const int id, const int subId, const int durability);

    bool ExistItem(const int id, const int subId);
    ItemInfo GetItemInfo(const int id, const int subId);

    // SubID�����X�g�Ŏ󂯎��
    std::vector<int> GetSubIdList(const int id);

    int CountItem(const int id);
    int CountItem(const std::string name, const int level = -1);

    float GetWeight();

    std::list<ItemInfo> GetAllItem();

    float CalcVolume();
    float GetVolume() const;

    void UpdateVolumeMax(const std::vector<ItemInfo>& bagMap);
    float GetVolumeMax() const;

    // �������̑܂̑ϋv�l�����炷
    void ReduceEquipBagDurability();

private:
    // �ȉ���4�̊֐���錾�E��`����̂����������E�E�E�Ȃ��Ă��E�E�E�ʂɁE�E�E
    Inventory() {};
    Inventory(const Inventory&);
    Inventory& operator=(const Inventory&) {}
    ~Inventory() {};

    float CalcWeight();

    void Sort();

    // �V���O���g���I�u�W�F�N�g
    static Inventory* obj;

    // �����i�̏d�ʁi����͊܂߂Ȃ��j
    float m_weight = 0.f;

    // �����i���X�g
    // �����A�C�e���𕡐������ł��邱�Ƃɒ���
    std::list<ItemInfo> m_itemInfoList;
    
    bool m_inited = false;

    // �ő�ύڗ�
    float m_volumeMax = 0.f;
    float m_volumeCurrent = 0.f;
};
}

