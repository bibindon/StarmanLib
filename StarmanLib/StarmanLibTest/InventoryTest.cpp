#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/Inventory.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include "../StarmanLib/ItemManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
            Inventory* obj = Inventory::GetObj();
            obj->Init("inventory.csv");
            Inventory::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            ItemManager* itemManager = ItemManager::GetObj();
            itemManager->Init("item.csv");

            Inventory* obj = Inventory::GetObj();
            obj->Init("inventory.csv");
            float weight = obj->GetWeight();
            // float��7�������L���������Ȃ��B4���̐��l���m�̔�r�Ȃ�A�����_�ȉ���3���܂ł������m����Ȃ��B
            // �J��Ԃ��|���Z�Ƒ����Z���s���̂�7�����Ȃ��B�ۑ�
            Assert::AreEqual((1063.094f <= weight && weight <= 1063.096f), true);
            Inventory::Destroy();
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            ItemManager* itemManager = ItemManager::GetObj();
            itemManager->Init("item.csv");

            Inventory* obj = Inventory::GetObj();
            obj->Init("inventory.csv");
            Assert::AreEqual(obj->CountItem(1), 1);
            Assert::AreEqual(obj->CountItem(37), 2);
            obj->AddItem(1);
            obj->AddItem(37);
            Assert::AreEqual(obj->CountItem(1), 2);
            Assert::AreEqual(obj->CountItem(37), 3);
            obj->RemoveItem(1);
            obj->RemoveItem(37);
            Assert::AreEqual(obj->CountItem(1), 1);
            Assert::AreEqual(obj->CountItem(37), 2);
            Inventory::Destroy();
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init("item.csv");

                Inventory* obj = Inventory::GetObj();
                obj->Init("inventory.csv");
                obj->AddItem(1);
                obj->AddItem(37);
                Assert::AreEqual(obj->CountItem(1), 2);
                Assert::AreEqual(obj->CountItem(37), 3);
                obj->Save("inventorySave.csv");
                Inventory::Destroy();
                ItemManager::Destroy();
            }
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init("item.csv");

                Inventory* obj = Inventory::GetObj();
                obj->Init("inventorySave.csv");
                Assert::AreEqual(obj->CountItem(1), 2);
                Assert::AreEqual(obj->CountItem(37), 3);
                Inventory::Destroy();
                ItemManager::Destroy();
            }
        }
    };
}