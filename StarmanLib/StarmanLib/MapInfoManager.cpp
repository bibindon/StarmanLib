#include "MapInfoManager.h"
#include "HeaderOnlyCsv.hpp"

using namespace NSStarmanLib;

MapInfoManager* MapInfoManager::obj { nullptr };

void MapInfo::SetName(const std::string& name)
{
    m_name = name;
}

std::string MapInfo::GetName()
{
    return m_name;
}

void MapInfo::SetDetail(const std::string& detail)
{
    m_detail = detail;
}

std::string MapInfo::GetDetail()
{
    return m_detail;
}

void MapInfo::SetPos(const int x, const int y)
{
    m_x = x;
    m_y = y;
}

void MapInfo::GetPos(int* x, int* y)
{
    *x = m_x;
    *y = m_y;
}

void MapInfo::SetDiscovered(const bool discovered)
{
    m_isDiscovered = discovered;
}

bool MapInfo::IsDiscovered()
{
    return m_isDiscovered;
}

MapInfoManager* MapInfoManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new MapInfoManager();
    }
    return obj;
}

void MapInfoManager::Init(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vss;
    vss = csv::Read(csvfile);
    for (std::size_t i = 1; i < vss.size(); ++i)
    {
        MapInfo mapInfo;
        mapInfo.SetName(vss.at(i).at(1));
        if (vss.at(i).at(2) == "ÅZ")
        {
            mapInfo.SetDiscovered(true);
        }
        else
        {
            mapInfo.SetDiscovered(false);
        }
        mapInfo.SetDetail(vss.at(i).at(3));
        int x = std::stoi(vss.at(i).at(4));
        int y = std::stoi(vss.at(i).at(5));
        mapInfo.SetPos(x, y);
        m_mapInfoList.push_back(mapInfo);
    }
}

void MapInfoManager::Destroy()
{
    delete MapInfoManager::obj;
    MapInfoManager::obj = nullptr;
}

std::vector<std::string> MapInfoManager::GetNameList()
{
    std::vector<std::string> vs;
    for (std::size_t i = 0; i < m_mapInfoList.size(); ++i)
    {
        vs.push_back(m_mapInfoList.at(i).GetName());
    }
    return vs;
}

bool MapInfoManager::IsDiscovered(const std::string& name)
{
    auto it = std::find_if(m_mapInfoList.begin(),
                           m_mapInfoList.end(),
                           [&](MapInfo mi) { return mi.GetName() == name; });

    return it->IsDiscovered();
}

void MapInfoManager::SetDiscovered(const std::string& name)
{
    auto it = std::find_if(m_mapInfoList.begin(),
                           m_mapInfoList.end(),
                           [&](MapInfo mi) { return mi.GetName() == name; });

    return it->SetDiscovered(true);
}

std::string MapInfoManager::GetDetail(const std::string& name)
{
    auto it = std::find_if(m_mapInfoList.begin(),
                           m_mapInfoList.end(),
                           [&](MapInfo mi) { return mi.GetName() == name; });

    return it->GetDetail();
}

void MapInfoManager::GetPos(const std::string& name, int* x, int* y)
{
    auto it = std::find_if(m_mapInfoList.begin(),
                           m_mapInfoList.end(),
                           [&](MapInfo mi) { return mi.GetName() == name; });

    it->GetPos(x, y);
}

void MapInfoManager::Save(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;
    vs.push_back("ID");
    vs.push_back("ínñº");
    vs.push_back("î≠å©çœÇ›");
    vs.push_back("ê‡ñæï∂");
    vs.push_back("X");
    vs.push_back("Y");
    vss.push_back(vs);
    vs.clear();
    for (std::size_t i = 0; i < m_mapInfoList.size(); ++i)
    {
        vs.push_back(std::to_string(i+1));
        vs.push_back(m_mapInfoList.at(i).GetName());
        if (m_mapInfoList.at(i).IsDiscovered())
        {
            vs.push_back("ÅZ");
        }
        else
        {
            vs.push_back("");
        }
        vs.push_back(m_mapInfoList.at(i).GetDetail());
        int x = 0;
        int y = 0;
        m_mapInfoList.at(i).GetPos(&x, &y);
        vs.push_back(std::to_string(x));
        vs.push_back(std::to_string(y));
        vss.push_back(vs);
        vs.clear();
    }
    csv::Write(csvfile, vss);
}
