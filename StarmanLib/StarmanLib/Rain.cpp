#include "Rain.h"

#include "PowereggDateTime.h"
#include <time.h>

NSStarmanLib::Rain* NSStarmanLib::Rain::m_rain = nullptr;

NSStarmanLib::Rain* NSStarmanLib::Rain::Get()
{
    if (m_rain == nullptr)
    {
        m_rain = new Rain();

        // 0 ~ 99の乱数
        srand((unsigned int)time(NULL));
    }

    return m_rain;
}

void NSStarmanLib::Rain::Destroy()
{
    delete m_rain;
    m_rain = nullptr;
}

// 雨の状態を更新。詳細はヘッダーファイル。
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

    // 0分0秒を越えたら更新処理を行う。
    // そのために、前回、Update関数が呼ばれた時刻から1時間経過しているかを確認する。
    bool updateNecessary = false;

    // 現在時刻（時）が以前より増えているなら1時間経過した
    if (currentHour > m_previousHour)
    {
        updateNecessary = true;
    }
    // 現在時刻（時）が以前より増えていなくても1時間経過している場合がある。
    // 23時→0時など。
    else
    {
        // 現在時刻（日）が以前より増えているなら1時間経過した。
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

        // 雨が降っていない場合、1％の確率で雨が降る
        if (!m_bRain)
        {
            // rnd == 0だったら1%の確率を引き当てた、ということ
            if (rnd == 0)
            {
                m_bRain = true;
            }
        }
        // 雨が降っていた場合、10％の確率で雨がやむ
        else
        {
            if (rnd <= 9)
            {
                m_bRain = false;
            }
        }
    }

    // 次回、この関数を呼ばれた時のために現在時刻を保存。
    m_previousYear = currentYear;
    m_previousMonth = currentMonth;
    m_previousDay = currentDay;
    m_previousHour = currentHour;
}

bool NSStarmanLib::Rain::IsRain() const
{
    return m_bRain;
}
