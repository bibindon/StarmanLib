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
            std::string text = obj->GetText("�X�e�[�^�X", "�X�e�[�^�X�ɂ���");
            Assert::AreEqual(text.size() != 0, true);
            std::string text2 = "\"���̃Q�[���ɂ͈ȉ��̂P�O�̃X�e�[�^�X�����݂���B\n\n";
            text2 += "�u�X�^�~�i�v�A�u�]�̃X�^�~�i�v�A�u�u���́v\n";
            text2 += "�u�����v�A�u�g�̂̔�J�E�����v\n";
            text2 += "�u�����v�A�u�^���p�N���v�A�u�����v�A�u�r�^�~���v�A�u�~�l�����v\"";
            Assert::AreEqual(text == text2, true);
            Assert::AreEqual(text.size() == text2.size(), true);
        }
        TEST_METHOD(TestMethod04)
        {
            {
                Guide* obj = Guide::GetObj();
                obj->Init("guideOrigin.csv");
                obj->SetVisible("�X�e�[�^�X", "�u�]�̃X�^�~�i�v�ɂ���");
                obj->Save("guideSave.csv");
                Guide::Destroy();
            }
            {
                Guide* obj = Guide::GetObj();
                obj->Init("guideSave.csv");
                bool result = obj->GetVisible("�X�e�[�^�X", "�u�]�̃X�^�~�i�v�ɂ���");
                Assert::AreEqual(result, true);
            }
        }
    };
}
