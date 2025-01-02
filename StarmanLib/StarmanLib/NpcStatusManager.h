#pragma once
#include <string>
#include <unordered_map>

namespace NSStarmanLib
{
// 糖質、タンパク質、脂質、ビタミン、ミネラルだけを状態に持つ
// プレイヤーは五大栄養素がすべて0にならないようにする必要がある。
// 糖質が0になったら餓死、それ以外が0になったら病死する。
// 倉庫にワードブレスがあればライネンの契約をし復活する。

enum class eNpcFeature
{
    STOREHOUSE,
    CRAFTMAN,
    NONE,
};

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

    void SetX(const float arg);
    float GetX() const;

    void SetY(const float arg);
    float GetY() const;

    void SetZ(const float arg);
    float GetZ() const;

    void SetRotY(const float arg);
    float GetRotY() const;

    void SetHasTalk(const bool arg);
    bool GetHasTalk() const;

    void SetTalkCsv(const std::string& arg);
    std::string GetTalkCsv() const;

    void SetFeatureEnable(const bool arg);
    bool GetFeatureEnable() const;

    void SetNpcFeature(const eNpcFeature arg);
    eNpcFeature GetNpcFeature() const;

    void SetMenuShow(const bool arg);
    bool GetMenuShow() const;

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

    float m_x = 0.f;

    float m_y = 0.f;

    float m_z = 0.f;

    float m_rotY = 0.f;

    // 会話すべき文言があるか？
    // ・NPCの会話は荷物番や鍛冶屋の機能を表示する前に表示する
    bool m_bHasTalk = false;

    // 会話すべき文言
    // m_talkCsvの内容を使って利用者に会話してもらう。
    std::string m_talkCsv;

    // 荷物番や鍛冶屋の機能が解禁されているか。
    bool m_bFeatureEnable = false;

    eNpcFeature m_eNpcFeature = eNpcFeature::NONE;

    // NPCをメニュー画面で表示するか
    bool m_bMenuShow = false;
};



class NpcStatusManager
{
public:

    static NpcStatusManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfile,
              const bool decrypt = false);
    void Save(const std::string& csvfile,
              const bool encrypt = false);

    NpcStatus GetNpcStatus(const std::string& name);
    void SetNpcStatus(const std::string& key, const NpcStatus& value);

    std::vector<std::string> GetNameList();

private:

    // シングルトンオブジェクト
    static NpcStatusManager* obj;

    std::unordered_map<std::string, NpcStatus> m_NpcStatusMap;

};
}

