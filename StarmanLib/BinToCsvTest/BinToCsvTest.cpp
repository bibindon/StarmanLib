#include "pch.h"
#include "CppUnitTest.h"
#include "../BinToCsv/main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinToCsvTest
{
    TEST_CLASS(BinToCsvTest)
    {
    public:
        
        TEST_METHOD(TestMethod1)
        {
            WriteCsv("..\\CsvToBinTest\\map_obj2.bin");

            BOOL result = PathFileExists("..\\CsvToBinTest\\map_obj2.bin");
            Assert::AreEqual(TRUE, result);
        }
    };
}
