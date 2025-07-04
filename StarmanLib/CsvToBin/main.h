#pragma once

#include <iostream>
#include <fstream>
#include "../StarmanLib/MapObjManager.h"
#include "../StarmanLib/EnemyInfoManager.h"
#include "../StarmanLib/HeaderOnlyCsv.hpp"
#include <tchar.h>

void WriteBinaryFromMapObj(const std::wstring& csvFile);

void WriteBinaryFromEnemy(const std::wstring& csvFile);

