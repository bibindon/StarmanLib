#include "ActionManager.h"
#include <tchar.h>

using namespace NSStarmanLib;

void ActionManager::GetActionTime(const std::wstring actionName, int* day, int* hour, int* minute, int* second)
{
    if (actionName == _T("伐採"))
    {
        *day = 0;
        *hour = 6;
        *minute = 0;
        *second = 0;
    }
    else if (actionName == _T("睡眠"))
    {
        *day = 0;
        *hour = 8;
        *minute = 0;
        *second = 0;
    }
    else if (actionName == _T("仮眠"))
    {
        *day = 0;
        *hour = 1;
        *minute = 30;
        *second = 0;
    }
}
