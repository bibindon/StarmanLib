#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/StatusManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StarmanLibTest
{

    TEST_CLASS(StatusManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            StatusManager* obj = StatusManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init("statusOrigin.csv");
            Assert::AreEqual(obj != nullptr, true);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init("statusOrigin.csv");
            float value = obj->GetBodyStaminaCurrent();
            Assert::AreEqual(value, 10.f);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init("statusOrigin.csv");
            float value = obj->GetWaterMax();
            Assert::AreEqual(value, 100.f);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init("statusOrigin.csv");
            obj->SetBodyStaminaCurrent(123.f);
            float value = obj->GetBodyStaminaCurrent();
            Assert::AreEqual(value, 123.f);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod06)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init("statusOrigin.csv");
            bool value = obj->GetFractureArm();
            Assert::AreEqual(value, false);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod07)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init("statusOrigin.csv");
            bool value = obj->GetLackOfSleep();
            Assert::AreEqual(value, false);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod08)
        {
            StatusManager* obj = StatusManager::GetObj();
            obj->Init("statusOrigin.csv");
            obj->SetFractureArm(true);
            bool value = obj->GetFractureArm();
            Assert::AreEqual(value, true);
            StatusManager::Destroy();
        }

        TEST_METHOD(TestMethod09)
        {
            {
                StatusManager* obj = StatusManager::GetObj();
                obj->Init("statusOrigin.csv");
                obj->SetBodyStaminaCurrent(123.f);
                obj->SetFractureArm(true);
                obj->Save("statusSave.csv");
                StatusManager::Destroy();
            }
            {
                StatusManager* obj = StatusManager::GetObj();
                obj->Init("statusSave.csv");
                float value1 = obj->GetBodyStaminaCurrent();
                Assert::AreEqual(value1, 123.f);

                bool value2 = obj->GetFractureArm();
                Assert::AreEqual(value2, true);
            }
            StatusManager::Destroy();
        }
    };
}