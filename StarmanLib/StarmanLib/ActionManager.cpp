#include "ActionManager.h"

void ActionManager::GetActionTime(const std::string actionName, int* day, int* hour, int* minute, int* second)
{
    if (actionName == "����")
    {
        *day = 0;
        *hour = 6;
        *minute = 0;
        *second = 0;
    }
    else if (actionName == "����")
    {
        *day = 0;
        *hour = 8;
        *minute = 0;
        *second = 0;
    }
    else if (actionName == "����")
    {
        *day = 0;
        *hour = 1;
        *minute = 30;
        *second = 0;
    }
}
