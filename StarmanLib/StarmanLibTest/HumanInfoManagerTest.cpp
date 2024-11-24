#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/HumanInfoManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(HumanInfoManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            HumanInfoManager* obj = HumanInfoManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            HumanInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            HumanInfoManager* obj = HumanInfoManager::GetObj();
            obj->Init("humanInfo.csv", "humanInfoSub.csv");
            HumanInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            HumanInfoManager* obj = HumanInfoManager::GetObj();
            obj->Init("humanInfo.csv", "humanInfoSub.csv");
            std::vector<std::string> vs = obj->GetHumanNameList();
            Assert::AreEqual((int)vs.size(), 12);
            HumanInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            HumanInfoManager* obj = HumanInfoManager::GetObj();
            obj->Init("humanInfo.csv", "humanInfoSub.csv");
            std::vector<std::string> vs = obj->GetHumanNameList();
            HumanInfo humanInfo = obj->GetHumanInfo(vs.at(0));
            Assert::AreEqual(humanInfo.GetName() == "�z�V�}��", true);
            bool find = (humanInfo.GetDetail().find("�P�V�O����") != std::string::npos);
            Assert::AreEqual(find, true);
            Assert::AreEqual(humanInfo.GetImagePath() == "human_hoshiman.png", true);
            HumanInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            HumanInfoManager* obj = HumanInfoManager::GetObj();
            obj->Init("humanInfo.csv", "humanInfoSub.csv");
            std::vector<std::string> vs = obj->GetHumanNameList();
            HumanInfo humanInfo = obj->GetHumanInfo(vs.at(11));
            Assert::AreEqual(humanInfo.GetName() == "�q�V�K�^�}��", true);
            bool find = (humanInfo.GetDetail().find("���܂������Ȃ�") != std::string::npos);
            Assert::AreEqual(find, true);
            Assert::AreEqual(humanInfo.GetImagePath() == "human_xxx.png", true);
            HumanInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod06)
        {
            {
                HumanInfoManager* obj = HumanInfoManager::GetObj();
                obj->Init("humanInfo.csv", "humanInfoSub.csv");
                HumanInfo humanInfo = obj->GetHumanInfo("�m�[�u��");
                Assert::AreEqual(humanInfo.GetVisible(), false);
                obj->SetHumanVisible("�m�[�u��");
                humanInfo = obj->GetHumanInfo("�m�[�u��");
                Assert::AreEqual(humanInfo.GetVisible(), true);
                obj->Save("humanInfoSubSave.csv");
                HumanInfoManager::Destroy();
            }
            {
                HumanInfoManager* obj = HumanInfoManager::GetObj();
                obj->Init("humanInfo.csv", "humanInfoSubSave.csv");
                HumanInfo humanInfo = obj->GetHumanInfo("�m�[�u��");
                Assert::AreEqual(humanInfo.GetVisible(), true);
                HumanInfoManager::Destroy();
            }
        }
    };
}
