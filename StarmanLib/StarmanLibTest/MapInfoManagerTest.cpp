#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/MapInfoManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StarmanLibTest
{

    TEST_CLASS(MapInfoManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            MapInfoManager* obj = MapInfoManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
        }

        TEST_METHOD(TestMethod02)
        {
            MapInfoManager* obj = MapInfoManager::GetObj();
            obj->Init("mapInfoOrigin.csv");
            std::vector<std::string> vs = obj->GetNameList();
            Assert::AreEqual(vs.size() != 0, true);
        }

        TEST_METHOD(TestMethod03)
        {
            MapInfoManager* obj = MapInfoManager::GetObj();
            obj->Init("mapInfoOrigin.csv");
            std::vector<std::string> vs = obj->GetNameList();
            Assert::AreEqual(vs.at(0) == "�p���[�G�b�O��", true);
        }

        TEST_METHOD(TestMethod04)
        {
            MapInfoManager* obj = MapInfoManager::GetObj();
            obj->Init("mapInfoOrigin.csv");
            bool bDiscovered = obj->IsDiscovered("�v�����^����");
            Assert::AreEqual(bDiscovered, true);
        }

        // �ۑ������Ƃ��̓��e�����������m�F
        TEST_METHOD(TestMethod05)
        {
            {
                MapInfoManager* obj = MapInfoManager::GetObj();
                obj->Init("mapInfoOrigin.csv");
                obj->SetDiscovered("�v���V�W����");
                obj->Save("mapInfoSave.csv");
                MapInfoManager::Destroy();
            }
            {
                MapInfoManager* obj = MapInfoManager::GetObj();
                obj->Init("mapInfoSave.csv");
                bool bDiscovered = obj->IsDiscovered("�v���V�W����");
                Assert::AreEqual(bDiscovered, true);
            }
        }
    };
}