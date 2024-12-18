#pragma once

#include <string>
#include <vector>

namespace NSStarmanLib
{
// TODO セーブデータの暗号化

class MapInfo
{
public:

    void SetName(const std::string& name);
    std::string GetName();

    void SetDetail(const std::string& detail);
    std::string GetDetail();

    void SetPos(const int x, const int y);
    void GetPos(int* x, int* y);

    void SetImagePath(const std::string& imagePath);
    std::string GetImagePath();

    void SetDiscovered(const bool);
    bool IsDiscovered();

private:

    std::string m_name;
    std::string m_imagePath;
    std::string m_detail;
    int m_x = 0;
    int m_y = 0;
    bool m_isDiscovered = false;
};

class MapInfoManager
{
public:
    static MapInfoManager* GetObj();
    void Init(const std::string& csvfile,
              const bool decrypt = false);
    static void Destroy();
    std::vector<std::string> GetNameList();
    bool IsDiscovered(const std::string& name);
    void SetDiscovered(const std::string& name);
    std::string GetDetail(const std::string& name);
    void GetPos(const std::string& name, int* x, int* y);
    std::string GetImagePath(const std::string& name);
    void Save(const std::string& csvfile,
              const bool encrypt = false);

private:

    static MapInfoManager* obj;
    std::vector<MapInfo> m_mapInfoList;
};
}

