#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/StatusManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StarmanLibTest
{

    TEST_CLASS(StatusManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            StatusManager* obj = StatusManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
        }
    };
}
