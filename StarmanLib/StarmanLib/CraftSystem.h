#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "CraftInfoManager.h"
#include <deque>

namespace NSStarmanLib
{

// �N���t�g���̃A�C�e���̏��N���X
class CraftingItem
{
public:

    std::string GetName() const;
    void SetName(std::string mname);

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

    int GetfinishYear() const;
    void SetfinishYear(int mfinishYear);

    int GetfinishMonth() const;
    void SetfinishMonth(int mfinishMonth);

    int GetfinishDay() const;
    void SetfinishDay(int mfinishDay);

    int GetfinishHour() const;
    void SetfinishHour(int mfinishHour);

    int GetfinishMinute() const;
    void SetfinishMinute(int mfinishMinute);

    int GetfinishSecond() const;
    void SetfinishSecond(int mfinishSecond);

    CraftInfo GetCraftInfo() const;
    void SetCraftInfo(const CraftInfo& arg);

private:

    std::string m_name;

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
    void SetCraftsmanSkill(const std::string& craftItem);

    bool GetCraftsmanSkill(const std::string& craftItem);

    // �N���t�g���˗����ꂽ��A�C�e��������A24���Ԍ�ɑq�ɂɃN���t�g�A�C�e�����z�u�����B
    // ��x�Ɉ�����N���t�g�ł��Ȃ��̂ŃN���t�g���Ɏ��̈˗����󂯂���L���[�C���O�����
    // 5�܂ŃL���[�C���O�o����
    bool CraftRequest(const std::string& craftItem);

    // �˗����L�����Z��
    bool CancelCraftStart(const int index);

    void UpdateCraftStatus();

private:

    // �V���O���g���I�u�W�F�N�g
    static CraftSystem* obj;

    std::unordered_map<std::string, bool> m_craftSkillMap;

    // ��x�ɃN���t�g�ł���A�C�e���͈�����̑z��
    std::list<CraftingItem> m_craftingItemList;

};
}
