#include "area3.h"
#include "debugfont.h"
#include "game.h"
#include "bg.h"
#include "manager.h"
#include "keyboard.h"
#include "map.h"
#include  "player.h"

#define MAP_AREA3_TOP_LEFT D3DXVECTOR2(0.0f,0.5f)
#define MAP_AREA3_TOP_RIGHT D3DXVECTOR2(0.5f,0.5f)
#define MAP_AREA3_UNDER_LEFT D3DXVECTOR2(0.0f,1.0f)
#define MAP_AREA3_UNDER_RIGHT D3DXVECTOR2(0.5f,1.0f)

CArea3::CArea3()
{
}

CArea3::~CArea3()
{
}

HRESULT CArea3::Init(CMap::MAP_AREA m_Area_Type)
{
	CAreaBase::Init(m_Area_Type);
	m_pPolygon[0] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH /2, 0.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f), CPolygon::TEX_TYPE_DOOR);
	m_pPolygon[1] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f), CPolygon::TEX_TYPE_DOOR);
	return E_NOTIMPL;
}

void CArea3::Uninit(void)
{
	CAreaBase::Uninit();
}

void CArea3::Update(void)
{
	CDebugFont::Print(CDebugFont::DEBUG_LAYER_RIGHT, "AREA3ƒNƒ‰ƒX\n");

	if (CMap::GetIndex() == m_Area_Type)
	{
		if (Colljon(m_pPolygon[0]))
		{
			CMap::SetMapIndex(CMap::MAP_AREA_1);
		}
		if (Colljon(m_pPolygon[1]))
		{
			CMap::SetMapIndex(CMap::MAP_AREA_4);
		}
	}
	CAreaBase::Update();
}

void CArea3::Draw(void)
{
	if (CMap::GetIndex() == m_Area_Type)
	{
		CAreaBase::Draw();
	}
}

void CArea3::SetMap(void)
{
	D3DXVECTOR2 pos[4];
	pos[0] = MAP_AREA3_TOP_LEFT;
	pos[1] = MAP_AREA3_TOP_RIGHT;
	pos[2] = MAP_AREA3_UNDER_LEFT;
	pos[3] = MAP_AREA3_UNDER_RIGHT;

	CGame::GetBg()->SetTexPos(pos);
}
