#include "CppUnitTest.h"
#include "../StarmanLib/Help.h"
#include "../StarmanLib/PowereggDateTime.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(HelpTest)
    {
    public:

        // public�֐����ĂԂ����̃e�X�g
        TEST_METHOD(TestMethod01)
        {
            auto help = Help::Get();

            // Target
            Assert::IsNotNull(help);

            Help::Destroy();
        }

        // public�֐����ĂԂ����̃e�X�g
        TEST_METHOD(TestMethod02)
        {
            auto help = Help::Get();
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");

            // Target
            help->Init("..\\StarmanLibTest\\help.csv");

            ItemManager::Destroy();
            Help::Destroy();
        }

        // public�֐����ĂԂ����̃e�X�g
        TEST_METHOD(TestMethod03)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");

            // Target
            help->Save("..\\StarmanLibTest\\helpSave.csv");

            ItemManager::Destroy();
            Help::Destroy();
        }

        // public�֐����ĂԂ����̃e�X�g
        TEST_METHOD(TestMethod04)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");

            // Target
            help->Update();

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // public�֐����ĂԂ����̃e�X�g
        TEST_METHOD(TestMethod05)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");

            // Target
            auto receiveItems = help->ReceiveItems("�T���J�N�}��");

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // �A�C�e�����󂯎��邩�̃e�X�g
        TEST_METHOD(TestMethod06)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems = help->ReceiveItems("�T���J�N�}��");

            // Target
            Assert::AreEqual<size_t>(3, receiveItems.size());
            Assert::AreEqual(3, receiveItems.at(0).GetId());
            Assert::AreEqual(5, receiveItems.at(1).GetId());
            Assert::AreEqual(6, receiveItems.at(2).GetId());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // �A�C�e�����󂯎��邩�̃e�X�g
        TEST_METHOD(TestMethod07)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems = help->ReceiveItems("�V�J�N�}��");

            // Target
            Assert::AreEqual<size_t>(0, receiveItems.size());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // 16�����߂�����X�V����邱�Ƃ��m�F����e�X�g
        TEST_METHOD(TestMethod08)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems1 = help->ReceiveItems("�T���J�N�}��");
            auto receiveItems2 = help->ReceiveItems("�V�J�N�}��");
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems("�T���J�N�}��");
            auto receiveItems4 = help->ReceiveItems("�V�J�N�}��");

            // Target
            Assert::AreEqual(false,
                             receiveItems1.size() == receiveItems3.size() &&
                             receiveItems2.size() == receiveItems4.size() &&
                             receiveItems1.at(0).GetId() == receiveItems3.at(0).GetId() &&
                             receiveItems1.at(1).GetId() == receiveItems3.at(1).GetId() &&
                             receiveItems1.at(2).GetId() == receiveItems3.at(2).GetId());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // �擾�������ɂȂ��Ă��邱��
        TEST_METHOD(TestMethod09)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems1 = help->ReceiveItems("�T���J�N�}��");
            auto receiveItems2 = help->ReceiveItems("�V�J�N�}��");
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems("�T���J�N�}��");
            auto receiveItems4 = help->ReceiveItems("�V�J�N�}��");

            receiveItems3 = help->ReceiveItems("�T���J�N�}��");
            receiveItems4 = help->ReceiveItems("�V�J�N�}��");

            // Target
            Assert::AreEqual(true, receiveItems3.empty());
            Assert::AreEqual(true, receiveItems4.empty());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // �擾�������ɂȂ�A���̌�A16�����ׂ��܂ł͎󂯎��Ȃ����ƁB
        TEST_METHOD(TestMethod10)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems1 = help->ReceiveItems("�T���J�N�}��");
            auto receiveItems2 = help->ReceiveItems("�V�J�N�}��");
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems("�T���J�N�}��");
            auto receiveItems4 = help->ReceiveItems("�V�J�N�}��");

            datetime->IncreaseDateTime(0, 0, 1, 0, 0);
            help->Update();

            receiveItems3 = help->ReceiveItems("�T���J�N�}��");
            receiveItems4 = help->ReceiveItems("�V�J�N�}��");

            // Target
            Assert::AreEqual(true, receiveItems3.empty());
            Assert::AreEqual(true, receiveItems4.empty());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }

        // 16�����ׂ�����A�C�e������[����A������x16�����ׂ����������x�A�C�e������[����邱�ƁB
        TEST_METHOD(TestMethod11)
        {
            ItemManager* obj = ItemManager::GetObj();
            obj->Init("..\\StarmanLibTest\\item.csv", "..\\StarmanLibTest\\item_pos.csv");
            auto help = Help::Get();
            help->Init("..\\StarmanLibTest\\help.csv");
            auto datetime = PowereggDateTime::GetObj();
            datetime->Init("..\\StarmanLibTest\\datetime.csv");
            auto receiveItems1 = help->ReceiveItems("�T���J�N�}��");
            auto receiveItems2 = help->ReceiveItems("�V�J�N�}��");
            datetime->IncreaseDateTime(0, 1, 0, 0, 0);

            help->Update();

            auto receiveItems3 = help->ReceiveItems("�T���J�N�}��");
            auto receiveItems4 = help->ReceiveItems("�V�J�N�}��");

            datetime->IncreaseDateTime(0, 1, 0, 0, 0);
            help->Update();

            receiveItems3 = help->ReceiveItems("�T���J�N�}��");
            receiveItems4 = help->ReceiveItems("�V�J�N�}��");

            datetime->IncreaseDateTime(0, 1, 0, 0, 0);
            help->Update();

            receiveItems3 = help->ReceiveItems("�T���J�N�}��");
            receiveItems4 = help->ReceiveItems("�V�J�N�}��");

            // Target
            Assert::AreEqual(false, receiveItems3.empty());
            Assert::AreEqual(false, receiveItems4.empty());

            ItemManager::Destroy();
            PowereggDateTime::Destroy();
            Help::Destroy();
        }
    };
}
