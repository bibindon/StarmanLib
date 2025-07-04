#include "EnemyInfoManager.h"
#include <algorithm>
#include "Util.h"

using namespace NSStarmanLib;

EnemyInfoManager* EnemyInfoManager::obj { nullptr };

EnemyInfoManager* EnemyInfoManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new EnemyInfoManager();
    }
    return obj;
}

void EnemyInfoManager::Destroy()
{
    delete EnemyInfoManager::obj;
    EnemyInfoManager::obj = nullptr;
}

void EnemyInfoManager::Init(const std::wstring& csvEnemyDef,
                            const std::wstring& csvEnemyInfo,
                            const std::wstring& csvEnemyVisible,
                            const bool decrypt)
{
    {
        std::vector<std::vector<std::wstring>> vvs = Util::ReadFromCsv(csvEnemyDef, decrypt);

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            std::wstring id = vvs.at(i).at(0);
            float work_f = 0.f;

            EnemyDef enemyDef;

            enemyDef.SetID(id);

            enemyDef.SetName(vvs.at(i).at(1));

            enemyDef.SetDetail(vvs.at(i).at(2));

            enemyDef.SetImagePath(vvs.at(i).at(3));

            m_enemyDefMap[id] = enemyDef;
        }
    }

    {
        std::vector<std::vector<std::wstring>> vvs = Util::ReadFromCsv(csvEnemyInfo, decrypt);

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            int serialNumber = 0;
            float work_f = 0.f;

            EnemyInfo enemyInfo;

            serialNumber = std::stoi(vvs.at(i).at(0));
            enemyInfo.SetSerialNumber(serialNumber);

            std::wstring id = vvs.at(i).at(1);
            enemyInfo.SetID(id);

            enemyInfo.SetName(m_enemyDefMap.at(id).GetName());

            work_f = std::stof(vvs.at(i).at(2));
            enemyInfo.SetX(work_f);

            work_f = std::stof(vvs.at(i).at(3));
            enemyInfo.SetY(work_f);

            work_f = std::stof(vvs.at(i).at(4));
            enemyInfo.SetZ(work_f);

            work_f = std::stof(vvs.at(i).at(5));
            enemyInfo.SetRotX(work_f);

            work_f = std::stof(vvs.at(i).at(6));
            enemyInfo.SetRotY(work_f);

            work_f = std::stof(vvs.at(i).at(7));
            enemyInfo.SetRotZ(work_f);

            int hp = std::stoi(vvs.at(i).at(8));
            enemyInfo.SetHP(hp);

            if (vvs.at(i).at(9) == _T("y"))
            {
                enemyInfo.SetDefeated(true);
            }
            else
            {
                enemyInfo.SetDefeated(false);
            }
            m_enemyInfoMap[serialNumber] = enemyInfo;
        }
    }
    {
        std::vector<std::vector<std::wstring>> vvs = Util::ReadFromCsv(csvEnemyVisible, decrypt);

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            std::wstring work_str;
            work_str = vvs.at(i).at(0);
            if (m_enemyDefMap.find(work_str) == m_enemyDefMap.end())
            {
                throw std::exception();
            }

            if (vvs.at(i).at(1) == _T("y"))
            {
                m_enemyDefMap[work_str].SetVisible(true);
            }
            else if (vvs.at(i).at(1) == _T(""))
            {
                m_enemyDefMap[work_str].SetVisible(false);
            }
            else
            {
                throw std::exception();
            }
        }
    }
}

void EnemyInfoManager::Save(const std::wstring& csvEnemyInfo,
                            const std::wstring& csvEvemyVisible,
                            const bool encrypt)
{
    {
        std::vector<std::vector<std::wstring>> vvs;
        std::vector<std::wstring> vs;
        vs.push_back(_T("SerialNumber"));
        vs.push_back(_T("Name"));
        vs.push_back(_T("PosX"));
        vs.push_back(_T("PosY"));
        vs.push_back(_T("PosZ"));
        vs.push_back(_T("RotX"));
        vs.push_back(_T("RotY"));
        vs.push_back(_T("RotZ"));
        vs.push_back(_T("残りHP"));
        vs.push_back(_T("討伐済み"));
        vvs.push_back(vs);
        vs.clear();
        for (auto it = m_enemyInfoMap.begin(); it != m_enemyInfoMap.end(); ++it)
        {
            vs.push_back(std::to_wstring(it->second.GetSerialNumber()));
            vs.push_back(it->second.GetID());
            vs.push_back(std::to_wstring(it->second.GetX()));
            vs.push_back(std::to_wstring(it->second.GetY()));
            vs.push_back(std::to_wstring(it->second.GetZ()));
            vs.push_back(std::to_wstring(it->second.GetRotX()));
            vs.push_back(std::to_wstring(it->second.GetRotY()));
            vs.push_back(std::to_wstring(it->second.GetRotZ()));
            vs.push_back(std::to_wstring(it->second.GetHP()));
            if (it->second.GetDefeated())
            {
                vs.push_back(_T("y"));
            }
            else
            {
                vs.push_back(_T(""));
            }
            vvs.push_back(vs);
            vs.clear();
        }

        Util::WriteToCsv(csvEnemyInfo, vvs, encrypt);
    }
    {
        std::vector<std::vector<std::wstring>> vvs;
        std::vector<std::wstring> vs;
        vs.push_back(_T("ID"));
        vs.push_back(_T("表示・非表示"));
        vvs.push_back(vs);
        vs.clear();

        for (auto it = m_enemyDefMap.begin(); it != m_enemyDefMap.end(); ++it)
        {
            vs.push_back(it->first);

            if (it->second.GetVisible())
            {
                vs.push_back(_T("y"));
            }
            else
            {
                vs.push_back(_T(""));
            }
            vvs.push_back(vs);
            vs.clear();
        }

        Util::WriteToCsv(csvEvemyVisible, vvs, encrypt);
    }
}

std::vector<EnemyInfo> EnemyInfoManager::GetEnemyInfo(const float x,
                                                  const float y,
                                                  const float z,
                                                  const float r)
{
    // 球で判定すると重いので立方体で判定する
    std::vector<EnemyInfo> enemyInfoList;
    for (auto it = m_enemyInfoMap.begin(); it != m_enemyInfoMap.end(); ++it)
    {
        float dx = it->second.GetX() - x;
        if (-r <= dx && dx <= r)
        {
            float dz = it->second.GetZ() - z;
            if (-r <= dz && dz <= r)
            {
                enemyInfoList.push_back(it->second);
            }
        }
    }
    return enemyInfoList;
}

void EnemyInfoManager::UpdateEnemyInfo(const int serialNumber, const EnemyInfo& enemyInfo)
{
    m_enemyInfoMap[serialNumber] = enemyInfo;
}

std::vector<std::wstring> NSStarmanLib::EnemyInfoManager::GetEnemyIdList()
{
    std::vector<std::wstring> idList;
    for (auto it = m_enemyDefMap.begin(); it != m_enemyDefMap.end(); ++it)
    {
        idList.push_back(it->second.GetID());
    }

    // IDを辞書順にソート
    std::sort(idList.begin(), idList.end(),
              [&](const std::wstring& x1, const std::wstring& x2)
              {
                  return x1 < x2;
              });

    return idList;
}

EnemyDef NSStarmanLib::EnemyInfoManager::GetEnemyDef(const std::wstring& id)
{
    EnemyDef enemyDef;
    for (auto it = m_enemyDefMap.begin(); it != m_enemyDefMap.end(); ++it)
    {
        if (it->second.GetID() == id)
        {
            enemyDef = it->second;
            break;
        }
    }
    return enemyDef;
}

void NSStarmanLib::EnemyInfoManager::SetEnemyVisible(const std::wstring& id, const bool visible)
{
    for (auto it = m_enemyDefMap.begin(); it != m_enemyDefMap.end(); ++it)
    {
        if (it->second.GetID() == id)
        {
            it->second.SetVisible(visible);
            break;
        }
    }
}

EnemyInfo NSStarmanLib::EnemyInfoManager::GetEnemyInfo(const int serialNumber)
{
    return m_enemyInfoMap.at(serialNumber);
}

void NSStarmanLib::EnemyInfoManager::SetDefeat(const int serialNumber)
{
    m_enemyInfoMap.at(serialNumber).SetDefeated(true);
}

void EnemyInfo::SetSerialNumber(const int arg)
{
    m_SerialNumber = arg;
}

int EnemyInfo::GetSerialNumber() const
{
    return m_SerialNumber;
}

void NSStarmanLib::EnemyInfo::SetID(const std::wstring& arg)
{
    m_idDef = arg;
}

std::wstring NSStarmanLib::EnemyInfo::GetID() const
{
    return m_idDef;
}

void EnemyInfo::SetName(const std::wstring& name)
{
    m_name = name;
}

std::wstring EnemyInfo::GetName() const
{
    return m_name;
}

void EnemyInfo::SetX(const float arg)
{
    m_x = arg;
}

void EnemyInfo::SetY(const float arg)
{
    m_y = arg;
}

void EnemyInfo::SetZ(const float arg)
{
    m_z = arg;
}

void EnemyInfo::SetRotX(const float arg)
{
    m_rotX = arg;
}

float EnemyInfo::GetRotX() const
{
    return m_rotX;
}

void EnemyInfo::SetRotY(const float arg)
{
    m_rotY = arg;
}

float EnemyInfo::GetRotY() const
{
    return m_rotY;
}

void EnemyInfo::SetRotZ(const float arg)
{
    m_rotZ = arg;
}

float EnemyInfo::GetRotZ() const
{
    return m_rotZ;
}

void EnemyInfo::SetHP(const int arg)
{
    m_HP = arg;
}

int EnemyInfo::GetHP() const
{
    return m_HP;
}

void EnemyInfo::SetDefeated(const bool arg)
{
    m_bDefeated = arg;
}

bool EnemyInfo::GetDefeated() const
{
    return m_bDefeated;
}

void NSStarmanLib::EnemyDef::SetID(const std::wstring& arg)
{
    m_id = arg;
}

std::wstring NSStarmanLib::EnemyDef::GetID() const
{
    return m_id;
}

void NSStarmanLib::EnemyDef::SetName(const std::wstring& arg)
{
    m_name = arg;
}

std::wstring NSStarmanLib::EnemyDef::GetName() const
{
    return m_name;
}

void NSStarmanLib::EnemyDef::SetDetail(const std::wstring& arg)
{
    m_detail = arg;
    m_detail.erase(std::remove(m_detail.begin(), m_detail.end(), '"'), m_detail.end());
}

std::wstring NSStarmanLib::EnemyDef::GetDetail() const
{
    return m_detail;
}

void NSStarmanLib::EnemyDef::SetImagePath(const std::wstring& arg)
{
    m_imagePath = arg;
}

std::wstring NSStarmanLib::EnemyDef::GetImagePath()
{
    return m_imagePath;
}

void NSStarmanLib::EnemyDef::SetVisible(const bool arg)
{
    m_visible = arg;
}

bool NSStarmanLib::EnemyDef::GetVisible() const
{
    return m_visible;
}
