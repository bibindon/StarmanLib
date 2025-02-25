#include "Voyage.h"

Voyage* Voyage::m_single = nullptr;

Voyage* Voyage::Get()
{
    if (m_single == nullptr)
    {
        m_single = new Voyage();
    }

    return m_single;
}

void Voyage::Init(const std::string& csvFile)
{
}

void Voyage::Save(const std::string& csvFile)
{
}

void Voyage::Update()
{
    // 潮や風によって流される処理はライブラリの利用者側で行う
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

    return *it;
}

void Voyage::PullRightOar()
{
    // do nothing
}

void Voyage::PullLeftOar()
{
    // do nothing
}

void Voyage::PullBothOar()
{
    // do nothing
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

void Voyage::Set3HoursAuto()
{
    // 川ではなく海にいるときじゃないと使えない。
    auto it = GetRaftCurrentPriv();
    if (it->GetPosType() == Raft::ePosType::River)
    {
        throw std::exception();
    }

    // 3時間経過
    // 3時間分移動
    // 3時間分、体力消費
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

