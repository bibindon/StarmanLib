#include "StatusManager.h"
#include "PowereggDateTime.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Rynen.h"
#include "WeaponManager.h"

#include "Util.h"

using namespace NSStarmanLib;

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

bool Status::GetDead() const
{
    return m_dead;
}

void Status::SetDead(const bool arg)
{
    m_dead = arg;
}

float Status::GetSatiety() const
{
    return m_satiety;
}

void Status::SetSatiety(const float arg)
{
    m_satiety = arg;
}

float Status::GetX() const
{
    return m_x;
}

void Status::SetX(const float arg)
{
    m_x = arg;
}

float Status::GetY() const
{
    return m_y;
}

void Status::SetY(const float arg)
{
    m_y = arg;
}

float Status::GetZ() const
{
    return m_z;
}

void Status::SetZ(const float arg)
{
    m_z = arg;
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

void StatusManager::Init(const std::string& csvfile,
                         const bool decrypt)
{
    {
        ItemManager* itemManager = ItemManager::GetObj();
        if (itemManager->Inited() == false)
        {
            throw std::exception();
        }
    }

    std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvfile, decrypt);

    for (std::size_t i = 1; i < vvs.size(); ++i)
    {
        if (vvs.at(i).at(1) == "�̂̃X�^�~�i�i���ݒl�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBodyStaminaCurrent(value);
        }
        else if (vvs.at(i).at(1) == "�̂̃X�^�~�i�i�ő�l�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBodyStaminaMax(value);
        }
        else if (vvs.at(i).at(1) == "�̂̃X�^�~�i�i�񕜉\�l�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBodyStaminaMaxSub(value);
        }
        else if (vvs.at(i).at(1) == "�]�̃X�^�~�i�i���ݒl�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBrainStaminaCurrent(value);
        }
        else if (vvs.at(i).at(1) == "�]�̃X�^�~�i�i�ő�l�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBrainStaminaMax(value);
        }
        else if (vvs.at(i).at(1) == "�]�̃X�^�~�i�i�񕜉\�l�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBrainStaminaMaxSub(value);
        }
        else if (vvs.at(i).at(1) == "�u����")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetExplosivePower(value);
        }
        else if (vvs.at(i).at(1) == "���̂̏C���x�i���ݒl�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetMuscleCurrent(value);
        }
        else if (vvs.at(i).at(1) == "���̂̏C���x�i�ő�l�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetMuscleMax(value);
        }
        else if (vvs.at(i).at(1) == "�����i���ݒl�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetCarboCurrent(value);
        }
        else if (vvs.at(i).at(1) == "�����i�ő�l�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetCarboMax(value);
        }
        else if (vvs.at(i).at(1) == "�^���p�N���i���ݒl�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetProteinCurrent(value);
        }
        else if (vvs.at(i).at(1) == "�^���p�N���i�ő�l�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetProteinMax(value);
        }
        else if (vvs.at(i).at(1) == "�����i���ݒl�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetLipidCurrent(value);
        }
        else if (vvs.at(i).at(1) == "�����i�ő�l�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetLipidMax(value);
        }
        else if (vvs.at(i).at(1) == "�r�^�~���i���ݒl�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetVitaminCurrent(value);
        }
        else if (vvs.at(i).at(1) == "�r�^�~���i�ő�l�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetVitaminMax(value);
        }
        else if (vvs.at(i).at(1) == "�~�l�����i���ݒl�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetMineralCurrent(value);
        }
        else if (vvs.at(i).at(1) == "�~�l�����i�ő�l�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetMineralMax(value);
        }
        else if (vvs.at(i).at(1) == "�����i���ݒl�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetWaterCurrent(value);
        }
        else if (vvs.at(i).at(1) == "�����i�ő�l�j")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetWaterMax(value);
        }
        else if (vvs.at(i).at(1) == "�r����")
        {
            if (vvs.at(i).at(2) == "��")
            {
                m_status.SetFractureArm(true);
            }
            else
            {
                m_status.SetFractureArm(false);
            }
        }
        else if (vvs.at(i).at(1) == "������")
        {
            if (vvs.at(i).at(2) == "��")
            {
                m_status.SetFractureLeg(true);
            }
            else
            {
                m_status.SetFractureLeg(false);
            }
        }
        else if (vvs.at(i).at(1) == "����")
        {
            if (vvs.at(i).at(2) == "��")
            {
                m_status.SetHeadache(true);
            }
            else
            {
                m_status.SetHeadache(false);
            }
        }
        else if (vvs.at(i).at(1) == "����")
        {
            if (vvs.at(i).at(2) == "��")
            {
                m_status.SetCold(true);
            }
            else
            {
                m_status.SetCold(false);
            }
        }
        else if (vvs.at(i).at(1) == "����")
        {
            if (vvs.at(i).at(2) == "��")
            {
                m_status.SetStomachache(true);
            }
            else
            {
                m_status.SetStomachache(false);
            }
        }
        else if (vvs.at(i).at(1) == "����")
        {
            if (vvs.at(i).at(2) == "��")
            {
                m_status.SetSleep(true);
            }
            else
            {
                m_status.SetSleep(false);
            }
        }
        else if (vvs.at(i).at(1) == "�E���Ǐ�")
        {
            if (vvs.at(i).at(2) == "��")
            {
                m_status.SetDehydration(true);
            }
            else
            {
                m_status.SetDehydration(false);
            }
        }
        else if (vvs.at(i).at(1) == "�����s��")
        {
            if (vvs.at(i).at(2) == "��")
            {
                m_status.SetLackOfSleep(true);
            }
            else
            {
                m_status.SetLackOfSleep(false);
            }
        }
        else if (vvs.at(i).at(1) == "��������ID")
        {
            ItemInfo itemInfo;
            if (vvs.at(i).at(2) == "")
            {
                itemInfo.SetId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                itemInfo.SetId(work);
            }
            m_EquipWeapon = itemInfo;
        }
        else if (vvs.at(i).at(1) == "��������SubID")
        {
            if (vvs.at(i).at(2) == "")
            {
                m_EquipWeapon.SetSubId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                m_EquipWeapon.SetSubId(work);

                Inventory* inventory = Inventory::GetObj();
                ItemInfo itemInfo = inventory->GetItemInfo(m_EquipWeapon.GetId(), m_EquipWeapon.GetSubId());
                m_EquipWeapon.SetDurabilityCurrent(itemInfo.GetDurabilityCurrent());
            }
        }
        else if (vvs.at(i).at(1) == "x")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetX(value);
        }
        else if (vvs.at(i).at(1) == "y")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetY(value);
        }
        else if (vvs.at(i).at(1) == "z")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetZ(value);
        }
        else if (vvs.at(i).at(1) == "���@�̌o���l�i���j")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_experienceFire = value;
        }
        else if (vvs.at(i).at(1) == "���@�̌o���l�i�X�j")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_experienceIce = value;
        }
        else if (vvs.at(i).at(1) == "���@�̌o���l�i�Łj")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_experienceDark = value;
        }
        else if (vvs.at(i).at(1) == "���@�̃��x���i���j")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_levelFire = value;
        }
        else if (vvs.at(i).at(1) == "���@�̃��x���i�X�j")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_levelIce = value;
        }
        else if (vvs.at(i).at(1) == "���@�̃��x���i�Łj")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_levelDark = value;
        }
        else if (vvs.at(i).at(1) == "�w���̑�1ID")
        {
            ItemInfo itemInfo;
            if (vvs.at(i).at(2) == "")
            {
                itemInfo.SetId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                itemInfo.SetId(work);
            }
            m_BagMap[eBagPos::Back1] = itemInfo;
        }
        else if (vvs.at(i).at(1) == "�w���̑�1SubID")
        {
            if (vvs.at(i).at(2) == "")
            {
                m_BagMap.at(eBagPos::Back1).SetSubId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                m_BagMap.at(eBagPos::Back1).SetSubId(work);

                Inventory* inventory = Inventory::GetObj();
                ItemInfo itemInfo = inventory->GetItemInfo(m_BagMap.at(eBagPos::Back1).GetId(),
                                                           m_BagMap.at(eBagPos::Back1).GetSubId());
                m_BagMap.at(eBagPos::Back1).SetDurabilityCurrent(itemInfo.GetDurabilityCurrent());
            }
        }
        else if (vvs.at(i).at(1) == "�w���̑�2ID")
        {
            ItemInfo itemInfo;
            if (vvs.at(i).at(2) == "")
            {
                itemInfo.SetId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                itemInfo.SetId(work);
            }
            m_BagMap[eBagPos::Back2] = itemInfo;
        }
        else if (vvs.at(i).at(1) == "�w���̑�2SubID")
        {
            if (vvs.at(i).at(2) == "")
            {
                m_BagMap.at(eBagPos::Back2).SetSubId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                m_BagMap.at(eBagPos::Back2).SetSubId(work);

                Inventory* inventory = Inventory::GetObj();
                ItemInfo itemInfo = inventory->GetItemInfo(m_BagMap.at(eBagPos::Back2).GetId(),
                                                           m_BagMap.at(eBagPos::Back2).GetSubId());
                m_BagMap.at(eBagPos::Back2).SetDurabilityCurrent(itemInfo.GetDurabilityCurrent());
            }
        }
        else if (vvs.at(i).at(1) == "���̑�ID")
        {
            ItemInfo itemInfo;
            if (vvs.at(i).at(2) == "")
            {
                itemInfo.SetId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                itemInfo.SetId(work);
            }
            m_BagMap[eBagPos::Front] = itemInfo;
        }
        else if (vvs.at(i).at(1) == "���̑�SubID")
        {
            if (vvs.at(i).at(2) == "")
            {
                m_BagMap.at(eBagPos::Front).SetSubId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                m_BagMap.at(eBagPos::Front).SetSubId(work);

                Inventory* inventory = Inventory::GetObj();
                ItemInfo itemInfo = inventory->GetItemInfo(m_BagMap.at(eBagPos::Front).GetId(),
                                                           m_BagMap.at(eBagPos::Front).GetSubId());
                m_BagMap.at(eBagPos::Front).SetDurabilityCurrent(itemInfo.GetDurabilityCurrent());
            }
        }
        else if (vvs.at(i).at(1) == "����̑�ID")
        {
            ItemInfo itemInfo;
            if (vvs.at(i).at(2) == "")
            {
                itemInfo.SetId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                itemInfo.SetId(work);
            }
            m_BagMap[eBagPos::Left] = itemInfo;
        }
        else if (vvs.at(i).at(1) == "����̑�SubID")
        {
            if (vvs.at(i).at(2) == "")
            {
                m_BagMap.at(eBagPos::Left).SetSubId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                m_BagMap.at(eBagPos::Left).SetSubId(work);

                Inventory* inventory = Inventory::GetObj();
                ItemInfo itemInfo = inventory->GetItemInfo(m_BagMap.at(eBagPos::Left).GetId(),
                                                           m_BagMap.at(eBagPos::Left).GetSubId());
                m_BagMap.at(eBagPos::Left).SetDurabilityCurrent(itemInfo.GetDurabilityCurrent());
            }
        }
        else if (vvs.at(i).at(1) == "�E��̑�ID")
        {
            ItemInfo itemInfo;
            if (vvs.at(i).at(2) == "")
            {
                itemInfo.SetId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                itemInfo.SetId(work);
            }
            m_BagMap[eBagPos::Right] = itemInfo;
        }
        else if (vvs.at(i).at(1) == "�E��̑�SubID")
        {
            if (vvs.at(i).at(2) == "")
            {
                m_BagMap.at(eBagPos::Right).SetSubId(-1);
            }
            else
            {
                int work = std::stoi(vvs.at(i).at(2));
                m_BagMap.at(eBagPos::Right).SetSubId(work);

                Inventory* inventory = Inventory::GetObj();
                ItemInfo itemInfo = inventory->GetItemInfo(m_BagMap.at(eBagPos::Right).GetId(),
                                                           m_BagMap.at(eBagPos::Right).GetSubId());
                m_BagMap.at(eBagPos::Right).SetDurabilityCurrent(itemInfo.GetDurabilityCurrent());
            }
        }
    }
    auto inventory = Inventory::GetObj();
    inventory->UpdateVolumeMax(GetAllBag());
}

void StatusManager::Update()
{
    // �v���C���[�̏�Ԃɂ��A���X�ɃX�^�~�i���ቺ
    float bodyStaminaCurrent = m_status.GetBodyStaminaCurrent();
    float bodyStaminaMaxSub = m_status.GetBodyStaminaMaxSub();

    float brainStaminaCurrent = m_status.GetBrainStaminaCurrent();
    float brainStaminaMaxSub = m_status.GetBrainStaminaMaxSub();

    if (m_playerState == PlayerState::STAND)
    {
        bodyStaminaCurrent -= 0.0001f;
        bodyStaminaMaxSub  -= 0.00002f;

        brainStaminaCurrent -= 0.0002f;
        brainStaminaMaxSub  -= 0.00004f;
    }
    else if (m_playerState == PlayerState::WALK)
    {
        bodyStaminaCurrent -= 0.0001f;
        bodyStaminaMaxSub  -= 0.00002f;

        brainStaminaCurrent -= 0.0002f;
        brainStaminaMaxSub  -= 0.00004f;
    }
    else if (m_playerState == PlayerState::SIT)
    {
        bodyStaminaCurrent += (bodyStaminaMaxSub - bodyStaminaCurrent) * 0.01f;
        bodyStaminaMaxSub  -= 0.00002f;

        brainStaminaCurrent += (brainStaminaMaxSub - brainStaminaCurrent) * 0.02f;
        brainStaminaMaxSub  -= 0.00004f;

        // �]�̗̑͂�20���ȉ��ō���ƐQ�Ă��܂�
        if (brainStaminaCurrent <= m_status.GetBrainStaminaMax() * 0.2f)
        {
            m_status.SetSleep(true);
        }
    }
    else if (m_playerState == PlayerState::LYING_DOWN)
    {
        bodyStaminaCurrent += (bodyStaminaMaxSub - bodyStaminaCurrent) * 0.02f;
        bodyStaminaMaxSub  += 0.00002f;

        brainStaminaCurrent += (brainStaminaMaxSub - brainStaminaCurrent) * 0.04f;
        brainStaminaMaxSub  -= 0.00008f;

        // �]�̗̑͂�50���ȉ��ŉ��ɂȂ�ƐQ�Ă��܂�
        if (brainStaminaCurrent <= m_status.GetBrainStaminaMax() * 0.5f)
        {
            m_status.SetSleep(true);
        }
    }
    else if (m_playerState == PlayerState::IDLE_WATER)
    {
        bodyStaminaCurrent -= 0.001f;
        bodyStaminaMaxSub  -= 0.0002f;

        brainStaminaCurrent -= 0.002f;
        brainStaminaMaxSub  -= 0.0004f;
    }
    else if (m_playerState == PlayerState::SWIM)
    {
        bodyStaminaCurrent -= 0.001f;
        bodyStaminaMaxSub  -= 0.0002f;

        brainStaminaCurrent -= 0.002f;
        brainStaminaMaxSub  -= 0.0004f;
    }

    //------------------------------------
    // ����
    // 1���ł�������ƃX�^�~�i�̉�����₷������������
    // 1�������邽�тɂ���Ɉ�������
    // ������90���ɂȂ�Ǝ��S����
    // 99����������0.9999��������
    // 98����������0.9998��������
    // 97����������0.9997��������
    //------------------------------------
    float work1 = 0.f;
    float work2 = 0.f;
    float work3 = 0.f;
    work1 = m_status.GetWaterCurrent();
    work2 = m_status.GetWaterMax();

    // ���݂�99�ōő傪100��������0.99�A�𓾂�
    work3 = work1 / work2;

    if (work3 <= 0.90f)
    {
        m_status.SetDead(true);
    }

    // 0.99 ��0.0099�ɂ���
    work3 /= 100;

    // 0.0099��0.9999�ɂ���
    work3 += 0.99f;

    bodyStaminaCurrent *= work3;

    //------------------------------------
    // ����
    // �s�����Ă�����A�X�^�~�i�̉�����₷������������
    // 40%�����������0.9998�{
    // 20%�ɂȂ�����0.9996�{
    // 0%�ɂȂ��Ă��쎀�͂��Ȃ��B���b��������B���b��0�Ȃ�쎀�B
    // 80%�ȏ゠���
    //------------------------------------
    work1 = m_status.GetCarboCurrent();
    work2 = m_status.GetCarboMax();
    work3 = work1 / work2;
    if (0.2f <= work3 && work3 <= 0.4f)
    {
        bodyStaminaCurrent *= 0.9998f;
        bodyStaminaMaxSub *= 0.9998f;

        brainStaminaCurrent *= 0.9998f;
        brainStaminaMaxSub *= 0.9998f;
    }
    else if (0.f < work3 && work3 <= 0.2f)
    {
        bodyStaminaCurrent *= 0.9996f;
        bodyStaminaMaxSub *= 0.9996f;

        brainStaminaCurrent *= 0.9996f;
        brainStaminaMaxSub *= 0.9996f;
    }
    else if (work3 <= 0.f)
    {
        if (m_status.GetLipidCurrent() <= 0.f)
        {
            m_status.SetDead(true);
        }
    }

    //------------------------------------
    // �r�^�~��
    // �s�����Ă�����A�X�^�~�i�̉�����₷������������
    // 40%�����������0.9999�{
    // 20%�ɂȂ�����0.9998�{
    //------------------------------------
    work1 = m_status.GetVitaminCurrent();
    work2 = m_status.GetVitaminMax();
    work3 = work1 / work2;
    if (work3 <= 0.2f)
    {
        bodyStaminaCurrent *= 0.9999f;
        bodyStaminaMaxSub *= 0.9999f;

        brainStaminaCurrent *= 0.9999f;
        brainStaminaMaxSub *= 0.9999f;
    }
    else if (work3 <= 0.4f)
    {
        bodyStaminaCurrent *= 0.9998f;
        bodyStaminaMaxSub *= 0.9998f;

        brainStaminaCurrent *= 0.9998f;
        brainStaminaMaxSub *= 0.9998f;
    }

    //------------------------------------
    // �~�l����
    // �s�����Ă�����A�X�^�~�i�̉�����₷������������
    // 20%�����������0.9999�{
    // 0%�ɂȂ�����0.9998�{
    //------------------------------------
    work1 = m_status.GetMineralCurrent();
    work2 = m_status.GetMineralMax();
    work3 = work1 / work2;
    if (work3 <= 0.f)
    {
        bodyStaminaCurrent *= 0.9999f;
        bodyStaminaMaxSub *= 0.9999f;

        brainStaminaCurrent *= 0.9999f;
        brainStaminaMaxSub *= 0.9999f;
    }
    else if (work3 <= 0.2f)
    {
        bodyStaminaCurrent *= 0.9998f;
        bodyStaminaMaxSub *= 0.9998f;

        brainStaminaCurrent *= 0.9998f;
        brainStaminaMaxSub *= 0.9998f;
    }

    //------------------------------------
    // �C���x���g���̏d��
    // �C���x���g���̏d�ʂɂ���ăX�^�~�i�̉�����₷������������
    // 0kg��������1�{
    // 10kg��������0.999�{
    // 100�s��������0.99�{
    // 1���𑫂��āA1�������̐��Ŋ���
    // ��
    //   10kg��������0.999�{
    //   10000 / (10 + 10000) = 0.999
    //------------------------------------
    {
        // �����Ă�����A���ɂȂ��Ă����疳���B
        if (m_playerState != PlayerState::LYING_DOWN &&
            m_playerState != PlayerState::SIT)
        {
            Inventory* inventory = Inventory::GetObj();
            float weight = inventory->GetWeight();
            work1 = 10000 / (weight + 10000);

            bodyStaminaCurrent *= work1;
            bodyStaminaMaxSub *= work1;

            brainStaminaCurrent *= work1;
            brainStaminaMaxSub *= work1;
        }
    }

    //-----------------------------------------
    // �v�Z���ʂ��Z�b�g
    //-----------------------------------------

    // �X�^�~�i���Ղ���������̂�1/10�ɂ��Ă݂�
    {
        auto work1 = m_status.GetBodyStaminaCurrent();
        auto work2 = m_status.GetBodyStaminaMaxSub();

        auto work3 = m_status.GetBrainStaminaCurrent();
        auto work4 = m_status.GetBrainStaminaMaxSub();

        bodyStaminaCurrent = work1 - (work1 - bodyStaminaCurrent) * 0.1f;
        bodyStaminaMaxSub = work2 - (work2 - bodyStaminaMaxSub) * 0.1f;

        brainStaminaCurrent = work3 - (work3 - brainStaminaCurrent) * 0.1f;
        brainStaminaMaxSub = work4 - (work4 - brainStaminaMaxSub) * 0.1f;
    }

    m_status.SetBodyStaminaCurrent(bodyStaminaCurrent);
    m_status.SetBodyStaminaMaxSub(bodyStaminaMaxSub);

    m_status.SetBrainStaminaCurrent(brainStaminaCurrent);
    m_status.SetBrainStaminaMaxSub(brainStaminaMaxSub);

    // ���S
    if (bodyStaminaCurrent <= 0.f)
    {
        m_status.SetDead(true);
    }

    //------------------------------------------------------
    // �̓��ܑ̌�h�{�f�Ɛ��������炷
    //------------------------------------------------------
    // ��������H�ׂȂ���Ἀ��̓�����0�ɂȂ��Ă����������͂Ȃ��͂��B
    work1 = m_status.GetCarboCurrent();
    work1 -= 0.02f;
    m_status.SetCarboCurrent(work1);

    work1 = m_status.GetProteinCurrent();
    work1 -= 0.01f;
    m_status.SetProteinCurrent(work1);

    // �������Ȃ��Ȃ����玉�b��������
    if (m_status.GetCarboCurrent() <= 0.f)
    {
        work1 = m_status.GetLipidCurrent();
        work1 -= 0.01f;
        m_status.SetLipidCurrent(work1);
    }

    work1 = m_status.GetVitaminCurrent();
    work1 -= 0.01f;
    m_status.SetVitaminCurrent(work1);

    work1 = m_status.GetMineralCurrent();
    work1 -= 0.01f;
    m_status.SetMineralCurrent(work1);

    work1 = m_status.GetWaterCurrent();
    work1 -= 0.01f;
    m_status.SetWaterCurrent(work1);

    //-----------------------------------------------------
    // ��8���ɂȂ����炢�����̃X�e�[�^�X���X�V
    //-----------------------------------------------------
    PowereggDateTime* dateTime = PowereggDateTime::GetObj();
    int currentDay = dateTime->GetDay();
    int currentHour = dateTime->GetHour();

    //--------------------------------------------------
    // 1. �O��7���ō���8���Ȃ璩8�����z���Ă���B
    // 2. �O��A7���ō���1���̎��A�����͏������Ȃ��Ă��邪��8�����z���Ă���B
    // 3. ������19������20���ɂȂ��Ă����璩8�����z�����Ƃ͂Ȃ�Ȃ��悤�Ɏv���邪
    //    ���t��1������2���ɑ����Ă����璩8�����z���Ă���B
    // ��x��24���Ԉȏ�A�����i�ނ��Ƃ͂Ȃ��\��
    //--------------------------------------------------

    // ���t��0�Ȃ珈�����Ȃ�
    if (m_previousDay != 0)
    {
        // ���t���ς���Ă��Ȃ��p�^�[��
        if (m_previousDay == currentDay)
        {
            if (m_previousHour <= 7 && currentHour >= 8)
            {
                m_over8clock = true;
            }
        }
        // ���t���i��ł���p�^�[��
        else if (m_previousDay < currentDay)
        {
            // �O��7�����O�Ȃ�8�����܂����ł���
            if (m_previousHour <= 7)
            {
                m_over8clock = true;
            }
        }
        else
        {
            throw std::exception();
        }
    }
    m_previousDay = currentDay;
    m_previousHour = currentHour;

    if (m_over8clock)
    {
        m_over8clock = false;

        // �̂̃X�^�~�i��70���ȉ��ɂȂ������Ƃ������1�x���Ȃ�������
        // �̂̃X�^�~�i�̍ő�l��1��������
        // �g���[�j���O�s��
        if (m_training == false)
        {
            float work = GetBodyStaminaMax();
            work *= 0.99f;
            SetBodyStaminaMax(work);

            // �񕜉\�l���ő�l�𒴂��Ă͂Ȃ�Ȃ��B
            if (GetBodyStaminaMaxSub() > work)
            {
                SetBodyStaminaMaxSub(work);
            }
        }

        if (m_status.GetSleep() == false)
        {
            m_status.SetSleep(true);
        }
    }

    //-----------------------------------------------------------
    // �_�񂵂�1�N�o�߂��Ă����玀�S
    //-----------------------------------------------------------
    Rynen* rynen = Rynen::GetObj();
    if (rynen->GetContracted())
    {
        int rynenYear = 0;
        int rynenMonth = 0;
        int rynenDay = 0;
        rynen->GetContractDate(&rynenYear, &rynenMonth, &rynenDay);

        int currentYear = dateTime->GetYear();
        int currentMonth = dateTime->GetMonth();
        int currentDay = dateTime->GetDay();

        bool deadline = false;
        if (rynenYear > currentYear)
        {
            deadline = true;
        }
        else if (rynenYear == currentYear)
        {
            if (rynenMonth > currentMonth)
            {
                deadline = true;
            }
            else if (rynenMonth == currentMonth)
            {
                if (rynenDay > currentDay)
                {
                    deadline = true;
                }
            }
        }

        if (deadline)
        {
            m_status.SetDead(true);
        }
    }

    //----------------------------------------------------
    // ��Ԉُ�̎���
    // ���Ԍo�߂ł�������Ȃ��B
    // ���ׁF5��
    // �r���܁E�����܁F90��
    // ���ɁE���ɁF1���i��24���ԁj
    //----------------------------------------------------
    if (m_status.GetCold())
    {
        --m_remainColdCure;
        if (m_remainColdCure == 0)
        {
            m_status.SetCold(false);
        }
    }

    if (m_status.GetFractureArm())
    {
        // �ܑ�h�{�f�������ȉ��̎��͉񕜂��~�܂�
        if (m_status.GetCarboCurrent() / m_status.GetCarboMax() >= 0.5f &&
            m_status.GetProteinCurrent() / m_status.GetProteinMax() >= 0.5f &&
            m_status.GetLipidCurrent() / m_status.GetLipidMax() >= 0.5f &&
            m_status.GetVitaminCurrent() / m_status.GetVitaminMax() >= 0.5f &&
            m_status.GetMineralCurrent() / m_status.GetMineralMax() >= 0.5f)
        {
            --m_remainArmFracCure;
        }

        if (m_remainArmFracCure == 0)
        {
            m_status.SetFractureArm(false);
        }
    }

    if (m_status.GetFractureLeg())
    {
        // �ܑ�h�{�f�������ȉ��̎��͉񕜂��~�܂�
        if (m_status.GetCarboCurrent() / m_status.GetCarboMax() >= 0.5f &&
            m_status.GetProteinCurrent() / m_status.GetProteinMax() >= 0.5f &&
            m_status.GetLipidCurrent() / m_status.GetLipidMax() >= 0.5f &&
            m_status.GetVitaminCurrent() / m_status.GetVitaminMax() >= 0.5f &&
            m_status.GetMineralCurrent() / m_status.GetMineralMax() >= 0.5f)
        {
            --m_remainLegFracCure;
        }

        if (m_remainLegFracCure == 0)
        {
            m_status.SetFractureLeg(false);
        }
    }

    if (m_status.GetHeadache())
    {
        --m_remainHeadacheCure;
        if (m_remainHeadacheCure == 0)
        {
            m_status.SetHeadache(false);
        }
    }

    if (m_status.GetStomachache())
    {
        --m_remainStomachacheCure;
        if (m_remainStomachacheCure== 0)
        {
            m_status.SetStomachache(false);
        }
    }

    if (m_status.GetDehydration())
    {
        if (m_status.GetCarboCurrent() / m_status.GetCarboMax() >= 0.5f &&
            m_status.GetProteinCurrent() / m_status.GetProteinMax() >= 0.5f &&
            m_status.GetLipidCurrent() / m_status.GetLipidMax() >= 0.5f &&
            m_status.GetVitaminCurrent() / m_status.GetVitaminMax() >= 0.5f &&
            m_status.GetMineralCurrent() / m_status.GetMineralMax() >= 0.5f)
        {
            if (m_status.GetWaterCurrent() / m_status.GetWaterMax() >= 0.98f)
            {
                --m_remainDehydration;
            }
        }

        if (m_remainDehydration== 0)
        {
            m_status.SetDehydration(false);
        }
    }
}

void StatusManager::Save(const std::string& csvfile,
                         const float player_x,
                         const float player_y,
                         const float player_z,
                         const bool encrypt)
{
    std::vector<std::vector<std::string> > vvs;
    std::vector<std::string> vs;
    std::string work;

    vs.clear();
    vs.push_back("ID");
    vs.push_back("�X�e�[�^�X��");
    vs.push_back("�l");
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("1");
    vs.push_back("�̂̃X�^�~�i�i���ݒl�j");
    work = std::to_string(m_status.GetBodyStaminaCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("2");
    vs.push_back("�̂̃X�^�~�i�i�ő�l�j");
    work = std::to_string(m_status.GetBodyStaminaMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("3");
    vs.push_back("�̂̃X�^�~�i�i�񕜉\�l�j");
    work = std::to_string(m_status.GetBodyStaminaMaxSub());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("4");
    vs.push_back("�]�̃X�^�~�i�i���ݒl�j");
    work = std::to_string(m_status.GetBrainStaminaCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("5");
    vs.push_back("�]�̃X�^�~�i�i�ő�l�j");
    work = std::to_string(m_status.GetBrainStaminaMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("6");
    vs.push_back("�]�̃X�^�~�i�i�񕜉\�l�j");
    work = std::to_string(m_status.GetBrainStaminaMaxSub());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("7");
    vs.push_back("�u����");
    work = std::to_string(m_status.GetExplosivePower());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("8");
    vs.push_back("���̂̏C���x�i���ݒl�j");
    work = std::to_string(m_status.GetMuscleCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("9");
    vs.push_back("���̂̏C���x�i�ő�l�j");
    work = std::to_string(m_status.GetMuscleMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("10");
    vs.push_back("�����i���ݒl�j");
    work = std::to_string(m_status.GetCarboCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("11");
    vs.push_back("�����i�ő�l�j");
    work = std::to_string(m_status.GetCarboMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("12");
    vs.push_back("�^���p�N���i���ݒl�j");
    work = std::to_string(m_status.GetProteinCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("13");
    vs.push_back("�^���p�N���i�ő�l�j");
    work = std::to_string(m_status.GetProteinMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("14");
    vs.push_back("�����i���ݒl�j");
    work = std::to_string(m_status.GetLipidCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("15");
    vs.push_back("�����i�ő�l�j");
    work = std::to_string(m_status.GetLipidMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("16");
    vs.push_back("�r�^�~���i���ݒl�j");
    work = std::to_string(m_status.GetVitaminCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("17");
    vs.push_back("�r�^�~���i�ő�l�j");
    work = std::to_string(m_status.GetVitaminMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("18");
    vs.push_back("�~�l�����i���ݒl�j");
    work = std::to_string(m_status.GetMineralCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("19");
    vs.push_back("�~�l�����i�ő�l�j");
    work = std::to_string(m_status.GetMineralMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("20");
    vs.push_back("�����i���ݒl�j");
    work = std::to_string(m_status.GetWaterCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("21");
    vs.push_back("�����i�ő�l�j");
    work = std::to_string(m_status.GetWaterMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("22");
    vs.push_back("�r����");
    if (m_status.GetFractureArm())
    {
        vs.push_back("��");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("23");
    vs.push_back("������");
    if (m_status.GetFractureLeg())
    {
        vs.push_back("��");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("24");
    vs.push_back("����");
    if (m_status.GetHeadache())
    {
        vs.push_back("��");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("25");
    vs.push_back("����");
    if (m_status.GetCold())
    {
        vs.push_back("��");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("26");
    vs.push_back("����");
    if (m_status.GetStomachache())
    {
        vs.push_back("��");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("27");
    vs.push_back("����");
    if (m_status.GetSleep())
    {
        vs.push_back("��");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("28");
    vs.push_back("�E���Ǐ�");
    if (m_status.GetDehydration())
    {
        vs.push_back("��");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("29");
    vs.push_back("�����s��");
    if (m_status.GetLackOfSleep())
    {
        vs.push_back("��");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("30");
    vs.push_back("��������ID");
    work = std::to_string(GetEquipWeapon().GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("31");
    vs.push_back("��������SubID");
    work = std::to_string(GetEquipWeapon().GetSubId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("32");
    vs.push_back("x");
    work = std::to_string(player_x);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("33");
    vs.push_back("y");
    work = std::to_string(player_y);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("34");
    vs.push_back("z");
    work = std::to_string(player_z);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("35");
    vs.push_back("���@�̌o���l�i���j");
    work = std::to_string(m_experienceFire);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("36");
    vs.push_back("���@�̌o���l�i�X�j");
    work = std::to_string(m_experienceIce);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("37");
    vs.push_back("���@�̌o���l�i�Łj");
    work = std::to_string(m_experienceDark);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("38");
    vs.push_back("���@�̃��x���i���j");
    work = std::to_string(m_levelFire);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("39");
    vs.push_back("���@�̃��x���i�X�j");
    work = std::to_string(m_levelIce);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("40");
    vs.push_back("���@�̃��x���i�Łj");
    work = std::to_string(m_levelDark);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("41");
    vs.push_back("�w���̑�1ID");
    work = std::to_string(m_BagMap.at(eBagPos::Back1).GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("42");
    vs.push_back("�w���̑�1SubID");
    work = std::to_string(m_BagMap.at(eBagPos::Back1).GetSubId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("43");
    vs.push_back("�w���̑�2ID");
    work = std::to_string(m_BagMap.at(eBagPos::Back2).GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("44");
    vs.push_back("�w���̑�2SubID");
    work = std::to_string(m_BagMap.at(eBagPos::Back2).GetSubId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("45");
    vs.push_back("���̑�ID");
    work = std::to_string(m_BagMap.at(eBagPos::Front).GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("46");
    vs.push_back("���̑�SubID");
    work = std::to_string(m_BagMap.at(eBagPos::Front).GetSubId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("47");
    vs.push_back("����̑�ID");
    work = std::to_string(m_BagMap.at(eBagPos::Left).GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("48");
    vs.push_back("����̑�SubID");
    work = std::to_string(m_BagMap.at(eBagPos::Left).GetSubId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("49");
    vs.push_back("�E��̑�ID");
    work = std::to_string(m_BagMap.at(eBagPos::Right).GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("50");
    vs.push_back("�E��̑�SubID");
    work = std::to_string(m_BagMap.at(eBagPos::Right).GetSubId());
    vs.push_back(work);
    vvs.push_back(vs);

    Util::WriteToCsv(csvfile, vvs, encrypt);
}

float StatusManager::GetWalkSpeed()
{
    // �ő�ύڗʂ𒴂��Ă�����������Ƃ��ł��Ȃ�
    {
        float work1 = Inventory::GetObj()->GetVolume();
        float work2 = Inventory::GetObj()->GetVolumeMax();
        if (work1 > work2)
        {
            return 0.f;
        }
    }

    float walkSpeed = 1.f;
    float work = 0.f;
    bool work_b = false;

    // �̂̃X�^�~�i��10���ȉ��ɂȂ�ƈړ����x��1/10�ɂȂ�B
    if (m_status.GetBodyStaminaCurrent() < m_status.GetBodyStaminaMax() * 0.5f)
    {
        walkSpeed *= 0.1f;
    }
    // �̂̃X�^�~�i��50���ȉ��ɂȂ�ƈړ����x�������ɂȂ�B
    else if (m_status.GetBodyStaminaCurrent() < m_status.GetBodyStaminaMax() * 0.5f)
    {
        walkSpeed *= 0.5f;
    }

    // �u���͂�������Ε����̂������Ȃ�
    // 100��������1.0�{�B110��������1.1�{
    work = m_status.GetExplosivePower();
    walkSpeed *= work / 100;

    // �C���x���g���̏d�ʂɂ���ĕ��s���x��x������
    // �����̎��ɂ������̂�
    // 10������10���d��(kg)�Ŋ���B
    // 0kg��������1�{
    // 10kg��������0.5�{
    // 100�s���������0.1�{
    // 10000�s���������0.01�{
    Inventory* inventory = Inventory::GetObj();
    float weight = inventory->GetWeight();
    work = (weight + 10) / 10;
    walkSpeed *= work;

    // �������܂��Ă�����ړ����x��90���_�E���i��0.1�{�ɂȂ�j
    work_b = m_status.GetFractureLeg();
    if (work_b)
    {
        walkSpeed *= 0.1f;
    }

    // ������
    walkSpeed *= 3.f;

    return walkSpeed;
}

float StatusManager::GetAttackPower()
{
    float result = 0.f;
    float work = 0.0;

    // -1�������畐��𑕔����Ă��Ȃ�
    auto inventory = Inventory::GetObj();
    if (m_EquipWeapon.GetId() != -1)
    {
        auto itemManager = ItemManager::GetObj();
        auto itemDef = itemManager->GetItemDef(m_EquipWeapon.GetId());
        auto weaponName = itemDef.GetName();
        auto weaponManager = WeaponManager::GetObj();
        auto itemInfo = inventory->GetItemInfo(m_EquipWeapon.GetId(), m_EquipWeapon.GetSubId());

        // �������̕���̍U����
        double attackRate = weaponManager->GetAttackRate(weaponName, itemDef.GetLevel());
        result = (float)attackRate;

        // �ϋv�x��0��������U���͂�1�ɂȂ�
        if (itemInfo.GetDurabilityCurrent() == 0)
        {
            result = 1.f;
        }
    }
    else
    {
        result = 1.f;
    }

    // �u����
    work = m_status.GetExplosivePower();
    result *= work;

    // �]�̃X�^�~�i
    // 10%�����Ă�����1%�U���͂�������B
    // 20%�����Ă�����2%�U���͂�������B
    work = m_status.GetBrainStaminaCurrent() / m_status.GetBrainStaminaMax();
    work = (1.0f - work) / 10;
    result *= (1.0f - work);

    // ����
    // 1%�����Ă�����1%�U���͂�������B
    // 2%�����Ă�����2%�U���͂�������B
    work = m_status.GetWaterCurrent() / m_status.GetWaterMax();
    result *= work;

    // �d��
    // �C���x���g���̏d�ʂɂ���čU���͂��ቺ����
    // 0kg��������1�{
    // 10kg��������0.9�{
    // 100�s��������0�{
    //------------------------------------
    float weight = inventory->GetWeight();
    work = (1.f - (weight / 100.0f));
    if (work < 0.f)
    {
        work = 0.f;
    }
    result *= work;

    // ���̂̏C���x
    work = m_status.GetMuscleCurrent() / m_status.GetMuscleMax();
    result *= work;

    // �r�̍����܂�Ă�����90���_�E���i��0.1�{�ɂȂ�j
    if (m_status.GetFractureArm())
    {
        result *= 0.1f;
    }

    // ���̍����܂�Ă�����90���_�E���i��0.1�{�ɂȂ�j
    if (m_status.GetFractureLeg())
    {
        result *= 0.1f;
    }

    // ���ׂ̏ꍇ�A50���_�E��
    if (m_status.GetCold())
    {
        result *= 0.5f;
    }

    // �E���Ǐ�̏ꍇ�A50���_�E��
    if (m_status.GetDehydration())
    {
        result *= 0.5f;
    }

    // ���ɂ̏ꍇ�A50���_�E��
    if (m_status.GetHeadache())
    {
        result *= 0.5f;
    }

    // ���ɂ̏ꍇ�A50���_�E��
    if (m_status.GetStomachache())
    {
        result *= 0.5f;
    }

    // ����ɑ܂������Ă�����U���͂���������
    if (GetBag(eBagPos::Left).GetId() != -1)
    {
        result *= 0.5f;
    }

    // �U���͂��}�C�i�X�A�͂��肦�Ȃ��B
    if (result < 0.f)
    {
        result = 0.f;
    }

    return result;
}

void StatusManager::ConsumeAttackCost()
{
    //--------------------------------
    // ����
    // ����̑ϋv�x�A�X�^�~�i�A���̑��A�S�����Ղ���
    //--------------------------------

    int work_i = 0;
    float work_f = 0;

    // ����̑ϋv�x
    if (m_EquipWeapon.GetId() != -1)
    {
        auto inventory = Inventory::GetObj();
        auto itemInfo = inventory->GetItemInfo(m_EquipWeapon.GetId(), m_EquipWeapon.GetSubId());
        work_i = itemInfo.GetDurabilityCurrent();
        --work_i;
        itemInfo.SetDurabilityCurrent(work_i);
    }

    // ����
    work_f = m_status.GetWaterCurrent();
    m_status.SetWaterCurrent(work_f - 0.01f);

    // �g�̂̃X�^�~�i
    work_f = m_status.GetBodyStaminaCurrent();
    m_status.SetBodyStaminaCurrent(work_f - 0.01f);

    // ���̂̏C���x
    work_f = m_status.GetMuscleCurrent();
    if (m_EquipWeapon.GetId() != -1)
    {
        m_status.SetMuscleCurrent(work_f - 0.01f);
    }
    // �f�肾������җ�ɏ��Ղ���
    else
    {
        m_status.SetMuscleCurrent(work_f - 0.05f);
    }

    //---------------------------------------------
    // ��Ԉُ������
    //---------------------------------------------

    // ����
    if (m_status.GetCold())
    {
        ++m_remainColdCure;
    }

    // �r�̍���
    if (m_status.GetFractureArm())
    {
        ++m_remainArmFracCure;
    }

    // ���̍���
    if (m_status.GetFractureLeg())
    {
        ++m_remainLegFracCure;
    }

    // �E���Ǐ�
    if (m_status.GetDehydration())
    {
        ++m_remainDehydration;
    }

    // ����
    if (m_status.GetHeadache())
    {
        ++m_remainHeadacheCure;
    }

    // ����
    if (m_status.GetStomachache())
    {
        ++m_remainStomachacheCure;
    }
}

float StatusManager::GetDefensePower()
{
    // TODO
    // �G�̍U���́A��l���̏u���͂Ȃ�
    return 1.0f;
}

bool StatusManager::Eat(const ItemDef& itemDef)
{
    if (itemDef.GetType() != ItemDef::ItemType::FOOD)
    {
        throw std::exception();
    }

    float work_f = 0.f;
    work_f = m_status.GetSatiety();
    work_f += itemDef.GetCarbo();

    // ������100�������疞���ł���Ƃ��Ă���ȏ�H�ׂ��Ȃ��B
    if (work_f >= 100.f)
    {
        return false;
    }
    m_status.SetSatiety(work_f);

    work_f = GetCarboCurrent();
    work_f += itemDef.GetCarbo();
    SetCarboCurrent(work_f);

    work_f = GetProteinCurrent();
    work_f += itemDef.GetProtein();
    SetProteinCurrent(work_f);

    work_f = GetLipidCurrent();
    work_f += itemDef.GetLipid();
    SetLipidCurrent(work_f);

    work_f = GetVitaminCurrent();
    work_f += itemDef.GetVitamin();
    SetVitaminCurrent(work_f);

    work_f = GetMineralCurrent();
    work_f += itemDef.GetMineral();
    SetMineralCurrent(work_f);

    work_f = GetMineralCurrent();
    work_f += itemDef.GetMineral();
    SetMineralCurrent(work_f);

    work_f = GetWaterCurrent();
    work_f += itemDef.GetWater();
    SetWaterCurrent(work_f);

    return true;
}

// TODO �Ȃ񂩕�
bool StatusManager::Sleep()
{
    PowereggDateTime* dateTime = PowereggDateTime::GetObj();

    // ������������
    // �]�̗̑͂�50���ȉ��ŉ��ɂȂ���or�]�̗̑͂�20���ȉ��ō������Ȃ牽���ł��Q�Ă��܂��B
    // ���̂Ƃ��A0���������琇���A������O�������牼���ɂȂ�B
    bool nap = false;

    if (7 <= dateTime->GetHour() && dateTime->GetHour() <= 23)
    {
        if (m_status.GetBrainStaminaCurrent() <= m_status.GetBrainStaminaMax() * 0.5f)
        {
            if (m_playerState == PlayerState::LYING_DOWN)
            {
                nap = true;
            }
        }
        else if (m_status.GetBrainStaminaCurrent() <= m_status.GetBrainStaminaMax() * 0.2f)
        {
            if (m_playerState == PlayerState::SIT)
            {
                nap = true;
            }
        }
        else
        {
            // �����s���ł��Ȃ��A�g���[�j���O�����Ă��Ȃ��Ȃ�
            // 7~23���̊ԂɐQ�悤�Ƃ��Ă��Q�邱�Ƃ��ł��Ȃ��B
            if (m_training == false &&
                m_status.GetLackOfSleep() == false)
            {
                return false;
            }
        }
    }

    // �ܑ�h�{�f�Ɛ���������
    {
        float work1 = 0.f;
        float work2 = 0.f;

        // ����
        work1 = GetCarboCurrent();
        work1 *= 0.8f;
        work1 -= 5.f;
        if (work1 < 0.f)
        {
            // ������0�Ȃ�A����������
            work2 = work1;
            work1 = 0.f;
        }
        SetCarboCurrent(work1);

        // �^���p�N��
        work1 = GetProteinCurrent();
        work1 *= 0.8f;
        work1 -= 5.f;
        if (work1 < 0.f)
        {
            work1 = 0.f;
        }
        SetProteinCurrent(work1);

        // ����
        work1 = GetLipidCurrent();
        work1 += work2;
        if (work1 < 0.f)
        {
            work1 = 0.f;
        }
        SetLipidCurrent(work1);

        // �r�^�~��
        work1 = GetVitaminCurrent();
        work1 *= 0.8f;
        work1 -= 5.f;
        if (work1 < 0.f)
        {
            work1 = 0.f;
        }
        SetVitaminCurrent(work1);

        // �~�l����
        work1 = GetMineralCurrent();
        work1 *= 0.8f;
        work1 -= 5.f;
        if (work1 < 0.f)
        {
            work1 = 0.f;
        }
        SetMineralCurrent(work1);

        // ����
        work1 = GetWaterCurrent();
        work1 -= 0.5f;
        if (work1 < 0.f)
        {
            work1 = 0.f;
        }
        SetWaterCurrent(work1);
    }

    // �����i�����ł͂Ȃ��j
    if (nap == false)
    {
        // �]�̗̑͂͐Q����S������B
        // �Q��̂��x��������񕜗ʂ�50���ɐ��������
        bool late = false;

        m_status.SetSleep(true);

        int hour = dateTime->GetHour();
        if (2 <= hour && hour <= 8)
        {
            late = true;
        }

        float work1 = 0.f;
        float work2 = 0.f;

        if (late == false)
        {
            work1 = GetBrainStaminaMax();
            SetBrainStaminaMaxSub(work1);
            SetBrainStaminaCurrent(work1);
        }
        // �Q�鎞�Ԃ��x��������
        else
        {
            work1 = GetBrainStaminaMax();
            work2 = GetBrainStaminaMaxSub();
            work2 += (work1 - work2) / 2;
            SetBrainStaminaMaxSub(work2);

            work2 = GetBrainStaminaCurrent();
            work2 += (work1 - work2) / 2;
            SetBrainStaminaCurrent(work1);
            m_status.SetLackOfSleep(true);
        }

        // �̂̃X�^�~�i�͐Q����Q�s���ł��S������
        work1 = GetBodyStaminaMax();
        SetBodyStaminaMaxSub(work1);
        SetBodyStaminaCurrent(work1);

        // ���̂̏C���x
        {
            work1 = GetMuscleCurrent();
            work2 = GetMuscleMax();

            work1 += 10.f;
            if (work1 >= work2)
            {
                work1 = work2;
            }
            SetMuscleCurrent(work1);
        }

        // ���@���x���A�b�v�̏�����
        {
            m_levelUpFire = false;
            m_levelUpIce = false;
            m_levelUpDark = false;

            m_levelDownFire = false;
            m_levelDownIce = false;
            m_levelDownDark = false;
        }

        // �o���l�̒ቺ
        {
            m_experienceFire -= 10;
            m_experienceIce -= 10;
            m_experienceDark -= 10;
        }

        // ���@���x���̏㏸
        {
            if (m_experienceFire >= 100)
            {
                m_experienceFire = 0;
                ++m_levelFire;

                if (m_levelFire >= 10)
                {
                    m_levelFire = 10;
                }
                else
                {
                    m_levelUpFire = true;
                }
            }

            if (m_experienceIce >= 100)
            {
                m_experienceIce = 0;
                ++m_levelIce;

                if (m_levelIce >= 10)
                {
                    m_levelIce = 10;
                }
                else
                {
                    m_levelUpIce = true;
                }
            }

            if (m_experienceDark >= 100)
            {
                m_experienceDark = 0;
                ++m_levelDark;

                if (m_levelDark >= 10)
                {
                    m_levelDark = 10;
                }
                else
                {
                    m_levelUpDark = true;
                }
            }
        }

        // ���@�̃��x���_�E��
        {
            if (m_experienceFire < 0)
            {
                // -5��������95�ɂ���
                m_experienceFire = 100 + m_experienceFire;
                --m_levelFire;

                if (m_levelFire < 0)
                {
                    m_levelFire = 0;
                    m_experienceFire = 0;
                }
                else
                {
                    m_levelDownFire = true;
                }
            }

            if (m_experienceIce < 0)
            {
                // -5��������95�ɂ���
                m_experienceIce = 100 + m_experienceIce;
                --m_levelIce;

                if (m_levelIce < 0)
                {
                    m_levelIce = 0;
                    m_experienceIce = 0;
                }
                else
                {
                    m_levelDownIce = true;
                }
            }

            if (m_experienceDark < 0)
            {
                // -5��������95�ɂ���
                m_experienceDark = 100 + m_experienceDark;
                --m_levelDark;

                if (m_levelDark < 0)
                {
                    m_levelDark = 0;
                    m_experienceDark = 0;
                }
                else
                {
                    m_levelDownDark = true;
                }
            }
        }

        // ���Ԃ�7���Ԑi�߂�
        dateTime->IncreaseDateTime(0, 0, 7, 0, 0);
    }
    // ����
    else if (nap)
    {
        // �]�̃X�^�~�i�͐Q����S������B
        float work = 0.f;
        float work2 = 0.f;
        work = GetBrainStaminaMax();
        SetBrainStaminaMaxSub(work);
        SetBrainStaminaCurrent(work);

        // �̂̃X�^�~�i�͐Q����S������
        work = GetBodyStaminaMax();
        SetBodyStaminaMaxSub(work);
        SetBodyStaminaCurrent(work);

        // ���̂̏C���x
        {
            work = GetMuscleCurrent();
            work2 = GetMuscleMax();

            work += 2.f;
            if (work >= work2)
            {
                work = work2;
            }
            SetMuscleCurrent(work);
        }

        // ���Ԃ�90���i�߂�
        dateTime->IncreaseDateTime(0, 0, 1, 30, 0);
    }
    return true;
}

void StatusManager::Talk()
{
    float work = 0.f;
    work = GetBrainStaminaCurrent();

    work -= 0.05f;
    SetBrainStaminaMaxSub(work);

    work -= 0.05f;
    SetBrainStaminaCurrent(work);
}

void StatusManager::UseMagic()
{
    float work = 0.f;
    work = GetBrainStaminaCurrent();

    work -= 0.25f;
    SetBrainStaminaMaxSub(work);

    work -= 0.25f;
    SetBrainStaminaCurrent(work);

    if (m_eMagicType == eMagicType::Fire)
    {
        ++m_experienceFire;
    }
    else if (m_eMagicType == eMagicType::Ice)
    {
        ++m_experienceIce;
    }
    else if (m_eMagicType == eMagicType::Dark)
    {
        ++m_experienceDark;
    }
}

void StatusManager::DrinkWordBress(const float playerX,
                                                 const float playerY,
                                                 const float playerZ)
{
    auto rynen = Rynen::GetObj();
    rynen->SetReviveEnable(true);
    rynen->SetRevivePos(playerX, playerY, playerZ);
}

void StatusManager::CutTree(const std::string& weapon, const int level)
{
    //------------------------------------------------------
    // ����̎�ނ⋭���l�ɂ���ăX�^�~�i���Ղ��ς��悤�ɂ���
    //------------------------------------------------------

    float magni = 0.f;

    if (weapon == "�c���̐�")
    {
        magni = 1.f;
    }
    else if (weapon == "�Ε�")
    {
        if (level == 0 || level == -1)
        {
            magni = 0.9f;
        }
        else if (level == 1)
        {
            magni = 0.8f;
        }
        else if (level == 2)
        {
            magni = 0.7f;
        }
        else if (level == 3)
        {
            magni = 0.6f;
        }
        else if (level == 4)
        {
            magni = 0.5f;
        }
        else if (level == 5)
        {
            magni = 0.4f;
        }
    }

    // �g�̂̃X�^�~�i
    {
        float work = 0.f;
        work = GetBodyStaminaMaxSub();

        work -= 15.f * magni;
        SetBodyStaminaMaxSub(work);

        work = GetBodyStaminaCurrent();

        work -= 30.f * magni;
        SetBodyStaminaCurrent(work);
    }

    // �]�̃X�^�~�i
    {
        float work = 0.f;
        work = GetBrainStaminaMaxSub();

        work -= 20.f * magni;
        SetBrainStaminaMaxSub(work);

        work = GetBrainStaminaCurrent();

        work -= 40.f * magni;
        SetBrainStaminaCurrent(work);
    }

    // ����
    {
        float work = 0.f;
        work = GetWaterCurrent();

        work -= 5.f * magni;
        SetWaterCurrent(work);
    }

    // ���̂̑���
    {
        auto work = GetMuscleCurrent();
        if (weapon == "�c���̐�")
        {
            SetMuscleCurrent(work - (20.f * magni));
        }
        else
        {
            SetMuscleCurrent(work - (15.f * magni));
        }
    }

    // ��Ԉُ�̈���
    {
        if (GetCold())
        {
            m_remainColdCure += 2;
        }

        if (GetFractureArm())
        {
            m_remainArmFracCure += 2;
        }

        if (GetFractureLeg())
        {
            m_remainLegFracCure += 2;
        }

        if (GetHeadache())
        {
            m_remainHeadacheCure += 1;
        }

        if (GetStomachache())
        {
            m_remainStomachacheCure += 1;
        }
    }
}

void StatusManager::PickPlant()
{
    // �g�̂̃X�^�~�i
    {
        float work = 0.f;
        work = GetBodyStaminaMaxSub();

        work -= 5.f;
        SetBodyStaminaMaxSub(work);

        work = GetBodyStaminaCurrent();

        work -= 10.f;
        SetBodyStaminaCurrent(work);
    }

    // �]�̃X�^�~�i
    {
        float work = 0.f;
        work = GetBrainStaminaMaxSub();

        work -= 5.f;
        SetBrainStaminaMaxSub(work);

        work = GetBrainStaminaCurrent();

        work -= 10.f;
        SetBrainStaminaCurrent(work);
    }

    // ����
    {
        float work = 0.f;
        work = GetWaterCurrent();

        work -= 1.f;
        SetWaterCurrent(work);
    }

    // ���̂̑���
    {
        auto work = GetMuscleCurrent();
        SetMuscleCurrent(work - 3.f);
    }
}

void StatusManager::PullOar()
{
    // �g�̂̃X�^�~�i
    {
        float work = 0.f;
        work = GetBodyStaminaMaxSub();

        work -= 0.01f;
        SetBodyStaminaMaxSub(work);

        work = GetBodyStaminaCurrent();

        work -= 0.02f;
        SetBodyStaminaCurrent(work);
    }

    // �]�̃X�^�~�i
    {
        float work = 0.f;
        work = GetBrainStaminaMaxSub();

        work -= 0.01f;
        SetBrainStaminaMaxSub(work);

        work = GetBrainStaminaCurrent();

        work -= 0.02f;
        SetBrainStaminaCurrent(work);
    }

    // ����
    {
        float work = 0.f;
        work = GetWaterCurrent();

        work -= 0.002f;
        SetWaterCurrent(work);
    }

    // ���̂̑���
    {
        auto work = GetMuscleCurrent();
        SetMuscleCurrent(work - 0.01f);
    }
}

void StatusManager::PullOarBoth()
{
    // �g�̂̃X�^�~�i
    {
        float work = 0.f;
        work = GetBodyStaminaMaxSub();

        work -= 0.02f;
        SetBodyStaminaMaxSub(work);

        work = GetBodyStaminaCurrent();

        work -= 0.04f;
        SetBodyStaminaCurrent(work);
    }

    // �]�̃X�^�~�i
    {
        float work = 0.f;
        work = GetBrainStaminaMaxSub();

        work -= 0.02f;
        SetBrainStaminaMaxSub(work);

        work = GetBrainStaminaCurrent();

        work -= 0.04f;
        SetBrainStaminaCurrent(work);
    }

    // ����
    {
        float work = 0.f;
        work = GetWaterCurrent();

        work -= 0.004f;
        SetWaterCurrent(work);
    }

    // ���̂̑���
    {
        auto work = GetMuscleCurrent();
        SetMuscleCurrent(work - 0.02f);
    }
}

void StatusManager::Voyage3Hours()
{
    // 10�b�Ɉ��I�[���𑆂��A��3���ԑ��������̂Ƃ���
    int count = 3600 * 3 / 10;
    for (int i = 0; i < count; ++i)
    {
        PullOarBoth();
    }
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
    // �]�̃X�^�~�i��0�ɂȂ�����C��
    if (arg < 0.f)
    {
        arg = 0.f;
        m_status.SetSleep(true);
    }
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
    if (arg < 0.f)
    {
        arg = 0.f;
        m_status.SetDead(true);
    }
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
    if (arg)
    {
        // ����̂�90��(�Q�[������180����)������B
        m_remainArmFracCure = 3600 * 2 * 180;
    }
    m_status.SetFractureArm(arg);
}

bool StatusManager::GetFractureLeg() const
{
    return m_status.GetFractureLeg();
}

void StatusManager::SetFractureLeg(bool arg)
{
    if (arg)
    {
        // ����̂�90��(�Q�[������180����)������B
        m_remainLegFracCure = 3600 * 2 * 180;
    }
    m_status.SetFractureLeg(arg);
}

bool StatusManager::GetHeadache() const
{
    return m_status.GetHeadache();
}

void StatusManager::SetHeadache(bool arg)
{
    if (arg)
    {
        // ����̂�1��(�Q�[������2����)������B
        m_remainHeadacheCure = 3600 * 2;
    }
    m_status.SetHeadache(arg);
}

bool StatusManager::GetCold() const
{
    return m_status.GetCold();
}

void StatusManager::SetCold(bool arg)
{
    if (arg)
    {
        // ����̂�5��(�Q�[������10����)������B
        m_remainColdCure = 3600 * 2 * 10;
    }
    m_status.SetCold(arg);
}

bool StatusManager::GetStomachache() const
{
    return m_status.GetStomachache();
}

void StatusManager::SetStomachache(bool arg)
{
    if (arg)
    {
        // ���ɂ͎���̂�1��(�Q�[������2����)������B
        m_remainStomachacheCure = 3600 * 2;
    }
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
    if (arg)
    {
        // ����̂�1��(�Q�[������2����)������B
        m_remainDehydration = 3600 * 2;
    }
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

void StatusManager::SetPlayerAction(const PlayerState arg)
{
    m_playerState = arg;
}

bool StatusManager::GetDead() const
{
    return m_status.GetDead();
}

void StatusManager::SetDead(const bool arg)
{
    m_status.SetDead(arg);
}

ItemInfo StatusManager::GetEquipWeapon() const
{
    return m_EquipWeapon;
}

void StatusManager::SetEquipWeapon(const ItemInfo& arg)
{
    m_EquipWeapon = arg;
}

eBagPos NSStarmanLib::StatusManager::EquipBag(const ItemInfo& bag)
{
    // �w���P�A�w���Q�A���A����A�E��̏��ő�������B

    eBagPos result = eBagPos::None;

    if (m_BagMap.at(eBagPos::Back1).GetId() == -1)
    {
        result = eBagPos::Back1;
    }
    else if (m_BagMap.at(eBagPos::Back2).GetId() == -1)
    {
        result = eBagPos::Back2;
    }
    else if (m_BagMap.at(eBagPos::Front).GetId() == -1)
    {
        result = eBagPos::Front;
    }
    else if (m_BagMap.at(eBagPos::Left).GetId() == -1)
    {
        result = eBagPos::Left;
    }
    else if (m_BagMap.at(eBagPos::Right).GetId() == -1)
    {
        result = eBagPos::Right;
    }

    if (result != eBagPos::None)
    {
        m_BagMap.at(result).SetId(bag.GetId());
        m_BagMap.at(result).SetSubId(bag.GetSubId());
        m_BagMap.at(result).SetDurabilityCurrent(bag.GetDurabilityCurrent());
    }


    // �ő�ύڗʂ̍Čv�Z
    Inventory::GetObj()->UpdateVolumeMax(GetAllBag());

    return result;
}

void NSStarmanLib::StatusManager::UnequipBag(const int id, const int subId)
{
    auto bagPos = GetBag(id, subId);
    UnequipBag(bagPos);
}

void NSStarmanLib::StatusManager::UnequipBag(const eBagPos bagPos)
{
    // �w�肵���ʒu�̑܂��O��
    //
    // ���̌�A�w���P�A�w���Q�A���A����A�E��̏��ő��������悤�ɁA������炷

    ItemInfo work = m_BagMap.at(bagPos);

    // �܂��A�܂��O��
    if (bagPos != eBagPos::None)
    {
        m_BagMap.at(bagPos).SetId(-1);
        m_BagMap.at(bagPos).SetSubId(-1);
        m_BagMap.at(bagPos).SetDurabilityCurrent(-1);
    }

    // ���ɁA�܂��ړ�
    // ������炷

    if (m_BagMap.at(eBagPos::Back1).GetId() == -1 &&
        m_BagMap.at(eBagPos::Back2).GetId() != -1)
    {
        m_BagMap.at(eBagPos::Back1) = m_BagMap.at(eBagPos::Back2);

        m_BagMap.at(eBagPos::Back2).SetId(-1);
        m_BagMap.at(eBagPos::Back2).SetSubId(-1);
        m_BagMap.at(eBagPos::Back2).SetDurabilityCurrent(-1);
    }

    if (m_BagMap.at(eBagPos::Back2).GetId() == -1 &&
        m_BagMap.at(eBagPos::Front).GetId() != -1)
    {
        m_BagMap.at(eBagPos::Back2) = m_BagMap.at(eBagPos::Front);

        m_BagMap.at(eBagPos::Front).SetId(-1);
        m_BagMap.at(eBagPos::Front).SetSubId(-1);
        m_BagMap.at(eBagPos::Front).SetDurabilityCurrent(-1);
    }

    if (m_BagMap.at(eBagPos::Front).GetId() == -1 &&
        m_BagMap.at(eBagPos::Left).GetId() != -1)
    {
        m_BagMap.at(eBagPos::Front) = m_BagMap.at(eBagPos::Left);

        m_BagMap.at(eBagPos::Left).SetId(-1);
        m_BagMap.at(eBagPos::Left).SetSubId(-1);
        m_BagMap.at(eBagPos::Left).SetDurabilityCurrent(-1);
    }

    if (m_BagMap.at(eBagPos::Left).GetId() == -1 &&
        m_BagMap.at(eBagPos::Right).GetId() != -1)
    {
        m_BagMap.at(eBagPos::Left) = m_BagMap.at(eBagPos::Right);

        m_BagMap.at(eBagPos::Right).SetId(-1);
        m_BagMap.at(eBagPos::Right).SetSubId(-1);
        m_BagMap.at(eBagPos::Right).SetDurabilityCurrent(-1);
    }

    // �ő�ύڗʂ̍Čv�Z
    Inventory::GetObj()->UpdateVolumeMax(GetAllBag());
}

ItemInfo NSStarmanLib::StatusManager::GetBag(const eBagPos bagPos) const
{
    return m_BagMap.at(bagPos);
}

NSStarmanLib::eBagPos NSStarmanLib::StatusManager::GetBag(const int id, const int subId) const
{
    eBagPos result = eBagPos::None;
    for (auto it = m_BagMap.begin(); it != m_BagMap.end(); ++it)
    {
        if (it->second.GetId() == id && it->second.GetSubId() == subId)
        {
            result = it->first;
        }
    }
    return result;
}

std::vector<ItemInfo> NSStarmanLib::StatusManager::GetAllBag()
{
    std::vector<ItemInfo> result;
    for (auto it = m_BagMap.begin(); it != m_BagMap.end(); ++it)
    {
        result.push_back(it->second);
    }
    return result;
}

std::vector<eBagPos> StatusManager::GetBagState()
{
    std::vector<eBagPos> result;

    if (m_BagMap.at(eBagPos::Back1).GetId() != -1)
    {
        result.push_back(eBagPos::Back1);
    }

    if (m_BagMap.at(eBagPos::Back2).GetId() != -1)
    {
        result.push_back(eBagPos::Back2);
    }

    if (m_BagMap.at(eBagPos::Front).GetId() != -1)
    {
        result.push_back(eBagPos::Front);
    }

    if (m_BagMap.at(eBagPos::Left).GetId() != -1)
    {
        result.push_back(eBagPos::Left);
    }

    if (m_BagMap.at(eBagPos::Right).GetId() != -1)
    {
        result.push_back(eBagPos::Right);
    }

    return result;
}

void NSStarmanLib::StatusManager::UpdateBagDurability()
{
    auto inventory = Inventory::GetObj();

    for (auto it = m_BagMap.begin(); it != m_BagMap.end(); ++it)
    {
        if (it->second.GetId() == -1)
        {
            continue;
        }

        // �܂��̂Ă��ꍇ�A�̂Ă��܂̑ϋv�l�͉����悤�Ƃ����
        // �C���x���g���ɑ��݂��Ȃ��̂ŗ�O���N���Ă��܂��B
        // ���݂��Ȃ��Ȃ�ϋv�l�������Ȃ�
        if (inventory->ExistItem(it->second.GetId(), it->second.GetSubId()))
        {
            auto itemInfo = inventory->GetItemInfo(it->second.GetId(), it->second.GetSubId());
            it->second.SetDurabilityCurrent(itemInfo.GetDurabilityCurrent());
        }
    }
}

void StatusManager::SetSuperStress()
{
    // �����X�g���X���������ꍇ�A�]�̗̑͂������ɂȂ�B���ݒn���ő�l�������ɂȂ�B
    float work = 0.f;
    work = GetBrainStaminaMax();
    work *= 0.5f;
    SetBrainStaminaMax(work);

    work = GetBrainStaminaMaxSub();
    work *= 0.5f;
    SetBrainStaminaMaxSub(work);

    work = GetBrainStaminaCurrent();
    work *= 0.5f;
    SetBrainStaminaCurrent(work);
}

void StatusManager::GetXYZ(float* x, float* y, float* z)
{
    *x = m_status.GetX();
    *y = m_status.GetY();
    *z = m_status.GetZ();
}

void StatusManager::SetMagicType(const eMagicType magicType)
{
    m_eMagicType = magicType;
}

eMagicType StatusManager::GetMagicType() const
{
    return m_eMagicType;
}

bool StatusManager::GetLevelUpFire()
{
    return m_levelUpFire;
}

bool StatusManager::GetLevelUpIce()
{
    return m_levelUpIce;
}

bool StatusManager::GetLevelUpDark()
{
    return m_levelUpDark;
}

bool StatusManager::GetLevelDownFire()
{
    return m_levelDownFire;
}

bool StatusManager::GetLevelDownIce()
{
    return m_levelDownIce;
}

bool StatusManager::GetLevelDownDark()
{
    return m_levelDownDark;
}

int StatusManager::GetLevelFire() const
{
    return m_levelFire;
}

int StatusManager::GetLevelIce() const
{
    return m_levelIce;
}

int StatusManager::GetLevelDark() const
{
    return m_levelDark;
}

