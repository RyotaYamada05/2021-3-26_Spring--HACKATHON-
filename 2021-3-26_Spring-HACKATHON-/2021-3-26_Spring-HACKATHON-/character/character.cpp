//=============================================================================
//
// キャラクター処理 [character.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "character.h"

//=============================================================================
//キャラクタークラスのコンストラクタ
//=============================================================================
CCharacter::CCharacter(int nPriority) : CScene2D(nPriority)
{
	//メンバ変数の初期化
	m_state = CHARACTER_STATE_NORMAL;
	m_nStateCounter = 0;
}

//=============================================================================
//キャラクタークラスのデストラクタ
//=============================================================================
CCharacter::~CCharacter()
{
}

//=============================================================================
//キャラクタークラスの状態判定処理
//=============================================================================
bool CCharacter::DecisionState(void)
{
	switch (m_state)
	{
	//通常状態
	case CHARACTER_STATE_NORMAL:
		break;

	//ダメージを受けた状態
	case CHARACTER_STATE_DAMAGE:
		SetColor(COLOR_ALPHA);

		m_nStateCounter++;

		if (m_nStateCounter >= 30)
		{
			SetColor(COLOR_WHITE);
			m_nStateCounter = 0;

			m_state = CHARACTER_STATE_NORMAL;
		}
		else if (m_nStateCounter % 10 <= 5)
		{
			SetColor(COLOR_ALPHA);
		}
		else
		{
			SetColor(COLOR_WHITE);
		}
		break;

	//死んでいる状態
	case CHARACTER_STATE_DIED:

		//死亡処理実行
		DiedProcess();

		return true;
		break;
	}

	return false;
}

//=============================================================================
//キャラクタークラスの状態設定処理
//=============================================================================
void CCharacter::SetState(CHARACTER_STATE state)
{
	m_state = state;
}

//=============================================================================
//キャラクタークラスの状態取得処理
//=============================================================================
CCharacter::CHARACTER_STATE CCharacter::GetState(void)
{
	return m_state;
}