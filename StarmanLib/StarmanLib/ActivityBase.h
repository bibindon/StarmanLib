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

private:

    ActivityBase();

    static ActivityBase* m_obj;

    eBaseType m_eBaseType = eBaseType::Precision;

};
}

