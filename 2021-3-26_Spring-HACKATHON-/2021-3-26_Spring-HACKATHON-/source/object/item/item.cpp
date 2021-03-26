//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "score.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define POINT_DIAMOND 1		// コインのポイント値
#define POINT_TREASURE 5	// 宝のポイント値
#define POINT_DOUBLE 2

//=============================================================================
//アイテムクラスのコンストラクタ
//=============================================================================
CItem::CItem()
{
	m_nPoint = 0;
}

//=============================================================================
//アイテムクラスのデストラクタ
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
//アイテムクラスのクリエイト処理
//=============================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ITEM type)
{
	CItem *pItem = new CItem;

	if (pItem)
	{
		pItem->SetPos(pos);
		pItem->SetSize(size);
		pItem->m_Item = type;
		pItem->Init();
	}
	else
	{
		return NULL;
	}
	return pItem;
}

//=============================================================================
//アイテムクラスの初期化処理
//=============================================================================
HRESULT CItem::Init(void)
{
	//CScene2Dの初期化
	CScene2D::Init();

	// アイテムのポイント値初期化
	switch (m_Item)
	{
	// コイン
	case ITEM_DIAMOND:
		m_nPoint = POINT_DIAMOND;
		break;
	// 宝
	case ITEM_TREASURE:
		m_nPoint = POINT_TREASURE;
	default:
		break;
	}

	SetColor(COLOR_BLUE);
	return S_OK;
}

//=============================================================================
//アイテムクラスの終了処理
//=============================================================================
void CItem::Uninit(void)
{
	//CScene2Dの終了
	CScene2D::Uninit();
}

//=============================================================================
//アイテムクラスの更新処理
//=============================================================================
void CItem::Update(void)
{
	//CScene2Dの更新
	CScene2D::Update();

	CPlayer *pPlayer = NULL;

	CScore *pScore = NULL;

	//プレイヤーとの当たり判定
	pPlayer = (CPlayer *)JudgeCollision(OBJTYPE_PLAYER, GetPos(), GetSize());

	
	if (pPlayer)
	{
		// アイテムの効果
		switch (m_Item)
		{
		// トラップの場合
		case ITEM_TRAP:
			pPlayer->OnTrapFlag();
			break;

		// ダイヤの場合
		case ITEM_DIAMOND:
			if (pScore)
			{
				pScore->AddScore(m_nPoint);
				DoubleScore();
			}
			break;

		// 宝の場合
		case ITEM_TREASURE:
			if (pScore)
			{
				pScore->AddScore(m_nPoint);
				DoubleScore();
			}
		default:
			break;
		}
		//終了する
		Uninit();
	}
}

//=============================================================================
//アイテムクラスの描画処理
//=============================================================================
void CItem::Draw(void)
{
	//CScene2Dの描画
	CScene2D::Draw();
}

//=============================================================================
//二倍になる処理
//=============================================================================
void CItem::DoubleScore(void)
{
	CScore *pScore = NULL;
	if (pScore)
	{
		pScore->AddScore(m_nPoint * POINT_DOUBLE);
	}
}
