#include "EnemyManager.h"
#include "HeaderOnlyCsv.hpp"

using namespace NSStarmanLib;

EnemyManager* EnemyManager::obj { nullptr };

EnemyManager* EnemyManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new EnemyManager();
    }
    return obj;
}

void EnemyManager::Destroy()
{
    delete EnemyManager::obj;
    EnemyManager::obj = nullptr;
}

void EnemyManager::Init(const std::string& csvEnemyDef,
                        const std::string& csvEnemyInfo)
{
    {
        std::vector<std::vector<std::string> > vss;
        vss = csv::Read(csvEnemyDef);
        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            int work_i = 0;
            float work_f = 0.f;

            EnemyDef enemyDef;

            work_i = std::stoi(vss.at(i).at(0));
            enemyDef.SetIDDef(work_i);

            enemyDef.SetName(vss.at(i).at(1));

            enemyDef.SetDetail(vss.at(i).at(2));

            enemyDef.SetImagePath(vss.at(i).at(3));

            m_enemyDefMap[(int)i] = enemyDef;
        }
    }

    {
        std::vector<std::vector<std::string> > vss;
        vss = csv::Read(csvEnemyInfo);
        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            int work_i = 0;
            float work_f = 0.f;

            EnemyInfo enemyInfo;

            work_i = std::stoi(vss.at(i).at(0));
            enemyInfo.SetID(work_i);

            enemyInfo.SetBreed(vss.at(i).at(1));

            std::string work_str = enemyInfo.GetBreed();
            for (auto it = m_enemyDefMap.begin(); it != m_enemyDefMap.end(); ++it)
            {
                if (it->second.GetName() == work_str)
                {
                    work_i = it->second.GetIDDef();
                    enemyInfo.SetIDDef(work_i);
                    break;
                }
            }

            work_f = std::stof(vss.at(i).at(2));
            enemyInfo.SetX(work_f);

            work_f = std::stof(vss.at(i).at(3));
            enemyInfo.SetY(work_f);

            work_f = std::stof(vss.at(i).at(4));
            enemyInfo.SetZ(work_f);

            work_f = std::stof(vss.at(i).at(5));
            enemyInfo.SetRotX(work_f);

            work_f = std::stof(vss.at(i).at(6));
            enemyInfo.SetRotY(work_f);

            work_f = std::stof(vss.at(i).at(7));
            enemyInfo.SetRotZ(work_f);

            work_i = std::stoi(vss.at(i).at(8));
            enemyInfo.SetHP(work_i);

            if (vss.at(i).at(9) == "○")
            {
                enemyInfo.SetDefeated(true);
            }
            else
            {
                enemyInfo.SetDefeated(false);
            }
            m_enemyInfoMap[(int)i] = enemyInfo;
        }
    }
}

void EnemyManager::Save(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;
    vs.push_back("ID");
    vs.push_back("タイプ");
    vs.push_back("PosX");
    vs.push_back("PosY");
    vs.push_back("PosZ");
    vs.push_back("RotX");
    vs.push_back("RotY");
    vs.push_back("RotZ");
    vs.push_back("残りHP");
    vs.push_back("討伐済み");
    vss.push_back(vs);
    vs.clear();
    for (auto it = m_enemyInfoMap.begin(); it != m_enemyInfoMap.end(); ++it)
    {
        vs.push_back(std::to_string(it->first));
        vs.push_back(it->second.GetBreed());
        vs.push_back(std::to_string(it->second.GetX()));
        vs.push_back(std::to_string(it->second.GetY()));
        vs.push_back(std::to_string(it->second.GetZ()));
        vs.push_back(std::to_string(it->second.GetRotX()));
        vs.push_back(std::to_string(it->second.GetRotY()));
        vs.push_back(std::to_string(it->second.GetRotZ()));
        vs.push_back(std::to_string(it->second.GetHP()));
        if (it->second.GetDefeated())
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

std::vector<EnemyInfo> EnemyManager::GetEnemyInfo(const float x,
                                                  const float y,
                                                  const float z,
                                                  const float r)
{
    std::vector<EnemyInfo> enemyInfoList;
    for (auto it = m_enemyInfoMap.begin(); it != m_enemyInfoMap.end(); ++it)
    {
        float dx = it->second.GetX() - x;
        float dy = it->second.GetY() - y;
        float dz = it->second.GetZ() - z;

        float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
        if (distance <= r)
        {
            enemyInfoList.push_back(it->second);
        }
    }
    return enemyInfoList;
}

void EnemyManager::UpdateEnemyInfo(const int id, const EnemyInfo& enemyInfo)
{
    m_enemyInfoMap[id] = enemyInfo;
}

void EnemyInfo::SetID(const int arg)
{
    m_id = arg;
}

int EnemyInfo::GetID()
{
    return m_id;
}

void NSStarmanLib::EnemyInfo::SetIDDef(const int arg)
{
    m_idDef = arg;
}

int NSStarmanLib::EnemyInfo::GetIDDef()
{
    return m_idDef;
}

void EnemyInfo::SetBreed(const std::string& breed)
{
    m_breed = breed;
}

std::string EnemyInfo::GetBreed()
{
    return m_breed;
}

void EnemyInfo::SetX(const float arg)
{
    m_x = arg;
}

float EnemyInfo::GetX()
{
    return m_x;
}

void EnemyInfo::SetY(const float arg)
{
    m_y = arg;
}

float EnemyInfo::GetY()
{
    return m_y;
}

void EnemyInfo::SetZ(const float arg)
{
    m_z = arg;
}

float EnemyInfo::GetZ()
{
    return m_z;
}

void EnemyInfo::SetRotX(const float arg)
{
    m_rotX = arg;
}

float EnemyInfo::GetRotX()
{
    return m_rotX;
}

void EnemyInfo::SetRotY(const float arg)
{
    m_rotY = arg;
}

float EnemyInfo::GetRotY()
{
    return m_rotY;
}

void EnemyInfo::SetRotZ(const float arg)
{
    m_rotZ = arg;
}

float EnemyInfo::GetRotZ()
{
    return m_rotZ;
}

void EnemyInfo::SetHP(const int arg)
{
    m_HP = arg;
}

int EnemyInfo::GetHP()
{
    return m_HP;
}

void EnemyInfo::SetDefeated(const bool arg)
{
    m_bDefeated = arg;
}

bool EnemyInfo::GetDefeated()
{
    return m_bDefeated;
}

void NSStarmanLib::EnemyDef::SetIDDef(const int arg)
{
    m_idDef = arg;
}

int NSStarmanLib::EnemyDef::GetIDDef()
{
    return m_idDef;
}

void NSStarmanLib::EnemyDef::SetName(const std::string& arg)
{
    m_name = arg;
}

std::string NSStarmanLib::EnemyDef::GetName()
{
    return m_name;
}

void NSStarmanLib::EnemyDef::SetDetail(const std::string& arg)
{
    m_detail = arg;
}

std::string NSStarmanLib::EnemyDef::GetDetail()
{
    return m_detail;
}

void NSStarmanLib::EnemyDef::SetImagePath(const std::string& arg)
{
    m_imagePath = arg;
}

std::string NSStarmanLib::EnemyDef::GetImagePath()
{
    return m_imagePath;
}
