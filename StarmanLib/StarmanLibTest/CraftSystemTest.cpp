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

    TEST_CLASS(CraftSystemTest)
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

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();
            powereggDateTime->Init("..\\StarmanLibTest\\datetime.csv");
        }

        TEST_METHOD_CLEANUP(CleanUp)
        {
            PowereggDateTime::Destroy();
            CraftInfoManager::Destroy();
            Storehouse::Destroy();
            Inventory::Destroy();
            ItemManager::Destroy();
        }
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
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueue.csv");
            Assert::AreEqual(obj != nullptr, true);
            CraftSystem::Destroy();
        }

        // �E�l�̃��x�����擾�ł��邩�e�X�g
        TEST_METHOD(TestMethod03)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueue.csv");
            int result = false;
            result = obj->GetCraftsmanSkill("�C�J�_");
            Assert::AreEqual(result, -1);

            result = obj->GetCraftsmanSkill("�؂̖_");
            Assert::AreEqual(result, 1);

            CraftSystem::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueue.csv");
            int result = 0;
            obj->SetCraftsmanSkill("�C�J�_", 1);
            result = obj->GetCraftsmanSkill("�C�J�_");
            Assert::AreEqual(result, 1);

            obj->SetCraftsmanSkill("�؂̖_", 2);
            result = obj->GetCraftsmanSkill("�؂̖_");
            Assert::AreEqual(result, 2);

            CraftSystem::Destroy();
        }

        // �E�l�̃X�L�����ۑ��ł��Ă��邱�Ƃ��m�F
        TEST_METHOD(TestMethod05)
        {
            {
                CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
                craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                          "..\\StarmanLibTest\\craftsmanQueue.csv");

                bool result = false;
                obj->SetCraftsmanSkill("�C�J�_", 1);
                obj->SetCraftsmanSkill("�A�g���g���Ɏg����", 1);
                obj->Save("..\\StarmanLibTest\\craftsmanSkillSave.csv",
                          "..\\StarmanLibTest\\craftsmanQueueSave.csv");

                CraftSystem::Destroy();
                CraftInfoManager::Destroy();
            }
            {
                CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
                craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("..\\StarmanLibTest\\craftsmanSkillSave.csv",
                          "..\\StarmanLibTest\\craftsmanQueueSave.csv");

                int result = false;
                result = obj->GetCraftsmanSkill("�C�J�_");
                Assert::AreEqual(result, 1);

                result = obj->GetCraftsmanSkill("�A�g���g���Ɏg����");
                Assert::AreEqual(result, 1);

                CraftSystem::Destroy();
                CraftInfoManager::Destroy();
            }
        }

        TEST_METHOD(TestMethod06)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueue.csv");
            obj->QueueCraftRequest("�C�J�_");

            CraftSystem::Destroy();
        }

        // �N���t�g�p�̑f�ނ��Ȃ��ăL���[�C���O���s
        TEST_METHOD(TestMethod07)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            bool result = obj->QueueCraftRequest("�C�J�_");

            Assert::AreEqual(result, false);

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 0, true);

            CraftSystem::Destroy();
        }

        // �L���[�C���O���ăX�^�[�g
        TEST_METHOD(TestMethod08)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
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
        }

        // �L���[�C���O�������_�ŃN���t�g�p�f�ނ��C���x���g������Ȃ��Ȃ�
        TEST_METHOD(TestMethod09)
        {
            Inventory* inventory = Inventory::GetObj();
            int temp = 0;

            temp = inventory->CountItem("�ׂ��؂̊�");
            Assert::AreEqual(temp, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), false);

            temp = inventory->CountItem("�ׂ��؂̊�");
            Assert::AreEqual(temp, 9);

            temp = inventory->CountItem("�����`�̐΁i���j");
            Assert::AreEqual(temp, 9);

            obj->UpdateCraftStatus();

            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), true);

            temp = inventory->CountItem("�ׂ��؂̊�");
            Assert::AreEqual(temp, 9);

            temp = inventory->CountItem("�����`�̐΁i���j");
            Assert::AreEqual(temp, 9);

            CraftSystem::Destroy();
        }

        // �L���[�C���O���ăX�^�[�g���Ċ�������
        TEST_METHOD(TestMethod10)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
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
        }

        // �L���[�C���O���ăX�^�[�g���Ċ������đq�ɂɊ����i���ǉ������
        TEST_METHOD(TestMethod11)
        {
            Storehouse* storehouse = Storehouse::GetObj();
            int work = 0;
            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 11);

            CraftSystem::Destroy();
        }

        // �����L���[�C���O���ăX�^�[�g���Ċ������đq�ɂɊ����i�������
        TEST_METHOD(TestMethod12)
        {
            Storehouse* storehouse = Storehouse::GetObj();
            int work = 0;
            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");
            obj->QueueCraftRequest("�Α�");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 11);

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 12);

            CraftSystem::Destroy();
        }

        // �����L���[�C���O���ăX�^�[�g���Ċ������đq�ɂɊ����i�������(2)
        TEST_METHOD(TestMethod13)
        {
            Storehouse* storehouse = Storehouse::GetObj();
            int work = 0;

            work = storehouse->CountItem("�Α�");
            Assert::AreEqual(work, 10);

            work = storehouse->CountItem("�A�g���g��");
            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");
            obj->QueueCraftRequest("�A�g���g��");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�");
            Assert::AreEqual(work, 11);

            work = storehouse->CountItem("�A�g���g��");
            Assert::AreEqual(work, 10);

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�");
            Assert::AreEqual(work, 11);

            work = storehouse->CountItem("�A�g���g��");
            Assert::AreEqual(work, 11);

            CraftSystem::Destroy();
        }

        // �i���x���擾�ł���
        TEST_METHOD(TestMethod14)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 12���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

            obj->UpdateCraftStatus();

            int progress = obj->GetProgress();

            Assert::AreEqual(progress, 50);

            CraftSystem::Destroy();
        }

        // �ۑ��ł���
        TEST_METHOD(TestMethod15)
        {
            {
                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                          "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
                obj->QueueCraftRequest("�Α�");

                obj->UpdateCraftStatus();

                PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

                // 12���ԁA����i�߂�
                powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

                obj->UpdateCraftStatus();

                int progress = obj->GetProgress();

                Assert::AreEqual(progress, 50);
                obj->Save("..\\StarmanLibTest\\craftsmanSkillSave.csv",
                          "..\\StarmanLibTest\\craftsmanQueueSave.csv");

                CraftSystem::Destroy();
            }
            {
                CraftSystem* obj = CraftSystem::GetObj();
                obj->Init("..\\StarmanLibTest\\craftsmanSkillSave.csv",
                          "..\\StarmanLibTest\\craftsmanQueueSave.csv");

                int work = 0;

                work = obj->GetCraftRequestList().size();
                Assert::AreEqual(work, 1);

                work = obj->GetProgress();
                Assert::AreEqual(work, 50);

                CraftRequest craftRequest = obj->GetCraftRequestList().front();
                Assert::AreEqual(craftRequest.GetCrafting(), true);

                Assert::AreEqual(craftRequest.GetStartHour(), 33);
                Assert::AreEqual(craftRequest.GetStartMinute(), 44);
                Assert::AreEqual(craftRequest.GetStartSecond(), 55);

                Assert::AreEqual(craftRequest.GetFinishHour(), 33);
                Assert::AreEqual(craftRequest.GetFinishMinute(), 44);
                Assert::AreEqual(craftRequest.GetFinishSecond(), 55);

                CraftSystem::Destroy();
            }
        }

        // �L���[�C���O���ăL�����Z��
        TEST_METHOD(TestMethod16)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 12���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

            obj->UpdateCraftStatus();

            obj->CancelCraftStart(0);

            int size = obj->GetCraftRequestList().size();

            Assert::AreEqual(size, 0);

            CraftSystem::Destroy();
        }

        // �����L���[�C���O���ăL�����Z��
        TEST_METHOD(TestMethod17)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            obj->QueueCraftRequest("�Α�");
            obj->QueueCraftRequest("�Α�");
            obj->QueueCraftRequest("�Α�");

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 12���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

            obj->UpdateCraftStatus();

            obj->CancelCraftStart(0);
            obj->CancelCraftStart(0);

            int size = obj->GetCraftRequestList().size();

            Assert::AreEqual(size, 1);

            CraftSystem::Destroy();
        }

        // �K��񐔁A�N���t�g���s���Ƌ����l�̍����A�C�e�����N���t�g�����悤�ɂȂ�B


        // �E�l�̏n���x��������ԂŃN���t�g���˗�����Ɠ����f�ނ��g���Ă�
        // �����x�̍����A�C�e���������B
        // �_�[�N�\�E���̂悤�ȌÂ������f�ނɎg���A�Ƃ������Ƃ͂��Ȃ��B

        // �f�ނɕ��킪����ꍇ�B

    };
}
