#include "MapObjManager.h"
#include "HeaderOnlyCsv.hpp"
#include <algorithm>
#include "CaesarCipher.h"

NSStarmanLib::MapObjManager* NSStarmanLib::MapObjManager::obj = nullptr;

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

void NSStarmanLib::MapObj::SetFilename(const std::string& arg)
{
	m_filename = arg;
}

std::string NSStarmanLib::MapObj::GetFilename() const
{
	return m_filename;
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

void NSStarmanLib::MapObj::SetRotX(const float arg)
{
	m_xRot = arg;
}

float NSStarmanLib::MapObj::GetRotX() const
{
	return m_xRot;
}

void NSStarmanLib::MapObj::SetRotY(const float arg)
{
	m_yRot = arg;
}

float NSStarmanLib::MapObj::GetRotY() const
{
	return m_yRot;
}

void NSStarmanLib::MapObj::SetRotZ(const float arg)
{
	m_zRot = arg;
}

float NSStarmanLib::MapObj::GetRotZ() const
{
	return m_zRot;
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

NSStarmanLib::MapObjManager* NSStarmanLib::MapObjManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new MapObjManager();
    }
    return obj;
}

void NSStarmanLib::MapObjManager::Init(const std::string& csvfile,
									   const bool decrypt)
{
    std::vector<std::vector<std::string>> vss;

	if (decrypt == false)
	{
		vss = csv::Read(csvfile);
	}
	else
	{
		std::string work = CaesarCipher::DecryptFromFile(csvfile);
		vss = csv::ReadFromString(work);
	}

    for (std::size_t i = 1; i < vss.size(); ++i)
    {
        MapObj mapObj;

        mapObj.SetId(std::stoi(vss.at(i).at(0)));

        mapObj.SetFilename(vss.at(i).at(1));

		float work = 0.f;

		work = std::stof(vss.at(i).at(2));
        mapObj.SetX(work);

		int frameX = (int)work / 100;
        mapObj.SetFrameX(frameX);

		work = std::stof(vss.at(i).at(3));
        mapObj.SetY(work);

		work = std::stof(vss.at(i).at(4));
        mapObj.SetZ(work);

		int frameZ = (int)work / 100;
        mapObj.SetFrameZ(frameZ);

		work = std::stof(vss.at(i).at(5));
        mapObj.SetRotX(work);

		work = std::stof(vss.at(i).at(6));
        mapObj.SetRotY(work);

		work = std::stof(vss.at(i).at(7));
        mapObj.SetRotZ(work);

		work = std::stof(vss.at(i).at(8));
        mapObj.SetScale(work);

		if (vss.at(i).at(9) == "○")
		{
			mapObj.SetVisible(true);
		}
		else
		{
			mapObj.SetVisible(false);
		}

        m_mapObjMap[frameX][frameZ].push_back(mapObj);
    }
}

void NSStarmanLib::MapObjManager::Save(const std::string& csvfile,
									   const bool encrypt)
{
    std::vector<MapObj> work;

    for (auto itX = m_mapObjMap.begin(); itX != m_mapObjMap.end(); ++itX)
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
              [](const MapObj& x1, const MapObj& x2)
              {
                  return x1.GetId() < x2.GetId();
              });

    std::vector<std::vector<std::string> > vss;
    std::vector<std::string> vs;
    std::string work_str;

    vs.clear();
    vs.push_back("ID");
    vs.push_back("モデル名");
    vs.push_back("X");
    vs.push_back("Y");
    vs.push_back("Z");
    vs.push_back("RotX");
    vs.push_back("RotY");
    vs.push_back("RotZ");
    vs.push_back("Scale");
    vs.push_back("表示");
    vss.push_back(vs);

    for (int i = 0; i < (int)work.size(); ++i)
    {
		vs.clear();
		vs.push_back(std::to_string(work.at(i).GetId()));
		vs.push_back(work.at(i).GetFilename());
		vs.push_back(std::to_string(work.at(i).GetX()));
		vs.push_back(std::to_string(work.at(i).GetY()));
		vs.push_back(std::to_string(work.at(i).GetZ()));
		vs.push_back(std::to_string(work.at(i).GetRotX()));
		vs.push_back(std::to_string(work.at(i).GetRotY()));
		vs.push_back(std::to_string(work.at(i).GetRotZ()));
		vs.push_back(std::to_string(work.at(i).GetScale()));
        if (work.at(i).GetVisible())
        {
            vs.push_back("○");
        }
        else
        {
            vs.push_back("");
        }

		vss.push_back(vs);
    }

	if (encrypt == false)
	{
		csv::Write(csvfile, vss);
	}
	else
	{
		std::stringstream ss;
		for (std::size_t i = 0; i < vss.size(); ++i)
		{
			for (std::size_t j = 0; j < vss.at(i).size(); ++j)
			{
				ss << vss.at(i).at(j);
				if (j != vss.at(i).size() - 1)
				{
					ss << ",";
				}
			}
			ss << "\n";
		}
		CaesarCipher::EncryptToFile(ss.str(), csvfile);
	}
}

void NSStarmanLib::MapObjManager::Destroy()
{
    delete MapObjManager::obj;
    MapObjManager::obj = nullptr;
}

std::vector<NSStarmanLib::MapObj> NSStarmanLib::MapObjManager::GetMapObjList(const float playerX,
																			 const float playerZ)
{
	std::vector<MapObj> result;
	// プレイヤーのX座標が   0 ~  99 なら格子Xは0
	// プレイヤーのX座標が 100 ~ 199 なら格子Xは1

	int frameX = (int)playerX / 100;
	int frameZ = (int)playerZ / 100;

	std::vector<MapObj> work;
	work = m_mapObjMap[frameX][frameZ];
	result = work;

	//-----------------------------------------------------------------------------
	// 左上、上、右上、左、右、左下、下、右下の格子についても追加
	//-----------------------------------------------------------------------------

	// 左上
	work = m_mapObjMap[frameX-1][frameZ+1];
	result.insert(result.end(), work.begin(), work.end());

	// 上
	work = m_mapObjMap[frameX][frameZ+1];
	result.insert(result.end(), work.begin(), work.end());

	// 右上
	work = m_mapObjMap[frameX+1][frameZ+1];
	result.insert(result.end(), work.begin(), work.end());

	// 左
	work = m_mapObjMap[frameX-1][frameZ];
	result.insert(result.end(), work.begin(), work.end());

	// 右
	work = m_mapObjMap[frameX+1][frameZ];
	result.insert(result.end(), work.begin(), work.end());

	// 左下
	work = m_mapObjMap[frameX-1][frameZ-1];
	result.insert(result.end(), work.begin(), work.end());

	// 下
	work = m_mapObjMap[frameX][frameZ-1];
	result.insert(result.end(), work.begin(), work.end());

	// 右下
	work = m_mapObjMap[frameX+1][frameZ-1];
	result.insert(result.end(), work.begin(), work.end());

	return result;
}

void NSStarmanLib::MapObjManager::GetMapObjListShow(const float playerX,
													const float playerZ,
													std::vector<MapObj>* needShow)
{
	needShow->clear();

	std::vector<MapObj> work = GetMapObjList(playerX, playerZ);

	for (int i = 0; i < (int)work.size(); ++i)
	{
		if (work.at(i).GetShow() == false && work.at(i).GetVisible())
		{
			needShow->push_back(work.at(i));
		}
	}
}

void NSStarmanLib::MapObjManager::GetMapObjListHide(const float playerX,
													const float playerZ,
													std::vector<MapObj>* needHide)
{
	int frameX = (int)playerX / 100;
	int frameZ = (int)playerZ / 100;

	// 描画範囲外オブジェクトについては、プレイヤーのいる格子から二つ離れた格子だけ調べればよい気がする
	// □□□□□□□□□□□□
	// □□□□□□□□□□□□
	// □□□■■■■■□□□□ (1)
	// □□□■□□□■□□□□ (2)
	// □□□■□★□■□□□□ (3)
	// □□□■□□□■□□□□ (4)
	// □□□■■■■■□□□□ (5)
	// □□□□□□□□□□□□
	//
	// 木を切ったとかで木を非表示にしたい場合については、プレイヤーとその周りについて調べる
	// □□□□□□□□□□
	// □□□■■■□□□□ (6)
	// □□□■★■□□□□ (7)
	// □□□■■■□□□□ (8)
	// □□□□□□□□□□

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
		std::vector<MapObj> list = m_mapObjMap[x][z];
		for (int j = 0; j < (int)list.size(); ++j)
		{
			if (list.at(j).GetShow())
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
		std::vector<MapObj> list = m_mapObjMap[x][z];
		for (int j = 0; j < (int)list.size(); ++j)
		{
			if (list.at(j).GetShow() && list.at(j).GetVisible() == false)
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
	std::vector<MapObj>& work = m_mapObjMap[frame_x][frame_z];
	auto it = std::find_if(work.begin(), work.end(),
						   [&](const MapObj& item)
						   {
							   return item.GetId() == id;
						   });
	if (it == work.end())
	{
		throw std::exception();
	}
	it->SetShow(show);
}

void NSStarmanLib::MapObjManager::SetVisible(const int frame_x,
											 const int frame_z,
											 const int id,
											 const bool visible)
{
	std::vector<MapObj>& work = m_mapObjMap[frame_x][frame_z];
	auto it = std::find_if(work.begin(), work.end(),
						   [&](const MapObj& item)
						   {
							   return item.GetId() == id;
						   });
	if (it == work.end())
	{
		throw std::exception();
	}
	it->SetVisible(visible);
}

