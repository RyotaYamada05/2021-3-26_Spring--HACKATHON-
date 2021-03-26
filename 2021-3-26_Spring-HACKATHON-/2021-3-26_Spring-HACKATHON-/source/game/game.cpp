//=============================================================================
//
// ゲーム処理処理 [game.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "scene2d.h"
#include "fade.h"
#include "manager.h"
#include "sound.h"
#include "debugfont.h"
#include "player.h"
#include "item.h"
#include "enemy.h"
#include "ui.h"
#include "polygon.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define WAIT_SCENE_CHANGE_TIME 360	//シーン切り替えの待機時間

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CGame::GAME_STATE CGame::m_state = CGame::GAME_STATE_NOMRAL;
CPolygon * CGame::m_pPolygon = NULL;

//=============================================================================
//ゲームクラスのコンストラクタ
//=============================================================================
CGame::CGame(int nPriority) :CScene(nPriority)
{
	m_nEnemyCounter = 0;
	m_nStaeCounter = 0;
	m_pUi = NULL;
}

//=============================================================================
//ゲームクラスのデストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
//ゲームクラスのクリエイト処理
//=============================================================================
CGame * CGame::Create(void)
{
	//ゲームクラスのポインタ変数
	CGame *pGame = NULL;

	//メモリの確保
	pGame = new CGame;

	//メモリが確保できていたら
	if (pGame)
	{
		//初期化処理呼び出し
		pGame->Init();
	}
	//メモリ確保に失敗したとき
	else
	{
		return NULL;
	}

	return pGame;
}

//=============================================================================
//ゲームクラスの初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	m_state = CGame::GAME_STATE_NOMRAL;

	// 背景クラスの生成
	CBg::Create();

	//BGMの再生
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);
	
	//UIクラスのインスタンス生成
	m_pUi = new CUi;

	if (FAILED(m_pUi->Init()))
	{
		return -1;
	}

	//プレイヤーの生成
	CPlayer::Create(SCREEN_CENTER_POS, D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//アイテムの生成
	CItem::Create(D3DXVECTOR3(200.0f, 200.0f, 0.0f), ITEM_SIZE);

	//エネミーの生成
	CEnemy::Create(D3DXVECTOR3(500.0f, 200.0f, 0.0f), ITEM_SIZE, CEnemy::ENEMY_TYPE_NOMRL,CEnemy::DEATH_ACTION_LIFE);

	CEnemy::Create(D3DXVECTOR3(900.0f, 500.0f, 0.0f), ITEM_SIZE, CEnemy::ENEMY_TYPE_NOMRL2);

	return S_OK;
}

//=============================================================================
//ゲームクラスの終了処理
//=============================================================================
void CGame::Uninit(void)
{
	if (m_pUi)
	{
		//UIクラスの終了処理呼び出し
		m_pUi->Uninit();

		//メモリの削除
		delete m_pUi;

		//メモリのクリア
		m_pUi = NULL;
	}
	if (m_pPolygon)
	{
		//ポリゴンクラスの終了処理呼び出し
		m_pPolygon->Uninit();

		//メモリの削除
		delete m_pPolygon;

		//メモリのクリア
		m_pPolygon = NULL;
	}

	//オブジェクトの破棄
	SetDeathFlag();
}

//=============================================================================
//ゲームクラスの更新処理
//=============================================================================
void CGame::Update(void)
{	
	switch (m_state)
	{
	case GAME_STATE_NOMRAL:
		m_nEnemyCounter++;

		
		break;

	//ボス戦開始処理
	case GAME_STATE_BOSS_START:
		
		
		break;

	case GAME_STATE_GAME_CLEAR:
	case GAME_STATE_GAME_OVER:
		if (m_nStaeCounter == WAIT_SCENE_CHANGE_TIME)
		{
			CManager::GetFade()->SetFade(CManager::MODE_TYPE_RESULT);
			CManager::GetSound()->Stop();
		}

		//ステートカウントアップ
		m_nStaeCounter++;

		break;
	}

	if (m_pPolygon)
	{
		//ポリゴンクラスの更新処理呼び出し
		m_pPolygon->Update();
	}

	if (m_pUi)
	{
		//UIクラスの更新処理呼び出し
		m_pUi->Update();
	}
}

//=============================================================================
//ゲームクラスの描画処理
//=============================================================================
void CGame::Draw(void)
{
	if (m_pPolygon)
	{
		//ポリゴンクラスの描画処理呼び出し
		m_pPolygon->Draw();
	}
}

//=============================================================================
//ゲームクラスの状態設定処理
//=============================================================================
void CGame::SetGameState(const GAME_STATE state)
{
	m_state = state;

	switch (m_state)
	{
	//ボス戦開始前処理
	case GAME_STATE_BOSS_START:
	
		break;

	//ボス戦
	case GAME_STATE_BOSS_BATTLE:
		
		break;

	//ゲームクリア
	case GAME_STATE_GAME_CLEAR:
		
		break;

	//ゲームオーバー
	case GAME_STATE_GAME_OVER:

		//BGMの停止
		CManager::GetSound()->Stop();

		//GAME_OVER用のSEを再生
		CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_GAME_OVER);
		if (!m_pPolygon)
		{
			//ゲームオーバー表示のポリゴン生成
			m_pPolygon = CPolygon::Create(SCREEN_CENTER_POS, D3DXVECTOR3(600.0f, 200.0f, 0.0f),
				CPolygon::TEX_TYPE_GAME_OVER);
		}
		break;

	default:
		break;
	}
}

//=============================================================================
//ゲームクラスの状態取得処理
//=============================================================================
CGame::GAME_STATE CGame::GetGameState(void)
{
	return m_state;
}