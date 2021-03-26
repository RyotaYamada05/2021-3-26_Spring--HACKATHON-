//=============================================================================
//
// 背景処理 [bg.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_BG_TEX 3	//背景数
#define MAX_2D_NUM 3	//2Dポリゴンの数
#define BG_SIZE D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f)	//背景サイズ

#define SCROOL_DOWN D3DXVECTOR2(0.0f,1.0f)
#define SCROOL_UP D3DXVECTOR2(0.0f,-1.0f)
#define SCROOL_LEFT D3DXVECTOR2(-1.0f,0.0f)
#define SCROOL_RGHIT D3DXVECTOR2(1.0f,0.0f)
#define TIME_VUALE 50
//=============================================================================
//前方宣言
//=============================================================================
class CScene2D;

//=============================================================================
//背景クラス
//=============================================================================
class CBg : public CScene
{
public:
	typedef struct
	{
		bool bScrool;
		D3DXVECTOR2 rot;
	}SCROOL_FALG;
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CBg(int nPriority = CScene::PRIORITY_BG);
	~CBg();

	static CBg *Create(const D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 
		const D3DXVECTOR3 size = BG_SIZE);
	static HRESULT Load(void);
	static void UnLoad(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTexPos(D3DXVECTOR2 *pPos);
	void SetScroolFlag(D3DXVECTOR2 rot);
	SCROOL_FALG GetScroolFlag(void);

private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEX];
	CScene2D *m_apScene2D;
	D3DXVECTOR2 m_pMoveValue[4];
	int m_nCounter;
	SCROOL_FALG m_Flag;
};
#endif