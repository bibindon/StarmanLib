#pragma once
#include <string>
#include <unordered_map>

// 糖質、タンパク質、脂質、ビタミン、ミネラルだけを状態に持つ
// プレイヤーは五大栄養素がすべて0にならないようにする必要がある。
// 糖質が0になったら餓死、それ以外が0になったら病死する。
// 倉庫にワードブレスがあればライネンの契約をし復活する。

class NpcStatus
{
public:

    void SetName(const std::string& arg);
    std::string GetName();

    void SetCarbo(const float arg);
    float GetCarbo();

    void SetProtein(const float arg);
    float GetProtein();

    void SetLipid(const float arg);
    float GetLipid();

    void SetVitamin(const float arg);
    float GetVitamin();

    void SetMineral(const float arg);
    float GetMineral();

    void SetRynenContract();
    float GetRynenContract();

    void SetDrinkWordbress(const bool arg);
    bool GetDrinkWordbress();

    void SetDead();
    bool GetDead();

private:

    // 名前
    std::string m_name;

    // 糖質
    float m_carbo { 0.f };

    // タンパク質
    float m_protein { 0.f };

    // 脂質
    float m_lipid { 0.f };

    // ビタミン
    float m_vitamin { 0.f };

    // ミネラル
    float m_mineral { 0.f };

    // ライネンの契約をしているか否か
    bool m_rynenContract { false };

    // ワードブレスを飲んでいるか否か
    bool m_bDrinkWordbress { false };

    // 死んでいるか否か
    bool m_dead { false };
};

class NpcStatusManager
{
public:

    static NpcStatusManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile);
    void Save(const std::string& csvfile);

    NpcStatus GetNpcStatus(const std::string& name);
    void SetNpcStatus(const std::string& key, const NpcStatus& value);

private:

    // シングルトンオブジェクト
    static NpcStatusManager* obj;

    std::unordered_map<std::string, NpcStatus> m_NpcStatusMap;

};

