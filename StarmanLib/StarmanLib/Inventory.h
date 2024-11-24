#pragma once

#include "HeaderOnlyCsv.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{
// プレイヤーの所持品を管理するクラス。
// アイテムの定義はItemManagerが管理している。
// 武器についてはWeaponManagerが所持数まで管理しているので
// Inventoryクラスに出番はない予定

class Inventory
{
public:

    static Inventory* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);
    void Save(const std::string& csvfile);

    // 一個ずつしか増加減出来ない想定
    void AddItem(const int id);
    void RemoveItem(const int id);
    int CountItem(const int id);

    float GetWeight();

private:

    float CalcWeight();

    // シングルトンオブジェクト
    static Inventory* obj;

    // 所持品の重量（武器は含めない）
    float m_weight;

    // 所持品リスト
    // 同じアイテムを複数所持できることに注意
    std::unordered_map<int, int> m_itemMap;
    
};
}

