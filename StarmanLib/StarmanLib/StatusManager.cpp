#include "StatusManager.h"

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
}

void StatusManager::Update()
{
}

void StatusManager::Save(const std::string& csvfile)
{
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
