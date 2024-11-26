#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace NSStarmanLib
{
// クラフト用の素材クラス
class CraftMaterial
{
public:

    void SetName(const std::string& arg);
    std::string GetName();

    void SetNumber(const int arg);
    int GetNumber();

    void SetLevel(const int arg);
    int GetLevel();

private:
    // 素材の名前
    std::string m_name;
    
    // 素材の必要数
    int m_number = 0;
    
    // 素材の強化レベル
    int m_level = 0;

};

// 完成品クラス
class CraftOutput
{
public:

    void SetName(const std::string& arg);
    std::string GetName() const;

    void SetNumber(const int arg);
    int GetNumber() const;

    void SetLevel(const int arg);
    int GetLevel() const;

private:

    // 完成品の名前
    std::string m_name;
    
    // 完成品の出力数
    int m_number = 0;
    
    // 完成品の強化レベル
    int m_level = 0;
};

// クラフトの情報クラス
class CraftInfo
{
public:

    void SetOutput(const CraftOutput& arg);
    CraftOutput GetOutput();

    void SetCraftMaterial(const int index, const CraftMaterial& arg);
    CraftMaterial GetCraftMaterial(const int index);
    std::vector<CraftMaterial> GetCraftMaterial();

private:

    CraftOutput m_output;

    std::unordered_map<int, CraftMaterial> m_materialList;
};

// クラフト情報の管理クラス
// イカダが完成品となるレシピは11種類ある。
// 強化値が＋１のイカダ、強化値が＋２のイカダ・・・
// レシピを特定するには、完成品の名前だけではなく、名前と個数と強化値が必要
class CraftInfoManager
{

public:

    static CraftInfoManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfileDefinition);

    std::vector<CraftOutput> GetCraftItemList();

    CraftInfo GetCraftInfo(const CraftOutput& output);
    CraftInfo GetCraftInfo(const std::string& name, const int num, const int level);

private:

    // シングルトンオブジェクト
    static CraftInfoManager* obj;

    std::vector<CraftInfo> m_craftInfoList;
};
}

