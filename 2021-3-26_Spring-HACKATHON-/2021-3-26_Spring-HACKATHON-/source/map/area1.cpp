#include "area1.h"
#include "debugfont.h"
#include "game.h"
#include "bg.h"
#include "manager.h"
#include "keyboard.h"
#include "map.h"
#include  "player.h"
#include "item.h"


#define MAP_AREA1_TOP_LEFT D3DXVECTOR2(0.0f,0.0f)
#define MAP_AREA1_TOP_RIGHT D3DXVECTOR2(0.5,0.0f)
#define MAP_AREA1_UNDER_LEFT D3DXVECTOR2(0.0f,0.5f)
#define MAP_AREA1_UNDER_RIGHT D3DXVECTOR2(0.5f,0.5f)

CArea1::CArea1()
{
	
}

CArea1::~CArea1()
{
}

HRESULT CArea1::Init(CMap::MAP_AREA m_Area_Type)
{
	CAreaBase::Init(m_Area_Type);
	m_pPolygon[0] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH -100.0f/2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CPolygon::TEX_TYPE_DOOR_RGIHT);
	m_pPolygon[1] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100.0f / 2, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CPolygon::TEX_TYPE_DOOR_UNDER);
	
	//ƒAƒCƒeƒ€‚Ì¶¬
	CItem::Create(D3DXVECTOR3(200.0f, 200.0f, 0.0f), ITEM_SIZE, CItem::ITEM_DIAMOND);

	return E_NOTIMPL;
}

void CArea1::Uninit(void)
{
	CAreaBase::Uninit();
}

void CArea1::Update(void)
{
	
	if (CMap::GetIndex() == m_Area_Type)
	{
		CBg::SCROOL_FALG ScFlag = CMap::GetBg()->GetScroolFlag();
		if (!ScFlag.bScrool)
		{
			if (Colljon(m_pPolygon[0]))
			{
				CMap::GetBg()->SetScroolFlag(SCROOL_RGHIT);
				CMap::SetMapIndex(CMap::MAP_AREA_2);
			}
			if (Colljon(m_pPolygon[1]))
			{
				CMap::GetBg()->SetScroolFlag(SCROOL_DOWN);
				CMap::SetMapIndex(CMap::MAP_AREA_3);
			}
		}
	}

	CAreaBase::Update();

}

void CArea1::Draw(void)
{
	if (CMap::GetIndex() == m_Area_Type)
	{
		CAreaBase::Draw();
	}
}

void CArea1::SetMap(void)
{
	D3DXVECTOR2 pos[4];
	pos[0] = MAP_AREA1_TOP_LEFT;
	pos[1] = MAP_AREA1_TOP_RIGHT;
	pos[2] = MAP_AREA1_UNDER_LEFT;
	pos[3] = MAP_AREA1_UNDER_RIGHT;

	CMap::GetBg()->SetTexPos(pos);
}

void CArea1::SetMapStart(void)
{
	D3DXVECTOR2 pos[4];
	pos[0] = MAP_AREA1_TOP_LEFT;
	pos[1] = MAP_AREA1_TOP_RIGHT;
	pos[2] = MAP_AREA1_UNDER_LEFT;
	pos[3] = MAP_AREA1_UNDER_RIGHT;

	CMap::GetBg()->SetTexPos(pos);
}
