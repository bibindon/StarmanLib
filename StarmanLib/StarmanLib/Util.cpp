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
