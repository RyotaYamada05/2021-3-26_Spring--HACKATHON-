//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "score.h"
#include "timer.h"
#include "ui.h"
#include "manager.h"

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
	m_nTime = 0;
	m_bflag = false;
	m_nCounter = 0;
	m_fAngle = 0.0f;
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
	if (!m_bflag)
	{
		//CScene2Dの更新
		CScene2D::Update();
		//プレイヤーのポインタ
		CPlayer *pPlayer = NULL;
		//スコアのポインタ
		CScore *pScore = CUi::GetScore();
		//タイムのポインタ
		CTime *pTime = NULL;
		//タイムのカウント情報を取得する
		m_nTime = pTime->GetTime();

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
				if (pScore != NULL)
				{
					//タイムが半分以上の場合
					if (m_nTime >= HALF_TIME)
					{
						pScore->AddScore(m_nPoint);
					}
					//タイムが半分以下の場合
					if (m_nTime <= HALF_TIME)
					{
						DoubleScore();
					}
				}
				break;

				// 宝の場合
			case ITEM_TREASURE:
				if (pScore != NULL)
				{
					//タイムが半分以上の場合
					if (m_nTime >= HALF_TIME)
					{
						pScore->AddScore(m_nPoint);
					}
					//タイムが半分以下の場合
					if (m_nTime <= HALF_TIME)
					{
						DoubleScore();
					}
				}
			default:
				break;
			}
			m_bflag = true;
		}
	}
	else
	{
		if (m_Item == ITEM_DIAMOND)
		{
			m_nCounter++;
			if (m_nCounter == 50)
			{
				float posX = (float)(100 + rand() % 900);
				float posY = (float)(100 + rand() % 500);

				SetPos(D3DXVECTOR3(posX, posY, 0.0f));
			}
			if (m_nCounter >= 120)
			{
				m_nCounter = 0;
				m_bflag = false;
			}
		}

		if (m_Item == ITEM_TREASURE)
		{
			m_nCounter++;
			if (m_nCounter == 50)
			{
				float posX = (float)(100 + rand() % 900);
				float posY = (float)(100 + rand() % 500);

				SetPos(D3DXVECTOR3(posX, posY, 0.0f));
			}
			if (m_nCounter >= 120)
			{
				m_nCounter = 0;
				m_bflag = false;
			}
		}

		if (m_Item == ITEM_TRAP)
		{
			m_nCounter++;
			if (m_nCounter == 50)
			{
				float posX = (float)(100 + rand() % 900);
				float posY = (float)(100 + rand() % 500);

				SetPos(D3DXVECTOR3(posX, posY, 0.0f));
			}
			if (m_nCounter >= 120)
			{
				m_nCounter = 0;
				m_bflag = false;
			}
		}
	}
}

//=============================================================================
//アイテムクラスの描画処理
//=============================================================================
void CItem::Draw(void)
{
	if (!m_bflag)
	{
		//CScene2Dの描画
		CScene2D::Draw();
	}
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
