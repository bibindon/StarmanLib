#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/WeaponManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using WeaponTypeMap = std::unordered_map<std::string, WeaponType>;
using WeaponMap = std::unordered_map<std::string, std::vector<Weapon>>;

namespace StarmanLibTest
{

    TEST_CLASS(StarmanLibTest)
    {
    public:
        TEST_METHOD(TestMethod01)
        {
            WeaponManager wm;
        }
        TEST_METHOD(TestMethod02)
        {
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                "..\\StarmanLibTest\\subWeaponSave.csv");
        }
        TEST_METHOD(TestMethod03)
        {
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                "..\\StarmanLibTest\\subWeaponSave.csv");
            WeaponTypeMap wmap = wm.GetWeaponTypeMap();
            Assert::AreEqual((int)wmap.size(), 10);
        }
        TEST_METHOD(TestMethod04)
        {
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                "..\\StarmanLibTest\\subWeaponSave.csv");
            WeaponTypeMap wmap = wm.GetWeaponTypeMap();
            Assert::AreEqual(wmap["1"].GetId().c_str(), "1");
            Assert::AreEqual(wmap["10"].GetId().c_str(), "10");
        }
        TEST_METHOD(TestMethod05)
        {
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                "..\\StarmanLibTest\\subWeaponSave.csv");
            WeaponTypeMap wmap = wm.GetWeaponTypeMap();
            Assert::AreEqual(wmap["1"].GetName().c_str(), "石");
            Assert::AreEqual(wmap["10"].GetName().c_str(), "アトラトルに使う槍");
            Assert::AreEqual(wmap["1"].GetDetail().c_str(), "\"投げたり、殴ったりする。シャレにならないくらい強い。\n\"");
            Assert::AreEqual(wmap["10"].GetDetail().c_str(), "\"槍の柄の部分が柔らかく「しなる」材質じゃないと、実は全然飛ばない。\n何回も使うとそのことに気が付く。\n\n＋１～＋５\n\"");
            Assert::AreEqual(wmap["1"].GetWeight(), 0.5);
            Assert::AreEqual(wmap["10"].GetWeight(), 0.6);
            Assert::AreEqual(wmap["1"].GetVolume(), 500);
            Assert::AreEqual(wmap["10"].GetVolume(), 2000);
            Assert::AreEqual(wmap["1"].GetOwnDamage(), 10);
            Assert::AreEqual(wmap["10"].GetOwnDamage(), 5);

            Assert::AreEqual(wmap["1"].GetIsShow(), true);
            Assert::AreEqual(wmap["10"].GetIsShow(), false);
        }
        TEST_METHOD(TestMethod06)
        {
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                "..\\StarmanLibTest\\subWeaponSave.csv");
            WeaponMap wmap = wm.GetWeaponMap();
            Assert::AreEqual((int)wmap["1"].size(), 4);
            Assert::AreEqual((int)wmap["10"].size(), 4);
        }
        TEST_METHOD(TestMethod07)
        {
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                "..\\StarmanLibTest\\subWeaponSave.csv");
            WeaponMap wmap = wm.GetWeaponMap();
            Assert::AreEqual(wmap["1"].at(0).GetId().c_str(), "1");
            Assert::AreEqual(wmap["1"].at(3).GetId().c_str(), "1");
            Assert::AreEqual(wmap["10"].at(0).GetId().c_str(), "10");
            Assert::AreEqual(wmap["10"].at(3).GetId().c_str(), "10");
        }
        TEST_METHOD(TestMethod08)
        {
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                "..\\StarmanLibTest\\subWeaponSave.csv");
            WeaponMap wmap = wm.GetWeaponMap();
            Assert::AreEqual(wmap["1"].at(0).GetIdSub(), 0);
            Assert::AreEqual(wmap["1"].at(3).GetIdSub(), 3);
            Assert::AreEqual(wmap["10"].at(0).GetIdSub(), 0);
            Assert::AreEqual(wmap["10"].at(3).GetIdSub(), 3);

            Assert::AreEqual(wmap["1"].at(0).GetReinforce(), 3);
            Assert::AreEqual(wmap["1"].at(3).GetReinforce(), 0);
            Assert::AreEqual(wmap["10"].at(0).GetReinforce(), 3);
            Assert::AreEqual(wmap["10"].at(3).GetReinforce(), 0);

            Assert::AreEqual(wmap["1"].at(0).GetAttackRate(), 0.1);
            Assert::AreEqual(wmap["1"].at(3).GetAttackRate(), 0.4);
            Assert::AreEqual(wmap["10"].at(0).GetAttackRate(), 3.7);
            Assert::AreEqual(wmap["10"].at(3).GetAttackRate(), 4.0);

            Assert::AreEqual(wmap["1"].at(0).GetFlightDistance(), 10);
            Assert::AreEqual(wmap["1"].at(3).GetFlightDistance(), 40);
            Assert::AreEqual(wmap["10"].at(0).GetFlightDistance(), 370);
            Assert::AreEqual(wmap["10"].at(3).GetFlightDistance(), 400);

            Assert::AreEqual(wmap["1"].at(0).GetDurabilityMax(), 999);
            Assert::AreEqual(wmap["1"].at(3).GetDurabilityMax(), 996);
            Assert::AreEqual(wmap["10"].at(0).GetDurabilityMax(), 963);
            Assert::AreEqual(wmap["10"].at(3).GetDurabilityMax(), 960);

            Assert::AreEqual(wmap["1"].at(0).GetDurability(), 500);
            Assert::AreEqual(wmap["1"].at(3).GetDurability(), 470);
            Assert::AreEqual(wmap["10"].at(0).GetDurability(), 140);
            Assert::AreEqual(wmap["10"].at(3).GetDurability(), 110);
        }
        TEST_METHOD(TestMethod09)
        {
            // アイテム情報編集
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                "..\\StarmanLibTest\\subWeaponSave.csv");
            WeaponTypeMap wtmap = wm.GetWeaponTypeMap();
            wtmap["1"].SetIsShow(false);
            wtmap["10"].SetIsShow(true);
            wm.SetWeaponTypeMap(wtmap);
            Assert::AreEqual(wm.GetWeaponTypeMap()["1"].GetIsShow(), false);
            Assert::AreEqual(wm.GetWeaponTypeMap()["10"].GetIsShow(), true);

            WeaponMap wmap = wm.GetWeaponMap();
            wmap["1"].at(0).SetDurability(wmap["1"].at(0).GetDurability() - 1);
            wmap["1"].at(3).SetDurability(wmap["1"].at(3).GetDurability() - 1);
            wmap["10"].at(0).SetDurability(wmap["10"].at(0).GetDurability() - 1);
            wmap["10"].at(3).SetDurability(wmap["10"].at(3).GetDurability() - 1);
            wm.SetWeaponMap(wmap);
            Assert::AreEqual(wm.GetWeaponMap()["1"].at(0).GetDurability(), 499);
            Assert::AreEqual(wm.GetWeaponMap()["1"].at(3).GetDurability(), 469);
            Assert::AreEqual(wm.GetWeaponMap()["10"].at(0).GetDurability(), 139);
            Assert::AreEqual(wm.GetWeaponMap()["10"].at(3).GetDurability(), 109);
        }
        TEST_METHOD(TestMethod10)
        {
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                "..\\StarmanLibTest\\subWeaponSave.csv");
            wm.Save("weaponSave2.csv", "subWeaponSave2.csv");
            std::ifstream ifs("weaponSave2.csv");
            std::istreambuf_iterator<char> itBegin(ifs);
            std::istreambuf_iterator<char> itEnd;
            std::string str;
            for (; itBegin != itEnd; itBegin++)
            {
                str += *itBegin;
            }
            Assert::AreEqual(str.c_str(), "ID,表示・非表示\n1,true\n2,false\n3,true\n4,false\n5,true\n6,false\n7,true\n8,false\n9,true\n10,false\n");
        }
        // 出力したセーブデータを再読み込み
        TEST_METHOD(TestMethod11)
        {
            {
                WeaponManager wm;
                wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                    "..\\StarmanLibTest\\subWeaponSave.csv");
                wm.Save("weaponSave2.csv", "subWeaponSave2.csv");
            }
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv", "weaponSave2.csv", "subWeaponSave2.csv");
            
            WeaponTypeMap wtmap = wm.GetWeaponTypeMap();
            Assert::AreEqual(wtmap["1"].GetIsShow(), true);
            Assert::AreEqual(wtmap["10"].GetIsShow(), false);

            WeaponMap wmap = wm.GetWeaponMap();
            Assert::AreEqual(wmap["1"].at(0).GetIdSub(), 0);
            Assert::AreEqual(wmap["1"].at(3).GetIdSub(), 3);
            Assert::AreEqual(wmap["10"].at(0).GetIdSub(), 0);
            Assert::AreEqual(wmap["10"].at(3).GetIdSub(), 3);

            Assert::AreEqual(wmap["1"].at(0).GetReinforce(), 3);
            Assert::AreEqual(wmap["1"].at(3).GetReinforce(), 0);
            Assert::AreEqual(wmap["10"].at(0).GetReinforce(), 3);
            Assert::AreEqual(wmap["10"].at(3).GetReinforce(), 0);

            Assert::AreEqual(wmap["1"].at(0).GetAttackRate(), 0.1);
            Assert::AreEqual(wmap["1"].at(3).GetAttackRate(), 0.4);
            Assert::AreEqual(wmap["10"].at(0).GetAttackRate(), 3.7);
            Assert::AreEqual(wmap["10"].at(3).GetAttackRate(), 4.0);

            Assert::AreEqual(wmap["1"].at(0).GetFlightDistance(), 10);
            Assert::AreEqual(wmap["1"].at(3).GetFlightDistance(), 40);
            Assert::AreEqual(wmap["10"].at(0).GetFlightDistance(), 370);
            Assert::AreEqual(wmap["10"].at(3).GetFlightDistance(), 400);

            Assert::AreEqual(wmap["1"].at(0).GetDurabilityMax(), 999);
            Assert::AreEqual(wmap["1"].at(3).GetDurabilityMax(), 996);
            Assert::AreEqual(wmap["10"].at(0).GetDurabilityMax(), 963);
            Assert::AreEqual(wmap["10"].at(3).GetDurabilityMax(), 960);

            Assert::AreEqual(wmap["1"].at(0).GetDurability(), 500);
            Assert::AreEqual(wmap["1"].at(3).GetDurability(), 470);
            Assert::AreEqual(wmap["10"].at(0).GetDurability(), 140);
            Assert::AreEqual(wmap["10"].at(3).GetDurability(), 110);
        }

        // 暗号化されたファイルの読み込みテスト
        TEST_METHOD(TestMethod12)
        {
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv.enc", "..\\StarmanLibTest\\weaponSave.csv.enc",
                "..\\StarmanLibTest\\subWeaponSave.csv.enc", true);

            WeaponTypeMap wmap = wm.GetWeaponTypeMap();
            Assert::AreEqual(wmap["1"].GetName().c_str(), "石");
            Assert::AreEqual(wmap["10"].GetName().c_str(), "アトラトルに使う槍");
            Assert::AreEqual(wmap["1"].GetDetail().c_str(), "\"投げたり、殴ったりする。シャレにならないくらい強い。\n\"");
            Assert::AreEqual(wmap["10"].GetDetail().c_str(), "\"槍の柄の部分が柔らかく「しなる」材質じゃないと、実は全然飛ばない。\n何回も使うとそのことに気が付く。\n\n＋１～＋５\n\"");
            Assert::AreEqual(wmap["1"].GetWeight(), 0.5);
            Assert::AreEqual(wmap["10"].GetWeight(), 0.6);
            Assert::AreEqual(wmap["1"].GetVolume(), 500);
            Assert::AreEqual(wmap["10"].GetVolume(), 2000);
            Assert::AreEqual(wmap["1"].GetOwnDamage(), 10);
            Assert::AreEqual(wmap["10"].GetOwnDamage(), 5);

            Assert::AreEqual(wmap["1"].GetIsShow(), true);
            Assert::AreEqual(wmap["10"].GetIsShow(), false);
        }
        // ファイルを暗号化して出力するテスト
        TEST_METHOD(TestMethod13)
        {
            WeaponManager wm;
            wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                "..\\StarmanLibTest\\subWeaponSave.csv");
            wm.Save("weaponSave2.csv.enc", "subWeaponSave2.csv.enc", true);
            {
                std::ifstream ifs1("weaponSave2.csv.enc");
                std::ifstream ifs2("..\\StarmanLibTest\\weaponSave.csv.enc");
                std::string file1 { std::istreambuf_iterator<char>(ifs1), std::istreambuf_iterator<char>() };
                std::string file2 { std::istreambuf_iterator<char>(ifs2), std::istreambuf_iterator<char>() };
                Assert::AreEqual(file1, file2);
            }
            {
                std::ifstream ifs1("subWeaponSave2.csv.enc");
                std::ifstream ifs2("..\\StarmanLibTest\\subWeaponSave.csv.enc");
                std::string file1 { std::istreambuf_iterator<char>(ifs1), std::istreambuf_iterator<char>() };
                std::string file2 { std::istreambuf_iterator<char>(ifs2), std::istreambuf_iterator<char>() };
                Assert::AreEqual(file1, file2);
            }
        }
        // 暗号化して出力したファイルを読み込むテスト
        TEST_METHOD(TestMethod14)
        {
            {
                WeaponManager wm;
                wm.Init("..\\StarmanLibTest\\weapon.csv", "..\\StarmanLibTest\\weaponSave.csv",
                    "..\\StarmanLibTest\\subWeaponSave.csv");
                wm.Save("weaponSave3.csv.enc", "subWeaponSave3.csv.enc", true);
            }
            {
                WeaponManager wm;
                wm.Init("..\\StarmanLibTest\\weapon.csv.enc",
                    "weaponSave3.csv.enc",
                    "subWeaponSave3.csv.enc", true);

                WeaponTypeMap wmap = wm.GetWeaponTypeMap();
                Assert::AreEqual(wmap["1"].GetName().c_str(), "石");
                Assert::AreEqual(wmap["10"].GetName().c_str(), "アトラトルに使う槍");
                Assert::AreEqual(wmap["1"].GetDetail().c_str(), "\"投げたり、殴ったりする。シャレにならないくらい強い。\n\"");
                Assert::AreEqual(wmap["10"].GetDetail().c_str(), "\"槍の柄の部分が柔らかく「しなる」材質じゃないと、実は全然飛ばない。\n何回も使うとそのことに気が付く。\n\n＋１～＋５\n\"");
                Assert::AreEqual(wmap["1"].GetWeight(), 0.5);
                Assert::AreEqual(wmap["10"].GetWeight(), 0.6);
                Assert::AreEqual(wmap["1"].GetVolume(), 500);
                Assert::AreEqual(wmap["10"].GetVolume(), 2000);
                Assert::AreEqual(wmap["1"].GetOwnDamage(), 10);
                Assert::AreEqual(wmap["10"].GetOwnDamage(), 5);

                Assert::AreEqual(wmap["1"].GetIsShow(), true);
                Assert::AreEqual(wmap["10"].GetIsShow(), false);
            }
        }
    };
}
