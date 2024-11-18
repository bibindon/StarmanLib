#pragma once
#include <string>
#include <vector>

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

    // ‘å•ª—Ş
    std::string m_category;

    // ¬•ª—Ş
    std::string m_subCategory;

    // à–¾•¶
    std::string m_text;

    // •\¦Ï‚İ‚©”Û‚©
    bool m_bVisible { false };
};

// ‘€ìà–¾
class Guide
{
public:

    static Guide* GetObj();
    void Init(const std::string& csvfile);
    static void Destroy();

    std::vector<std::string> GetCategoryList();
    std::vector<std::string> GetSubCategoryList(const std::string& category);
    std::string GetText(const std::string& category, const std::string& subCategory);

    bool GetVisible(const std::string& category, const std::string& subCategory);
    void SetVisible(const std::string& category, const std::string& subCategory);

    void Save(const std::string& csvfile);

private:

    static Guide* obj;
    std::vector<GuideItem> m_guideList;
};

