//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "character.h"

//=============================================================================
//プレイヤークラス
//=============================================================================
class CPlayer :public CCharacter
{
public:
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CPlayer(int nPriority = PRIORITY_PLAYER);
	~CPlayer();

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Move(void);
	void MoveLimit(D3DXVECTOR3 *pPos);
	void Damage(const int nDamage);
	void Recovery(const int nRecovery);
	void DiedProcess(void);

	void OnTrapFlag(void) { m_bTrapFlag = true; } // トラップフラグon
	void MoveSpeedDown(void);
	void AddItemCount(void);
#ifdef _DEBUG
	void DebugDataPrint(void);
#endif
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXVECTOR3 m_move;	//移動量
	int m_nItemCount;	//アイテム取得数
	int m_nCount;
	bool m_bTrapFlag;
};
#endif // !_PLAYER_H_