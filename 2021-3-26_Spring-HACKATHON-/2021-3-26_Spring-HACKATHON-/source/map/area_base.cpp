#include "area_base.h"
#include "game.h"
#include "player.h"

CAreaBase::CAreaBase()
{
	memset(m_pPolygon, 0, sizeof(m_pPolygon));
}

CAreaBase::~CAreaBase()
{
}

HRESULT CAreaBase::Init(CMap::MAP_AREA Area_Type)
{
	m_Area_Type = Area_Type;

	return E_NOTIMPL;
}

void CAreaBase::Uninit(void)
{
	for (int nCntPoly = 0; nCntPoly < 2; nCntPoly++)
	{
		m_pPolygon[nCntPoly]->Uninit();

		delete m_pPolygon[nCntPoly];

		m_pPolygon[nCntPoly] = NULL;
	}
}

void CAreaBase::Update(void)
{
	for (int nCntPoly = 0; nCntPoly < 2; nCntPoly++)
	{
		m_pPolygon[nCntPoly]->Update();
	}
}

void CAreaBase::Draw(void)
{
	for (int nCntPoly = 0; nCntPoly < 2; nCntPoly++)
	{
		m_pPolygon[nCntPoly]->Draw();
	}
}

bool CAreaBase::Colljon(CPolygon * pPolygon)
{
	CPlayer* pPlayer = CGame::GetPlayer();

	//“–‚½‚è”»’è
	if (pPlayer->GetPos().x + (pPlayer->GetSize().x / 2) >= pPolygon->GetPos().x - (pPolygon->GetSize().x / 2) &&
		pPlayer->GetPos().x - (pPlayer->GetSize().x / 2) <= pPolygon->GetPos().x + (pPolygon->GetSize().x / 2) &&
		pPlayer->GetPos().y + (pPlayer->GetSize().y / 2) >= pPolygon->GetPos().y - (pPolygon->GetSize().y / 2) &&
		pPlayer->GetPos().y - (pPlayer->GetSize().y / 2) <= pPolygon->GetPos().y + (pPolygon->GetSize().y / 2))
	{
		return true;
	}

	return false;
}

void CAreaBase::SetMap(void)
{
}

CMap::MAP_AREA CAreaBase::GetArea(void)
{
	return m_Area_Type;
}
