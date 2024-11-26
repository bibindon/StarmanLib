#include "CraftSystem.h"
#include "HeaderOnlyCsv.hpp"
#include "PowereggDateTime.h"
#include "Inventory.h"
#include "ItemManager.h"

using namespace NSStarmanLib;

CraftSystem* CraftSystem::obj { nullptr };

CraftSystem* CraftSystem::GetObj()
{
    if (obj == nullptr)
    {
        obj = new CraftSystem();
    }
    return obj;
}

void CraftSystem::Destroy()
{
    delete CraftSystem::obj;
    CraftSystem::obj = nullptr;
}

void CraftSystem::Init(const std::string& csvfileSkill, const std::string& csvfileQueue)
{
    std::vector<std::vector<std::string> > vss;
    vss = csv::Read(csvfileSkill);

    for (std::size_t i = 1; i < vss.size(); ++i)
    {
        CraftSkill craftSkill;

        std::string name = vss.at(i).at(0);
        craftSkill.SetName(name);

        int level = std::stoi(vss.at(i).at(1));
        craftSkill.SetLevel(level);

        if (vss.at(i).at(2) == "○")
        {
            craftSkill.SetEnable(true);
        }
        else
        {
            craftSkill.SetEnable(false);
        }
    }
}

void NSStarmanLib::CraftSystem::Save(const std::string& csvfileSkill,
                                     const std::string& csvfileQueue)
{
    std::vector<std::vector<std::string>> vss;
    std::vector<std::string> vs;

    vs.push_back("クラフトアイテム");
    vs.push_back("強化値");
    vs.push_back("クラフト可能");
    vss.push_back(vs);
    vs.clear();

    for (auto it = m_craftSkillList.begin(); it != m_craftSkillList.end(); ++it)
    {
        vs.push_back(it->GetName());
        if (it->GetLevel() != -1)
        {
            vs.push_back(std::to_string(it->GetLevel()));
        }
        else
        {
            vs.push_back("");
        }

        if (it->GetEnable())
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
    csv::Write(csvfileSkill, vss);
}

void NSStarmanLib::CraftSystem::SetCraftsmanSkill(const std::string& craftItem, const int level)
{
    CraftSkill craftSkill;
    craftSkill.SetName(craftItem);
    craftSkill.SetLevel(level);
    craftSkill.SetEnable(true);
    m_craftSkillList.push_back(craftSkill);
}

bool NSStarmanLib::CraftSystem::GetCraftsmanSkill(const std::string& craftItem, const int level)
{
    bool result = false;
    for (auto it = m_craftSkillList.begin(); it != m_craftSkillList.end(); ++it)
    {
        if (it->GetName() == craftItem && it->GetLevel() == level)
        {
            result = it->GetEnable();
            break;
        }
    }
    return result;
}

bool NSStarmanLib::CraftSystem::QueueCraftRequest(const std::string& craftItem, const int level)
{
    // 予約は5回まで
    if (m_craftRequestList.size() >= 4)
    {
        return false;
    }

    CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();

    // クラフト情報を得るにはクラフト成果物を渡す必要があるため
    // まずはクラフト成果物を用意する
    CraftOutput craftOutput;

    craftOutput.SetName(craftItem);
    craftOutput.SetLevel(level);
    craftOutput.SetNumber(1);

    // 用意したクラフト成果物でクラフト情報を得る
    CraftInfo craftInfo = craftInfoManager->GetCraftInfo(craftOutput);

    // 素材を消費する
    // 素材が足りないときはfalseを返す
    ItemManager* itemManager = ItemManager::GetObj();
    std::vector<CraftMaterial> craftMaterialList = craftInfo.GetCraftMaterial();

    Inventory* inventory = Inventory::GetObj();

    for (std::size_t i = 0; i < craftMaterialList.size(); ++i)
    {
        std::string name;
        int materialId = 0;
        int materialNum = 0;
        int materialLevel = 0;

        name = craftMaterialList.at(i).GetName();
        materialNum = craftMaterialList.at(i).GetNumber();
        materialLevel = craftMaterialList.at(i).GetLevel();

        // 素材の必要数分削除する
        for (int j = 0; j < materialNum; ++j)
        {
            inventory->RemoveItem(name, materialLevel);
        }
    }

    // クラフト中のアイテム情報
    CraftRequest craftingItem;

    // 作りたいものをセット
    // クラフト開始時間とクラフト完了時間はここでは設定しない（クラフト要求はキューイング出来るため）
    craftingItem.SetCraftInfo(craftInfo);
    craftingItem.SetCrafting(false);

    m_craftRequestList.push_back(craftingItem);

    return true;
}

bool NSStarmanLib::CraftSystem::CancelCraftStart(const int index)
{
    if ((int)m_craftRequestList.size() <= index)
    {
        return false;
    }
    m_craftRequestList.erase(std::next(m_craftRequestList.begin(), index));
    return true;
}

void NSStarmanLib::CraftSystem::UpdateCraftStatus()
{
    // リクエストがないならやることなし
    if (m_craftRequestList.size() == 0)
    {
        return;
    }

    // クラフトリクエストの先頭がクラフト中ならばやることなし
    if (m_craftRequestList.front().GetCrafting())
    {
        return;
    }

    // クラフトリクエストの先頭がクラフト中でないならば、クラフトを開始する
    if (m_craftRequestList.front().GetCrafting() == false)
    {
        m_craftRequestList.front().SetCrafting(true);

        // パワーエッグ星での現在時刻とクラフト完了時刻を設定する
        PowereggDateTime* obj = PowereggDateTime::GetObj();
        m_craftRequestList.front().SetStartYear(obj->GetYear());
        m_craftRequestList.front().SetStartMonth(obj->GetMonth());
        m_craftRequestList.front().SetStartDay(obj->GetDay());
        m_craftRequestList.front().SetStartHour(obj->GetHour());
        m_craftRequestList.front().SetStartMinute(obj->GetMinute());
        m_craftRequestList.front().SetStartSecond(obj->GetSecond());

        // 完了時刻は24時間後。
        // 完了時刻をアイテムごとに変えるのは難しくないのでやっても良いような気がする
        // 1月32日や13月は存在しないので、その対応を行うために
        // 秒、分、時、というように細かいほうから設定していく
        m_craftRequestList.front().SetfinishSecond(obj->GetSecond());
        m_craftRequestList.front().SetfinishMinute(obj->GetMinute());
        m_craftRequestList.front().SetfinishHour(obj->GetHour());

        // 1月31日とか2月28日のような月末でないならば日数に＋１する。
        if (obj->GetDay() < obj->DAY_OF_MONTH(obj->GetMonth()))
        {
            m_craftRequestList.front().SetfinishDay(obj->GetDay() + 1);
            m_craftRequestList.front().SetfinishMonth(obj->GetMonth());
            m_craftRequestList.front().SetfinishYear(obj->GetYear());
        }
        // 月末ならば日数を1日にする
        else
        {
            m_craftRequestList.front().SetfinishDay(1);

            // 月数を+1する
            // 13月にならないように注意する
            if (obj->GetMonth() != 12)
            {
                m_craftRequestList.front().SetfinishMonth(obj->GetMonth() + 1);
                m_craftRequestList.front().SetfinishYear(obj->GetYear());
            }
            // 12月ならば、完了日を翌年の1月にする
            else if (obj->GetMonth() == 12)
            {
                m_craftRequestList.front().SetfinishMonth(1);
                m_craftRequestList.front().SetfinishYear(obj->GetYear() + 1);
            }
        }

    }
}

std::string CraftRequest::GetName() const
{
    return m_name;
}

void CraftRequest::SetName(std::string mname)
{
    m_name = mname;
}

int CraftRequest::GetStartYear() const
{
    return m_startYear;
}

void CraftRequest::SetStartYear(int startYear)
{
    m_startYear = startYear;
}

int CraftRequest::GetStartMonth() const
{
    return m_startMonth;
}

void CraftRequest::SetStartMonth(int startMonth)
{
    m_startMonth = startMonth;
}

int CraftRequest::GetStartDay() const
{
    return m_startDay;
}

void CraftRequest::SetStartDay(int startDay)
{
    m_startDay = startDay;
}

int CraftRequest::GetStartHour() const
{
    return m_startHour;
}

void CraftRequest::SetStartHour(int startHour)
{
    m_startHour = startHour;
}

int CraftRequest::GetStartMinute() const
{
    return m_startMinute;
}

void CraftRequest::SetStartMinute(int startMinute)
{
    m_startMinute = startMinute;
}

int CraftRequest::GetStartSecond() const
{
    return m_startSecond;
}

void CraftRequest::SetStartSecond(int startSecond)
{
    m_startSecond = startSecond;
}

int CraftRequest::GetfinishYear() const
{
    return m_finishYear;
}

void CraftRequest::SetfinishYear(int mfinishYear)
{
    m_finishYear = mfinishYear;
}

int CraftRequest::GetfinishMonth() const
{
    return m_finishMonth;
}

void CraftRequest::SetfinishMonth(int mfinishMonth)
{
    m_finishMonth = mfinishMonth;
}

int CraftRequest::GetfinishDay() const
{
    return m_finishDay;
}

void CraftRequest::SetfinishDay(int mfinishDay)
{
    m_finishDay = mfinishDay;
}

int CraftRequest::GetfinishHour() const
{
    return m_finishHour;
}

void CraftRequest::SetfinishHour(int mfinishHour)
{
    m_finishHour = mfinishHour;
}

int CraftRequest::GetfinishMinute() const
{
    return m_finishMinute;
}

void CraftRequest::SetfinishMinute(int mfinishMinute)
{
    m_finishMinute = mfinishMinute;
}

int CraftRequest::GetfinishSecond() const
{
    return m_finishSecond;
}

void CraftRequest::SetfinishSecond(int mfinishSecond)
{
    m_finishSecond = mfinishSecond;
}

CraftInfo NSStarmanLib::CraftRequest::GetCraftInfo() const
{
    return m_craftInfo;
}

void NSStarmanLib::CraftRequest::SetCraftInfo(const CraftInfo& arg)
{
    m_craftInfo = arg;
}

bool NSStarmanLib::CraftRequest::GetCrafting() const
{
    return m_crafting;
}

void NSStarmanLib::CraftRequest::SetCrafting(const bool arg)
{
    m_crafting = arg;
}

void NSStarmanLib::CraftSkill::SetName(const std::string& arg)
{
    m_name = arg;
}

std::string NSStarmanLib::CraftSkill::GetName() const
{
    return m_name;
}

void NSStarmanLib::CraftSkill::SetLevel(const int arg)
{
    m_level = arg;
}

int NSStarmanLib::CraftSkill::GetLevel() const
{
    return m_level;
}

void NSStarmanLib::CraftSkill::SetEnable(const bool arg)
{
    m_enable = arg;
}

bool NSStarmanLib::CraftSkill::GetEnable() const
{
    return m_enable;
}
