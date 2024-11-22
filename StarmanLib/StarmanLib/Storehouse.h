#pragma once

#include "HeaderOnlyCsv.hpp"

#include <string>
#include <vector>
#include <unordered_map>

// 倉庫クラス
// 拠点に預けているアイテム
// ストーリーの都合で拠点は途中で1度変わることに注意。
// 拠点間で倉庫の中身を取り出せるようにはしない想定。
class Storehouse
{

public:

    static Storehouse* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);
    void Save(const std::string& csvfile);

    // 一個ずつしか増加減出来ない想定
    void AddItem(const int id);
    void RemoveItem(const int id);
    int CountItem(const int id);

private:

    // シングルトンオブジェクト
    static Storehouse* obj;

    // 所持品リスト
    // 同じアイテムを複数所持できることに注意
    std::unordered_map<int, int> m_itemMap;
    
};

