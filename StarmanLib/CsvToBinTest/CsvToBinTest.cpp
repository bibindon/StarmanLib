﻿#include "pch.h"
#include "CppUnitTest.h"
#include "../CsvToBin/main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CsvToBinTest
{
    TEST_CLASS(CsvToBinTest)
    {
    public:
        
        TEST_METHOD(TestMethod1)
        {
            WriteBinary(_T("..\\CsvToBinTest\\map_obj.csv"));

            BOOL result = PathFileExists(_T("..\\CsvToBinTest\\map_obj.bin"));
            Assert::AreEqual(TRUE, result);
        }
    };
}
