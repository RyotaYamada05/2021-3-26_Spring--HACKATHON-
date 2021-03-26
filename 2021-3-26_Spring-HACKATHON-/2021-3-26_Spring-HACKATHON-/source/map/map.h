//=============================================================================
//
// マップ処理 [map.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
class CAreaBase;
class CBg;

//=============================================================================
//マップクラス
//=============================================================================
class CMap
{
public:
	typedef enum
	{
		MAP_AREA_1 = 0,
		MAP_AREA_2,
		MAP_AREA_3,
		MAP_AREA_4,
		MAP_AREA_MAX
	}MAP_AREA;

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CMap();
	~CMap();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	static MAP_AREA GetIndex(void);
	static void SetMapIndex(const MAP_AREA index);
	static CBg * GetBg(void);
	virtual void SetMap(void);


	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
private:
	static MAP_AREA m_MapIndex;	//マップ番号
	static CAreaBase *m_pArea[MAP_AREA_MAX];
	static CBg *m_pBg;
};
#endif