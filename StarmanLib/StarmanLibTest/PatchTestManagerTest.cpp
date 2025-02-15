#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/PatchTestManager.h"
#include "../StarmanLib/PowereggDateTime.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(PatchTestManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            PatchTestManager* obj = PatchTestManager::Get();
            Assert::AreEqual(true, obj != nullptr);
        }

        TEST_METHOD(TestMethod02)
        {
            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init("..\\StarmanLibTest\\patchTestOrigin.csv", "", "");

            auto que = obj->GetQueue();
            Assert::AreEqual(true, que.empty());

            auto resultList = obj->GetResultList("“ä‚Ì‘‚P");
            Assert::AreEqual(true, resultList.empty());
        }

        TEST_METHOD(TestMethod03)
        {
            {
                PowereggDateTime* obj = PowereggDateTime::GetObj();
                obj->Init("..\\StarmanLibTest\\datetime.csv");
            }

            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init("..\\StarmanLibTest\\patchTestOrigin.csv", "", "");

            obj->QueuePatchTest("“ä‚Ì‘‚P");

            auto que = obj->GetQueue();
            Assert::AreEqual(1, (int)que.size());

            auto resultList = obj->GetResultList("“ä‚Ì‘‚P");
            Assert::AreEqual(true, resultList.empty());
        }

        TEST_METHOD(TestMethod04)
        {
            PowereggDateTime* datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");

            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init("..\\StarmanLibTest\\patchTestOrigin.csv", "", "");

            obj->QueuePatchTest("“ä‚Ì‘‚P");
            obj->Update();

            datetime->IncreaseDateTime(0, 0, 2, 0, 0);
            obj->Update();

            auto que = obj->GetQueue();
            Assert::AreEqual(1, (int)que.size());

            Assert::AreEqual(true, que.at(0).GetState() == PatchTest::eState::FINISHED);

            auto resultList = obj->GetResultList("“ä‚Ì‘‚P");
            Assert::AreEqual(1, (int)resultList.size());
        }

        TEST_METHOD(TestMethod05)
        {
            PowereggDateTime* datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");

            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init("..\\StarmanLibTest\\patchTestOrigin.csv", "", "");

            obj->QueuePatchTest("“ä‚Ì‘‚P");
            obj->QueuePatchTest("“ä‚Ì‘‚P");
            obj->QueuePatchTest("“ä‚Ì‘‚Q");
            obj->QueuePatchTest("“ä‚Ì‘‚R");
            obj->Update();

            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();
            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();
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

            auto resultList1 = obj->GetResultList("“ä‚Ì‘‚P");
            Assert::AreEqual(2, (int)resultList1.size());

            auto resultList2 = obj->GetResultList("“ä‚Ì‘‚Q");
            Assert::AreEqual(0, (int)resultList2.size());

            auto resultList3 = obj->GetResultList("“ä‚Ì‘‚R");
            Assert::AreEqual(0, (int)resultList3.size());
        }

        // SaveŠÖ”‚Å—Ž‚¿‚È‚¢‚±‚Æ‚ðŠm”F‚·‚éƒeƒXƒg
        TEST_METHOD(TestMethod06)
        {
            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init("..\\StarmanLibTest\\patchTestOrigin.csv", "", "");
            obj->Save("..\\StarmanLibTest\\patchTestInfoSave2.csv",
                      "..\\StarmanLibTest\\patchTestQueSave2.csv");
        }

        // ƒpƒbƒ`ƒeƒXƒg‚ðs‚Á‚Ä‚©‚çSave‚·‚éƒeƒXƒg
        TEST_METHOD(TestMethod07)
        {
            PowereggDateTime* datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");

            PatchTestManager* obj = PatchTestManager::Get();
            obj->Init("..\\StarmanLibTest\\patchTestOrigin.csv", "", "");

            obj->QueuePatchTest("“ä‚Ì‘‚P");
            obj->QueuePatchTest("“ä‚Ì‘‚P");
            obj->QueuePatchTest("“ä‚Ì‘‚Q");
            obj->QueuePatchTest("“ä‚Ì‘‚R");
            obj->Update();

            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();
            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();
            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();
            datetime->IncreaseDateTime(0, 0, 0, 31, 0);
            obj->Update();

            obj->Save("..\\StarmanLibTest\\patchTestInfoSave2.csv",
                      "..\\StarmanLibTest\\patchTestQueSave2.csv");
        }

        // Save‚µ‚½ƒf[ƒ^‚ð“Ç‚ÝŽæ‚éƒeƒXƒg
        TEST_METHOD(TestMethod08)
        {
            {
                PowereggDateTime* datetime = PowereggDateTime::GetObj();
                datetime->Init("..\\StarmanLibTest\\datetime.csv");

                PatchTestManager* obj = PatchTestManager::Get();
                obj->Init("..\\StarmanLibTest\\patchTestOrigin.csv", "", "");

                obj->QueuePatchTest("“ä‚Ì‘‚P");
                obj->QueuePatchTest("“ä‚Ì‘‚P");
                obj->QueuePatchTest("“ä‚Ì‘‚Q");
                obj->QueuePatchTest("“ä‚Ì‘‚R");
                obj->Update();

                datetime->IncreaseDateTime(0, 0, 0, 31, 0);
                obj->Update();
                datetime->IncreaseDateTime(0, 0, 0, 31, 0);
                obj->Update();
                datetime->IncreaseDateTime(0, 0, 0, 31, 0);
                obj->Update();
                datetime->IncreaseDateTime(0, 0, 0, 31, 0);
                obj->Update();

                obj->Save("..\\StarmanLibTest\\patchTestInfoSave2.csv",
                          "..\\StarmanLibTest\\patchTestQueSave2.csv");
            }

            {
                PatchTestManager* obj = PatchTestManager::Get();
                obj->Init("..\\StarmanLibTest\\patchTestOrigin.csv",
                          "..\\StarmanLibTest\\patchTestInfoSave2.csv",
                          "..\\StarmanLibTest\\patchTestQueSave2.csv");

                auto que = obj->GetQueue();
                Assert::AreEqual(4, (int)que.size());
            }
        }
    };
}
