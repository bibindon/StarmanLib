#pragma once

#include "HeaderOnlyCsv.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{
// 倉庫クラス
// 拠点に預けているアイテム
// ストーリーの都合で拠点は途中で1度変わることに注意。
// 拠点間で倉庫の中身を取り出せるようにはしない想定。
// TODO 仲間NPCが瀕死になったらワードブレスが一つ減る。
class Storehouse
{

public:

    static Storehouse* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);
    void Save(const std::string& csvfile);

    // 一個ずつしか増加減出来ない想定
    void AddItem(const int id);
    void AddItem(const std::string& name, const int level = -1);
    void RemoveItem(const int id);
    void RemoveItem(const std::string& name, const int level = -1);
    int CountItem(const int id);
    int CountItem(const std::string& name, const int level = -1);

private:

    // シングルトンオブジェクト
    static Storehouse* obj;

    // 所持品リスト
    // 同じアイテムを複数所持できることに注意
    std::unordered_map<int, int> m_itemMap;

};
}

