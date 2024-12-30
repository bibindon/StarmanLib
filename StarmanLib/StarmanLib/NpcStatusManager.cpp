#include "NpcStatusManager.h"
#include "Util.h"

using namespace NSStarmanLib;

NpcStatusManager* NpcStatusManager::obj { nullptr };

void NpcStatus::SetName(const std::string& arg)
{
    m_name = arg;
}

std::string NpcStatus::GetName()
{
    return m_name;
}

void NpcStatus::SetCarbo(const float arg)
{
    m_carbo = arg;
}

float NpcStatus::GetCarbo()
{
    return m_carbo;
}

void NpcStatus::SetProtein(const float arg)
{
    m_protein = arg;
}

float NpcStatus::GetProtein()
{
    return m_protein;
}

void NpcStatus::SetLipid(const float arg)
{
    m_lipid = arg;
}

float NpcStatus::GetLipid()
{
    return m_lipid;
}

void NpcStatus::SetVitamin(const float arg)
{
    m_vitamin = arg;
}

float NpcStatus::GetVitamin()
{
    return m_vitamin;
}

void NpcStatus::SetMineral(const float arg)
{
    m_mineral = arg;
}

float NpcStatus::GetMineral()
{
    return m_mineral;
}

void NpcStatus::SetRynenContract()
{
    m_rynenContract = true;
}

float NpcStatus::GetRynenContract()
{
    return m_rynenContract;
}

void NpcStatus::SetDrinkWordbress(const bool arg)
{
    m_bDrinkWordbress = arg;
}

bool NpcStatus::GetDrinkWordbress()
{
    return m_bDrinkWordbress;
}

void NpcStatus::SetDead()
{
    m_dead = true;
}

bool NpcStatus::GetDead()
{
    return m_dead;
}

void NSStarmanLib::NpcStatus::SetX(const float arg)
{
    m_x = arg;
}

float NSStarmanLib::NpcStatus::GetX() const
{
    return m_x;
}

void NSStarmanLib::NpcStatus::SetY(const float arg)
{
    m_y = arg;
}

float NSStarmanLib::NpcStatus::GetY() const
{
    return m_y;
}

void NSStarmanLib::NpcStatus::SetZ(const float arg)
{
    m_z = arg;
}

float NSStarmanLib::NpcStatus::GetZ() const
{
    return m_z;
}

void NSStarmanLib::NpcStatus::SetRotY(const float arg)
{
    m_rotY = arg;
}

float NSStarmanLib::NpcStatus::GetRotY() const
{
    return m_rotY;
}

void NSStarmanLib::NpcStatus::SetHasTalk(const bool arg)
{
    m_bHasTalk = arg;
}

bool NSStarmanLib::NpcStatus::GetHasTalk() const
{
    return m_bHasTalk;
}

void NSStarmanLib::NpcStatus::SetTalkCsv(const std::string& arg)
{
    m_talkCsv = arg;
}

std::string NSStarmanLib::NpcStatus::GetTalkCsv() const
{
    return m_talkCsv;
}

void NSStarmanLib::NpcStatus::SetFeatureEnable(const bool arg)
{
    m_bFeatureEnable = arg;
}

bool NSStarmanLib::NpcStatus::GetFeatureEnable() const
{
    return m_bFeatureEnable;
}

void NSStarmanLib::NpcStatus::SetNpcFeature(const eNpcFeature arg)
{
    m_eNpcFeature = arg;
}

eNpcFeature NSStarmanLib::NpcStatus::GetNpcFeature() const
{
    return m_eNpcFeature;
}

void NSStarmanLib::NpcStatus::SetMenuShow(const bool arg)
{
    m_bMenuShow = arg;
}

bool NSStarmanLib::NpcStatus::GetMenuShow() const
{
    return m_bMenuShow;
}

NpcStatusManager* NpcStatusManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new NpcStatusManager();
    }
    return obj;
}

void NpcStatusManager::Destroy()
{
    delete NpcStatusManager::obj;
    NpcStatusManager::obj = nullptr;
}

void NpcStatusManager::Init(const std::string& csvfile,
                            const bool decrypt)
{
    std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvfile, decrypt);

    for (std::size_t i = 1; i < vvs.size(); ++i)
    {
        float work_f = 0.f;

        NpcStatus npcStatus;

        npcStatus.SetName(vvs.at(i).at(0));

        work_f = std::stof(vvs.at(i).at(1));
        npcStatus.SetCarbo(work_f);

        work_f = std::stof(vvs.at(i).at(2));
        npcStatus.SetProtein(work_f);

        work_f = std::stof(vvs.at(i).at(3));
        npcStatus.SetLipid(work_f);

        work_f = std::stof(vvs.at(i).at(4));
        npcStatus.SetVitamin(work_f);

        work_f = std::stof(vvs.at(i).at(5));
        npcStatus.SetMineral(work_f);

        if (vvs.at(i).at(6) == "○")
        {
            npcStatus.SetRynenContract();
        }

        if (vvs.at(i).at(7) == "○")
        {
            npcStatus.SetDrinkWordbress(true);
        }
        else
        {
            npcStatus.SetDrinkWordbress(false);
        }

        if (vvs.at(i).at(8) == "○")
        {
            npcStatus.SetDead();
        }

        work_f = std::stof(vvs.at(i).at(9));
        npcStatus.SetX(work_f);

        work_f = std::stof(vvs.at(i).at(10));
        npcStatus.SetY(work_f);

        work_f = std::stof(vvs.at(i).at(11));
        npcStatus.SetZ(work_f);

        work_f = std::stof(vvs.at(i).at(12));
        npcStatus.SetRotY(work_f);

        if (vvs.at(i).at(13) == "○")
        {
            npcStatus.SetHasTalk(true);
        }
        else
        {
            npcStatus.SetHasTalk(false);
        }

        npcStatus.SetTalkCsv(vvs.at(i).at(14));

        if (vvs.at(i).at(15) == "○")
        {
            npcStatus.SetFeatureEnable(true);
        }
        else
        {
            npcStatus.SetFeatureEnable(false);
        }

        if (vvs.at(i).at(16) == "クラフト")
        {
            npcStatus.SetNpcFeature(eNpcFeature::CRAFTMAN);
        }
        else if (vvs.at(i).at(16) == "倉庫")
        {
            npcStatus.SetNpcFeature(eNpcFeature::STOREHOUSE);
        }
        else
        {
            npcStatus.SetNpcFeature(eNpcFeature::NONE);
        }

        if (vvs.at(i).at(17) == "○")
        {
            npcStatus.SetMenuShow(true);
        }
        else
        {
            npcStatus.SetMenuShow(false);
        }

        m_NpcStatusMap[npcStatus.GetName()] = npcStatus;
    }
}

void NpcStatusManager::Save(const std::string& csvfile,
                            const bool encrypt)
{
    std::vector<std::vector<std::string> > vvs;
    std::vector<std::string> vs;
    std::string work;

    vs.push_back("名前");
    vs.push_back("糖質");
    vs.push_back("タンパク質");
    vs.push_back("脂質");
    vs.push_back("ビタミン");
    vs.push_back("ミネラル");
    vs.push_back("ライネンの契約をしている");
    vs.push_back("ワードブレスを飲んでいる");
    vs.push_back("死んでいる");
    vs.push_back("x");
    vs.push_back("y");
    vs.push_back("z");
    vs.push_back("yRot");
    vs.push_back("会話可能");
    vs.push_back("会話スクリプト");
    vs.push_back("機能解禁");
    vs.push_back("機能種別");
    vs.push_back("メニュー表示");
    vvs.push_back(vs);
    vs.clear();

    for (auto it = m_NpcStatusMap.begin(); it != m_NpcStatusMap.end(); ++it)
    {
        std::string work;
        vs.push_back(it->first);

        work = std::to_string(it->second.GetCarbo());
        vs.push_back(work);

        work = std::to_string(it->second.GetProtein());
        vs.push_back(work);

        work = std::to_string(it->second.GetLipid());
        vs.push_back(work);

        work = std::to_string(it->second.GetVitamin());
        vs.push_back(work);

        work = std::to_string(it->second.GetMineral());
        vs.push_back(work);

        if (it->second.GetRynenContract())
        {
            vs.push_back("○");
        }
        else
        {
            vs.push_back("");
        }

        if (it->second.GetDrinkWordbress())
        {
            vs.push_back("○");
        }
        else
        {
            vs.push_back("");
        }

        if (it->second.GetDead())
        {
            vs.push_back("○");
        }
        else
        {
            vs.push_back("");
        }

        work = std::to_string(it->second.GetX());
        vs.push_back(work);

        work = std::to_string(it->second.GetY());
        vs.push_back(work);

        work = std::to_string(it->second.GetZ());
        vs.push_back(work);

        work = std::to_string(it->second.GetRotY());
        vs.push_back(work);

        if (it->second.GetHasTalk())
        {
            vs.push_back("○");
        }
        else
        {
            vs.push_back("");
        }

        vs.push_back(it->second.GetTalkCsv());

        if (it->second.GetFeatureEnable())
        {
            vs.push_back("○");
        }
        else
        {
            vs.push_back("");
        }

        if (it->second.GetNpcFeature() == eNpcFeature::CRAFTMAN)
        {
            vs.push_back("クラフト");
        }
        else if (it->second.GetNpcFeature() == eNpcFeature::STOREHOUSE)
        {
            vs.push_back("倉庫");
        }
        else
        {
            vs.push_back("");
        }

        if (it->second.GetMenuShow())
        {
            vs.push_back("○");
        }
        else
        {
            vs.push_back("");
        }

        vvs.push_back(vs);
        vs.clear();
    }

    Util::WriteToCsv(csvfile, vvs, encrypt);
}

NpcStatus NpcStatusManager::GetNpcStatus(const std::string& name)
{
    return m_NpcStatusMap.at(name);
}

void NpcStatusManager::SetNpcStatus(const std::string& key, const NpcStatus& value)
{
    m_NpcStatusMap[key] = value;
}
