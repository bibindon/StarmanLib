#include "MapObjManager.h"
#include <algorithm>
#include "Util.h"
#include <fstream>

NSStarmanLib::MapObjManager* NSStarmanLib::MapObjManager::obj = nullptr;

/*
void NSStarmanLib::MapObj::SetId(const int id)
{
    m_id = id;
}

int NSStarmanLib::MapObj::GetId() const
{
    return m_id;
}

void NSStarmanLib::MapObj::SetFrameX(const int x)
{
    m_frameX = x;
}

int NSStarmanLib::MapObj::GetFrameX() const
{
    return m_frameX;
}

void NSStarmanLib::MapObj::SetFrameZ(const int z)
{
    m_frameZ = z;
}

int NSStarmanLib::MapObj::GetFrameZ() const
{
    return m_frameZ;
}

void NSStarmanLib::MapObj::SetModelId(const int arg)
{
    m_modelId = arg;
}

int NSStarmanLib::MapObj::GetModelId() const
{
    return m_modelId;
}

void NSStarmanLib::MapObj::SetX(const float arg)
{
    m_x = arg;
}

float NSStarmanLib::MapObj::GetX() const
{
    return m_x;
}

void NSStarmanLib::MapObj::SetY(const float arg)
{
    m_y = arg;
}

float NSStarmanLib::MapObj::GetY() const
{
    return m_y;
}

void NSStarmanLib::MapObj::SetZ(const float arg)
{
    m_z = arg;
}

float NSStarmanLib::MapObj::GetZ() const
{
    return m_z;
}

void NSStarmanLib::MapObj::SetRotY(const float arg)
{
    m_yRot = arg;
}

float NSStarmanLib::MapObj::GetRotY() const
{
    return m_yRot;
}

void NSStarmanLib::MapObj::SetScale(const float arg)
{
    m_scale = arg;
}

float NSStarmanLib::MapObj::GetScale() const
{
    return m_scale;
}

void NSStarmanLib::MapObj::SetShow(const bool arg)
{
    m_show = arg;
}

bool NSStarmanLib::MapObj::GetShow() const
{
    return m_show;
}

void NSStarmanLib::MapObj::SetVisible(const bool arg)
{
    m_visible = arg;
}

bool NSStarmanLib::MapObj::GetVisible() const
{
    return m_visible;
}
*/

NSStarmanLib::MapObjManager* NSStarmanLib::MapObjManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new MapObjManager();
    }
    return obj;
}

void NSStarmanLib::MapObjManager::Init(const std::string& csvfile,
                                       const std::string& csvModelId,
                                       const bool decrypt)
{
    {
        std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvfile, decrypt);

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            stMapObj work;

            float work_f = 0.f;

            work.m_id = std::stoi(vvs.at(i).at(0));

            work.m_modelId = std::stoi(vvs.at(i).at(1));

            work_f = std::stof(vvs.at(i).at(2));
            work.m_x = work_f;
            work.m_frameX = (int)work_f/100;

            work.m_y = std::stof(vvs.at(i).at(3));

            work_f = std::stof(vvs.at(i).at(4));
            work.m_z = work_f;
            work.m_frameZ = (int)work_f/100;

            work.m_yRot = std::stof(vvs.at(i).at(5));

            work.m_scale = std::stof(vvs.at(i).at(6));

            if (vvs.at(i).at(7) == "y")
            {
                work.m_visible = true;
            }
            else
            {
                work.m_visible = false;
            }

            m_stMapObjMap[work.m_frameX][work.m_frameZ].emplace_back(work);
        }
    }
    {
        std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvModelId, decrypt);

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            m_XnameMap[std::stoi(vvs.at(i).at(0))] = vvs.at(i).at(1);
        }
    }
}

void NSStarmanLib::MapObjManager::InitWithBinary(const std::string& binFile,
                                                 const std::string& csvModelId,
                                                 const bool decrypt)
{
    {
        std::vector<NSStarmanLib::stMapObj> stMapObjList;

        std::ifstream inFile(binFile, std::ios::binary);
        if (inFile.is_open() == false)
        {
            throw std::exception();
        }

        size_t size = 0;

        // �x�N�^�[�T�C�Y��ǂݍ���
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));

        // �x�N�^�[�T�C�Y��ݒ�
        stMapObjList.resize(size);

        // �f�[�^�{�̂�ǂݍ���
        inFile.read(reinterpret_cast<char*>(stMapObjList.data()),
                    static_cast<std::streamsize>(size) * sizeof(NSStarmanLib::stMapObj));

        inFile.close();

        for (auto it = stMapObjList.begin(); it != stMapObjList.end(); ++it)
        {
            m_stMapObjMap[it->m_frameX][it->m_frameX].emplace_back(*it);
        }
    }

    {
        std::vector<std::vector<std::string>> vvs = Util::ReadFromCsv(csvModelId, decrypt);

        for (std::size_t i = 1; i < vvs.size(); ++i)
        {
            m_XnameMap[std::stoi(vvs.at(i).at(0))] = vvs.at(i).at(1);
        }
    }
}

void NSStarmanLib::MapObjManager::Save(const std::string& csvfile,
                                       const bool encrypt)
{
    std::vector<stMapObj> work;

    for (auto itX = m_stMapObjMap.begin(); itX != m_stMapObjMap.end(); ++itX)
    {
        for (auto itZ = itX->second.begin(); itZ != itX->second.end(); ++itZ)
        {
            for (int i = 0; i < (int)itZ->second.size(); ++i)
            {
                work.push_back(itZ->second.at(i));
            }
        }
    }

    std::sort(work.begin(), work.end(),
              [](const stMapObj& x1, const stMapObj& x2)
              {
                  return x1.m_id < x2.m_id;
              });

    std::vector<std::vector<std::string> > vss;
    std::vector<std::string> vs;
    std::string work_str;

    vs.clear();
    vs.push_back("ID");
    vs.push_back("���f��ID");
    vs.push_back("X");
    vs.push_back("Y");
    vs.push_back("Z");
    vs.push_back("RotY");
    vs.push_back("Scale");
    vs.push_back("�\��");
    vss.push_back(vs);

    for (int i = 0; i < (int)work.size(); ++i)
    {
        vs.clear();
        vs.push_back(std::to_string(work.at(i).m_id));
        vs.push_back(std::to_string(work.at(i).m_modelId));
        vs.push_back(std::to_string(work.at(i).m_x));
        vs.push_back(std::to_string(work.at(i).m_y));
        vs.push_back(std::to_string(work.at(i).m_z));
        vs.push_back(std::to_string(work.at(i).m_yRot));
        vs.push_back(std::to_string(work.at(i).m_scale));
        if (work.at(i).m_visible)
        {
            vs.push_back("y");
        }
        else
        {
            vs.push_back("n");
        }

        vss.push_back(vs);
    }

    Util::WriteToCsv(csvfile, vss, encrypt);
}

void NSStarmanLib::MapObjManager::SaveWithBinary(const std::string& binfile)
{
}

void NSStarmanLib::MapObjManager::Destroy()
{
    delete MapObjManager::obj;
    MapObjManager::obj = nullptr;
}

std::vector<NSStarmanLib::stMapObj>
NSStarmanLib::MapObjManager::GetMapObjList(const float playerX,
                                           const float playerZ)
{
    std::vector<stMapObj> result;
    // �v���C���[��X���W��   0 ~  99 �Ȃ�i�qX��0
    // �v���C���[��X���W�� 100 ~ 199 �Ȃ�i�qX��1

    int frameX = (int)playerX / 100;
    int frameZ = (int)playerZ / 100;

    std::vector<stMapObj> work;
    work = m_stMapObjMap[frameX][frameZ];
    result = work;

    //-----------------------------------------------------------------------------
    // ����A��A�E��A���A�E�A�����A���A�E���̊i�q�ɂ��Ă��ǉ�
    //-----------------------------------------------------------------------------

    // ����
    work = m_stMapObjMap[frameX-1][frameZ+1];
    result.insert(result.end(), work.begin(), work.end());

    // ��
    work = m_stMapObjMap[frameX][frameZ+1];
    result.insert(result.end(), work.begin(), work.end());

    // �E��
    work = m_stMapObjMap[frameX+1][frameZ+1];
    result.insert(result.end(), work.begin(), work.end());

    // ��
    work = m_stMapObjMap[frameX-1][frameZ];
    result.insert(result.end(), work.begin(), work.end());

    // �E
    work = m_stMapObjMap[frameX+1][frameZ];
    result.insert(result.end(), work.begin(), work.end());

    // ����
    work = m_stMapObjMap[frameX-1][frameZ-1];
    result.insert(result.end(), work.begin(), work.end());

    // ��
    work = m_stMapObjMap[frameX][frameZ-1];
    result.insert(result.end(), work.begin(), work.end());

    // �E��
    work = m_stMapObjMap[frameX+1][frameZ-1];
    result.insert(result.end(), work.begin(), work.end());

    return result;
}

std::vector<NSStarmanLib::stMapObj>
NSStarmanLib::MapObjManager::GetMapObjListR(const float playerX,
                                            const float playerZ,
                                            const float r)
{
    std::vector<stMapObj> result;
    // �v���C���[��X���W��   0 ~  99 �Ȃ�i�qX��0
    // �v���C���[��X���W�� 100 ~ 199 �Ȃ�i�qX��1

    int frameX = (int)playerX / 100;
    int frameZ = (int)playerZ / 100;

    std::vector<stMapObj> work;
    work = m_stMapObjMap[frameX][frameZ];

    std::vector<stMapObj> work2;
    float r2 = r * r;
    for (int i = 0; i < (int)work.size(); ++i)
    {
        float x3 = work.at(i).m_x;
        float z3 = work.at(i).m_z;
        float r3 = (playerX - x3) * (playerX - x3) + (playerZ - z3) * (playerZ - z3);
        if (r2 > r3)
        {
            work2.push_back(work.at(i));
        }
    }

    return work2;
}

void NSStarmanLib::MapObjManager::GetMapObjListShow(const float playerX,
                                                    const float playerZ,
                                                    std::vector<stMapObj>* needShow)
{
    needShow->clear();

    std::vector<stMapObj> work = GetMapObjList(playerX, playerZ);

    for (int i = 0; i < (int)work.size(); ++i)
    {
        if (work.at(i).m_show == false && work.at(i).m_visible)
        {
            needShow->push_back(work.at(i));
        }
    }
}

void NSStarmanLib::MapObjManager::GetMapObjListHide(const float playerX,
                                                    const float playerZ,
                                                    std::vector<stMapObj>* needHide)
{
    int frameX = (int)playerX / 100;
    int frameZ = (int)playerZ / 100;

    // �`��͈͊O�I�u�W�F�N�g�ɂ��ẮA�v���C���[�̂���i�q�������ꂽ�i�q�������ׂ�΂悢�C������
    // ������������������������
    // ������������������������
    // ������������������������ (1)
    // ������������������������ (2)
    // ������������������������ (3)
    // ������������������������ (4)
    // ������������������������ (5)
    // ������������������������
    //
    // �؂�؂����Ƃ��Ŗ؂��\���ɂ������ꍇ�ɂ��ẮA�v���C���[�Ƃ��̎���ɂ��Ē��ׂ�
    // ��������������������
    // �������������������� (6)
    // �������������������� (7)
    // �������������������� (8)
    // ��������������������

    struct XZ
    {
        int x = 0;
        int z = 0;
    };
    std::vector<XZ> target;
    XZ xz;

    // (1)
    xz.z = frameZ + 2;

    xz.x = frameX - 2;
    target.push_back(xz);

    xz.x = frameX - 1;
    target.push_back(xz);

    xz.x = frameX;
    target.push_back(xz);

    xz.x = frameX + 1;
    target.push_back(xz);

    xz.x = frameX + 2;
    target.push_back(xz);

    // (2)
    xz.z = frameZ + 1;
    xz.x = frameX - 2;
    target.push_back(xz);

    xz.x = frameX + 2;
    target.push_back(xz);

    // (3)
    xz.z = frameZ;
    xz.x = frameX - 2;
    target.push_back(xz);

    xz.x = frameX + 2;
    target.push_back(xz);

    // (4)
    xz.z = frameZ - 1;
    xz.x = frameX - 2;
    target.push_back(xz);

    xz.x = frameX + 2;
    target.push_back(xz);

    // (5)
    xz.z = frameZ - 2;

    xz.x = frameX - 2;
    target.push_back(xz);

    xz.x = frameX - 1;
    target.push_back(xz);

    xz.x = frameX;
    target.push_back(xz);

    xz.x = frameX + 1;
    target.push_back(xz);

    xz.x = frameX + 2;
    target.push_back(xz);

    for (int i = 0; i < (int)target.size(); ++i)
    {
        int x = target.at(i).x;
        int z = target.at(i).z;
        std::vector<stMapObj> list = m_stMapObjMap[x][z];
        for (int j = 0; j < (int)list.size(); ++j)
        {
            if (list.at(j).m_show)
            {
                needHide->push_back(list.at(j));
            }
        }
    }

    target.clear();

    // (6)
    xz.z = frameZ + 1;
    xz.x = frameX - 1;
    target.push_back(xz);

    xz.z = frameZ + 1;
    xz.x = frameX;
    target.push_back(xz);

    xz.z = frameZ + 1;
    xz.x = frameX + 1;
    target.push_back(xz);

    // (7)
    xz.z = frameZ;
    xz.x = frameX - 1;
    target.push_back(xz);

    xz.z = frameZ;
    xz.x = frameX;
    target.push_back(xz);

    xz.z = frameZ;
    xz.x = frameX + 1;
    target.push_back(xz);

    // (8)
    xz.z = frameZ - 1;
    xz.x = frameX - 1;
    target.push_back(xz);

    xz.z = frameZ - 1;
    xz.x = frameX;
    target.push_back(xz);

    xz.z = frameZ - 1;
    xz.x = frameX + 1;
    target.push_back(xz);

    for (int i = 0; i < (int)target.size(); ++i)
    {
        int x = target.at(i).x;
        int z = target.at(i).z;
        std::vector<stMapObj> list = m_stMapObjMap[x][z];
        for (int j = 0; j < (int)list.size(); ++j)
        {
            if (list.at(j).m_show && list.at(j).m_visible == false)
            {
                needHide->push_back(list.at(j));
            }
        }
    }
}

void NSStarmanLib::MapObjManager::SetShow(const int frame_x,
                                          const int frame_z,
                                          const int id,
                                          const bool show)
{
    std::vector<stMapObj>& work = m_stMapObjMap[frame_x][frame_z];
    auto it = std::find_if(work.begin(), work.end(),
                           [&](const stMapObj& item)
                           {
                               return item.m_id == id;
                           });
    if (it == work.end())
    {
        throw std::exception();
    }
    it->m_show = show;
}

void NSStarmanLib::MapObjManager::SetVisible(const int frame_x,
                                             const int frame_z,
                                             const int id,
                                             const bool visible)
{
    std::vector<stMapObj>& work = m_stMapObjMap[frame_x][frame_z];
    auto it = std::find_if(work.begin(), work.end(),
                           [&](const stMapObj& item)
                           {
                               return item.m_id == id;
                           });
    if (it == work.end())
    {
        throw std::exception();
    }
    it->m_visible = visible;
}

std::string NSStarmanLib::MapObjManager::GetModelName(const int id)
{
    return m_XnameMap.at(id);
}

