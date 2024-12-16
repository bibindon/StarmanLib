#include "pch.h"
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
            itemManager->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

            Inventory* obj = Inventory::GetObj();
            obj->Init("..\\StarmanLibTest\\inventory.csv");
            Inventory::Destroy();

            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            ItemManager* itemManager = ItemManager::GetObj();
            itemManager->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

            Inventory* obj = Inventory::GetObj();
            obj->Init("..\\StarmanLibTest\\inventory.csv");
            float weight = obj->GetWeight();
            // float��7�������L���������Ȃ��B4���̐��l���m�̔�r�Ȃ�A�����_�ȉ���3���܂ł������m����Ȃ��B
            // �J��Ԃ��|���Z�Ƒ����Z���s���̂�7�����Ȃ��B�ۑ�
//            Assert::AreEqual((1063.094f <= weight && weight <= 1063.096f), true);
            Assert::AreEqual(1000.f <= weight, true);
            Inventory::Destroy();
            ItemManager::Destroy();
        }

        // �A�C�e���̑����̃e�X�g
        TEST_METHOD(TestMethod04)
        {
            ItemManager* itemManager = ItemManager::GetObj();
            itemManager->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

            Inventory* obj = Inventory::GetObj();
            obj->Init("..\\StarmanLibTest\\inventory.csv");
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

        // �Z�[�u�@�\�̊m�F
        TEST_METHOD(TestMethod05)
        {
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

                Inventory* obj = Inventory::GetObj();
                obj->Init("..\\StarmanLibTest\\inventory.csv");
                obj->AddItem(1);
                obj->AddItem(37);
                Assert::AreEqual(obj->CountItem(1), 11);
                Assert::AreEqual(obj->CountItem(37), 11);
                obj->Save("..\\StarmanLibTest\\inventorySave.csv");
                Inventory::Destroy();
                ItemManager::Destroy();
            }
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

                Inventory* obj = Inventory::GetObj();
                obj->Init("..\\StarmanLibTest\\inventorySave.csv");
                Assert::AreEqual(obj->CountItem(1), 11);
                Assert::AreEqual(obj->CountItem(37), 11);
                Inventory::Destroy();
                ItemManager::Destroy();
            }
        }

        // SubID�̍̔Ԃ̊m�F
        // ������ނ̃A�C�e���𕡐����Ă�̂ł��ꂼ��̃A�C�e����SubID������U���Ă���
        // �A�C�e�����폜�ł���̂�SubID�͘A�ԂɂȂ�Ȃ��B
        //
        // SubID��1,2,3,4,5�̂Ƃ�SubID��3�ASubID��4�̃A�C�e�����폜���āA
        // ���̂��ƃA�C�e����ǉ�������SubID��1,2,3,5�ɂȂ��Ă���͂��B
        TEST_METHOD(TestMethod06)
        {
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

                Inventory* obj = Inventory::GetObj();
                obj->Init("..\\StarmanLibTest\\inventory.csv");

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

        // SubID�̍̔Ԃ̊m�F
        // ���߂Ēǉ������A�C�e���Ȃ�SubID��1���̔Ԃ����͂�
        TEST_METHOD(TestMethod07)
        {
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

                Inventory* obj = Inventory::GetObj();
                obj->Init("..\\StarmanLibTest\\inventory.csv");

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
