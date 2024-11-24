#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/CraftInfoManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StarmanLibTest
{

    TEST_CLASS(CraftInfoManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            CraftInfoManager* obj = CraftInfoManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            CraftInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            CraftInfoManager* obj = CraftInfoManager::GetObj();
            obj->Init("craftDef.csv");
            Assert::AreEqual(obj != nullptr, true);
            CraftInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            CraftInfoManager* obj = CraftInfoManager::GetObj();
            obj->Init("craftDef.csv");
            std::vector<CraftOutput> work = obj->GetCraftItemList();
            Assert::AreEqual(work.size() == 20, true);
            CraftInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            CraftInfoManager* obj = CraftInfoManager::GetObj();
            obj->Init("craftDef.csv");
            std::vector<CraftOutput> work = obj->GetCraftItemList();

            {
                std::string work_sz = work.at(0).GetName();
                Assert::AreEqual(work_sz == "�C�J�_", true);

                int work_i = 0;

                work_i = work.at(0).GetNumber();
                Assert::AreEqual(work_i == 1, true);

                work_i = work.at(0).GetLevel();
                Assert::AreEqual(work_i == -1, true);
            }
            {
                std::string work_sz = work.at(1).GetName();
                Assert::AreEqual(work_sz == "�C�J�_", true);

                int work_i = 0;

                work_i = work.at(1).GetNumber();
                Assert::AreEqual(work_i == 1, true);

                work_i = work.at(1).GetLevel();
                Assert::AreEqual(work_i == 1, true);
            }
            {
                std::string work_sz = work.at(19).GetName();
                Assert::AreEqual(work_sz == "�A�g���g���Ɏg����", true);

                int work_i = 0;

                work_i = work.at(19).GetNumber();
                Assert::AreEqual(work_i == 1, true);

                work_i = work.at(19).GetLevel();
                Assert::AreEqual(work_i == -1, true);
            }
            CraftInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            CraftInfoManager* obj = CraftInfoManager::GetObj();
            obj->Init("craftDef.csv");
            std::vector<CraftOutput> work = obj->GetCraftItemList();

            {
                CraftInfo craftInfo = obj->GetCraftInfo(work.at(0));
                std::string work_sz;
                int work_i = 0;

                // �f�ނP
                work_sz = craftInfo.GetCraftMaterial(0).GetName();
                Assert::AreEqual(work_sz == "�ׂ��؂̊�", true);

                work_i = craftInfo.GetCraftMaterial(0).GetNumber();
                Assert::AreEqual(work_i == 100, true);

                work_i = craftInfo.GetCraftMaterial(0).GetLevel();
                Assert::AreEqual(work_i == -1, true);

                // �f�ނQ
                work_sz = craftInfo.GetCraftMaterial(1).GetName();
                Assert::AreEqual(work_sz == "�c�^", true);

                work_i = craftInfo.GetCraftMaterial(1).GetNumber();
                Assert::AreEqual(work_i == 100, true);

                work_i = craftInfo.GetCraftMaterial(1).GetLevel();
                Assert::AreEqual(work_i == -1, true);
            }
            {
                CraftInfo craftInfo = obj->GetCraftInfo(work.at(19));
                std::string work_sz;
                int work_i = 0;

                // �f�ނP
                work_sz = craftInfo.GetCraftMaterial(0).GetName();
                Assert::AreEqual(work_sz == "�؂̎}", true);

                work_i = craftInfo.GetCraftMaterial(0).GetNumber();
                Assert::AreEqual(work_i == 1, true);

                work_i = craftInfo.GetCraftMaterial(0).GetLevel();
                Assert::AreEqual(work_i == -1, true);

                // �f�ނQ
                work_sz = craftInfo.GetCraftMaterial(1).GetName();
                Assert::AreEqual(work_sz == "�����`�̐΁i���j", true);

                work_i = craftInfo.GetCraftMaterial(1).GetNumber();
                Assert::AreEqual(work_i == 1, true);

                work_i = craftInfo.GetCraftMaterial(1).GetLevel();
                Assert::AreEqual(work_i == -1, true);

                // �f�ނR
                work_sz = craftInfo.GetCraftMaterial(2).GetName();
                Assert::AreEqual(work_sz == "�c�^", true);

                work_i = craftInfo.GetCraftMaterial(2).GetNumber();
                Assert::AreEqual(work_i == 2, true);

                work_i = craftInfo.GetCraftMaterial(2).GetLevel();
                Assert::AreEqual(work_i == -1, true);
            }
            CraftInfoManager::Destroy();
        }
    };
}
