#include "MapObjManager.h"
#include "HeaderOnlyCsv.hpp"

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

NSStarmanLib::MapObjManager* NSStarmanLib::MapObjManager::GetObj()
{
    if (obj == nullptr)
    {
        obj = new MapObjManager();
    }
    return obj;
}

void NSStarmanLib::MapObjManager::Init(const std::string& csvfile)
{
    std::vector<std::vector<std::string>> vss;
    vss = csv::Read(csvfile);
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

        m_mapObjMap[frameX][frameZ].push_back(mapObj);
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
		if (work.at(i).GetShow() == false)
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

	// プレイヤーのいる格子から二つ離れた格子だけ調べればよい気がする
	// □□□□□□□□□□□□
	// □□□□□□□□□□□□
	// □□□■■■■■□□□□ (1)
	// □□□■□□□■□□□□ (2)
	// □□□■□★□■□□□□ (3)
	// □□□■□□□■□□□□ (4)
	// □□□■■■■■□□□□ (5)
	// □□□□□□□□□□□□

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
}

void NSStarmanLib::MapObjManager::SetShow(const int frame_x,
										  const int frame_Z,
										  const int id,
										  const bool show)
{
	std::vector<MapObj>& work = m_mapObjMap[frame_x][frame_Z];
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
