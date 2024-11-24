#pragma once

#include "HeaderOnlyCsv.hpp"

#include <string>
#include <vector>
#include <unordered_map>

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

    void Init(const std::string& csvfile);
    void Save(const std::string& csvfile);

    // ��������������o���Ȃ��z��
    void AddItem(const int id);
    void RemoveItem(const int id);
    int CountItem(const int id);

    float GetWeight();

private:

    float CalcWeight();

    // �V���O���g���I�u�W�F�N�g
    static Inventory* obj;

    // �����i�̏d�ʁi����͊܂߂Ȃ��j
    float m_weight;

    // �����i���X�g
    // �����A�C�e���𕡐������ł��邱�Ƃɒ���
    std::unordered_map<int, int> m_itemMap;
    
};
}

