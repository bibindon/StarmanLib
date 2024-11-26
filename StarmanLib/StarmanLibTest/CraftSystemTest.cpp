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
#include "../StarmanLib/PowereggDateTime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

void Initialize()
{
    ItemManager* itemManager = ItemManager::GetObj();
    itemManager->Init("item.csv");

    Inventory* inventory = Inventory::GetObj();
    inventory->Init("inventory.csv");

    Storehouse* storehouse = Storehouse::GetObj();
    storehouse->Init("storehouse.csv");

    CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
    craftInfoManager->Init("craftDef.csv");

    PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();
    powereggDateTime->Init("datetime.csv");
}

void Finalize()
{
    PowereggDateTime::Destroy();
    CraftInfoManager::Destroy();
    Storehouse::Destroy();
    Inventory::Destroy();
    ItemManager::Destroy();
}

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
            Initialize();

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");
            obj->QueueCraftRequest("イカダ");

            CraftSystem::Destroy();

            Finalize();
        }

        // クラフト用の素材がなくてキューイング失敗
        TEST_METHOD(TestMethod07)
        {
            Initialize();

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueueEmpty.csv");
            bool result = obj->QueueCraftRequest("イカダ");

            Assert::AreEqual(result, false);

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 0, true);

            CraftSystem::Destroy();

            Finalize();
        }

        // キューイングしてスタート
        TEST_METHOD(TestMethod08)
        {
            Initialize();

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("アトラトル");

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), false);

            obj->UpdateCraftStatus();

            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), true);

            CraftSystem::Destroy();

            Finalize();
        }

        // キューイングした時点でクラフト用素材がインベントリからなくなる
        TEST_METHOD(TestMethod09)
        {
            Initialize();

            Inventory* inventory = Inventory::GetObj();
            int temp = 0;

            temp = inventory->CountItem("細い木の幹");
            Assert::AreEqual(temp, 15);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("石槍");

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), false);

            temp = inventory->CountItem("細い木の幹");
            Assert::AreEqual(temp, 14);

            temp = inventory->CountItem("いい形の石（槍）");
            Assert::AreEqual(temp, 1);

            obj->UpdateCraftStatus();

            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), true);

            temp = inventory->CountItem("細い木の幹");
            Assert::AreEqual(temp, 14);

            temp = inventory->CountItem("いい形の石（槍）");
            Assert::AreEqual(temp, 1);

            CraftSystem::Destroy();

            Finalize();
        }

        // キューイングしてスタートして完了する
        TEST_METHOD(TestMethod10)
        {
            Initialize();

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("石槍");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            // クラフト要求がなくなっていること
            Assert::AreEqual((int)craftRequestList.size() == 0, true);

            CraftSystem::Destroy();

            Finalize();
        }

        // キューイングしてスタートして完了して倉庫に完成品が追加される
        TEST_METHOD(TestMethod11)
        {
            Initialize();

            Storehouse* storehouse = Storehouse::GetObj();
            int work = 0;
            work = storehouse->CountItem("石槍");

            Assert::AreEqual(work, 0);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("石槍");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("石槍");

            Assert::AreEqual(work, 1);

            CraftSystem::Destroy();

            Finalize();
        }

        // 複数キューイングしてスタートして完了して倉庫に完成品が現れる

        // 進捗度が取得できる

        // 保存できる

        // キューイングしてキャンセル

        // 複数キューイングしてキャンセル

        // 素材に武器がある場合。

    };
}
