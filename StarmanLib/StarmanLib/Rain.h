#pragma once

namespace NSStarmanLib
{

//------------------------------------------------------
// ‰J‚ÌƒAƒ‹ƒSƒŠƒYƒ€
//
// ‰J‚ª~‚Á‚Ä‚¢‚È‚¢‚Æ‚«
//      1“‚ÌŠm—¦‚Å1ŠÔŒã‚É‰J‚ª~‚éB
//      ‚»‚Ì1ŠÔŒã‚à1“‚ÌŠm—¦‚Å‰J‚ª~‚éB
//      ‚»‚ñ‚ÈŠ´‚¶‚Å24ŠÔŒã‚É‚Í22“‚ÌŠm—¦‚Å‰J‚ª~‚éB
//      1 - (0.99) ^ 24
//
// ‰J‚ª~‚Á‚½‚ç1ŠÔ‚Í­‚È‚­‚Æ‚à~‚é
//
// ‰J‚ª~‚Á‚½‚ç
//      1ŠÔŒã‚É‰J‚ª~‚ŞŠm—¦‚Í10“B
//      ‚»‚Ì1ŠÔŒã‚É‰J‚ª~‚ŞŠm—¦‚à10“A‚³‚ç‚É‚»‚Ì1ŠÔŒã‚É‰J‚ª~‚ŞŠm—¦‚à10“B
//      24ŠÔŒã‚à‰J‚ª~‚Á‚Ä‚¢‚éŠm—¦‚Í0.9‚Ì24æ‚Å8“‚É‚È‚éB
//      ‚Æ‚É‚©‚­‚»‚ñ‚ÈŠ´‚¶‚ÅŒvZ‚·‚éB
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

