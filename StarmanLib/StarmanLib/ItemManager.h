#pragma once

#include <string>
#include <unordered_map>
#include <map>

namespace NSStarmanLib
{

// アイテムには耐久度があり、同じアイテムでも耐久度が異なることが可能。
// 例えば、石斧を二つ所持しているが、片方は耐久度が100で、
// もう片方は耐久度が50というのは可能である。
// これを実現するためにItemInfoとItemDefというクラスに分ける。
// ItemDefはアイテムの定義、ItemInfoは個々のアイテムの状態とする
// ItemInfoはInventoryクラス（インベントリ）やStorehouseクラス（倉庫）で使われる。
// SubIdで個々のアイテムの識別を行うが、アイテムは削除できるので連番になるとは限らない

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

    std::wstring GetName() const;
    void SetName(std::wstring arg);

    std::wstring GetDetail() const;
    void SetDetail(std::wstring arg);

    std::wstring GetImagePath() const;
    void SetImagePath(std::wstring arg);

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

    std::wstring GetWeaponId() const;
    void SetWeaponId(const std::wstring& arg);

private:
    // ID
    int m_id = 0;

    // 名称
    std::wstring m_name;

    // 詳細
    std::wstring m_detail;

    // 画像のファイル名
    std::wstring m_imagePath;

    // 重量（kg）
    float m_weight = 0.f;

    // 体積（mL）
    float m_volume = 0.f;

    // 種類
    ItemType m_eType = ItemType::OTHERS;

    // 糖質
    float m_carbo = 0.f;

    // タンパク質
    float m_protein = 0.f;

    // 脂質
    float m_lipid = 0.f;

    // ビタミン
    float m_vitamin = 0.f;

    // ミネラル
    float m_mineral = 0.f;

    // 水分
    // マイナスになることがある。
    float m_water = 0.f;

    // デバフ（体のスタミナ）
    float m_bodyStaminaDebuff = 0.f;

    // デバフ（脳のスタミナ）
    float m_brainStaminaDebuff = 0.f;

    // デバフ（肉体の修復度）
    float m_muscleDebuff = 0.f;

    // デバフ（頭痛）
    bool m_headache = false;

    // デバフ（腹痛）
    bool m_stomachache = false;

    // 強化値
    int m_level = -1;

    // 耐久度
    int m_durabilityMax = -1;

    std::wstring m_weaponId;
};

class ItemInfo
{
public:

    void SetId(const int arg);
    int GetId() const;

    void SetSubId(const int arg);
    int GetSubId() const;

    void SetDurabilityCurrent(const int arg);
    int GetDurabilityCurrent() const;

    ItemDef GetItemDef() const;

private:

    int m_id = 0;

    int m_subId = 0;

    int m_durabilityCurrent = 0;
};

// ワールドマップ上のどこにアイテムが落ちているかの情報
class ItemPos
{
public:
    void SetItemPosId(const int id);
    int GetItemPosId() const;

    void SetItemDefId(const int id);
    int GetItemDefId() const;

    void SetPos(const float x, const float y, const float z);
    void GetPos(float* x, float* y, float* z);

    void SetObtained(const bool arg);
    bool GetObtained();

private:

    int m_itemPosId = 0;
    int m_itemDefId = 0;
    float m_x = 0.f;
    float m_y = 0.f;
    float m_z = 0.f;
    bool m_obtained = false;
};

// アイテム情報を管理するクラス
// 「主人公はどのアイテムをいくつ持っているか？」は
// Inventoryクラスが担当するためこのクラスは関係ないことに注意。
class ItemManager
{
public:

    static ItemManager* GetObj();

    static void Destroy();

    void Init(const std::wstring& csvfile, const std::wstring& csvfilePos,
              const bool decrypt = false);
    bool Inited();
    void Save(const std::wstring& csvfilePos,
              const bool encrypt = false);

    std::vector<int> GetItemIdList();
    // 名前を使うの禁止、としたいが、メニュー画面のために残す必要がある
    ItemDef GetItemDef(const std::wstring& key, const int level = -1);
    ItemDef GetItemDef(const int id);
    ItemDef GetItemDefByWeaponId(const std::wstring& weaponId, const int level = -1);
    std::vector<int> GetItemDef(const ItemDef::ItemType type);
    
    ItemDef GetItemDefByPosID(const int posId);

    // 1メートル以内にあるアイテムを一つだけ返す
    ItemPos GetItemPosByPos(const float x, const float y, const float z, const float r = 1.f);
    void SetItemPosObtained(const int itemPosId);

private:

    // シングルトンオブジェクト
    static ItemManager* obj;

    std::unordered_map<int, ItemDef> m_itemDefMap;

    bool m_inited = false;

    std::map<int, ItemPos> m_itemPosMap;
};
}

