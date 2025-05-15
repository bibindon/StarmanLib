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
            obj->Init("..\\StarmanLibTest\\skill.csv", "..\\StarmanLibTest\\skillSub.csv");
            Assert::AreEqual(obj != nullptr, true);
            SkillManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            SkillManager* obj = SkillManager::GetObj();
            obj->Init("..\\StarmanLibTest\\skill.csv", "..\\StarmanLibTest\\skillSub.csv");

            int level = 0;

            level = obj->GetSkillLevel("炎の魔法");
            Assert::AreEqual(level, 1);

            level = obj->GetSkillLevel("氷の魔法");
            Assert::AreEqual(level, 2);

            level = obj->GetSkillLevel("闇の魔法");
            Assert::AreEqual(level, 3);

            SkillManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            SkillManager* obj = SkillManager::GetObj();
            obj->Init("..\\StarmanLibTest\\skill.csv", "..\\StarmanLibTest\\skillSub.csv");

            std::string temp;

            temp = obj->GetDetail("炎の魔法");
            Assert::AreEqual(temp.find("負傷してしまう") != std::string::npos, true);

            SkillManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            SkillManager* obj = SkillManager::GetObj();
            obj->Init("..\\StarmanLibTest\\skill.csv", "..\\StarmanLibTest\\skillSub.csv");

            float temp = obj->GetDamage("炎の魔法", 5);
            Assert::AreEqual(temp, 60.f);

            SkillManager::Destroy();
        }

        TEST_METHOD(TestMethod06)
        {
            SkillManager* obj = SkillManager::GetObj();
            obj->Init("..\\StarmanLibTest\\skill.csv", "..\\StarmanLibTest\\skillSub.csv");

            float temp = obj->GetRange("闇の魔法", 5);
            Assert::AreEqual(temp, 60.f);

            SkillManager::Destroy();
        }

        TEST_METHOD(TestMethod07)
        {
            {
                SkillManager* obj = SkillManager::GetObj();
                obj->Init("..\\StarmanLibTest\\skill.csv", "..\\StarmanLibTest\\skillSub.csv");

                obj->SetSkillLevel("闇の魔法", 5);
                obj->Save("..\\StarmanLibTest\\skillSubSave.csv");

                SkillManager::Destroy();
            }
            {
                SkillManager* obj = SkillManager::GetObj();
                obj->Init("..\\StarmanLibTest\\skill.csv", "..\\StarmanLibTest\\skillSubSave.csv");

                int level = obj->GetSkillLevel("闇の魔法");
                Assert::AreEqual(level, 5);

                SkillManager::Destroy();
            }
        }
    };
}
