#include "Guide.h"
#include "Util.h"

using namespace NSStarmanLib;

Guide* Guide::obj { nullptr };

void GuideItem::SetCategory(const std::string& category)
{
    m_category = category;
}

std::string GuideItem::GetCategory()
{
    return m_category;
}

void GuideItem::SetSubCategory(const std::string& subCategory)
{
    m_subCategory = subCategory;
}

std::string GuideItem::GetSubCategory()
{
    return m_subCategory;
}

void GuideItem::SetText(const std::string& text)
{
    m_text = text;
    m_text.erase(std::remove(m_text.begin(), m_text.end(), '"'), m_text.end());
}

std::string GuideItem::GetText()
{
    return m_text;
}

void GuideItem::SetVisible(const bool visible)
{
    m_bVisible = visible;
}

bool GuideItem::GetVisible()
{
    return m_bVisible;
}

Guide* Guide::GetObj()
{
    if (obj == nullptr)
    {
        obj = new Guide();
    }
    return obj;
}

void Guide::Init(const std::string& csvfile,
                 const bool decrypt)
{
    std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvfile, decrypt);

    for (std::size_t i = 1; i < vvs.size(); ++i)
    {
        GuideItem guideItem;
        guideItem.SetCategory(vvs.at(i).at(1));
        guideItem.SetSubCategory(vvs.at(i).at(2));
        guideItem.SetText(vvs.at(i).at(3));
        if (vvs.at(i).at(4) == "○")
        {
            guideItem.SetVisible(true);
        }
        else
        {
            guideItem.SetVisible(false);
        }
        m_guideList.push_back(guideItem);
    }
}

void Guide::Destroy()
{
    delete Guide::obj;
    Guide::obj = nullptr;
}

std::vector<std::string> Guide::GetCategoryList()
{
    std::vector<std::string> vs;
    for (std::size_t i = 0; i < m_guideList.size(); ++i)
    {
        vs.push_back(m_guideList.at(i).GetCategory());
    }
    return vs;
}

std::vector<std::string> Guide::GetSubCategoryList(const std::string& category)
{
    std::vector<std::string> vs;
    for (std::size_t i = 0; i < m_guideList.size(); ++i)
    {
        if (m_guideList.at(i).GetCategory() == category)
        {
            vs.push_back(m_guideList.at(i).GetSubCategory());
        }
    }
    return vs;
}

std::string Guide::GetText(const std::string& category, const std::string& subCategory)
{
    std::string result;
    for (std::size_t i = 0; i < m_guideList.size(); ++i)
    {
        if (m_guideList.at(i).GetCategory() == category)
        {
            if (m_guideList.at(i).GetSubCategory() == subCategory)
            {
                result = m_guideList.at(i).GetText();
                break;
            }
        }
    }
    return result;
}

bool Guide::GetVisible(const std::string& category, const std::string& subCategory)
{
    bool result = false;
    for (std::size_t i = 0; i < m_guideList.size(); ++i)
    {
        if (m_guideList.at(i).GetCategory() == category)
        {
            if (m_guideList.at(i).GetSubCategory() == subCategory)
            {
                result = m_guideList.at(i).GetVisible();
                break;
            }
        }
    }
    return result;
}

void Guide::SetVisible(const std::string& category, const std::string& subCategory)
{
    for (std::size_t i = 0; i < m_guideList.size(); ++i)
    {
        if (m_guideList.at(i).GetCategory() == category)
        {
            if (m_guideList.at(i).GetSubCategory() == subCategory)
            {
                m_guideList.at(i).SetVisible(true);
                break;
            }
        }
    }
}

void Guide::Save(const std::string& csvfile,
                 const bool encrypt)
{
    std::vector<std::vector<std::string>> vvs;
    std::vector<std::string> vs;
    vs.push_back("ID");
    vs.push_back("大分類");
    vs.push_back("小分類");
    vs.push_back("説明文");
    vs.push_back("表示済み");
    vvs.push_back(vs);
    vs.clear();
    for (std::size_t i = 0; i < m_guideList.size(); ++i)
    {
        vs.push_back(std::to_string(i+1));
        vs.push_back(m_guideList.at(i).GetCategory());
        vs.push_back(m_guideList.at(i).GetSubCategory());

        // ダブルクォートを戦闘と末尾に付与する
        std::string work;
        work = m_guideList.at(i).GetText();
        work = "\"" + work + "\"";
        vs.push_back(work);
        if (m_guideList.at(i).GetVisible())
        {
            vs.push_back("○");
        }
        else
        {
            vs.push_back("");
        }
        vvs.push_back(vs);
        vs.clear();
    }

    Util::WriteToCsv(csvfile, vvs, encrypt);
}
