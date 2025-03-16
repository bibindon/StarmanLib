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

        // Init�֐��ɂ��ǂݍ��݃e�X�g
        TEST_METHOD(TestMethod03)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init("..\\StarmanLibTest\\weapon.csv",
                     "..\\StarmanLibTest\\weaponSave.csv");

            std::string work;
            //------------------------------------------------
            work = wm->GetDetail("��");
            Assert::AreNotEqual(std::string::npos, work.find("��������"));

            work = wm->GetDetail("�A�g���g���Ɏg����");
            Assert::AreNotEqual(std::string::npos, work.find("���̂��ƂɋC���t���B"));

            //------------------------------------------------
            work = wm->GetXfilename("��");
            Assert::AreEqual("stone.x", work.c_str());

            work = wm->GetXfilename("�A�g���g���Ɏg����");
            Assert::AreEqual("spearForAtlatl.x", work.c_str());

            //------------------------------------------------
            work = wm->GetImageName("��");
            Assert::AreEqual("stone.png", work.c_str());

            work = wm->GetImageName("�A�g���g���Ɏg����");
            Assert::AreEqual("spearForAtlatl.png", work.c_str());

            //------------------------------------------------
            work = wm->GetImageName("��");
            Assert::AreEqual("stone.png", work.c_str());

            work = wm->GetImageName("�A�g���g���Ɏg����");
            Assert::AreEqual("spearForAtlatl.png", work.c_str());

            double work_d = 0.0;
            //------------------------------------------------
            work_d = wm->GetWeight("��");
            Assert::AreEqual(0.5, work_d);

            work_d = wm->GetWeight("�A�g���g���Ɏg����");
            Assert::AreEqual(0.6, work_d);

            int work_i = 0;
            //------------------------------------------------
            work_i = wm->GetVolume("��");
            Assert::AreEqual(500, work_i);

            work_i = wm->GetVolume("�A�g���g���Ɏg����");
            Assert::AreEqual(2000, work_i);

            //------------------------------------------------
            work_i = wm->GetReinforceMax("��");
            Assert::AreEqual(0, work_i);

            work_i = wm->GetReinforceMax("�A�g���g���Ɏg����");
            Assert::AreEqual(5, work_i);

            //------------------------------------------------
            work_i = wm->GetReinforceMax("��");
            Assert::AreEqual(0, work_i);

            work_i = wm->GetReinforceMax("�A�g���g���Ɏg����");
            Assert::AreEqual(5, work_i);

            //------------------------------------------------
            work_i = wm->GetOwnDamage("��");
            Assert::AreEqual(10, work_i);

            work_i = wm->GetOwnDamage("�A�g���g���Ɏg����");
            Assert::AreEqual(5, work_i);

            bool work_b = false;

            //------------------------------------------------
            work_b = wm->GetIsShow("��");
            Assert::AreEqual(true, work_b);

            work_b = wm->GetIsShow("�A�g���g���Ɏg����");
            Assert::AreEqual(false, work_b);

            WeaponManager::Destroy();
        }

        // Init�֐��ɂ��ǂݍ��݃e�X�g
        // �����l���w��
        TEST_METHOD(TestMethod04)
        {
            WeaponManager* wm = WeaponManager::GetObj();
            wm->Init("..\\StarmanLibTest\\weapon.csv",
                     "..\\StarmanLibTest\\weaponSave.csv");

            double work_d = 0.0;

            // �΂͋����ł��Ȃ��̂ŋ����l�{�Q�̐΂͑��݂��Ȃ��B
            // �擾���悤�Ƃ������O����������
            Assert::ExpectException<std::exception>(
                [&]
                {
                    work_d = wm->GetAttackRate("��", 2);
                });

            //-------------------------------------------------
            work_d = wm->GetAttackRate("��", -1);
            Assert::AreEqual(3.0, work_d);

            work_d = wm->GetAttackRate("�A�g���g���Ɏg����", 3);
            Assert::AreEqual(2.0, work_d);

            //-------------------------------------------------
            work_d = wm->GetFlightDistance("��", -1);
            Assert::AreEqual(30.0, work_d);

            work_d = wm->GetFlightDistance("�|��̋|", 3);
            Assert::AreEqual(6.0, work_d);

            work_d = wm->GetFlightDistance("�A�g���g���Ɏg����", 3);
            Assert::AreEqual(40.0, work_d);

            //-------------------------------------------------
            int work_i = 0;
            work_i = wm->GetDurabilityMax("��", -1);
            Assert::AreEqual(999, work_i);

            work_i = wm->GetDurabilityMax("�A�g���g���Ɏg����", 3);
            Assert::AreEqual(40, work_i);

            WeaponManager::Destroy();
        }
    };
}

