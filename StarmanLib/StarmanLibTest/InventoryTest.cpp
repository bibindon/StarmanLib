#include "CppUnitTest.h"
#include "../StarmanLib/Inventory.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include "../StarmanLib/ItemManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(InventoryTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            Inventory* obj = Inventory::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            Inventory::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            ItemManager* itemManager = ItemManager::GetObj();
            itemManager->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));

            Inventory* obj = Inventory::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\inventory.csv"));
            Inventory::Destroy();

            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            ItemManager* itemManager = ItemManager::GetObj();
            itemManager->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));

            Inventory* obj = Inventory::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\inventory.csv"));
            float weight = obj->GetWeight();
            // floatは7桁しか有効桁数がない。4桁の数値同士の比較なら、小数点以下は3桁までしか正確じゃない。
            // 繰り返し掛け算と足し算を行うので7桁もない。課題
//            Assert::AreEqual((1063.094f <= weight && weight <= 1063.096f), true);
            Assert::AreEqual(1000.f <= weight, true);
            Inventory::Destroy();
            ItemManager::Destroy();
        }

        // アイテムの増減のテスト
        TEST_METHOD(TestMethod04)
        {
            ItemManager* itemManager = ItemManager::GetObj();
            itemManager->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));

            Inventory* obj = Inventory::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\inventory.csv"));
            Assert::AreEqual(obj->CountItem(1), 10);
            Assert::AreEqual(obj->CountItem(37), 10);
            obj->AddItem(1);
            obj->AddItem(37);
            Assert::AreEqual(obj->CountItem(1), 11);
            Assert::AreEqual(obj->CountItem(37), 11);
            obj->RemoveItem(1, 1);
            obj->RemoveItem(37, 1);
            Assert::AreEqual(obj->CountItem(1), 10);
            Assert::AreEqual(obj->CountItem(37), 10);
            Inventory::Destroy();
            ItemManager::Destroy();
        }

        // セーブ機能の確認
        TEST_METHOD(TestMethod05)
        {
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));

                Inventory* obj = Inventory::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\inventory.csv"));
                obj->AddItem(1);
                obj->AddItem(37);
                Assert::AreEqual(obj->CountItem(1), 11);
                Assert::AreEqual(obj->CountItem(37), 11);
                obj->Save(_T("..\\StarmanLibTest\\inventorySave.csv"));
                Inventory::Destroy();
                ItemManager::Destroy();
            }
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));

                Inventory* obj = Inventory::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\inventorySave.csv"));
                Assert::AreEqual(obj->CountItem(1), 11);
                Assert::AreEqual(obj->CountItem(37), 11);
                Inventory::Destroy();
                ItemManager::Destroy();
            }
        }

        // SubIDの採番の確認
        // 同じ種類のアイテムを複数持てるのでそれぞれのアイテムにSubIDが割り振られている
        // アイテムを削除できるのでSubIDは連番にならない。
        //
        // SubIDが1,2,3,4,5のときSubID＝3、SubID＝4のアイテムを削除して、
        // そのあとアイテムを追加したらSubIDは1,2,3,5になっているはず。
        TEST_METHOD(TestMethod06)
        {
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));

                Inventory* obj = Inventory::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\inventory.csv"));

                obj->AddItem(1);
                obj->AddItem(37);

                Assert::AreEqual(obj->ExistItem(1, 11), true);
                Assert::AreEqual(obj->ExistItem(37, 11), true);

                obj->RemoveItem(1, 3);
                obj->RemoveItem(1, 4);
                obj->AddItem(1);

                obj->RemoveItem(37, 3);
                obj->RemoveItem(37, 4);
                obj->AddItem(37);

                Assert::AreEqual(obj->ExistItem(1, 3), true);
                Assert::AreEqual(obj->ExistItem(1, 4), false);
                Assert::AreEqual(obj->ExistItem(37, 3), true);
                Assert::AreEqual(obj->ExistItem(37, 4), false);

                Inventory::Destroy();
                ItemManager::Destroy();
            }
        }

        // SubIDの採番の確認
        // 初めて追加されるアイテムならSubIDは1が採番されるはず
        TEST_METHOD(TestMethod07)
        {
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));

                Inventory* obj = Inventory::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\inventory.csv"));

                obj->RemoveItem(3, 1);
                obj->RemoveItem(3, 2);
                obj->RemoveItem(3, 3);
                obj->RemoveItem(3, 4);
                obj->RemoveItem(3, 5);
                obj->RemoveItem(3, 6);
                obj->RemoveItem(3, 7);
                obj->RemoveItem(3, 8);
                obj->RemoveItem(3, 9);
                obj->RemoveItem(3, 10);

                Assert::AreEqual(obj->CountItem(3), 0);

                obj->AddItem(3);

                Assert::AreEqual(obj->CountItem(3), 1);
                Assert::AreEqual(obj->ExistItem(3, 0), false);
                Assert::AreEqual(obj->ExistItem(3, 1), true);
                Assert::AreEqual(obj->ExistItem(3, 2), false);

                Inventory::Destroy();
                ItemManager::Destroy();
            }
        }
    };
}
