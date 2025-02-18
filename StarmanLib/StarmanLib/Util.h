#pragma once

#include <string>
#include <vector>

class Util
{
public:
    static std::vector<std::vector<std::string>>
        ReadFromCsv(const std::string& filename, const bool decrypt);

    static void WriteToCsv(const std::string& filename,
                           const std::vector<std::vector<std::string>>& vvs,
                           const bool encrypt);

    static std::vector<std::string> split(const std::string& s, char delim = ':');

    template <typename T>
    static void EraseRemove(std::vector<T>& vec, const T& value)
    {
        vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());
    }

    template <typename T, typename Predicate>
    static void EraseRemoveIf(std::vector<T>& vec, Predicate pred)
    {
        vec.erase(std::remove_if(vec.begin(), vec.end(), pred), vec.end());
    }
};

