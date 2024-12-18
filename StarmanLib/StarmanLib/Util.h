#pragma once

#include <string>
#include <vector>

class Util
{
public:
    static std::vector<std::vector<std::string>>
        ReadFromCsv(const std::string& filename, const bool decrypt);

    static void WriteToCsv(const std::string& filename,
                           const std::vector<std::vector<std::string>>& vss,
                           const bool encrypt);
};

