#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/NpcStatusManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StarmanLibTest
{

    TEST_CLASS(NpcStatusManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            NpcStatusManager* obj = NpcStatusManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            NpcStatusManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            NpcStatusManager* obj = NpcStatusManager::GetObj();
            obj->Init("npcStatus.csv");
            Assert::AreEqual(obj != nullptr, true);
            NpcStatusManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            NpcStatusManager* obj = NpcStatusManager::GetObj();
            obj->Init("npcStatus.csv");
            NpcStatus npc = obj->GetNpcStatus("�T���J�N�}��");
            float work = 0.f;

            work = npc.GetCarbo();
            Assert::AreEqual(work == 11.f, true);

            work = npc.GetProtein();
            Assert::AreEqual(work == 22.f, true);

            work = npc.GetLipid();
            Assert::AreEqual(work == 33.f, true);

            work = npc.GetVitamin();
            Assert::AreEqual(work == 44.f, true);

            work = npc.GetMineral();
            Assert::AreEqual(work == 55.f, true);

            NpcStatusManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            NpcStatusManager* obj = NpcStatusManager::GetObj();
            obj->Init("npcStatus.csv");
            NpcStatus npc = obj->GetNpcStatus("�V�J�N�}��");
            bool work = false;

            work = npc.GetRynenContract();
            Assert::AreEqual(work, true);

            work = npc.GetDrinkWordbress();
            Assert::AreEqual(work, true);

            work = npc.GetDead();
            Assert::AreEqual(work, true);

            NpcStatusManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            {
                NpcStatusManager* obj = NpcStatusManager::GetObj();
                obj->Init("npcStatus.csv");
                NpcStatus npc = obj->GetNpcStatus("�_�C�P�C�}��");
                bool work = false;

                npc.SetCarbo(1.f);
                npc.SetProtein(2.f);
                npc.SetLipid(3.f);
                npc.SetVitamin(4.f);
                npc.SetMineral(5.f);
                npc.SetRynenContract();
                npc.SetDrinkWordbress(true);
                npc.SetDead();
                obj->SetNpcStatus("�_�C�P�C�}��", npc);
                obj->Save("npcStatusSave.csv");
                NpcStatusManager::Destroy();
            }
            {
                NpcStatusManager* obj = NpcStatusManager::GetObj();
                obj->Init("npcStatusSave.csv");
                NpcStatus npc = obj->GetNpcStatus("�_�C�P�C�}��");
                bool work_b = false;
                float work_f = 0.f;

                work_f = npc.GetCarbo();
                Assert::AreEqual(work_f, 1.f);

                work_f = npc.GetProtein();
                Assert::AreEqual(work_f, 2.f);

                work_f = npc.GetLipid();
                Assert::AreEqual(work_f, 3.f);

                work_f = npc.GetVitamin();
                Assert::AreEqual(work_f, 4.f);

                work_f = npc.GetMineral();
                Assert::AreEqual(work_f, 5.f);

                work_b = npc.GetRynenContract();
                Assert::AreEqual(work_b, true);

                work_b = npc.GetDrinkWordbress();
                Assert::AreEqual(work_b, true);

                work_b = npc.GetDead();
                Assert::AreEqual(work_b, true);

                NpcStatusManager::Destroy();
            }
        }
    };
}
