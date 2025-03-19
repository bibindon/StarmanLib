#include "CppUnitTest.h"
#include "../StarmanLib/CraftSystem.h"
#include "../StarmanLib/ItemManager.h"
#include "../StarmanLib/Storehouse.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include "../StarmanLib/PowereggDateTime.h"
#include "../StarmanLib/Voyage.h"

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
            itemManager->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

            StorehouseManager* storehouseManager = StorehouseManager::Get();
            storehouseManager->Init("..\\StarmanLibTest\\storehouseListOrigin.csv");

            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();
            powereggDateTime->Init("..\\StarmanLibTest\\datetime.csv");
        }

        TEST_METHOD_CLEANUP(CleanUp)
        {
            PowereggDateTime::Destroy();
            CraftInfoManager::Destroy();
            StorehouseManager::Destroy();
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
            std::string work;
            obj->QueueCraftRequest("イカダ", &work, 1);

            CraftSystem::Destroy();
        }

        // クラフト用の素材がなくてキューイング失敗
        TEST_METHOD(TestMethod07)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work;
            bool result = obj->QueueCraftRequest("イカダ", &work, 1);

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

            std::string work;
            obj->QueueCraftRequest("アトラトル", &work, 1);

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
            auto storehouse = StorehouseManager::Get()->GetCurrentActiveStorehouse();
            int temp = 0;

            temp = storehouse->CountItem("細い木の幹");
            Assert::AreEqual(temp, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work;
            obj->QueueCraftRequest("石槍", &work, 1);

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), false);

            temp = storehouse->CountItem("細い木の幹");
            Assert::AreEqual(temp, 9);

            temp = storehouse->CountItem("いい形の石（槍）");
            Assert::AreEqual(temp, 9);

            obj->UpdateCraftStatus();

            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), true);

            temp = storehouse->CountItem("細い木の幹");
            Assert::AreEqual(temp, 9);

            temp = storehouse->CountItem("いい形の石（槍）");
            Assert::AreEqual(temp, 9);

            CraftSystem::Destroy();
        }

        // キューイングしてスタートして完了する
        TEST_METHOD(TestMethod10)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            
            std::string work;
            obj->QueueCraftRequest("石槍", &work, 1);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            // クラフト要求がなくなっていること
            Assert::AreEqual(true, (int)craftRequestList.size() == 0);

            CraftSystem::Destroy();
        }

        // キューイングしてスタートして完了して倉庫に完成品が追加される
        TEST_METHOD(TestMethod11)
        {
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;
            work = storehouse->CountItem("石槍");

            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work2;
            obj->QueueCraftRequest("石槍", &work2, 1);

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
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;
            work = storehouse->CountItem("石槍");

            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work2;
            obj->QueueCraftRequest("石槍", &work2, 1);
            obj->QueueCraftRequest("石槍", &work2, 1);

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
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;

            work = storehouse->CountItem("石槍");
            Assert::AreEqual(work, 10);

            work = storehouse->CountItem("アトラトル");
            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work2;
            obj->QueueCraftRequest("石槍", &work2, 1);
            obj->QueueCraftRequest("アトラトル", &work2, 1);

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

            std::string work;
            obj->QueueCraftRequest("石槍", &work, 1);

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

                std::string work;
                obj->QueueCraftRequest("石槍", &work, 1);

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

            std::string work;
            obj->QueueCraftRequest("石槍", &work, 1);

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

        // キューイングしてキャンセル
        // 開始していないクラフトをキャンセルしたら素材が返ってくる
        TEST_METHOD(TestMethod16_2)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            std::string work;
            obj->QueueCraftRequest("石槍", &work, 1);
            obj->QueueCraftRequest("石槍", &work, 1);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 12時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

            obj->UpdateCraftStatus();

            auto storehouse = StorehouseManager::Get()->GetCurrentActiveStorehouse();
            auto mat1 = storehouse->CountItem("細い木の幹");
            auto mat2 = storehouse->CountItem("いい形の石（槍）");

            Assert::AreEqual(8, mat1);
            Assert::AreEqual(8, mat2);

            obj->CancelCraftStart(1);

            mat1 = storehouse->CountItem("細い木の幹");
            mat2 = storehouse->CountItem("いい形の石（槍）");
            Assert::AreEqual(9, mat1);
            Assert::AreEqual(9, mat2);

            CraftSystem::Destroy();
        }

        // キューイングしてキャンセル
        // 開始したクラフトをキャンセルしたら素材が返ってこない
        TEST_METHOD(TestMethod16_3)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work;
            obj->QueueCraftRequest("石槍", &work, 1);
            obj->QueueCraftRequest("石槍", &work, 1);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 12時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

            obj->UpdateCraftStatus();

            auto storehouse = StorehouseManager::Get()->GetCurrentActiveStorehouse();
            auto mat1 = storehouse->CountItem("細い木の幹");
            auto mat2 = storehouse->CountItem("いい形の石（槍）");

            Assert::AreEqual(8, mat1);
            Assert::AreEqual(8, mat2);

            obj->CancelCraftStart(0);

            mat1 = storehouse->CountItem("細い木の幹");
            mat2 = storehouse->CountItem("いい形の石（槍）");
            Assert::AreEqual(8, mat1);
            Assert::AreEqual(8, mat2);

            CraftSystem::Destroy();
        }

        // 複数キューイングしてキャンセル
        TEST_METHOD(TestMethod17)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            std::string work;
            obj->QueueCraftRequest("石槍", &work, 1);
            obj->QueueCraftRequest("石槍", &work, 1);
            obj->QueueCraftRequest("石槍", &work, 1);

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
        TEST_METHOD(TestMethod18)
        {
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;
            bool work_b = false;
            work = storehouse->CountItem("石槍", -1);

            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            work = obj->GetCraftsmanSkill("石槍");
            Assert::AreEqual(work, -1);

            std::string work2;
            work_b = obj->QueueCraftRequest("石槍", &work2, 1);
            work_b = obj->QueueCraftRequest("石槍", &work2, 1);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("石槍", -1);

            Assert::AreEqual(work, 11);

            work = obj->GetCraftsmanSkill("石槍");
            Assert::AreEqual(work, -1);

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("石槍", -1);

            Assert::AreEqual(work, 12);

            work = obj->GetCraftsmanSkill("石槍");
            Assert::AreEqual(work, 1);

            CraftSystem::Destroy();
        }

        // 職人の熟練度が高い状態でクラフトを依頼すると同じ素材を使っても
        // 強化度の高いアイテムが作られる。
        // ダークソウルのような古い武器を素材に使う、ということはしない。
        TEST_METHOD(TestMethod19)
        {
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;
            bool work_b = false;

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work2;
            work_b = obj->QueueCraftRequest("石槍", &work2, 1);

            // 職人に石槍の製造を依頼すると、この時点では強化値なしの石槍を作り始める。
            work = obj->GetCraftRequestList().front().GetCraftInfo().GetOutput().GetLevel();
            Assert::AreEqual(work, -1);

            work_b = obj->QueueCraftRequest("石槍", &work2, 1);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            // 1日と1時間、時を進める
            // ここで職人のレベルアップ。＋１の石槍を作れるようになる
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            // ここで石槍を予約したら＋１の石槍が作られる
            work_b = obj->QueueCraftRequest("石槍", &work2, 1);

            // ＋１の石槍が予約されているか？
            work = obj->GetCraftRequestList().front().GetCraftInfo().GetOutput().GetLevel();
            Assert::AreEqual(work, 1);

            CraftSystem::Destroy();
        }

        // 武器を作り、武器管理クラスが更新されるかテスト
        TEST_METHOD(TestMethod20)
        {
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;
            bool work_b = false;

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work2;
            work_b = obj->QueueCraftRequest("石槍", &work2, 1);

            // 武器の制作を開始
            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            // 武器の制作が完了
            obj->UpdateCraftStatus();

            CraftSystem::Destroy();
        }
        
        // 素材に武器がある場合。
        //TEST_METHOD(TestMethod21)
        //{
        //    Storehouse* storehouse = Storehouse::GetObj();
        //    int work = 0;
        //    bool work_b = false;

        //    CraftSystem* obj = CraftSystem::GetObj();
        //    obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
        //              "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

        //    work_b = obj->QueueCraftRequest("石槍");

        //    // 職人に石槍の製造を依頼すると、この時点では強化値なしの石槍を作り始める。
        //    work = obj->GetCraftRequestList().front().GetCraftInfo().GetOutput().GetLevel();
        //    Assert::AreEqual(work, -1);

        //    work_b = obj->QueueCraftRequest("石槍");

        //    obj->UpdateCraftStatus();

        //    PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

        //    // 1日と1時間、時を進める
        //    powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

        //    obj->UpdateCraftStatus();

        //    // 1日と1時間、時を進める
        //    // ここで職人のレベルアップ。＋１の石槍を作れるようになる
        //    powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

        //    obj->UpdateCraftStatus();

        //    // ここで石槍を予約したら＋１の石槍が作られる
        //    work_b = obj->QueueCraftRequest("石槍");

        //    // ＋１の石槍が予約されているか？
        //    work = obj->GetCraftRequestList().front().GetCraftInfo().GetOutput().GetLevel();
        //    Assert::AreEqual(work, 1);

        //    CraftSystem::Destroy();
        //}

        // イカダのクラフト
        // 完成しても倉庫に格納されず、拠点の近くに配置される
        TEST_METHOD(TestMethod21)
        {
            auto raftNum1 = (int)Voyage::Get()->GetRaftList().size();

            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            for (int i = 0; i < 200; ++i)
            {
                storehouse->AddItem("細い木の幹");
                storehouse->AddItem("ツタ");
            }

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work;
            obj->QueueCraftRequest("イカダ", &work);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1日と1時間、時を進める
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            auto raftCount = storehouse->CountItem("イカダ");

            Assert::AreEqual(0, raftCount);

            auto raftNum2 = (int)Voyage::Get()->GetRaftList().size();

            Assert::AreEqual(1, raftNum2 - raftNum1);

            CraftSystem::Destroy();
        }
    };
}
