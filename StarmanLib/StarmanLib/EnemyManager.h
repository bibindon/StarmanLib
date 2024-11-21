#pragma once

#include <string>
#include <unordered_map>

// 敵管理クラス。
// CSVファイルに記載された敵の座標やHPなどを提供するのみである。
// 敵の行動パターンだとか衝突判定、ジャンプの軌道など詳細なことはここではやらない。
// （ライブラリの使用者がゲーム内で独自の実装を行うべき）

class EnemyInfo
{
public:

    void SetID(const int arg);
    int GetID();

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

    int m_id { 0 };

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

class EnemyManager
{
public:

    static EnemyManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);

    void Save(const std::string& csvfile);

    // 引数で示す座標と半径の内側にいる敵を取得
    std::vector<EnemyInfo> GetEnemyInfo(const float x, const float y, const float z, const float r);

    void UpdateEnemyInfo(const int id, const EnemyInfo& enemyInfo);

private:

    // シングルトンオブジェクト
    static EnemyManager* obj;

    std::unordered_map<int, EnemyInfo> m_enemyInfoMap;

};

