//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "enemy.h"
#include "enemy2.h"
#include "player.h"
#include "item.h"

//=============================================================================
//エネミークラスのコンストラクタ
//=============================================================================
CEnemy::CEnemy(int nPriority) : CCharacter(nPriority)
{
}

//=============================================================================
//エネミークラスのデストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
//エネミークラスのクリエイト処理
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMY_TYPE type, DEATH_ACTION deathAction)
{
	CEnemy *pEnemy = NULL;

	switch (type)
	{
	case ENEMY_TYPE_NOMRL:
		pEnemy = new CEnemy;
		break;

	case ENEMY_TYPE_NOMRL2:
		pEnemy = new CEnemy2;
		break;
	default:
		break;
	}
	
	if (pEnemy)
	{
		pEnemy->SetPos(pos);
		pEnemy->SetSize(size);
		pEnemy->SetDeathAction(deathAction);
		pEnemy->Init();

	}
	else
	{
		return NULL;
	}
	return pEnemy;
}

//=============================================================================
//エネミークラスの初期化処理
//=============================================================================
HRESULT CEnemy::Init(void)
{
	CScene2D::Init();

	//オブジェクトタイプの設定
	SetObjType(CScene::OBJTYPE_ENEMY);

	SetColor(COLOR_YELLOW);
	return S_OK;
}

//=============================================================================
//エネミークラスの終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//エネミークラスの更新処理
//=============================================================================
void CEnemy::Update(void)
{
	CScene2D::Update();
	CPlayer *pPlayer = NULL;

	//プレイヤーとの当たり判定
	pPlayer = (CPlayer *)JudgeCollision(OBJTYPE_PLAYER, GetPos(), GetSize());

	if (pPlayer)
	{
		SetState(CHARACTER_STATE_DIED);
	}

	//状態判定処理
	CHARACTER_STATE charaState = CheckState();
	
	if (STATE_DEATH(charaState))
	{//死んでいた場合
		return;
	}
}

//=============================================================================
//エネミークラスの描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
//エネミークラスの死亡処理
//死亡時に一回だけ行いたい処理をここに記述
//=============================================================================
void CEnemy::DiedProcess(void)
{
	switch (m_DeathAction)
	{
	case DEATH_ACTION_LIFE:
		CItem::Create(GetPos(),ITEM_SIZE,CItem::ITEM_COIN);
		break;

	default:
		break;
	}
	//終了処理
	Uninit();
}

//=============================================================================
//死亡時処理変数の設定
//=============================================================================
void CEnemy::SetDeathAction(DEATH_ACTION deathAction)
{
	m_DeathAction = deathAction;
}
