#include "SkillManager.h"

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

void SkillManager::Init(const std::string& csvfileDefinition, const std::string& csvfilePlayer)
{
    {
        std::vector<std::vector<std::string> > vss;
        vss = csv::Read(csvfileDefinition);

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
            skillDefinition.SetRange(2, std::stof(vss.at(i).at(16)));
            skillDefinition.SetRange(3, std::stof(vss.at(i).at(17)));
            skillDefinition.SetRange(4, std::stof(vss.at(i).at(18)));
            skillDefinition.SetRange(5, std::stof(vss.at(i).at(19)));
            skillDefinition.SetRange(6, std::stof(vss.at(i).at(20)));
            skillDefinition.SetRange(7, std::stof(vss.at(i).at(21)));
            skillDefinition.SetRange(8, std::stof(vss.at(i).at(22)));
            skillDefinition.SetRange(9, std::stof(vss.at(i).at(23)));
            skillDefinition.SetRange(10, std::stof(vss.at(i).at(24)));
            m_skillLevelMap[skillDefinition.GetName()] = skillDefinition;
        }
    }
    {
        std::vector<std::vector<std::string> > vss;
        vss = csv::Read(csvfilePlayer);
        int work = 0;

        work = std::stoi(vss.at(0).at(1));
        m_playerSkillLevelMap[vss.at(0).at(0)] = work;

        work = std::stoi(vss.at(1).at(1));
        m_playerSkillLevelMap[vss.at(1).at(0)] = work;

        work = std::stoi(vss.at(2).at(1));
        m_playerSkillLevelMap[vss.at(2).at(0)] = work;
    }
}

void SkillManager::Save(const std::string& csvfile)
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

    csv::Write(csvfile, vss);
}

void SkillManager::SetSkillLevel(const std::string& skillName, const int skillLevel)
{
    m_playerSkillLevelMap[skillName] = skillLevel;
}

int SkillManager::GetSkillLevel(const std::string& skillName)
{
    return m_playerSkillLevelMap[skillName];
}
