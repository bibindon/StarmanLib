#pragma once
#include <string>

class CaesarCipher
{
public:
    static std::string Encrypt(const std::string& text)
    {
        std::string result;
        char* work = nullptr;
        work = new char[text.size() + 1];
        strcpy_s(work, text.size() + 1, text.c_str());
        for (std::size_t i = 0; i < text.size(); ++i)
        {
            work[i] = work[i] + 10;
        }
        result = std::string(work);
        delete[] work;
        return result;
    }

    static void EncryptToFile(const std::string& text, const std::string& filename)
    {
        std::string buff;
        {
            char* work = nullptr;
            work = new char[text.size() + 1];
            strcpy_s(work, text.size() + 1, text.c_str());
            for (std::size_t i = 0; i < text.size(); ++i)
            {
                work[i] = work[i] + 10;
            }
            buff = std::string(work);
            delete[] work;
        }

        std::ofstream ofs(filename);
        ofs << buff;
    }

    static std::string Decrypt(const std::string& text)
    {
        std::string result;
        char* work = nullptr;
        work = new char[text.size() + 1];
        strcpy_s(work, text.size() + 1, text.c_str());
        for (std::size_t i = 0; i < text.size(); ++i)
        {
            work[i] = work[i] - 10;
        }
        result = std::string(work);
        delete[] work;
        return result;
    }

    static std::string DecryptFromFile(const std::string& text)
    {
        std::ifstream ifs(text);
        if (!ifs)
        {
            return std::string();
        }
        std::istreambuf_iterator<char> itBegin(ifs);
        std::istreambuf_iterator<char> itEnd;
        std::string work(itBegin, itEnd);

        work = Decrypt(work);
        return work;
    }
};

