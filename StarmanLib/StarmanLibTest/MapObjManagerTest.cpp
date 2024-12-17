#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/MapObjManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(MapObjManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            MapObjManager* obj = MapObjManager::GetObj();
            Assert::AreEqual(true, obj != nullptr);
            MapObjManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            MapObjManager* obj = MapObjManager::GetObj();
            obj->Init("..\\StarmanLibTest\\map_obj.csv");
            std::vector<MapObj> vs = obj->GetMapObjList(-290, 550);
            Assert::AreEqual(true, vs.size() != 0);
            MapObjManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            MapObjManager* obj = MapObjManager::GetObj();
            obj->Init("..\\StarmanLibTest\\map_obj.csv");
            std::vector<MapObj> vs = obj->GetMapObjList(-150, 550);
            Assert::AreEqual(3, (int)vs.size());
            MapObjManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            MapObjManager* obj = MapObjManager::GetObj();
            obj->Init("..\\StarmanLibTest\\map_obj.csv");
            std::vector<MapObj> vs = obj->GetMapObjList(-150, 550);
            Assert::AreEqual(3, (int)vs.size());

            vs = obj->GetMapObjList(-150, 550);
            Assert::AreEqual(3, (int)vs.size());
            MapObjManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            MapObjManager* obj = MapObjManager::GetObj();
            obj->Init("..\\StarmanLibTest\\map_obj.csv");
            std::vector<MapObj> vs = obj->GetMapObjList(-150, 550);
            obj->SetShow(-2, 5, 1, true);

             vs = obj->GetMapObjList(-150, 550);
            Assert::AreEqual(3, (int)vs.size());
            MapObjManager::Destroy();
        }

        TEST_METHOD(TestMethod06)
        {
            MapObjManager* obj = MapObjManager::GetObj();
            obj->Init("..\\StarmanLibTest\\map_obj.csv");
            std::vector<MapObj> vs;
            obj->GetMapObjListShow(-150, 550, &vs);
            Assert::AreEqual(3, (int)vs.size());

            obj->SetShow(-2, 5, 1, true);

            obj->GetMapObjListShow(-150, 550, &vs);
            Assert::AreEqual(2, (int)vs.size());
            MapObjManager::Destroy();
        }

        TEST_METHOD(TestMethod07)
        {
            MapObjManager* obj = MapObjManager::GetObj();
            obj->Init("..\\StarmanLibTest\\map_obj.csv");
            std::vector<MapObj> vs;
            obj->GetMapObjListHide(-150, 550, &vs);
            Assert::AreEqual(0, (int)vs.size());

            obj->SetShow(-2, 5, 1, true);

            obj->GetMapObjListHide(0, 550, &vs);
            Assert::AreEqual(1, (int)vs.size());
            MapObjManager::Destroy();
        }
    };
}
