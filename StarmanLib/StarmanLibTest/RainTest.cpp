#include "CppUnitTest.h"
#include "../StarmanLib/RainModel.h"

#include "../StarmanLib/PowereggDateTime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(RainTest)
    {
    public:

        // �P����Public�֐����Ă�ŗ����Ȃ����Ƃ��m�F����e�X�g
        TEST_METHOD(TestMethod01)
        {
            // Target
            RainModel* obj = RainModel::Get();

            Assert::AreEqual(true, obj != nullptr);
            obj->Destroy();
        }

        // �P����Public�֐����Ă�ŗ����Ȃ����Ƃ��m�F����e�X�g
        TEST_METHOD(TestMethod02)
        {
            RainModel* obj = RainModel::Get();

            // Target
            obj->Update();

            obj->Destroy();
        }

        // �P����Public�֐����Ă�ŗ����Ȃ����Ƃ��m�F����e�X�g
        TEST_METHOD(TestMethod03)
        {
            RainModel* obj = RainModel::Get();
            obj->Update();

            // Target
            obj->IsRain();

            obj->Destroy();
        }

        // �P����Public�֐����Ă�ŗ����Ȃ����Ƃ��m�F����e�X�g
        TEST_METHOD(TestMethod04)
        {
            RainModel* obj = RainModel::Get();

            // Target
            obj->Destroy();
        }

        // ����Ă���Ƃ��A1���Ԍ�ɉJ���~�邩�A��10000��m�F����
        // �J���~��m����1�����x�ł��邱�Ƃ��m�F����
        TEST_METHOD(TestMethod05)
        {
            auto datetime = PowereggDateTime::GetObj();
            RainModel* obj = RainModel::Get();

            // ���s��
            int tryCount = 0;

            // �J���~������
            int rainStartCount = 0;

            for (int i = 0; i < 10000; ++i)
            {
                bool isRain1 = obj->IsRain();

                // ���ꂾ������J���~�邩�m�F����`�����X
                if (!isRain1)
                {
                    ++tryCount;
                }

                datetime->IncreaseDateTime(0, 0, 1, 0, 0);
                obj->Update();

                bool isRain2 = obj->IsRain();

                if (!isRain1 && isRain2)
                {
                    rainStartCount++;
                }
            }

            double rainRate = (double)rainStartCount / tryCount;
            Assert::AreEqual(true, rainRate <= 0.05);
            Assert::AreEqual(true, rainRate != 0.0);

            obj->Destroy();
            datetime->Destroy();
        }
    };
}
