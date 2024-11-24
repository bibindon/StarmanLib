#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/ItemManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(ItemManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            ItemManager* obj = ItemManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("item.csv");
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("item.csv");
            ItemInfo itemInfo = obj->GetItemInfo("ÉXÉ}Éz");
            Assert::AreEqual(itemInfo.GetImagePath() == "sumaho.png", true);
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("item.csv");
            ItemInfo itemInfo = obj->GetItemInfo("çïÇ¢äL");
            Assert::AreEqual(itemInfo.GetImagePath() == "mussels.png", true);
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("item.csv");
            ItemInfo itemInfo = obj->GetItemInfo("çïÇ¢äL");
            Assert::AreEqual(itemInfo.GetType() == ItemInfo::ItemType::FOOD, true);
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod06)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("item.csv");
            ItemInfo itemInfo = obj->GetItemInfo("çïÇ¢äL");
            Assert::AreEqual(itemInfo.GetWater(), 10.f);
            ItemManager::Destroy();
        }
    };
}
