#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/SkillManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(SkillManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            SkillManager* obj = SkillManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            SkillManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            SkillManager* obj = SkillManager::GetObj();
            obj->Init("skill.csv", "skillSub.csv");
            Assert::AreEqual(obj != nullptr, true);
            SkillManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            SkillManager* obj = SkillManager::GetObj();
            obj->Init("skill.csv", "skillSub.csv");

            int level = 0;

            level = obj->GetSkillLevel("���̖��@");
            Assert::AreEqual(level, 1);

            level = obj->GetSkillLevel("�X�̖��@");
            Assert::AreEqual(level, 2);

            level = obj->GetSkillLevel("�ł̖��@");
            Assert::AreEqual(level, 3);

            SkillManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            SkillManager* obj = SkillManager::GetObj();
            obj->Init("skill.csv", "skillSub.csv");

            std::string temp;

            temp = obj->GetDetail("���̖��@");
            Assert::AreEqual(temp.find("�������Ă��܂�") != std::string::npos, true);

            SkillManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            SkillManager* obj = SkillManager::GetObj();
            obj->Init("skill.csv", "skillSub.csv");

            float temp = obj->GetDamage("���̖��@", 5);
            Assert::AreEqual(temp, 60.f);

            SkillManager::Destroy();
        }

        TEST_METHOD(TestMethod06)
        {
            SkillManager* obj = SkillManager::GetObj();
            obj->Init("skill.csv", "skillSub.csv");

            float temp = obj->GetRange("�ł̖��@", 5);
            Assert::AreEqual(temp, 60.f);

            SkillManager::Destroy();
        }

        TEST_METHOD(TestMethod07)
        {
            {
                SkillManager* obj = SkillManager::GetObj();
                obj->Init("skill.csv", "skillSub.csv");

                obj->SetSkillLevel("�ł̖��@", 5);
                obj->Save("skillSubSave.csv");

                SkillManager::Destroy();
            }
            {
                SkillManager* obj = SkillManager::GetObj();
                obj->Init("skill.csv", "skillSubSave.csv");

                int level = obj->GetSkillLevel("�ł̖��@");
                Assert::AreEqual(level, 5);

                SkillManager::Destroy();
            }
        }
    };
}
