//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "character.h"

//=============================================================================
//エネミークラス
//=============================================================================
class CEnemy : public CCharacter
{
public:
	typedef enum
	{
		ENEMY_TYPE_NOMRL = 0,
		ENEMY_TYPE_NOMRL2,
	}ENEMY_TYPE;

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CEnemy(int nPriority = PRIORITY_ENEMY);
	~CEnemy();

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMY_TYPE type);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void DiedProcess(void);
private:
};
#endif // !_ENEMY_H_
