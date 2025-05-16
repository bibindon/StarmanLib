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
            itemManager->Init(_T("..\\StarmanLibTest\\item.csv"), _T("..\\StarmanLibTest\\item_pos.csv"));

            Inventory* inventory = Inventory::GetObj();
            inventory->Init(_T("..\\StarmanLibTest\\inventory.csv"));

            StorehouseManager* storehouseManager = StorehouseManager::Get();
            storehouseManager->Init(_T("..\\StarmanLibTest\\storehouseListOrigin.csv"));

            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init(_T("..\\StarmanLibTest\\craftDef.csv"));
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
            wm->Init(_T("..\\StarmanLibTest\\weapon.csv"),
                     _T("..\\StarmanLibTest\\weaponSave.csv"));

            WeaponManager::Destroy();
        }

        // Init関数による読み込みテスト
        TEST_METHOD(TestMethod03)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init(_T("..\\StarmanLibTest\\weapon.csv"),
                     _T("..\\StarmanLibTest\\weaponSave.csv"));

            std::wstring work;
            //------------------------------------------------
            work = wm->GetDetail(_T("石"));
            Assert::AreNotEqual(std::wstring::npos, work.find(_T("投げたり")));

            work = wm->GetDetail(_T("アトラトルに使う槍"));
            Assert::AreNotEqual(std::wstring::npos, work.find(_T("そのことに気が付く。")));

            //------------------------------------------------
            work = wm->GetXfilename(_T("石"));
            Assert::AreEqual(_T("stone.x"), work.c_str());

            work = wm->GetXfilename(_T("アトラトルに使う槍"));
            Assert::AreEqual(_T("spearForAtlatl.x"), work.c_str());

            //------------------------------------------------
            work = wm->GetImageName(_T("石"));
            Assert::AreEqual(_T("stone.png"), work.c_str());

            work = wm->GetImageName(_T("アトラトルに使う槍"));
            Assert::AreEqual(_T("spearForAtlatl.png"), work.c_str());

            //------------------------------------------------
            work = wm->GetImageName(_T("石"));
            Assert::AreEqual(_T("stone.png"), work.c_str());

            work = wm->GetImageName(_T("アトラトルに使う槍"));
            Assert::AreEqual(_T("spearForAtlatl.png"), work.c_str());

            double work_d = 0.0;
            //------------------------------------------------
            work_d = wm->GetWeight(_T("石"));
            Assert::AreEqual(0.5, work_d);

            work_d = wm->GetWeight(_T("アトラトルに使う槍"));
            Assert::AreEqual(0.6, work_d);

            int work_i = 0;
            //------------------------------------------------
            work_i = wm->GetVolume(_T("石"));
            Assert::AreEqual(500, work_i);

            work_i = wm->GetVolume(_T("アトラトルに使う槍"));
            Assert::AreEqual(2000, work_i);

            //------------------------------------------------
            work_i = wm->GetReinforceMax(_T("石"));
            Assert::AreEqual(0, work_i);

            work_i = wm->GetReinforceMax(_T("アトラトルに使う槍"));
            Assert::AreEqual(5, work_i);

            //------------------------------------------------
            work_i = wm->GetReinforceMax(_T("石"));
            Assert::AreEqual(0, work_i);

            work_i = wm->GetReinforceMax(_T("アトラトルに使う槍"));
            Assert::AreEqual(5, work_i);

            //------------------------------------------------
            work_i = wm->GetOwnDamage(_T("石"));
            Assert::AreEqual(10, work_i);

            work_i = wm->GetOwnDamage(_T("アトラトルに使う槍"));
            Assert::AreEqual(5, work_i);

            bool work_b = false;

            //------------------------------------------------
            work_b = wm->GetIsShow(_T("石"));
            Assert::AreEqual(true, work_b);

            work_b = wm->GetIsShow(_T("アトラトルに使う槍"));
            Assert::AreEqual(false, work_b);

            WeaponManager::Destroy();
        }

        // Init関数による読み込みテスト
        // 強化値を指定
        TEST_METHOD(TestMethod04)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init(_T("..\\StarmanLibTest\\weapon.csv"),
                     _T("..\\StarmanLibTest\\weaponSave.csv"));

            double work_d = 0.0;

            // 石は強化できないので強化値＋２の石は存在しない。
            // 取得しようとしたら例外が発生する
            Assert::ExpectException<std::exception>(
                [&]
                {
                    work_d = wm->GetAttackRate(_T("石"), 2);
                });

            //-------------------------------------------------
            work_d = wm->GetAttackRate(_T("石"), -1);
            Assert::AreEqual(3.0, work_d);

            work_d = wm->GetAttackRate(_T("アトラトルに使う槍"), 3);
            Assert::AreEqual(2.0, work_d);

            //-------------------------------------------------
            work_d = wm->GetFlightDistance(_T("石"), -1);
            Assert::AreEqual(30.0, work_d);

            work_d = wm->GetFlightDistance(_T("弓矢の弓"), 3);
            Assert::AreEqual(6.0, work_d);

            work_d = wm->GetFlightDistance(_T("アトラトルに使う槍"), 3);
            Assert::AreEqual(40.0, work_d);

            //-------------------------------------------------
            int work_i = 0;
            work_i = wm->GetDurabilityMax(_T("石"), -1);
            Assert::AreEqual(999, work_i);

            work_i = wm->GetDurabilityMax(_T("アトラトルに使う槍"), 3);
            Assert::AreEqual(40, work_i);

            WeaponManager::Destroy();
        }
    };
}

