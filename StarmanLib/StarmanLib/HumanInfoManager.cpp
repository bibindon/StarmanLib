#include "HumanInfoManager.h"
#include "ItemManager.h"

using namespace NSStarmanLib;

HumanInfoManager* HumanInfoManager::obj { nullptr };

HumanInfoManager* HumanInfoManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new HumanInfoManager();
    }
    return obj;
}

void HumanInfoManager::Destroy()
{
    delete HumanInfoManager::obj;
    HumanInfoManager::obj = nullptr;
}

void HumanInfoManager::Init(const std::string& csvfileBase, const std::string& csvfileSaved)
{
    {
        std::vector<std::vector<std::string> > vss;
        vss = csv::Read(csvfileBase);
        HumanInfo humanInfo;
        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            humanInfo.SetName(vss.at(i).at(1));

            // 「"」記号があれば削除
            std::string work = vss.at(i).at(2);
            work.erase(std::remove(work.begin(), work.end(), '"'), work.end());

            humanInfo.SetDetail(work);
            humanInfo.SetImagePath(vss.at(i).at(3));
            m_humanInfoMap[humanInfo.GetName()] = humanInfo;
        }
    }
    {
        std::vector<std::vector<std::string> > vss;
        vss = csv::Read(csvfileSaved);
        if (vss.size() == 0)
        {
            return;
        }
        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            std::string name = vss.at(i).at(0);
            if (vss.at(i).at(1) == "○")
            {
                m_humanInfoMap.at(name).SetVisible(true);
            }
            else
            {
                m_humanInfoMap.at(name).SetVisible(false);
            }
        }
    }
}

void HumanInfoManager::Save(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;
    vs.push_back("名前");
    vs.push_back("表示");
    vss.push_back(vs);
    vs.clear();

    for (auto it = m_humanInfoMap.begin(); it != m_humanInfoMap.end(); ++it)
    {
        vs.push_back(it->first);
        if (it->second.GetVisible())
        {
            vs.push_back("○");
        }
        else
        {
            vs.push_back("");
        }
        vss.push_back(vs);
        vs.clear();
    }

    csv::Write(csvfile, vss);
}

HumanInfo HumanInfoManager::GetHumanInfo(const std::string& name)
{
    return m_humanInfoMap.at(name);
}

std::vector<std::string> HumanInfoManager::GetHumanNameList()
{
    std::vector<std::string> result;
    for (auto it = m_humanInfoMap.begin(); it != m_humanInfoMap.end(); ++it)
    {
        result.push_back(it->first);
    }
    return result;
}

void HumanInfoManager::SetHumanVisible(const std::string& name)
{
    m_humanInfoMap.at(name).SetVisible(true);
}

void HumanInfo::SetName(const std::string& arg)
{
    m_name = arg;
}

std::string HumanInfo::GetName()
{
    return m_name;
}

void HumanInfo::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

std::string HumanInfo::GetDetail()
{
    return m_detail;
}

void HumanInfo::SetImagePath(const std::string& arg)
{
    m_imagePath = arg;
}

std::string HumanInfo::GetImagePath()
{
    return m_imagePath;
}

void HumanInfo::SetVisible(const bool arg)
{
    m_bVisible = arg;
}

bool HumanInfo::GetVisible()
{
    return m_bVisible;
}
