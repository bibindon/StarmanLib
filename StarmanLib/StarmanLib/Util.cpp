#include "Util.h"
#include "HeaderOnlyCsv.hpp"
#include "CaesarCipher.h"

std::vector<std::vector<std::string>> Util::ReadFromCsv(const std::string& filename,
                                                        const bool decrypt)
{
    std::vector<std::vector<std::string>> vvs;

    if (decrypt == false)
    {
        vvs = csv::Read(filename);
    }
    else
    {
        std::string work = CaesarCipher::DecryptFromFile(filename);
        vvs = csv::ReadFromString(work);
    }

    return vvs;
}

void Util::WriteToCsv(const std::string& filename,
                      const std::vector<std::vector<std::string>>& vvs,
                      const bool encrypt)
{
    if (encrypt == false)
    {
        csv::Write(filename, vvs);
    }
    else
    {
        std::stringstream ss;
        for (std::size_t i = 0; i < vvs.size(); ++i)
        {
            for (std::size_t j = 0; j < vvs.at(i).size(); ++j)
            {
                ss << vvs.at(i).at(j);
                if (j != vvs.at(i).size() - 1)
                {
                    ss << ",";
                }
            }
            ss << "\n";
        }
        CaesarCipher::EncryptToFile(ss.str(), filename);
    }
}

std::vector<std::string> Util::split(const std::string& s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

bool Util::HitByBoundingBox(const float x1,
                            const float y1,
                            const float z1,
                            const float x2,
                            const float y2,
                            const float z2,
                            const float length)
{
    float work = 0.f;
    work = std::abs(x1 - x2);
    if (work <= length)
    {
        work = std::abs(y1 - y2);
        if (work <= length)
        {
            work = std::abs(z1 - z2);
            if (work <= length)
            {
                return true;
            }
        }
    }
    return false;
}

bool Util::HitByBoundingBoxWithoutY(const float x1,
                                    const float z1,
                                    const float x2,
                                    const float z2,
                                    const float length)
{
    float work = 0.f;
    work = std::abs(x1 - x2);
    if (work <= length)
    {
        work = std::abs(z1 - z2);
        if (work <= length)
        {
            return true;
        }
    }
    return false;
}
