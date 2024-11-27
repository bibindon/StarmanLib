//-------------------------------------------------------------
// CraftSystem��Init�֐�����ɁACraftInfoManager��Init���Ă΂�Ă���K�v������B
//-------------------------------------------------------------
#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "CraftInfoManager.h"
#include <deque>

namespace NSStarmanLib
{

// �N���t�g�\�񃊃X�g�̃A�C�e��
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

// �N���t�g�V�X�e���p�N���X
// �ECraftInfoManager���g�p����Inventory�N���X��Storehouse�N���X�𑀍삷��B
// �E�E�l�̏n���x���Ǘ�����B
// �E�E�l�̏n���x�A�C���x���g���̏󋵂���N���t�g�\ OR �N���t�g�s�\�̏���񋟂���B
// �EPowereggDateTime�N���X���g�p����24���Ԍ�Ɋ��������A�C�e����q�ɂɔz�u����B 
// �E��x�ɃN���t�g�ł���A�C�e���͈�����̑z��
// �E�N���t�g���L�����Z���ł��邪�f�ނ͂Ȃ��Ȃ�
// �E��������O�Ɏ��̈˗����ł���B5�܂ŃL���[�C���O�o����
class CraftSystem
{

public:

    static CraftSystem* GetObj();

    static void Destroy();

    void Init(const std::string& csvfileSkill, const std::string& csvfileQueue);

    void Save(const std::string& csvfileSkill, const std::string& csvfileQueue);

    // �E�l���N���t�g�\�ł��邩�H�̃t���O��ON�ɂ���
    void SetCraftsmanSkill(const std::string& craftItem, const int level = -1);

    bool GetCraftsmanSkill(const std::string& craftItem, const int level = -1);

    // �N���t�g���˗����ꂽ��A�C�e��������A24���Ԍ�ɑq�ɂɃN���t�g�A�C�e�����z�u�����B
    // ��x�Ɉ�����N���t�g�ł��Ȃ��̂ŃN���t�g���Ɏ��̈˗����󂯂���L���[�C���O�����
    // 5�܂ŃL���[�C���O�o����
    bool QueueCraftRequest(const std::string& craftItem, const int level = -1);

    // �˗����L�����Z��
    bool CancelCraftStart(const int index);

    void UpdateCraftStatus();

    int GetProgress();

    std::list<CraftRequest> GetCraftRequestList();

private:

    void StartCraft();

    // �V���O���g���I�u�W�F�N�g
    static CraftSystem* obj;

    std::vector<CraftSkill> m_craftSkillList;

    // ��x�ɃN���t�g�ł���A�C�e���͈�����̑z��
    std::list<CraftRequest> m_craftRequestList;

};
}

