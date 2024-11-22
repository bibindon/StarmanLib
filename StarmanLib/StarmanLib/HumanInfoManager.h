#pragma once

#include "HeaderOnlyCsv.hpp"

#include <string>
#include <vector>
#include <unordered_map>

class HumanInfo
{
public:

    void SetName(const std::string& arg);
    std::string GetName();

    void SetDetail(const std::string& arg);
    std::string GetDetail();

    void SetImagePath(const std::string& arg);
    std::string GetImagePath();

    void SetVisible(const bool arg);
    bool GetVisible();

private:

    std::string m_name;
    std::string m_detail;
    std::string m_imagePath;

    // �l�����̓��j���[��ʂŕ\������A
    // �Q�[���̐i�s�x�ɂ���ĕ\�������l�ƕ\������Ȃ��l������z��
    bool m_bVisible;
};

class HumanInfoManager
{

public:

    static HumanInfoManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfileBase, const std::string& csvfileSaved);
    void Save(const std::string& csvfile);

    HumanInfo GetHumanInfo(const std::string& name);
    std::vector<std::string> GetHumanNameList();
    void SetHumanVisible(const std::string& name);

private:

    // �V���O���g���I�u�W�F�N�g
    static HumanInfoManager* obj;

    std::unordered_map<std::string, HumanInfo> m_humanInfoMap;

};

