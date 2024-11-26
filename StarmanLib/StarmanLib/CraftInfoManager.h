#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace NSStarmanLib
{
// �N���t�g�p�̑f�ރN���X
class CraftMaterial
{
public:

    void SetName(const std::string& arg);
    std::string GetName();

    void SetNumber(const int arg);
    int GetNumber();

    void SetLevel(const int arg);
    int GetLevel();

private:
    // �f�ނ̖��O
    std::string m_name;
    
    // �f�ނ̕K�v��
    int m_number = 0;
    
    // �f�ނ̋������x��
    int m_level = 0;

};

// �����i�N���X
class CraftOutput
{
public:

    void SetName(const std::string& arg);
    std::string GetName() const;

    void SetNumber(const int arg);
    int GetNumber() const;

    void SetLevel(const int arg);
    int GetLevel() const;

private:

    // �����i�̖��O
    std::string m_name;
    
    // �����i�̏o�͐�
    int m_number = 0;
    
    // �����i�̋������x��
    int m_level = 0;
};

// �N���t�g�̏��N���X
class CraftInfo
{
public:

    void SetOutput(const CraftOutput& arg);
    CraftOutput GetOutput();

    void SetCraftMaterial(const int index, const CraftMaterial& arg);
    CraftMaterial GetCraftMaterial(const int index);
    std::vector<CraftMaterial> GetCraftMaterial();

private:

    CraftOutput m_output;

    std::unordered_map<int, CraftMaterial> m_materialList;
};

// �N���t�g���̊Ǘ��N���X
// �C�J�_�������i�ƂȂ郌�V�s��11��ނ���B
// �����l���{�P�̃C�J�_�A�����l���{�Q�̃C�J�_�E�E�E
// ���V�s����肷��ɂ́A�����i�̖��O�����ł͂Ȃ��A���O�ƌ��Ƌ����l���K�v
class CraftInfoManager
{

public:

    static CraftInfoManager* GetObj();

    static void Destroy();

    void Init(const std::string& csvfileDefinition);

    std::vector<CraftOutput> GetCraftItemList();

    CraftInfo GetCraftInfo(const CraftOutput& output);
    CraftInfo GetCraftInfo(const std::string& name, const int num, const int level);

private:

    // �V���O���g���I�u�W�F�N�g
    static CraftInfoManager* obj;

    std::vector<CraftInfo> m_craftInfoList;
};
}

