#pragma once

#include <string>
#include <unordered_map>

namespace NSStarmanLib
{

// アイテムには耐久度があり、同じアイテムでも耐久度が異なることが可能。
// 例えば、石斧を二つ所持しているが、片方は耐久度が100で、
// もう片方は耐久度が50というのは可能である。
// これを実現するためにItemInfoとItemDefというクラスに分ける。
// ItemDefはアイテムの定義、ItemInfoは個々のアイテムの状態とする
// ItemInfoはInventoryクラス（インベントリ）やStorehouseクラス（倉庫）で使われる。

class ItemInfo
{
public:

    void SetId(const int arg);
    int GetId() const;

    void SetSubId(const int arg);
    int GetSubId() const;

    void SetDurabilityCurrent(const int arg);
    int GetDurabilityCurrent() const;

private:

    int m_id = 0;

    int m_subId = 0;

    int m_durabilityCurrent = 0;
};

class ItemDef
{
public:
    enum class ItemType
    {
        // 貴重品
        VALUABLES,

        // 食材
        FOOD,

        // 素材
        MATERIAL,

        // 武器
        WEAPON,

        // その他
        OTHERS,
    };

    int GetId() const;
    void SetId(int arg);

    std::string GetName() const;
    void SetName(std::string arg);

    std::string GetDetail() const;
    void SetDetail(std::string arg);

    std::string GetImagePath() const;
    void SetImagePath(std::string arg);

    float GetWeight() const;
    void SetWeight(float arg);

    float GetVolume() const;
    void SetVolume(float arg);

    ItemType GetType() const;
    void SetType(ItemType arg);

    float GetCarbo() const;
    void SetCarbo(float arg);

    float GetProtein() const;
    void SetProtein(float arg);

    float GetLipid() const;
    void SetLipid(float arg);

    float GetVitamin() const;
    void SetVitamin(float arg);

    float GetMineral() const;
    void SetMineral(float arg);

    float GetWater() const;
    void SetWater(float arg);

    float GetBodyStaminaDebuff() const;
    void SetBodyStaminaDebuff(float arg);

    float GetBrainStaminaDebuff() const;
    void SetBrainStaminaDebuff(float arg);

    float GetMuscleDebuff() const;
    void SetMuscleDebuff(float arg);

    bool GetHeadache() const;
    void SetHeadache(bool arg);

    bool GetStomachache() const;
    void SetStomachache(bool arg);

    int GetLevel() const;
    void SetLevel(int arg);

    int GetDurabilityMax() const;
    void SetDurabilityMax(int arg);

private:
    // ID
    int m_id = 0;

    // 名称
    std::string m_name;

    // 詳細
    std::string m_detail;

    // 画像のファイル名
    std::string m_imagePath;

    // 重量（kg）
    float m_weight;

    // 体積（mL）
    float m_volume;

    // 種類
    ItemType m_eType;

    // 糖質
    float m_carbo;

    // タンパク質
    float m_protein;

    // 脂質
    float m_lipid;

    // ビタミン
    float m_vitamin;

    // ミネラル
    float m_mineral;

    // 水分
    // マイナスになることがある。
    float m_water;

    // デバフ（体のスタミナ）
    float m_bodyStaminaDebuff;

    // デバフ（脳のスタミナ）
    float m_brainStaminaDebuff;

    // デバフ（肉体の修復度）
    float m_muscleDebuff;

    // デバフ（頭痛）
    bool m_headache;

    // デバフ（腹痛）
    bool m_stomachache;

    // 強化値
    int m_level = -1;

    // 耐久度
    int m_durabilityMax = -1;
};

// アイテム情報を管理するクラス
// 「主人公はアイテムをいくつ持っているか？」は
// Inventoryクラスが担当するためこのクラスは関係ないことに注意。
class ItemManager
{
public:

    static ItemManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);
    bool Inited();

    ItemDef GetItemDef(const std::string& key, const int level = -1);
    ItemDef GetItemDef(const int id);

private:

    // シングルトンオブジェクト
    static ItemManager* obj;

    std::unordered_map<int, ItemDef> m_itemDefMap;

    bool m_inited = false;
};
}

