#include "MapInfoManager.h"

#include "Util.h"

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

    // 「"」記号は取り除く
    m_detail.erase(std::remove(m_detail.begin(), m_detail.end(), '"'), m_detail.end());
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

void NSStarmanLib::MapInfo::SetImagePath(const std::string& imagePath)
{
    m_imagePath = imagePath;
}

std::string NSStarmanLib::MapInfo::GetImagePath()
{
    return m_imagePath;
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

void MapInfoManager::Init(const std::string& csvfile,
                          const bool decrypt)
{
    std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvfile, decrypt);

    for (std::size_t i = 1; i < vvs.size(); ++i)
    {
        MapInfo mapInfo;
        mapInfo.SetName(vvs.at(i).at(1));
        if (vvs.at(i).at(2) == "○")
        {
            mapInfo.SetDiscovered(true);
        }
        else
        {
            mapInfo.SetDiscovered(false);
        }
        mapInfo.SetDetail(vvs.at(i).at(3));
        int x = std::stoi(vvs.at(i).at(4));
        int y = std::stoi(vvs.at(i).at(5));
        mapInfo.SetPos(x, y);

        mapInfo.SetImagePath(vvs.at(i).at(6));
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

std::string NSStarmanLib::MapInfoManager::GetImagePath(const std::string& name)
{
    auto it = std::find_if(m_mapInfoList.begin(),
                           m_mapInfoList.end(),
                           [&](MapInfo mi) { return mi.GetName() == name; });

    return it->GetImagePath();
}

void MapInfoManager::Save(const std::string& csvfile,
                          const bool encrypt)
{
    std::vector<std::vector<std::string>> vvs;
    std::vector<std::string> vs;
    vs.push_back("ID");
    vs.push_back("地名");
    vs.push_back("発見済み");
    vs.push_back("説明文");
    vs.push_back("X");
    vs.push_back("Y");
    vs.push_back("画像ファイル名");
    vvs.push_back(vs);
    vs.clear();
    for (std::size_t i = 0; i < m_mapInfoList.size(); ++i)
    {
        vs.push_back(std::to_string(i+1));
        vs.push_back(m_mapInfoList.at(i).GetName());
        if (m_mapInfoList.at(i).IsDiscovered())
        {
            vs.push_back("○");
        }
        else
        {
            vs.push_back("");
        }
        std::string work = m_mapInfoList.at(i).GetDetail();
        work = "\"" + work + "\"";
        vs.push_back(work);

        int x = 0;
        int y = 0;
        m_mapInfoList.at(i).GetPos(&x, &y);
        vs.push_back(std::to_string(x));
        vs.push_back(std::to_string(y));

        vs.push_back(m_mapInfoList.at(i).GetImagePath());

        vvs.push_back(vs);
        vs.clear();
    }

    Util::WriteToCsv(csvfile, vvs, encrypt);
}
