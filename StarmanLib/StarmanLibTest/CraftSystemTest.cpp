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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

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
            {
                ItemManager* itemManager = ItemManager::GetObj();
                itemManager->Init("item.csv");

                Inventory* inventory = Inventory::GetObj();
                inventory->Init("inventory.csv");

                Storehouse* storehouse = Storehouse::GetObj();
                storehouse->Init("storehouse.csv");

                CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
                craftInfoManager->Init("craftDef.csv");
            }

            CraftSystem* obj = CraftSystem::GetObj();
            obj->Init("craftsmanSkill.csv", "craftsmanQueue.csv");
            obj->QueueCraftRequest("�C�J�_");

            CraftSystem::Destroy();
        }
        // TODO �L���[�C���O���ăX�^�[�g
        // TODO �L���[�C���O���ăX�^�[�g���đf�ނ��Ȃ��Ȃ�
        // TODO �L���[�C���O���ăX�^�[�g���Ċ�������
        // TODO �L���[�C���O���ăX�^�[�g���Ċ������đq�ɂɊ����i�������
        // TODO �����L���[�C���O���ăX�^�[�g���Ċ������đq�ɂɊ����i�������
        // TODO �i���x���擾�ł���
        // TODO �ۑ��ł���
        // TODO �L���[�C���O���ăL�����Z��
        // TODO �����L���[�C���O���ăL�����Z��

    };
}
