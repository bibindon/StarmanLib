#pragma once

namespace NSStarmanLib
{

//------------------------------------------------------
// �J�̃A���S���Y��
//
// �J���~���Ă��Ȃ��Ƃ�
//      1���̊m����1���Ԍ�ɉJ���~��B
//      ����1���Ԍ��1���̊m���ŉJ���~��B
//      ����Ȋ�����24���Ԍ�ɂ�22���̊m���ŉJ���~��B
//      1 - (0.99) ^ 24
//
// �J���~������1���Ԃ͏��Ȃ��Ƃ��~��
//
// �J���~������
//      1���Ԍ�ɉJ���~�ފm����10���B
//      ����1���Ԍ�ɉJ���~�ފm����10���A����ɂ���1���Ԍ�ɉJ���~�ފm����10���B
//      24���Ԍ���J���~���Ă���m����0.9��24���8���ɂȂ�B
//      �Ƃɂ�������Ȋ����Ōv�Z����B
//------------------------------------------------------

class Rain
{
public:
    
    static Rain* Get();
    void Destroy();
    void Update();
    bool IsRain() const;

private:

    static Rain* m_rain;
    bool m_bRain = false;

    int m_previousYear = 0;
    int m_previousMonth = 0;
    int m_previousDay = 0;
    int m_previousHour = 0;
};
}

