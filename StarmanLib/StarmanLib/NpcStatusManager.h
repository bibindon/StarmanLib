#pragma once

// 糖質、タンパク質、脂質、ビタミン、ミネラルだけを状態に持つ
// プレイヤーは五大栄養素がすべて0にならないようにする必要がある。
// 糖質が0になったら餓死、それ以外が0になったら病死する。

class NpcStatus
{
public:



private:

    float m_carbo { 0.f };
    float m_protein { 0.f };
    float m_lipid { 0.f };
    float m_vitamin { 0.f };
    float m_mineral { 0.f };

};

class NpcStatusManager
{
};

