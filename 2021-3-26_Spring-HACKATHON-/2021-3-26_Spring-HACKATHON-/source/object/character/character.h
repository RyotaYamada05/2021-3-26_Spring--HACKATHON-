//=============================================================================
//
// キャラクター処理 [character.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene2d.h"
#define DEATH(bDeath)(((bool)(bDeath)) == true)

//=============================================================================
//キャラクタークラス
//=============================================================================
class CCharacter :public CScene2D
{
public:
	//=========================================================================
	//キャラクターの状態
	//=========================================================================
	typedef enum
	{
		CHARACTER_STATE_NORMAL = 0,	//通常状態
		CHARACTER_STATE_DAMAGE,	//被弾状態
		CHARACTER_STATE_DIED,	//死亡状態
		CHARACTER_STATE_MAX,
	}CHARACTER_STATE;

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CCharacter(int nPriority);
	~CCharacter();
	bool CheckState(void);
	void SetState(CHARACTER_STATE state);
	CHARACTER_STATE GetState(void);
	virtual void DiedProcess(void) = 0;
	void AddLife(const int nAddValue);
	void SubLife(const int nSubValue);
	void SetLife(const int nLife);
	int GetLife(void);

	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
protected:
	CHARACTER_STATE m_state;	//状態

private:
	int m_nLife;	//体力
	int m_nStateCounter;		//状態カウンター
};
#endif