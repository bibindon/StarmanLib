#include "Util.h"
#include "HeaderOnlyCsv.hpp"
#include "CaesarCipher.h"

std::vector<std::vector<std::string>> Util::ReadFromCsv(const std::string& filename,
                                                        const bool decrypt)
{
    std::vector<std::vector<std::string>> vss;

    if (decrypt == false)
    {
        vss = csv::Read(filename);
    }
    else
    {
        std::string work = CaesarCipher::DecryptFromFile(filename);
        vss = csv::ReadFromString(work);
    }

    return vss;
}

void Util::WriteToCsv(const std::string& filename,
                      const std::vector<std::vector<std::string>>& vss,
                      const bool encrypt)
{
    if (encrypt == false)
    {
        csv::Write(filename, vss);
    }
    else
    {
        std::stringstream ss;
        for (std::size_t i = 0; i < vss.size(); ++i)
        {
            for (std::size_t j = 0; j < vss.at(i).size(); ++j)
            {
                ss << vss.at(i).at(j);
                if (j != vss.at(i).size() - 1)
                {
                    ss << ",";
                }
            }
            ss << "\n";
        }
        CaesarCipher::EncryptToFile(ss.str(), filename);
    }
}
