#include "StatusManager.h"
#include "HeaderOnlyCsv.hpp"

float Status::GetBodyStaminaCurrent() const
{
    return m_bodyStaminaCurrent;
}

void Status::SetBodyStaminaCurrent(float mbodyStaminaCurrent)
{
    m_bodyStaminaCurrent = mbodyStaminaCurrent;
}

float Status::GetBodyStaminaMax() const
{
    return m_bodyStaminaMax;
}

void Status::SetBodyStaminaMax(float mbodyStaminaMax)
{
    m_bodyStaminaMax = mbodyStaminaMax;
}

float Status::GetBodyStaminaMaxSub() const
{
    return m_bodyStaminaMaxSub;
}

void Status::SetBodyStaminaMaxSub(float mbodyStaminaMaxSub)
{
    m_bodyStaminaMaxSub = mbodyStaminaMaxSub;
}

float Status::GetBrainStaminaCurrent() const
{
    return m_brainStaminaCurrent;
}

void Status::SetBrainStaminaCurrent(float mbrainStaminaCurrent)
{
    m_brainStaminaCurrent = mbrainStaminaCurrent;
}

float Status::GetBrainStaminaMax() const
{
    return m_brainStaminaMax;
}

void Status::SetBrainStaminaMax(float mbrainStaminaMax)
{
    m_brainStaminaMax = mbrainStaminaMax;
}

float Status::GetBrainStaminaMaxSub() const
{
    return m_brainStaminaMaxSub;
}

void Status::SetBrainStaminaMaxSub(float mbrainStaminaMaxSub)
{
    m_brainStaminaMaxSub = mbrainStaminaMaxSub;
}

float Status::GetExplosivePower() const
{
    return m_explosivePower;
}

void Status::SetExplosivePower(float mexplosivePower)
{
    m_explosivePower = mexplosivePower;
}

float Status::GetMuscleCurrent() const
{
    return m_muscleCurrent;
}

void Status::SetMuscleCurrent(float mmuscleCurrent)
{
    m_muscleCurrent = mmuscleCurrent;
}

float Status::GetMuscleMax() const
{
    return m_muscleMax;
}

void Status::SetMuscleMax(float mmuscleMax)
{
    m_muscleMax = mmuscleMax;
}

float Status::GetCarboCurrent() const
{
    return m_carboCurrent;
}

void Status::SetCarboCurrent(float mcarbo)
{
    m_carboCurrent = mcarbo;
}

float Status::GetCarboMax() const
{
    return m_carboMax;
}

void Status::SetCarboMax(float mcarbo)
{
    m_carboMax = mcarbo;
}

float Status::GetProteinCurrent() const
{
    return m_proteinCurrent;
}

void Status::SetProteinCurrent(float mprotein)
{
    m_proteinCurrent = mprotein;
}

float Status::GetProteinMax() const
{
    return m_proteinMax;
}

void Status::SetProteinMax(float mprotein)
{
    m_proteinMax = mprotein;
}

float Status::GetLipidCurrent() const
{
    return m_lipidCurrent;
}

void Status::SetLipidCurrent(float mlipid)
{
    m_lipidCurrent = mlipid;
}

float Status::GetLipidMax() const
{
    return m_lipidMax;
}

void Status::SetLipidMax(float mlipid)
{
    m_lipidMax = mlipid;
}

float Status::GetVitaminCurrent() const
{
    return m_vitaminCurrent;
}

void Status::SetVitaminCurrent(float mvitamin)
{
    m_vitaminCurrent = mvitamin;
}

float Status::GetVitaminMax() const
{
    return m_vitaminMax;
}

void Status::SetVitaminMax(float mvitamin)
{
    m_vitaminMax = mvitamin;
}

float Status::GetMineralCurrent() const
{
    return m_mineralCurrent;
}

void Status::SetMineralCurrent(float mmineral)
{
    m_mineralCurrent = mmineral;
}

float Status::GetMineralMax() const
{
    return m_mineralMax;
}

void Status::SetMineralMax(float mmineral)
{
    m_mineralMax = mmineral;
}

float Status::GetWaterCurrent() const
{
    return m_waterCurrent;
}

void Status::SetWaterCurrent(float mwater)
{
    m_waterCurrent = mwater;
}

float Status::GetWaterMax() const
{
    return m_waterMax;
}

void Status::SetWaterMax(float mwater)
{
    m_waterMax = mwater;
}

bool Status::GetFractureArm() const
{
    return m_fractureArm;
}

void Status::SetFractureArm(bool mfractureArm)
{
    m_fractureArm = mfractureArm;
}

bool Status::GetFractureLeg() const
{
    return m_fractureLeg;
}

void Status::SetFractureLeg(bool mfractureLeg)
{
    m_fractureLeg = mfractureLeg;
}

bool Status::GetHeadache() const
{
    return m_headache;
}

void Status::SetHeadache(bool mheadache)
{
    m_headache = mheadache;
}

bool Status::GetCold() const
{
    return m_cold;
}

void Status::SetCold(bool mcold)
{
    m_cold = mcold;
}

bool Status::GetStomachache() const
{
    return m_stomachache;
}

void Status::SetStomachache(bool mstomachache)
{
    m_stomachache = mstomachache;
}

bool Status::GetSleep() const
{
    return m_sleep;
}

void Status::SetSleep(bool msleep)
{
    m_sleep = msleep;
}

bool Status::GetDehydration() const
{
    return m_dehydration;
}

void Status::SetDehydration(bool mdehydration)
{
    m_dehydration = mdehydration;
}

bool Status::GetLackOfSleep() const
{
    return m_lackOfSleep;
}

void Status::SetLackOfSleep(bool mlackOfSleep)
{
    m_lackOfSleep = mlackOfSleep;
}

StatusManager* StatusManager::obj { nullptr };

StatusManager* StatusManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new StatusManager();
    }
    return obj;
}

void StatusManager::Destroy()
{
    delete StatusManager::obj;
    StatusManager::obj = nullptr;
}

void StatusManager::Init(const std::string& csvfile)
{
    std::vector<std::vector<std::string> > vss = csv::Read(csvfile);
    for (std::size_t i = 1; i < vss.size(); ++i)
    {
        if (vss.at(i).at(1) == "体のスタミナ（現在値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetBodyStaminaCurrent(value);
        }
        else if (vss.at(i).at(1) == "体のスタミナ（最大値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetBodyStaminaMax(value);
        }
        else if (vss.at(i).at(1) == "体のスタミナ（回復可能値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetBodyStaminaMaxSub(value);
        }
        else if (vss.at(i).at(1) == "脳のスタミナ（現在値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetBrainStaminaCurrent(value);
        }
        else if (vss.at(i).at(1) == "脳のスタミナ（最大値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetBrainStaminaMax(value);
        }
        else if (vss.at(i).at(1) == "脳のスタミナ（回復可能値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetBrainStaminaMaxSub(value);
        }
        else if (vss.at(i).at(1) == "瞬発力")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetExplosivePower(value);
        }
        else if (vss.at(i).at(1) == "肉体の修復度（現在値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetMuscleCurrent(value);
        }
        else if (vss.at(i).at(1) == "肉体の修復度（最大値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetMuscleMax(value);
        }
        else if (vss.at(i).at(1) == "糖質（現在値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetCarboCurrent(value);
        }
        else if (vss.at(i).at(1) == "糖質（最大値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetCarboMax(value);
        }
        else if (vss.at(i).at(1) == "タンパク質（現在値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetProteinCurrent(value);
        }
        else if (vss.at(i).at(1) == "タンパク質（最大値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetProteinMax(value);
        }
        else if (vss.at(i).at(1) == "脂質（現在値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetLipidCurrent(value);
        }
        else if (vss.at(i).at(1) == "脂質（最大値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetLipidMax(value);
        }
        else if (vss.at(i).at(1) == "ビタミン（現在値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetVitaminCurrent(value);
        }
        else if (vss.at(i).at(1) == "ビタミン（最大値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetVitaminMax(value);
        }
        else if (vss.at(i).at(1) == "ミネラル（現在値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetMineralCurrent(value);
        }
        else if (vss.at(i).at(1) == "ミネラル（最大値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetMineralMax(value);
        }
        else if (vss.at(i).at(1) == "水分（現在値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetWaterCurrent(value);
        }
        else if (vss.at(i).at(1) == "水分（最大値）")
        {
            float value = std::stof(vss.at(i).at(2));
            m_status.SetWaterMax(value);
        }
        else if (vss.at(i).at(1) == "腕骨折")
        {
            if (vss.at(i).at(2) == "〇")
            {
                m_status.SetFractureArm(true);
            }
            else
            {
                m_status.SetFractureArm(false);
            }
        }
        else if (vss.at(i).at(1) == "足骨折")
        {
            if (vss.at(i).at(2) == "〇")
            {
                m_status.SetFractureLeg(true);
            }
            else
            {
                m_status.SetFractureLeg(false);
            }
        }
        else if (vss.at(i).at(1) == "頭痛")
        {
            if (vss.at(i).at(2) == "〇")
            {
                m_status.SetHeadache(true);
            }
            else
            {
                m_status.SetHeadache(false);
            }
        }
        else if (vss.at(i).at(1) == "風邪")
        {
            if (vss.at(i).at(2) == "〇")
            {
                m_status.SetCold(true);
            }
            else
            {
                m_status.SetCold(false);
            }
        }
        else if (vss.at(i).at(1) == "腹痛")
        {
            if (vss.at(i).at(2) == "〇")
            {
                m_status.SetStomachache(true);
            }
            else
            {
                m_status.SetStomachache(false);
            }
        }
        else if (vss.at(i).at(1) == "睡眠")
        {
            if (vss.at(i).at(2) == "〇")
            {
                m_status.SetSleep(true);
            }
            else
            {
                m_status.SetSleep(false);
            }
        }
        else if (vss.at(i).at(1) == "脱水症状")
        {
            if (vss.at(i).at(2) == "〇")
            {
                m_status.SetDehydration(true);
            }
            else
            {
                m_status.SetDehydration(false);
            }
        }
        else if (vss.at(i).at(1) == "睡眠不足")
        {
            if (vss.at(i).at(2) == "〇")
            {
                m_status.SetLackOfSleep(true);
            }
            else
            {
                m_status.SetLackOfSleep(false);
            }
        }
    }
}

void StatusManager::Update()
{
    float bodyStaminaCurrent = m_status.GetBodyStaminaCurrent();
    float bodyStaminaMaxSub = m_status.GetBodyStaminaMaxSub();

    // TODO 回復量が徐々に低下するようにしたりしたい
    if (m_playerAction == PlayerAction::STAND)
    {
        bodyStaminaCurrent -= 0.0001f;
        bodyStaminaMaxSub -= 0.00002f;
    }
    else if (m_playerAction == PlayerAction::WALK)
    {
        bodyStaminaCurrent -= 0.0001f;
        bodyStaminaMaxSub -= 0.00002f;
    }
    else if (m_playerAction == PlayerAction::SIT)
    {
        bodyStaminaCurrent += 0.001f;
        bodyStaminaMaxSub -= 0.00002f;
    }
    else if (m_playerAction == PlayerAction::LYING_DOWN)
    {
        bodyStaminaCurrent += 0.002f;
        bodyStaminaMaxSub += 0.00002f;
    }

    m_status.SetBodyStaminaCurrent(bodyStaminaCurrent);
    m_status.SetBodyStaminaMaxSub(bodyStaminaMaxSub);
}

void StatusManager::Save(const std::string& csvfile)
{
    std::vector<std::vector<std::string> > vss;
    std::vector<std::string> vs;
    std::string work;

    vs.clear();
    vs.push_back("ID");
    vs.push_back("ステータス名");
    vs.push_back("値");
    vss.push_back(vs);

    vs.clear();
    vs.push_back("1");
    vs.push_back("体のスタミナ（現在値）");
    work = std::to_string(m_status.GetBodyStaminaCurrent());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("2");
    vs.push_back("体のスタミナ（最大値）");
    work = std::to_string(m_status.GetBodyStaminaMax());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("3");
    vs.push_back("体のスタミナ（回復可能値）");
    work = std::to_string(m_status.GetBodyStaminaMaxSub());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("4");
    vs.push_back("脳のスタミナ（現在値）");
    work = std::to_string(m_status.GetBrainStaminaCurrent());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("5");
    vs.push_back("脳のスタミナ（最大値）");
    work = std::to_string(m_status.GetBrainStaminaMax());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("6");
    vs.push_back("脳のスタミナ（回復可能値）");
    work = std::to_string(m_status.GetBrainStaminaMaxSub());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("7");
    vs.push_back("瞬発力");
    work = std::to_string(m_status.GetExplosivePower());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("8");
    vs.push_back("肉体の修復度（現在値）");
    work = std::to_string(m_status.GetMuscleCurrent());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("9");
    vs.push_back("肉体の修復度（最大値）");
    work = std::to_string(m_status.GetMuscleMax());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("10");
    vs.push_back("糖質（現在値）");
    work = std::to_string(m_status.GetCarboCurrent());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("11");
    vs.push_back("糖質（最大値）");
    work = std::to_string(m_status.GetCarboMax());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("12");
    vs.push_back("タンパク質（現在値）");
    work = std::to_string(m_status.GetProteinCurrent());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("13");
    vs.push_back("タンパク質（最大値）");
    work = std::to_string(m_status.GetProteinMax());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("14");
    vs.push_back("脂質（現在値）");
    work = std::to_string(m_status.GetLipidCurrent());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("15");
    vs.push_back("脂質（最大値）");
    work = std::to_string(m_status.GetLipidMax());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("16");
    vs.push_back("ビタミン（現在値）");
    work = std::to_string(m_status.GetVitaminCurrent());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("17");
    vs.push_back("ビタミン（最大値）");
    work = std::to_string(m_status.GetVitaminMax());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("18");
    vs.push_back("ミネラル（現在値）");
    work = std::to_string(m_status.GetMineralCurrent());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("19");
    vs.push_back("ミネラル（最大値）");
    work = std::to_string(m_status.GetMineralMax());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("20");
    vs.push_back("水分（現在値）");
    work = std::to_string(m_status.GetWaterCurrent());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("21");
    vs.push_back("水分（最大値）");
    work = std::to_string(m_status.GetWaterMax());
    vs.push_back(work);
    vss.push_back(vs);

    vs.clear();
    vs.push_back("22");
    vs.push_back("腕骨折");
    if (m_status.GetFractureArm())
    {
        vs.push_back("〇");
    }
    else
    {
        vs.push_back("");
    }
    vss.push_back(vs);

    vs.clear();
    vs.push_back("23");
    vs.push_back("足骨折");
    if (m_status.GetFractureLeg())
    {
        vs.push_back("〇");
    }
    else
    {
        vs.push_back("");
    }
    vss.push_back(vs);

    vs.clear();
    vs.push_back("24");
    vs.push_back("頭痛");
    if (m_status.GetHeadache())
    {
        vs.push_back("〇");
    }
    else
    {
        vs.push_back("");
    }
    vss.push_back(vs);

    vs.clear();
    vs.push_back("25");
    vs.push_back("風邪");
    if (m_status.GetCold())
    {
        vs.push_back("〇");
    }
    else
    {
        vs.push_back("");
    }
    vss.push_back(vs);

    vs.clear();
    vs.push_back("26");
    vs.push_back("腹痛");
    if (m_status.GetStomachache())
    {
        vs.push_back("〇");
    }
    else
    {
        vs.push_back("");
    }
    vss.push_back(vs);

    vs.clear();
    vs.push_back("27");
    vs.push_back("睡眠");
    if (m_status.GetSleep())
    {
        vs.push_back("〇");
    }
    else
    {
        vs.push_back("");
    }
    vss.push_back(vs);

    vs.clear();
    vs.push_back("28");
    vs.push_back("脱水症状");
    if (m_status.GetDehydration())
    {
        vs.push_back("〇");
    }
    else
    {
        vs.push_back("");
    }
    vss.push_back(vs);

    vs.clear();
    vs.push_back("29");
    vs.push_back("睡眠不足");
    if (m_status.GetLackOfSleep())
    {
        vs.push_back("〇");
    }
    else
    {
        vs.push_back("");
    }
    vss.push_back(vs);

    csv::Write(csvfile, vss);
}

// TODO
float StatusManager::GetWalkSpeed()
{
    // Inventoryクラスから現在の重量を取得して歩行速度を返す。
    return 1.0f;
}

float StatusManager::GetAttackPower()
{
    // TODO
    return 1.0f;
}

float StatusManager::GetDefensePower()
{
    // TODO
    return 1.0f;
}

float StatusManager::GetBodyStaminaCurrent() const
{
    return m_status.GetBodyStaminaCurrent();
}

void StatusManager::SetBodyStaminaCurrent(float arg)
{
    m_status.SetBodyStaminaCurrent(arg);
}

float StatusManager::GetBodyStaminaMax() const
{
    return m_status.GetBodyStaminaMax();
}

void StatusManager::SetBodyStaminaMax(float arg)
{
    m_status.SetBodyStaminaMax(arg);
}

float StatusManager::GetBodyStaminaMaxSub() const
{
    return m_status.GetBodyStaminaMaxSub();
}

void StatusManager::SetBodyStaminaMaxSub(float arg)
{
    m_status.SetBodyStaminaMaxSub(arg);
}

float StatusManager::GetBrainStaminaCurrent() const
{
    return m_status.GetBrainStaminaCurrent();
}

void StatusManager::SetBrainStaminaCurrent(float arg)
{
    m_status.SetBrainStaminaCurrent(arg);
}

float StatusManager::GetBrainStaminaMax() const
{
    return m_status.GetBrainStaminaMax();
}

void StatusManager::SetBrainStaminaMax(float arg)
{
    m_status.SetBrainStaminaMax(arg);
}

float StatusManager::GetBrainStaminaMaxSub() const
{
    return m_status.GetBrainStaminaMaxSub();
}

void StatusManager::SetBrainStaminaMaxSub(float arg)
{
    m_status.SetBrainStaminaMaxSub(arg);
}

float StatusManager::GetExplosivePower() const
{
    return m_status.GetExplosivePower();
}

void StatusManager::SetExplosivePower(float arg)
{
    m_status.SetExplosivePower(arg);
}

float StatusManager::GetMuscleCurrent() const
{
    return m_status.GetMuscleCurrent();
}

void StatusManager::SetMuscleCurrent(float arg)
{
    m_status.SetMuscleCurrent(arg);
}

float StatusManager::GetMuscleMax() const
{
    return m_status.GetMuscleMax();
}

void StatusManager::SetMuscleMax(float arg)
{
    m_status.SetMuscleMax(arg);
}

float StatusManager::GetCarboCurrent() const
{
    return m_status.GetCarboCurrent();
}

void StatusManager::SetCarboCurrent(float arg)
{
    m_status.SetCarboCurrent(arg);
}

float StatusManager::GetCarboMax() const
{
    return m_status.GetCarboMax();
}

void StatusManager::SetCarboMax(float arg)
{
    m_status.SetCarboMax(arg);
}

float StatusManager::GetProteinCurrent() const
{
    return m_status.GetProteinCurrent();
}

void StatusManager::SetProteinCurrent(float arg)
{
    m_status.SetProteinCurrent(arg);
}

float StatusManager::GetProteinMax() const
{
    return m_status.GetProteinMax();
}

void StatusManager::SetProteinMax(float arg)
{
    m_status.SetProteinMax(arg);
}

float StatusManager::GetLipidCurrent() const
{
    return m_status.GetLipidCurrent();
}

void StatusManager::SetLipidCurrent(float arg)
{
    m_status.SetLipidCurrent(arg);
}

float StatusManager::GetLipidMax() const
{
    return m_status.GetLipidMax();
}

void StatusManager::SetLipidMax(float arg)
{
    m_status.SetLipidMax(arg);
}

float StatusManager::GetVitaminCurrent() const
{
    return m_status.GetVitaminCurrent();
}

void StatusManager::SetVitaminCurrent(float arg)
{
    m_status.SetVitaminCurrent(arg);
}

float StatusManager::GetVitaminMax() const
{
    return m_status.GetVitaminMax();
}

void StatusManager::SetVitaminMax(float arg)
{
    m_status.SetVitaminMax(arg);
}

float StatusManager::GetMineralCurrent() const
{
    return m_status.GetMineralCurrent();
}

void StatusManager::SetMineralCurrent(float arg)
{
    m_status.SetMineralCurrent(arg);
}

float StatusManager::GetMineralMax() const
{
    return m_status.GetMineralMax();
}

void StatusManager::SetMineralMax(float arg)
{
    m_status.SetMineralMax(arg);
}

float StatusManager::GetWaterCurrent() const
{
    return m_status.GetWaterCurrent();
}

void StatusManager::SetWaterCurrent(float arg)
{
    m_status.SetWaterCurrent(arg);
}

float StatusManager::GetWaterMax() const
{
    return m_status.GetWaterMax();
}

void StatusManager::SetWaterMax(float arg)
{
    m_status.SetWaterMax(arg);
}

bool StatusManager::GetFractureArm() const
{
    return m_status.GetFractureArm();
}

void StatusManager::SetFractureArm(bool arg)
{
    m_status.SetFractureArm(arg);
}

bool StatusManager::GetFractureLeg() const
{
    return m_status.GetFractureLeg();
}

void StatusManager::SetFractureLeg(bool arg)
{
    m_status.SetFractureLeg(arg);
}

bool StatusManager::GetHeadache() const
{
    return m_status.GetHeadache();
}

void StatusManager::SetHeadache(bool arg)
{
    m_status.SetHeadache(arg);
}

bool StatusManager::GetCold() const
{
    return m_status.GetCold();
}

void StatusManager::SetCold(bool arg)
{
    m_status.SetCold(arg);
}

bool StatusManager::GetStomachache() const
{
    return m_status.GetStomachache();
}

void StatusManager::SetStomachache(bool arg)
{
    m_status.SetStomachache(arg);
}

bool StatusManager::GetSleep() const
{
    return m_status.GetSleep();
}

void StatusManager::SetSleep(bool arg)
{
    m_status.SetSleep(arg);
}

bool StatusManager::GetDehydration() const
{
    return m_status.GetDehydration();
}

void StatusManager::SetDehydration(bool arg)
{
    m_status.SetDehydration(arg);
}

bool StatusManager::GetLackOfSleep() const
{
    return m_status.GetLackOfSleep();
}

void StatusManager::SetLackOfSleep(bool arg)
{
    m_status.SetLackOfSleep(arg);
}

void StatusManager::SetPlayerAction(const PlayerAction arg)
{
    m_playerAction = arg;
}
