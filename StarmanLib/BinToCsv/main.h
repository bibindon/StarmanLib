#pragma once

#include <iostream>
#include <fstream>
#include "../StarmanLib/MapObjManager.h"
#include "../StarmanLib/HeaderOnlyCsv.hpp"

static void WriteCsv(const std::string& binFile)
{
    std::vector<NSStarmanLib::stMapObj> stMapObjList;

    std::ifstream inFile(binFile, std::ios::binary);
    if (inFile.is_open() == false)
    {
        throw std::exception();
    }

    size_t size = 0;

    // ベクターサイズを読み込む
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));

    // ベクターサイズを設定
    stMapObjList.resize(size);

    // データ本体を読み込む
    inFile.read(reinterpret_cast<char*>(stMapObjList.data()),
                static_cast<std::streamsize>(size) * sizeof(NSStarmanLib::stMapObj));

    inFile.close();

    std::vector<std::vector<std::string>> vvs;
    std::vector<std::string> vs;

    vs.push_back("ID");
    vs.push_back("モデルID");
    vs.push_back("X");
    vs.push_back("Y");
    vs.push_back("Z");
    vs.push_back("RotY");
    vs.push_back("Scale");
    vs.push_back("表示");
    vvs.push_back(vs);

    for (const auto& item : stMapObjList)
    {
        vs.clear();
        vs.push_back(std::to_string(item.m_id));
        vs.push_back(std::to_string(item.m_modelId));
        vs.push_back(std::to_string((int)item.m_x));
        vs.push_back(std::to_string((int)item.m_y));
        vs.push_back(std::to_string((int)item.m_z));
        vs.push_back(std::to_string(item.m_yRot));
        vs.push_back(std::to_string(item.m_scale));

        if (item.m_visible)
        {
            vs.push_back("y");
        }
        else
        {
            vs.push_back("n");
        }

        vvs.push_back(vs);
    }

    std::string csvFile = binFile;
    csvFile.replace(csvFile.size() - 4, 4, ".csv");

    csv::Write(csvFile, vvs);
}
