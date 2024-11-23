#pragma once

#include <string>

// �Q�[�����̓��t�E����
// �p���[�G�b�O���ł�24���Ԃň�����o�߂��A�Q�[�����ł�2���Ԃ�24���Ԃ��o�߂���B

class PowereggDateTime
{
public:

    static PowereggDateTime* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);
    void Save(const std::string& csvfile);

    // ����i�߂�B�p���[�G�b�O���̎��Ԏ��Ŏw�肷��B
    // �p���[�G�b�O���ł�24���Ԃ��Q�[�����ł�2���Ԃł��邪�A
    // �Q�[�������Ԃł͂Ȃ��p���[�G�b�O���ł̎��Ԃ��w�肷��B
    void IncreaseDateTime(int month, int day, int hour, int minute, int second);
    int GetYear();
    int GetMonth();
    int GetDay();
    int GetHour();
    int GetMinute();
    int GetSecond();

private:

    // �V���O���g��
    static PowereggDateTime* obj;

    int m_year { 0 };
    int m_month { 0 };
    int m_day { 0 };
    int m_hour { 0 };
    int m_minute { 0 };
    int m_second { 0 };

    // DAY_OF_MONTH[1]��1���̓�����\���B
    // DAY_OF_MONTH[0]�͖���
    const int DAY_OF_MONTH[13] { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
};

