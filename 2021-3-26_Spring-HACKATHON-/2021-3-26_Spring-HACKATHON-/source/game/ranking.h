//=============================================================================
//
// ランキングクラス処理 [ranking.h]
// Author : Ito Yogo
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define RANKING_MAX_RANK (5)	// ランキングの順位
#define RANKING_MAX_NUM (8)		// ランキングの桁数
#define RANKING_MOVE (D3DXVECTOR3(0.0f, 5.0f, 0.0f))		// ランキングの移動量
#define RANK_1_STOP_POS (D3DXVECTOR3(0.0f, 180.0f, 0.0f))		// ランキングの移動量
#define RANK_2_STOP_POS (D3DXVECTOR3(0.0f, 270.0f, 0.0f))		// ランキングの移動量
#define RANK_3_STOP_POS (D3DXVECTOR3(0.0f, 360.0f, 0.0f))		// ランキングの移動量
#define RANK_4_STOP_POS (D3DXVECTOR3(0.0f, 450.0f, 0.0f))		// ランキングの移動量
#define RANK_5_STOP_POS (D3DXVECTOR3(0.0f, 540.0f, 0.0f))		// ランキングの移動量

//=============================================================================
// 前方宣言
//=============================================================================
class CNumber;
class CDollar;
class CScore;

//=============================================================================
// タイムクラスクラス
//=============================================================================
class CRanking : public CScene
{
public:
	typedef enum 
	{
		RANK_1 = 0,
		RANK_2,
		RANK_3,
		RANK_4,
		RANK_5,
	}RANK;

	//=========================================================================
	// メンバ関数宣言
	//=========================================================================
	CRanking(int nPriority = CScene::PRIORITY_UI);
	~CRanking();

	static CRanking *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void UpdateRanking(void);
	void ReadFile(void);
	void WriteFile(void);

private:
	//=========================================================================
	// メンバ変数宣言
	//=========================================================================
	CNumber *m_apNumber[RANKING_MAX_RANK][RANKING_MAX_NUM];	// ナンバークラスポインタ
	CScore *m_pScore;	//スコアのポインタ変数
	int m_nRankingData[RANKING_MAX_RANK];					// ランキングのデータ
	int m_nRank;											// 自分の順位
	bool m_bDown;
	bool m_bEnter;
	RANK m_Rank;
	CDollar *m_pDllar[RANKING_MAX_RANK];
	CDollar *m_pDllar02;
};
#endif 