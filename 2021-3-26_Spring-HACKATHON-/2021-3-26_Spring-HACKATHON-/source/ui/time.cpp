//=============================================================================
//
// タイム処理 [time.cpp]
// Author : Ito Yogo
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "time.h"
#include "number.h"
#include "scene2d.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CTime::m_nTime = 0;

//=============================================================================
// タイムクラスのコンストラクタ
//=============================================================================
CTime::CTime(int nPriority) :CScene(nPriority)
{
	//各メンバ変数のクリア
	memset(m_apNumber, 0, sizeof(m_apNumber));
}

//=============================================================================
// タイムクラスのデストラクタ
//=============================================================================
CTime::~CTime()
{
}

//=============================================================================
// タイムクラスのクリエイト処理
//=============================================================================
CTime * CTime::Create(void)
{
	//スコアクラスのポインタ変数
	CTime *pTime = NULL;

	//メモリの確保
	pTime = new CTime;

	//メモリが確保できていたら
	if (pTime)
	{
		//初期化処理呼び出し
		pTime->Init();
	}

	//メモリ確保に失敗した時
	else
	{
		return NULL;
	}

	return pTime;
}

//=============================================================================
// タイムクラスの初期化処理
//=============================================================================
HRESULT CTime::Init(void)
{
	m_nTime = 5400;

	for (int nCount = 0; nCount < TIME_MAX_NUM; nCount++)
	{
		//ナンバークラスをSCORE_MAX_NUM分生成
		m_apNumber[nCount] = CNumber::Create(0, CNumber::NUMBER_TYPE_001,	//表示する数字と種類
			D3DXVECTOR3(((SCREEN_WIDTH / 2) - (NUMBER_SIZE_X * nCount) + (NUMBER_SIZE_X / 2)),		//x軸の位置
			(NUMBER_SIZE_Y / 2), //yの位置
				0.0f),	//zの位置
			NUMBER_SIZE, COLOR_WHITE);	//サイズと色
	}

	// タイマーの数値を秒に変換
	int nTimeSec = m_nTime / 60;
	int nTimeMin = 0;

	float fIndex;			//指数　(タイム表示用)
	float fRadix = 10.0f;	//基数　(タイム表示用)

	for (fIndex = 0; fIndex < TIME_MAX_NUM; fIndex++)
	{
		//各桁の値を求める
		int nScore = (int)powf(fRadix, fIndex);
		int nScore2 = (int)powf(fRadix, fIndex + 1);
		int nAnswer = (nTimeSec % nScore2) / nScore;

		if (m_apNumber[(int)fIndex])
		{
			//数字の設定
			m_apNumber[(int)fIndex]->SetNumber(nAnswer);
		}
	}

	return S_OK;
}

//=============================================================================
// タイムクラスの終了処理
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCount = 0; nCount < TIME_MAX_NUM; nCount++)
	{
		if (m_apNumber[nCount])
		{
			//ナンバークラスの終了処理呼び出し
			m_apNumber[nCount]->Uninit();

			//メモリの削除
			delete m_apNumber[nCount];

			//メモリのクリア
			m_apNumber[nCount] = NULL;
		}
	}

	//オブジェクトの破棄
	SetDeathFlag();
}

//=============================================================================
// タイムクラスの更新処理
//=============================================================================
void CTime::Update(void)
{
}

//=============================================================================
// タイムクラスの描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCount = 0; nCount < TIME_MAX_NUM; nCount++)
	{
		if (m_apNumber[nCount])
		{
			//ナンバークラスの描画処理呼び出し
			m_apNumber[nCount]->Draw();
		}
	}
}

//=============================================================================
// タイムクラスのタイム減算処理
//=============================================================================
void CTime::SubTime()
{
	//タイムの減算
	m_nTime--;

	// タイマーの数値を秒に変換
	int nTimeSec = m_nTime / 60;
	int nTimeMin = 0;

	float fIndex;			//指数　(タイム表示用)
	float fRadix = 10.0f;	//基数　(タイム表示用)

	for (fIndex = 0; fIndex < TIME_MAX_NUM; fIndex++)
	{
		//各桁の値を求める
		int nScore = (int)powf(fRadix, fIndex);
		int nScore2 = (int)powf(fRadix, fIndex + 1);
		int nAnswer = (nTimeSec % nScore2) / nScore;

		if (m_apNumber[(int)fIndex])
		{
			//数字の設定
			m_apNumber[(int)fIndex]->SetNumber(nAnswer);
		}
	}

	if (m_nTime < 0)
	{
		m_nTime = 0;
	}
}

//=============================================================================
// タイムクラスのタイム取得処理
//=============================================================================
int CTime::GetTime(void)
{
	return m_nTime;
}