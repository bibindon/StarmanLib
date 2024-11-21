#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/Guide.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StarmanLibTest
{

    TEST_CLASS(GuideTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            Guide* obj = Guide::GetObj();
            Assert::AreEqual(obj != nullptr, true);
        }
        TEST_METHOD(TestMethod02)
        {
            Guide* obj = Guide::GetObj();
            obj->Init("guideOrigin.csv");
            Assert::AreEqual((int)obj->GetCategoryList().size() != 0, true);
        }
        TEST_METHOD(TestMethod03)
        {
            Guide* obj = Guide::GetObj();
            obj->Init("guideOrigin.csv");
            std::string text = obj->GetText("ステータス", "ステータスについて");
            Assert::AreEqual(text.size() != 0, true);
            std::string text2 = "\"このゲームには以下の１０のステータスが存在する。\n\n";
            text2 += "「スタミナ」、「脳のスタミナ」、「瞬発力」\n";
            text2 += "「水分」、「身体の疲労・損傷」\n";
            text2 += "「糖質」、「タンパク質」、「脂質」、「ビタミン」、「ミネラル」\"";
            Assert::AreEqual(text == text2, true);
            Assert::AreEqual(text.size() == text2.size(), true);
        }
        TEST_METHOD(TestMethod04)
        {
            {
                Guide* obj = Guide::GetObj();
                obj->Init("guideOrigin.csv");
                obj->SetVisible("ステータス", "「脳のスタミナ」について");
                obj->Save("guideSave.csv");
                Guide::Destroy();
            }
            {
                Guide* obj = Guide::GetObj();
                obj->Init("guideSave.csv");
                bool result = obj->GetVisible("ステータス", "「脳のスタミナ」について");
                Assert::AreEqual(result, true);
            }
        }
    };
}
