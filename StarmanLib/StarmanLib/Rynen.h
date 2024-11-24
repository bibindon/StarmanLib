#pragma once
#include <string>

namespace NSStarmanLib
{
// ���C�l���Ƃ����_����Ǘ�����N���X
// �����ƌ_�񂷂�Ɩ��@���g����悤�ɂȂ�A���[�h�u���X�Ƃ������r�Ŏ���ł������ł���悤�ɂȂ�B
// �������A1�N��Ɏ��ʁB
// 
// �����V�X�e��
// ���[�h�u���X�Ƃ������r�����񂾂�1�x���������Ԃ���B
// �E�����Ԃ�ꏊ�͏��r�����񂾏ꏊ
// �E���{����ł������Ԃ���̂�1�x����
// �E�����Ԃ�����ɂ�����x���߂΂�����x�����Ԃ���
// �E�̗͂͑S������
// �E���r������ł��Ȃ���ԂŎ��񂾂�Q�[���̓I�[�v�j���O����X�^�[�g�ɂȂ�
class Rynen
{
public:

    static Rynen* GetObj();
    static void Destroy();
    void Init(const std::string& csvfile);
    void Save(const std::string& csvfile);

    void SetContracted(const bool arg);
    bool GetContracted();

    void SetReviveEnable(const bool arg);
    bool GetReviveEnable();

    void SetRevivePos(const float x, const float y, const float z);
    void GetRevivePos(float* x, float* y, float* z);

    void SetContractDate(const int month, const int day);
    void GetContractDate(int* month, int* day);

private:

    // �V���O���g���I�u�W�F�N�g
    static Rynen* obj;

    // �_��ς݃t���O
    bool m_contracted { false };

    // �����\�t���O
    bool m_reviveEnable { false };

    // �����ꏊ
    float m_x { 0.f };
    float m_y { 0.f };
    float m_z { 0.f };

    // �_�񂵂���
    int m_month { 0 };
    int m_day { 0 };
};
}

