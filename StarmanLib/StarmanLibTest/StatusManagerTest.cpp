﻿#include "CppUnitTest.h"
#include "../StarmanLib/StatusManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include "../StarmanLib/Inventory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(StatusManagerTest)
    {
    public:

        TEST_METHOD_INITIALIZE(Initialize)
        {
            ItemManager* itemManager = ItemManager::GetObj();
            itemManager->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));

            Inventory* inventory = Inventory::GetObj();
            inventory->Init(_T("..\\StarmanLibTest\\inventory.csv"));
        }

        TEST_METHOD_CLEANUP(CleanUp)
        {
            Inventory::Destroy();
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod01)
        {
            StatusManager* obj = StatusManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\statusOrigin.csv"));
            Assert::AreEqual(obj != nullptr, true);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\statusOrigin.csv"));
            float value = obj->GetBodyStaminaCurrent();
            Assert::AreEqual(value, 10.f);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\statusOrigin.csv"));
            float value = obj->GetWaterMax();
            Assert::AreEqual(value, 100.f);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\statusOrigin.csv"));
            obj->SetBodyStaminaCurrent(123.f);
            float value = obj->GetBodyStaminaCurrent();
            Assert::AreEqual(value, 123.f);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod06)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\statusOrigin.csv"));
            bool value = obj->GetFractureArm();
            Assert::AreEqual(value, false);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod07)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\statusOrigin.csv"));
            bool value = obj->GetLackOfSleep();
            Assert::AreEqual(value, false);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod08)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\statusOrigin.csv"));
            obj->SetFractureArm(true);
            bool value = obj->GetFractureArm();
            Assert::AreEqual(value, true);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod09)
        {
            {
                StatusManager* obj = StatusManager::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\statusOrigin.csv"));
                obj->SetBodyStaminaCurrent(123.f);
                obj->SetFractureArm(true);
                obj->Save(_T("..\\StarmanLibTest\\statusSave.csv"), 1, 2, 3);
                StatusManager::Destroy();
            }
            {
                StatusManager* obj = StatusManager::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\statusSave.csv"));
                float value1 = obj->GetBodyStaminaCurrent();
                Assert::AreEqual(value1, 123.f);

                bool value2 = obj->GetFractureArm();
                Assert::AreEqual(value2, true);
            }
            StatusManager::Destroy();
        }

        // テストしたいこと
        // 武器を装備していない状態で落ちないこと
        TEST_METHOD(TestMethod10)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\statusTest10.csv"));
            float work = obj->GetAttackPower();
            obj->ConsumeAttackCost();
        }
    };
}

