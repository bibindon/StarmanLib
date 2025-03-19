#include "CppUnitTest.h"
#include "../StarmanLib/CraftSystem.h"
#include "../StarmanLib/ItemManager.h"
#include "../StarmanLib/Storehouse.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include "../StarmanLib/PowereggDateTime.h"
#include "../StarmanLib/Voyage.h"

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
            itemManager->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

            StorehouseManager* storehouseManager = StorehouseManager::Get();
            storehouseManager->Init("..\\StarmanLibTest\\storehouseListOrigin.csv");

            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
            craftInfoManager->Init("..\\StarmanLibTest\\craftDef.csv");

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();
            powereggDateTime->Init("..\\StarmanLibTest\\datetime.csv");
        }

        TEST_METHOD_CLEANUP(CleanUp)
        {
            PowereggDateTime::Destroy();
            CraftInfoManager::Destroy();
            StorehouseManager::Destroy();
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
            std::string work;
            obj->QueueCraftRequest("�C�J�_", &work, 1);

            CraftSystem::Destroy();
        }

        // �N���t�g�p�̑f�ނ��Ȃ��ăL���[�C���O���s
        TEST_METHOD(TestMethod07)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work;
            bool result = obj->QueueCraftRequest("�C�J�_", &work, 1);

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

            std::string work;
            obj->QueueCraftRequest("�A�g���g��", &work, 1);

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
            auto storehouse = StorehouseManager::Get()->GetCurrentActiveStorehouse();
            int temp = 0;

            temp = storehouse->CountItem("�ׂ��؂̊�");
            Assert::AreEqual(temp, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work;
            obj->QueueCraftRequest("�Α�", &work, 1);

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), false);

            temp = storehouse->CountItem("�ׂ��؂̊�");
            Assert::AreEqual(temp, 9);

            temp = storehouse->CountItem("�����`�̐΁i���j");
            Assert::AreEqual(temp, 9);

            obj->UpdateCraftStatus();

            craftRequestList = obj->GetCraftRequestList();

            Assert::AreEqual((int)craftRequestList.size() == 1, true);
            Assert::AreEqual(craftRequestList.front().GetCrafting(), true);

            temp = storehouse->CountItem("�ׂ��؂̊�");
            Assert::AreEqual(temp, 9);

            temp = storehouse->CountItem("�����`�̐΁i���j");
            Assert::AreEqual(temp, 9);

            CraftSystem::Destroy();
        }

        // �L���[�C���O���ăX�^�[�g���Ċ�������
        TEST_METHOD(TestMethod10)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            
            std::string work;
            obj->QueueCraftRequest("�Α�", &work, 1);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            std::list<CraftRequest> craftRequestList;
            craftRequestList = obj->GetCraftRequestList();

            // �N���t�g�v�����Ȃ��Ȃ��Ă��邱��
            Assert::AreEqual(true, (int)craftRequestList.size() == 0);

            CraftSystem::Destroy();
        }

        // �L���[�C���O���ăX�^�[�g���Ċ������đq�ɂɊ����i���ǉ������
        TEST_METHOD(TestMethod11)
        {
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;
            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work2;
            obj->QueueCraftRequest("�Α�", &work2, 1);

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
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;
            work = storehouse->CountItem("�Α�");

            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work2;
            obj->QueueCraftRequest("�Α�", &work2, 1);
            obj->QueueCraftRequest("�Α�", &work2, 1);

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
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;

            work = storehouse->CountItem("�Α�");
            Assert::AreEqual(work, 10);

            work = storehouse->CountItem("�A�g���g��");
            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work2;
            obj->QueueCraftRequest("�Α�", &work2, 1);
            obj->QueueCraftRequest("�A�g���g��", &work2, 1);

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

            std::string work;
            obj->QueueCraftRequest("�Α�", &work, 1);

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

                std::string work;
                obj->QueueCraftRequest("�Α�", &work, 1);

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

            std::string work;
            obj->QueueCraftRequest("�Α�", &work, 1);

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

        // �L���[�C���O���ăL�����Z��
        // �J�n���Ă��Ȃ��N���t�g���L�����Z��������f�ނ��Ԃ��Ă���
        TEST_METHOD(TestMethod16_2)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            std::string work;
            obj->QueueCraftRequest("�Α�", &work, 1);
            obj->QueueCraftRequest("�Α�", &work, 1);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 12���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

            obj->UpdateCraftStatus();

            auto storehouse = StorehouseManager::Get()->GetCurrentActiveStorehouse();
            auto mat1 = storehouse->CountItem("�ׂ��؂̊�");
            auto mat2 = storehouse->CountItem("�����`�̐΁i���j");

            Assert::AreEqual(8, mat1);
            Assert::AreEqual(8, mat2);

            obj->CancelCraftStart(1);

            mat1 = storehouse->CountItem("�ׂ��؂̊�");
            mat2 = storehouse->CountItem("�����`�̐΁i���j");
            Assert::AreEqual(9, mat1);
            Assert::AreEqual(9, mat2);

            CraftSystem::Destroy();
        }

        // �L���[�C���O���ăL�����Z��
        // �J�n�����N���t�g���L�����Z��������f�ނ��Ԃ��Ă��Ȃ�
        TEST_METHOD(TestMethod16_3)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work;
            obj->QueueCraftRequest("�Α�", &work, 1);
            obj->QueueCraftRequest("�Α�", &work, 1);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 12���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 0, 12, 0, 0);

            obj->UpdateCraftStatus();

            auto storehouse = StorehouseManager::Get()->GetCurrentActiveStorehouse();
            auto mat1 = storehouse->CountItem("�ׂ��؂̊�");
            auto mat2 = storehouse->CountItem("�����`�̐΁i���j");

            Assert::AreEqual(8, mat1);
            Assert::AreEqual(8, mat2);

            obj->CancelCraftStart(0);

            mat1 = storehouse->CountItem("�ׂ��؂̊�");
            mat2 = storehouse->CountItem("�����`�̐΁i���j");
            Assert::AreEqual(8, mat1);
            Assert::AreEqual(8, mat2);

            CraftSystem::Destroy();
        }

        // �����L���[�C���O���ăL�����Z��
        TEST_METHOD(TestMethod17)
        {
            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");
            std::string work;
            obj->QueueCraftRequest("�Α�", &work, 1);
            obj->QueueCraftRequest("�Α�", &work, 1);
            obj->QueueCraftRequest("�Α�", &work, 1);

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
        TEST_METHOD(TestMethod18)
        {
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;
            bool work_b = false;
            work = storehouse->CountItem("�Α�", -1);

            Assert::AreEqual(work, 10);

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            work = obj->GetCraftsmanSkill("�Α�");
            Assert::AreEqual(work, -1);

            std::string work2;
            work_b = obj->QueueCraftRequest("�Α�", &work2, 1);
            work_b = obj->QueueCraftRequest("�Α�", &work2, 1);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�", -1);

            Assert::AreEqual(work, 11);

            work = obj->GetCraftsmanSkill("�Α�");
            Assert::AreEqual(work, -1);

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            work = storehouse->CountItem("�Α�", -1);

            Assert::AreEqual(work, 12);

            work = obj->GetCraftsmanSkill("�Α�");
            Assert::AreEqual(work, 1);

            CraftSystem::Destroy();
        }

        // �E�l�̏n���x��������ԂŃN���t�g���˗�����Ɠ����f�ނ��g���Ă�
        // �����x�̍����A�C�e���������B
        // �_�[�N�\�E���̂悤�ȌÂ������f�ނɎg���A�Ƃ������Ƃ͂��Ȃ��B
        TEST_METHOD(TestMethod19)
        {
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;
            bool work_b = false;

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work2;
            work_b = obj->QueueCraftRequest("�Α�", &work2, 1);

            // �E�l�ɐΑ��̐������˗�����ƁA���̎��_�ł͋����l�Ȃ��̐Α������n�߂�B
            work = obj->GetCraftRequestList().front().GetCraftInfo().GetOutput().GetLevel();
            Assert::AreEqual(work, -1);

            work_b = obj->QueueCraftRequest("�Α�", &work2, 1);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            // 1����1���ԁA����i�߂�
            // �����ŐE�l�̃��x���A�b�v�B�{�P�̐Α�������悤�ɂȂ�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            // �����ŐΑ���\�񂵂���{�P�̐Α��������
            work_b = obj->QueueCraftRequest("�Α�", &work2, 1);

            // �{�P�̐Α����\�񂳂�Ă��邩�H
            work = obj->GetCraftRequestList().front().GetCraftInfo().GetOutput().GetLevel();
            Assert::AreEqual(work, 1);

            CraftSystem::Destroy();
        }

        // ��������A����Ǘ��N���X���X�V����邩�e�X�g
        TEST_METHOD(TestMethod20)
        {
            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            int work = 0;
            bool work_b = false;

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work2;
            work_b = obj->QueueCraftRequest("�Α�", &work2, 1);

            // ����̐�����J�n
            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            // ����̐��삪����
            obj->UpdateCraftStatus();

            CraftSystem::Destroy();
        }
        
        // �f�ނɕ��킪����ꍇ�B
        //TEST_METHOD(TestMethod21)
        //{
        //    Storehouse* storehouse = Storehouse::GetObj();
        //    int work = 0;
        //    bool work_b = false;

        //    CraftSystem* obj = CraftSystem::GetObj();
        //    obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
        //              "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

        //    work_b = obj->QueueCraftRequest("�Α�");

        //    // �E�l�ɐΑ��̐������˗�����ƁA���̎��_�ł͋����l�Ȃ��̐Α������n�߂�B
        //    work = obj->GetCraftRequestList().front().GetCraftInfo().GetOutput().GetLevel();
        //    Assert::AreEqual(work, -1);

        //    work_b = obj->QueueCraftRequest("�Α�");

        //    obj->UpdateCraftStatus();

        //    PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

        //    // 1����1���ԁA����i�߂�
        //    powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

        //    obj->UpdateCraftStatus();

        //    // 1����1���ԁA����i�߂�
        //    // �����ŐE�l�̃��x���A�b�v�B�{�P�̐Α�������悤�ɂȂ�
        //    powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

        //    obj->UpdateCraftStatus();

        //    // �����ŐΑ���\�񂵂���{�P�̐Α��������
        //    work_b = obj->QueueCraftRequest("�Α�");

        //    // �{�P�̐Α����\�񂳂�Ă��邩�H
        //    work = obj->GetCraftRequestList().front().GetCraftInfo().GetOutput().GetLevel();
        //    Assert::AreEqual(work, 1);

        //    CraftSystem::Destroy();
        //}

        // �C�J�_�̃N���t�g
        // �������Ă��q�ɂɊi�[���ꂸ�A���_�̋߂��ɔz�u�����
        TEST_METHOD(TestMethod21)
        {
            auto raftNum1 = (int)Voyage::Get()->GetRaftList().size();

            StorehouseManager* storehouseManager = StorehouseManager::Get();
            Storehouse* storehouse = storehouseManager->GetStorehouse(1);

            for (int i = 0; i < 200; ++i)
            {
                storehouse->AddItem("�ׂ��؂̊�");
                storehouse->AddItem("�c�^");
            }

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("..\\StarmanLibTest\\craftsmanSkill.csv",
                      "..\\StarmanLibTest\\craftsmanQueueEmpty.csv");

            std::string work;
            obj->QueueCraftRequest("�C�J�_", &work);

            obj->UpdateCraftStatus();

            PowereggDateTime* powereggDateTime = PowereggDateTime::GetObj();

            // 1����1���ԁA����i�߂�
            powereggDateTime->IncreaseDateTime(0, 1, 1, 0, 0);

            obj->UpdateCraftStatus();

            auto raftCount = storehouse->CountItem("�C�J�_");

            Assert::AreEqual(0, raftCount);

            auto raftNum2 = (int)Voyage::Get()->GetRaftList().size();

            Assert::AreEqual(1, raftNum2 - raftNum1);

            CraftSystem::Destroy();
        }
    };
}
