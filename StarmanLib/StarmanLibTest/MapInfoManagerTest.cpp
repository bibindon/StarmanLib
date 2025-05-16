#include "CppUnitTest.h"
#include "../StarmanLib/MapInfoManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <cassert>
#include <tchar.h>

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
            obj->Init(_T("..\\StarmanLibTest\\mapInfoOrigin.csv"));
            std::vector<std::wstring> vs = obj->GetNameList();
            Assert::AreEqual(vs.size() != 0, true);
        }

        TEST_METHOD(TestMethod03)
        {
            MapInfoManager* obj = MapInfoManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\mapInfoOrigin.csv"));
            std::vector<std::wstring> vs = obj->GetNameList();
            Assert::AreEqual(vs.at(0) == _T("パワーエッグ星"), true);
        }

        TEST_METHOD(TestMethod04)
        {
            MapInfoManager* obj = MapInfoManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\mapInfoOrigin.csv"));
            bool bDiscovered = obj->IsDiscovered(_T("プロリタン島"));
            Assert::AreEqual(bDiscovered, true);
        }

        TEST_METHOD(TestMethod05)
        {
            MapInfoManager* obj = MapInfoManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\mapInfoOrigin.csv"));
            std::wstring result = obj->GetImagePath(_T("プロリタン島"));
            Assert::AreEqual(_T("res\\\\image\\\\narrowmap2.png"), result.c_str());
        }

        // 保存したときの内容が正しいか確認
        TEST_METHOD(TestMethod06)
        {
            {
                MapInfoManager* obj = MapInfoManager::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\mapInfoOrigin.csv"));
                obj->SetDiscovered(_T("プレシジョン"));
                obj->Save(_T("..\\StarmanLibTest\\mapInfoSave.csv"));
                MapInfoManager::Destroy();
            }
            {
                MapInfoManager* obj = MapInfoManager::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\mapInfoSave.csv"));
                bool bDiscovered = obj->IsDiscovered(_T("プレシジョン"));
                Assert::AreEqual(bDiscovered, true);
            }
        }
    };
}
