#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/CraftSystem.h"
#include "../StarmanLib/ItemManager.h"
#include "../StarmanLib/Inventory.h"
#include "../StarmanLib/Storehouse.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include "../StarmanLib/PowereggDateTime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

void Initialize()
{
    ItemManager* itemManager = ItemManager::GetObj();
    itemManager->Init("item.csv");

    Inventory* inventory = Inventory::GetObj();
    inventory->Init("inventory.csv");

    Storehouse* storehouse = Storehouse::GetObj();
    storehouse->Init("storehouse.csv");

    CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
    craftInfoManager->Init("craftDef.csv");

    PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();
    powereggDateTime->Init("datetime.csv");
}

void Finalize()
{
    PowereggDateTime::Destroy();
    CraftInfoManager::Destroy();
    Storehouse::Destroy();
    Inventory::Destroy();
    ItemManager::Destroy();
}

    TEST_CLASS(CraftSystemTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");
            Assert::AreEqual(obj != nullptr, true);
            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");
            bool result = false;
            result = obj->GetCraftsmanSkill("�C�J�_");
            Assert::AreEqual(result, true);

            result = obj->GetCraftsmanSkill("�C�J�_", 1);
            Assert::AreEqual(result, false);

            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");
            bool result = false;
            obj->SetCraftsmanSkill("�C�J�_");
            result = obj->GetCraftsmanSkill("�C�J�_");
            Assert::AreEqual(result, true);

            obj->SetCraftsmanSkill("�C�J�_", 1);
            result = obj->GetCraftsmanSkill("�C�J�_", 1);
            Assert::AreEqual(result, true);

            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            {
                CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
                craftInfoManager->Init("craftDef.csv");

                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");

                bool result = false;
                obj->SetCraftsmanSkill("�C�J�_", 1);
                obj->SetCraftsmanSkill("�Εt���S�p�C�v");
                obj->Save("craftsmanSkillSave.csv", "craftsmanQueueSave.csv");

                CraftSystem::Destroy();
                CraftInfoManager::Destroy();
            }
            {
                CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
                craftInfoManager->Init("craftDef.csv");

                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("craftsmanSkillSave.csv", "craftsmanQueueSave.csv");

                bool result = false;
                result = obj->GetCraftsmanSkill("�C�J�_", 1);
                Assert::AreEqual(result, true);

                result = obj->GetCraftsmanSkill("�Εt���S�p�C�v");
                Assert::AreEqual(result, true);

                CraftSystem::Destroy();
                CraftInfoManager::Destroy();
            }
        }

        TEST_METHOD(TestMethod06)
        {
            Initialize();

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");
            obj->QueueCraftRequest("�C�J�_");

            CraftSystem::Destroy();

            Finalize();
        }

        // �N���t�g�p�̑f�ނ��Ȃ��ăL���[�C���O���s
        TEST_METHOD(TestMethod07)
        {
            Initialize();

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueueEmpty.csv");
            bool result = obj->QueueCraftRequest("�C�J�_");

            Assert::AreEqual(result, false);

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 0, true);

            CraftSystem::Destroy();

            Finalize();
        }

        // �L���[�C���O���ăX�^�[�g
        TEST_METHOD(TestMethod08)
        {
            Initialize();

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�A�g���g��");

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), false);

            obj->UpdateCraftStatus();

            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), true);

            CraftSystem::Destroy();

            Finalize();
        }

        // �L���[�C���O�������_�ŃN���t�g�p�f�ނ��C���x���g������Ȃ��Ȃ�
        TEST_METHOD(TestMethod09)
        {
            Initialize();

            Inventory* inventory = Inventory::GetObj();
            int temp = 0;

            temp = inventory->CountItem("�ׂ��؂̊�");
            Assert::AreEqual(temp, 15);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), false);

            temp = inventory->CountItem("�ׂ��؂̊�");
            Assert::AreEqual(temp, 14);

            temp = inventory->CountItem("�����`�̐΁i���j");
            Assert::AreEqual(temp, 1);

            obj->UpdateCraftStatus();

            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), true);

            temp = inventory->CountItem("�ׂ��؂̊�");
            Assert::AreEqual(temp, 14);

            temp = inventory->CountItem("�����`�̐΁i���j");
            Assert::AreEqual(temp, 1);

            CraftSystem::Destroy();

            Finalize();
        }

        // �L���[�C���O���ăX�^�[�g���Ċ�������
        TEST_METHOD(TestMethod10)
        {
            Initialize();

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            // �N���t�g�v�����Ȃ��Ȃ��Ă��邱��
            Assert::AreEqual((int)craftRequestList.size() == 0, true);

            CraftSystem::Destroy();

            Finalize();
        }

        // �L���[�C���O���ăX�^�[�g���Ċ������đq�ɂɊ����i���ǉ������
        TEST_METHOD(TestMethod11)
        {
            Initialize();

            Storehouse* storehouse = Storehouse::GetObj();
            int work = 0;
            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 0);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 1);

            CraftSystem::Destroy();

            Finalize();
        }

        // �����L���[�C���O���ăX�^�[�g���Ċ������đq�ɂɊ����i�������

        // �i���x���擾�ł���

        // �ۑ��ł���

        // �L���[�C���O���ăL�����Z��

        // �����L���[�C���O���ăL�����Z��

        // �f�ނɕ��킪����ꍇ�B

    };
}
