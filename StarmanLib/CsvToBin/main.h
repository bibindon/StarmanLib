#pragma once

#include <iostream>
#include <fstream>
#include "../StarmanLib/MapObjManager.h"
#include "../StarmanLib/HeaderOnlyCsv.hpp"
#include <tchar.h>

static void WriteBinary(const std::wstring& csvFile)
{
    auto vvs = csv::Read(csvFile);

    std::vector<NSStarmanLib::stMapObj> stMapObjList;
    for (std::size_t i = 1; i < vvs.size(); ++i)
    {
        NSStarmanLib::stMapObj work;
        float work_f = 0.f;

        work.m_id = std::stoi(vvs.at(i).at(0));

        work.m_modelId = std::stoi(vvs.at(i).at(1));

        work_f = std::stof(vvs.at(i).at(2));
        work.m_x = work_f;
        work.m_frameX = (int)work_f/100;

        work.m_y = std::stof(vvs.at(i).at(3));

        work_f = std::stof(vvs.at(i).at(4));
        work.m_z = work_f;
        work.m_frameZ = (int)work_f/100;

        work.m_yRot = std::stof(vvs.at(i).at(5));

        work.m_scale = std::stof(vvs.at(i).at(6));

        if (vvs.at(i).at(7) == _T("y"))
        {
            work.m_visible = true;
        }
        else
        {
            work.m_visible = false;
        }
        stMapObjList.emplace_back(work);
    }

    std::wstring binFile = csvFile;
    binFile.replace(binFile.size() - 4, 4, _T(".bin"));

    std::wofstream outFile(binFile, std::ios::binary);
    if (outFile.is_open())
    {
        size_t size = stMapObjList.size();

        // ベクターサイズを書き込む
        outFile.write(reinterpret_cast<const wchar_t*>(&size), sizeof(size));

        // データ本体を書き込む
        outFile.write(reinterpret_cast<const wchar_t*>(stMapObjList.data()),
                      static_cast<std::streamsize>(size) * sizeof(NSStarmanLib::stMapObj));

        outFile.close();
    }
    else
    {
        throw std::exception();
    }
}
