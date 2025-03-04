#include "Voyage.h"
#include "Inventory.h"
#include "StatusManager.h"
#include "PowereggDateTime.h"
#include "Util.h"

using namespace NSStarmanLib;

Voyage* Voyage::m_single = nullptr;

Voyage* Voyage::Get()
{
    if (m_single == nullptr)
    {
        m_single = new Voyage();
    }

    return m_single;
}

void Voyage::Init(const std::string& csvVoyage, const std::string& csvRaft)
{
    {
        std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvVoyage, false);

        if (vvs.at(0).at(1) == "y")
        {
            m_bRaftMode = true;
        }
        else if (vvs.at(0).at(1) == "n")
        {
            m_bRaftMode = false;
        }
        else
        {
            throw std::exception();
        }

        int raftId = -1;

        if (!vvs.at(1).at(1).empty())
        {
            raftId = std::stoi(vvs.at(1).at(1));
        }

        m_currentRaftId = raftId;
    }

    {
        if (csvRaft.empty())
        {
            return;
        }

        std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvRaft, false);
        for (size_t i = 1; i < vvs.size(); ++i)
        {
            Raft raft;

            int raftId = std::stoi(vvs.at(i).at(0));
            raft.SetId(raftId);

            if (vvs.at(i).at(1) == "y")
            {
                raft.SetSail(true);
            }
            else if (vvs.at(i).at(1) == "n")
            {
                raft.SetSail(false);
            }
            else
            {
                throw std::exception();
            }

            float work1, work2, work3;

            work1 = std::stof(vvs.at(i).at(2));
            work2 = std::stof(vvs.at(i).at(3));
            work3 = std::stof(vvs.at(i).at(4));

            raft.SetXYZ(work1, work2, work3);

            int work_i = 0;
            work_i = std::stoi(vvs.at(i).at(5));
            raft.SetDurability(work_i);

            if (vvs.at(i).at(6) == "Sea")
            {
                raft.SetPosType(Raft::ePosType::Sea);
            }
            else if (vvs.at(i).at(6) == "River")
            {
                raft.SetPosType(Raft::ePosType::River);
            }
            else
            {
                throw std::exception();
            }

            work_i = std::stoi(vvs.at(i).at(7));
            raft.SetStorehouseId(work_i);

            m_raftList.push_back(raft);
        }
    }
}

void Voyage::Save(const std::string& csvVoyage, const std::string& csvRaft)
{
    {
        std::vector<std::vector<std::string> > vvs;
        std::vector<std::string> vs;
        std::string work_str;

        vs.push_back("イカダを使用中か");

        if (m_bRaftMode)
        {
            vs.push_back("y");
        }
        else
        {
            vs.push_back("n");
        }

        vvs.push_back(vs);

        vs.clear();
        vs.push_back("現在使用中のイカダ");
        vs.push_back(std::to_string(m_currentRaftId));

        vvs.push_back(vs);

        Util::WriteToCsv(csvVoyage, vvs, false);
    }

    {
        std::vector<std::vector<std::string> > vvs;
        std::vector<std::string> vs;
        std::string work_str;

        vs.push_back("ID");
        vs.push_back("帆の展開");
        vs.push_back("x");
        vs.push_back("y");
        vs.push_back("z");
        vs.push_back("耐久値");
        vs.push_back("場所タイプ");
        vs.push_back("倉庫ID");
        vvs.push_back(vs);

        for (auto it = m_raftList.begin(); it != m_raftList.end(); ++it)
        {
            vs.clear();

            work_str = std::to_string(it->GetId());
            vs.push_back(work_str);

            if (it->GetSail())
            {
                work_str = "y";
            }
            else
            {
                work_str = "n";
            }

            vs.push_back(work_str);

            float x, y, z;
            it->GetXYZ(&x, &y, &z);

            work_str = std::to_string(x);
            vs.push_back(work_str);

            work_str = std::to_string(y);
            vs.push_back(work_str);

            work_str = std::to_string(z);
            vs.push_back(work_str);

            work_str = std::to_string(it->GetDurability());
            vs.push_back(work_str);

            if (it->GetPosType() == Raft::ePosType::River)
            {
                vs.push_back("River");
            }
            else
            {
                vs.push_back("Sea");
            }

            work_str = std::to_string(it->GetStorehouseId());
            vs.push_back(work_str);
            vvs.push_back(vs);
        }

        Util::WriteToCsv(csvRaft, vvs, false);
    }
    
    srand((unsigned int)time(NULL));
}

// 毎フレーム呼ばれる想定
// 潮や風によって流される処理はライブラリの利用者側で行う
void Voyage::Update()
{
    // 10秒ごとに耐久度が1減る
    // 10秒（現実時間）＝120秒（ゲーム時間）
    static int counter = 0;
    ++counter;

    if (counter >= 60 * 60 * 60)
    {
        counter = 0;
    }

    if (counter % (60 * 10) == 0)
    {
        auto raft = GetRaftCurrentPriv();
        auto dura = raft->GetDurability();
        raft->SetDurability(dura - 1);
    }

    // 1時間おきに風の向きと強さが変わる
    // 1時間（ゲーム時間）＝5分（現実時間）
    // 強さ：-10.0 m/s ~ 10.0 m/s
    if (counter % (60 * 60 * 5) == 0)
    {
        {
            int rnd = rand() % 200;
            rnd -= 100;
            float rnd_f = (float)rnd;
            rnd_f /= 10.f;
            m_windX = rnd_f;
        }
        {

            int rnd = rand() % 200;
            rnd -= 100;
            float rnd_f = (float)rnd;
            rnd_f /= 10.f;
            m_windZ = rnd_f;
        }
    }

    // 1時間おきに潮の向きと強さが変わる
    // 1時間（ゲーム時間）＝5分（現実時間）
    // 強さ：0m/s ~ 3m/s
    if (counter % (60 * 60 * 5) == 0)
    {
        {
            int rnd = rand() % 200;
            rnd -= 100;
            float rnd_f = (float)rnd;
            rnd_f /= 10.f;
            m_tideX = rnd_f;
        }
        {

            int rnd = rand() % 200;
            rnd -= 100;
            float rnd_f = (float)rnd;
            rnd_f /= 10.f;
            m_tideZ = rnd_f;
        }
    }
}

void Voyage::SetRaftMode(const bool arg)
{
    m_bRaftMode = arg;
}

bool Voyage::GetRaftMode() const
{
    return m_bRaftMode;
}

void Voyage::AddRaft(const Raft& arg)
{
    Raft raft(arg);
    raft.SetId(m_raftList.size());

    m_raftList.push_back(arg);
}

std::vector<Raft> Voyage::GetRaftList()
{
    return m_raftList;
}

Raft Voyage::GetRaftCurrent()
{
    auto it = std::find_if(m_raftList.begin(), m_raftList.end(),
                           [&](Raft& x)
                           {
                               return x.GetId() == m_currentRaftId;
                           });

    if (it == m_raftList.end())
    {
        throw std::exception();
    }

    return *it;
}

int NSStarmanLib::Voyage::GetRaftCurrentId() const
{
    return m_currentRaftId;
}

void Voyage::PullRightOar()
{
    // 耐久度を減らす
    auto raft = GetRaftCurrentPriv();
    auto dura = raft->GetDurability();
    raft->SetDurability(dura - 1);

    // 体力を消耗させる
    auto status = StatusManager::GetObj();
    status->PullOar();
}

void Voyage::PullLeftOar()
{
    // 耐久度を減らす
    auto raft = GetRaftCurrentPriv();
    auto dura = raft->GetDurability();
    raft->SetDurability(dura - 1);

    // 体力を消耗させる
    auto status = StatusManager::GetObj();
    status->PullOar();
}

void Voyage::PullBothOar()
{
    // 耐久度を減らす
    auto raft = GetRaftCurrentPriv();
    auto dura = raft->GetDurability();
    raft->SetDurability(dura - 1);

    // 体力を消耗させる
    auto status = StatusManager::GetObj();
    status->PullOarBoth();
}

void Voyage::SetCurrentRaftCoord(const float x, const float y, const float z)
{
    auto it = GetRaftCurrentPriv();
    it->SetXYZ(x, y, z);
}

void Voyage::GetCurrentRaftCoord(float* x, float* y, float* z)
{
    auto it = GetRaftCurrentPriv();
    it->GetXYZ(x, y, z);
}

bool Voyage::Set3HoursAuto()
{
    // 川ではなく海にいるときじゃないと使えない。
    auto it = GetRaftCurrentPriv();
    if (it->GetPosType() == Raft::ePosType::River)
    {
        return false;
    }

    // 3時間経過
    auto datetime = PowereggDateTime::GetObj();
    datetime->IncreaseDateTime(0, 0, 3, 0, 0);

    // 3時間分、耐久度低下
    // ゲーム時間で120秒ごとに耐久度が1減るので
    // 3600秒 * 3時間 / 120秒で90減る
    auto dura = it->GetDurability();
    dura -= (3600 * 3) / 120;
    it->SetDurability(dura);

    // 3時間分、移動
    // 移動処理はライブラリ側ではやらない

    // 3時間分、体力消費
    // 10秒に一回オールを漕ぐ、を3時間続けたものとする
    auto status = StatusManager::GetObj();
    status->Voyage3Hours();

    return true;
}

bool Voyage::Enable3HoursAuto()
{
    bool result = true;

    // 川ではなく海にいるときじゃないと使えない。
    auto it = GetRaftCurrentPriv();
    if (it->GetPosType() == Raft::ePosType::River)
    {
        result = false;
    }

    return result;
}

void Voyage::SetSailCurrentRaft(const bool arg)
{
    auto it = GetRaftCurrentPriv();
    it->SetSail(arg);
}

bool Voyage::GetSailCurrentRaft() const
{
    const auto it = GetRaftCurrentPriv();
    return it->GetSail();
}

void Voyage::SetPosTypeCurrentRaft(const Raft::ePosType arg)
{
    auto it = GetRaftCurrentPriv();
    it->SetPosType(arg);
}

Raft::ePosType Voyage::GetPosTypeCurrentRaft() const
{
    const auto it = GetRaftCurrentPriv();
    return it->GetPosType();
}

void Voyage::GetTideXZ(float* x, float* z)
{
    *x = m_tideX;
    *z = m_tideZ;
}

void Voyage::GetWindXZ(float* x, float* z)
{
    *x = m_windX;
    *z = m_windZ;
}

bool Voyage::CheckNearRaft(const float x, const float y, const float z, int* id)
{
    bool result = false;

    for (auto it = m_raftList.begin(); it != m_raftList.end(); ++it)
    {
        float x2, y2, z2;
        it->GetXYZ(&x2, &y2, &z2);

        result = Util::HitByBoundingBox(x, y, z, x2, y2, z2, 2);
        if (result)
        {
            if (id != nullptr)
            {
                *id = it->GetId();
            }

            break;
        }
    }

    return result;
}

bool Voyage::CheckRaftEnable()
{
    // 袋を装備していたらイカダに乗ることはできない。

    auto status = StatusManager::GetObj();
    auto bagState = status->GetBagState();

    if (bagState.empty())
    {
        return true;
    }
    return false;
}

bool Voyage::CheckRaftBroken()
{
    auto raft = GetRaftCurrentPriv()->GetDurability();
    if (raft <= 0)
    {
        return true;
    }
    return false;
}

Raft* Voyage::GetRaftCurrentPriv() const
{
    auto it = std::find_if(m_raftList.begin(), m_raftList.end(),
                           [&](const Raft& x)
                           {
                               return x.GetId() == m_currentRaftId;
                           });

    
    return (Raft* const)&(*it);
}

void Raft::SetId(const int arg)
{
    m_id = arg;
}

int Raft::GetId() const
{
    return m_id;
}

void Raft::SetSail(const bool arg)
{
    m_bSail = arg;
}

bool Raft::GetSail() const
{
    return m_bSail;
}

void Raft::SetXYZ(const float x, const float y, const float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void Raft::GetXYZ(float* x, float* y, float* z)
{
    *x = m_x;
    *y = m_y;
    *z = m_z;
}

void Raft::SetDurability(const int arg)
{
    m_durability = arg;
}

int Raft::GetDurability() const
{
    return m_durability;
}

void Raft::SetLevel(const int arg)
{
    m_level = arg;
}

int Raft::GetLevel() const
{
    return m_level;
}

void Raft::SetPosType(const ePosType arg)
{
    m_ePosType = arg;
}

Raft::ePosType Raft::GetPosType() const
{
    return m_ePosType;
}

void Raft::SetStorehouseId(const int arg)
{
    m_storehouseId = arg;
}

int Raft::GetStorehouseId() const
{
    return m_storehouseId;
}

float Raft::GetStorehouseWeight() const
{
    // TODO
    return 0.0f;
}

