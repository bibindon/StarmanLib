#pragma once

#include "HeaderOnlyCsv.hpp"

#include <string>
#include <vector>
#include <unordered_map>

// �q�ɃN���X
// ���_�ɗa���Ă���A�C�e��
// �X�g�[���[�̓s���ŋ��_�͓r����1�x�ς�邱�Ƃɒ��ӁB
// ���_�Ԃőq�ɂ̒��g�����o����悤�ɂ͂��Ȃ��z��B
class Storehouse
{

public:

    static Storehouse* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);
    void Save(const std::string& csvfile);

    // ��������������o���Ȃ��z��
    void AddItem(const int id);
    void RemoveItem(const int id);
    int CountItem(const int id);

private:

    // �V���O���g���I�u�W�F�N�g
    static Storehouse* obj;

    // �����i���X�g
    // �����A�C�e���𕡐������ł��邱�Ƃɒ���
    std::unordered_map<int, int> m_itemMap;
    
};

