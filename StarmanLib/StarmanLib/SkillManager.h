#pragma once

#include "HeaderOnlyCsv.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace NSStarmanLib
{
// TODO 熟練度について
// 筋肉の成長と同じ道をたどる。
// 魔法を使って、疲れて、休憩して、改めて使うとレベルが上がる。

class SkillDefinition
{
public:

    void SetName(const std::string& arg);
    std::string GetName();

    void SetDetail(const std::string& arg);
    std::string GetDetail();

    void SetDamage(const int arg1, const float& arg2);
    float GetDamage(const int arg);

    void SetRange(const int arg1, const float& arg2);
    float GetRange(const int arg);

private:

    std::string m_name;
    std::string m_detail;
    std::unordered_map<int, float> m_damageMap;
    std::unordered_map<int, float> m_rangeMap;
};

class SkillManager
{
public:

    static SkillManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfileDefinition, const std::string& csvfilePlayer,
              const bool decrypt = false);

    void Save(const std::string& csvfile,
              const bool encrypt = false);

    void SetSkillLevel(const std::string& skillName, const int skillLevel);
    int GetSkillLevel(const std::string& skillName);

    std::string GetDetail(const std::string& key);
    float GetDamage(const std::string& key, const int level);
    float GetRange(const std::string& key, const int level);

    std::vector<std::string> GetNameList();

private:

    // シングルトンオブジェクト
    static SkillManager* obj;

    // スキルの定義
    std::unordered_map<std::string, SkillDefinition> m_skillLevelMap;

    // 現在の主人公のスキルレベルの状況
    std::unordered_map<std::string, int> m_playerSkillLevelMap;

};
}

