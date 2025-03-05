#pragma once

#include <string>

namespace NSStarmanLib
{

enum class eBaseType
{
    Precision = 0,
    DirectNex,
};

// 活動拠点情報
// 
// Configというクラス名にして、活動拠点以外の様々な設定値を扱えるようにするかもしれない。
class ActivityBase
{
public:

    static ActivityBase* Get();

    void Init(const std::string& csvFile);
    void Save(const std::string& csvFile);
    void SetBaseType(const eBaseType arg);
    eBaseType GetBaseType() const;
    void Finalize();

private:

    ActivityBase();

    static ActivityBase* m_obj;

    eBaseType m_eBaseType = eBaseType::Precision;

};
}

