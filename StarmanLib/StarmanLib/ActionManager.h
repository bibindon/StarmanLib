#pragma once
#include <string>

namespace NSStarmanLib
{
// �؂𕀂Ő؂�A�Ȃ�
// �؂�|�����Ƃ�����u�؂�|���܂����H�i�U���ԏ���j�v�A�̂悤�ɕ\�������
// �U���ԂƂ����̂̓p���[�G�b�O���̎��ԁB
// �E�����i�ނ悤�ɂ���B
// �E�̗͂��K��ʂ�������
// �E�쎀���O�Ŏ��s���邱�Ƃ͂ł��Ȃ��B
//
// ���Ԃ̂�����s���̎��
// 
// ����
// ����
// ����
// �̏W�i���z�΁j
// ���H
// �C��
// ����
// �ނ�
//
// �܂��͔��̂����ŗǂ��B���̍s���͐�������Ȃ��C������B

class ActionManager
{
public:
    void GetActionTime(const std::string actionName,
                       int* day,
                       int* hour,
                       int* minute,
                       int* second);
private:

};
}
