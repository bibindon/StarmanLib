#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/WeaponManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include "../StarmanLib/ItemManager.h"
#include "../StarmanLib/Inventory.h"
#include "../StarmanLib/Storehouse.h"
#include "../StarmanLib/CraftInfoManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(WeaponManagerTest)
    {
    public:

        TEST_METHOD_INITIALIZE(Initialize)
        {
            ItemManager* itemManager = ItemManager::GetObj();
            itemManager->Init("..\\StarmanLibTest\\item.csv");

            Inventory* inventory = Inventory::GetObj();
            inventory->Init("..\\StarmanLibTest\\inventory.csv");

            Storehouse* storehouse = Storehouse::GetObj();
            storehouse->Init("..\\StarmanLibTest\\storehouse.csv");

            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");
        }

        TEST_METHOD_CLEANUP(CleanUp)
        {
            CraftInfoManager::Destroy();
            Storehouse::Destroy();
            Inventory::Destroy();
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod01)
        {
            WeaponManager* wm = WeaponManager::GetObj();
        }

        TEST_METHOD(TestMethod02)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init("..\\StarmanLibTest\\weapon.csv",
                     "..\\StarmanLibTest\\weaponSave.csv");
        }

        // Init関数による読み込みテスト
        TEST_METHOD(TestMethod03)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init("..\\StarmanLibTest\\weapon.csv",
                     "..\\StarmanLibTest\\weaponSave.csv");
            WeaponDef weaponDef = wm->GetWeaponDef("石");
            std::string weaponId = weaponDef.GetWeaponId();
            Assert::AreEqual(weaponId == "w1", true);
        }

        // Init関数による読み込みテスト
        TEST_METHOD(TestMethod04)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init("..\\StarmanLibTest\\weapon.csv",
                     "..\\StarmanLibTest\\weaponSave.csv");
            {
                WeaponDef weaponDef = wm->GetWeaponDef("石");
                std::string weaponId = weaponDef.GetWeaponId();
                Assert::AreEqual(weaponId == "w1", true);
            }
            {
                WeaponDef weaponDef = wm->GetWeaponDef("アトラトルに使う槍");
                std::string weaponId = weaponDef.GetWeaponId();
                Assert::AreEqual(weaponId == "w10", true);
            }
        }

        TEST_METHOD(TestMethod05)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init("..\\StarmanLibTest\\weapon.csv",
                     "..\\StarmanLibTest\\weaponSave.csv");

            {
                WeaponDef weaponDef = wm->GetWeaponDef("石");
                Assert::AreEqual(weaponDef.GetWeaponId() == "w1", true);
                Assert::AreEqual(weaponDef.GetName() == "石", true);
                Assert::AreEqual(weaponDef.GetDetail() == "\"投げたり、殴ったりする。シャレにならないくらい強い。\n\"", true);
                Assert::AreEqual(weaponDef.GetXfileName() == "stone.x", true);
                Assert::AreEqual(weaponDef.GetImageName() == "stone.png", true);
                Assert::AreEqual(weaponDef.GetWeight() == 0.5f, true);
                Assert::AreEqual(weaponDef.GetVolume() == 500, true);
                Assert::AreEqual(weaponDef.GetOwnDamage() == 10, true);
            }
        }

        // SubIDが正しいか確認
        // 同じアイテムを複数持てるし、こちらの斧は耐久度が５０、こちらの斧は耐久度が１００とかできるので
        // SubIdという考えがある。
        // インベントリと倉庫があるがSubIdは被らないようになっている。
        TEST_METHOD(TestMethod06)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init("..\\StarmanLibTest\\weapon.csv",
                     "..\\StarmanLibTest\\weaponSave.csv");

            ItemManager* itemManager = ItemManager::GetObj();
            Inventory* inventory = Inventory::GetObj();
            Storehouse* storehouse = Storehouse::GetObj();

            ItemDef itemDef = itemManager->GetItemDef("石");
            WeaponDef weaponDef = wm->GetWeaponDef("石");

            std::vector<int> subIdList = inventory->GetSubIdList(itemDef.GetId());
            for (std::size_t i = 0; i < subIdList.size(); ++i)
            {
                bool result = false;
                // TODO 強化値はどうなる？
                result = wm->ExistWeapon(weaponDef.GetWeaponId(), subIdList.at(i));
                Assert::AreEqual(result, true);
            }

            std::vector<int> subIdList2 = storehouse->GetSubIdList(itemDef.GetId());
            for (std::size_t i = 0; i < subIdList2.size(); ++i)
            {
                bool result = false;
                // TODO 強化値はどうなる？
                result = wm->ExistWeapon(weaponDef.GetWeaponId(), subIdList2.at(i));
                Assert::AreEqual(result, true);
            }
        }

//        TEST_METHOD(TestMethod07)
//        {
//            WeaponManager* wm = WeaponManager::GetObj();
//            wm->Init("..\\StarmanLibTest\\weapon.csv",
//                     "..\\StarmanLibTest\\weaponSave.csv");
//            WeaponMap wmap = wm->GetWeaponMap();
//            Assert::AreEqual(wmap["1"].at(0).GetWeaponId().c_str(), "1");
//            Assert::AreEqual(wmap["1"].at(3).GetWeaponId().c_str(), "1");
//            Assert::AreEqual(wmap["10"].at(0).GetWeaponId().c_str(), "10");
//            Assert::AreEqual(wmap["10"].at(3).GetWeaponId().c_str(), "10");
//        }
//        TEST_METHOD(TestMethod08)
//        {
//            WeaponManager* wm = WeaponManager::GetObj();
//            wm->Init("..\\StarmanLibTest\\weapon.csv",
//                     "..\\StarmanLibTest\\weaponSave.csv");
//            WeaponMap wmap = wm->GetWeaponMap();
//            Assert::AreEqual(wmap["1"].at(0).GetIdSub(), 1);
//            Assert::AreEqual(wmap["1"].at(3).GetIdSub(), 4);
//            Assert::AreEqual(wmap["10"].at(0).GetIdSub(), 1);
//            Assert::AreEqual(wmap["10"].at(3).GetIdSub(), 4);
//
//            Assert::AreEqual(wmap["1"].at(0).GetReinforce(), 3);
//            Assert::AreEqual(wmap["1"].at(3).GetReinforce(), -1);
//            Assert::AreEqual(wmap["10"].at(0).GetReinforce(), 3);
//            Assert::AreEqual(wmap["10"].at(3).GetReinforce(), -1);
//
//            Assert::AreEqual(wmap["1"].at(0).GetAttackRate(), 0.1);
//            Assert::AreEqual(wmap["1"].at(3).GetAttackRate(), 0.4);
//            Assert::AreEqual(wmap["10"].at(0).GetAttackRate(), 3.7);
//            Assert::AreEqual(wmap["10"].at(3).GetAttackRate(), 4.0);
//
//            Assert::AreEqual(wmap["1"].at(0).GetFlightDistance(), 10);
//            Assert::AreEqual(wmap["1"].at(3).GetFlightDistance(), 40);
//            Assert::AreEqual(wmap["10"].at(0).GetFlightDistance(), 370);
//            Assert::AreEqual(wmap["10"].at(3).GetFlightDistance(), 400);
//
//            Assert::AreEqual(wmap["1"].at(0).GetDurabilityMax(), -1);
//            Assert::AreEqual(wmap["1"].at(3).GetDurabilityMax(), -1);
//            Assert::AreEqual(wmap["10"].at(0).GetDurabilityMax(), -1);
//            Assert::AreEqual(wmap["10"].at(3).GetDurabilityMax(), -1);
//
//            Assert::AreEqual(wmap["1"].at(0).GetDurability(), 500);
//            Assert::AreEqual(wmap["1"].at(3).GetDurability(), 470);
//            Assert::AreEqual(wmap["10"].at(0).GetDurability(), 140);
//            Assert::AreEqual(wmap["10"].at(3).GetDurability(), 110);
//        }
//        TEST_METHOD(TestMethod09)
//        {
//            // アイテム情報編集
//            WeaponManager* wm = WeaponManager::GetObj();
//            wm->Init("..\\StarmanLibTest\\weapon.csv",
//                     "..\\StarmanLibTest\\weaponSave.csv");
//            WeaponTypeMap wtmap = wm->GetWeaponTypeMap();
//            wtmap["1"].SetIsShow(false);
//            wtmap["10"].SetIsShow(true);
//            wm->SetWeaponTypeMap(wtmap);
//            Assert::AreEqual(wm->GetWeaponTypeMap()["1"].GetIsShow(), false);
//            Assert::AreEqual(wm->GetWeaponTypeMap()["10"].GetIsShow(), true);
//
//            WeaponMap wmap = wm->GetWeaponMap();
//            wmap["1"].at(0).SetDurability(wmap["1"].at(0).GetDurability() - 1);
//            wmap["1"].at(3).SetDurability(wmap["1"].at(3).GetDurability() - 1);
//            wmap["10"].at(0).SetDurability(wmap["10"].at(0).GetDurability() - 1);
//            wmap["10"].at(3).SetDurability(wmap["10"].at(3).GetDurability() - 1);
//            wm->SetWeaponMap(wmap);
//            Assert::AreEqual(wm->GetWeaponMap()["1"].at(0).GetDurability(), 499);
//            Assert::AreEqual(wm->GetWeaponMap()["1"].at(3).GetDurability(), 469);
//            Assert::AreEqual(wm->GetWeaponMap()["10"].at(0).GetDurability(), 139);
//            Assert::AreEqual(wm->GetWeaponMap()["10"].at(3).GetDurability(), 109);
//        }
//        TEST_METHOD(TestMethod10)
//        {
//            WeaponManager* wm = WeaponManager::GetObj();
//            wm->Init("..\\StarmanLibTest\\weapon.csv",
//                     "..\\StarmanLibTest\\weaponSave.csv");
//
//            wm->Save("..\\StarmanLibTest\\weaponSave2.csv");
//
//            std::ifstream ifs("..\\StarmanLibTest\\weaponSave2.csv");
//            std::istreambuf_iterator<char> itBegin(ifs);
//            std::istreambuf_iterator<char> itEnd;
//            std::string str;
//            for (; itBegin != itEnd; itBegin++)
//            {
//                str += *itBegin;
//            }
//            Assert::AreEqual(str.c_str(), "ID,表示・非表示\n1,true\n2,false\n3,true\n4,false\n5,true\n6,false\n7,true\n8,false\n9,true\n10,false\n");
//        }
//        // 出力したセーブデータを再読み込み
//        TEST_METHOD(TestMethod11)
//        {
//            {
//                WeaponManager* wm = WeaponManager::GetObj();
//                wm->Init("..\\StarmanLibTest\\weapon.csv",
//                         "..\\StarmanLibTest\\weaponSave.csv");
//
//                wm->Save("..\\StarmanLibTest\\weaponSave2.csv");
//                WeaponManager::Destroy();
//            }
//            WeaponManager* wm = WeaponManager::GetObj();
//            wm->Init("..\\StarmanLibTest\\weapon.csv",
//                     "..\\StarmanLibTest\\weaponSave2.csv");
//            
//            WeaponTypeMap wtmap = wm->GetWeaponTypeMap();
//            Assert::AreEqual(wtmap["w1"].GetIsShow(), true);
//            Assert::AreEqual(wtmap["w10"].GetIsShow(), false);
//
//            WeaponMap wmap = wm->GetWeaponMap();
//            Assert::AreEqual(wmap["1"].at(0).GetIdSub(), 1);
//            Assert::AreEqual(wmap["1"].at(3).GetIdSub(), 4);
//            Assert::AreEqual(wmap["10"].at(0).GetIdSub(), 1);
//            Assert::AreEqual(wmap["10"].at(3).GetIdSub(), 4);
//
//            Assert::AreEqual(wmap["1"].at(0).GetReinforce(), 3);
//            Assert::AreEqual(wmap["1"].at(3).GetReinforce(), -1);
//            Assert::AreEqual(wmap["10"].at(0).GetReinforce(), 3);
//            Assert::AreEqual(wmap["10"].at(3).GetReinforce(), -1);
//
//            Assert::AreEqual(wmap["1"].at(0).GetAttackRate(), 0.1);
//            Assert::AreEqual(wmap["1"].at(3).GetAttackRate(), 0.4);
//            Assert::AreEqual(wmap["10"].at(0).GetAttackRate(), 3.7);
//            Assert::AreEqual(wmap["10"].at(3).GetAttackRate(), 4.0);
//
//            Assert::AreEqual(wmap["1"].at(0).GetFlightDistance(), 10);
//            Assert::AreEqual(wmap["1"].at(3).GetFlightDistance(), 40);
//            Assert::AreEqual(wmap["10"].at(0).GetFlightDistance(), 370);
//            Assert::AreEqual(wmap["10"].at(3).GetFlightDistance(), 400);
//
//            Assert::AreEqual(wmap["1"].at(0).GetDurabilityMax(), -1);
//            Assert::AreEqual(wmap["1"].at(3).GetDurabilityMax(), -1);
//            Assert::AreEqual(wmap["10"].at(0).GetDurabilityMax(), -1);
//            Assert::AreEqual(wmap["10"].at(3).GetDurabilityMax(), -1);
//
//            Assert::AreEqual(wmap["1"].at(0).GetDurability(), 500);
//            Assert::AreEqual(wmap["1"].at(3).GetDurability(), 470);
//            Assert::AreEqual(wmap["10"].at(0).GetDurability(), 140);
//            Assert::AreEqual(wmap["10"].at(3).GetDurability(), 110);
//        }
//
//        // 暗号化されたファイルの読み込みテスト
//        TEST_METHOD(TestMethod12)
//        {
//            WeaponManager* wm = WeaponManager::GetObj();
//            wm->Init("..\\StarmanLibTest\\weapon.csv.enc",
//                     "..\\StarmanLibTest\\weaponSave.csv.enc",
//                     true);
//
//            WeaponTypeMap wmap = wm->GetWeaponTypeMap();
//            Assert::AreEqual(wmap["w1"].GetName().c_str(), "石");
//            Assert::AreEqual(wmap["w10"].GetName().c_str(), "アトラトルに使う槍");
//            Assert::AreEqual(wmap["w1"].GetDetail().c_str(), "\"投げたり、殴ったりする。シャレにならないくらい強い。\n\"");
//            Assert::AreEqual(wmap["w10"].GetDetail().c_str(), "\"槍の柄の部分が柔らかく「しなる」材質じゃないと、実は全然飛ばない。\n何回も使うとそのことに気が付く。\n\n＋１～＋５\n\"");
//            Assert::AreEqual(wmap["w1"].GetWeight(), 0.5);
//            Assert::AreEqual(wmap["w10"].GetWeight(), 0.6);
//            Assert::AreEqual(wmap["w1"].GetVolume(), 500);
//            Assert::AreEqual(wmap["w10"].GetVolume(), 2000);
//            Assert::AreEqual(wmap["w1"].GetOwnDamage(), 10);
//            Assert::AreEqual(wmap["w10"].GetOwnDamage(), 5);
//
//            Assert::AreEqual(wmap["w1"].GetIsShow(), true);
//            Assert::AreEqual(wmap["w10"].GetIsShow(), false);
//        }
//        // ファイルを暗号化して出力するテスト
//        TEST_METHOD(TestMethod13)
//        {
//            WeaponManager* wm = WeaponManager::GetObj();
//            wm->Init("..\\StarmanLibTest\\weapon.csv",
//                     "..\\StarmanLibTest\\weaponSave.csv");
//
//            wm->Save("..\\StarmanLibTest\\weaponSave2.csv.enc",
//                     true);
//            {
//                std::ifstream ifs1("..\\StarmanLibTest\\weaponSave2.csv.enc");
//                std::ifstream ifs2("..\\StarmanLibTest\\weaponSave.csv.enc");
//                std::string file1 { std::istreambuf_iterator<char>(ifs1), std::istreambuf_iterator<char>() };
//                std::string file2 { std::istreambuf_iterator<char>(ifs2), std::istreambuf_iterator<char>() };
//                Assert::AreEqual(file1, file2);
//            }
//        }
//        // 暗号化して出力したファイルを読み込むテスト
//        TEST_METHOD(TestMethod14)
//        {
//            {
//                WeaponManager* wm = WeaponManager::GetObj();
//                wm->Init("..\\StarmanLibTest\\weapon.csv",
//                         "..\\StarmanLibTest\\weaponSave.csv");
//
//                wm->Save("..\\StarmanLibTest\\weaponSave3.csv.enc",
//                         true);
//                WeaponManager::Destroy();
//            }
//            {
//                WeaponManager* wm = WeaponManager::GetObj();
//                wm->Init("..\\StarmanLibTest\\weapon.csv.enc",
//                         "..\\StarmanLibTest\\weaponSave3.csv.enc",
//                         true);
//
//                WeaponTypeMap wmap = wm->GetWeaponTypeMap();
//                Assert::AreEqual(wmap["w1"].GetName().c_str(), "石");
//                Assert::AreEqual(wmap["w10"].GetName().c_str(), "アトラトルに使う槍");
//                Assert::AreEqual(wmap["w1"].GetDetail().c_str(), "\"投げたり、殴ったりする。シャレにならないくらい強い。\n\"");
//                Assert::AreEqual(wmap["w10"].GetDetail().c_str(), "\"槍の柄の部分が柔らかく「しなる」材質じゃないと、実は全然飛ばない。\n何回も使うとそのことに気が付く。\n\n＋１～＋５\n\"");
//                Assert::AreEqual(wmap["w1"].GetWeight(), 0.5);
//                Assert::AreEqual(wmap["w10"].GetWeight(), 0.6);
//                Assert::AreEqual(wmap["w1"].GetVolume(), 500);
//                Assert::AreEqual(wmap["w10"].GetVolume(), 2000);
//                Assert::AreEqual(wmap["w1"].GetOwnDamage(), 10);
//                Assert::AreEqual(wmap["w10"].GetOwnDamage(), 5);
//
//                Assert::AreEqual(wmap["w1"].GetIsShow(), true);
//                Assert::AreEqual(wmap["w10"].GetIsShow(), false);
//            }
//        }
    };
}

