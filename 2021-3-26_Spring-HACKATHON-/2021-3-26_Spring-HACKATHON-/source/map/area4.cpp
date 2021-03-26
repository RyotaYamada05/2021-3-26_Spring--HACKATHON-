#include "area4.h"
#include "debugfont.h"
#include "game.h"
#include "bg.h"
#include "manager.h"
#include "keyboard.h"
#include "map.h"
#include  "player.h"


#define MAP_AREA4_TOP_LEFT D3DXVECTOR2(0.5f,0.5f)
#define MAP_AREA4_TOP_RIGHT D3DXVECTOR2(1.0f,0.5f)
#define MAP_AREA4_UNDER_LEFT D3DXVECTOR2(0.5f,1.0f)
#define MAP_AREA4_UNDER_RIGHT D3DXVECTOR2(1.0f,1.0f)

CArea4::CArea4()
{
}

CArea4::~CArea4()
{
}

HRESULT CArea4::Init(CMap::MAP_AREA m_Area_Type)
{
	CAreaBase::Init(m_Area_Type);
	m_pPolygon[0] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + 100.0f/2, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CPolygon::TEX_TYPE_DOOR_TOP);
	m_pPolygon[1] = CPolygon::Create(D3DXVECTOR3(0.0f + 100.0f / 2, SCREEN_HEIGHT / 2, 0.0f ), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CPolygon::TEX_TYPE_DOOR_LEFT);
	return E_NOTIMPL;
}

void CArea4::Uninit(void)
{
	CAreaBase::Uninit();
}

void CArea4::Update(void)
{

	if (CMap::GetIndex() == m_Area_Type)
	{
		CBg::SCROOL_FALG ScFlag = CMap::GetBg()->GetScroolFlag();

		if (!ScFlag.bScrool)
		{
			if (Colljon(m_pPolygon[0]))
			{
				CMap::GetBg()->SetScroolFlag(SCROOL_UP);

				CMap::SetMapIndex(CMap::MAP_AREA_2);
			}
			if (Colljon(m_pPolygon[1]))
			{
				CMap::GetBg()->SetScroolFlag(SCROOL_LEFT);

				CMap::SetMapIndex(CMap::MAP_AREA_3);
			}
		}
	}
	CAreaBase::Update();
}

void CArea4::Draw(void)
{
	if (CMap::GetIndex() == m_Area_Type)
	{
		CAreaBase::Draw();
	}
}

void CArea4::SetMap(void)
{
	D3DXVECTOR2 pos[4];
	pos[0] = MAP_AREA4_TOP_LEFT;
	pos[1] = MAP_AREA4_TOP_RIGHT;
	pos[2] = MAP_AREA4_UNDER_LEFT;
	pos[3] = MAP_AREA4_UNDER_RIGHT;

	CMap::GetBg()->SetTexPos(pos);
}
