#include "enemy2.h"

CEnemy2::CEnemy2(int nPriority):CEnemy(nPriority)
{ 

}

CEnemy2::~CEnemy2()
{
}

HRESULT CEnemy2::Init(void)
{
	CEnemy::Init();
	SetColor(COLOR_RED);
	return S_OK;
}

void CEnemy2::Uninit(void)
{
	CEnemy::Uninit();
}

void CEnemy2::Update(void)
{
	CEnemy::Update();

	SetColor(COLOR_RED);
}

void CEnemy2::Draw(void)
{
	CEnemy::Draw();
}
