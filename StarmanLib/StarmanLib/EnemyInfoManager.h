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
    int GetIDDef();

    void SetName(const std::string& arg);
    std::string GetName();

    void SetDetail(const std::string& arg);
    std::string GetDetail();

    void SetImagePath(const std::string& arg);
    std::string GetImagePath();

    void SetVisible(const bool arg);
    bool GetVisible();

private:

    // 敵一種類ごとに割り振られるID
    int m_idDef = 0;

    // 説明文
    std::string m_name;

    // 説明文
    std::string m_detail;

    // ファイルパス
    std::string m_imagePath;

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
    int GetIDDef();

    void SetBreed(const std::string& breed);
    std::string GetBreed();

    void SetX(const float arg);
    float GetX();

    void SetY(const float arg);
    float GetY();

    void SetZ(const float arg);
    float GetZ();

    void SetRotX(const float arg);
    float GetRotX();

    void SetRotY(const float arg);
    float GetRotY();

    void SetRotZ(const float arg);
    float GetRotZ();

    void SetHP(const int arg);
    int GetHP();

    void SetDefeated(const bool arg);
    bool GetDefeated();

private:

    // 敵一体ごとに割り振られるID
    int m_id = 0;

    // 敵一種類ごとに割り振られるID
    int m_idDef = 0;

    // モンスターの種族
    std::string m_breed;

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

    void Init(const std::string& csvEnemyDef,
              const std::string& csvEnemyInfo,
              const std::string& csvEnemyVisible);

    void Save(const std::string& csvEnemyInfo,
              const std::string& csvEnemyVisible);

    // 引数で示す座標と半径の内側にいる敵を取得
    std::vector<EnemyInfo> GetEnemyInfo(const float x, const float y, const float z, const float r);

    void UpdateEnemyInfo(const int id, const EnemyInfo& enemyInfo);

    std::vector<std::string> GetEnemyNameList();

    EnemyDef GetEnemyDef(const std::string name);
    void SetEnemyVisible(const std::string name, const bool visible);

private:

    // シングルトンオブジェクト
    static EnemyInfoManager* obj;

    std::unordered_map<int, EnemyDef> m_enemyDefMap;
    std::unordered_map<int, EnemyInfo> m_enemyInfoMap;

};
}

