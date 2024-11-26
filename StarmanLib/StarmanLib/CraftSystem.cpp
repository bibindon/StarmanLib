#include "CraftSystem.h"
#include "HeaderOnlyCsv.hpp"
#include "PowereggDateTime.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Storehouse.h"

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
    {
        std::vector<std::vector<std::string> > vss;
        vss = csv::Read(csvfileQueue);

        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();

            std::string name = vss.at(i).at(0);
            int level = std::stoi(vss.at(i).at(1));

            // クラフト情報を取得
            CraftInfo craftInfo = craftInfoManager->GetCraftInfo(name, 1, level);

            // クラフト中のアイテム情報
            CraftRequest craftRequest;

            craftRequest.SetCraftInfo(craftInfo);

            if (vss.at(i).at(2) == "○")
            {
                craftRequest.SetCrafting(true);
            }
            else
            {
                craftRequest.SetCrafting(false);
            }

            craftRequest.SetStartYear(std::stoi(vss.at(i).at(3)));
            craftRequest.SetStartMonth(std::stoi(vss.at(i).at(4)));
            craftRequest.SetStartDay(std::stoi(vss.at(i).at(5)));
            craftRequest.SetStartHour(std::stoi(vss.at(i).at(6)));
            craftRequest.SetStartMinute(std::stoi(vss.at(i).at(7)));
            craftRequest.SetStartSecond(std::stoi(vss.at(i).at(8)));

            craftRequest.SetFinishYear(std::stoi(vss.at(i).at(9)));
            craftRequest.SetFinishMonth(std::stoi(vss.at(i).at(10)));
            craftRequest.SetFinishDay(std::stoi(vss.at(i).at(11)));
            craftRequest.SetFinishHour(std::stoi(vss.at(i).at(12)));
            craftRequest.SetFinishMinute(std::stoi(vss.at(i).at(13)));
            craftRequest.SetFinishSecond(std::stoi(vss.at(i).at(14)));

            m_craftRequestList.push_back(craftRequest);
        }
    }
}

void NSStarmanLib::CraftSystem::Save(const std::string& csvfileSkill,
                                     const std::string& csvfileQueue)
{
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
    {
        std::vector<std::vector<std::string>> vss;
        std::vector<std::string> vs;

        vs.push_back("クラフトアイテム");
        vs.push_back("強化値");
        vs.push_back("クラフト中");
        vs.push_back("開始年");
        vs.push_back("開始月");
        vs.push_back("開始日");
        vs.push_back("開始時");
        vs.push_back("開始分");
        vs.push_back("開始秒");
        vs.push_back("完了年");
        vs.push_back("完了月");
        vs.push_back("完了日");
        vs.push_back("完了時");
        vs.push_back("完了分");
        vs.push_back("完了秒");
        vss.push_back(vs);
        vs.clear();

        for (auto it = m_craftRequestList.begin(); it != m_craftRequestList.end(); ++it)
        {
            vs.push_back(it->GetName());
            vs.push_back(std::to_string(it->GetCraftInfo().GetOutput().GetLevel()));

            if (it->GetCrafting())
            {
                vs.push_back("○");
            }
            else
            {
                vs.push_back("");
            }

            vs.push_back(std::to_string(it->GetStartYear()));
            vs.push_back(std::to_string(it->GetStartMonth()));
            vs.push_back(std::to_string(it->GetStartDay()));
            vs.push_back(std::to_string(it->GetStartHour()));
            vs.push_back(std::to_string(it->GetStartMinute()));
            vs.push_back(std::to_string(it->GetStartSecond()));

            vs.push_back(std::to_string(it->GetFinishYear()));
            vs.push_back(std::to_string(it->GetFinishMonth()));
            vs.push_back(std::to_string(it->GetFinishDay()));
            vs.push_back(std::to_string(it->GetFinishHour()));
            vs.push_back(std::to_string(it->GetFinishMinute()));
            vs.push_back(std::to_string(it->GetFinishSecond()));

            vss.push_back(vs);
            vs.clear();
        }
        csv::Write(csvfileQueue, vss);
    }
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

    // クラフト情報
    CraftInfo craftInfo = craftInfoManager->GetCraftInfo(craftItem, 1, level);

    // 素材を消費する
    // 素材が足りないときはfalseを返す
    ItemManager* itemManager = ItemManager::GetObj();
    std::vector<CraftMaterial> craftMaterialList = craftInfo.GetCraftMaterial();

    Inventory* inventory = Inventory::GetObj();
    bool materialShortage = false;

    // インベントリ内に必要なだけの素材があるかのチェック
    for (std::size_t i = 0; i < craftMaterialList.size(); ++i)
    {
        std::string name;
        int materialNum = 0;
        int materialLevel = 0;

        name = craftMaterialList.at(i).GetName();
        materialNum = craftMaterialList.at(i).GetNumber();
        materialLevel = craftMaterialList.at(i).GetLevel();

        int materialNumCurrent = inventory->CountItem(name, materialLevel);

        // 素材が足りない
        if (materialNumCurrent < materialNum)
        {
            materialShortage = true;
            break;
        }
    }

    if (materialShortage)
    {
        return false;
    }

    // インベントリ内の素材を削除
    for (std::size_t i = 0; i < craftMaterialList.size(); ++i)
    {
        std::string name;
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
        m_craftRequestList.front().SetFinishSecond(obj->GetSecond());
        m_craftRequestList.front().SetFinishMinute(obj->GetMinute());
        m_craftRequestList.front().SetFinishHour(obj->GetHour());

        // 1月31日とか2月28日のような月末でないならば日数に＋１する。
        if (obj->GetDay() < obj->DAY_OF_MONTH(obj->GetMonth()))
        {
            m_craftRequestList.front().SetFinishDay(obj->GetDay() + 1);
            m_craftRequestList.front().SetFinishMonth(obj->GetMonth());
            m_craftRequestList.front().SetFinishYear(obj->GetYear());
        }
        // 月末ならば日数を1日にする
        else
        {
            m_craftRequestList.front().SetFinishDay(1);

            // 月数を+1する
            // 13月にならないように注意する
            if (obj->GetMonth() != 12)
            {
                m_craftRequestList.front().SetFinishMonth(obj->GetMonth() + 1);
                m_craftRequestList.front().SetFinishYear(obj->GetYear());
            }
            // 12月ならば、完了日を翌年の1月にする
            else if (obj->GetMonth() == 12)
            {
                m_craftRequestList.front().SetFinishMonth(1);
                m_craftRequestList.front().SetFinishYear(obj->GetYear() + 1);
            }
        }
    }
    // クラフト中ならばクラフト完了でないか確認する
    else if (m_craftRequestList.front().GetCrafting())
    {

        // 日付同士の比較
        // 1年2月3日4時5分6秒と6年5月4日3時2分1秒のどちらが未来・過去かを判定するには
        // 010203040506 と 060504030201 という12桁の数値と見なして12桁の数値同士の比較を行えばよい
        int y1, M1, d1, h1, m1, s1;
        int y2, M2, d2, h2, m2, s2;

        y1 = m_craftRequestList.front().GetFinishYear();
        M1 = m_craftRequestList.front().GetFinishMonth();
        d1 = m_craftRequestList.front().GetFinishDay();
        h1 = m_craftRequestList.front().GetFinishHour();
        m1 = m_craftRequestList.front().GetFinishMinute();
        s1 = m_craftRequestList.front().GetFinishSecond();

        PowereggDateTime* obj = PowereggDateTime::GetObj();
        y2 = obj->GetYear();
        M2 = obj->GetMonth();
        d2 = obj->GetDay();
        h2 = obj->GetHour();
        m2 = obj->GetMinute();
        s2 = obj->GetSecond();

        bool fromPastToFuture = PowereggDateTime::FromPastToFuture(y1, M1, d1, h1, m1, s1, 
                                                                   y2, M2, d2, h2, m2, s2);

        // 作業完了時刻よりも現在時刻新しい、ことは完成していることを意味する
        if (fromPastToFuture)
        {
            // 完成したアイテムを倉庫に配置する
            CraftOutput output = m_craftRequestList.front().GetCraftInfo().GetOutput();
            Storehouse* storehouse = Storehouse::GetObj();
            for (int i = 0; i < output.GetNumber(); ++i)
            {
                storehouse->AddItem(output.GetName(), output.GetLevel());
            }

            // 先頭の要素をリクエストのリストから削除
            m_craftRequestList.pop_front();
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

int CraftRequest::GetFinishYear() const
{
    return m_finishYear;
}

void CraftRequest::SetFinishYear(int mfinishYear)
{
    m_finishYear = mfinishYear;
}

int CraftRequest::GetFinishMonth() const
{
    return m_finishMonth;
}

void CraftRequest::SetFinishMonth(int mfinishMonth)
{
    m_finishMonth = mfinishMonth;
}

int CraftRequest::GetFinishDay() const
{
    return m_finishDay;
}

void CraftRequest::SetFinishDay(int mfinishDay)
{
    m_finishDay = mfinishDay;
}

int CraftRequest::GetFinishHour() const
{
    return m_finishHour;
}

void CraftRequest::SetFinishHour(int mfinishHour)
{
    m_finishHour = mfinishHour;
}

int CraftRequest::GetFinishMinute() const
{
    return m_finishMinute;
}

void CraftRequest::SetFinishMinute(int mfinishMinute)
{
    m_finishMinute = mfinishMinute;
}

int CraftRequest::GetFinishSecond() const
{
    return m_finishSecond;
}

void CraftRequest::SetFinishSecond(int mfinishSecond)
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
