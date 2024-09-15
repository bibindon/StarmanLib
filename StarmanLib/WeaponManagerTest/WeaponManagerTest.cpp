#include "pch.h"
#include "CppUnitTest.h"
#include "../WeaponManager/WeaponManager.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WeaponManagerTest
{
    TEST_CLASS(WeaponManagerTest)
    {
    public:
        
        TEST_METHOD(TestMethod1)
        {
            WeaponManager wm;
        }
        TEST_METHOD(TestMethod2)
        {
            WeaponManager wm;
            wm.Init("..\\WeaponManagerTest\\weapon.csv", "..\\WeaponManagerTest\\weaponSave.csv");
        }
        TEST_METHOD(TestMethod3)
        {
            WeaponManager wm;
            wm.Init("..\\WeaponManagerTest\\weapon.csv", "..\\WeaponManagerTest\\weaponSave.csv");
            wm.Save("weaponSave2.csv");
        }
        TEST_METHOD(TestMethod4)
        {
            WeaponManager wm;
            wm.Init("..\\WeaponManagerTest\\weapon.csv", "..\\WeaponManagerTest\\weaponSave.csv");

            Assert::AreEqual((int)wm.GetWeaponList().size(), 10);
            Assert::AreEqual((int)wm.GetWeaponList().at(0).GetNum(), 10);
        }
        TEST_METHOD(TestMethod5)
        {
            WeaponManager wm;
            wm.Init("..\\WeaponManagerTest\\weapon.csv", "..\\WeaponManagerTest\\weaponSave.csv");
            wm.Save("weaponSave2.csv");
            std::ifstream ifs("weaponSave2.csv");
            std::istreambuf_iterator<char> itBegin(ifs);
            std::istreambuf_iterator<char> itEnd;
            std::string str;
            for (; itBegin != itEnd; itBegin++)
            {
                str += *itBegin;
            }
            Assert::AreEqual(str.c_str(), "1,0,false\n2,0,false\n3,0,false\n4,0,false\n5,0,false\n6,0,false\n7,0,false\n8,0,false\n9,0,false\n10,0,false\n");
        }
    };
}
