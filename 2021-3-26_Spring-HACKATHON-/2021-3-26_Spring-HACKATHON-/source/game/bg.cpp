//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define RATE_BG 0.0008f

#define MOVE_VUALE 0.5f



//=============================================================================
//静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG_TEX] = {};	//テクスチャのポインタ

//=============================================================================
//背景クラスのコンストラクタ
//=============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	//0クリア
	m_apScene2D = NULL;
	m_nCounter = 0;
	m_Flag.rot = D3DXVECTOR2(0.0f, 0.0f);
	m_Flag.bScrool = false;
}

//=============================================================================
//背景クラスのデストラクタ
//=============================================================================
CBg::~CBg()
{
}

//=============================================================================
//背景クラスのクリエイト処理
//=============================================================================
CBg * CBg::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//背景クラスのポインタ変数
	CBg *pBg = NULL;

	//インスタンス生成
	pBg = new CBg;

	//メモリが確保できていたら
	if (pBg)
	{
		//背景クラスの初期化処理呼び出し
		pBg->Init();
	}

	return pBg;
}

//=============================================================================
//背景クラスのテクスチャロード処理
//=============================================================================
HRESULT CBg::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pD3DDevice, "data/Texture/BG/map.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pD3DDevice, "data/Texture/BG/mountain.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pD3DDevice, "data/Texture/BG/wood.png", &m_apTexture[2]);

	return S_OK;
}

//=============================================================================
//背景クラスのテクスチャ破棄処理
//=============================================================================
void CBg::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEX; nCount++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCount])
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//背景クラスの初期化処理
//=============================================================================
HRESULT CBg::Init(void)
{

	//2Dポリゴンクラスのインスタンス生成
	m_apScene2D = CScene2D::Create(SCREEN_CENTER_POS, SCREEN_SIZE, CScene::PRIORITY_BG);

	if (m_apScene2D)
	{
		//テクスチャの割り当て
		m_apScene2D->BindTexture(m_apTexture[0]);
	}


	return S_OK;
}

//=============================================================================
//背景クラスの終了処理
//=============================================================================
void CBg::Uninit(void)
{
	if (m_apScene2D)
	{
		m_apScene2D->Uninit();
	}

	//オブジェクトの破棄
	SetDeathFlag();
}

//=============================================================================
//背景クラスの更新処理
//=============================================================================
void CBg::Update(void)
{
	if (m_Flag.bScrool)
	{
		m_nCounter++;

		D3DXVECTOR2 aUVpos[4];
		D3DXVECTOR2 *aUvPosNow = NULL;

		aUvPosNow = m_apScene2D->GetUV();

		for (int nCntScrool = 0; nCntScrool < 4; nCntScrool++)
		{
			aUvPosNow[nCntScrool].x += m_Flag.rot.x * (MOVE_VUALE / TIME_VUALE);
			aUvPosNow[nCntScrool].y += m_Flag.rot.y * (MOVE_VUALE / TIME_VUALE);

			aUVpos[nCntScrool] = aUvPosNow[nCntScrool];
		}
		
		if (m_apScene2D)
		{
			//2DポリゴンクラスのUV座標設定処理呼び出し
			m_apScene2D->SetUV(aUvPosNow);
		}
		if (m_nCounter >= TIME_VUALE)
		{
			m_Flag.bScrool = false;
			m_nCounter = 0;
		}
	}
}

//=============================================================================
//背景クラスの描画処理
//=============================================================================
void CBg::Draw(void)
{
}

void CBg::SetTexPos(D3DXVECTOR2 * pPos)
{
	D3DXVECTOR2 aUVpos[4];

	if (m_apScene2D)
	{
		//UV座標の定義
		aUVpos[0] = pPos[0];
		aUVpos[1] = pPos[1];
		aUVpos[2] = pPos[2];
		aUVpos[3] = pPos[3];

		//2DポリゴンクラスのUV座標設定処理呼び出し
		m_apScene2D->SetUV(aUVpos);
	}
}

void CBg::SetScroolFlag(D3DXVECTOR2 rot)
{
	m_Flag.bScrool = true;

	m_Flag.rot = rot;
}

CBg::SCROOL_FALG CBg::GetScroolFlag(void)
{
	return m_Flag;
}

