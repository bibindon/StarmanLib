#include "CppUnitTest.h"
#include "../StarmanLib/Help.h"
#include "../StarmanLib/PowereggDateTime.h"
#include "../StarmanLib/NpcStatusManager.h"
#include "../StarmanLib/CraftSystem.h"
#include "../StarmanLib/Storehouse.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(HelpTest)
    {
    public:

        // public関数を呼ぶだけのテスト
        TEST_METHOD(TestMethod01)
        {
            auto help = Help::Get();

            // Target
            Assert::IsNotNull(help);

            Help::Destroy();
        }

        // public関数を呼ぶだけのテスト
        TEST_METHOD(TestMethod02)
        {
            auto help = Help::Get();
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

            // Target
            help->Init("..\\StarmanLibTest\\help.csv");

            ItemManager::Destroy();
            Help::Destroy();
        }

        // public関数を呼ぶだけのテスト
        TEST_METHOD(TestMethod03)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");

            // Target
            help->Save("..\\StarmanLibTest\\helpSave.csv");

            ItemManager::Destroy();
            Help::Destroy();
        }

        // public関数を呼ぶだけのテスト
        TEST_METHOD(TestMethod04)
        {
            NpcStatusManager::GetObj()->Init("..\\StarmanLibTest\\npcStatus.csv");
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");

            // Target
            help->Update();

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
            NpcStatusManager::Destroy();
        }

        // public関数を呼ぶだけのテスト
        TEST_METHOD(TestMethod05)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");

            // Target
            auto receiveItems = help->ReceiveItems("sankakuman");

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // アイテムを受け取れるかのテスト
        TEST_METHOD(TestMethod06)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems = help->ReceiveItems("sankakuman");

            // Target
            Assert::AreEqual<size_t>(3, receiveItems.size());
            Assert::AreEqual(3, receiveItems.at(0).GetId());
            Assert::AreEqual(5, receiveItems.at(1).GetId());
            Assert::AreEqual(6, receiveItems.at(2).GetId());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // アイテムを受け取れるかのテスト
        TEST_METHOD(TestMethod07)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems = help->ReceiveItems("shikakuman");

            // Target
            Assert::AreEqual<size_t>(0, receiveItems.size());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // 16時を過ぎたら更新されることを確認するテスト
        TEST_METHOD(TestMethod08)
        {
            NpcStatusManager::GetObj()->Init("..\\StarmanLibTest\\npcStatus.csv");
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems1 = help->ReceiveItems("sankakuman");
            auto receiveItems2 = help->ReceiveItems("shikakuman");
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems("sankakuman");
            auto receiveItems4 = help->ReceiveItems("shikakuman");

            // Target
            Assert::AreEqual(false,
                             receiveItems1.size() == receiveItems3.size() &&
                             receiveItems2.size() == receiveItems4.size() &&
                             receiveItems1.at(0).GetId() == receiveItems3.at(0).GetId() &&
                             receiveItems1.at(1).GetId() == receiveItems3.at(1).GetId() &&
                             receiveItems1.at(2).GetId() == receiveItems3.at(2).GetId());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
            NpcStatusManager::Destroy();
        }

        // 取得したら空になっていること
        TEST_METHOD(TestMethod09)
        {
            NpcStatusManager::GetObj()->Init("..\\StarmanLibTest\\npcStatus.csv");
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems1 = help->ReceiveItems("sankakuman");
            auto receiveItems2 = help->ReceiveItems("shikakuman");
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems("sankakuman");
            auto receiveItems4 = help->ReceiveItems("shikakuman");

            receiveItems3 = help->ReceiveItems("sankakuman");
            receiveItems4 = help->ReceiveItems("shikakuman");

            // Target
            Assert::AreEqual(true, receiveItems3.empty());
            Assert::AreEqual(true, receiveItems4.empty());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
            NpcStatusManager::Destroy();
        }

        // 取得したら空になり、その後、16時を跨ぐまでは受け取れないこと。
        TEST_METHOD(TestMethod10)
        {
            NpcStatusManager::GetObj()->Init("..\\StarmanLibTest\\npcStatus.csv");
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems1 = help->ReceiveItems("sankakuman");
            auto receiveItems2 = help->ReceiveItems("shikakuman");
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems("sankakuman");
            auto receiveItems4 = help->ReceiveItems("shikakuman");

            datetime->IncreaseDateTime(0, 0, 1, 0, 0);
            help->Update();

            receiveItems3 = help->ReceiveItems("sankakuman");
            receiveItems4 = help->ReceiveItems("shikakuman");

            // Target
            Assert::AreEqual(true, receiveItems3.empty());
            Assert::AreEqual(true, receiveItems4.empty());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
            NpcStatusManager::Destroy();
        }

        // 16時を跨いだらアイテムが補充され、もう一度16時を跨いだらもう一度アイテムが補充されること。
        TEST_METHOD(TestMethod11)
        {
            NpcStatusManager::GetObj()->Init("..\\StarmanLibTest\\npcStatus.csv");
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems1 = help->ReceiveItems("sankakuman");
            auto receiveItems2 = help->ReceiveItems("shikakuman");
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems("sankakuman");
            auto receiveItems4 = help->ReceiveItems("shikakuman");

            datetime->IncreaseDateTime(0, 1, 0, 0, 0);
            help->Update();

            receiveItems3 = help->ReceiveItems("sankakuman");
            receiveItems4 = help->ReceiveItems("shikakuman");

            datetime->IncreaseDateTime(0, 1, 0, 0, 0);
            help->Update();

            receiveItems3 = help->ReceiveItems("sankakuman");
            receiveItems4 = help->ReceiveItems("shikakuman");

            // Target
            Assert::AreEqual(false, receiveItems3.empty());
            Assert::AreEqual(false, receiveItems4.empty());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
            NpcStatusManager::Destroy();
        }

        // イカダをクラフトしていたらアイテムを受け取れないことを確認するテスト
        TEST_METHOD(TestMethod12)
        {
            NpcStatusManager::GetObj()->Init("..\\StarmanLibTest\\npcStatus.csv");
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");

            CraftInfoManager::GetObj()->Init("..\\StarmanLibTest\\craftDef.csv");
            CraftSystem::GetObj()->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                                        "..\\StarmanLibTest\\craftsmanQueue.csv");

            StorehouseManager::Get()->Init("..\\StarmanLibTest\\storehouseListOrigin.csv");

            std::string err;
            CraftSystem::GetObj()->QueueCraftRequest("イカダ", &err);

            auto receiveItems1 = help->ReceiveItems("sankakuman");
            auto receiveItems2 = help->ReceiveItems("shikakuman");

            Assert::AreEqual(true, receiveItems1.empty());
            Assert::AreEqual(true, receiveItems2.empty());

            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems("sankakuman");
            auto receiveItems4 = help->ReceiveItems("shikakuman");

            Assert::AreEqual(true, receiveItems1.empty());
            Assert::AreEqual(true, receiveItems2.empty());

            StorehouseManager::Destroy();
            CraftSystem::Destroy();
            CraftInfoManager::Destroy();

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
            NpcStatusManager::Destroy();
        }
    };
}
