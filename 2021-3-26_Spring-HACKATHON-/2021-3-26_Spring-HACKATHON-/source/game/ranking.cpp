//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : Ito Yogo
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include <stdio.h>
#include "ranking.h"
#include "number.h"
#include "scene2d.h"
#include "score.h"
#include "dollar.h"
#include "keyboard.h"
#include "joystick.h"
#include "manager.h"
#include "sound.h"
#include "fade.h"

//=============================================================================
// ランキングクラスのコンストラクタ
//=============================================================================
CRanking::CRanking(int nPriority) :CScene(nPriority)
{
	//各メンバ変数のクリア
	memset(m_apNumber, 0, sizeof(m_apNumber));
	memset(m_nRankingData, 0, sizeof(m_nRankingData));
	m_Rank = RANK_5;
	m_bDown = false;
	m_bEnter = false;
	m_pDllar02 = NULL;
}

//=============================================================================
// ランキングクラスのデストラクタ
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// ランキングクラスのクリエイト処理
//=============================================================================
CRanking * CRanking::Create(void)
{
	// ランキングクラスのポインタ変数
	CRanking *pRanking = NULL;

	// メモリの確保
	pRanking = new CRanking;

	// メモリが確保できていたら
	if (pRanking)
	{
		//初期化処理呼び出し
		pRanking->Init();
	}
	// メモリ確保に失敗した時
	else
	{
		return NULL;
	}

	return pRanking;
}

//=============================================================================
// ランキングクラスの初期化処理
//=============================================================================
HRESULT CRanking::Init(void)
{
	// ファイルの読み込み
	ReadFile();

	// ランキングの更新
	UpdateRanking();

	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_CENTER_POS.x + 500.0f, 600.0f, 0.0f));

	for (int nCountRank = 0; nCountRank < RANKING_MAX_RANK; nCountRank++)
	{
		////ナンバークラスをSCORE_MAX_NUM分生成
		//m_apNumber[nCountRank][0] = CNumber::Create(0, CNumber::NUMBER_TYPE_000,	//表示する数字と種類
		//	D3DXVECTOR3(((SCREEN_WIDTH / 2) - NUMBER_SIZE_X) + (NUMBER_SIZE_X / 2),		//x軸の位置
		//	(NUMBER_SIZE_Y / 2), //yの位置
		//		0.0f),	//zの位置
		//	NUMBER_SIZE, COLOR_WHITE);	//サイズと色

		//for (int nCount = 0; nCount < RANKING_MAX_NUM; nCount++)
		//{
		//	//ナンバークラスをSCORE_MAX_NUM分生成
		//	m_apNumber[nCountRank][nCount] = CNumber::Create(0, CNumber::NUMBER_TYPE_000,	//表示する数字と種類
		//		D3DXVECTOR3(((SCREEN_WIDTH / 2) - (NUMBER_SIZE_X * nCount) + (NUMBER_SIZE_X / 2)),		//x軸の位置
		//		(NUMBER_SIZE_Y / 2), //yの位置
		//			0.0f),	//zの位置
		//		NUMBER_SIZE, COLOR_WHITE);	//サイズと色
		//}

		float fIndex = 0.0f;  //指数　(スコア表示用)
		float fRadix = 10.0f; //基数　(スコア表示用)

		// 数字の設定
		for (fIndex = 0; fIndex < SCORE_MAX_NUM; fIndex++)
		{
			int nScore = (int)powf(fRadix, fIndex);
			int nScore2 = (int)powf(fRadix, fIndex + 1);
			int nAnswer = (m_nRankingData[nCountRank] % nScore2) / nScore;

			if (!m_apNumber[nCountRank][(int)fIndex])
			{
				m_apNumber[nCountRank][(int)fIndex] = CNumber::Create(0, CNumber::NUMBER_TYPE_002,	//表示する数字と種類
					D3DXVECTOR3((SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 8) - ((fIndex * SCORE_SIZE.x)),		//x軸の位置
					(SCORE_SIZE.y / 2) - 200.0f, //yの位置
						0.0f),	//zの位置
					SCORE_SIZE, COLOR_WHITE);	//サイズと色
			}

			if (m_apNumber[nCountRank][(int)fIndex])
			{
				// 各ナンバーのセット
				m_apNumber[nCountRank][(int)fIndex]->SetNumber(nAnswer);
			}
		}

		// 0を消す
		for (int nScoreNum = SCORE_MAX_NUM - 1; 0 < nScoreNum; nScoreNum--)
		{
			int nScore = (int)powf(fRadix, nScoreNum);
			int nScore2 = (int)powf(fRadix, nScoreNum + 1);
			int nAnswer = (m_nRankingData[nCountRank] % nScore2) / nScore;

			if (m_apNumber[nCountRank][nScoreNum] && nAnswer == 0)
			{
				delete m_apNumber[nCountRank][nScoreNum];
				m_apNumber[nCountRank][nScoreNum] = NULL;
			}
			else if (m_apNumber[nCountRank][nScoreNum] && nAnswer != 0)
			{
				break;
			}
		}

		// ランキングのドル
		for (int nCount = SCORE_MAX_NUM - 1; -1 < nCount; nCount--)
		{
			if (m_apNumber[nCountRank][nCount])
			{
				D3DXVECTOR3 pos = m_apNumber[nCountRank][nCount]->GetPos();
				m_pDllar[nCountRank] = CDollar::Create(D3DXVECTOR3(pos.x - 50.0f, pos.y, pos.z));
				break;
			}
		}

		for (int nCount = SCORE_MAX_NUM - 1; -1 < nCount; nCount--)
		{
			if (m_pScore->GetNumber(nCount))
			{
				D3DXVECTOR3 pos = m_pScore->GetNumber(nCount)->GetPos();
				m_pDllar02 = CDollar::Create(D3DXVECTOR3(pos.x - 50.0f, pos.y, pos.z));
				break;
			}
		}
	}
	return S_OK;
}

//=============================================================================
// ランキングクラスの終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	for (int nCountRank = 0; nCountRank < RANKING_MAX_RANK; nCountRank++)
	{
		for (int nCount = 0; nCount < RANKING_MAX_NUM; nCount++)
		{
			if (m_apNumber[nCountRank][nCount])
			{
				//ナンバークラスの終了処理呼び出し
				m_apNumber[nCountRank][nCount]->Uninit();

				//メモリの削除
				delete m_apNumber[nCountRank][nCount];

				//メモリのクリア
				m_apNumber[nCountRank][nCount] = NULL;
			}
		}
	}

	if (m_pScore)
	{
		m_pScore->SetScore(0);
		m_pScore = NULL;
	}

	//オブジェクトの破棄
	SetDeathFlag();
}

//=============================================================================
// ランキングクラスの更新処理
//=============================================================================
void CRanking::Update(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < RANKING_MAX_NUM; nCount++)
	{
		if (m_apNumber[m_Rank][nCount])
		{
			//ナンバークラスの描画処理呼び出し
			pos = m_apNumber[m_Rank][nCount]->GetPos();
			pos += RANKING_MOVE;

			switch (m_Rank)
			{
			case RANK_1:
				if (pos.y >= RANK_1_STOP_POS.y)
				{
					pos.y = RANK_1_STOP_POS.y;
					m_bDown = true;

					//キーボードクラスの情報取得
					CInputKeyboard *pKeyBoard = CManager::GetKeyborad();
					CInputJoyStick *pJoyStick = CManager::GetJoyStick();

					//ENTERキーまたはジョイBが押されてかつm_bEnterがfalseの時
					if ((pKeyBoard->GetKeyBoardRelease(DIK_RETURN) ||
						pJoyStick->GetJoyStickTrigger(CInputJoyStick::JOY_BUTTON_B)) && m_bEnter == false)
					{

						m_bEnter = true;

						//SEを再生
						CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_ENTER);

						//フェード情報を取得
						CFade *pFade = CManager::GetFade();

						if (pFade != NULL)
						{
							//フェードを行う
							pFade->SetFade(CManager::MODE_TYPE_TITLE);
						}

						return;
					}
				}
				break;

			case RANK_2:
				if (pos.y >= RANK_2_STOP_POS.y)
				{
					pos.y = RANK_2_STOP_POS.y;
					m_bDown = true;
				}
				break;

			case RANK_3:
				if (pos.y >= RANK_3_STOP_POS.y)
				{
					pos.y = RANK_3_STOP_POS.y;
					m_bDown = true;
				}
				break;

			case RANK_4:
				if (pos.y >= RANK_4_STOP_POS.y)
				{
					pos.y = RANK_4_STOP_POS.y;
					m_bDown = true;
				}
				break;

			case RANK_5:
				if (pos.y >= RANK_5_STOP_POS.y)
				{
					pos.y = RANK_5_STOP_POS.y;
					m_bDown = true;
				}
				break;

			default:
				break;
			}

			m_apNumber[m_Rank][nCount]->SetPos(pos);
		}


		if (m_bDown == true)
		{
			switch (m_Rank)
			{
			case RANK_1:
				break;

			case RANK_2:
				if (nCount == RANKING_MAX_NUM - 1)
				{
					m_Rank = RANK_1;
					m_bDown = false;
				}
				break;

			case RANK_3:
				if (nCount == RANKING_MAX_NUM - 1)
				{
					m_Rank = RANK_2;
					m_bDown = false;
				}
				break;

			case RANK_4:
				if (nCount == RANKING_MAX_NUM - 1)
				{
					m_Rank = RANK_3;
					m_bDown = false;
				}

				break;

			case RANK_5:
				if (nCount == RANKING_MAX_NUM - 1)
				{
					m_Rank = RANK_4;
					m_bDown = false;
				}
				break;

			default:
				break;
			}
		}
	}

	if (m_pDllar)
	{
		for (int nRank = 0; nRank < RANKING_MAX_RANK; nRank++)
		{
			for (int nCount = SCORE_MAX_NUM - 1; -1 < nCount; nCount--)
			{
				if (m_apNumber[m_Rank][nCount])
				{
					D3DXVECTOR3 pos = m_apNumber[nRank][nCount]->GetPos();
					m_pDllar[nRank]->SetPos(D3DXVECTOR3(pos.x - 50.0f, pos.y, pos.z));
					break;
				}
			}
			m_pDllar[nRank]->Update();
		}
	}

	if (m_pDllar02)
	{
		for (int nCount = SCORE_MAX_NUM - 1; -1 < nCount; nCount--)
		{
			if (m_pScore->GetNumber(nCount))
			{
				D3DXVECTOR3 pos = m_pScore->GetNumber(nCount)->GetPos();
				m_pDllar02->SetPos(D3DXVECTOR3(pos.x - 50.0f, pos.y, pos.z));
				break;
			}
		}

		m_pDllar02->Update();
	}

	if (m_pScore)
	{
		m_pScore->Update();
	}
}

//=============================================================================
// ランキングクラスの描画処理
//=============================================================================
void CRanking::Draw(void)
{
	for (int nCountRank = 0; nCountRank < RANKING_MAX_RANK; nCountRank++)
	{
		for (int nCount = 0; nCount < RANKING_MAX_NUM; nCount++)
		{
			if (m_apNumber[nCountRank][nCount])
			{
				//ナンバークラスの描画処理呼び出し
				m_apNumber[nCountRank][nCount]->Draw();
			}
		}
	}
}

//=============================================================================
// ランキングクラスのランキングの更新
//=============================================================================
void CRanking::UpdateRanking(void)
{
	// スコアの受け取り
	int nScore = CScore::GetScore();
	for (int nCntRank = 0; nCntRank < RANKING_MAX_RANK; nCntRank++)
	{
		// 受け取ったスコアがファイルの中のスコアより多いとき
		if (m_nRankingData[nCntRank] <= nScore)
		{
			// 4位からカウントする
			for (int nCount = RANKING_MAX_RANK - 1; nCount > nCntRank; nCount--)
			{
				// ひとつ前の配列に時間と名前を上書きする
				m_nRankingData[nCount] = m_nRankingData[nCount - 1];
			}

			// 空いたnCntRank番目に受け取ったスコアを入れる
			m_nRankingData[nCntRank] = nScore;

			// 順位の代入
			m_nRank = nCntRank;

			// ファイルの書きこみ
			WriteFile();
			break;
		}
	}
}

//=============================================================================
// ランキングクラスのファイル読み込み
//=============================================================================
void CRanking::ReadFile(void)
{
	FILE *pFile;
	pFile = fopen("data/Text/ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int nCountRank = 0; nCountRank < RANKING_MAX_RANK; nCountRank++)
		{
			fscanf(pFile, "%d", &m_nRankingData[nCountRank]);
		}
		fclose(pFile);
	}
}

//=============================================================================
// ランキングクラスのファイル書き込み
//=============================================================================
void CRanking::WriteFile(void)
{
	FILE *pFile;
	pFile = fopen("data/Text/ranking.txt", "w");

	if (pFile != NULL)
	{
		for (int nCountRank = 0; nCountRank < RANKING_MAX_RANK; nCountRank++)
		{
			fprintf(pFile, "%d\n", m_nRankingData[nCountRank]);
		}
		fclose(pFile);
	}
}