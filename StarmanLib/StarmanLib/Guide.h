#pragma once
#include <string>
#include <vector>

namespace NSStarmanLib
{
class GuideItem
{
public:
    void SetCategory(const std::string& category);
    std::string GetCategory();

    void SetSubCategory(const std::string& subCategory);
    std::string GetSubCategory();

    void SetText(const std::string& text);
    std::string GetText();

    void SetVisible(const bool visible);
    bool GetVisible();

private:

    // �啪��
    std::string m_category;

    // ������
    std::string m_subCategory;

    // ������
    std::string m_text;

    // �\���ς݂��ۂ�
    bool m_bVisible { false };
};

// �������
class Guide
{
public:

    static Guide* GetObj();
    void Init(const std::string& csvfile,
              const bool decrypt = false);
    static void Destroy();

    std::vector<std::string> GetCategoryList();
    std::vector<std::string> GetSubCategoryList(const std::string& category);
    std::string GetText(const std::string& category, const std::string& subCategory);

    bool GetVisible(const std::string& category, const std::string& subCategory);
    void SetVisible(const std::string& category, const std::string& subCategory);

    void Save(const std::string& csvfile,
              const bool encrypt = false);

private:

    static Guide* obj;
    std::vector<GuideItem> m_guideList;
};
}

