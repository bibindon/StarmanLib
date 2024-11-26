#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/CraftSystem.h"
#include "../StarmanLib/ItemManager.h"
#include "../StarmanLib/Inventory.h"
#include "../StarmanLib/Storehouse.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(CraftSystemTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");
            Assert::AreEqual(obj != nullptr, true);
            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");
            bool result = false;
            result = obj->GetCraftsmanSkill("イカダ");
            Assert::AreEqual(result, true);

            result = obj->GetCraftsmanSkill("イカダ", 1);
            Assert::AreEqual(result, false);

            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");
            bool result = false;
            obj->SetCraftsmanSkill("イカダ");
            result = obj->GetCraftsmanSkill("イカダ");
            Assert::AreEqual(result, true);

            obj->SetCraftsmanSkill("イカダ", 1);
            result = obj->GetCraftsmanSkill("イカダ", 1);
            Assert::AreEqual(result, true);

            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            {
                CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
                craftInfoManager->Init("craftDef.csv");

                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");

                bool result = false;
                obj->SetCraftsmanSkill("イカダ", 1);
                obj->SetCraftsmanSkill("石付き鉄パイプ");
                obj->Save("craftsmanSkillSave.csv", "craftsmanQueueSave.csv");

                CraftSystem::Destroy();
                CraftInfoManager::Destroy();
            }
            {
                CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
                craftInfoManager->Init("craftDef.csv");

                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("craftsmanSkillSave.csv", "craftsmanQueueSave.csv");

                bool result = false;
                result = obj->GetCraftsmanSkill("イカダ", 1);
                Assert::AreEqual(result, true);

                result = obj->GetCraftsmanSkill("石付き鉄パイプ");
                Assert::AreEqual(result, true);

                CraftSystem::Destroy();
                CraftInfoManager::Destroy();
            }
        }

        TEST_METHOD(TestMethod06)
        {
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init("item.csv");

                Inventory* inventory = Inventory::GetObj();
                inventory->Init("inventory.csv");

                Storehouse* storehouse = Storehouse::GetObj();
                storehouse->Init("storehouse.csv");

                CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
                craftInfoManager->Init("craftDef.csv");
            }

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");
            obj->QueueCraftRequest("イカダ");

            CraftSystem::Destroy();
        }
        // TODO キューイングしてスタート
        // TODO キューイングしてスタートして素材がなくなる
        // TODO キューイングしてスタートして完了する
        // TODO キューイングしてスタートして完了して倉庫に完成品が現れる
        // TODO 複数キューイングしてスタートして完了して倉庫に完成品が現れる
        // TODO 進捗度が取得できる
        // TODO 保存できる
        // TODO キューイングしてキャンセル
        // TODO 複数キューイングしてキャンセル

    };
}
