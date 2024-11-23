#pragma once

#include <string>

// ゲーム内の日付・時刻
// パワーエッグ星では24時間で一日が経過し、ゲーム内では2時間で24時間が経過する。

class PowereggDateTime
{
public:

    static PowereggDateTime* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);
    void Save(const std::string& csvfile);

    // 時を進める。パワーエッグ星の時間軸で指定する。
    // パワーエッグ星での24時間がゲーム内では2時間であるが、
    // ゲーム内時間ではなくパワーエッグ星での時間を指定する。
    void IncreaseDateTime(int month, int day, int hour, int minute, int second);
    int GetYear();
    int GetMonth();
    int GetDay();
    int GetHour();
    int GetMinute();
    int GetSecond();

private:

    // シングルトン
    static PowereggDateTime* obj;

    int m_year { 0 };
    int m_month { 0 };
    int m_day { 0 };
    int m_hour { 0 };
    int m_minute { 0 };
    int m_second { 0 };

    // DAY_OF_MONTH[1]が1月の日数を表す。
    // DAY_OF_MONTH[0]は無効
    const int DAY_OF_MONTH[13] { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
};

