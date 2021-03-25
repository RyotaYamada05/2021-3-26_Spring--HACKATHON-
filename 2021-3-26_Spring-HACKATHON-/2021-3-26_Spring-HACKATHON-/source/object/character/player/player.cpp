//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "debugfont.h"
#include "game.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MOVE_VALUE 5.0f			//移動量
#define INERTIA_CONSTANT 0.15f	//慣性の定数
#define MAX_PLAYER_LIFE	50		//プレイヤーの最大体力

//=============================================================================
//プレイヤークラスのコンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority):CCharacter(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nItemCount = 0;
}

//=============================================================================
//プレイヤークラスのデストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
//プレイヤークラスのクリエイト処理
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンス生成
	CPlayer *pPlayer = new CPlayer;

	if (pPlayer)
	{
		pPlayer->SetPos(pos);
		pPlayer->SetSize(size);
		pPlayer->Init();
	}
	return pPlayer;
}

//=============================================================================
//プレイヤークラスの初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//体力の設定（初期化では現在ライフも最大と同値で初期化する）
	SetMaxLife(MAX_PLAYER_LIFE);
	SetLife(MAX_PLAYER_LIFE);

	//CScene2Dの初期化
	CScene2D::Init();

	//オブジェクトタイプの設定
	SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//=============================================================================
//プレイヤークラスの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	//CScene2Dの終了処理
	CScene2D::Uninit();
}

//=============================================================================
//プレイヤークラスの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	//移動処理
	Move();

#ifdef _DEBUG
	if (CManager::GetKeyborad()->GetKeyBoardTrigger(DIK_NUMPAD2))
	{
		Damage(10);
	}
	if (CManager::GetKeyborad()->GetKeyBoardTrigger(DIK_NUMPAD7))
	{
		SubLife(1);
	}
	if (CManager::GetKeyborad()->GetKeyBoardTrigger(DIK_NUMPAD8))
	{
		SetLife(0);
	}
	if (CManager::GetKeyborad()->GetKeyBoardTrigger(DIK_NUMPAD9))
	{
		AddLife(1);
	}
#endif

	//CScene2Dの更新処理
	CScene2D::Update();

	CHARACTER_STATE charaState = CheckState();
	//状態判定処理
	if (STATE_DEATH(charaState))
	{//死んでいた場合
		return;
	}

#ifdef _DEBUG
	DebugDataPrint();
#endif
}

//=============================================================================
//プレイヤークラスの描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	//CScene2Dの描画処理
	CScene2D::Draw();
}

//=============================================================================
//プレイヤークラスの移動処理
//=============================================================================
void CPlayer::Move(void)
{
	//位置を取得
	D3DXVECTOR3 pos = GetPos();

	if (CManager::GetKeyborad()->GetKeyBoardPress(DIK_W))
	{
		m_move.y = -MOVE_VALUE;
	}
	if (CManager::GetKeyborad()->GetKeyBoardPress(DIK_S))
	{
		m_move.y = MOVE_VALUE;
	}
	if (CManager::GetKeyborad()->GetKeyBoardPress(DIK_A))
	{
		m_move.x = -MOVE_VALUE;
	}
	if (CManager::GetKeyborad()->GetKeyBoardPress(DIK_D))
	{
		m_move.x = MOVE_VALUE;
	}
	
	//慣性の処理
	m_move.x += (0.0f - m_move.x) * INERTIA_CONSTANT;
	m_move.y += (0.0f - m_move.y) * INERTIA_CONSTANT;

	//位置に移動量を与える
	pos += m_move;

	//移動制限
	MoveLimit(&pos);

	//位置を設定
	SetPos(pos);
}

//=============================================================================
//プレイヤークラスの移動範囲の制限処理
//=============================================================================
void CPlayer::MoveLimit(D3DXVECTOR3 *pPos)
{
	//サイズの取得
	D3DXVECTOR3 size = GetSize();

	
	//プレイヤーが画面外へ行かないようにする処理
	if (pPos->x + (size.x / 2) >= SCREEN_WIDTH)
	{
		pPos->x = SCREEN_WIDTH - (size.x / 2);
	}
	if (pPos->x - (size.x / 2) <= 0)
	{
		pPos->x = 0 + size.x / 2;
	}
	if (pPos->y + (size.y / 2) >= SCREEN_HEIGHT)
	{
		pPos->y = SCREEN_HEIGHT - (size.y / 2);
	}
	if (pPos->y - (size.y / 2) <= 0)
	{
		pPos->y = 0 + size.y / 2;
	}
}

//=============================================================================
//プレイヤークラスのダメージ処理
//=============================================================================
void CPlayer::Damage(const int nDamage)
{
	if (STATE_NORMAL(GetState()))
	{
		//HPを減らす
		SubLife(nDamage);

		//体力が0以下になったら死亡
		if (GetLife() <= 0)
		{
			//死亡状態へ移行
			SetState(CHARACTER_STATE_DIED);
		}
		else
		{
			//ダメージ状態へ移行
			SetState(CHARACTER_STATE_DAMAGE);
		}
	}
}

//=============================================================================
//プレイヤークラスの体力回復処理
//=============================================================================
void CPlayer::Recovery(const int nRecovery)
{
	AddLife(nRecovery);
}

//=============================================================================
//プレイヤークラスの死亡処理
//死亡時に一回だけ行いたい処理をここに記述
//=============================================================================
void CPlayer::DiedProcess(void)
{
	//終了処理
	Uninit();

	//ゲームモードをゲームオーバー状態へ移行
	CGame::SetGameState(CGame::GAME_STATE_GAME_OVER);
}

//=============================================================================
//プレイヤークラスのアイテム取得数の加算処理
//=============================================================================
void CPlayer::AddItemCount(void)
{
	m_nItemCount++;
}

#ifdef _DEBUG
//=============================================================================
//プレイヤークラスのデバッグ情報の表示処理
//デバッグ情報の表示を取りまとめる関数
//=============================================================================
void CPlayer::DebugDataPrint(void)
{
	CDebugFont::Print(CDebugFont::DEBUG_LAYER_LEFT, "プレイヤーの現在HP:%d\n", GetLife());
	CDebugFont::Print(CDebugFont::DEBUG_LAYER_LEFT, "プレイヤーの最大HP:%d\n", GetMaxLife());
	CDebugFont::Print(CDebugFont::DEBUG_LAYER_LEFT, "プレイヤーの位置X:%0.2f\n", GetPos().x);
	CDebugFont::Print(CDebugFont::DEBUG_LAYER_LEFT, "プレイヤーの位置Y:%0.2f\n", GetPos().y);
	CDebugFont::Print(CDebugFont::DEBUG_LAYER_LEFT, "プレイヤーのアイテム取得数:%d\n", m_nItemCount);
}
#endif