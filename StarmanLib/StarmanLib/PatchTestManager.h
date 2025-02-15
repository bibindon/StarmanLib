#pragma once
#include <string>
#include <vector>
#include <map>
#include <array>

namespace NSStarmanLib
{

// TODO ����Q���Ƀp�b�`�e�X�g����̂��H�Ƃ�����肪����B
class PatchTest
{
public:

    enum eState
    {
        NOT_START,
        STARTED,
        FINISHED,
    };

    enum eResult
    {
        NOT_YET,
        POISON,
        NOT_POISON,
    };

    void SetItemName(const std::string& arg);
    std::string GetItemName() const;

    // �˗�����
    void SetDateTimeReq(const int y, const int M, const int d,
                        const int h, const int m, const int s);

    void GetDateTimeReq(int* y, int* M, int* d, int* h, int* m, int* s);

    // �J�n����
    void SetDateTimeStart(const int y, const int M, const int d,
                          const int h, const int m, const int s);

    void GetDateTimeStart(int* y, int* M, int* d, int* h, int* m, int* s);

    // ��������
    void SetDateTimeEnd(const int y, const int M, const int d,
                        const int h, const int m, const int s);

    void GetDateTimeEnd(int* y, int* M, int* d, int* h, int* m, int* s);

    void SetState(const eState arg);
    eState GetState() const;

    void SetResult(const eResult result);
    eResult GetResult() const;

private:

    std::string m_itemName;
    eState m_eState = eState::NOT_START;
    eResult m_eResult = eResult::NOT_YET;

    //--------------------------------------------
    // �˗�����
    //--------------------------------------------
    int m_yearReq = 0;

    // 0���͑��݂��Ȃ����Ƃɒ��ӂ��邱��
    int m_monthReq = 0;

    // 0���͑��݂��Ȃ����Ƃɒ��ӂ��邱��
    int m_dayReq = 0;

    int m_hourReq = 0;
    int m_minuteReq = 0;
    int m_secondReq = 0;

    //--------------------------------------------
    // �J�n����
    //--------------------------------------------
    int m_yearStart = 0;

    // 0���͑��݂��Ȃ����Ƃɒ��ӂ��邱��
    int m_monthStart = 0;

    // 0���͑��݂��Ȃ����Ƃɒ��ӂ��邱��
    int m_dayStart = 0;

    int m_hourStart = 0;
    int m_minuteStart = 0;
    int m_secondStart = 0;

    //--------------------------------------------
    // ��������
    //--------------------------------------------
    int m_yearEnd = 0;

    // 0���͑��݂��Ȃ����Ƃɒ��ӂ��邱��
    int m_monthEnd = 0;

    // 0���͑��݂��Ȃ����Ƃɒ��ӂ��邱��
    int m_dayEnd = 0;

    int m_hourEnd = 0;
    int m_minuteEnd = 0;
    int m_secondEnd = 0;

};

class PatchItemInfo
{
public:

    void SetName(const std::string arg);
    std::string GetName() const;

    void SetPoison(const bool arg);
    bool GetPoison() const;

    void SetTryNum(const int arg);
    int GetTryNum();

    void SetAccurate(const float arg);
    float GetAccurate() const;

private:

    std::string m_name;
    bool m_poison = false;

    // �p�b�`�e�X�g���ꂽ��
    int m_tryNum = 0;

    // ����
    float m_accurate = 0.f;

};

class PatchTestManager
{
public:

    static PatchTestManager* Get();
    static void Destroy();
    void Init(const std::string& originFile,
              const std::string& saveFileInfo,
              const std::string& saveFileQue);

    void Save(const std::string& csvfileInfo,
              const std::string& csvfileQue);

    // �������E��1�b�Ɉ��Ă΂��z��
    void Update();

    void QueuePatchTest(const PatchTest& patchTest);
    std::vector<PatchTest> GetQueue();

    // ���߂�3��̃e�X�g���ʂ��擾�ł���ƕ֗���������Ȃ��B
    // GUI�ŕ\���������B
    std::array<PatchTest, 3> GetResultList(const std::string& name);

private:

    static PatchTestManager* m_obj;

    // Queue�ƌ�����std::vector���g���B
    // std::queue���g���Ɛ擪�Ɩ��������A�N�Z�X�ł��Ȃ��̂ŕ��ʂɍ���B
    std::vector<PatchTest> m_PatchTestQue;

    // �A�C�e����񃊃X�g
    // �ŁA�ł���Ȃ��A�͂��炩���ߌ��܂��Ă��Ȃ��B
    // �Q�[���J�n���Ƀ����_���Ō��܂�
    std::map<std::string, PatchItemInfo> m_infoMap;

    // TODO �A�C�e�����Ƃ̏n���x

};
}

