﻿#include "CppUnitTest.h"
#include "../StarmanLib/EnemyInfoManager.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <tchar.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NSStarmanLib;

namespace StarmanLibTest
{

    TEST_CLASS(EnemyManagerTest)
    {
    public:

        TEST_METHOD(TestMethod01)
        {
            EnemyInfoManager* obj = EnemyInfoManager::GetObj();
            Assert::AreEqual(obj != nullptr, true);
            EnemyInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod02)
        {
            EnemyInfoManager* obj = EnemyInfoManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\enemyDef.csv"),
                      _T("..\\StarmanLibTest\\enemyOrigin.csv"),
                      _T("..\\StarmanLibTest\\enemyVisible.csv"));

            Assert::AreEqual(obj != nullptr, true);
            EnemyInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod03)
        {
            EnemyInfoManager* obj = EnemyInfoManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\enemyDef.csv"),
                      _T("..\\StarmanLibTest\\enemyOrigin.csv"),
                      _T("..\\StarmanLibTest\\enemyVisible.csv"));
            std::vector<stEnemyInfo> enemyInfoList = obj->GetEnemyInfo(10.f, 0.f, 10.f, 1.f);
            Assert::AreEqual((int)enemyInfoList.size() == 1, true);
            EnemyInfoManager::Destroy();
        }

        // テストしたいこと
        // 座標と範囲を指定して敵の情報が取得できること
        TEST_METHOD(TestMethod04)
        {
            EnemyInfoManager* obj = EnemyInfoManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\enemyDef.csv"),
                      _T("..\\StarmanLibTest\\enemyOrigin.csv"),
                      _T("..\\StarmanLibTest\\enemyVisible.csv"));
            std::vector<stEnemyInfo> enemyInfoList = obj->GetEnemyInfo(5.f, 5.f, 5.f, 6.f);
            Assert::AreEqual(1, (int)enemyInfoList.size());
            Assert::AreEqual(enemyInfoList.at(0).m_SerialNumber == 1, true);
            Assert::AreEqual(enemyInfoList.at(0).m_id == _T("cube"), true);
            Assert::AreEqual(enemyInfoList.at(0).m_name == _T("リッポウタイ"), true);
            Assert::AreEqual(enemyInfoList.at(0).m_x, 10.f);
            Assert::AreEqual(enemyInfoList.at(0).m_bDefeated, true);
            EnemyInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod05)
        {
            EnemyInfoManager* obj = EnemyInfoManager::GetObj();
            obj->Init(_T("..\\StarmanLibTest\\enemyDef.csv"),
                      _T("..\\StarmanLibTest\\enemyOrigin.csv"),
                      _T("..\\StarmanLibTest\\enemyVisible.csv"));
            std::vector<stEnemyInfo> enemyInfoList = obj->GetEnemyInfo(96.f, 0.f, 97.f, 2.f);
            Assert::AreEqual((int)enemyInfoList.size() == 1, true);
            Assert::AreEqual(enemyInfoList.at(0).m_SerialNumber == 30, true);
            Assert::AreEqual(enemyInfoList.at(0).m_id == _T("cube"), true);
            Assert::AreEqual(enemyInfoList.at(0).m_name == _T("リッポウタイ"), true);
            Assert::AreEqual(enemyInfoList.at(0).m_x, 97.f);
            Assert::AreEqual(enemyInfoList.at(0).m_bDefeated, false);
            EnemyInfoManager::Destroy();
        }

        TEST_METHOD(TestMethod06)
        {
            {
                EnemyInfoManager* obj = EnemyInfoManager::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\enemyDef.csv"),
                          _T("..\\StarmanLibTest\\enemyOrigin.csv"),
                          _T("..\\StarmanLibTest\\enemyVisible.csv"));
                stEnemyInfo enemyInfo;
                enemyInfo.m_x = 111.f;
                enemyInfo.m_y = 222.f;
                enemyInfo.m_z = 333.f;
                enemyInfo.m_HP = 444;
                enemyInfo.m_bDefeated = true;
                obj->UpdateEnemyInfo(5, enemyInfo);
                obj->Save(_T("..\\StarmanLibTest\\enemySave.csv"),
                          _T("..\\StarmanLibTest\\enemyVisibleSave.csv"));
                EnemyInfoManager::Destroy();
            }
        }

        TEST_METHOD(TestMethod07)
        {
            {
                EnemyInfoManager* obj = EnemyInfoManager::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\enemyDef.csv"),
                          _T("..\\StarmanLibTest\\enemyOrigin.csv"),
                          _T("..\\StarmanLibTest\\enemyVisible.csv"));
                stEnemyInfo enemyInfo;
                enemyInfo.m_SerialNumber = 20;
                enemyInfo.m_id = _T("enban");
                enemyInfo.m_name = _T("エンバン");
                enemyInfo.m_x = 111.f;
                enemyInfo.m_y = 222.f;
                enemyInfo.m_z = 333.f;
                enemyInfo.m_HP = 444;
                enemyInfo.m_bDefeated = true;
                obj->UpdateEnemyInfo(20, enemyInfo);
                obj->SetEnemyVisible(_T("enban"), true);
                obj->Save(_T("..\\StarmanLibTest\\enemySave.csv"),
                          _T("..\\StarmanLibTest\\enemyVisibleSave.csv"));
                EnemyInfoManager::Destroy();
            }
            {
                EnemyInfoManager* obj = EnemyInfoManager::GetObj();
                obj->Init(_T("..\\StarmanLibTest\\enemyDef.csv"),
                          _T("..\\StarmanLibTest\\enemySave.csv"),
                          _T("..\\StarmanLibTest\\enemyVisibleSave.csv"));
                std::vector<stEnemyInfo> enemyInfoList = obj->GetEnemyInfo(111.f, 222.f, 333.f, 1.f);
                Assert::AreEqual(true, (int)enemyInfoList.size() == 1);
                Assert::AreEqual(true, enemyInfoList.at(0).m_SerialNumber == 20);
                Assert::AreEqual(true, enemyInfoList.at(0).m_id == L"enban");
                Assert::AreEqual(true, enemyInfoList.at(0).m_name == _T("エンバン"));
                Assert::AreEqual(444, enemyInfoList.at(0).m_HP);
                Assert::AreEqual(true, enemyInfoList.at(0).m_bDefeated);

                bool work = obj->GetEnemyDef(_T("enban")).GetVisible();
                Assert::AreEqual(true, work);
                EnemyInfoManager::Destroy();
            }
        }
    };
}
