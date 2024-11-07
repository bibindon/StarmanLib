#include "MapInfoManager.h"

void MapInfo::SetName(const std::string& name)
{
}

std::string MapInfo::GetName()
{
    return std::string();
}

void MapInfo::SetDetail(const std::string& detail)
{
}

std::string MapInfo::GetDetail()
{
    return std::string();
}

void MapInfo::SetPos(const int x, const int y)
{
}

void MapInfo::GetPos(int* x, int* y)
{
}

void MapInfo::SetDiscovered(const bool)
{
}

bool MapInfo::IsDiscovered()
{
    return false;
}

MapInfoManager* MapInfoManager::GetObj()
{
    return nullptr;
}

std::vector<std::string> MapInfoManager::GetNameList()
{
    return std::vector<std::string>();
}

bool MapInfoManager::IsDiscovered(const std::string& name)
{
    return false;
}

std::string MapInfoManager::GetDetail(const std::string& name)
{
    return std::string();
}

void MapInfoManager::GetPos(const std::string& name, int* x, int* y)
{
}

void MapInfoManager::Save()
{
}

void MapInfoManager::Init(const std::string& csvfile)
{
}
