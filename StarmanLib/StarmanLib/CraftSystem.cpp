#include "CraftSystem.h"
#include "PowereggDateTime.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Storehouse.h"
#include "Util.h"
#include "Voyage.h"

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

void CraftSystem::Init(const std::string& csvfileSkill, const std::string& csvfileQueue,
                       const bool decrypt)
{
    // CraftSystem��Init�֐�����ɁACraftInfoManager��Init���Ă΂�Ă���K�v������B
    {
        CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();
        if (craftInfoManager->Inited() == false)
        {
            throw std::exception();
        }
    }

    {
        std::vector<std::vector<std::string> > vvs = Util::ReadFromCsv(csvfileSkill, decrypt);

        if (vvs.empty())
        {
            throw std::exception();
        }

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            CraftSkill craftSkill;

            std::string name = vvs.at(i).at(0);
            craftSkill.SetName(name);

            int level = 0;
            if (vvs.at(i).at(1).empty())
            {
                level = -1;
            }
            else
            {
                level = std::stoi(vvs.at(i).at(1));
            }
            craftSkill.SetLevel(level);

            if (vvs.at(i).at(2) == "��")
            {
                craftSkill.SetEnable(true);
            }
            else
            {
                craftSkill.SetEnable(false);
            }

            int work = 0;
            if (vvs.at(i).at(3).empty())
            {
                work = -1;
            }
            else
            {
                work = std::stoi(vvs.at(i).at(3));
            }
            craftSkill.SetLevelUpNecessity(work);

            if (vvs.at(i).at(4).empty())
            {
                work = -1;
            }
            else
            {
                work = std::stoi(vvs.at(i).at(4));
            }
            craftSkill.SetSuccessNum(work);

            m_craftSkillList.push_back(craftSkill);
        }
    }
    {
        std::vector<std::vector<std::string> > vvs = Util::ReadFromCsv(csvfileQueue, decrypt);

        if (vvs.empty())
        {
            throw std::exception();
        }

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();

            std::string name = vvs.at(i).at(0);

            int level = 0;

            if (vvs.at(i).at(1).empty())
            {
                level = -1;
            }
            else
            {
                level = std::stoi(vvs.at(i).at(1));
            }

            // �N���t�g�����擾
            CraftInfo craftInfo = craftInfoManager->GetCraftInfo(name, 1, level);

            // �N���t�g���̃A�C�e�����
            CraftRequest craftRequest;

            craftRequest.SetCraftInfo(craftInfo);

            if (vvs.at(i).at(2) == "��")
            {
                craftRequest.SetCrafting(true);
            }
            else
            {
                craftRequest.SetCrafting(false);
            }

            if (craftRequest.GetCrafting())
            {
                craftRequest.SetStartYear(std::stoi(vvs.at(i).at(3)));
                craftRequest.SetStartMonth(std::stoi(vvs.at(i).at(4)));
                craftRequest.SetStartDay(std::stoi(vvs.at(i).at(5)));
                craftRequest.SetStartHour(std::stoi(vvs.at(i).at(6)));
                craftRequest.SetStartMinute(std::stoi(vvs.at(i).at(7)));
                craftRequest.SetStartSecond(std::stoi(vvs.at(i).at(8)));

                craftRequest.SetFinishYear(std::stoi(vvs.at(i).at(9)));
                craftRequest.SetFinishMonth(std::stoi(vvs.at(i).at(10)));
                craftRequest.SetFinishDay(std::stoi(vvs.at(i).at(11)));
                craftRequest.SetFinishHour(std::stoi(vvs.at(i).at(12)));
                craftRequest.SetFinishMinute(std::stoi(vvs.at(i).at(13)));
                craftRequest.SetFinishSecond(std::stoi(vvs.at(i).at(14)));
            }
            else
            {
                craftRequest.SetStartYear(-1);
                craftRequest.SetStartMonth(-1);
                craftRequest.SetStartDay(-1);
                craftRequest.SetStartHour(-1);
                craftRequest.SetStartMinute(-1);
                craftRequest.SetStartSecond(-1);

                craftRequest.SetFinishYear(-1);
                craftRequest.SetFinishMonth(-1);
                craftRequest.SetFinishDay(-1);
                craftRequest.SetFinishHour(-1);
                craftRequest.SetFinishMinute(-1);
                craftRequest.SetFinishSecond(-1);
            }

            craftRequest.SetStorehouseId(std::stoi(vvs.at(i).at(15)));

            m_craftRequestList.push_back(craftRequest);
        }
    }
}

void NSStarmanLib::CraftSystem::Save(const std::string& csvfileSkill,
                                     const std::string& csvfileQueue,
                                     const bool encrypt)
{
    {
        std::vector<std::vector<std::string>> vvs;
        std::vector<std::string> vs;

        vs.push_back("�N���t�g�A�C�e��");
        vs.push_back("�����l");
        vs.push_back("�N���t�g�\");
        vs.push_back("���̃��x�����K������̂ɕK�v�ȃN���t�g��");
        vs.push_back("���݂̃N���t�g�o����");
        vvs.push_back(vs);
        vs.clear();

        for (auto it = m_craftSkillList.begin(); it != m_craftSkillList.end(); ++it)
        {
            vs.push_back(it->GetName());
            if (it->GetLevel() == -1)
            {
                vs.push_back("");
            }
            else
            {
                vs.push_back(std::to_string(it->GetLevel()));
            }

            if (it->GetEnable())
            {
                vs.push_back("��");
            }
            else
            {
                vs.push_back("");
            }

            if (it->GetLevelUpNecessity() == -1)
            {
                vs.push_back("");
            }
            else
            {
                vs.push_back(std::to_string(it->GetLevelUpNecessity()));
            }

            if (it->GetSuccessNum() == -1)
            {
                throw std::exception();
            }
            else
            {
                vs.push_back(std::to_string(it->GetSuccessNum()));
            }

            vvs.push_back(vs);
            vs.clear();
        }

        Util::WriteToCsv(csvfileSkill, vvs, encrypt);
    }
    {
        std::vector<std::vector<std::string>> vvs;
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
        vs.push_back("���[��q��ID");
        vvs.push_back(vs);
        vs.clear();

        for (auto it = m_craftRequestList.begin(); it != m_craftRequestList.end(); ++it)
        {
            vs.push_back(it->GetName());

            int level = it->GetCraftInfo().GetOutput().GetLevel();
            if (level != -1)
            {
                vs.push_back(std::to_string(level));
            }
            else
            {
                vs.push_back("");
            }

            if (it->GetCrafting())
            {
                vs.push_back("��");
            }
            else
            {
                vs.push_back("");
            }

            if (it->GetCrafting())
            {
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
            }
            else
            {
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");

                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
                vs.push_back("");
            }

            vs.push_back(std::to_string(it->GetStorehouseId()));

            vvs.push_back(vs);
            vs.clear();
        }

        Util::WriteToCsv(csvfileQueue, vvs, encrypt);
    }
}

void NSStarmanLib::CraftSystem::SetCraftsmanSkill(const std::string& craftItem, const int level)
{
    auto it = std::find_if(m_craftSkillList.begin(), m_craftSkillList.end(),
                           [&](CraftSkill& x)
                           {
                               return x.GetName() == craftItem && x.GetLevel() == level;
                           });

    if (it != m_craftSkillList.end())
    {
        it->SetEnable(true);
    }
}

int NSStarmanLib::CraftSystem::GetCraftsmanSkill(const std::string& craftItem)
{
    // �{�P�̐Ε��Ɓ{�Q�̐Ε������āA�{�R�̐Ε������Ȃ��Ȃ�2��Ԃ��B
    // �icraftItem�̍���A�C�e���̒��ōō����x���̐��l��Ԃ��B�j
    int level = -1;
    for (auto it = m_craftSkillList.begin(); it != m_craftSkillList.end(); ++it)
    {
        if (it->GetName() == craftItem && it->GetEnable())
        {
            if (it->GetLevel() > level)
            {
                level = it->GetLevel();
            }
        }
    }
    return level;
}

bool NSStarmanLib::CraftSystem::QueueCraftRequest(const std::string& craftItem,
                                                  const int storehouseId)
{
    // �\���5���܂�
    if (m_craftRequestList.size() >= 4)
    {
        return false;
    }

    CraftInfoManager* craftInfoManager = CraftInfoManager::GetObj();

    // ���݁A�E�l������craftItem�̃��x�����擾
    // �{�P�̐Ε��Ɓ{�Q�̐Ε������āA�{�R�̐Ε������Ȃ��Ȃ�2���擾�B
    int level = GetCraftsmanSkill(craftItem);

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
    // �N���t�g�v���̓L���[�C���O����邽�߁A�ꌩ�A���̎��_�őf�ނ��폜����K�v�͂Ȃ��悤�Ɏv����B
    // �������A���ۂɃN���t�g���J�n���ꂽ�Ƃ��ɃA�C�e�����폜����A�Ƃ��������ɂ���ƁA
    // ���ɓ���ȃv���O�����������K�v������B���̂��߁A���̎��_�őf�ނ͍폜���邱�Ƃɂ���B
    for (std::size_t i = 0; i < craftMaterialList.size(); ++i)
    {
        std::string name;
        int materialNum = 0;
        int materialLevel = 0;

        name = craftMaterialList.at(i).GetName();
        materialNum = craftMaterialList.at(i).GetNumber();
        materialLevel = craftMaterialList.at(i).GetLevel();

        // �f�ނ̕K�v�����폜����
        // subId�͐��l���Ⴂ���̂��珇�Ɏg��

        std::vector<int> subIdList = inventory->GetSubIdList(craftMaterialList.at(i).GetId());
        for (int j = 0; j < materialNum; ++j)
        {
            inventory->RemoveItem(name, subIdList.at(i), materialLevel);
        }
    }

    // �N���t�g���̃A�C�e�����
    CraftRequest craftRequest;

    // ��肽�����̂��Z�b�g
    // �N���t�g�J�n���ԂƃN���t�g�������Ԃ͂����ł͐ݒ肵�Ȃ��i�N���t�g�v���̓L���[�C���O�o���邽�߁j
    craftRequest.SetCraftInfo(craftInfo);
    craftRequest.SetCrafting(false);

    // ���������ۂ̊i�[��̑q��
    craftRequest.SetStorehouseId(storehouseId);

    m_craftRequestList.push_back(craftRequest);

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

    // �N���t�g���N�G�X�g�̐擪���N���t�g���łȂ��Ȃ�΁A�N���t�g���J�n����
    if (m_craftRequestList.front().GetCrafting() == false)
    {
        StartCraft();
    }
    // �N���t�g���N�G�X�g�̐擪���N���t�g���Ȃ�΃N���t�g�����łȂ����m�F����
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

            int storehouseId = m_craftRequestList.front().GetStorehouseId();
            Storehouse* storehouse = StorehouseManager::Get()->GetStorehouse(storehouseId);

            for (int i = 0; i < output.GetNumber(); ++i)
            {
                // �C�J�_�̏ꍇ�͑q�ɂɓ���Ȃ��B
                if (output.GetName() == "�C�J�_")
                {
                    auto voyage = Voyage::Get();
                    Raft raft;
                    // TODO �C�J�_�̍��W�͂ǂ���ݒ肷��H
                    // raft.SetXYZ();
                    auto itemManager = ItemManager::GetObj();
                    auto itemDef = itemManager->GetItemDef(output.GetName(), output.GetLevel());

                    auto dura = itemDef.GetDurabilityMax();
                    raft.SetDurability(dura);

                    // TODO �C�J�_�̏ꏊ�^�C�v�͂ǂ���ݒ肷��H
                    // raft.SetPosType();

                    auto storehouseList = StorehouseManager::Get()->GetStorehouseIdList();
                    raft.SetStorehouseId(storehouseList.size());

                    voyage->AddRaft(raft);
                }
                else
                {
                    storehouse->AddItem(output.GetName(), output.GetLevel());
                }
            }

            // �E�l�̏n���x�̍X�V
            // �����l�Ȃ��̑܂�2��������A���͋����l�{�P�̑܂�����悤�ɂȂ�B
            // ���̂��ߍ�����񐔂��L�^����
            bool levelup = false;
            for (std::size_t i = 0; i < m_craftSkillList.size(); ++i)
            {
                if (output.GetName() == m_craftSkillList.at(i).GetName() &&
                    output.GetLevel() == m_craftSkillList.at(i).GetLevel())
                {
                    int successNum = m_craftSkillList.at(i).GetSuccessNum();
                    ++successNum;
                    m_craftSkillList.at(i).SetSuccessNum(successNum);

                    // ���x���A�b�v����
                    // �K��񐔁A�N���t�g�ɐ������Ă����玟�̋����l�̃N���t�g���\�ɂ���
                    if (m_craftSkillList.at(i).GetLevelUpNecessity() <= successNum)
                    {
                        levelup = true;
                    }
                    break;
                }
            }

            // ���x���A�b�v����
            // �܂��A�����l�����̃N���t�g�����݂��邩�𒲂ׂ�B
            if (levelup)
            {
                // ������+1~+5�ŉ\�̏ꍇ�A�����l��-1, 1, 2, 3, 4, 5��6�ʂ�ƂȂ�B
                // 0���܂܂�Ȃ����Ƃɒ��ӁB
                int targetSkill = -1;
                bool targetSkillExist = false;
                if (output.GetLevel() == -1)
                {
                    targetSkill = 1;
                }
                else if (output.GetLevel() >= 1)
                {
                    targetSkill = output.GetLevel() + 1;
                }
                else
                {
                    throw std::exception();
                }

                std::size_t targetSkillIndex = 0;
                for (std::size_t i = 0; i < m_craftSkillList.size(); ++i)
                {

                    if (output.GetName() == m_craftSkillList.at(i).GetName() &&
                        targetSkill      == m_craftSkillList.at(i).GetLevel())
                    {
                        targetSkillExist = true;
                        targetSkillIndex = i;
                        break;
                    }
                }

                // ���݂���Ȃ�N���t�g�\�ɕύX����
                if (targetSkillExist)
                {
                    if (m_craftSkillList.at(targetSkillIndex).GetEnable() == false)
                    {
                        m_craftSkillList.at(targetSkillIndex).SetEnable(true);
                    }
                }
            }


            // �擪�̗v�f�����N�G�X�g�̃��X�g����폜
            m_craftRequestList.pop_front();

            // �\�񃊃X�g���O�ł͂Ȃ��Ȃ�A�V���ɐ퓬�̗v�f�ƂȂ������N�G�X�g���N���t�g�J�n
            if (m_craftRequestList.size() >= 1)
            {
                StartCraft();
            }
        }
    }
}

void NSStarmanLib::CraftSystem::StartCraft()
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

int NSStarmanLib::CraftSystem::GetProgress()
{
    if (m_craftRequestList.front().GetCrafting() == false)
    {
        return -1;
    }

    // 24���ԂŊ����Ȃ̂�1���Ԃ�4%�㏸������B���E�b�͍l���Ȃ��B
    // �o�ߎ���
    int elapsedHour = 0;

    PowereggDateTime* obj = PowereggDateTime::GetObj();
    int currentHour = obj->GetHour();
    int finishHour = m_craftRequestList.front().GetFinishHour();
    if (currentHour > finishHour)
    {
        elapsedHour = currentHour - finishHour;
    }
    // ���ݎ�����0���𒴂�����24�𑫂��Ă������
    else
    {
        elapsedHour = (currentHour+24) - finishHour;
    }
    return elapsedHour * 100 / 24;
}

std::list<CraftRequest> NSStarmanLib::CraftSystem::GetCraftRequestList()
{
    return m_craftRequestList;
}

std::string CraftRequest::GetName() const
{
    return m_craftInfo.GetOutput().GetName();
}

int NSStarmanLib::CraftRequest::GetLevel() const
{
    return m_craftInfo.GetOutput().GetLevel();
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

int NSStarmanLib::CraftRequest::GetStorehouseId() const
{
    return m_storehouseId;
}

void NSStarmanLib::CraftRequest::SetStorehouseId(const int id)
{
    m_storehouseId = id;
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

void NSStarmanLib::CraftSkill::SetLevelUpNecessity(const int arg)
{
    m_levelUpNecessity = arg;
}

int NSStarmanLib::CraftSkill::GetLevelUpNecessity() const
{
    return m_levelUpNecessity;
}

void NSStarmanLib::CraftSkill::SetSuccessNum(const int arg)
{
    m_successNum = arg;
}

int NSStarmanLib::CraftSkill::GetSuccessNum() const
{
    return m_successNum;
}

