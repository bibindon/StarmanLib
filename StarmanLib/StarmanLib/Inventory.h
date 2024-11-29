#pragma once

#include "HeaderOnlyCsv.hpp"
#include "ItemManager.h"

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
    bool Inited();
    void Save(const std::string& csvfile);

    // 一個ずつしか増加減出来ない想定
    void AddItem(const int id, const int durability = -1);
    void AddItem(const std::string name, const int level = -1, const int durability = -1);

    // subId・・・耐久値の50の石斧と耐久値が100の石斧を所持することができる
    // そのため、アイテムにはsubIdが振られる。アイテムを削除するにはsubIdがないとできない
    // アイテムは削除できるのでSubIDが連番になるとは限らない
    void RemoveItem(const int id, const int subId);
    void RemoveItem(const std::string name, const int subId, const int level = -1);

    void SetItemDurability(const int id, const int subId, const int durability);

    bool ExistItem(const int id, const int subId);
    ItemInfo GetItemInfo(const int id, const int subId);

    // SubIDをリストで受け取る
    std::vector<int> GetSubIdList(const int id);

    int CountItem(const int id);
    int CountItem(const std::string name, const int level = -1);

    float GetWeight();

private:
    // 以下の4つの関数を宣言・定義するのが正しいが・・・なくても・・・別に・・・
    Inventory() {};
    Inventory(const Inventory&);
    Inventory& operator=(const Inventory&) {}
    ~Inventory() {};

    float CalcWeight();

    void Sort();

    // シングルトンオブジェクト
    static Inventory* obj;

    // 所持品の重量（武器は含めない）
    float m_weight = 0.f;

    // 所持品リスト
    // 同じアイテムを複数所持できることに注意
    std::list<ItemInfo> m_itemInfoList;
    
    bool m_inited = false;
};
}

