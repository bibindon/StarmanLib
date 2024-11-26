#include "CraftSystem.h"
#include "HeaderOnlyCsv.hpp"
#include "PowereggDateTime.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Storehouse.h"

using namespace NSStarmanLib;

CraftSystem* CraftSystem::obj { nullptr };

CraftSystem* CraftSystem::GetObj()
{
    if (obj == nullptr)
    {
        obj = new CraftSystem();
    }
    return obj;
}

void CraftSystem::Destroy()
{
    delete CraftSystem::obj;
    CraftSystem::obj = nullptr;
}

void CraftSystem::Init(const std::string& csvfileSkill, const std::string& csvfileQueue)
{
    {
        std::vector<std::vector<std::string> > vss;
        vss = csv::Read(csvfileSkill);

        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            CraftSkill craftSkill;

            std::string name = vss.at(i).at(0);
            craftSkill.SetName(name);

            int level = std::stoi(vss.at(i).at(1));
            craftSkill.SetLevel(level);

            if (vss.at(i).at(2) == "��")
            {
                craftSkill.SetEnable(true);
            }
            else
            {
                craftSkill.SetEnable(false);
            }
        }
    }
    {
        std::vector<std::vector<std::string> > vss;
        vss = csv::Read(csvfileQueue);

        for (std::size_t i = 1; i < vss.size(); ++i)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();

            std::string name = vss.at(i).at(0);
            int level = std::stoi(vss.at(i).at(1));

            // �N���t�g�����擾
            CraftInfo craftInfo = craftInfoManager->GetCraftInfo(name, 1, level);

            // �N���t�g���̃A�C�e�����
            CraftRequest craftRequest;

            craftRequest.SetCraftInfo(craftInfo);

            if (vss.at(i).at(2) == "��")
            {
                craftRequest.SetCrafting(true);
            }
            else
            {
                craftRequest.SetCrafting(false);
            }

            craftRequest.SetStartYear(std::stoi(vss.at(i).at(3)));
            craftRequest.SetStartMonth(std::stoi(vss.at(i).at(4)));
            craftRequest.SetStartDay(std::stoi(vss.at(i).at(5)));
            craftRequest.SetStartHour(std::stoi(vss.at(i).at(6)));
            craftRequest.SetStartMinute(std::stoi(vss.at(i).at(7)));
            craftRequest.SetStartSecond(std::stoi(vss.at(i).at(8)));

            craftRequest.SetFinishYear(std::stoi(vss.at(i).at(9)));
            craftRequest.SetFinishMonth(std::stoi(vss.at(i).at(10)));
            craftRequest.SetFinishDay(std::stoi(vss.at(i).at(11)));
            craftRequest.SetFinishHour(std::stoi(vss.at(i).at(12)));
            craftRequest.SetFinishMinute(std::stoi(vss.at(i).at(13)));
            craftRequest.SetFinishSecond(std::stoi(vss.at(i).at(14)));

            m_craftRequestList.push_back(craftRequest);
        }
    }
}

void NSStarmanLib::CraftSystem::Save(const std::string& csvfileSkill,
                                     const std::string& csvfileQueue)
{
    {
        std::vector<std::vector<std::string>> vss;
        std::vector<std::string> vs;

        vs.push_back("�N���t�g�A�C�e��");
        vs.push_back("�����l");
        vs.push_back("�N���t�g�\");
        vss.push_back(vs);
        vs.clear();

        for (auto it = m_craftSkillList.begin(); it != m_craftSkillList.end(); ++it)
        {
            vs.push_back(it->GetName());
            if (it->GetLevel() != -1)
            {
                vs.push_back(std::to_string(it->GetLevel()));
            }
            else
            {
                vs.push_back("");
            }

            if (it->GetEnable())
            {
                vs.push_back("��");
            }
            else
            {
                vs.push_back("");
            }
            vss.push_back(vs);
            vs.clear();
        }
        csv::Write(csvfileSkill, vss);
    }
    {
        std::vector<std::vector<std::string>> vss;
        std::vector<std::string> vs;

        vs.push_back("�N���t�g�A�C�e��");
        vs.push_back("�����l");
        vs.push_back("�N���t�g��");
        vs.push_back("�J�n�N");
        vs.push_back("�J�n��");
        vs.push_back("�J�n��");
        vs.push_back("�J�n��");
        vs.push_back("�J�n��");
        vs.push_back("�J�n�b");
        vs.push_back("�����N");
        vs.push_back("������");
        vs.push_back("������");
        vs.push_back("������");
        vs.push_back("������");
        vs.push_back("�����b");
        vss.push_back(vs);
        vs.clear();

        for (auto it = m_craftRequestList.begin(); it != m_craftRequestList.end(); ++it)
        {
            vs.push_back(it->GetName());
            vs.push_back(std::to_string(it->GetCraftInfo().GetOutput().GetLevel()));

            if (it->GetCrafting())
            {
                vs.push_back("��");
            }
            else
            {
                vs.push_back("");
            }

            vs.push_back(std::to_string(it->GetStartYear()));
            vs.push_back(std::to_string(it->GetStartMonth()));
            vs.push_back(std::to_string(it->GetStartDay()));
            vs.push_back(std::to_string(it->GetStartHour()));
            vs.push_back(std::to_string(it->GetStartMinute()));
            vs.push_back(std::to_string(it->GetStartSecond()));

            vs.push_back(std::to_string(it->GetFinishYear()));
            vs.push_back(std::to_string(it->GetFinishMonth()));
            vs.push_back(std::to_string(it->GetFinishDay()));
            vs.push_back(std::to_string(it->GetFinishHour()));
            vs.push_back(std::to_string(it->GetFinishMinute()));
            vs.push_back(std::to_string(it->GetFinishSecond()));

            vss.push_back(vs);
            vs.clear();
        }
        csv::Write(csvfileQueue, vss);
    }
}

void NSStarmanLib::CraftSystem::SetCraftsmanSkill(const std::string& craftItem, const int level)
{
    CraftSkill craftSkill;
    craftSkill.SetName(craftItem);
    craftSkill.SetLevel(level);
    craftSkill.SetEnable(true);
    m_craftSkillList.push_back(craftSkill);
}

bool NSStarmanLib::CraftSystem::GetCraftsmanSkill(const std::string& craftItem, const int level)
{
    bool result = false;
    for (auto it = m_craftSkillList.begin(); it != m_craftSkillList.end(); ++it)
    {
        if (it->GetName() == craftItem && it->GetLevel() == level)
        {
            result = it->GetEnable();
            break;
        }
    }
    return result;
}

bool NSStarmanLib::CraftSystem::QueueCraftRequest(const std::string& craftItem, const int level)
{
    // �\���5��܂�
    if (m_craftRequestList.size() >= 4)
    {
        return false;
    }

    CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();

    // �N���t�g���
    CraftInfo craftInfo = craftInfoManager->GetCraftInfo(craftItem, 1, level);

    // �f�ނ������
    // �f�ނ�����Ȃ��Ƃ���false��Ԃ�
    ItemManager* itemManager = ItemManager::GetObj();
    std::vector<CraftMaterial> craftMaterialList = craftInfo.GetCraftMaterial();

    Inventory* inventory = Inventory::GetObj();
    bool materialShortage = false;

    // �C���x���g�����ɕK�v�Ȃ����̑f�ނ����邩�̃`�F�b�N
    for (std::size_t i = 0; i < craftMaterialList.size(); ++i)
    {
        std::string name;
        int materialNum = 0;
        int materialLevel = 0;

        name = craftMaterialList.at(i).GetName();
        materialNum = craftMaterialList.at(i).GetNumber();
        materialLevel = craftMaterialList.at(i).GetLevel();

        int materialNumCurrent = inventory->CountItem(name, materialLevel);

        // �f�ނ�����Ȃ�
        if (materialNumCurrent < materialNum)
        {
            materialShortage = true;
            break;
        }
    }

    if (materialShortage)
    {
        return false;
    }

    // �C���x���g�����̑f�ނ��폜
    for (std::size_t i = 0; i < craftMaterialList.size(); ++i)
    {
        std::string name;
        int materialNum = 0;
        int materialLevel = 0;

        name = craftMaterialList.at(i).GetName();
        materialNum = craftMaterialList.at(i).GetNumber();
        materialLevel = craftMaterialList.at(i).GetLevel();

        // �f�ނ̕K�v�����폜����
        for (int j = 0; j < materialNum; ++j)
        {
            inventory->RemoveItem(name, materialLevel);
        }
    }

    // �N���t�g���̃A�C�e�����
    CraftRequest craftingItem;

    // ��肽�����̂��Z�b�g
    // �N���t�g�J�n���ԂƃN���t�g�������Ԃ͂����ł͐ݒ肵�Ȃ��i�N���t�g�v���̓L���[�C���O�o���邽�߁j
    craftingItem.SetCraftInfo(craftInfo);
    craftingItem.SetCrafting(false);

    m_craftRequestList.push_back(craftingItem);

    return true;
}

bool NSStarmanLib::CraftSystem::CancelCraftStart(const int index)
{
    if ((int)m_craftRequestList.size() <= index)
    {
        return false;
    }
    m_craftRequestList.erase(std::next(m_craftRequestList.begin(), index));
    return true;
}

void NSStarmanLib::CraftSystem::UpdateCraftStatus()
{
    // ���N�G�X�g���Ȃ��Ȃ��邱�ƂȂ�
    if (m_craftRequestList.size() == 0)
    {
        return;
    }

    // �N���t�g���N�G�X�g�̐擪���N���t�g���Ȃ�΂�邱�ƂȂ�
    if (m_craftRequestList.front().GetCrafting())
    {
        return;
    }

    // �N���t�g���N�G�X�g�̐擪���N���t�g���łȂ��Ȃ�΁A�N���t�g���J�n����
    if (m_craftRequestList.front().GetCrafting() == false)
    {
        m_craftRequestList.front().SetCrafting(true);

        // �p���[�G�b�O���ł̌��ݎ����ƃN���t�g����������ݒ肷��
        PowereggDateTime* obj = PowereggDateTime::GetObj();
        m_craftRequestList.front().SetStartYear(obj->GetYear());
        m_craftRequestList.front().SetStartMonth(obj->GetMonth());
        m_craftRequestList.front().SetStartDay(obj->GetDay());
        m_craftRequestList.front().SetStartHour(obj->GetHour());
        m_craftRequestList.front().SetStartMinute(obj->GetMinute());
        m_craftRequestList.front().SetStartSecond(obj->GetSecond());

        // ����������24���Ԍ�B
        // �����������A�C�e�����Ƃɕς���͓̂���Ȃ��̂ł���Ă��ǂ��悤�ȋC������
        // 1��32����13���͑��݂��Ȃ��̂ŁA���̑Ή����s�����߂�
        // �b�A���A���A�Ƃ����悤�ɍׂ����ق�����ݒ肵�Ă���
        m_craftRequestList.front().SetFinishSecond(obj->GetSecond());
        m_craftRequestList.front().SetFinishMinute(obj->GetMinute());
        m_craftRequestList.front().SetFinishHour(obj->GetHour());

        // 1��31���Ƃ�2��28���̂悤�Ȍ����łȂ��Ȃ�Γ����Ɂ{�P����B
        if (obj->GetDay() < obj->DAY_OF_MONTH(obj->GetMonth()))
        {
            m_craftRequestList.front().SetFinishDay(obj->GetDay() + 1);
            m_craftRequestList.front().SetFinishMonth(obj->GetMonth());
            m_craftRequestList.front().SetFinishYear(obj->GetYear());
        }
        // �����Ȃ�Γ�����1���ɂ���
        else
        {
            m_craftRequestList.front().SetFinishDay(1);

            // ������+1����
            // 13���ɂȂ�Ȃ��悤�ɒ��ӂ���
            if (obj->GetMonth() != 12)
            {
                m_craftRequestList.front().SetFinishMonth(obj->GetMonth() + 1);
                m_craftRequestList.front().SetFinishYear(obj->GetYear());
            }
            // 12���Ȃ�΁A�������𗂔N��1���ɂ���
            else if (obj->GetMonth() == 12)
            {
                m_craftRequestList.front().SetFinishMonth(1);
                m_craftRequestList.front().SetFinishYear(obj->GetYear() + 1);
            }
        }
    }
    // �N���t�g���Ȃ�΃N���t�g�����łȂ����m�F����
    else if (m_craftRequestList.front().GetCrafting())
    {

        // ���t���m�̔�r
        // 1�N2��3��4��5��6�b��6�N5��4��3��2��1�b�̂ǂ��炪�����E�ߋ����𔻒肷��ɂ�
        // 010203040506 �� 060504030201 �Ƃ���12���̐��l�ƌ��Ȃ���12���̐��l���m�̔�r���s���΂悢
        int y1, M1, d1, h1, m1, s1;
        int y2, M2, d2, h2, m2, s2;

        y1 = m_craftRequestList.front().GetFinishYear();
        M1 = m_craftRequestList.front().GetFinishMonth();
        d1 = m_craftRequestList.front().GetFinishDay();
        h1 = m_craftRequestList.front().GetFinishHour();
        m1 = m_craftRequestList.front().GetFinishMinute();
        s1 = m_craftRequestList.front().GetFinishSecond();

        PowereggDateTime* obj = PowereggDateTime::GetObj();
        y2 = obj->GetYear();
        M2 = obj->GetMonth();
        d2 = obj->GetDay();
        h2 = obj->GetHour();
        m2 = obj->GetMinute();
        s2 = obj->GetSecond();

        bool fromPastToFuture = PowereggDateTime::FromPastToFuture(y1, M1, d1, h1, m1, s1, 
                                                                   y2, M2, d2, h2, m2, s2);

        // ��Ɗ��������������ݎ����V�����A���Ƃ͊������Ă��邱�Ƃ��Ӗ�����
        if (fromPastToFuture)
        {
            // ���������A�C�e����q�ɂɔz�u����
            CraftOutput output = m_craftRequestList.front().GetCraftInfo().GetOutput();
            Storehouse* storehouse = Storehouse::GetObj();
            for (int i = 0; i < output.GetNumber(); ++i)
            {
                storehouse->AddItem(output.GetName(), output.GetLevel());
            }

            // �擪�̗v�f�����N�G�X�g�̃��X�g����폜
            m_craftRequestList.pop_front();
        }
    }
}

std::string CraftRequest::GetName() const
{
    return m_name;
}

void CraftRequest::SetName(std::string mname)
{
    m_name = mname;
}

int CraftRequest::GetStartYear() const
{
    return m_startYear;
}

void CraftRequest::SetStartYear(int startYear)
{
    m_startYear = startYear;
}

int CraftRequest::GetStartMonth() const
{
    return m_startMonth;
}

void CraftRequest::SetStartMonth(int startMonth)
{
    m_startMonth = startMonth;
}

int CraftRequest::GetStartDay() const
{
    return m_startDay;
}

void CraftRequest::SetStartDay(int startDay)
{
    m_startDay = startDay;
}

int CraftRequest::GetStartHour() const
{
    return m_startHour;
}

void CraftRequest::SetStartHour(int startHour)
{
    m_startHour = startHour;
}

int CraftRequest::GetStartMinute() const
{
    return m_startMinute;
}

void CraftRequest::SetStartMinute(int startMinute)
{
    m_startMinute = startMinute;
}

int CraftRequest::GetStartSecond() const
{
    return m_startSecond;
}

void CraftRequest::SetStartSecond(int startSecond)
{
    m_startSecond = startSecond;
}

int CraftRequest::GetFinishYear() const
{
    return m_finishYear;
}

void CraftRequest::SetFinishYear(int mfinishYear)
{
    m_finishYear = mfinishYear;
}

int CraftRequest::GetFinishMonth() const
{
    return m_finishMonth;
}

void CraftRequest::SetFinishMonth(int mfinishMonth)
{
    m_finishMonth = mfinishMonth;
}

int CraftRequest::GetFinishDay() const
{
    return m_finishDay;
}

void CraftRequest::SetFinishDay(int mfinishDay)
{
    m_finishDay = mfinishDay;
}

int CraftRequest::GetFinishHour() const
{
    return m_finishHour;
}

void CraftRequest::SetFinishHour(int mfinishHour)
{
    m_finishHour = mfinishHour;
}

int CraftRequest::GetFinishMinute() const
{
    return m_finishMinute;
}

void CraftRequest::SetFinishMinute(int mfinishMinute)
{
    m_finishMinute = mfinishMinute;
}

int CraftRequest::GetFinishSecond() const
{
    return m_finishSecond;
}

void CraftRequest::SetFinishSecond(int mfinishSecond)
{
    m_finishSecond = mfinishSecond;
}

CraftInfo NSStarmanLib::CraftRequest::GetCraftInfo() const
{
    return m_craftInfo;
}

void NSStarmanLib::CraftRequest::SetCraftInfo(const CraftInfo& arg)
{
    m_craftInfo = arg;
}

bool NSStarmanLib::CraftRequest::GetCrafting() const
{
    return m_crafting;
}

void NSStarmanLib::CraftRequest::SetCrafting(const bool arg)
{
    m_crafting = arg;
}

void NSStarmanLib::CraftSkill::SetName(const std::string& arg)
{
    m_name = arg;
}

std::string NSStarmanLib::CraftSkill::GetName() const
{
    return m_name;
}

void NSStarmanLib::CraftSkill::SetLevel(const int arg)
{
    m_level = arg;
}

int NSStarmanLib::CraftSkill::GetLevel() const
{
    return m_level;
}

void NSStarmanLib::CraftSkill::SetEnable(const bool arg)
{
    m_enable = arg;
}

bool NSStarmanLib::CraftSkill::GetEnable() const
{
    return m_enable;
}
