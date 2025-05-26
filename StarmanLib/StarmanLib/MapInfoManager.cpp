#include "MapInfoManager.h"

#include "Util.h"

using namespace NSStarmanLib;

MapInfoManager* MapInfoManager::obj { nullptr };

void MapInfo::SetId(const int id)
{
    m_id = id;
}

int MapInfo::GetId() const
{
    return m_id;
}

void MapInfo::SetName(const std::wstring& name)
{
    m_name = name;
}

std::wstring MapInfo::GetName()
{
    return m_name;
}

void MapInfo::SetDetail(const std::wstring& detail)
{
    m_detail = detail;

    // 「"」記号は取り除く
    m_detail.erase(std::remove(m_detail.begin(), m_detail.end(), '"'), m_detail.end());
}

std::wstring MapInfo::GetDetail()
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

void NSStarmanLib::MapInfo::SetImagePath(const std::wstring& imagePath)
{
    m_imagePath = imagePath;
}

std::wstring NSStarmanLib::MapInfo::GetImagePath()
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

void MapInfoManager::Init(const std::wstring& csvfile,
                          const bool decrypt)
{
    m_mapInfoList.clear();

    std::vector<std::vector<std::wstring>> vvs = Util::ReadFromCsv(csvfile, decrypt);

    for (std::size_t i = 1; i < vvs.size(); ++i)
    {
        MapInfo mapInfo;
        mapInfo.SetId(std::stoi(vvs.at(i).at(0)));
        mapInfo.SetName(vvs.at(i).at(1));
        if (vvs.at(i).at(2) == _T("○"))
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

std::vector<std::wstring> MapInfoManager::GetNameList()
{
    std::vector<std::wstring> vs;
    for (std::size_t i = 0; i < m_mapInfoList.size(); ++i)
    {
        vs.push_back(m_mapInfoList.at(i).GetName());
    }
    return vs;
}

bool MapInfoManager::IsDiscovered(const std::wstring& name)
{
    auto it = std::find_if(m_mapInfoList.begin(),
                           m_mapInfoList.end(),
                           [&](MapInfo mi) { return mi.GetName() == name; });

    return it->IsDiscovered();
}

void MapInfoManager::SetDiscovered(const int id)
{
    auto it = std::find_if(m_mapInfoList.begin(),
                           m_mapInfoList.end(),
                           [&](MapInfo mi) { return mi.GetId() == id; });

    it->SetDiscovered(true);
}

void MapInfoManager::SetDiscovered(const std::wstring& name)
{
    auto it = std::find_if(m_mapInfoList.begin(),
                           m_mapInfoList.end(),
                           [&](MapInfo mi) { return mi.GetName() == name; });

    it->SetDiscovered(true);
}

std::wstring MapInfoManager::GetDetail(const std::wstring& name)
{
    auto it = std::find_if(m_mapInfoList.begin(),
                           m_mapInfoList.end(),
                           [&](MapInfo mi) { return mi.GetName() == name; });

    return it->GetDetail();
}

void MapInfoManager::GetPos(const std::wstring& name, int* x, int* y)
{
    auto it = std::find_if(m_mapInfoList.begin(),
                           m_mapInfoList.end(),
                           [&](MapInfo mi) { return mi.GetName() == name; });

    it->GetPos(x, y);
}

std::wstring NSStarmanLib::MapInfoManager::GetImagePath(const std::wstring& name)
{
    auto it = std::find_if(m_mapInfoList.begin(),
                           m_mapInfoList.end(),
                           [&](MapInfo mi) { return mi.GetName() == name; });

    return it->GetImagePath();
}

void MapInfoManager::Save(const std::wstring& csvfile,
                          const bool encrypt)
{
    std::vector<std::vector<std::wstring>> vvs;
    std::vector<std::wstring> vs;
    vs.push_back(_T("ID"));
    vs.push_back(_T("地名"));
    vs.push_back(_T("発見済み"));
    vs.push_back(_T("説明文"));
    vs.push_back(_T("X"));
    vs.push_back(_T("Y"));
    vs.push_back(_T("画像ファイル名"));
    vvs.push_back(vs);
    vs.clear();
    for (std::size_t i = 0; i < m_mapInfoList.size(); ++i)
    {
        vs.push_back(std::to_wstring(m_mapInfoList.at(i).GetId()));
        vs.push_back(m_mapInfoList.at(i).GetName());
        if (m_mapInfoList.at(i).IsDiscovered())
        {
            vs.push_back(_T("○"));
        }
        else
        {
            vs.push_back(_T(""));
        }
        std::wstring work = m_mapInfoList.at(i).GetDetail();
        work = _T("\"") + work + _T("\"");
        vs.push_back(work);

        int x = 0;
        int y = 0;
        m_mapInfoList.at(i).GetPos(&x, &y);
        vs.push_back(std::to_wstring(x));
        vs.push_back(std::to_wstring(y));

        vs.push_back(m_mapInfoList.at(i).GetImagePath());

        vvs.push_back(vs);
        vs.clear();
    }

    Util::WriteToCsv(csvfile, vvs, encrypt);
}

