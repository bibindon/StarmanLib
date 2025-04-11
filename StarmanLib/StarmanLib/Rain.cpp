#include "Rain.h"

#include "PowereggDateTime.h"
#include <time.h>

NSStarmanLib::Rain* NSStarmanLib::Rain::m_rain = nullptr;

NSStarmanLib::Rain* NSStarmanLib::Rain::Get()
{
    if (m_rain == nullptr)
    {
        m_rain = new Rain();

        // 0 ~ 99�̗���
        srand((unsigned int)time(NULL));
    }

    return m_rain;
}

void NSStarmanLib::Rain::Destroy()
{
    delete m_rain;
    m_rain = nullptr;
}

// �J�̏�Ԃ��X�V�B�ڍׂ̓w�b�_�[�t�@�C���B
void NSStarmanLib::Rain::Update()
{
    auto datetime = PowereggDateTime::GetObj();
    if (datetime == nullptr)
    {
        return;
    }

    int currentYear = datetime->GetYear();
    int currentMonth = datetime->GetMonth();
    int currentDay = datetime->GetDay();
    int currentHour = datetime->GetHour();

    // 0��0�b���z������X�V�������s���B
    // ���̂��߂ɁA�O��AUpdate�֐����Ă΂ꂽ��������1���Ԍo�߂��Ă��邩���m�F����B
    bool updateNecessary = false;

    // ���ݎ����i���j���ȑO��葝���Ă���Ȃ�1���Ԍo�߂���
    if (currentHour > m_previousHour)
    {
        updateNecessary = true;
    }
    // ���ݎ����i���j���ȑO��葝���Ă��Ȃ��Ă�1���Ԍo�߂��Ă���ꍇ������B
    // 23����0���ȂǁB
    else
    {
        // ���ݎ����i���j���ȑO��葝���Ă���Ȃ�1���Ԍo�߂����B
        if (currentDay > m_previousDay)
        {
            updateNecessary = true;
        }
        else
        {
            if (currentMonth > m_previousMonth)
            {
                updateNecessary = true;
            }
            else
            {
                if (currentYear > m_previousYear)
                {
                    updateNecessary = true;
                }
            }
        }
    }

    if (updateNecessary)
    {
        int rnd = rand() % 100;

        // �J���~���Ă��Ȃ��ꍇ�A1���̊m���ŉJ���~��
        if (!m_bRain)
        {
            // rnd == 0��������1%�̊m�����������Ă��A�Ƃ�������
            if (rnd == 0)
            {
                m_bRain = true;
            }
        }
        // �J���~���Ă����ꍇ�A10���̊m���ŉJ�����
        else
        {
            if (rnd <= 9)
            {
                m_bRain = false;
            }
        }
    }

    // ����A���̊֐����Ă΂ꂽ���̂��߂Ɍ��ݎ�����ۑ��B
    m_previousYear = currentYear;
    m_previousMonth = currentMonth;
    m_previousDay = currentDay;
    m_previousHour = currentHour;
}

bool NSStarmanLib::Rain::IsRain() const
{
    return m_bRain;
}
