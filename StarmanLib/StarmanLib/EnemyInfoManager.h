#pragma once

#include <string>
#include <unordered_map>

namespace NSStarmanLib
{

// 敵の定義情報
// 敵一種類につき、1インスタンス
class EnemyDef
{
public:

    void SetIDDef(const int arg);
    int GetIDDef() const;

    void SetName(const std::wstring& arg);
    std::wstring GetName();

    void SetDetail(const std::wstring& arg);
    std::wstring GetDetail();

    void SetImagePath(const std::wstring& arg);
    std::wstring GetImagePath();

    void SetVisible(const bool arg);
    bool GetVisible() const;

private:

    // 敵一種類ごとに割り振られるID
    int m_idDef = 0;

    // 説明文
    std::wstring m_name;

    // 説明文
    std::wstring m_detail;

    // ファイルパス
    std::wstring m_imagePath;

    // メニューでの表示・非表示
    bool m_visible;
};

// 敵管理クラス。
// 敵1体につき、1インスタンス
// CSVファイルに記載された敵の座標やHPなどを提供するのみである。
// 敵の行動パターンだとか衝突判定、ジャンプの軌道など詳細なことはここではやらない。
// （ライブラリの使用者がゲーム内で独自の実装を行うべき）
class EnemyInfo
{
public:

    void SetID(const int arg);
    int GetID();

    void SetIDDef(const int arg);
    int GetIDDef() const;

    void SetBreed(const std::wstring& breed);
    std::wstring GetBreed();

    void SetX(const float arg);
    float GetX() const { return m_x; }

    void SetY(const float arg);
    float GetY() const { return m_y; }

    void SetZ(const float arg);
    float GetZ() const { return m_z; }

    void SetRotX(const float arg);
    float GetRotX() const;

    void SetRotY(const float arg);
    float GetRotY() const;

    void SetRotZ(const float arg);
    float GetRotZ() const;

    void SetHP(const int arg);
    int GetHP() const;

    void SetDefeated(const bool arg);
    bool GetDefeated() const;

private:

    // 敵一体ごとに割り振られるID
    int m_id = 0;

    // 敵一種類ごとに割り振られるID
    int m_idDef = 0;

    // モンスターの種族
    std::wstring m_breed;

    float m_x { 0.f };
    float m_y { 0.f };
    float m_z { 0.f };

    float m_rotX { 0.f };
    float m_rotY { 0.f };
    float m_rotZ { 0.f };

    // 残りHP
    int m_HP { 0 };
    bool m_bDefeated { false };

};

class EnemyInfoManager
{
public:

    static EnemyInfoManager* GetObj();

    static void Destroy();

    void Init(const std::wstring& csvEnemyDef,
              const std::wstring& csvEnemyInfo,
              const std::wstring& csvEnemyVisible,
              const bool decrypt = false);

    void Save(const std::wstring& csvEnemyInfo,
              const std::wstring& csvEnemyVisible,
              const bool encrypt = false);

    // 引数で示す座標と半径の内側にいる敵を取得
    std::vector<EnemyInfo> GetEnemyInfo(const float x, const float y, const float z, const float r);

    void UpdateEnemyInfo(const int id, const EnemyInfo& enemyInfo);

    std::vector<std::wstring> GetEnemyNameList();

    EnemyDef GetEnemyDef(const std::wstring name);
    void SetEnemyVisible(const std::wstring name, const bool visible);

    EnemyInfo GetEnemyInfo(const int id);
    void SetDefeat(const int id);

private:

    // シングルトンオブジェクト
    static EnemyInfoManager* obj;

    std::unordered_map<int, EnemyDef> m_enemyDefMap;
    std::unordered_map<int, EnemyInfo> m_enemyInfoMap;

};
}

