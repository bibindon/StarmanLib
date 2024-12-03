#include "pch.h"
#include "CppUnitTest.h"
#include "../StarmanLib/EnemyManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(EnemyManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            EnemyManager* obj = EnemyManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            EnemyManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            EnemyManager* obj = EnemyManager::GetObj();
            obj->Init("..\\StarmanLibTest\\enemyDef.csv",
                      "..\\StarmanLibTest\\enemyOrigin.csv",
                      "..\\StarmanLibTest\\enemyVisible.csv");

            Assert::AreEqual(obj != nullptr, true);
            EnemyManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            EnemyManager* obj = EnemyManager::GetObj();
            obj->Init("..\\StarmanLibTest\\enemyDef.csv",
                      "..\\StarmanLibTest\\enemyOrigin.csv",
                      "..\\StarmanLibTest\\enemyVisible.csv");
            std::vector<EnemyInfo> enemyInfoList = obj->GetEnemyInfo(10.f, 0.f, 10.f, 1.f);
            Assert::AreEqual((int)enemyInfoList.size() == 1, true);
            EnemyManager::Destroy();
        }

        TEST_METHOD(TestMethod04)
        {
            EnemyManager* obj = EnemyManager::GetObj();
            obj->Init("..\\StarmanLibTest\\enemyDef.csv",
                      "..\\StarmanLibTest\\enemyOrigin.csv",
                      "..\\StarmanLibTest\\enemyVisible.csv");
            std::vector<EnemyInfo> enemyInfoList = obj->GetEnemyInfo(5.f, 5.f, 5.f, 10.f);
            Assert::AreEqual((int)enemyInfoList.size() == 1, true);
            Assert::AreEqual(enemyInfoList.at(0).GetID() == 1, true);
            Assert::AreEqual(enemyInfoList.at(0).GetBreed() == "リッポウタイ", true);
            Assert::AreEqual(enemyInfoList.at(0).GetX(), 10.f);
            Assert::AreEqual(enemyInfoList.at(0).GetDefeated(), true);
            EnemyManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            EnemyManager* obj = EnemyManager::GetObj();
            obj->Init("..\\StarmanLibTest\\enemyDef.csv",
                      "..\\StarmanLibTest\\enemyOrigin.csv",
                      "..\\StarmanLibTest\\enemyVisible.csv");
            std::vector<EnemyInfo> enemyInfoList = obj->GetEnemyInfo(96.f, 0.f, 97.f, 2.f);
            Assert::AreEqual((int)enemyInfoList.size() == 1, true);
            Assert::AreEqual(enemyInfoList.at(0).GetID() == 30, true);
            Assert::AreEqual(enemyInfoList.at(0).GetBreed() == "リッポウタイ", true);
            Assert::AreEqual(enemyInfoList.at(0).GetX(), 97.f);
            Assert::AreEqual(enemyInfoList.at(0).GetDefeated(), false);
            EnemyManager::Destroy();
        }

        TEST_METHOD(TestMethod06)
        {
            {
                EnemyManager* obj = EnemyManager::GetObj();
                obj->Init("..\\StarmanLibTest\\enemyDef.csv",
                          "..\\StarmanLibTest\\enemyOrigin.csv",
                          "..\\StarmanLibTest\\enemyVisible.csv");
                EnemyInfo enemyInfo;
                enemyInfo.SetX(111.f);
                enemyInfo.SetY(222.f);
                enemyInfo.SetZ(333.f);
                enemyInfo.SetHP(444);
                enemyInfo.SetDefeated(true);
                obj->UpdateEnemyInfo(5, enemyInfo);
                obj->Save("..\\StarmanLibTest\\enemySave.csv",
                          "..\\StarmanLibTest\\enemyVisibleSave.csv");
                EnemyManager::Destroy();
            }
        }

        TEST_METHOD(TestMethod07)
        {
            {
                EnemyManager* obj = EnemyManager::GetObj();
                obj->Init("..\\StarmanLibTest\\enemyDef.csv",
                          "..\\StarmanLibTest\\enemyOrigin.csv",
                          "..\\StarmanLibTest\\enemyVisible.csv");
                EnemyInfo enemyInfo;
                enemyInfo.SetID(20);
                enemyInfo.SetBreed("エンバン");
                enemyInfo.SetX(111.f);
                enemyInfo.SetY(222.f);
                enemyInfo.SetZ(333.f);
                enemyInfo.SetHP(444);
                enemyInfo.SetDefeated(true);
                obj->UpdateEnemyInfo(20, enemyInfo);
                obj->SetEnemyVisible("エンバン", true);
                obj->Save("..\\StarmanLibTest\\enemySave.csv",
                          "..\\StarmanLibTest\\enemyVisibleSave.csv");
                EnemyManager::Destroy();
            }
            {
                EnemyManager* obj = EnemyManager::GetObj();
                obj->Init("..\\StarmanLibTest\\enemyDef.csv",
                          "..\\StarmanLibTest\\enemySave.csv",
                          "..\\StarmanLibTest\\enemyVisibleSave.csv");
                std::vector<EnemyInfo> enemyInfoList = obj->GetEnemyInfo(111.f, 222.f, 333.f, 1.f);
                Assert::AreEqual(true, (int)enemyInfoList.size() == 1);
                Assert::AreEqual(true, enemyInfoList.at(0).GetID() == 20);
                Assert::AreEqual(true, enemyInfoList.at(0).GetBreed() == "エンバン");
                Assert::AreEqual(444, enemyInfoList.at(0).GetHP());
                Assert::AreEqual(true, enemyInfoList.at(0).GetDefeated());

                bool work = obj->GetEnemyDef("エンバン").GetVisible();
                Assert::AreEqual(true, work);
                EnemyManager::Destroy();
            }
        }
    };
}
