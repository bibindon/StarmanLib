#pragma once

#include <string>
#include <vector>

namespace NSStarmanLib
{
// TODO セーブデータの暗号化

class MapInfo
{
public:

    void SetId(const int id);
    int GetId() const;

    void SetName(const std::wstring& name);
    std::wstring GetName();

    void SetDetail(const std::wstring& detail);
    std::wstring GetDetail();

    void SetPos(const int x, const int y);
    void GetPos(int* x, int* y);

    void SetImagePath(const std::wstring& imagePath);
    std::wstring GetImagePath();

    void SetDiscovered(const bool);
    bool IsDiscovered();

private:

    int m_id = 0;
    std::wstring m_name;
    std::wstring m_imagePath;
    std::wstring m_detail;
    int m_x = 0;
    int m_y = 0;
    bool m_isDiscovered = false;
};

class MapInfoManager
{
public:
    static MapInfoManager* GetObj();
    void Init(const std::wstring& csvfile,
              const bool decrypt = false);
    static void Destroy();
    std::vector<std::wstring> GetNameList();
    bool IsDiscovered(const std::wstring& name);
    void SetDiscovered(const std::wstring& name);
    void SetDiscovered(const int name);
    std::wstring GetDetail(const std::wstring& name);
    void GetPos(const std::wstring& name, int* x, int* y);
    std::wstring GetImagePath(const std::wstring& name);
    void Save(const std::wstring& csvfile,
              const bool encrypt = false);

private:

    static MapInfoManager* obj;
    std::vector<MapInfo> m_mapInfoList;
};
}

