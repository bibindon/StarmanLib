//-------------------------------------------------------------
// CraftSystemのInit関数より先に、CraftInfoManagerのInitが呼ばれている必要がある。
//-------------------------------------------------------------
#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "CraftInfoManager.h"
#include <deque>

namespace NSStarmanLib
{

// クラフト予約リストのアイテム
class CraftRequest
{
public:

    std::string GetName() const;
    void SetName(std::string mname);

    int GetLevel() const;
    void SetLevel(const int arg);

    int GetStartYear() const;
    void SetStartYear(int startYear);

    int GetStartMonth() const;
    void SetStartMonth(int startMonth);

    int GetStartDay() const;
    void SetStartDay(int startDay);

    int GetStartHour() const;
    void SetStartHour(int startHour);

    int GetStartMinute() const;
    void SetStartMinute(int startMinute);

    int GetStartSecond() const;
    void SetStartSecond(int startSecond);

    int GetFinishYear() const;
    void SetFinishYear(int mfinishYear);

    int GetFinishMonth() const;
    void SetFinishMonth(int mfinishMonth);

    int GetFinishDay() const;
    void SetFinishDay(int mfinishDay);

    int GetFinishHour() const;
    void SetFinishHour(int mfinishHour);

    int GetFinishMinute() const;
    void SetFinishMinute(int mfinishMinute);

    int GetFinishSecond() const;
    void SetFinishSecond(int mfinishSecond);

    CraftInfo GetCraftInfo() const;
    void SetCraftInfo(const CraftInfo& arg);

    bool GetCrafting() const;
    void SetCrafting(const bool arg);

private:

    std::string m_name;
    int m_level;

    bool m_crafting = false;

    int m_startYear { 0 };
    int m_startMonth { 0 };
    int m_startDay { 0 };
    int m_startHour { 0 };
    int m_startMinute { 0 };
    int m_startSecond { 0 };

    int m_finishYear { 0 };
    int m_finishMonth { 0 };
    int m_finishDay { 0 };
    int m_finishHour { 0 };
    int m_finishMinute { 0 };
    int m_finishSecond { 0 };

    CraftInfo m_craftInfo;

};

class CraftSkill
{
public:

    void SetName(const std::string& arg);
    std::string GetName() const;

    void SetLevel(const int arg);
    int GetLevel() const;

    void SetEnable(const bool arg);
    bool GetEnable() const;

private:

    std::string m_name;
    int m_level;
    bool m_enable;
};

// クラフトシステム用クラス
// ・CraftInfoManagerを使用してInventoryクラスやStorehouseクラスを操作する。
// ・職人の熟練度を管理する。
// ・職人の熟練度、インベントリの状況からクラフト可能 OR クラフト不可能の情報を提供する。
// ・PowereggDateTimeクラスを使用して24時間後に完成したアイテムを倉庫に配置する。 
// ・一度にクラフトできるアイテムは一つだけの想定
// ・クラフトをキャンセルできるが素材はなくなる
// ・完成する前に次の依頼ができる。5個までキューイング出来る
class CraftSystem
{

public:

    static CraftSystem* GetObj();

    static void Destroy();

    void Init(const std::string& csvfileSkill, const std::string& csvfileQueue);

    void Save(const std::string& csvfileSkill, const std::string& csvfileQueue);

    // 職人がクラフト可能であるか？のフラグをONにする
    void SetCraftsmanSkill(const std::string& craftItem, const int level = -1);

    bool GetCraftsmanSkill(const std::string& craftItem, const int level = -1);

    // クラフトを依頼されたらアイテムが減り、24時間後に倉庫にクラフトアイテムが配置される。
    // 一度に一つしかクラフトできないのでクラフト中に次の依頼を受けたらキューイングされる
    // 5個までキューイング出来る
    bool QueueCraftRequest(const std::string& craftItem, const int level = -1);

    // 依頼をキャンセル
    bool CancelCraftStart(const int index);

    void UpdateCraftStatus();

    int GetProgress();

    std::list<CraftRequest> GetCraftRequestList();

private:

    void StartCraft();

    // シングルトンオブジェクト
    static CraftSystem* obj;

    std::vector<CraftSkill> m_craftSkillList;

    // 一度にクラフトできるアイテムは一つだけの想定
    std::list<CraftRequest> m_craftRequestList;

};
}

