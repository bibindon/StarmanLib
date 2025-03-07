#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/CraftInfoManager.h"
#include "../StarmanLib/Inventory.h"
#include "../StarmanLib/ItemManager.h"
#include "../StarmanLib/Storehouse.h"

#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(CraftInfoManagerTest)
    {
    public:

        TEST_METHOD_INITIALIZE(Initialize)
        {
            ItemManager* itemManager = ItemManager::GetObj();
            itemManager->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

            Inventory* inventory = Inventory::GetObj();
            inventory->Init("..\\StarmanLibTest\\inventory.csv");

            StorehouseManager* storehouseManager = StorehouseManager::Get();
            storehouseManager->Init("..\\StarmanLibTest\\storehouseListOrigin.csv");
        }

        TEST_METHOD_CLEANUP(CleanUp)
        {
            CraftInfoManager::Destroy();
            StorehouseManager::Destroy();
            Inventory::Destroy();
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod01)
        {
            CraftInfoManager* obj = CraftInfoManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            CraftInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            CraftInfoManager* obj = CraftInfoManager::GetObj();
            obj->Init("..\\StarmanLibTest\\craftDef.csv");
            Assert::AreEqual(obj != nullptr, true);
            CraftInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            CraftInfoManager* obj = CraftInfoManager::GetObj();
            obj->Init("..\\StarmanLibTest\\craftDef.csv");
            std::vector<CraftOutput> work = obj->GetCraftItemList();
            Assert::AreEqual((int)work.size(), 57);
            CraftInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            CraftInfoManager* obj = CraftInfoManager::GetObj();
            obj->Init("..\\StarmanLibTest\\craftDef.csv");
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
                std::string work_sz = work.at(56).GetName();
                Assert::AreEqual(work_sz.c_str(), "�A�g���g���Ɏg����");

                int work_i = 0;

                work_i = work.at(56).GetNumber();
                Assert::AreEqual(work_i, 1);

                work_i = work.at(56).GetLevel();
                Assert::AreEqual(work_i, 5);
            }
            CraftInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            CraftInfoManager* obj = CraftInfoManager::GetObj();
            obj->Init("..\\StarmanLibTest\\craftDef.csv");
            std::vector<CraftOutput> work = obj->GetCraftItemList();

            {
                CraftInfo craftInfo = obj->GetCraftInfo(work.at(0));
                std::string work_sz;
                int work_i = 0;

                // �f�ނP
                work_sz = craftInfo.GetCraftMaterialDef(0).GetName();
                Assert::AreEqual(work_sz == "�ׂ��؂̊�", true);

                work_i = craftInfo.GetCraftMaterialDef(0).GetNumber();
                Assert::AreEqual(work_i == 100, true);

                work_i = craftInfo.GetCraftMaterialDef(0).GetLevel();
                Assert::AreEqual(work_i == -1, true);

                // �f�ނQ
                work_sz = craftInfo.GetCraftMaterialDef(1).GetName();
                Assert::AreEqual(work_sz == "�c�^", true);

                work_i = craftInfo.GetCraftMaterialDef(1).GetNumber();
                Assert::AreEqual(work_i == 100, true);

                work_i = craftInfo.GetCraftMaterialDef(1).GetLevel();
                Assert::AreEqual(work_i == -1, true);
            }
            {
                CraftInfo craftInfo = obj->GetCraftInfo(work.at(56));
                std::string work_sz;
                int work_i = 0;

                // �f�ނP
                work_sz = craftInfo.GetCraftMaterialDef(0).GetName();
                Assert::AreEqual(work_sz == "�؂̎}", true);

                work_i = craftInfo.GetCraftMaterialDef(0).GetNumber();
                Assert::AreEqual(work_i == 1, true);

                work_i = craftInfo.GetCraftMaterialDef(0).GetLevel();
                Assert::AreEqual(work_i == -1, true);

                // �f�ނQ
                work_sz = craftInfo.GetCraftMaterialDef(1).GetName();
                Assert::AreEqual(work_sz == "�����`�̐΁i���j", true);

                work_i = craftInfo.GetCraftMaterialDef(1).GetNumber();
                Assert::AreEqual(work_i == 1, true);

                work_i = craftInfo.GetCraftMaterialDef(1).GetLevel();
                Assert::AreEqual(work_i == -1, true);

                // �f�ނR
                work_sz = craftInfo.GetCraftMaterialDef(2).GetName();
                Assert::AreEqual(work_sz == "�c�^", true);

                work_i = craftInfo.GetCraftMaterialDef(2).GetNumber();
                Assert::AreEqual(work_i == 2, true);

                work_i = craftInfo.GetCraftMaterialDef(2).GetLevel();
                Assert::AreEqual(work_i == -1, true);
            }
            CraftInfoManager::Destroy();
        }
    };
}
