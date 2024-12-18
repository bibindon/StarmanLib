#include "SkillManager.h"

#include "Util.h"

using namespace NSStarmanLib;

SkillManager* SkillManager::obj { nullptr };

void SkillDefinition::SetName(const std::string& arg)
{
    m_name = arg;
}

std::string SkillDefinition::GetName()
{
    return m_name;
}

void SkillDefinition::SetDetail(const std::string& arg)
{
    m_detail = arg;
    m_detail.erase(std::remove(m_detail.begin(), m_detail.end(), '"'), m_detail.end());
}

std::string SkillDefinition::GetDetail()
{
    return m_detail;
}

void SkillDefinition::SetDamage(const int arg1, const float& arg2)
{
    m_damageMap[arg1] = arg2;
}

float SkillDefinition::GetDamage(const int arg)
{
    return m_damageMap[arg];
}

void SkillDefinition::SetRange(const int arg1, const float& arg2)
{
    m_rangeMap[arg1] = arg2;
}

float SkillDefinition::GetRange(const int arg)
{
    return m_rangeMap[arg];
}

SkillManager* SkillManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new SkillManager();
    }
    return obj;
}

void SkillManager::Destroy()
{
    delete SkillManager::obj;
    SkillManager::obj = nullptr;
}

void SkillManager::Init(const std::string& csvfileDefinition, const std::string& csvfilePlayer,
                        const bool decrypt)
{
    {
        std::vector<std::vector<std::string>> vss = Util::ReadFromCsv(csvfileDefinition, decrypt);

        SkillDefinition skillDefinition;
        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            skillDefinition.SetName(vss.at(i).at(0));
            skillDefinition.SetDetail(vss.at(i).at(1));
            skillDefinition.SetDamage(0, std::stof(vss.at(i).at(2)));
            skillDefinition.SetDamage(1, std::stof(vss.at(i).at(3)));
            skillDefinition.SetDamage(2, std::stof(vss.at(i).at(4)));
            skillDefinition.SetDamage(3, std::stof(vss.at(i).at(5)));
            skillDefinition.SetDamage(4, std::stof(vss.at(i).at(6)));
            skillDefinition.SetDamage(5, std::stof(vss.at(i).at(7)));
            skillDefinition.SetDamage(6, std::stof(vss.at(i).at(8)));
            skillDefinition.SetDamage(7, std::stof(vss.at(i).at(9)));
            skillDefinition.SetDamage(8, std::stof(vss.at(i).at(10)));
            skillDefinition.SetDamage(9, std::stof(vss.at(i).at(11)));
            skillDefinition.SetDamage(10, std::stof(vss.at(i).at(12)));

            skillDefinition.SetRange(0, std::stof(vss.at(i).at(13)));
            skillDefinition.SetRange(1, std::stof(vss.at(i).at(14)));
            skillDefinition.SetRange(2, std::stof(vss.at(i).at(15)));
            skillDefinition.SetRange(3, std::stof(vss.at(i).at(16)));
            skillDefinition.SetRange(4, std::stof(vss.at(i).at(17)));
            skillDefinition.SetRange(5, std::stof(vss.at(i).at(18)));
            skillDefinition.SetRange(6, std::stof(vss.at(i).at(19)));
            skillDefinition.SetRange(7, std::stof(vss.at(i).at(20)));
            skillDefinition.SetRange(8, std::stof(vss.at(i).at(21)));
            skillDefinition.SetRange(9, std::stof(vss.at(i).at(22)));
            skillDefinition.SetRange(10, std::stof(vss.at(i).at(23)));
            m_skillLevelMap[skillDefinition.GetName()] = skillDefinition;
        }
    }
    {
        std::vector<std::vector<std::string>> vss = Util::ReadFromCsv(csvfilePlayer, decrypt);

        int work = 0;

        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            work = std::stoi(vss.at(i).at(1));
            m_playerSkillLevelMap[vss.at(i).at(0)] = work;
        }
    }
}

void SkillManager::Save(const std::string& csvfile,
                        const bool encrypt)
{
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;
    std::string work;

    vs.push_back("–¼Ì");
    vs.push_back("ƒŒƒxƒ‹");
    vss.push_back(vs);
    vs.clear();

    for (auto it = m_playerSkillLevelMap.begin(); it != m_playerSkillLevelMap.end(); ++it)
    {
        vs.push_back(it->first);
        vs.push_back(std::to_string(it->second));
        vss.push_back(vs);
        vs.clear();
    }

    Util::WriteToCsv(csvfile, vss, encrypt);
}

void SkillManager::SetSkillLevel(const std::string& skillName, const int skillLevel)
{
    if (m_playerSkillLevelMap.find(skillName) == m_playerSkillLevelMap.end())
    {
        throw std::exception();
    }
    m_playerSkillLevelMap[skillName] = skillLevel;
}

int SkillManager::GetSkillLevel(const std::string& skillName)
{
    return m_playerSkillLevelMap.at(skillName);
}

std::string SkillManager::GetDetail(const std::string& key)
{
    return m_skillLevelMap.at(key).GetDetail();
}

float SkillManager::GetDamage(const std::string& key, const int level)
{
    return m_skillLevelMap.at(key).GetDamage(level);
}

float SkillManager::GetRange(const std::string& key, const int level)
{
    return m_skillLevelMap.at(key).GetRange(level);
}

std::vector<std::string> NSStarmanLib::SkillManager::GetNameList()
{
    std::vector<std::string> nameList;

    for (auto it = m_skillLevelMap.begin(); it != m_skillLevelMap.end(); ++it)
    {
        nameList.push_back(it->first);
    }

    return nameList;
}


