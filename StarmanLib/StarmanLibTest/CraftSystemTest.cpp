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

    TEST_CLASS(CraftSystemTest)
    {
    public:

        TEST_METHOD_INITIALIZE(Initialize)
        {
            ItemManager* itemManager = ItemManager::GetObj();
            itemManager->Init("..\\StarmanLibTest\\item.csv");

            Inventory* inventory = Inventory::GetObj();
            inventory->Init("..\\StarmanLibTest\\inventory.csv");

            Storehouse* storehouse = Storehouse::GetObj();
            storehouse->Init("..\\StarmanLibTest\\storehouse.csv");

            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();
            powereggDateTime->Init("..\\StarmanLibTest\\datetime.csv");
        }

        TEST_METHOD_CLEANUP(CleanUp)
        {
            PowereggDateTime::Destroy();
            CraftInfoManager::Destroy();
            Storehouse::Destroy();
            Inventory::Destroy();
            ItemManager::Destroy();
        }
        TEST_METHOD(TestMethod01)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueue.csv");
            Assert::AreEqual(obj != nullptr, true);
            CraftSystem::Destroy();
        }

        // 職人のレベルが取得できるかテスト
        TEST_METHOD(TestMethod03)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueue.csv");
            int result = false;
            result = obj->GetCraftsmanSkill("イカダ");
            Assert::AreEqual(result, -1);

            result = obj->GetCraftsmanSkill("木の棒");
            Assert::AreEqual(result, 1);

            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueue.csv");
            int result = 0;
            obj->SetCraftsmanSkill("イカダ", 1);
            result = obj->GetCraftsmanSkill("イカダ");
            Assert::AreEqual(result, 1);

            obj->SetCraftsmanSkill("木の棒", 2);
            result = obj->GetCraftsmanSkill("木の棒");
            Assert::AreEqual(result, 2);

            CraftSystem::Destroy();
        }

        // 職人のスキルが保存できていることを確認
        TEST_METHOD(TestMethod05)
        {
            {
                CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
                craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                          "..\\StarmanLibTest\\craftsmanQueue.csv");

                bool result = false;
                obj->SetCraftsmanSkill("イカダ", 1);
                obj->SetCraftsmanSkill("アトラトルに使う槍", 1);
                obj->Save("..\\StarmanLibTest\\craftsmanSkillSave.csv",
                          "..\\StarmanLibTest\\craftsmanQueueSave.csv");

                CraftSystem::Destroy();
                CraftInfoManager::Destroy();
            }
            {
                CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
                craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("..\\StarmanLibTest\\craftsmanSkillSave.csv",
                          "..\\StarmanLibTest\\craftsmanQueueSave.csv");

                int result = false;
                result = obj->GetCraftsmanSkill("イカダ");
                Assert::AreEqual(result, 1);

                result = obj->GetCraftsmanSkill("アトラトルに使う槍");
                Assert::AreEqual(result, 1);

                CraftSystem::Destroy();
                CraftInfoManager::Destroy();
            }
        }

        TEST_METHOD(TestMethod06)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueue.csv");
            obj->QueueCraftRequest("イカダ");

            CraftSystem::Destroy();
        }

        // クラフト用の素材がなくてキューイング失敗
        TEST_METHOD(TestMethod07)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            bool result = obj->QueueCraftRequest("イカダ");

            Assert::AreEqual(result, false);

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 0, true);

            CraftSystem::Destroy();
        }

        // キューイングしてスタート
        TEST_METHOD(TestMethod08)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
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
        }

        // キューイングした時点でクラフト用素材がインベントリからなくなる
        TEST_METHOD(TestMethod09)
        {
            Inventory* inventory = Inventory::GetObj();
            int temp = 0;

            temp = inventory->CountItem("細い木の幹");
            Assert::AreEqual(temp, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("石槍");

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), false);

            temp = inventory->CountItem("細い木の幹");
            Assert::AreEqual(temp, 9);

            temp = inventory->CountItem("いい形の石（槍）");
            Assert::AreEqual(temp, 9);

            obj->UpdateCraftStatus();

            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), true);

            temp = inventory->CountItem("細い木の幹");
            Assert::AreEqual(temp, 9);

            temp = inventory->CountItem("いい形の石（槍）");
            Assert::AreEqual(temp, 9);

            CraftSystem::Destroy();
        }

        // キューイングしてスタートして完了する
        TEST_METHOD(TestMethod10)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
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
        }

        // キューイングしてスタートして完了して倉庫に完成品が追加される
        TEST_METHOD(TestMethod11)
        {
            Storehouse* storehouse = Storehouse::GetObj();
            int work = 0;
            work = storehouse->CountItem("石槍");

            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("石槍");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("石槍");

            Assert::AreEqual(work, 11);

            CraftSystem::Destroy();
        }

        // 複数キューイングしてスタートして完了して倉庫に完成品が現れる
        TEST_METHOD(TestMethod12)
        {
            Storehouse* storehouse = Storehouse::GetObj();
            int work = 0;
            work = storehouse->CountItem("石槍");

            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("石槍");
            obj->QueueCraftRequest("石槍");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("石槍");

            Assert::AreEqual(work, 11);

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("石槍");

            Assert::AreEqual(work, 12);

            CraftSystem::Destroy();
        }

        // 複数キューイングしてスタートして完了して倉庫に完成品が現れる(2)
        TEST_METHOD(TestMethod13)
        {
            Storehouse* storehouse = Storehouse::GetObj();
            int work = 0;

            work = storehouse->CountItem("石槍");
            Assert::AreEqual(work, 10);

            work = storehouse->CountItem("アトラトル");
            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("石槍");
            obj->QueueCraftRequest("アトラトル");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("石槍");
            Assert::AreEqual(work, 11);

            work = storehouse->CountItem("アトラトル");
            Assert::AreEqual(work, 10);

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("石槍");
            Assert::AreEqual(work, 11);

            work = storehouse->CountItem("アトラトル");
            Assert::AreEqual(work, 11);

            CraftSystem::Destroy();
        }

        // 進捗度が取得できる
        TEST_METHOD(TestMethod14)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("石槍");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 12時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

            obj->UpdateCraftStatus();

            int progress = obj->GetProgress();

            Assert::AreEqual(progress, 50);

            CraftSystem::Destroy();
        }

        // 保存できる
        TEST_METHOD(TestMethod15)
        {
            {
                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                          "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
                obj->QueueCraftRequest("石槍");

                obj->UpdateCraftStatus();

                PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

                // 12時間、時を進める
                powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

                obj->UpdateCraftStatus();

                int progress = obj->GetProgress();

                Assert::AreEqual(progress, 50);
                obj->Save("..\\StarmanLibTest\\craftsmanSkillSave.csv",
                          "..\\StarmanLibTest\\craftsmanQueueSave.csv");

                CraftSystem::Destroy();
            }
            {
                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("..\\StarmanLibTest\\craftsmanSkillSave.csv",
                          "..\\StarmanLibTest\\craftsmanQueueSave.csv");

                int work = 0;

                work = obj->GetCraftRequestList().size();
                Assert::AreEqual(work, 1);

                work = obj->GetProgress();
                Assert::AreEqual(work, 50);

                CraftRequest craftRequest = obj->GetCraftRequestList().front();
                Assert::AreEqual(craftRequest.GetCrafting(), true);

                Assert::AreEqual(craftRequest.GetStartHour(), 33);
                Assert::AreEqual(craftRequest.GetStartMinute(), 44);
                Assert::AreEqual(craftRequest.GetStartSecond(), 55);

                Assert::AreEqual(craftRequest.GetFinishHour(), 33);
                Assert::AreEqual(craftRequest.GetFinishMinute(), 44);
                Assert::AreEqual(craftRequest.GetFinishSecond(), 55);

                CraftSystem::Destroy();
            }
        }

        // キューイングしてキャンセル
        TEST_METHOD(TestMethod16)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("石槍");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 12時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

            obj->UpdateCraftStatus();

            obj->CancelCraftStart(0);

            int size = obj->GetCraftRequestList().size();

            Assert::AreEqual(size, 0);

            CraftSystem::Destroy();
        }

        // 複数キューイングしてキャンセル
        TEST_METHOD(TestMethod17)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("石槍");
            obj->QueueCraftRequest("石槍");
            obj->QueueCraftRequest("石槍");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 12時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

            obj->UpdateCraftStatus();

            obj->CancelCraftStart(0);
            obj->CancelCraftStart(0);

            int size = obj->GetCraftRequestList().size();

            Assert::AreEqual(size, 1);

            CraftSystem::Destroy();
        }

        // 規定回数、クラフトを行うと強化値の高いアイテムがクラフトされるようになる。


        // 職人の熟練度が高い状態でクラフトを依頼すると同じ素材を使っても
        // 強化度の高いアイテムが作られる。
        // ダークソウルのような古い武器を素材に使う、ということはしない。

        // 素材に武器がある場合。

    };
}
