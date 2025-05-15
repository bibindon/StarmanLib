#pragma once

#include "HeaderOnlyCsv.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{
class HumanInfo
{
public:

    void SetName(const std::string& arg);
    std::string GetName();

    void SetDetail(const std::string& arg);
    std::string GetDetail();

    void SetImagePath(const std::string& arg);
    std::string GetImagePath();

    void SetVisible(const bool arg);
    bool GetVisible();

private:

    std::string m_name;
    std::string m_detail;
    std::string m_imagePath;

    // 人物情報はメニュー画面で表示され、
    // ゲームの進行度によって表示される人と表示されない人がいる想定
    bool m_bVisible;
};

class HumanInfoManager
{

public:

    static HumanInfoManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfileBase, const std::string& csvfileSaved,
              const bool decrypt = false);

    void Save(const std::string& csvfile,
              const bool encrypt = false);

    HumanInfo GetHumanInfo(const std::string& name);
    std::vector<std::string> GetHumanNameList();
    void SetHumanVisible(const std::string& name);

private:

    // シングルトンオブジェクト
    static HumanInfoManager* obj;

    std::unordered_map<std::string, HumanInfo> m_humanInfoMap;

};
}

