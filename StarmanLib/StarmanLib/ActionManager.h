#pragma once
#include <string>

namespace NSStarmanLib
{
// 木を斧で切る、など
// 木を倒そうとしたら「木を倒しますか？（６時間消費）」、のように表示される
// ６時間というのはパワーエッグ星の時間。
// ・時が進むようにする。
// ・体力も規定量が消費される
// ・餓死寸前で実行することはできない。
//
// 時間のかかる行動の種類
// 
// 伐採
// 睡眠
// 仮眠
// イカダを漕ぐ（3時間）
// 採集（銅鉱石）
// 加工
// 修理
// 調理
// 釣り
//
// まずは伐採だけで良い。他の行動は正直いらない気がする。

class ActionManager
{
public:
    void GetActionTime(const std::wstring actionName,
                       int* day,
                       int* hour,
                       int* minute,
                       int* second);
private:

};
}
