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
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            ItemDef itemDef = obj->GetItemDef("スマホ");
            Assert::AreEqual(itemDef.GetImagePath() == "sumaho.png", true);
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            ItemDef itemDef = obj->GetItemDef("黒い貝");
            Assert::AreEqual(itemDef.GetImagePath() == "mussels.png", true);
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            ItemDef itemDef = obj->GetItemDef("黒い貝");
            Assert::AreEqual(itemDef.GetType() == ItemDef::ItemType::FOOD, true);
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod06)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            ItemDef itemDef = obj->GetItemDef("黒い貝");
            Assert::AreEqual(itemDef.GetWater(), 10.f);
            ItemManager::Destroy();
        }
    };
}
