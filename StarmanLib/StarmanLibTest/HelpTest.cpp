﻿#include "CppUnitTest.h"
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
            obj->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));

            // Target
            help->Init(_T("..\\StarmanLibTest\\help.csv"));

            ItemManager::Destroy();
            Help::Destroy();
        }

        // public関数を呼ぶだけのテスト
        TEST_METHOD(TestMethod03)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));
            auto help = Help::Get();
            help->Init(_T("..\\StarmanLibTest\\help.csv"));

            // Target
            help->Save(_T("..\\StarmanLibTest\\helpSave.csv"));

            ItemManager::Destroy();
            Help::Destroy();
        }

        // public関数を呼ぶだけのテスト
        TEST_METHOD(TestMethod04)
        {
            NpcStatusManager::GetObj()->Init(_T("..\\StarmanLibTest\\npcStatus.csv"));
            ItemManager* obj = ItemManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));
            auto help = Help::Get();
            help->Init(_T("..\\StarmanLibTest\\help.csv"));
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));

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
            obj->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));
            auto help = Help::Get();
            help->Init(_T("..\\StarmanLibTest\\help.csv"));
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));

            // Target
            auto receiveItems = help->ReceiveItems(_T("sankakuman"));

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // アイテムを受け取れるかのテスト
        TEST_METHOD(TestMethod06)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));
            auto help = Help::Get();
            help->Init(_T("..\\StarmanLibTest\\help.csv"));
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));
            auto receiveItems = help->ReceiveItems(_T("sankakuman"));

            // Target
            Assert::AreEqual<size_t>(3, receiveItems.size());
            Assert::AreEqual<std::wstring>(L"sotetsu", receiveItems.at(0).GetId());
            Assert::AreEqual<std::wstring>(L"coconut", receiveItems.at(1).GetId());
            Assert::AreEqual<std::wstring>(L"coconutRipe", receiveItems.at(2).GetId());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // アイテムを受け取れるかのテスト
        TEST_METHOD(TestMethod07)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));
            auto help = Help::Get();
            help->Init(_T("..\\StarmanLibTest\\help.csv"));
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));
            auto receiveItems = help->ReceiveItems(_T("shikakuman"));

            // Target
            Assert::AreEqual<size_t>(0, receiveItems.size());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // 16時を過ぎたら更新されることを確認するテスト
        TEST_METHOD(TestMethod08)
        {
            NpcStatusManager::GetObj()->Init(_T("..\\StarmanLibTest\\npcStatus.csv"));
            ItemManager* obj = ItemManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));
            auto help = Help::Get();
            help->Init(_T("..\\StarmanLibTest\\help.csv"));
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));
            auto receiveItems1 = help->ReceiveItems(_T("sankakuman"));
            auto receiveItems2 = help->ReceiveItems(_T("shikakuman"));
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems(_T("sankakuman"));
            auto receiveItems4 = help->ReceiveItems(_T("shikakuman"));

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
            NpcStatusManager::GetObj()->Init(_T("..\\StarmanLibTest\\npcStatus.csv"));
            ItemManager* obj = ItemManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));
            auto help = Help::Get();
            help->Init(_T("..\\StarmanLibTest\\help.csv"));
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));
            auto receiveItems1 = help->ReceiveItems(_T("sankakuman"));
            auto receiveItems2 = help->ReceiveItems(_T("shikakuman"));
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems(_T("sankakuman"));
            auto receiveItems4 = help->ReceiveItems(_T("shikakuman"));

            receiveItems3 = help->ReceiveItems(_T("sankakuman"));
            receiveItems4 = help->ReceiveItems(_T("shikakuman"));

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
            NpcStatusManager::GetObj()->Init(_T("..\\StarmanLibTest\\npcStatus.csv"));
            ItemManager* obj = ItemManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));
            auto help = Help::Get();
            help->Init(_T("..\\StarmanLibTest\\help.csv"));
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));
            auto receiveItems1 = help->ReceiveItems(_T("sankakuman"));
            auto receiveItems2 = help->ReceiveItems(_T("shikakuman"));
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems(_T("sankakuman"));
            auto receiveItems4 = help->ReceiveItems(_T("shikakuman"));

            datetime->IncreaseDateTime(0, 0, 1, 0, 0);
            help->Update();

            receiveItems3 = help->ReceiveItems(_T("sankakuman"));
            receiveItems4 = help->ReceiveItems(_T("shikakuman"));

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
            NpcStatusManager::GetObj()->Init(_T("..\\StarmanLibTest\\npcStatus.csv"));
            ItemManager* obj = ItemManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));
            auto help = Help::Get();
            help->Init(_T("..\\StarmanLibTest\\help.csv"));
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));
            auto receiveItems1 = help->ReceiveItems(_T("sankakuman"));
            auto receiveItems2 = help->ReceiveItems(_T("shikakuman"));
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems(_T("sankakuman"));
            auto receiveItems4 = help->ReceiveItems(_T("shikakuman"));

            datetime->IncreaseDateTime(0, 1, 0, 0, 0);
            help->Update();

            receiveItems3 = help->ReceiveItems(_T("sankakuman"));
            receiveItems4 = help->ReceiveItems(_T("shikakuman"));

            datetime->IncreaseDateTime(0, 1, 0, 0, 0);
            help->Update();

            receiveItems3 = help->ReceiveItems(_T("sankakuman"));
            receiveItems4 = help->ReceiveItems(_T("shikakuman"));

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
            NpcStatusManager::GetObj()->Init(_T("..\\StarmanLibTest\\npcStatus.csv"));
            ItemManager* obj = ItemManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));
            auto help = Help::Get();
            help->Init(_T("..\\StarmanLibTest\\help.csv"));
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init(_T("..\\StarmanLibTest\\datetime.csv"));

            CraftInfoManager::GetObj()->Init(_T("..\\StarmanLibTest\\craftDef.csv"));
            CraftSystem::GetObj()->Init(_T("..\\StarmanLibTest\\craftsmanSkill.csv"),
                                        _T("..\\StarmanLibTest\\craftsmanQueue.csv"));

            StorehouseManager::Get()->Init(_T("..\\StarmanLibTest\\storehouseListOrigin.csv"));

            std::wstring err;
            CraftSystem::GetObj()->QueueCraftRequest(_T("raft"), &err);

            auto receiveItems1 = help->ReceiveItems(_T("sankakuman"));
            auto receiveItems2 = help->ReceiveItems(_T("shikakuman"));

            Assert::AreEqual(true, receiveItems1.empty());
            Assert::AreEqual(true, receiveItems2.empty());

            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems(_T("sankakuman"));
            auto receiveItems4 = help->ReceiveItems(_T("shikakuman"));

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
