#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include "PatchTestManager.h"
#include "PowereggDateTime.h"
#include "Util.h"

using namespace NSStarmanLib;

PatchTestManager* PatchTestManager::m_obj = nullptr;

PatchTestManager* NSStarmanLib::PatchTestManager::Get()
{
    if (m_obj == nullptr)
    {
        m_obj = new PatchTestManager();
    }

    return m_obj;
}

void NSStarmanLib::PatchTestManager::Destroy()
{
    delete m_obj;
    m_obj = nullptr;
}

void NSStarmanLib::PatchTestManager::Init(const std::string& originFile,
                                          const std::string& saveFileInfo,
                                          const std::string& saveFileQue)
{
    //-------------------------------------------------------------
    // �ŁA�łł͂Ȃ��A�Ƃ������͂��炩���ߌ��܂��Ă���킯�ł͂Ȃ��B
    // �Q�[���J�n���Ƀ����_���Ō��܂�
    //-------------------------------------------------------------

    // saveFileInfo����Ȃ�Q�[���J�n���B
    // �ŁA�łł͂Ȃ������쐬����
    if (saveFileInfo.empty())
    {
        std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(originFile, false);

        // ���ݎ����̏��ŏ�����
        srand((unsigned int)time(NULL));

        for (size_t i = 1; i < vvs.size(); ++i)
        {
            m_infoMap[vvs.at(i).at(0)].SetName(vvs.at(i).at(0));

            int rnd = rand();

            // 50%�̊m���œ�
            if (rnd % 100 <= 49)
            {
                m_infoMap[vvs.at(i).at(0)].SetPoison(true);
            }
            else
            {
                m_infoMap[vvs.at(i).at(0)].SetPoison(false);
            }

            // �ŏ��͐���60��
            m_infoMap[vvs.at(i).at(0)].SetAccurate(0.6f);
        }
    }
    else
    {
        {
            std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(saveFileInfo, false);

            for (size_t i = 1; i < vvs.size(); ++i)
            {
                if (vvs.at(i).at(1) == "y")
                {
                    m_infoMap[vvs.at(i).at(0)].SetPoison(true);
                }
                else if (vvs.at(i).at(1) == "n")
                {
                    m_infoMap[vvs.at(i).at(0)].SetPoison(false);
                }
                else
                {
                    throw std::exception();
                }

                int tryNum = std::stoi(vvs.at(i).at(2));
                m_infoMap[vvs.at(i).at(0)].SetTryNum(tryNum);

                float accurate = std::stof(vvs.at(i).at(3));
                m_infoMap[vvs.at(i).at(0)].SetAccurate(accurate);
            }
        }

        {
            std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(saveFileQue, false);

            for (size_t i = 1; i < vvs.size(); ++i)
            {
                PatchTest patchTest;

                patchTest.SetItemName(vvs.at(i).at(0));

                if (vvs.at(i).at(1) == "NOT_START")
                {
                    patchTest.SetState(PatchTest::eState::NOT_START);
                }
                else if (vvs.at(i).at(1) == "STARTED")
                {
                    patchTest.SetState(PatchTest::eState::STARTED);
                }
                else if (vvs.at(i).at(1) == "FINISHED")
                {
                    patchTest.SetState(PatchTest::eState::FINISHED);
                }
                else
                {
                    throw std::exception();
                }

                {
                    if (vvs.at(i).at(2).empty())
                    {
                        throw std::exception();
                    }

                    auto vs = Util::split(vvs.at(i).at(2));

                    patchTest.SetDateTimeReq(std::stoi(vs.at(0)),
                                             std::stoi(vs.at(1)),
                                             std::stoi(vs.at(2)),
                                             std::stoi(vs.at(3)),
                                             std::stoi(vs.at(4)),
                                             std::stoi(vs.at(5)));
                }

                {
                    if (!vvs.at(i).at(3).empty())
                    {
                        auto vs = Util::split(vvs.at(i).at(3));

                        patchTest.SetDateTimeStart(std::stoi(vs.at(0)),
                                                   std::stoi(vs.at(1)),
                                                   std::stoi(vs.at(2)),
                                                   std::stoi(vs.at(3)),
                                                   std::stoi(vs.at(4)),
                                                   std::stoi(vs.at(5)));
                    }
                }

                {
                    if (vvs.at(i).size() >= 5 || !vvs.at(i).at(4).empty())
                    {
                        auto vs = Util::split(vvs.at(i).at(4));

                        patchTest.SetDateTimeEnd(std::stoi(vs.at(0)),
                                                 std::stoi(vs.at(1)),
                                                 std::stoi(vs.at(2)),
                                                 std::stoi(vs.at(3)),
                                                 std::stoi(vs.at(4)),
                                                 std::stoi(vs.at(5)));
                    }
                }

                {
                    if (vvs.at(i).size() <= 5 || vvs.at(i).at(5).empty())
                    {
                        patchTest.SetResult(PatchTest::eResult::NOT_YET);
                    }
                    else if (vvs.at(i).at(5) == "��")
                    {
                        patchTest.SetResult(PatchTest::eResult::POISON);
                    }
                    else if (vvs.at(i).at(5) == "�łł͂Ȃ�")
                    {
                        patchTest.SetResult(PatchTest::eResult::NOT_POISON);
                    }
                    else
                    {
                        throw std::exception();
                    }
                }
            }
        }
    }
}

void NSStarmanLib::PatchTestManager::Save(const std::string& csvfileInfo,
                                          const std::string& csvfileQue)
{
    {
        std::vector<std::vector<std::string>> vvs;
        std::vector<std::string> vs;

        vs.push_back("�A�C�e����");
        vs.push_back("�Ő�");
        vs.push_back("�p�b�`�e�X�g��");
        vs.push_back("����");
        vvs.push_back(vs);
        vs.clear();

        for (auto it = m_infoMap.begin(); it != m_infoMap.end(); ++it)
        {
            vs.clear();

            vs.push_back(it->second.GetName());

            if (it->second.GetPoison())
            {
                vs.push_back("y");
            }
            else
            {
                vs.push_back("n");
            }
            
            vs.push_back(std::to_string(it->second.GetTryNum()));
            vs.push_back(std::to_string(it->second.GetAccurate()));
            vvs.push_back(vs);
        }

        Util::WriteToCsv(csvfileInfo, vvs, false);
    }

    {
        std::vector<std::vector<std::string>> vvs;
        std::vector<std::string> vs;

        vs.push_back("�A�C�e����");
        vs.push_back("���");
        vs.push_back("�\�����");
        vs.push_back("�J�n����");
        vs.push_back("��������");
        vs.push_back("�e�X�g����");
        vvs.push_back(vs);
        vs.clear();

        for (auto it = m_PatchTestQue.begin(); it != m_PatchTestQue.end(); ++it)
        {
            vs.clear();

            vs.push_back(it->GetItemName());

            if (it->GetState() == PatchTest::eState::NOT_START)
            {
                vs.push_back("NOT_START");
            }
            else if (it->GetState() == PatchTest::eState::STARTED)
            {
                vs.push_back("STARTED");
            }
            else if (it->GetState() == PatchTest::eState::FINISHED)
            {
                vs.push_back("FINISHED");
            }
            else
            {
                throw std::exception();
            }
            
            {
                std::string work;
                int y, M, d, h, m, s;
                it->GetDateTimeReq(&y, &M, &d, &h, &m, &s);
                work += std::to_string(y) + ":";
                work += std::to_string(M) + ":";
                work += std::to_string(d) + ":";
                work += std::to_string(h) + ":";
                work += std::to_string(m) + ":";
                work += std::to_string(s);

                vs.push_back(work);
            }

            {
                std::string work;
                int y, M, d, h, m, s;
                it->GetDateTimeStart(&y, &M, &d, &h, &m, &s);
                work += std::to_string(y) + ":";
                work += std::to_string(M) + ":";
                work += std::to_string(d) + ":";
                work += std::to_string(h) + ":";
                work += std::to_string(m) + ":";
                work += std::to_string(s);

                vs.push_back(work);
            }

            {
                std::string work;
                int y, M, d, h, m, s;
                it->GetDateTimeEnd(&y, &M, &d, &h, &m, &s);
                work += std::to_string(y) + ":";
                work += std::to_string(M) + ":";
                work += std::to_string(d) + ":";
                work += std::to_string(h) + ":";
                work += std::to_string(m) + ":";
                work += std::to_string(s);

                vs.push_back(work);
            }

            if (it->GetResult() == PatchTest::eResult::NOT_YET)
            {
                // do nothing
            }
            else if (it->GetResult() == PatchTest::eResult::POISON)
            {
                vs.push_back("��");
            }
            else if (it->GetResult() == PatchTest::eResult::NOT_POISON)
            {
                vs.push_back("�łł͂Ȃ�");
            }

            vvs.push_back(vs);
        }

        Util::WriteToCsv(csvfileQue, vvs, false);
    }
}

void NSStarmanLib::PatchTestManager::Update()
{
    if (PowereggDateTime::GetObj() == nullptr)
    {
        return;
    }

    auto dateTime = PowereggDateTime::GetObj();

    // ���ׂ�FINISHED�Ȃ��邱�ƂȂ�
    bool allFinish =
        std::all_of(m_PatchTestQue.begin(), m_PatchTestQue.end(),
                    [](PatchTest patchTest)
                    {
                        return patchTest.GetState() == PatchTest::eState::FINISHED;
                    });

    if (allFinish)
    {
        return;
    }

    // ���s���̃e�X�g�����邩
    bool existStarted =
        std::any_of(m_PatchTestQue.begin(), m_PatchTestQue.end(),
                    [](PatchTest patchTest)
                    {
                        return patchTest.GetState() == PatchTest::eState::STARTED;
                    });

    // ���s���̃e�X�g������Ȃ�΁A�����������߂��Ă��Ȃ���������s��
    if (existStarted)
    {
        auto it = std::find_if(m_PatchTestQue.begin(), m_PatchTestQue.end(),
                               [](PatchTest patchTest)
                               {
                                   return patchTest.GetState() == PatchTest::eState::STARTED;
                               });

        int y, M, d, h, m, s;
        it->GetDateTimeEnd(&y, &M, &d, &h, &m, &s);

        auto finished = PowereggDateTime::FromPastToFuture(y, M, d, h, m, s,
                                                           dateTime->GetYear(),
                                                           dateTime->GetMonth(),
                                                           dateTime->GetDay(),
                                                           dateTime->GetHour(),
                                                           dateTime->GetMinute(),
                                                           dateTime->GetSecond());

        if (finished)
        {
            // ��������
            it->SetState(PatchTest::eState::FINISHED);

            auto name = it->GetItemName();
            auto accurate = m_infoMap[name].GetAccurate();

            // ���𗦂ɂ�錋�ʔ���

            srand((unsigned int)time(NULL));

            // 0 ~ 99�̗���
            int rnd = rand() % 100;

            int nAccurate = (int)accurate * 100;

            // ����
            if (rnd < nAccurate)
            {
                auto poison = m_infoMap[name].GetPoison();
                if (poison)
                {
                    it->SetResult(PatchTest::eResult::POISON);
                }
                else
                {
                    it->SetResult(PatchTest::eResult::NOT_POISON);
                }
            }
            // �s����
            else
            {
                auto poison = m_infoMap[name].GetPoison();
                if (poison)
                {
                    it->SetResult(PatchTest::eResult::NOT_POISON);
                }
                else
                {
                    it->SetResult(PatchTest::eResult::POISON);
                }
            }

            // �p�b�`�e�X�g�񐔂��X�V
            auto tryNum = m_infoMap[name].GetTryNum();
            ++tryNum;
            m_infoMap[name].SetTryNum(tryNum);

            // ���𗦂��X�V
            accurate += 0.1f;
            if (accurate >= 0.9f)
            {
                accurate = 0.9f;
            }

            m_infoMap[name].SetAccurate(accurate);

            // �J�n����
            ++it;
            if (it != m_PatchTestQue.end())
            {
                it->SetState(PatchTest::eState::STARTED);
                it->SetDateTimeStart(dateTime->GetYear(),
                                     dateTime->GetMonth(),
                                     dateTime->GetDay(),
                                     dateTime->GetHour(),
                                     dateTime->GetMinute(),
                                     dateTime->GetSecond());

                it->SetDateTimeEnd(dateTime->GetYear(),
                                   dateTime->GetMonth(),
                                   dateTime->GetDay(),
                                   dateTime->GetHour() + 1,
                                   dateTime->GetMinute(),
                                   dateTime->GetSecond());
            }
        }
    }
    // ���s���̃e�X�g���Ȃ��Ȃ�΁A��ԌÂ��˗����J�n����
    else
    {
        // �˗��͖����ɒǉ�����̂Ő擪�قǌÂ��˗�
        for (size_t i = 0; i < m_PatchTestQue.size(); ++i)
        {
            auto& patchTest = m_PatchTestQue.at(i);

            // ����������������J�n����
            if (patchTest.GetState() == PatchTest::eState::NOT_START)
            {
                patchTest.SetState(PatchTest::eState::STARTED);
                patchTest.SetDateTimeStart(dateTime->GetYear(),
                                           dateTime->GetMonth(),
                                           dateTime->GetDay(),
                                           dateTime->GetHour(),
                                           dateTime->GetMinute(),
                                           dateTime->GetSecond());

                patchTest.SetDateTimeEnd(dateTime->GetYear(),
                                         dateTime->GetMonth(),
                                         dateTime->GetDay(),
                                         dateTime->GetHour() + 1,
                                         dateTime->GetMinute(),
                                         dateTime->GetSecond());

                break;
            }
        }
    }
}

void NSStarmanLib::PatchTestManager::QueuePatchTest(const std::string& name)
{
    auto it = m_infoMap.find(name);
    if (it == m_infoMap.end())
    {
        throw std::exception();
    }

    // ��x�Ɉ˗��ł���̂͂R��܂�
    auto notFinishCount =
        std::count_if(m_PatchTestQue.begin(), m_PatchTestQue.end(),
                      [](PatchTest patchTest)
                      {
                          return patchTest.GetState() != PatchTest::eState::FINISHED;
                      });

    if (notFinishCount >= 4)
    {
        return;
    }

    PatchTest patchTest;

    patchTest.SetItemName(name);

    auto dateTime = PowereggDateTime::GetObj();

    patchTest.SetDateTimeReq(dateTime->GetYear(),
                             dateTime->GetMonth(),
                             dateTime->GetDay(),
                             dateTime->GetHour(),
                             dateTime->GetMinute(),
                             dateTime->GetSecond()
                             );

    m_PatchTestQue.push_back(patchTest);
}

std::vector<PatchTest> NSStarmanLib::PatchTestManager::GetQueue()
{
    return m_PatchTestQue;
}

// �擪����ԐV�����A�����Ɍ������قǌÂ��e�X�g����
std::vector<PatchTest> NSStarmanLib::PatchTestManager::GetResultList(const std::string& name)
{
    std::vector<PatchTest> resultList;

    for (auto it = m_PatchTestQue.rbegin(); it != m_PatchTestQue.rend(); ++it)
    {
        if (it->GetItemName() == name)
        {
            if (it->GetState() == PatchTest::eState::FINISHED)
            {
                resultList.push_back(*it);
            }
        }
    }

    return resultList;
}

void NSStarmanLib::PatchTest::SetItemName(const std::string& arg)
{
    m_itemName = arg;
}

std::string NSStarmanLib::PatchTest::GetItemName() const
{
    return m_itemName;
}

void NSStarmanLib::PatchTest::SetDateTimeReq(const int y, const int M, const int d,
                                             const int h, const int m, const int s)
{
    m_yearReq = y;
    m_monthReq = M;
    m_dayReq = d;

    m_hourReq = h;
    m_minuteReq = m;
    m_secondReq = s;
}

void NSStarmanLib::PatchTest::GetDateTimeReq(int* y, int* M, int* d, int* h, int* m, int* s)
{
    *y = m_yearReq;
    *M = m_monthReq;
    *d = m_dayReq;

    *h = m_hourReq;
    *m = m_minuteReq;
    *s = m_secondReq;
}

void NSStarmanLib::PatchTest::SetDateTimeStart(int y, int M, int d, int h, int m, int s)
{
    m_yearStart = y;
    m_monthStart = M;
    m_dayStart = d;

    m_hourStart = h;
    m_minuteStart = m;
    m_secondStart = s;
}

void NSStarmanLib::PatchTest::GetDateTimeStart(int* y, int* M, int* d, int* h, int* m, int* s)
{
    *y = m_yearStart;
    *M = m_monthStart;
    *d = m_dayStart;

    *h = m_hourStart;
    *m = m_minuteStart;
    *s = m_secondStart;
}

void NSStarmanLib::PatchTest::SetDateTimeEnd(int y, int M, int d, int h, int m, int s)
{
    m_yearEnd = y;
    m_monthEnd = M;
    m_dayEnd = d;

    m_hourEnd = h;
    m_minuteEnd = m;
    m_secondEnd = s;
}

void NSStarmanLib::PatchTest::GetDateTimeEnd(int* y, int* M, int* d, int* h, int* m, int* s)
{
    *y = m_yearEnd;
    *M = m_monthEnd;
    *d = m_dayEnd;

    *h = m_hourEnd;
    *m = m_minuteEnd;
    *s = m_secondEnd;
}

void NSStarmanLib::PatchTest::SetState(const eState arg)
{
    m_eState = arg;
}

PatchTest::eState NSStarmanLib::PatchTest::GetState() const
{
    return m_eState;
}

void NSStarmanLib::PatchTest::SetResult(const eResult result)
{
    m_eResult = result;
}

PatchTest::eResult NSStarmanLib::PatchTest::GetResult() const
{
    return m_eResult;
}

void NSStarmanLib::PatchItemInfo::SetName(const std::string arg)
{
    m_name = arg;
}

std::string NSStarmanLib::PatchItemInfo::GetName() const
{
    return m_name;
}

void NSStarmanLib::PatchItemInfo::SetPoison(const bool arg)
{
    m_poison = arg;
}

bool NSStarmanLib::PatchItemInfo::GetPoison() const
{
    return m_poison;
}

void NSStarmanLib::PatchItemInfo::SetTryNum(const int arg)
{
    m_tryNum = arg;
}

int NSStarmanLib::PatchItemInfo::GetTryNum()
{
    return m_tryNum;
}

void NSStarmanLib::PatchItemInfo::SetAccurate(const float arg)
{
    m_accurate = arg;
}

float NSStarmanLib::PatchItemInfo::GetAccurate() const
{
    return m_accurate;
}
