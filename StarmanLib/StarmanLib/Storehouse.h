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

    static Storehouse* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);
    bool Inited();
    void Save(const std::string& csvfile);

    // ��������������o���Ȃ��z��
    void AddItem(const int id, const int durability = -1);
    void AddItem(const std::string name, const int level = -1, const int durability = -1);

    // �V����SubID�����蓖�ĂȂ��i�C���x���g������q�ɂփA�C�e�����ړ�����Ƃ��Ɏg���j
    void AddExistingItem(const int id, const int subId);

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

private:

    float CalcWeight();

    void Sort();

    // �V���O���g���I�u�W�F�N�g
    static Storehouse* obj;

    // �����i�̏d�ʁi����͊܂߂Ȃ��j
    float m_weight;

    // �����i���X�g
    // �����A�C�e���𕡐������ł��邱�Ƃɒ���
    std::list<ItemInfo> m_itemInfoList;
    
    bool m_inited = false;
};
}

