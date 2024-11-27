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
    itemManager->Init("..\\StarmanLibTest\\item.csv");

    Inventory* inventory = Inventory::GetObj();
    inventory->Init("..\\StarmanLibTest\\inventory.csv");

    Storehouse* storehouse = Storehouse::GetObj();
    storehouse->Init("..\\StarmanLibTest\\storehouse.csv");

    CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
    craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

    PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();
    powereggDateTime->Init("..\\StarmanLibTest\\datetime.csv");
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
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueue.csv");
            Assert::AreEqual(obj != nullptr, true);
            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueue.csv");
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
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueue.csv");
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
                craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueue.csv");

                bool result = false;
                obj->SetCraftsmanSkill("�C�J�_", 1);
                obj->SetCraftsmanSkill("�Εt���S�p�C�v");
                obj->Save("..\\StarmanLibTest\\craftsmanSkillSave.csv", "..\\StarmanLibTest\\craftsmanQueueSave.csv");

                CraftSystem::Destroy();
                CraftInfoManager::Destroy();
            }
            {
                CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
                craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("..\\StarmanLibTest\\craftsmanSkillSave.csv", "..\\StarmanLibTest\\craftsmanQueueSave.csv");

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
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueue.csv");
            obj->QueueCraftRequest("�C�J�_");

            CraftSystem::Destroy();

            Finalize();
        }

        // �N���t�g�p�̑f�ނ��Ȃ��ăL���[�C���O���s
        TEST_METHOD(TestMethod07)
        {
            Initialize();

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
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
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
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
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
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
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
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
        // TODO ������ǂ��������B
        TEST_METHOD(TestMethod11)
        {
            Initialize();

            Storehouse* storehouse = Storehouse::GetObj();
            int work = 0;
            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 0);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
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
        TEST_METHOD(TestMethod12)
        {
            Initialize();

            Storehouse* storehouse = Storehouse::GetObj();
            int work = 0;
            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 0);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");
            obj->QueueCraftRequest("�Α�");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 1);

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 2);

            CraftSystem::Destroy();

            Finalize();
        }

        // �����L���[�C���O���ăX�^�[�g���Ċ������đq�ɂɊ����i�������(2)
        TEST_METHOD(TestMethod13)
        {
            Initialize();

            Storehouse* storehouse = Storehouse::GetObj();
            int work = 0;

            work = storehouse->CountItem("�Α�");
            Assert::AreEqual(work, 0);

            work = storehouse->CountItem("�A�g���g��");
            Assert::AreEqual(work, 0);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv", "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");
            obj->QueueCraftRequest("�A�g���g��");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�");
            Assert::AreEqual(work, 1);

            work = storehouse->CountItem("�A�g���g��");
            Assert::AreEqual(work, 0);

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�");
            Assert::AreEqual(work, 1);

            work = storehouse->CountItem("�A�g���g��");
            Assert::AreEqual(work, 1);

            CraftSystem::Destroy();

            Finalize();
        }

        // �i���x���擾�ł���

        // �ۑ��ł���

        // �L���[�C���O���ăL�����Z��

        // �����L���[�C���O���ăL�����Z��

        // �f�ނɕ��킪����ꍇ�B

    };
}
