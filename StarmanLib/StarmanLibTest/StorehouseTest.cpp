#include "CppUnitTest.h"
#include "../StarmanLib/Inventory.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include "../StarmanLib/Storehouse.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

TEST_CLASS(StorehouseTest)
{
public:

    TEST_METHOD(TestMethod01)
    {
        auto storehouse = StorehouseManager::Get();

        bool bException = false;
        try
        {
            storehouse->Init("no-exist-file.csv");
        }
        catch (const std::exception&)
        {
            bException = true;
        }
        Assert::AreEqual(true, bException);
    }
};
}
