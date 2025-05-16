#include "CppUnitTest.h"
#include "../StarmanLib/PatchTestManager.h"
#include "../StarmanLib/PowereggDateTime.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <tchar.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(PatchTestManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            PatchTestManager::Destroy();
            PatchTestManager* obj = PatchTestManager::Get();
            Assert::AreEqual(true, obj != nullptr);
        }

        TEST_METHOD(TestMethod02)
        {
            PatchTestManager::Destroy();
            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init(_T("..\\StarmanLibTest\\patchTestOrigin.csv"), _T(""), _T(""));

            auto que = obj->GetQueue();
            Assert::AreEqual(true, que.empty());

            auto resultList = obj->GetResultList(_T("謎の草１"));
            Assert::AreEqual(true, resultList.empty());
        }

        TEST_METHOD(TestMethod03)
        {
            {
                PowereggDateTime* obj = PowereggDateTime::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\datetime.csv"));
            }

            PatchTestManager::Destroy();
            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init(_T("..\\StarmanLibTest\\patchTestOrigin.csv"), _T(""), _T(""));

            obj->QueuePatchTest(_T("謎の草１"));

            auto que = obj->GetQueue();
            Assert::AreEqual(1, (int)que.size());

            auto resultList = obj->GetResultList(_T("謎の草１"));
            Assert::AreEqual(true, resultList.empty());
        }

        TEST_METHOD(TestMethod04)
        {
            PowereggDateTime* datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));

            PatchTestManager::Destroy();
            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init(_T("..\\StarmanLibTest\\patchTestOrigin.csv"), _T(""), _T(""));

            obj->QueuePatchTest(_T("謎の草１"));
            obj->Update();

            datetime->IncreaseDateTime(0, 0, 2, 0, 0);
            obj->Update();

            auto que = obj->GetQueue();
            Assert::AreEqual(1, (int)que.size());

            Assert::AreEqual(true, que.at(0).GetState() == PatchTest::eState::FINISHED);

            auto resultList = obj->GetResultList(_T("謎の草１"));
            Assert::AreEqual(1, (int)resultList.size());
        }

        TEST_METHOD(TestMethod05)
        {
            PowereggDateTime* datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));

            PatchTestManager::Destroy();
            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init(_T("..\\StarmanLibTest\\patchTestOrigin.csv"), _T(""), _T(""));

            obj->QueuePatchTest(_T("謎の草１"));
            obj->QueuePatchTest(_T("謎の草１"));
            obj->QueuePatchTest(_T("謎の草２"));
            obj->Update();

            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();

            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();

            obj->QueuePatchTest(_T("謎の草３"));
            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();

            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();

            auto que = obj->GetQueue();
            Assert::AreEqual(4, (int)que.size());

            Assert::AreEqual(true, que.at(0).GetState() == PatchTest::eState::FINISHED);
            Assert::AreEqual(true, que.at(1).GetState() == PatchTest::eState::FINISHED);
            Assert::AreEqual(true, que.at(2).GetState() == PatchTest::eState::STARTED);
            Assert::AreEqual(true, que.at(3).GetState() == PatchTest::eState::NOT_START);

            auto resultList1 = obj->GetResultList(_T("謎の草１"));
            Assert::AreEqual(2, (int)resultList1.size());

            auto resultList2 = obj->GetResultList(_T("謎の草２"));
            Assert::AreEqual(0, (int)resultList2.size());

            auto resultList3 = obj->GetResultList(_T("謎の草３"));
            Assert::AreEqual(0, (int)resultList3.size());
        }

        // Init関数で落ちないことを確認するテスト
        TEST_METHOD(TestMethod05_2)
        {
            PatchTestManager::Destroy();
            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init(_T("..\\StarmanLibTest\\patchTestOrigin.csv"),
                      _T("..\\StarmanLibTest\\patchTestInfoSave.csv"),
                      _T("..\\StarmanLibTest\\patchTestQueSave.csv"));
        }

        // Init関数でデータが読み込まれていることを確認する
        TEST_METHOD(TestMethod05_3)
        {
            PatchTestManager::Destroy();
            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init(_T("..\\StarmanLibTest\\patchTestOrigin.csv"),
                      _T("..\\StarmanLibTest\\patchTestInfoSave.csv"),
                      _T("..\\StarmanLibTest\\patchTestQueSave.csv"));

            auto que = obj->GetQueue();
            Assert::AreEqual(true, que.size() != 0);
        }

        // Save関数で落ちないことを確認するテスト
        TEST_METHOD(TestMethod06)
        {
            PatchTestManager::Destroy();
            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init(_T("..\\StarmanLibTest\\patchTestOrigin.csv"), _T(""), _T(""));
            obj->Save(_T("..\\StarmanLibTest\\patchTestInfoSave2.csv"),
                      _T("..\\StarmanLibTest\\patchTestQueSave2.csv"));
        }

        // パッチテストを行ってからSaveするテスト
        TEST_METHOD(TestMethod07)
        {
            PowereggDateTime* datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));

            PatchTestManager::Destroy();
            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init(_T("..\\StarmanLibTest\\patchTestOrigin.csv"), _T(""), _T(""));

            obj->QueuePatchTest(_T("謎の草１"));
            obj->QueuePatchTest(_T("謎の草１"));
            obj->QueuePatchTest(_T("謎の草２"));
            obj->Update();

            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();

            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();

            obj->QueuePatchTest(_T("謎の草３"));
            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();

            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();

            obj->Save(_T("..\\StarmanLibTest\\patchTestInfoSave2.csv"),
                      _T("..\\StarmanLibTest\\patchTestQueSave2.csv"));
        }

        // Saveしたデータを読み取るテスト
        TEST_METHOD(TestMethod08)
        {
            {
                PowereggDateTime* datetime = PowereggDateTime::GetObj();
                datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));

                PatchTestManager::Destroy();
                PatchTestManager* obj = PatchTestManager::Get();
                obj->Init(_T("..\\StarmanLibTest\\patchTestOrigin.csv"), _T(""), _T(""));

                obj->QueuePatchTest(_T("謎の草１"));
                obj->QueuePatchTest(_T("謎の草１"));
                obj->QueuePatchTest(_T("謎の草２"));
                obj->Update();

                datetime->IncreaseDateTime(0, 0, 0, 31, 0);
                obj->Update();

                datetime->IncreaseDateTime(0, 0, 0, 31, 0);
                obj->Update();

                obj->QueuePatchTest(_T("謎の草３"));
                datetime->IncreaseDateTime(0, 0, 0, 31, 0);
                obj->Update();

                datetime->IncreaseDateTime(0, 0, 0, 31, 0);
                obj->Update();

                obj->Save(_T("..\\StarmanLibTest\\patchTestInfoSave2.csv"),
                          _T("..\\StarmanLibTest\\patchTestQueSave2.csv"));
            }

            {
                PatchTestManager* obj = PatchTestManager::Get();
                obj->Init(_T("..\\StarmanLibTest\\patchTestOrigin.csv"),
                          _T("..\\StarmanLibTest\\patchTestInfoSave2.csv"),
                          _T("..\\StarmanLibTest\\patchTestQueSave2.csv"));

                auto que = obj->GetQueue();
                Assert::AreEqual(4, (int)que.size());
            }
        }
    };
}
