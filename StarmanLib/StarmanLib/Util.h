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

    static bool HitByBoundingBox(const float x1, const float y1, const float z1,
                                 const float x2, const float y2, const float z2,
                                 const float length);

    static bool HitByBoundingBoxWithoutY(const float x1, const float z1,
                                         const float x2, const float z2,
                                         const float length);

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

