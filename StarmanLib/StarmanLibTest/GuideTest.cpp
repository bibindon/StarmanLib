#include "CppUnitTest.h"
#include "../StarmanLib/Guide.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

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
            obj->Init("..\\StarmanLibTest\\guideOrigin.csv");
            Assert::AreEqual((int)obj->GetCategoryList().size() != 0, true);
        }
        TEST_METHOD(TestMethod03)
        {
            Guide* obj = Guide::GetObj();
            obj->Init("..\\StarmanLibTest\\guideOrigin.csv");
            std::string text = obj->GetText("ステータス", "ステータスについて");
            Assert::AreEqual(text.size() != 0, true);
            std::string text2 = "\"このゲームには以下の１０のステータスが存在する。\n\n";
            text2 += "「スタミナ」、「脳のスタミナ」、「瞬発力」\n";
            text2 += "「水分」、「身体の疲労・損傷」\n";
            text2 += "「糖質」、「タンパク質」、「脂質」、「ビタミン」、「ミネラル」\"";
            Assert::AreEqual(text.find("「ミネラル」") != std::string::npos, true);
            Assert::AreEqual(text.empty() == false, true);
        }
        TEST_METHOD(TestMethod04)
        {
            {
                Guide* obj = Guide::GetObj();
                obj->Init("..\\StarmanLibTest\\guideOrigin.csv");
                obj->SetVisible("ステータス", "「脳のスタミナ」について");
                obj->Save("..\\StarmanLibTest\\guideSave.csv");
                Guide::Destroy();
            }
            {
                Guide* obj = Guide::GetObj();
                obj->Init("..\\StarmanLibTest\\guideSave.csv");
                bool result = obj->GetVisible("ステータス", "「脳のスタミナ」について");
                Assert::AreEqual(result, true);
            }
        }
    };
}
