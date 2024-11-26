#pragma once

#include "HeaderOnlyCsv.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{
// �q�ɃN���X
// ���_�ɗa���Ă���A�C�e��
// �X�g�[���[�̓s���ŋ��_�͓r����1�x�ς�邱�Ƃɒ��ӁB
// ���_�Ԃőq�ɂ̒��g�����o����悤�ɂ͂��Ȃ��z��B
// TODO ����NPC���m���ɂȂ����烏�[�h�u���X�������B
class Storehouse
{

public:

    static Storehouse* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);
    void Save(const std::string& csvfile);

    // ��������������o���Ȃ��z��
    void AddItem(const int id);
    void AddItem(const std::string& name, const int level = -1);
    void RemoveItem(const int id);
    void RemoveItem(const std::string& name, const int level = -1);
    int CountItem(const int id);
    int CountItem(const std::string& name, const int level = -1);

private:

    // �V���O���g���I�u�W�F�N�g
    static Storehouse* obj;

    // �����i���X�g
    // �����A�C�e���𕡐������ł��邱�Ƃɒ���
    std::unordered_map<int, int> m_itemMap;

};
}

