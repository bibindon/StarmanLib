#pragma once

#include <string>

namespace NSStarmanLib
{

enum class eBaseType
{
    Precision = 0,
    DirectNex,
};

// �������_���
// 
// Config�Ƃ����N���X���ɂ��āA�������_�ȊO�̗l�X�Ȑݒ�l��������悤�ɂ��邩������Ȃ��B
class ActivityBase
{
public:

    static ActivityBase* Get();

    void Init(const std::string& csvFile);
    void Save(const std::string& csvFile);
    void SetBaseType(const eBaseType arg);
    eBaseType GetBaseType() const;
    void Finalize();

    // �D������̍��W
    // �N���t�g���ꂽ�C�J�_���z�u�����ꏊ
    void GetPierPos(const eBaseType baseType, float* x, float* y, float* z);

    // �C�J�_���D������ɂ��邩�B5���[�g���ȓ��ɂ���ꍇ�́A�C�J�_������ƌ��Ȃ����
    bool CheckRaftNearPier(const float x, const float y, const float z);

    // ���݂̊������_�ɃC�J�_�����邩
    bool CheckRaftExist();

private:

    ActivityBase();

    static ActivityBase* m_obj;

    eBaseType m_eBaseType = eBaseType::Precision;

};
}

