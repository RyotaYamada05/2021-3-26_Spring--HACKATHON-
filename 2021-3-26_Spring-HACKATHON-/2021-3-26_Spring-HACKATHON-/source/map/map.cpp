//=============================================================================
//
// マップ処理 [map.h]
// Author : 山田陵太
//
//=============================================================================
#include "map.h"
#include "game.h"
#include "player.h"
#include "area1.h"
#include "area2.h"
#include "area3.h"
#include "area4.h"
#include "manager.h"
#include "keyboard.h"

CAreaBase *CMap::m_pArea[MAP_AREA_MAX] = {};
CMap::MAP_AREA CMap::m_MapIndex = MAP_AREA_1;

//=============================================================================
//マップクラスのコンストラクタ
//=============================================================================
CMap::CMap()
{
	memset(m_pArea, 0, sizeof(m_pArea));
	m_MapIndex = MAP_AREA_1;
}

//=============================================================================
//マップクラスのデストラクタ
//=============================================================================
CMap::~CMap()
{
}

//=============================================================================
//マップクラスの初期化
//=============================================================================
HRESULT CMap::Init(void)
{
	if (!m_pArea[MAP_AREA_1])
	{
		m_pArea[MAP_AREA_1] = new CArea1;
		if (m_pArea[MAP_AREA_1])
		{
			m_pArea[MAP_AREA_1]->Init(MAP_AREA_1);
		}
	}

	if (!m_pArea[MAP_AREA_2])
	{
		m_pArea[MAP_AREA_2] = new CArea2;
		if (m_pArea[MAP_AREA_2])
		{
			m_pArea[MAP_AREA_2]->Init(MAP_AREA_2);
		}
	}
	
	if (!m_pArea[MAP_AREA_3])
	{
		m_pArea[MAP_AREA_3] = new CArea3;
		if (m_pArea[MAP_AREA_3])
		{
			m_pArea[MAP_AREA_3]->Init(MAP_AREA_3);
		}
	}
	
	if (!m_pArea[MAP_AREA_4])
	{
		m_pArea[MAP_AREA_4] = new CArea4;
		if (m_pArea[MAP_AREA_4])
		{
			m_pArea[MAP_AREA_4]->Init(MAP_AREA_4);
		}
	}

	return S_OK;
}

//=============================================================================
//マップクラスの終了
//=============================================================================
void CMap::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAP_AREA_MAX; nCnt++)
	{
		if (m_pArea[nCnt])
		{
			m_pArea[nCnt]->Uninit();
			delete m_pArea[nCnt];
			m_pArea[nCnt] = NULL;
		}
	}
}

//=============================================================================
//マップクラスの更新
//=============================================================================
void CMap::Update(void)
{
	for (int nCnt = 0; nCnt < MAP_AREA_MAX; nCnt++)
	{
		if (m_pArea[nCnt])
		{
			m_pArea[nCnt]->Update();
		}
	}

	if (CManager::GetKeyborad()->GetKeyBoardTrigger(DIK_1))
	{
		SetMapIndex(MAP_AREA_1);
	}
	if (CManager::GetKeyborad()->GetKeyBoardTrigger(DIK_2))
	{
		SetMapIndex(MAP_AREA_2);
	}
	if (CManager::GetKeyborad()->GetKeyBoardTrigger(DIK_3))
	{
		SetMapIndex(MAP_AREA_3);
	}
	if (CManager::GetKeyborad()->GetKeyBoardTrigger(DIK_4))
	{
		SetMapIndex(MAP_AREA_4);
	}
}

//=============================================================================
//マップクラスの描画
//=============================================================================
void CMap::Draw(void)
{
	for (int nCnt = 0; nCnt < MAP_AREA_MAX; nCnt++)
	{
		if (m_pArea[nCnt])
		{
			m_pArea[nCnt]->Draw();
		}
	}
}

CMap::MAP_AREA CMap::GetIndex(void)
{
	return m_MapIndex;
}

void CMap::SetMapIndex(const MAP_AREA index)
{
	m_MapIndex = index;
	m_pArea[m_MapIndex]->SetMap();

}

void CMap::SetMap(void)
{

}
