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
	CPlayer(int nPriority = PRIORITY_PLAYER);
	~CPlayer();

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Move(void);
	void Damage(const int nDamage);
	void DiedProcess(void);
private:
};
#endif // !_PLAYER_H_