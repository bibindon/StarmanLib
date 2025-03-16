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
            itemManager->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

            Inventory* inventory = Inventory::GetObj();
            inventory->Init("..\\StarmanLibTest\\inventory.csv");

            StorehouseManager* storehouseManager = StorehouseManager::Get();
            storehouseManager->Init("..\\StarmanLibTest\\storehouseListOrigin.csv");

            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");
        }

        TEST_METHOD_CLEANUP(CleanUp)
        {
            CraftInfoManager::Destroy();
            StorehouseManager::Destroy();
            Inventory::Destroy();
            ItemManager::Destroy();
        }

        TEST_METHOD(TestMethod01)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            WeaponManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init("..\\StarmanLibTest\\weapon.csv",
                     "..\\StarmanLibTest\\weaponSave.csv");

            WeaponManager::Destroy();
        }

        // Init関数による読み込みテスト
        TEST_METHOD(TestMethod03)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init("..\\StarmanLibTest\\weapon.csv",
                     "..\\StarmanLibTest\\weaponSave.csv");

            std::string work;
            //------------------------------------------------
            work = wm->GetDetail("石");
            Assert::AreNotEqual(std::string::npos, work.find("投げたり"));

            work = wm->GetDetail("アトラトルに使う槍");
            Assert::AreNotEqual(std::string::npos, work.find("そのことに気が付く。"));

            //------------------------------------------------
            work = wm->GetXfilename("石");
            Assert::AreEqual("stone.x", work.c_str());

            work = wm->GetXfilename("アトラトルに使う槍");
            Assert::AreEqual("spearForAtlatl.x", work.c_str());

            //------------------------------------------------
            work = wm->GetImageName("石");
            Assert::AreEqual("stone.png", work.c_str());

            work = wm->GetImageName("アトラトルに使う槍");
            Assert::AreEqual("spearForAtlatl.png", work.c_str());

            //------------------------------------------------
            work = wm->GetImageName("石");
            Assert::AreEqual("stone.png", work.c_str());

            work = wm->GetImageName("アトラトルに使う槍");
            Assert::AreEqual("spearForAtlatl.png", work.c_str());

            double work_d = 0.0;
            //------------------------------------------------
            work_d = wm->GetWeight("石");
            Assert::AreEqual(0.5, work_d);

            work_d = wm->GetWeight("アトラトルに使う槍");
            Assert::AreEqual(0.6, work_d);

            int work_i = 0;
            //------------------------------------------------
            work_i = wm->GetVolume("石");
            Assert::AreEqual(500, work_i);

            work_i = wm->GetVolume("アトラトルに使う槍");
            Assert::AreEqual(2000, work_i);

            //------------------------------------------------
            work_i = wm->GetReinforceMax("石");
            Assert::AreEqual(0, work_i);

            work_i = wm->GetReinforceMax("アトラトルに使う槍");
            Assert::AreEqual(5, work_i);

            //------------------------------------------------
            work_i = wm->GetReinforceMax("石");
            Assert::AreEqual(0, work_i);

            work_i = wm->GetReinforceMax("アトラトルに使う槍");
            Assert::AreEqual(5, work_i);

            //------------------------------------------------
            work_i = wm->GetOwnDamage("石");
            Assert::AreEqual(10, work_i);

            work_i = wm->GetOwnDamage("アトラトルに使う槍");
            Assert::AreEqual(5, work_i);

            bool work_b = false;

            //------------------------------------------------
            work_b = wm->GetIsShow("石");
            Assert::AreEqual(true, work_b);

            work_b = wm->GetIsShow("アトラトルに使う槍");
            Assert::AreEqual(false, work_b);

            WeaponManager::Destroy();
        }

        // Init関数による読み込みテスト
        // 強化値を指定
        TEST_METHOD(TestMethod04)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init("..\\StarmanLibTest\\weapon.csv",
                     "..\\StarmanLibTest\\weaponSave.csv");

            double work_d = 0.0;

            // 石は強化できないので強化値＋２の石は存在しない。
            // 取得しようとしたら例外が発生する
            Assert::ExpectException<std::exception>(
                [&]
                {
                    work_d = wm->GetAttackRate("石", 2);
                });

            //-------------------------------------------------
            work_d = wm->GetAttackRate("石", -1);
            Assert::AreEqual(3.0, work_d);

            work_d = wm->GetAttackRate("アトラトルに使う槍", 3);
            Assert::AreEqual(2.0, work_d);

            //-------------------------------------------------
            work_d = wm->GetFlightDistance("石", -1);
            Assert::AreEqual(30.0, work_d);

            work_d = wm->GetFlightDistance("弓矢の弓", 3);
            Assert::AreEqual(6.0, work_d);

            work_d = wm->GetFlightDistance("アトラトルに使う槍", 3);
            Assert::AreEqual(40.0, work_d);

            //-------------------------------------------------
            int work_i = 0;
            work_i = wm->GetDurabilityMax("石", -1);
            Assert::AreEqual(999, work_i);

            work_i = wm->GetDurabilityMax("アトラトルに使う槍", 3);
            Assert::AreEqual(40, work_i);

            WeaponManager::Destroy();
        }
    };
}

