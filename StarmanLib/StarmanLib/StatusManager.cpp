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
        if (vvs.at(i).at(1) == "体のスタミナ（現在値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBodyStaminaCurrent(value);
        }
        else if (vvs.at(i).at(1) == "体のスタミナ（最大値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBodyStaminaMax(value);
        }
        else if (vvs.at(i).at(1) == "体のスタミナ（回復可能値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBodyStaminaMaxSub(value);
        }
        else if (vvs.at(i).at(1) == "脳のスタミナ（現在値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBrainStaminaCurrent(value);
        }
        else if (vvs.at(i).at(1) == "脳のスタミナ（最大値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBrainStaminaMax(value);
        }
        else if (vvs.at(i).at(1) == "脳のスタミナ（回復可能値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetBrainStaminaMaxSub(value);
        }
        else if (vvs.at(i).at(1) == "瞬発力")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetExplosivePower(value);
        }
        else if (vvs.at(i).at(1) == "肉体の修復度（現在値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetMuscleCurrent(value);
        }
        else if (vvs.at(i).at(1) == "肉体の修復度（最大値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetMuscleMax(value);
        }
        else if (vvs.at(i).at(1) == "糖質（現在値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetCarboCurrent(value);
        }
        else if (vvs.at(i).at(1) == "糖質（最大値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetCarboMax(value);
        }
        else if (vvs.at(i).at(1) == "タンパク質（現在値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetProteinCurrent(value);
        }
        else if (vvs.at(i).at(1) == "タンパク質（最大値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetProteinMax(value);
        }
        else if (vvs.at(i).at(1) == "脂質（現在値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetLipidCurrent(value);
        }
        else if (vvs.at(i).at(1) == "脂質（最大値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetLipidMax(value);
        }
        else if (vvs.at(i).at(1) == "ビタミン（現在値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetVitaminCurrent(value);
        }
        else if (vvs.at(i).at(1) == "ビタミン（最大値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetVitaminMax(value);
        }
        else if (vvs.at(i).at(1) == "ミネラル（現在値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetMineralCurrent(value);
        }
        else if (vvs.at(i).at(1) == "ミネラル（最大値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetMineralMax(value);
        }
        else if (vvs.at(i).at(1) == "水分（現在値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetWaterCurrent(value);
        }
        else if (vvs.at(i).at(1) == "水分（最大値）")
        {
            float value = std::stof(vvs.at(i).at(2));
            m_status.SetWaterMax(value);
        }
        else if (vvs.at(i).at(1) == "腕骨折")
        {
            if (vvs.at(i).at(2) == "○")
            {
                m_status.SetFractureArm(true);
            }
            else
            {
                m_status.SetFractureArm(false);
            }
        }
        else if (vvs.at(i).at(1) == "足骨折")
        {
            if (vvs.at(i).at(2) == "○")
            {
                m_status.SetFractureLeg(true);
            }
            else
            {
                m_status.SetFractureLeg(false);
            }
        }
        else if (vvs.at(i).at(1) == "頭痛")
        {
            if (vvs.at(i).at(2) == "○")
            {
                m_status.SetHeadache(true);
            }
            else
            {
                m_status.SetHeadache(false);
            }
        }
        else if (vvs.at(i).at(1) == "風邪")
        {
            if (vvs.at(i).at(2) == "○")
            {
                m_status.SetCold(true);
            }
            else
            {
                m_status.SetCold(false);
            }
        }
        else if (vvs.at(i).at(1) == "腹痛")
        {
            if (vvs.at(i).at(2) == "○")
            {
                m_status.SetStomachache(true);
            }
            else
            {
                m_status.SetStomachache(false);
            }
        }
        else if (vvs.at(i).at(1) == "睡眠")
        {
            if (vvs.at(i).at(2) == "○")
            {
                m_status.SetSleep(true);
            }
            else
            {
                m_status.SetSleep(false);
            }
        }
        else if (vvs.at(i).at(1) == "脱水症状")
        {
            if (vvs.at(i).at(2) == "○")
            {
                m_status.SetDehydration(true);
            }
            else
            {
                m_status.SetDehydration(false);
            }
        }
        else if (vvs.at(i).at(1) == "睡眠不足")
        {
            if (vvs.at(i).at(2) == "○")
            {
                m_status.SetLackOfSleep(true);
            }
            else
            {
                m_status.SetLackOfSleep(false);
            }
        }
        else if (vvs.at(i).at(1) == "装備武器ID")
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
        else if (vvs.at(i).at(1) == "装備武器SubID")
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
        else if (vvs.at(i).at(1) == "魔法の経験値（炎）")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_experienceFire = value;
        }
        else if (vvs.at(i).at(1) == "魔法の経験値（氷）")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_experienceIce = value;
        }
        else if (vvs.at(i).at(1) == "魔法の経験値（闇）")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_experienceDark = value;
        }
        else if (vvs.at(i).at(1) == "魔法のレベル（炎）")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_levelFire = value;
        }
        else if (vvs.at(i).at(1) == "魔法のレベル（氷）")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_levelIce = value;
        }
        else if (vvs.at(i).at(1) == "魔法のレベル（闇）")
        {
            int value = std::stoi(vvs.at(i).at(2));
            m_levelDark = value;
        }
        else if (vvs.at(i).at(1) == "背中の袋1ID")
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
        else if (vvs.at(i).at(1) == "背中の袋1SubID")
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
        else if (vvs.at(i).at(1) == "背中の袋2ID")
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
        else if (vvs.at(i).at(1) == "背中の袋2SubID")
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
        else if (vvs.at(i).at(1) == "腹の袋ID")
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
        else if (vvs.at(i).at(1) == "腹の袋SubID")
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
        else if (vvs.at(i).at(1) == "左手の袋ID")
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
        else if (vvs.at(i).at(1) == "左手の袋SubID")
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
        else if (vvs.at(i).at(1) == "右手の袋ID")
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
        else if (vvs.at(i).at(1) == "右手の袋SubID")
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
    // プレイヤーの状態により、徐々にスタミナが低下
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

        // 脳の体力が20％以下で座ると寝てしまう
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

        // 脳の体力が50％以下で横になると寝てしまう
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
    // 水分
    // 1％でも下がるとスタミナの下がりやすさが悪化する
    // 1％下がるたびにさらに悪化する
    // 水分が90％になると死亡する
    // 99％だったら0.9999をかける
    // 98％だったら0.9998をかける
    // 97％だったら0.9997をかける
    //------------------------------------
    float work1 = 0.f;
    float work2 = 0.f;
    float work3 = 0.f;
    work1 = m_status.GetWaterCurrent();
    work2 = m_status.GetWaterMax();

    // 現在が99で最大が100だったら0.99、を得る
    work3 = work1 / work2;

    if (work3 <= 0.90f)
    {
        m_status.SetDead(true);
    }

    // 0.99 を0.0099にする
    work3 /= 100;

    // 0.0099を0.9999にする
    work3 += 0.99f;

    bodyStaminaCurrent *= work3;

    //------------------------------------
    // 糖質
    // 不足していたら、スタミナの下がりやすさが悪化する
    // 40%を下回ったら0.9998倍
    // 20%になったら0.9996倍
    // 0%になっても餓死はしない。脂肪が消費される。脂肪も0なら餓死。
    // 80%以上あると
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
    // ビタミン
    // 不足していたら、スタミナの下がりやすさが悪化する
    // 40%を下回ったら0.9999倍
    // 20%になったら0.9998倍
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
    // ミネラル
    // 不足していたら、スタミナの下がりやすさが悪化する
    // 20%を下回ったら0.9999倍
    // 0%になったら0.9998倍
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
    // インベントリの重量
    // インベントリの重量によってスタミナの下がりやすさが悪化する
    // 0kgだったら1倍
    // 10kgだったら0.999倍
    // 100㎏だったら0.99倍
    // 1万を足して、1万をその数で割る
    // 例
    //   10kgだったら0.999倍
    //   10000 / (10 + 10000) = 0.999
    //------------------------------------
    {
        // 座っていたり、横になっていたら無視。
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
    // 計算結果をセット
    //-----------------------------------------

    // スタミナ消耗が速すぎるので1/10にしてみる
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

    // 死亡
    if (bodyStaminaCurrent <= 0.f)
    {
        m_status.SetDead(true);
    }

    //------------------------------------------------------
    // 体内の五大栄養素と水分を減らす
    //------------------------------------------------------
    // 一日何も食べなければ体内の糖質が0になってもおかしくはないはず。
    work1 = m_status.GetCarboCurrent();
    work1 -= 0.02f;
    m_status.SetCarboCurrent(work1);

    work1 = m_status.GetProteinCurrent();
    work1 -= 0.01f;
    m_status.SetProteinCurrent(work1);

    // 糖質がなくなったら脂肪が消費される
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
    // 朝8時になったらいくつかのステータスを更新
    //-----------------------------------------------------
    PowereggDateTime* dateTime = PowereggDateTime::GetObj();
    int currentDay = dateTime->GetDay();
    int currentHour = dateTime->GetHour();

    //--------------------------------------------------
    // 1. 前回が7時で今回が8時なら朝8時を越えている。
    // 2. 前回、7時で今回が1時の時、数字は小さくなっているが朝8時を越えている。
    // 3. 時刻が19時から20時になっていたら朝8時を越えたとはならないように思えるが
    //    日付が1日から2日に代わっていたら朝8時を越えている。
    // 一度に24時間以上、時が進むことはない予定
    //--------------------------------------------------

    // 日付が0なら処理しない
    if (m_previousDay != 0)
    {
        // 日付が変わっていないパターン
        if (m_previousDay == currentDay)
        {
            if (m_previousHour <= 7 && currentHour >= 8)
            {
                m_over8clock = true;
            }
        }
        // 日付が進んでいるパターン
        else if (m_previousDay < currentDay)
        {
            // 前回が7時より前なら8時をまたいでいる
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

        // 体のスタミナが70％以下になったことが一日に1度もなかったら
        // 体のスタミナの最大値が1％下がる
        // トレーニング不足
        if (m_training == false)
        {
            float work = GetBodyStaminaMax();
            work *= 0.99f;
            SetBodyStaminaMax(work);

            // 回復可能値が最大値を超えてはならない。
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
    // 契約して1年経過していたら死亡
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
    // 状態異常の治療
    // 時間経過でしか治らない。
    // 風邪：5日
    // 腕骨折・足骨折：90日
    // 頭痛・腹痛：1日（＝24時間）
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
        // 五大栄養素が半分以下の時は回復が止まる
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
        // 五大栄養素が半分以下の時は回復が止まる
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
    vs.push_back("ステータス名");
    vs.push_back("値");
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("1");
    vs.push_back("体のスタミナ（現在値）");
    work = std::to_string(m_status.GetBodyStaminaCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("2");
    vs.push_back("体のスタミナ（最大値）");
    work = std::to_string(m_status.GetBodyStaminaMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("3");
    vs.push_back("体のスタミナ（回復可能値）");
    work = std::to_string(m_status.GetBodyStaminaMaxSub());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("4");
    vs.push_back("脳のスタミナ（現在値）");
    work = std::to_string(m_status.GetBrainStaminaCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("5");
    vs.push_back("脳のスタミナ（最大値）");
    work = std::to_string(m_status.GetBrainStaminaMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("6");
    vs.push_back("脳のスタミナ（回復可能値）");
    work = std::to_string(m_status.GetBrainStaminaMaxSub());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("7");
    vs.push_back("瞬発力");
    work = std::to_string(m_status.GetExplosivePower());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("8");
    vs.push_back("肉体の修復度（現在値）");
    work = std::to_string(m_status.GetMuscleCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("9");
    vs.push_back("肉体の修復度（最大値）");
    work = std::to_string(m_status.GetMuscleMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("10");
    vs.push_back("糖質（現在値）");
    work = std::to_string(m_status.GetCarboCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("11");
    vs.push_back("糖質（最大値）");
    work = std::to_string(m_status.GetCarboMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("12");
    vs.push_back("タンパク質（現在値）");
    work = std::to_string(m_status.GetProteinCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("13");
    vs.push_back("タンパク質（最大値）");
    work = std::to_string(m_status.GetProteinMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("14");
    vs.push_back("脂質（現在値）");
    work = std::to_string(m_status.GetLipidCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("15");
    vs.push_back("脂質（最大値）");
    work = std::to_string(m_status.GetLipidMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("16");
    vs.push_back("ビタミン（現在値）");
    work = std::to_string(m_status.GetVitaminCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("17");
    vs.push_back("ビタミン（最大値）");
    work = std::to_string(m_status.GetVitaminMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("18");
    vs.push_back("ミネラル（現在値）");
    work = std::to_string(m_status.GetMineralCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("19");
    vs.push_back("ミネラル（最大値）");
    work = std::to_string(m_status.GetMineralMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("20");
    vs.push_back("水分（現在値）");
    work = std::to_string(m_status.GetWaterCurrent());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("21");
    vs.push_back("水分（最大値）");
    work = std::to_string(m_status.GetWaterMax());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("22");
    vs.push_back("腕骨折");
    if (m_status.GetFractureArm())
    {
        vs.push_back("○");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("23");
    vs.push_back("足骨折");
    if (m_status.GetFractureLeg())
    {
        vs.push_back("○");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("24");
    vs.push_back("頭痛");
    if (m_status.GetHeadache())
    {
        vs.push_back("○");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("25");
    vs.push_back("風邪");
    if (m_status.GetCold())
    {
        vs.push_back("○");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("26");
    vs.push_back("腹痛");
    if (m_status.GetStomachache())
    {
        vs.push_back("○");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("27");
    vs.push_back("睡眠");
    if (m_status.GetSleep())
    {
        vs.push_back("○");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("28");
    vs.push_back("脱水症状");
    if (m_status.GetDehydration())
    {
        vs.push_back("○");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("29");
    vs.push_back("睡眠不足");
    if (m_status.GetLackOfSleep())
    {
        vs.push_back("○");
    }
    else
    {
        vs.push_back("");
    }
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("30");
    vs.push_back("装備武器ID");
    work = std::to_string(GetEquipWeapon().GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("31");
    vs.push_back("装備武器SubID");
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
    vs.push_back("魔法の経験値（炎）");
    work = std::to_string(m_experienceFire);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("36");
    vs.push_back("魔法の経験値（氷）");
    work = std::to_string(m_experienceIce);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("37");
    vs.push_back("魔法の経験値（闇）");
    work = std::to_string(m_experienceDark);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("38");
    vs.push_back("魔法のレベル（炎）");
    work = std::to_string(m_levelFire);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("39");
    vs.push_back("魔法のレベル（氷）");
    work = std::to_string(m_levelIce);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("40");
    vs.push_back("魔法のレベル（闇）");
    work = std::to_string(m_levelDark);
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("41");
    vs.push_back("背中の袋1ID");
    work = std::to_string(m_BagMap.at(eBagPos::Back1).GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("42");
    vs.push_back("背中の袋1SubID");
    work = std::to_string(m_BagMap.at(eBagPos::Back1).GetSubId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("43");
    vs.push_back("背中の袋2ID");
    work = std::to_string(m_BagMap.at(eBagPos::Back2).GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("44");
    vs.push_back("背中の袋2SubID");
    work = std::to_string(m_BagMap.at(eBagPos::Back2).GetSubId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("45");
    vs.push_back("腹の袋ID");
    work = std::to_string(m_BagMap.at(eBagPos::Front).GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("46");
    vs.push_back("腹の袋SubID");
    work = std::to_string(m_BagMap.at(eBagPos::Front).GetSubId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("47");
    vs.push_back("左手の袋ID");
    work = std::to_string(m_BagMap.at(eBagPos::Left).GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("48");
    vs.push_back("左手の袋SubID");
    work = std::to_string(m_BagMap.at(eBagPos::Left).GetSubId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("49");
    vs.push_back("右手の袋ID");
    work = std::to_string(m_BagMap.at(eBagPos::Right).GetId());
    vs.push_back(work);
    vvs.push_back(vs);

    vs.clear();
    vs.push_back("50");
    vs.push_back("右手の袋SubID");
    work = std::to_string(m_BagMap.at(eBagPos::Right).GetSubId());
    vs.push_back(work);
    vvs.push_back(vs);

    Util::WriteToCsv(csvfile, vvs, encrypt);
}

float StatusManager::GetWalkSpeed()
{
    // 最大積載量を超えていたら歩くことができない
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

    // 体のスタミナが10％以下になると移動速度が1/10になる。
    if (m_status.GetBodyStaminaCurrent() < m_status.GetBodyStaminaMax() * 0.5f)
    {
        walkSpeed *= 0.1f;
    }
    // 体のスタミナが50％以下になると移動速度が半分になる。
    else if (m_status.GetBodyStaminaCurrent() < m_status.GetBodyStaminaMax() * 0.5f)
    {
        walkSpeed *= 0.5f;
    }

    // 瞬発力が高ければ歩くのが早くなる
    // 100だったら1.0倍。110だったら1.1倍
    work = m_status.GetExplosivePower();
    walkSpeed *= work / 100;

    // インベントリの重量によって歩行速度を遅くする
    // 反比例の式にしたいので
    // 10足して10を重量(kg)で割る。
    // 0kgだったら1倍
    // 10kgだったら0.5倍
    // 100㎏だったら約0.1倍
    // 10000㎏だったら約0.01倍
    Inventory* inventory = Inventory::GetObj();
    float weight = inventory->GetWeight();
    work = (weight + 10) / 10;
    walkSpeed *= work;

    // 足を骨折していたら移動速度が90％ダウン（＝0.1倍になる）
    work_b = m_status.GetFractureLeg();
    if (work_b)
    {
        walkSpeed *= 0.1f;
    }

    // 微調整
    walkSpeed *= 3.f;

    return walkSpeed;
}

float StatusManager::GetAttackPower()
{
    float result = 0.f;
    float work = 0.0;

    // -1だったら武器を装備していない
    auto inventory = Inventory::GetObj();
    if (m_EquipWeapon.GetId() != -1)
    {
        auto itemManager = ItemManager::GetObj();
        auto itemDef = itemManager->GetItemDef(m_EquipWeapon.GetId());
        auto weaponName = itemDef.GetName();
        auto weaponManager = WeaponManager::GetObj();
        auto itemInfo = inventory->GetItemInfo(m_EquipWeapon.GetId(), m_EquipWeapon.GetSubId());

        // 装備中の武器の攻撃力
        double attackRate = weaponManager->GetAttackRate(weaponName, itemDef.GetLevel());
        result = (float)attackRate;

        // 耐久度が0だったら攻撃力は1になる
        if (itemInfo.GetDurabilityCurrent() == 0)
        {
            result = 1.f;
        }
    }
    else
    {
        result = 1.f;
    }

    // 瞬発力
    work = m_status.GetExplosivePower();
    result *= work;

    // 脳のスタミナ
    // 10%減っていたら1%攻撃力を下げる。
    // 20%減っていたら2%攻撃力を下げる。
    work = m_status.GetBrainStaminaCurrent() / m_status.GetBrainStaminaMax();
    work = (1.0f - work) / 10;
    result *= (1.0f - work);

    // 水分
    // 1%減っていたら1%攻撃力を下げる。
    // 2%減っていたら2%攻撃力を下げる。
    work = m_status.GetWaterCurrent() / m_status.GetWaterMax();
    result *= work;

    // 重量
    // インベントリの重量によって攻撃力が低下する
    // 0kgだったら1倍
    // 10kgだったら0.9倍
    // 100㎏だったら0倍
    //------------------------------------
    float weight = inventory->GetWeight();
    work = (1.f - (weight / 100.0f));
    if (work < 0.f)
    {
        work = 0.f;
    }
    result *= work;

    // 肉体の修復度
    work = m_status.GetMuscleCurrent() / m_status.GetMuscleMax();
    result *= work;

    // 腕の骨が折れていたら90％ダウン（＝0.1倍になる）
    if (m_status.GetFractureArm())
    {
        result *= 0.1f;
    }

    // 足の骨が折れていたら90％ダウン（＝0.1倍になる）
    if (m_status.GetFractureLeg())
    {
        result *= 0.1f;
    }

    // 風邪の場合、50％ダウン
    if (m_status.GetCold())
    {
        result *= 0.5f;
    }

    // 脱水症状の場合、50％ダウン
    if (m_status.GetDehydration())
    {
        result *= 0.5f;
    }

    // 頭痛の場合、50％ダウン
    if (m_status.GetHeadache())
    {
        result *= 0.5f;
    }

    // 腹痛の場合、50％ダウン
    if (m_status.GetStomachache())
    {
        result *= 0.5f;
    }

    // 左手に袋を持っていたら攻撃力が半減する
    if (GetBag(eBagPos::Left).GetId() != -1)
    {
        result *= 0.5f;
    }

    // 攻撃力がマイナス、はありえない。
    if (result < 0.f)
    {
        result = 0.f;
    }

    return result;
}

void StatusManager::ConsumeAttackCost()
{
    //--------------------------------
    // 消耗
    // 武器の耐久度、スタミナ、その他、全部消耗する
    //--------------------------------

    int work_i = 0;
    float work_f = 0;

    // 武器の耐久度
    if (m_EquipWeapon.GetId() != -1)
    {
        auto inventory = Inventory::GetObj();
        auto itemInfo = inventory->GetItemInfo(m_EquipWeapon.GetId(), m_EquipWeapon.GetSubId());
        work_i = itemInfo.GetDurabilityCurrent();
        --work_i;
        itemInfo.SetDurabilityCurrent(work_i);
    }

    // 水分
    work_f = m_status.GetWaterCurrent();
    m_status.SetWaterCurrent(work_f - 0.01f);

    // 身体のスタミナ
    work_f = m_status.GetBodyStaminaCurrent();
    m_status.SetBodyStaminaCurrent(work_f - 0.01f);

    // 肉体の修復度
    work_f = m_status.GetMuscleCurrent();
    if (m_EquipWeapon.GetId() != -1)
    {
        m_status.SetMuscleCurrent(work_f - 0.01f);
    }
    // 素手だったら猛烈に消耗する
    else
    {
        m_status.SetMuscleCurrent(work_f - 0.05f);
    }

    //---------------------------------------------
    // 状態異常を悪化
    //---------------------------------------------

    // 風邪
    if (m_status.GetCold())
    {
        ++m_remainColdCure;
    }

    // 腕の骨折
    if (m_status.GetFractureArm())
    {
        ++m_remainArmFracCure;
    }

    // 足の骨折
    if (m_status.GetFractureLeg())
    {
        ++m_remainLegFracCure;
    }

    // 脱水症状
    if (m_status.GetDehydration())
    {
        ++m_remainDehydration;
    }

    // 頭痛
    if (m_status.GetHeadache())
    {
        ++m_remainHeadacheCure;
    }

    // 腹痛
    if (m_status.GetStomachache())
    {
        ++m_remainStomachacheCure;
    }
}

float StatusManager::GetDefensePower()
{
    // TODO
    // 敵の攻撃力、主人公の瞬発力など
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

    // 糖質が100だったら満腹であるとしてこれ以上食べられない。
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

// TODO なんか変
bool StatusManager::Sleep()
{
    PowereggDateTime* dateTime = PowereggDateTime::GetObj();

    // 仮眠か睡眠か
    // 脳の体力が50％以下で横になったor脳の体力が20％以下で座ったなら何時でも寝てしまう。
    // このとき、0時だったら睡眠、それより前だったら仮眠になる。
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
            // 睡眠不足でもなく、トレーニングもしていないなら
            // 7~23時の間に寝ようとしても寝ることができない。
            if (m_training == false &&
                m_status.GetLackOfSleep() == false)
            {
                return false;
            }
        }
    }

    // 五大栄養素と水分を消費
    {
        float work1 = 0.f;
        float work2 = 0.f;

        // 糖質
        work1 = GetCarboCurrent();
        work1 *= 0.8f;
        work1 -= 5.f;
        if (work1 < 0.f)
        {
            // 糖質が0なら、脂質が減る
            work2 = work1;
            work1 = 0.f;
        }
        SetCarboCurrent(work1);

        // タンパク質
        work1 = GetProteinCurrent();
        work1 *= 0.8f;
        work1 -= 5.f;
        if (work1 < 0.f)
        {
            work1 = 0.f;
        }
        SetProteinCurrent(work1);

        // 脂質
        work1 = GetLipidCurrent();
        work1 += work2;
        if (work1 < 0.f)
        {
            work1 = 0.f;
        }
        SetLipidCurrent(work1);

        // ビタミン
        work1 = GetVitaminCurrent();
        work1 *= 0.8f;
        work1 -= 5.f;
        if (work1 < 0.f)
        {
            work1 = 0.f;
        }
        SetVitaminCurrent(work1);

        // ミネラル
        work1 = GetMineralCurrent();
        work1 *= 0.8f;
        work1 -= 5.f;
        if (work1 < 0.f)
        {
            work1 = 0.f;
        }
        SetMineralCurrent(work1);

        // 水分
        work1 = GetWaterCurrent();
        work1 -= 0.5f;
        if (work1 < 0.f)
        {
            work1 = 0.f;
        }
        SetWaterCurrent(work1);
    }

    // 睡眠（仮眠ではない）
    if (nap == false)
    {
        // 脳の体力は寝たら全快する。
        // 寝るのが遅かったら回復量が50％に制限される
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
        // 寝る時間が遅かったら
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

        // 体のスタミナは寝たら寝不足でも全快する
        work1 = GetBodyStaminaMax();
        SetBodyStaminaMaxSub(work1);
        SetBodyStaminaCurrent(work1);

        // 肉体の修復度
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

        // 魔法レベルアップの初期化
        {
            m_levelUpFire = false;
            m_levelUpIce = false;
            m_levelUpDark = false;

            m_levelDownFire = false;
            m_levelDownIce = false;
            m_levelDownDark = false;
        }

        // 経験値の低下
        {
            m_experienceFire -= 10;
            m_experienceIce -= 10;
            m_experienceDark -= 10;
        }

        // 魔法レベルの上昇
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

        // 魔法のレベルダウン
        {
            if (m_experienceFire < 0)
            {
                // -5だったら95にする
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
                // -5だったら95にする
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
                // -5だったら95にする
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

        // 時間を7時間進める
        dateTime->IncreaseDateTime(0, 0, 7, 0, 0);
    }
    // 仮眠
    else if (nap)
    {
        // 脳のスタミナは寝たら全快する。
        float work = 0.f;
        float work2 = 0.f;
        work = GetBrainStaminaMax();
        SetBrainStaminaMaxSub(work);
        SetBrainStaminaCurrent(work);

        // 体のスタミナは寝たら全快する
        work = GetBodyStaminaMax();
        SetBodyStaminaMaxSub(work);
        SetBodyStaminaCurrent(work);

        // 肉体の修復度
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

        // 時間を90分進める
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
    // 武器の種類や強化値によってスタミナ消耗が変わるようにする
    //------------------------------------------------------

    float magni = 0.f;

    if (weapon == "縦長の石")
    {
        magni = 1.f;
    }
    else if (weapon == "石斧")
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

    // 身体のスタミナ
    {
        float work = 0.f;
        work = GetBodyStaminaMaxSub();

        work -= 15.f * magni;
        SetBodyStaminaMaxSub(work);

        work = GetBodyStaminaCurrent();

        work -= 30.f * magni;
        SetBodyStaminaCurrent(work);
    }

    // 脳のスタミナ
    {
        float work = 0.f;
        work = GetBrainStaminaMaxSub();

        work -= 20.f * magni;
        SetBrainStaminaMaxSub(work);

        work = GetBrainStaminaCurrent();

        work -= 40.f * magni;
        SetBrainStaminaCurrent(work);
    }

    // 水分
    {
        float work = 0.f;
        work = GetWaterCurrent();

        work -= 5.f * magni;
        SetWaterCurrent(work);
    }

    // 肉体の損傷
    {
        auto work = GetMuscleCurrent();
        if (weapon == "縦長の石")
        {
            SetMuscleCurrent(work - (20.f * magni));
        }
        else
        {
            SetMuscleCurrent(work - (15.f * magni));
        }
    }

    // 状態異常の悪化
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
    // 身体のスタミナ
    {
        float work = 0.f;
        work = GetBodyStaminaMaxSub();

        work -= 5.f;
        SetBodyStaminaMaxSub(work);

        work = GetBodyStaminaCurrent();

        work -= 10.f;
        SetBodyStaminaCurrent(work);
    }

    // 脳のスタミナ
    {
        float work = 0.f;
        work = GetBrainStaminaMaxSub();

        work -= 5.f;
        SetBrainStaminaMaxSub(work);

        work = GetBrainStaminaCurrent();

        work -= 10.f;
        SetBrainStaminaCurrent(work);
    }

    // 水分
    {
        float work = 0.f;
        work = GetWaterCurrent();

        work -= 1.f;
        SetWaterCurrent(work);
    }

    // 肉体の損傷
    {
        auto work = GetMuscleCurrent();
        SetMuscleCurrent(work - 3.f);
    }
}

void StatusManager::PullOar()
{
    // 身体のスタミナ
    {
        float work = 0.f;
        work = GetBodyStaminaMaxSub();

        work -= 0.01f;
        SetBodyStaminaMaxSub(work);

        work = GetBodyStaminaCurrent();

        work -= 0.02f;
        SetBodyStaminaCurrent(work);
    }

    // 脳のスタミナ
    {
        float work = 0.f;
        work = GetBrainStaminaMaxSub();

        work -= 0.01f;
        SetBrainStaminaMaxSub(work);

        work = GetBrainStaminaCurrent();

        work -= 0.02f;
        SetBrainStaminaCurrent(work);
    }

    // 水分
    {
        float work = 0.f;
        work = GetWaterCurrent();

        work -= 0.002f;
        SetWaterCurrent(work);
    }

    // 肉体の損傷
    {
        auto work = GetMuscleCurrent();
        SetMuscleCurrent(work - 0.01f);
    }
}

void StatusManager::PullOarBoth()
{
    // 身体のスタミナ
    {
        float work = 0.f;
        work = GetBodyStaminaMaxSub();

        work -= 0.02f;
        SetBodyStaminaMaxSub(work);

        work = GetBodyStaminaCurrent();

        work -= 0.04f;
        SetBodyStaminaCurrent(work);
    }

    // 脳のスタミナ
    {
        float work = 0.f;
        work = GetBrainStaminaMaxSub();

        work -= 0.02f;
        SetBrainStaminaMaxSub(work);

        work = GetBrainStaminaCurrent();

        work -= 0.04f;
        SetBrainStaminaCurrent(work);
    }

    // 水分
    {
        float work = 0.f;
        work = GetWaterCurrent();

        work -= 0.004f;
        SetWaterCurrent(work);
    }

    // 肉体の損傷
    {
        auto work = GetMuscleCurrent();
        SetMuscleCurrent(work - 0.02f);
    }
}

void StatusManager::Voyage3Hours()
{
    // 10秒に一回オールを漕ぐ、を3時間続けたものとする
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
    // 脳のスタミナが0になったら気絶
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
        // 治るのに90日(ゲーム内で180時間)かかる。
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
        // 治るのに90日(ゲーム内で180時間)かかる。
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
        // 治るのに1日(ゲーム内で2時間)かかる。
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
        // 治るのに5日(ゲーム内で10時間)かかる。
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
        // 腹痛は治るのに1日(ゲーム内で2時間)かかる。
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
        // 治るのに1日(ゲーム内で2時間)かかる。
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
    // 背中１、背中２、腹、左手、右手の順で装備する。

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


    // 最大積載量の再計算
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
    // 指定した位置の袋を外す
    //
    // その後、背中１、背中２、腹、左手、右手の順で装備されるように、一個ずつずらす

    ItemInfo work = m_BagMap.at(bagPos);

    // まず、袋を外す
    if (bagPos != eBagPos::None)
    {
        m_BagMap.at(bagPos).SetId(-1);
        m_BagMap.at(bagPos).SetSubId(-1);
        m_BagMap.at(bagPos).SetDurabilityCurrent(-1);
    }

    // 次に、袋を移動
    // 一個ずつずらす

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

    // 最大積載量の再計算
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

        // 袋を捨てた場合、捨てた袋の耐久値は下げようとすると
        // インベントリに存在しないので例外が起きてしまう。
        // 存在しないなら耐久値を下げない
        if (inventory->ExistItem(it->second.GetId(), it->second.GetSubId()))
        {
            auto itemInfo = inventory->GetItemInfo(it->second.GetId(), it->second.GetSubId());
            it->second.SetDurabilityCurrent(itemInfo.GetDurabilityCurrent());
        }
    }
}

void StatusManager::SetSuperStress()
{
    // 強いストレスがあった場合、脳の体力が半分になる。現在地も最大値も半分になる。
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

