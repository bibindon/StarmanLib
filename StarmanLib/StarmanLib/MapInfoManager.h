#pragma once

#include <string>
#include <vector>

class MapInfo
{
public:

    void SetName(const std::string& name);
    std::string GetName();

    void SetDetail(const std::string& detail);
    std::string GetDetail();

    void SetPos(const int x, const int y);
    void GetPos(int* x, int* y);

    void SetDiscovered(const bool);
    bool IsDiscovered();

private:

    std::string m_name;
    std::string m_detail;
    int m_x;
    int m_y;
    bool m_isDiscovered;
};

class MapInfoManager
{
public:
    static MapInfoManager* GetObj();
    std::vector<std::string> GetNameList();
    bool IsDiscovered(const std::string& name);
    std::string GetDetail(const std::string& name);
    void GetPos(const std::string& name, int* x, int* y);
    void Save();

private:
    void Init(const std::string& csvfile);

};

