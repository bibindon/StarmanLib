#include "CraftSystem.h"
#include "PowereggDateTime.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Storehouse.h"
#include "Util.h"
#include "Voyage.h"

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

void CraftSystem::Init(const std::string& csvfileSkill, const std::string& csvfileQueue,
                       const bool decrypt)
{
    // CraftSystemのInit関数より先に、CraftInfoManagerのInitが呼ばれている必要がある。
    {
        CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
        if (craftInfoManager->Inited() == false)
        {
            throw std::exception();
        }
    }

    {
        std::vector<std::vector<std::string> > vvs = Util::ReadFromCsv(csvfileSkill, decrypt);

        if (vvs.empty())
        {
            throw std::exception();
        }

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            CraftSkill craftSkill;

            std::string name = vvs.at(i).at(0);
            craftSkill.SetName(name);

            int level = 0;
            if (vvs.at(i).at(1).empty())
            {
                level = -1;
            }
            else
            {
                level = std::stoi(vvs.at(i).at(1));
            }
            craftSkill.SetLevel(level);

            if (vvs.at(i).at(2) == "○")
            {
                craftSkill.SetEnable(true);
            }
            else
            {
                craftSkill.SetEnable(false);
            }

            int work = 0;
            if (vvs.at(i).at(3).empty())
            {
                work = -1;
            }
            else
            {
                work = std::stoi(vvs.at(i).at(3));
            }
            craftSkill.SetLevelUpNecessity(work);

            if (vvs.at(i).at(4).empty())
            {
                work = -1;
            }
            else
            {
                work = std::stoi(vvs.at(i).at(4));
            }
            craftSkill.SetSuccessNum(work);

            m_craftSkillList.push_back(craftSkill);
        }
    }
    {
        std::vector<std::vector<std::string> > vvs = Util::ReadFromCsv(csvfileQueue, decrypt);

        if (vvs.empty())
        {
            throw std::exception();
        }

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();

            std::string name = vvs.at(i).at(0);

            int level = 0;

            if (vvs.at(i).at(1).empty())
            {
                level = -1;
            }
            else
            {
                level = std::stoi(vvs.at(i).at(1));
            }

            // クラフト情報を取得
            CraftInfo craftInfo = craftInfoManager->GetCraftInfo(name, 1, level);

            // クラフト中のアイテム情報
            CraftRequest craftRequest;

            craftRequest.SetCraftInfo(craftInfo);

            if (vvs.at(i).at(2) == "○")
            {
                craftRequest.SetCrafting(true);
            }
            else
            {
                craftRequest.SetCrafting(false);
            }

            if (craftRequest.GetCrafting())
            {
                craftRequest.SetStartYear(std::stoi(vvs.at(i).at(3)));
                craftRequest.SetStartMonth(std::stoi(vvs.at(i).at(4)));
                craftRequest.SetStartDay(std::stoi(vvs.at(i).at(5)));
                craftRequest.SetStartHour(std::stoi(vvs.at(i).at(6)));
                craftRequest.SetStartMinute(std::stoi(vvs.at(i).at(7)));
                craftRequest.SetStartSecond(std::stoi(vvs.at(i).at(8)));

                craftRequest.SetFinishYear(std::stoi(vvs.at(i).at(9)));
                craftRequest.SetFinishMonth(std::stoi(vvs.at(i).at(10)));
                craftRequest.SetFinishDay(std::stoi(vvs.at(i).at(11)));
                craftRequest.SetFinishHour(std::stoi(vvs.at(i).at(12)));
                craftRequest.SetFinishMinute(std::stoi(vvs.at(i).at(13)));
                craftRequest.SetFinishSecond(std::stoi(vvs.at(i).at(14)));
            }
            else
            {
                craftRequest.SetStartYear(-1);
                craftRequest.SetStartMonth(-1);
                craftRequest.SetStartDay(-1);
                craftRequest.SetStartHour(-1);
                craftRequest.SetStartMinute(-1);
                craftRequest.SetStartSecond(-1);

                craftRequest.SetFinishYear(-1);
                craftRequest.SetFinishMonth(-1);
                craftRequest.SetFinishDay(-1);
                craftRequest.SetFinishHour(-1);
                craftRequest.SetFinishMinute(-1);
                craftRequest.SetFinishSecond(-1);
            }

            craftRequest.SetStorehouseId(std::stoi(vvs.at(i).at(15)));

            m_craftRequestList.push_back(craftRequest);
        }
    }
}

void NSStarmanLib::CraftSystem::Save(const std::string& csvfileSkill,
                                     const std::string& csvfileQueue,
                                     const bool encrypt)
{
    {
        std::vector<std::vector<std::string>> vvs;
        std::vector<std::string> vs;

        vs.push_back("クラフトアイテム");
        vs.push_back("強化値");
        vs.push_back("クラフト可能");
        vs.push_back("次のレベルを習得するのに必要なクラフト回数");
        vs.push_back("現在のクラフト経験回数");
        vvs.push_back(vs);
        vs.clear();

        for (auto it = m_craftSkillList.begin(); it != m_craftSkillList.end(); ++it)
        {
            vs.push_back(it->GetName());
            if (it->GetLevel() == -1)
            {
                vs.push_back("");
            }
            else
            {
                vs.push_back(std::to_string(it->GetLevel()));
            }

            if (it->GetEnable())
            {
                vs.push_back("○");
            }
            else
            {
                vs.push_back("");
            }

            if (it->GetLevelUpNecessity() == -1)
            {
                vs.push_back("");
            }
            else
            {
                vs.push_back(std::to_string(it->GetLevelUpNecessity()));
            }

            if (it->GetSuccessNum() == -1)
            {
                throw std::exception();
            }
            else
            {
                vs.push_back(std::to_string(it->GetSuccessNum()));
            }

            vvs.push_back(vs);
            vs.clear();
        }

        Util::WriteToCsv(csvfileSkill, vvs, encrypt);
    }
    {
        std::vector<std::vector<std::string>> vvs;
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
        vs.push_back("収納先倉庫ID");
        vvs.push_back(vs);
        vs.clear();

        for (auto it = m_craftRequestList.begin(); it != m_craftRequestList.end(); ++it)
        {
            vs.push_back(it->GetName());

            int level = it->GetCraftInfo().GetOutput().GetLevel();
            if (level != -1)
            {
                vs.push_back(std::to_string(level));
            }
            else
            {
                vs.push_back("");
            }

            if (it->GetCrafting())
            {
                vs.push_back("○");
            }
            else
            {
                vs.push_back("");
            }

            if (it->GetCrafting())
            {
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
            }
            else
            {
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");

                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
            }

            vs.push_back(std::to_string(it->GetStorehouseId()));

            vvs.push_back(vs);
            vs.clear();
        }

        Util::WriteToCsv(csvfileQueue, vvs, encrypt);
    }
}

void NSStarmanLib::CraftSystem::SetCraftsmanSkill(const std::string& craftItem, const int level)
{
    auto it = std::find_if(m_craftSkillList.begin(), m_craftSkillList.end(),
                           [&](CraftSkill& x)
                           {
                               return x.GetName() == craftItem && x.GetLevel() == level;
                           });

    if (it != m_craftSkillList.end())
    {
        it->SetEnable(true);
    }
}

int NSStarmanLib::CraftSystem::GetCraftsmanSkill(const std::string& craftItem)
{
    // ＋１の石斧と＋２の石斧が作れて、＋３の石斧が作れないなら2を返す。
    // （craftItemの作れるアイテムの中で最高レベルの数値を返す。）
    int level = -1;
    for (auto it = m_craftSkillList.begin(); it != m_craftSkillList.end(); ++it)
    {
        if (it->GetName() == craftItem && it->GetEnable())
        {
            if (it->GetLevel() > level)
            {
                level = it->GetLevel();
            }
        }
    }
    return level;
}

bool NSStarmanLib::CraftSystem::QueueCraftRequest(const std::string& craftItem,
                                                  const int storehouseId)
{
    // 予約は5件まで
    if (m_craftRequestList.size() >= 4)
    {
        return false;
    }

    CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();

    // 現在、職人が作れるcraftItemのレベルを取得
    // ＋１の石斧と＋２の石斧が作れて、＋３の石斧が作れないなら2を取得。
    int level = GetCraftsmanSkill(craftItem);

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
    // クラフト要求はキューイングされるため、一見、この時点で素材を削除する必要はないように思える。
    // しかし、実際にクラフトが開始されたときにアイテムを削除する、というやり方にすると、
    // 非常に難解なプログラムを書く必要がある。そのため、この時点で素材は削除することにする。
    for (std::size_t i = 0; i < craftMaterialList.size(); ++i)
    {
        std::string name;
        int materialNum = 0;
        int materialLevel = 0;

        name = craftMaterialList.at(i).GetName();
        materialNum = craftMaterialList.at(i).GetNumber();
        materialLevel = craftMaterialList.at(i).GetLevel();

        // 素材の必要数分削除する
        // subIdは数値が若いものから順に使う

        std::vector<int> subIdList = inventory->GetSubIdList(craftMaterialList.at(i).GetId());
        for (int j = 0; j < materialNum; ++j)
        {
            inventory->RemoveItem(name, subIdList.at(i), materialLevel);
        }
    }

    // クラフト中のアイテム情報
    CraftRequest craftRequest;

    // 作りたいものをセット
    // クラフト開始時間とクラフト完了時間はここでは設定しない（クラフト要求はキューイング出来るため）
    craftRequest.SetCraftInfo(craftInfo);
    craftRequest.SetCrafting(false);

    // 完成した際の格納先の倉庫
    craftRequest.SetStorehouseId(storehouseId);

    m_craftRequestList.push_back(craftRequest);

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

    // クラフトリクエストの先頭がクラフト中でないならば、クラフトを開始する
    if (m_craftRequestList.front().GetCrafting() == false)
    {
        StartCraft();
    }
    // クラフトリクエストの先頭がクラフト中ならばクラフト完了でないか確認する
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

            int storehouseId = m_craftRequestList.front().GetStorehouseId();
            Storehouse* storehouse = StorehouseManager::Get()->GetStorehouse(storehouseId);

            for (int i = 0; i < output.GetNumber(); ++i)
            {
                // イカダの場合は倉庫に入れない。
                if (output.GetName() == "イカダ")
                {
                    auto voyage = Voyage::Get();
                    Raft raft;
                    // TODO イカダの座標はどこを設定する？
                    // raft.SetXYZ();
                    auto itemManager = ItemManager::GetObj();
                    auto itemDef = itemManager->GetItemDef(output.GetName(), output.GetLevel());

                    auto dura = itemDef.GetDurabilityMax();
                    raft.SetDurability(dura);

                    // TODO イカダの場所タイプはどこを設定する？
                    // raft.SetPosType();

                    auto storehouseList = StorehouseManager::Get()->GetStorehouseIdList();
                    raft.SetStorehouseId(storehouseList.size());

                    voyage->AddRaft(raft);
                }
                else
                {
                    storehouse->AddItem(output.GetName(), output.GetLevel());
                }
            }

            // 職人の熟練度の更新
            // 強化値なしの袋を2回作ったら、次は強化値＋１の袋を作れるようになる。
            // そのため作った回数を記録する
            bool levelup = false;
            for (std::size_t i = 0; i < m_craftSkillList.size(); ++i)
            {
                if (output.GetName() == m_craftSkillList.at(i).GetName() &&
                    output.GetLevel() == m_craftSkillList.at(i).GetLevel())
                {
                    int successNum = m_craftSkillList.at(i).GetSuccessNum();
                    ++successNum;
                    m_craftSkillList.at(i).SetSuccessNum(successNum);

                    // レベルアップ判定
                    // 規定回数、クラフトに成功していたら次の強化値のクラフトを可能にする
                    if (m_craftSkillList.at(i).GetLevelUpNecessity() <= successNum)
                    {
                        levelup = true;
                    }
                    break;
                }
            }

            // レベルアップ処理
            // まず、強化値が一つ上のクラフトが存在するかを調べる。
            if (levelup)
            {
                // 強化が+1~+5で可能の場合、強化値は-1, 1, 2, 3, 4, 5の6通りとなる。
                // 0が含まれないことに注意。
                int targetSkill = -1;
                bool targetSkillExist = false;
                if (output.GetLevel() == -1)
                {
                    targetSkill = 1;
                }
                else if (output.GetLevel() >= 1)
                {
                    targetSkill = output.GetLevel() + 1;
                }
                else
                {
                    throw std::exception();
                }

                std::size_t targetSkillIndex = 0;
                for (std::size_t i = 0; i < m_craftSkillList.size(); ++i)
                {

                    if (output.GetName() == m_craftSkillList.at(i).GetName() &&
                        targetSkill      == m_craftSkillList.at(i).GetLevel())
                    {
                        targetSkillExist = true;
                        targetSkillIndex = i;
                        break;
                    }
                }

                // 存在するならクラフト可能に変更する
                if (targetSkillExist)
                {
                    if (m_craftSkillList.at(targetSkillIndex).GetEnable() == false)
                    {
                        m_craftSkillList.at(targetSkillIndex).SetEnable(true);
                    }
                }
            }


            // 先頭の要素をリクエストのリストから削除
            m_craftRequestList.pop_front();

            // 予約リストが０ではないなら、新たに戦闘の要素となったリクエストをクラフト開始
            if (m_craftRequestList.size() >= 1)
            {
                StartCraft();
            }
        }
    }
}

void NSStarmanLib::CraftSystem::StartCraft()
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

int NSStarmanLib::CraftSystem::GetProgress()
{
    if (m_craftRequestList.front().GetCrafting() == false)
    {
        return -1;
    }

    // 24時間で完成なので1時間で4%上昇させる。分・秒は考えない。
    // 経過時間
    int elapsedHour = 0;

    PowereggDateTime* obj = PowereggDateTime::GetObj();
    int currentHour = obj->GetHour();
    int finishHour = m_craftRequestList.front().GetFinishHour();
    if (currentHour > finishHour)
    {
        elapsedHour = currentHour - finishHour;
    }
    // 現在時刻が0時を超えたら24を足してから引く
    else
    {
        elapsedHour = (currentHour+24) - finishHour;
    }
    return elapsedHour * 100 / 24;
}

std::list<CraftRequest> NSStarmanLib::CraftSystem::GetCraftRequestList()
{
    return m_craftRequestList;
}

std::string CraftRequest::GetName() const
{
    return m_craftInfo.GetOutput().GetName();
}

int NSStarmanLib::CraftRequest::GetLevel() const
{
    return m_craftInfo.GetOutput().GetLevel();
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

int NSStarmanLib::CraftRequest::GetStorehouseId() const
{
    return m_storehouseId;
}

void NSStarmanLib::CraftRequest::SetStorehouseId(const int id)
{
    m_storehouseId = id;
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

void NSStarmanLib::CraftSkill::SetLevelUpNecessity(const int arg)
{
    m_levelUpNecessity = arg;
}

int NSStarmanLib::CraftSkill::GetLevelUpNecessity() const
{
    return m_levelUpNecessity;
}

void NSStarmanLib::CraftSkill::SetSuccessNum(const int arg)
{
    m_successNum = arg;
}

int NSStarmanLib::CraftSkill::GetSuccessNum() const
{
    return m_successNum;
}

