#pragma once

#include <string>
#include <vector>
#include <unordered_map>

// およそ100メートル以内の3Dモデルの情報を返す。
// 1秒に一回くらい呼ばれる想定
namespace NSStarmanLib
{

class MapObj
{
public:

	void SetId(const int id);
	int GetId() const;

	void SetFrameX(const int x);
	int GetFrameX() const;

	void SetFrameZ(const int z);
	int GetFrameZ() const;

	void SetFilename(const std::string& arg);
	std::string GetFilename() const;

	void SetX(const float arg);
	float GetX() const;

	void SetY(const float arg);
	float GetY() const;

	void SetZ(const float arg);
	float GetZ() const;

	void SetRotX(const float arg);
	float GetRotX() const;

	void SetRotY(const float arg);
	float GetRotY() const;

	void SetRotZ(const float arg);
	float GetRotZ() const;

	void SetScale(const float arg);
	float GetScale() const;

	void SetShow(const bool arg);
	bool GetShow() const;

private:

	int m_id = 0;

	int m_frameX = 0;
	int m_frameZ = 0;

	std::string m_filename;

	float m_x = 0.f;
	float m_y = 0.f;
	float m_z = 0.f;

	float m_xRot = 0.f;
	float m_yRot = 0.f;
	float m_zRot = 0.f;

	float m_scale = 0.f;

	bool m_show = false;
};

// 全部調べたら大変負荷が重くなるので100メートルごとの格子を考える。
// マップを100メートルごとの格子で分割し、自分がいる格子とその周りの8つの格子だけを処理する
class MapObjManager
{
public:

    static MapObjManager* GetObj();
    void Init(const std::string& csvfile);
    static void Destroy();

	// 表示すべきオブジェクトを返す
	std::vector<MapObj> GetMapObjList(const float playerX, const float playerZ);

	// 表示すべきなのに表示されていないオブジェクトを返す
	void GetMapObjListShow(const float playerX,
						   const float playerZ,
						   std::vector<MapObj>* needShow);

	// 表示すべきでないのに表示されているオブジェクトを返す
	void GetMapObjListHide(const float playerX,
						   const float playerZ,
						   std::vector<MapObj>* needHide);


	void SetShow(const int frame_x, const int frame_y, const int id, const bool show);

private:

    static MapObjManager* obj;

	// m_mapObjMap[10][20] これは1000m ~ 1100m, 2000m ~ 2100mの範囲の3Ｄモデルのリストを意味する
    std::unordered_map<int, std::unordered_map<int, std::vector<MapObj>>> m_mapObjMap;

	
};

}

