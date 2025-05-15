#include "Help.h"

#include "Util.h"
#include "PowereggDateTime.h"
#include "CraftSystem.h"
#include "NpcStatusManager.h"

#include <time.h>
#include <cassert>

using namespace NSStarmanLib;

Help* Help::m_obj = nullptr;

Help* NSStarmanLib::Help::Get()
{
    if (m_obj == nullptr)
    {
        m_obj = new Help();
    }
    return m_obj;
}

void NSStarmanLib::Help::Destroy()
{
    delete m_obj;
    m_obj = nullptr;
}

void NSStarmanLib::Help::Init(const std::string& filepath)
{
    assert(ItemManager::GetObj()->Inited());

    // 拾ってよいアイテムのリスト
    // 3,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,25,33,34,35,38,39,40,41,42,
    // 54, 55, 56, 57
    m_enableItemIdList.clear();
    m_enableItemIdList.push_back(3);
    m_enableItemIdList.push_back(5);
    m_enableItemIdList.push_back(6);
    m_enableItemIdList.push_back(7);
    m_enableItemIdList.push_back(8);
    m_enableItemIdList.push_back(9);
    m_enableItemIdList.push_back(11);
    m_enableItemIdList.push_back(12);
    m_enableItemIdList.push_back(13);
    m_enableItemIdList.push_back(14);
    m_enableItemIdList.push_back(15);
    m_enableItemIdList.push_back(16);
    m_enableItemIdList.push_back(17);
    m_enableItemIdList.push_back(18);
    m_enableItemIdList.push_back(19);
    m_enableItemIdList.push_back(20);
    m_enableItemIdList.push_back(21);
    m_enableItemIdList.push_back(22);
    m_enableItemIdList.push_back(23);
    m_enableItemIdList.push_back(25);
    m_enableItemIdList.push_back(33);
    m_enableItemIdList.push_back(34);
    m_enableItemIdList.push_back(35);
    m_enableItemIdList.push_back(38);
    m_enableItemIdList.push_back(39);
    m_enableItemIdList.push_back(40);
    m_enableItemIdList.push_back(41);
    m_enableItemIdList.push_back(42);
    m_enableItemIdList.push_back(54);
    m_enableItemIdList.push_back(55);
    m_enableItemIdList.push_back(56);
    m_enableItemIdList.push_back(57);

	m_presentMap["sankakuman"] = std::vector<ItemDef>();
	m_presentMap["shikakuman"] = std::vector<ItemDef>();
	
	m_presented["sankakuman"] = false;
	m_presented["shikakuman"] = false;

    std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(filepath, false);

    auto itemManager = ItemManager::GetObj();

    for (int i = 1; i < vvs.size(); ++i)
    {
        auto name = vvs.at(i).at(0);
        for (int j = 1; j < vvs.at(i).size(); ++j)
        {
            if (vvs.at(i).at(j).empty())
            {
                break;
            }

            int itemId = std::stoi(vvs.at(i).at(j));
            auto itemDef = itemManager->GetItemDef(itemId);
            m_presentMap.at(name).push_back(itemDef);
        }
    }

    m_bLoaded = true;
}

// TODO NPCの健康状態を考慮
void NSStarmanLib::Help::Update()
{
    auto datetime = PowereggDateTime::GetObj();

    // 時が巻き戻っていたら回収アイテムをクリアする
    bool backtime = BackTime();

    if (backtime)
    {
        for (auto& x : m_presented)
        {
            x.second = false;
        }

        for (auto& x : m_presentMap)
        {
            x.second.clear();
        }

        m_previousYear = datetime->GetYear();
        m_previousMonth = datetime->GetMonth();
        m_previousDay = datetime->GetDay();
        m_previousHour = datetime->GetHour();
        return;
    }

    auto crossOver = CrossOver16();

    if (crossOver)
    {
        // イカダをクラフトしているならアイテム収集はナシ。
        auto request = CraftSystem::GetObj()->GetCraftRequestList();
        if (request.empty() || request.front().GetName() != "イカダ")
        {
            srand((unsigned int)time(NULL));

            for (auto& x : m_presentMap)
            {
                // アイテムをランダムに10個以下で選択
                auto items = GetRandomItem(x.first);

                // 受け取らずに翌日の16時になったら新しいアイテムになり、古いものは消失
                x.second = items;

                m_presented.at(x.first) = false;
            }
        }
        else
        {
            for (auto& x : m_presentMap)
            {
                x.second.clear();
                m_presented.at(x.first) = false;
            }
        }
    }

    m_previousYear = datetime->GetYear();
    m_previousMonth = datetime->GetMonth();
    m_previousDay = datetime->GetDay();
    m_previousHour = datetime->GetHour();
}

void NSStarmanLib::Help::Save(const std::string& filepath)
{
    // m_presentMapの内容を出力
    std::vector<std::vector<std::string>> vvs;
    std::vector<std::string> vs;
    int work = 0;

    vs.push_back("名前");
    vs.push_back("アイテム1");
    vs.push_back("アイテム2");
    vs.push_back("アイテム3");
    vs.push_back("アイテム4");
    vs.push_back("アイテム5");
    vs.push_back("アイテム6");
    vs.push_back("アイテム7");
    vs.push_back("アイテム8");
    vs.push_back("アイテム9");
    vs.push_back("アイテム10");
    vvs.push_back(vs);
    vs.clear();

    for (auto& helper : m_presentMap)
    {
        vs.push_back(helper.first);
        for (auto& item : helper.second)
        {
            auto id = item.GetId();
            vs.push_back(std::to_string(id));
        }
        vvs.push_back(vs);
        vs.clear();
    }

    Util::WriteToCsv(filepath, vvs, false);
}

std::vector<ItemDef> NSStarmanLib::Help::ReceiveItems(const std::string& npcName)
{
    // イカダをクラフトしていたらアイテム収集はナシ。
    auto request = CraftSystem::GetObj()->GetCraftRequestList();
    if (!request.empty() && request.front().GetName() == "イカダ")
    {
        m_presentMap.at(npcName).clear();
    }

    auto present = m_presentMap.at(npcName);

    m_presentMap.at(npcName).clear();
    m_presented.at(npcName) = true;

    return present;
}

bool NSStarmanLib::Help::Received(const std::string& npcName)
{
    // 空だったら渡した後。
    auto received = m_presentMap.at(npcName).empty();
    return received;
}

bool NSStarmanLib::Help::CanReceive(const std::string& npcName)
{
    if (!m_bLoaded)
    {
        return false;
    }

    // 渡した後、もしくは一つもないなら受け取り出来ない。
    auto empty = m_presentMap.at(npcName).empty();
    if (empty)
    {
        return false;
    }

    auto presented = m_presented.at(npcName);
    if (presented)
    {
        return false;
    }

    auto request = CraftSystem::GetObj()->GetCraftRequestList();
    if (!request.empty() && request.front().GetName() == "イカダ")
    {
        m_presentMap.at(npcName).clear();
        return false;
    }

    return true;
}

std::vector<ItemDef> NSStarmanLib::Help::GetRandomItem(const std::string& npcName)
{
    int rnd = 0;
    int work = 0;

    // 個数をランダムで決める(1~10)
    int itemNum = 1;
    {
        // TODO 一番低い栄養素をもとに最大取得個数を求める
        auto carbo = NpcStatusManager::GetObj()->GetNpcStatus(npcName).GetCarbo();

        int maxNum = (int)(carbo / 10);

        if (maxNum != 0)
        {
            rnd = rand();
            work = rnd % maxNum + 1;
        }
        else
        {
            work = 1;
        }

        itemNum = work;
    }

    // アイテムをランダムで決める
    std::vector<ItemDef> randomItem;
    {
        auto idListNum = m_enableItemIdList.size();

        for (int i = 0; i < itemNum; ++i)
        {
            rnd = rand();
            work = rnd % idListNum;
            int id = m_enableItemIdList.at(work);
            auto itemDef = ItemManager::GetObj()->GetItemDef(id);
            randomItem.push_back(itemDef);
        }
    }

    return randomItem;
}

bool NSStarmanLib::Help::CrossOver16()
{
    auto datetime = PowereggDateTime::GetObj();
    bool crossOver = false;

    if (datetime->GetYear() > m_previousYear)
    {
        crossOver = true;
    }
    else if (datetime->GetYear() == m_previousYear)
    {
        if (datetime->GetMonth() > m_previousMonth)
        {
            crossOver = true;
        }
        else if (datetime->GetMonth() == m_previousMonth)
        {
            if (datetime->GetDay() > m_previousDay)
            {
                crossOver = true;
            }
            else if (datetime->GetDay() == m_previousDay)
            {
                if (datetime->GetHour() >= 16)
                {
                    if (m_previousHour < 16)
                    {
                        crossOver = true;
                    }
                }
            }
        }
    }

    return crossOver;
}

bool NSStarmanLib::Help::BackTime()
{
    auto datetime = PowereggDateTime::GetObj();
    bool backtime = false;

    if (datetime->GetYear() < m_previousYear)
    {
        backtime = true;
    }
    else if (datetime->GetYear() == m_previousYear)
    {
        if (datetime->GetMonth() < m_previousMonth)
        {
            backtime = true;
        }
        else if (datetime->GetMonth() == m_previousMonth)
        {
            if (datetime->GetDay() < m_previousDay)
            {
                backtime = true;
            }
            else if (datetime->GetDay() == m_previousDay)
            {
                if (datetime->GetHour() < m_previousHour)
                {
                    backtime = true;
                }
            }
        }
    }

    return backtime;
}
