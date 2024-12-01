#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/MapInfoManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <cassert>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

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
            obj->Init("..\\StarmanLibTest\\mapInfoOrigin.csv");
            std::vector<std::string> vs = obj->GetNameList();
            Assert::AreEqual(vs.size() != 0, true);
        }

        TEST_METHOD(TestMethod03)
        {
            MapInfoManager* obj = MapInfoManager::GetObj();
            obj->Init("..\\StarmanLibTest\\mapInfoOrigin.csv");
            std::vector<std::string> vs = obj->GetNameList();
            Assert::AreEqual(vs.at(0) == "パワーエッグ星", true);
        }

        TEST_METHOD(TestMethod04)
        {
            MapInfoManager* obj = MapInfoManager::GetObj();
            obj->Init("..\\StarmanLibTest\\mapInfoOrigin.csv");
            bool bDiscovered = obj->IsDiscovered("プロリタン島");
            Assert::AreEqual(bDiscovered, true);
        }

        TEST_METHOD(TestMethod05)
        {
            MapInfoManager* obj = MapInfoManager::GetObj();
            obj->Init("..\\StarmanLibTest\\mapInfoOrigin.csv");
            std::string result = obj->GetImagePath("プロリタン島");
            Assert::AreEqual("res\\\\image\\\\narrowmap2.png", result.c_str());
        }

        // 保存したときの内容が正しいか確認
        TEST_METHOD(TestMethod06)
        {
            {
                MapInfoManager* obj = MapInfoManager::GetObj();
                obj->Init("..\\StarmanLibTest\\mapInfoOrigin.csv");
                obj->SetDiscovered("プレシジョン");
                obj->Save("..\\StarmanLibTest\\mapInfoSave.csv");
                MapInfoManager::Destroy();
            }
            {
                MapInfoManager* obj = MapInfoManager::GetObj();
                obj->Init("..\\StarmanLibTest\\mapInfoSave.csv");
                bool bDiscovered = obj->IsDiscovered("プレシジョン");
                Assert::AreEqual(bDiscovered, true);
            }
        }
    };
}
