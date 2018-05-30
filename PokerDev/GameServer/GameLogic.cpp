
#include "TableFrameSink.h"
#include "GameLogic.h"

#include <iostream>
#include <fstream>

#include "PokerDefine.h"
using namespace PokerDef;

extern void TraceMessage(LPCTSTR pszMessage);
extern void TraceMessageDetails(LPCTSTR pszMessage, LPCTSTR pszFile);
namespace nsRouAiRou
{


#ifdef _DEBUG
#define TRUST_TIME				3
#define ROAR_TIME				15
#define PLAY_TIME				20
#define FIRST_START_PLAY_TIME	20
#else
#define TRUST_TIME				3
#define ROAR_TIME				15
#define PLAY_TIME				20
#define FIRST_START_PLAY_TIME	20
#endif


//任务ID定义
#define TASK_HEI_510K		1
#define TASK_HONG_510K		2
#define TASK_MEI_510K		3
#define TASK_FANG_510K		4
#define TASK_4_2			5
#define TASK_4_5			6
#define TASK_4_10			7
#define TASK_4_K			8
#define TASK_DOUBLE_KING	9		// 对王
#define TASK_6_ONESTR		10		// 6连以上的顺子
#define TASK_FIRST_4_STR	11
#define TASK_FIRST_STR_678	12
#define TASK_FIRST_STR_789	13
#define TASK_FIRST_STR_910J	14
#define TASK_FIRST_STR_10JQ	15
#define TASK_FIRST_STR_JQK	16
#define TASK_FIRST_STR_QKA	17
#define TASK_LAST_HEI_510K	18
#define TASK_LAST_HONG_510K	19
#define TASK_LAST_MEI_510K	20
#define TASK_LAST_DOUBLE_5	21		// 对5结尾
#define TASK_LAST_DOUBLE_10	22		// 对10结尾
#define TASK_LAST_DOUBLE_K	23		// 对k结尾
#define TASK_LAST_ONESTR	24		// 任意顺子结尾
#define TASK_LAST_4_STR		25
#define TASK_LAST_STR_678	26
#define TASK_LAST_STR_789	27
#define TASK_LAST_STR_910J	28
#define TASK_LAST_STR_10JQ	29
#define TASK_LAST_STR_JQK	30
#define TASK_LAST_STR_QKA	31
#define TASK_LAST_3			32
#define TASK_YAO_BAI		33

#define TASK_ZHUA_TIAN		34
#define TASK_ZHUA_8_XI		35
#define TASK_ZHUA_7_XI		36

extern string g_strRoomRule;  //房间规则

#define PAI_NUM		1

#define SEND_TABLE_DATA(chair,ID,msg) do{char cbBuffer[SOCKET_PACKET];\
	if (g_iDebug > 200)Sleep(g_iDebug);	\
	memset(cbBuffer, 0, SOCKET_PACKET);\
	bostream bos;\
	bos.attach(cbBuffer, SOCKET_PACKET);\
	bos<<msg;SendTableData(chair,ID,cbBuffer,bos.length());}while(0)

#define SEND_TABLE_DATA_ALL(ID,msg) do{char cbBuffer[SOCKET_PACKET];\
	if (g_iDebug > 200)Sleep(g_iDebug);	\
	memset(cbBuffer, 0, SOCKET_PACKET);\
	bostream bos;\
	bos.attach(cbBuffer, SOCKET_PACKET);\
	bos<<msg;SendTableDataToAll(ID,cbBuffer,bos.length());}while(0)

#define SEND_TABLE_DATA_OTHER(chair,ID,msg) do{char cbBuffer[SOCKET_PACKET];\
	if (g_iDebug > 200)Sleep(g_iDebug);	\
	memset(cbBuffer, 0, SOCKET_PACKET);\
	bostream bos;\
	bos.attach(cbBuffer, SOCKET_PACKET);\
	bos<<msg;SendTableDataToOther(chair,ID,cbBuffer,bos.length());}while(0)


static int g_iDebug = 0;
static int g_iLog = 0;

#define LOGS(chair, msg)	do{\
	if (g_iLog > 0)	\
	{	\
		IServerUserItem* item = GetServerUserItem(chair);	\
		if (item)	\
		{	\
			char fn[64];	\
			memset(fn, 0 ,64);	\
			sprintf(fn, "%d_%d.txt",m_pGameServiceOption->wServerPort,item->GetTableID());	\
			char id[64];	\
			memset(id, 0 ,64);	\
			sprintf(id, "userid=%u", item->GetUserID());	\
			TraceMessageDetails(id, fn);	\
			TraceMessageDetails(msg, fn);	\
		}	\
	}	\
}while(0)

int switchCard2Ox(int _index)
{
	int _hight = (_index-1)/13;
	int _low = (_index-1)%13 +1;

	return( _low + (_hight<<4  ) );
}


//游戏记录
void CGameLogic::OnWriteGameRecord(unsigned int ichair, CString szGameRecord ,const bool bStatus)
{
	if(g_iLog == 0) return;

	//游戏记录
	IServerUserItem *pIServerUserItem = NULL;
	CString szCurrentUser = _T("用户：");

	if (ichair >=0 && ichair< GetPlayerCount())
	{
		if(m_pITableFrame != NULL)
		{
			pIServerUserItem = m_pITableFrame->GetServerUserItem(ichair);
		}
		if(pIServerUserItem != NULL)
		{
			szCurrentUser.AppendFormat("%s",pIServerUserItem->GetAccounts());
		}

	}

	//分步写文件 | 在此修改
	//写入文件
	try
	{
		CFile FileGameRecord;
		const BOOL bOpen = FileGameRecord.Open(m_szNameGameRecord, CFile::modeWrite | CFile::modeNoTruncate | CFile::modeCreate);
		if(bOpen == TRUE)
		{

			SYSTEMTIME sysTime;
			::GetLocalTime(&sysTime);
			CString strCurDate=TEXT("");
			strCurDate = TEXT("");
			strCurDate.Format("%02d%02d",sysTime.wMonth,sysTime.wDay);

			FileGameRecord.SeekToEnd();
			long fsize=FileGameRecord.GetLength();

			//跨天后在新的文件夹继续写日志
			if(strcmp(m_szTimeGameRecord, strCurDate) != 0)
			{
				CreateGameRecordFile(true);
			}
			//不需要太大的日志
			else if (fsize>5*1024*1024)
			{
				//FileGameRecord.SetLength(0);
				CreateGameRecordFile(true);//不清0，下次写在新创建的日志文件
			}

			//SYSTEMTIME sysTime;
			//::GetLocalTime(&sysTime);
			CString strDate=TEXT("");
			strDate.Format("%d/%d/%d %d:%d:%d",sysTime.wYear,sysTime.wMonth,sysTime.wDay,sysTime.wHour,sysTime.wMinute,sysTime.wSecond);

			FileGameRecord.Write(strDate,(UINT)(strlen(strDate)));
			FileGameRecord.Write("\r\n",(UINT)(strlen("\r\n")));

			if(szCurrentUser != "")
			{
				FileGameRecord.Write(szCurrentUser,(UINT)(strlen(szCurrentUser)));
				FileGameRecord.Write("  ",(UINT)(strlen("  ")));
			}

			FileGameRecord.Write(szGameRecord,(UINT)(strlen(szGameRecord)));
			FileGameRecord.Write("\r\n\r\n",(UINT)(strlen("\r\n\r\n")));

			FileGameRecord.Close();
		}
		else
		{
			return ;
		}
	}
	catch(...)
	{

	}

	return ;
}

//创建游戏记录目录
void CGameLogic::CreateGameRecordFile(const bool bStatus)
{
	//生成文件路径
	m_szNameGameRecord = "";

	ASSERT(m_pGameServiceOption != NULL);
	if(m_pGameServiceOption == NULL)
	{
		return ;
	}

	SYSTEMTIME sysTime;
	::GetLocalTime(&sysTime);
	//CString strDate=TEXT("");
	m_szTimeGameRecord = TEXT("");
	m_szTimeGameRecord.Format("%02d%02d",sysTime.wMonth,sysTime.wDay);

	//目录路径
	TCHAR szDirectory[MAX_PATH] = {0};
	::GetCurrentDirectory(DWORD(sizeof(szDirectory)),szDirectory);
	strcat(szDirectory,_T("\\大冶\\"));
	strcat(szDirectory,m_pGameServiceOption->szGameRoomName);
	strcat(szDirectory,_T("\\"));
	strcat(szDirectory,m_szTimeGameRecord);
	strcat(szDirectory,_T("\\"));


	WIN32_FIND_DATA WTF;
	const HANDLE hFind = ::FindFirstFile(szDirectory,&WTF);
	if( !( (hFind != INVALID_HANDLE_VALUE) && (WTF.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) )
	{
		//建立目录
		WORD wDirectoryEnd = 0;
		do
		{
			if(0 == szDirectory[wDirectoryEnd])
			{
				CreateDirectory(szDirectory, NULL);
				break ;
			}
			if('\\' == szDirectory[wDirectoryEnd])
			{
				szDirectory[wDirectoryEnd] = 0;
				CreateDirectory(szDirectory, NULL);
				szDirectory[wDirectoryEnd] = '\\';
			}

			++wDirectoryEnd ;
		}while(1);
	}

	m_szNameGameRecord = szDirectory;

	if(m_pITableFrame != NULL)
	{
		m_szNameGameRecord.AppendFormat("第%d桌日志_%02d%02d",m_pITableFrame->GetTableID() + 1,sysTime.wHour,sysTime.wMinute);
	}

	m_szNameGameRecord.AppendFormat("%s",_T(".txt"));

	return ;
}

CGameLogic::CGameLogic(void)
{
	//初始化下一个庄家位置
	m_nextbanker = 0;

	ProduceCards();

	Reset();

	//初始化谁断线了，牌数，财富数据
	for(int i = 0; i < MAX_PLAYER;i++)
	{
		m_whoBreak[i]  = 0; 
		m_thePaiCount[i] = MAXCARD;
		m_theCanNotOut[i] = 0;
		m_playerrich[i] = 0;

		m_whoTotal8Xi[i]			= 0;
		m_whoTotal7Xi[i]			= 0;
		m_whoTotalGonglong[i]		= 0;
	}
	memset(m_lastScore,0,sizeof(m_lastScore));
	memset(m_total,0,sizeof(m_total));
	memset(m_bUserReady, 0, sizeof(m_bUserReady));

	memset(m_MaxScore,0,sizeof(m_MaxScore));
	memset(m_totalFirstTurn,0,sizeof(m_totalFirstTurn));
	memset(m_totalDuPai,0,sizeof(m_totalDuPai));

	m_cbLeftCardCount = 0;
	m_iCurrentFanShu = 0;
	m_CurCompleteCount = 0;

	m_nPlayTime = PLAY_TIME;
	m_nAutoOutTime = TRUST_TIME;
	m_nTrustCounts      = 5;		// 托管次数

	m_byMaxKingNum = 2;
	m_byFakeKingValue = 3;
	m_byIsShowChardCount = 1;
}


CGameLogic::~CGameLogic(void)
{
	
}

//产生牌数据
void CGameLogic::ProduceCards()
{
	//初始化所有牌点数
	for (int i=0;i< MAX_POKER_COUNTS;i++)
	{
		for(int j = 0;j< PAI_NUM;j++)
			m_dbp[i+j*MAX_POKER_COUNTS] = i+1;
	}

	//初始化所有牌点数，供做牌的时候使用
	for (BYTE i = 0 ; i < ALLCARD ; i++)
	{
		m_tempdbp[i] = m_dbp[i];
	}
}

//定时器事件
bool __cdecl CGameLogic::OnTimerMessage(WORD wTimerID, WPARAM wBindParam)
{
	if (wTimerID == GAME_TIMER)
	{
		if (m_tDownTime > 0 &&
			m_theActionStep > AS_NULL && 
			m_theActionStep < AS_COUNT)
		{
			if (GetCPUTickCount() >= m_tDownTime)
			{
				SetActionStep(m_theActionStep);
			}
		}
	}

	return false;
}

//游戏结束
bool __cdecl CGameLogic::OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	m_pITableFrame->KillGameTimer(GAME_TIMER);
	switch (cbReason)
	{
	case GER_NORMAL:		//常规结束
		{
			return true;
		}
		break;
	case GER_USER_LEFT:
		{
			GameOver(wChairID, GOT_ESCAPE);
			return true;
		}
		break;
	case GER_DISMISS:
		{
			GameOver(wChairID, GOT_DISMISS);
			return true;
		}
		break;
	}

	return false;
}
//用户断线
bool CGameLogic::OnActionUserOffLine(WORD wChairID, IServerUserItem * pIServerUserItem)
{
	if (wChairID >= 0 && wChairID < MAX_PLAYER)
	{
		m_whoBreak[wChairID] = TRUE;
	}

	CString szGameRecord = _T("当前用户：");
	szGameRecord.AppendFormat("掉线");
	OnWriteGameRecord(wChairID,szGameRecord);

	return true;
}

//用户重入
bool CGameLogic::OnActionUserReConnect(WORD wChairID, IServerUserItem * pIServerUserItem)
{
	if (wChairID >= 0 && wChairID < MAX_PLAYER)
	{
		m_whoBreak[wChairID] = FALSE;
	}

	return true;
}

//用户坐下
bool CGameLogic::OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	m_thePlayerState[wChairID] = OX_GS_SITDOWN;

	BYTE byUserCnt = 0;
	for(int seat = 0; seat < MAX_PLAYER; seat++)
	{
		if(m_thePlayerState[seat] != OX_GS_NULL)
			byUserCnt++;
	}
	if(byUserCnt == 1) m_nextbanker = 0;//第一个人进来时要把庄家数据清理

	return true;
}
//用户起来
bool CGameLogic::OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	m_thePlayerState[wChairID] = OX_GS_NULL;

	return true;
}
//用户同意
bool CGameLogic::OnActionUserReady(WORD wChairID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize)
{
	m_thePlayerState[wChairID] = OX_GS_READY;

	return true;
}

bool __cdecl CGameLogic::SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret)
{
	switch (cbGameStatus)
	{
	case GS_FREE:		//空闲状态
		{
			//解析规则
			if (this->m_pITableFrame != NULL && this->m_pITableFrame->GetGameServiceOption() != NULL)
			{
				ParseRule(this->m_pITableFrame->GetGameServiceOption()->szGameRoomRule);
			}

			//构造数据
			CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree,sizeof(StatusFree));

			//游戏变量
			StatusFree.cbStatus=cbGameStatus;
			StatusFree.lCellMinScore=m_pGameServiceOption->lCellScore * m_iBaseScore;
			StatusFree.lCellMaxScore=m_pGameServiceOption->lRestrictScore;

			CMD_CS_GameRule msgRule;
			msgRule.theBase = m_pGameServiceOption->lCellScore * m_iBaseScore;
			msgRule.theSeverCharge = m_spay;
			msgRule.iFaOfTao = m_iFaOfTao;
			msgRule.iJiangOfTao = m_iJiangOfTao;
			msgRule.theMinGameScore = m_pGameServiceOption->lLessScore;//进入房间的最小财富
			msgRule.theMaxGameScore = m_pGameServiceOption->lMaxScore;//进入房间的最大财富
			msgRule.isShowChardCount = m_byIsShowChardCount;
			msgRule.iFakeKingValue = m_byFakeKingValue;
			msgRule.iMaxKingNum = m_byMaxKingNum;
			SEND_TABLE_DATA(wChiarID,SUB_CS_GAMERULE,msgRule);

			//发送场景
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));	
		}
	//case GS_PLAYING:	//游戏状态
	case GS_MJ_PLAY:
		{
			/* 
			这种做法不全面，暂时放弃

			//构造数据
			CMD_S_StatusPlay StatusPlay;
			ZeroMemory(&StatusPlay,sizeof(StatusPlay));

			StatusPlay.cbStatus=cbGameStatus;
			StatusPlay.lCellMinScore=m_pGameServiceOption->lCellScore;
			StatusPlay.lCellMaxScore=m_pGameServiceOption->lRestrictScore;
			
			//发送场景
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));
			*/

			WORD chairID = wChiarID;
			BOOL isReLink = TRUE;//这个现在暂时先写死（后续在考虑看牌的情况）
			

			char buff[16];
			
			bostream bos;
			bos.attach((char*)buff, 16);
			bos << chairID;
			bos << isReLink;

			OnGameAction(SUB_S_RELINK,buff,bos.length(),pIServerUserItem);//视为游戏逻辑消息，交给sendGameStatus去处理
			
			return true;

		}

		
	default :
		return true;
	}
	//效验结果
	ASSERT(FALSE);
	return false;
}

void CGameLogic::SetDebugCard(const string &_file)
{
	TCHAR szPath[MAX_PATH]={0};
	TCHAR szConfigFileName[MAX_PATH];
	GetCurrentDirectory(sizeof(szPath),szPath);
	ZeroMemory(szConfigFileName,sizeof(szConfigFileName));

	sprintf(szConfigFileName,_T("%s\\%s"),szPath, _file);


	int nAble=GetPrivateProfileInt( TEXT("IsAble"), TEXT("able"), 0, szConfigFileName );

	if (nAble == 1)
	{
		TCHAR szCard1[MAX_PATH]={0};
		CString card1 = szCard1;
		int Tempt0[MAXCARD]={0};
		GetPrivateProfileString( TEXT("Card"), TEXT("user1"), TEXT(""), szCard1, MAX_PATH, szConfigFileName );
		card1=szCard1;
		_stscanf(card1,TEXT("0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x"),
			&Tempt0[0],&Tempt0[1],&Tempt0[2],&Tempt0[3],&Tempt0[4],
			&Tempt0[5],&Tempt0[6],&Tempt0[7],&Tempt0[8],&Tempt0[9],
			&Tempt0[10],&Tempt0[11],&Tempt0[12],&Tempt0[13],&Tempt0[14]);

		CString card2;
		TCHAR szCard2[MAX_PATH]={0};
		int Tempt1[MAXCARD]={0};
		GetPrivateProfileString( TEXT("Card"), TEXT("user2"), TEXT(""), szCard2, MAX_PATH, szConfigFileName );
		card2.Format("%s",szCard2);
		_stscanf(card2,TEXT("0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x"),
			&Tempt1[0],&Tempt1[1],&Tempt1[2],&Tempt1[3],&Tempt1[4],
			&Tempt1[5],&Tempt1[6],&Tempt1[7],&Tempt1[8],&Tempt1[9],
			&Tempt1[10],&Tempt1[11],&Tempt1[12],&Tempt1[13],&Tempt1[14]);

		CString card3;
		TCHAR szCard3[MAX_PATH]={0};
		int Tempt2[MAXCARD]={0};
		GetPrivateProfileString( TEXT("Card"), TEXT("user3"), TEXT(""), szCard3, MAX_PATH, szConfigFileName );
		card3.Format("%s",szCard3);
		_stscanf(card3,TEXT("0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x"),
			&Tempt2[0],&Tempt2[1],&Tempt2[2],&Tempt2[3],&Tempt2[4],
			&Tempt2[5],&Tempt2[6],&Tempt2[7],&Tempt2[8],&Tempt2[9],
			&Tempt2[10],&Tempt2[11],&Tempt2[12],&Tempt2[13],&Tempt2[14]);

		CString card4;
		TCHAR szCard4[MAX_PATH]={0};
		int Tempt3[MAXCARD]={0};
		if (GetPlayerCount() >= 4)
		{
			GetPrivateProfileString( TEXT("Card"), TEXT("user4"), TEXT(""), szCard4, MAX_PATH, szConfigFileName );
			card4.Format("%s",szCard4);
			_stscanf(card4,TEXT("0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x"),
				&Tempt3[0],&Tempt3[1],&Tempt3[2],&Tempt3[3],&Tempt3[4],
				&Tempt3[5],&Tempt3[6],&Tempt3[7],&Tempt3[8],&Tempt3[9],
				&Tempt3[10],&Tempt3[11],&Tempt3[12],&Tempt3[13],&Tempt3[14]);
		}

		CString card5;
		TCHAR szCard5[MAX_PATH]={0};
		int Tempt4[MAXCARD]={0};
		if (GetPlayerCount() >= 5)
		{
			GetPrivateProfileString( TEXT("Card"), TEXT("user4"), TEXT(""), szCard5, MAX_PATH, szConfigFileName );
			card5.Format("%s",szCard5);
			_stscanf(card5,TEXT("0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x"),
				&Tempt4[0],&Tempt4[1],&Tempt4[2],&Tempt4[3],&Tempt4[4],
				&Tempt4[5],&Tempt4[6],&Tempt4[7],&Tempt4[8],&Tempt4[9],
				&Tempt4[10],&Tempt4[11],&Tempt4[12],&Tempt4[13],&Tempt4[14]);
		}

		//牌墩的牌
		CString leftcard;
		TCHAR szLeftCard[1024]={0};
		int LeftTempt[104]={0};
		GetPrivateProfileString( TEXT("Card"), TEXT("RepertoryCard"), TEXT(""), szLeftCard, 1024, szConfigFileName );
		leftcard.Format("%s",szLeftCard);
		_stscanf(leftcard,TEXT("0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,\
							   0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,\
							   0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,\
							   0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,\
							   0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,\
							   0x%x,0x%x,0x%x,0x%x"),
							   &LeftTempt[0],&LeftTempt[1],&LeftTempt[2],&LeftTempt[3],&LeftTempt[4],&LeftTempt[5],&LeftTempt[6],&LeftTempt[7],&LeftTempt[8],&LeftTempt[9],
							   &LeftTempt[10],&LeftTempt[11],&LeftTempt[12],&LeftTempt[13],&LeftTempt[14],&LeftTempt[15],&LeftTempt[16],&LeftTempt[17],&LeftTempt[18],&LeftTempt[19],
							   &LeftTempt[20],&LeftTempt[21],&LeftTempt[22],&LeftTempt[23],&LeftTempt[24],&LeftTempt[25],&LeftTempt[26],&LeftTempt[27],&LeftTempt[28],&LeftTempt[29],
							   &LeftTempt[30],&LeftTempt[31],&LeftTempt[32],&LeftTempt[33],&LeftTempt[34],&LeftTempt[35],&LeftTempt[36],&LeftTempt[37],&LeftTempt[38],&LeftTempt[39],
							   &LeftTempt[40],&LeftTempt[41],&LeftTempt[42],&LeftTempt[43],&LeftTempt[44],&LeftTempt[45],&LeftTempt[46],&LeftTempt[47],&LeftTempt[48],&LeftTempt[49],
							   &LeftTempt[50],&LeftTempt[51],&LeftTempt[52],&LeftTempt[53]);

		for (int k=0; k<MAX_PLAYER; k++)
		{
			if (k >= GetPlayerCount() )
			{
				break;
			}
			//for(int i=0; i < MAXCARD;i++)
			for(int i=0; i < FIRSTCARD*3;i++)//虽然理论上一个玩家最多有MAXCARD(27)张牌，当游戏开始时每人只发5张牌
			{
				switch(k){
				case 0:
					m_dbplay[k][i] = getCardIndexByOx(Tempt0[i]);
					break;
				case 1:
					m_dbplay[k][i] = getCardIndexByOx(Tempt1[i]);
					break;
				case 2:
					m_dbplay[k][i] = getCardIndexByOx(Tempt2[i]);
					break;
				case 3:
					m_dbplay[k][i] = getCardIndexByOx(Tempt3[i]);
					break;
				case 4:
					m_dbplay[k][i] = getCardIndexByOx(Tempt4[i]);
					break;
				default:
					break;
				}
			}
		}
		m_cbLeftCardCount = 0;
		for (int i=0;i<ALLCARD;i++)
		{
			if (LeftTempt[i] == 0) break;
			m_dbp[i]=getCardIndexByOx(LeftTempt[i]);
			m_cbLeftCardCount++;
		}
		//根据实际做牌数目来更新每个玩家的牌数
		for(int seat = 0; seat < MAX_PLAYER;seat++)
		{
			m_thePaiCount[seat] = m_dagun.GetCardNum(m_dbplay[seat]);
		}
		m_nextbanker = 1;//做牌时，固定第一个人为庄或开始吼牌
	}
}

int CGameLogic::getCardIndexByOx(BYTE _card)
{
	BYTE low_index = 0x0F;
	BYTE hight_index = 0xF0;

	return( (low_index&_card) + ((hight_index&_card)>>4 )*13 );

}

void CGameLogic::Reset()
{
	InitGame();
	time(&nowTime);
}

void CGameLogic::InitGame()
{
	m_cbGameEndStatus = GS_MJ_FREE;

	for(int i =0;i < MAX_PLAYER;i++)
	{
		//牌数据
		for(int j = 0;j < MAXCARD; j++)
		{
			m_dbplay[i][j]	= 0;
			m_allPaiOutNoMagic[i][j]	= 0;
			m_allPaiOut[i][j]	= 0;
			m_lastPaiOut[i][j]	= 0;
		}
		m_theCanNotOut[i] = 0;
		m_thePaiCount[i] = FIRSTCARD;
		//托管
		m_TrustCounts[i]    = 0;
		m_TuoGuanPlayer[i]	= 0;
		//断线
		m_WireBreakCounts[i] = 0;

		/////////////
		m_thePlayerState[i]		= OX_GS_NULL;

		m_playerscore[i]	= 0;
		m_whoAllOutted[i]	= 0;
		m_whoBreak[i]		= 0;
		m_whoPass[i]		= 0;

		m_playHardBomb[i]		= 0;
		m_playSoftBomb[i]		= 0;
		m_playMagicBomb[i]		= 0;
		m_whoQuanGuan[i]		= 0;
		m_byEveryOneOutCnt[i]	= 0;
		m_byEveryOneCurlunOutCnt[i] = 0;
		m_xiScore[i]		= 0;
	}
	memset(m_OutPaifakeking,0,sizeof(m_OutPaifakeking));
	m_bBaoPei      = 0;
	m_whoHardKill	= 0;
	m_iCurrentFanShu = 0;
	m_cbLeftCardCount = 0;
	m_tDownTime     = 0;
	m_whoplay		= 0;
	m_whoplayout	= 0;
	m_banker		= 0;
	m_nowActionStep = AS_NULL;
	m_theActionStep = AS_NULL;
	m_lastOutType   = TYPE_NULL;
	m_GameState     = gsNull;

	//m_iBaseScore	= 1;//需要发给客户端的全局数据，在reset里面不能初始化，否则在断线重连后每小局的配置不一样
	m_score			= 0;
	m_whoHasKingBomb = 0;//谁有天炸
	srand(time(0));

	m_iJiangOfTao = 5;		//默认值2
	m_iFaOfTao = 10;		//默认值2
	m_iAddSpecailBeishu = 1;//默认值1，改成1倍底
	m_byAddSepcialFlag = 1;	//特殊牌型默认加分

	memset(m_bUserReady, 0, sizeof(m_bUserReady));

	//初始化随机任务
	m_iRandomTask = -1;
	m_bHaveOutCard = false;
	m_mapAllTask.clear();
	m_vecAllTaskID.clear();
	for (int j=0 ; j<MAX_PLAYER ; j++)
	{
		m_vecFinishedTask[j].clear();
	}

// 	//解析游戏规则，格式：n1;v1|n2:v2
// 	vector<string> vecParam;
// 	stovs(g_strRoomRule, "|", vecParam);
// 	for (int i=0; i<vecParam.size(); i++)
// 	{
// 		vector<string> nv;
// 		stovs(vecParam[i], ":", nv);
// 		if (nv.size() == 2)
// 		{
// 			if (nv[0] == "Fa")
// 			{
// 				m_iFaOfTao = atoi(nv[1].c_str());
// 			}
// 			else if (nv[0] == "Jiang")
// 			{
// 				m_iJiangOfTao = atoi(nv[1].c_str());
// 			}
// 			else if (nv[0] == "TaskID")
// 			{
// 				ParseTaskConfig(nv[1].c_str());
// 			}
// 			else if (nv[0] == "D")
// 			{
// 				g_iDebug = atoi(nv[1].c_str());
// 			}
// 			else if (nv[0] == "G")
// 			{
// 				g_iLog = atoi(nv[1].c_str());
// 			}
// 		}
// 	}
}

void CGameLogic::OnGameAction(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	switch(wSubCmdID)
	{
		case SUB_CS_ROAR:	//用户吼牌
			{
				//变量定义
				CMD_Roar_CB roar;
				bistream bis;
				bis.attach((char*)pDataBuffer, wDataSize);
				bis >> roar;

//				SEND_TABLE_DATA_ALL( SUB_CS_ROAR, roar);
				if (g_iLog > 0)
				{
					char buf[64];
					memset(buf, 0 ,64);
					sprintf(buf, "吼牌:theFlag=%d", roar.theFlag);
						
					OnWriteGameRecord(roar.theSeat, buf);
				}

				//逻辑处理
				//OnRoarAction(roar.theSeat, roar.theFlag);
			}
			break;
		case SUB_CS_OUT:	//用户出牌
			{
				//变量定义
				CMD_OutCard_CB outCards;
				bistream bis;
				bis.attach((char*)pDataBuffer, wDataSize);
				bis >> outCards;

				//校验规则
				if(m_GameState != gsPlay)
				{
					char buf[125] = {0};
					sprintf(buf, "%d: 游戏状态不正确", outCards.theSeat);
					TraceMessage(buf);
					return;
				}

				if(outCards.theCount < 0 || outCards.theCount > MAXCARD)
				{//错误
					char buf[125] = {0};
					sprintf(buf, "%d: 出牌数据错误,出牌的长度非法", outCards.theSeat);
					TraceMessage(buf);
					return;
				}

				AutoOutCard(outCards.theSeat, outCards);

	//			m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_CS_OUT, cbBuffer, bos.length());
	//			m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_CS_OUT, cbBuffer, bos.length());

				//for test
				//结束游戏
	//			m_pITableFrame->ConcludeGame();
			}
			break;
		case SUB_S_TUOGUAN: //托管
			{
				//变量定义
				CMD_S_Tuoguan_CB tuoguan;
				bistream bis;
				bis.attach((char*)pDataBuffer, wDataSize);
				bis >> tuoguan;

				//详细日志
				if (g_iLog > 0)
				{
					char buf[128];
					memset(buf, 0 ,128);
					sprintf(buf, "托管： m_whoplay=%d tuoguan.theSeat=%d tuoguan.theFlag=%d", m_whoplay, tuoguan.theSeat,tuoguan.theFlag);
						
					OnWriteGameRecord(tuoguan.theSeat, buf);
				}

				//校验规则
				if((m_GameState == gsPlay) || (m_GameState == gsRoarPai))
				{
					if(tuoguan.theFlag == CMD_S_Tuoguan_CB::T_TUOGUAN)
					{	
						m_TuoGuanPlayer[tuoguan.theSeat] = TRUE;
						m_TrustCounts[tuoguan.theSeat]++;
						if(tuoguan.theSeat + 1  == m_whoplay){
							m_tDownTime = GetCPUTickCount()+m_nAutoOutTime;
						}
						SEND_TABLE_DATA_ALL(SUB_S_TUOGUAN,tuoguan);
					}
					else if(tuoguan.theFlag == CMD_S_Tuoguan_CB::T_NULL){
						time_t now;
						time(&now);
						m_TuoGuanPlayer[tuoguan.theSeat] = FALSE;

						//如果是当前的玩家，那么重新设置一下开始时间
						if(tuoguan.theSeat + 1 == m_whoplay)
						{
							m_tDownTime = m_nPlayTime-(now-nowTime)+GetCPUTickCount();
						}

						tuoguan.theTime = m_nPlayTime-(now-nowTime);
						SEND_TABLE_DATA_ALL(SUB_S_TUOGUAN,tuoguan);
					}
					else 
						return ;
				}
				else
				{
					char buf[125] = {0};
					sprintf(buf, "%d: 游戏状态不正确", tuoguan.theSeat);
					TraceMessage(buf);
					return;
				}
			}
			break;
		case SUB_S_RELINK:
			{			
			    WORD chairID;
				BOOL isReLink;
				bistream bis;
				bis.attach((char*)pDataBuffer, wDataSize);
				bis >> chairID;
				bis >> isReLink;

				//详细日志
				if (g_iLog > 0)
				{
					char buf[128];
					memset(buf, 0 ,128);
					sprintf(buf, "断线重连： chairID=%d isReLink=%d", chairID,isReLink);
						
					OnWriteGameRecord(chairID, buf);
				}

				sendGameStatus(chairID,isReLink,pIServerUserItem);
			}
			break;
		case SUB_C_GOON_NEXT_GAME:
			{
				// 局数校验 大于当前总局数，不处理此消息
				if (m_CurCompleteCount >= m_rule.iJuShu || m_pITableFrame->GetGameStatus() != GS_MJ_PLAY)
				{
					return ;
				}
				//用户效验
				tagServerUserData * pUserData=pIServerUserItem->GetUserData();
				if (pUserData->dwUserID == 0) return ;

				//详细日志
				if (g_iLog > 0)
				{
					CString szGameRecord = _T("当前用户：");
					if(m_pITableFrame != NULL)
					{
						szGameRecord.AppendFormat("%s SUB_C_GOON_NEXT_GAME",pIServerUserItem->GetAccounts());
					}
					OnWriteGameRecord(pUserData->wChairID, szGameRecord);
				}

				//将该消息广播出去。游戏开始后，不用广播
				if (m_cbGameEndStatus != GS_MJ_PLAY)
				{
					//m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_C_GOON_NEXT_GAME,pDataBuffer,wDataSize);
					m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_C_GOON_NEXT_GAME,(void*)pDataBuffer,wDataSize);
					m_pITableFrame->SendUserStatus(pUserData->wChairID, US_READY);  //把我的状态发给其他人
				}
				//SEND_TABLE_DATA(INVALID_CHAIR,SUB_C_GOON_NEXT_GAME,pDataBuffer);
				int nChiarID = pUserData->wChairID;
				if (nChiarID >= 0 && nChiarID < GetPlayerCount())
				{
					m_bUserReady[nChiarID]=true;
				}

				// 如果4个玩家都准备好了，自动开启下一局
				for (int i =0 ;i < GetPlayerCount();++i)
				{		
					if (!m_bUserReady[i])
					{
						break;
					}
					if (i == GetPlayerCount() -1)
					{
						//RepositTableFrameSink();// 复位桌子
						Reset();
						StartNextGame();
					}
				}
			}
			break;
		default:
			break;
	}
}

// 开启下一局
bool CGameLogic::StartNextGame()
{
	m_GameState = gsPlay;
	//避免播放动画时还有人加入，造成发牌,需要一开始就设置为游戏中的状态
	for(int seat = 0; seat < MAX_PLAYER; seat++)
	{
		IServerUserItem * pIServerUserItem = GetServerUserItem(seat);
		if(pIServerUserItem == NULL)
		{
			m_thePlayerState[seat] = OX_GS_NULL;
			continue;
		}
		m_thePlayerState[seat] = OX_GS_PLAYING;
	}

	OnWriteGameRecord(INVALID_CHAIR,_T("开始StartNextGame......"));
	OnWriteGameRecord(INVALID_CHAIR,this->m_pITableFrame->GetGameServiceOption()->szGameRoomRule);

	m_cbGameEndStatus = GS_MJ_PLAY; 
	memset(m_bUserReady, 0, sizeof(m_bUserReady));

	//解析规则
	ParseRule(this->m_pITableFrame->GetGameServiceOption()->szGameRoomRule);

	//详细日志
	if (g_iLog > 0)
	{
		CString szGameRecord = _T("底:");
		szGameRecord.AppendFormat("%d,茶水:%d,底分(客户端配置):%d,是否特殊牌型加分:%d,",m_nBase,m_spay,m_iBaseScore,m_byAddSepcialFlag);
		szGameRecord.AppendFormat("赖子单出算%d,是否显示手牌数目:%d",m_byFakeKingValue,m_byIsShowChardCount);
		OnWriteGameRecord(INVALID_CHAIR, szGameRecord);
	}

	m_pITableFrame->SetGameStatus(GS_MJ_PLAY);
	m_CurCompleteCount++;

	//混乱随机种子
	DWORD _randTmp = (DWORD)time(NULL) + m_pITableFrame->GetTableID() + KIND_ID *100+ m_pITableFrame->GetGameServiceOption()->wSortID*1000;
	srand(_randTmp);
	srand(rand()*10000+((DWORD)time(NULL)));

	int m,n;
	//洗牌
	for(int i=0; i<1000; i++)
	{
		m = div(rand(),ALLCARD).rem;
		n = div(rand(),ALLCARD).rem;
		BYTE zz = m_dbp[m];
		m_dbp[m] = m_dbp[n];
		m_dbp[n] = zz;
	}
	m_cbLeftCardCount = ALLCARD;

	memset(m_dbplay,0,sizeof(m_dbplay));
		
	for(int i=0; i < FIRSTCARD;i++)
	{
		for(int k=0; k < MAX_PLAYER && m_cbLeftCardCount > 0; k++)  //发牌
		{
			IServerUserItem * pIServerUserItem = GetServerUserItem(k);
			if(pIServerUserItem == NULL || m_thePlayerState[k] != OX_GS_PLAYING)
			{
				continue;
			}
			m_dbplay[k][i] = m_dbp[--m_cbLeftCardCount];	
		}
	}
		
	if (g_iDebug > 0)
	{
		SetDebugCard("RouAiRouServer_test.ini");
	}

	//开始新的一局记录
	m_sReplayRecord.reset();

	if(m_nextbanker > 0 && m_nextbanker <= MAX_PLAYER )
	{
		m_whoplay = m_nextbanker;
		for (int iSeat = 0;iSeat < MAX_PLAYER;iSeat++)
		{	
			if(m_thePlayerState[m_whoplay - 1] == OX_GS_PLAYING)
			{
				break;
			}
			m_whoplay = m_whoplay % MAX_PLAYER + 1;
		}
	}
	else
	{
		m_whoplay = GetXianShou();
		//m_whoplay = rand()%MAX_PLAYER + 1;
	}

	m_banker = m_whoplay;

	//记录每个玩家开始游戏时所携带的分数
	for(int seat = 0; seat < MAX_PLAYER; seat++)
	{
		IServerUserItem * pIServerUserItem = m_pITableFrame->GetServerUserItem(seat);
		if(pIServerUserItem == NULL || pIServerUserItem->GetUserScore() == NULL|| m_thePlayerState[seat] != OX_GS_PLAYING)
		{
			continue;
		}
		//写日志记录 每个用户的原始分数
		CString szCardRecord = _T("ID:");
		szCardRecord.AppendFormat("%d,携带分数为:%d ,椅子编号:%d .",pIServerUserItem->GetUserID(),pIServerUserItem->GetUserScore()->lScore,seat);	
		OnWriteGameRecord(seat,szCardRecord);
	}

	CMD_S_GameStart_CB startmsg;

	startmsg.theIsGameStart = TRUE;
	startmsg.theBanker = m_whoplay;
	startmsg.theType = CMD_S_GameStart_CB::GAME_START;
	startmsg.theLeftCardsCount = m_cbLeftCardCount;

	for(int seat = 0; seat < MAX_PLAYER; seat++)
	{
//		m_playerrich[seat] = player->getPlayTypeScore();
		IServerUserItem * pIServerUserItem = m_pITableFrame->GetServerUserItem(seat);
		if(pIServerUserItem == NULL || m_thePlayerState[seat] != OX_GS_PLAYING)
		{
			m_thePaiCount[seat] = 0; //没有游戏的人牌数量为0
			continue;
		}
		const tagUserScore *pUserScore=pIServerUserItem->GetUserScore();
		if(pUserScore /*&& pUserScore->lScore>0*/) 
			m_sReplayRecord.iScore[seat] = pUserScore->lScore;

		startmsg.theSeat = seat;
		startmsg.theCount = m_thePaiCount[seat];
		
		for(int i = 0;i < MAXCARD; i++)
		{
			startmsg.theCards[i] = m_dbplay[startmsg.theSeat][i];
			m_sReplayRecord.vecHandCard[startmsg.theSeat].push_back(m_dbplay[startmsg.theSeat][i]);
		}

		//详细日志
		if (g_iLog > 0)
		{
			CString szGameRecord = _T("发牌后手牌:");
			for(int i = 0;i < MAXCARD; i++)
			{
				//牌型
				if (m_dbplay[startmsg.theSeat][i] > 0)//有效才记录
				{
					szGameRecord.AppendFormat("0x%02x,",switchCard2Ox(m_dbplay[startmsg.theSeat][i]));
				}		
			}
			if (seat + 1 == m_banker)
			{
				szGameRecord.AppendFormat(" 是庄家，先出牌");
			}
			OnWriteGameRecord(startmsg.theSeat, szGameRecord);
		}

		SEND_TABLE_DATA(seat,SUB_S_GAME_START,startmsg);
	}
	CString szGameRecord = _T("牌堆牌:");
	for(int i = 0;i < m_cbLeftCardCount && i < ALLCARD; i++)
	{
		szGameRecord.AppendFormat("0x%02x,",switchCard2Ox(m_dbp[i]));
	}
	OnWriteGameRecord(MAX_PLAYER,szGameRecord);

	SendPaiCount();
	//StartRoar(m_whoplay-1);
	//StartPlay(m_whoplay);
	SetActionStep(AS_GAMESTART, 1);//开始发牌1秒后发送牌权

	//if (m_rule.iJuShu > 0)
	//{
	//	m_pITableFrame->TableHongbaoSet(m_CurCompleteCount);
	//}
	return true;
}
//系统选出场上玩家点数最小的手牌（王和3不参与比较，2最大，4最小；
//点数相同则按照黑桃＞红桃＞草花＞方片比较花色），拥有最小牌的玩家最先出牌，后面每局谁先跑谁先出牌；
BYTE CGameLogic::GetXianShou()
{
	BYTE byXianShou = MAX_PLAYER;
	BYTE byMinCard = 0;
	for(int seat = 0; seat < MAX_PLAYER; seat++)
	{
		IServerUserItem * pIServerUserItem = m_pITableFrame->GetServerUserItem(seat);
		if(pIServerUserItem == NULL || m_thePlayerState[seat] != OX_GS_PLAYING)
		{
			continue;
		}

		BYTE byTempCards[FIRSTCARD]= {0};
		for(int i = 0;i < FIRSTCARD; i++)
		{
			if (m_dagun.IsMagic(m_dbplay[seat][i]))
			{
				byTempCards[i] = CARDINDEX_BIG;
			}
			else byTempCards[i] = m_dbplay[seat][i];
		}
		//排序
		m_dagun.SortByIndex(byTempCards,FIRSTCARD);
		//找到最小的牌，赖子除外
		if (byMinCard == 0)
		{
			byMinCard = byTempCards[0];
			byXianShou = seat;
		}
		else
		{
			if (m_dagun.GetCardLevel(byMinCard) > m_dagun.GetCardLevel(byTempCards[0]))
			{
				byMinCard = byTempCards[0];
				byXianShou = seat;
			}
			else if (m_dagun.GetCardLevel(byMinCard) == m_dagun.GetCardLevel(byTempCards[0]))
			{
				if (GetCardColor(byMinCard) > GetCardColor(byTempCards[0]))
				{
					byMinCard = byTempCards[0];
					byXianShou = seat;
				}
			}
		}
	}
	return byXianShou + 1;
}
//写入游戏记录，用于回放 recordType:1首牌数据，2出牌记录
CString CGameLogic::getWriteReplayRecordCString(BYTE recordType)
{
	CString outDate = TEXT("");
	CString strHandCard = TEXT("");
	CString strOrder = TEXT("");
	if (recordType == 1)
	{
		for (int iPlayer = 0; iPlayer < GetPlayerCount(); iPlayer++)
		{
			strHandCard.AppendFormat("%d:", iPlayer);
			for (int iCount = 0; iCount < m_sReplayRecord.vecHandCard[iPlayer].size(); iCount++)
			{
				strHandCard.AppendFormat("%s", GetStringByCard(m_sReplayRecord.vecHandCard[iPlayer][iCount]).c_str());
			}
			strHandCard.AppendFormat("|");
		}

		//写入玩家分数
		strHandCard.Append("S:");
		for (int iPlayer = 0; iPlayer < GetPlayerCount(); iPlayer++)
		{
			strHandCard.AppendFormat("%d", m_sReplayRecord.iScore[iPlayer]);
			//最后一位不要"，"
			if (iPlayer < GetPlayerCount() - 1)
			{
				strHandCard.AppendFormat(",");
			}
		}

		outDate += strHandCard;
	}
	else if (recordType == 2)
	{
		auto iter = std::begin(m_sReplayRecord.vecOrder);
		while (iter != std::end(m_sReplayRecord.vecOrder))
		{
			Replay_Order order = *iter;
			
			switch (order.operation)
			{
			case E_SendCard:
				strOrder.AppendFormat("|S%d:", order.chair_id);
				break;
			case E_OutCard:
				if (order.value.size() > 0 || order.vecOrderExt.size() > 0)
				{
					strOrder.AppendFormat("|C%d:", order.chair_id);
				}
				else
				{
					strOrder.AppendFormat("|C%d", order.chair_id);
				}
				break;
			case E_TurnOver:
				//客户端需要在E_TurnOver时清除所有玩家打出的牌
				if (order.vecOrderExt.size() == 0) 
				{
					strOrder.AppendFormat("|T%d", order.chair_id);
				}
				else
				{
					strOrder.AppendFormat("|T%d:", order.chair_id);
				}
				break;
			case E_HuoPai:
				strOrder.AppendFormat("|H%d:", order.chair_id);
				break;
			case E_EndHouPai:
				strOrder.AppendFormat("|E%d:", order.chair_id);
				break;
			case E_EndGame:
				strOrder.AppendFormat("|G%d:", order.chair_id);
				break;
			case E_GameJieSan:
				strOrder.AppendFormat("|J%d:", order.chair_id);
				break;
			default:
				break;
			}

			//写牌数据
			if (order.value.size() > 0)
			{
				for (int iCount = 0; iCount < order.value.size(); iCount++)
				{
					strOrder.AppendFormat("%s", GetStringByCard(order.value[iCount]).c_str());
				}
			}

			//写附加信息，例如本轮分，抓分，明鸡
			if (order.vecOrderExt.size() > 0)
			{
				for (int iCount = 0; iCount < order.vecOrderExt.size(); iCount++)
				{
					Replay_Order_Ext tempOrderExt = order.vecOrderExt[iCount];
					
					if (Replay_Ext_Type::E_Ext_HouPai == tempOrderExt.ext_type)
					{
						strOrder.AppendFormat(",H%d", tempOrderExt.ext_value);
					}
					else if (Replay_Ext_Type::E_Ext_TurnScore == tempOrderExt.ext_type)
					{
						strOrder.AppendFormat(",S%d", tempOrderExt.ext_value);
					}
					else if (Replay_Ext_Type::E_Ext_GetScore == tempOrderExt.ext_type)
					{
						strOrder.AppendFormat(",G%d", tempOrderExt.ext_value);
					}
					else if (Replay_Ext_Type::E_Ext_MingJi == tempOrderExt.ext_type)
					{
						strOrder.AppendFormat(",J");
					}
					else if (Replay_Ext_Type::E_Ext_GLongShu == tempOrderExt.ext_type)
					{
						strOrder.AppendFormat(",L%d", tempOrderExt.ext_value);
					}
					else if (Replay_Ext_Type::E_Ext_PaiXing == tempOrderExt.ext_type)
					{
						strOrder.AppendFormat(",P%d", tempOrderExt.ext_value);
					}
				}
			}

			iter++;
		}

		outDate += strOrder;
	}

	return outDate;
}
//解析配置的任务,格式： "t:5|fz:123445|hhj:4|hhg:1|hhw:100|hhf:4|hhd:60"
void CGameLogic::ParseRule(const string& strRule)
{
	m_nBase = m_pGameServiceOption->lCellScore;
	m_nSerPay = m_pGameServiceOption->wRevenue;
	m_spay = m_nBase*m_nSerPay/100;

	if (strRule.size() == 0)
	{
		return;
	}

	//表示底分要除以10
	//m_bCellScore = true;  

	//默认开口胡
	m_rule.bNeedKaiKou = false;
	m_rule.iTypeLaizi = 3;
	m_rule.bKouKou = false;
	m_rule.iBird = 0;
	m_rule.bOnlyZimo = false;
	m_rule.bHongZhongLai = false;
	m_rule.bHongZhongPi = false;
	m_rule.bHongZhongFan = false;
	m_rule.bZhuangxian = false;
	m_rule.iZhuangxianFan = 2;//庄家输赢多2分
	m_rule.wCreateType = 0;

	//抓鸟结算番数
	m_rule.iBirdFan = 2;//抓中1个+2
	//点杠1分
	m_rule.iGangFan = 1;
	//是否可以热铳
	m_rule.bReChonHu = true;
	//抢杠胡时是否一人全包
	m_rule.bQiangGangBao = true;
	//底分
	m_rule.iDiFen = 2;
	m_iBaseScore  = 1;//通过客户端界面配置的底分
	//是否去万，默认不去万
	m_rule.bNoWan = false;

	//解析游戏规则，格式：n1:v1|n2:v2
	vector<string> vecID;
	stovs(strRule, "|", vecID);
	for (int i=0; i<vecID.size(); i++)
	{
		vector<string> details;
		stovs(vecID[i], ":", details);
		if (details.size() == 2)
		{
			string k = details[0];
			string v = details[1];
			if (k == "Fa")
			{
				if (atoi(v.c_str()) > 0)
				{
					m_iFaOfTao = atoi(v.c_str());
				}
			}
			else if (k == "Jiang")
			{
				if (atoi(v.c_str()) > 0)
				{
					m_iJiangOfTao = atoi(v.c_str());
				}
			}
			if (k == "fz")
			{
				//房主
				m_rule.dwFangZhuID = atoi(v.c_str());
			}
			else if (k == "hhj")
			{
				//局数
				m_rule.iJuShu = atoi(v.c_str())* m_pGameServiceOption->wGameJuShu;;
			}
			else if (k == "hhf")
			{
				//最少起胡番数
				m_rule.iMinFan = atoi(v.c_str());
			}
			else if (k == "D")   
			{
				//调试开关
				g_iDebug = atoi(v.c_str());
			}
			else if (k == "G")   
			{
				//日志开关
				g_iLog = atoi(v.c_str());
			}
			else if (k == "ctp")
			{
				m_rule.wCreateType = atoi(v.c_str());
			}
			else if (k == "hdf")
			{
				if (0 < atoi(v.c_str()))
				{
					m_iBaseScore = atoi(v.c_str());
				}
			}
			else if (k == "addb")
			{
				if (0 < atoi(v.c_str()))
				{
					m_iAddSpecailBeishu = atoi(v.c_str());
				}
			}
			////特殊牌型是否加分
			//else if (k == "hpx")
			//{
			//	if (0 == atoi(v.c_str()) || 1 == atoi(v.c_str()) )
			//	{
			//		m_byAddSepcialFlag = atoi(v.c_str());
			//	}
			//}
			////王单出算几，2或3
			//else if (k == "hdc")
			//{
			//	if (2 == atoi(v.c_str()) || 3 == atoi(v.c_str()) )
			//	{
			//		m_byFakeKingValue = atoi(v.c_str());
			//	}
			//}
			////是否显示手牌数量
			//else if (k == "hsk")
			//{
			//	if (0 == atoi(v.c_str()) || 1 == atoi(v.c_str()) )
			//	{
			//		m_byIsShowChardCount = atoi(v.c_str());
			//	}
			//}
			
		}
	}

	//王单出算几
	m_dagun.SetFakeKingValue(m_byFakeKingValue);

	//开关
	if (g_iDebug > 0)
	{
		//m_rule.iJuShu = g_iDebug;
	}
}


void CGameLogic::OnStartGame()
{
	//InitGame();
	OnWriteGameRecord(INVALID_CHAIR,_T("开始OnEventGameStart......"));

	ParseRule(this->m_pITableFrame->GetGameServiceOption()->szGameRoomRule);
	
	//由于8王和4王是共用m_dbp[]数据的，所以每大局时需要重新初始化牌数据
	ProduceCards();

	m_vecGameEnd.clear();
	//m_nextbanker = 0;
	Reset();
	m_GameState = gsNull;
	SetActionStep(AS_NULL);
	m_CurCompleteCount = 0;
	m_nBase = m_pGameServiceOption->lCellScore;
	m_nSerPay = m_pGameServiceOption->wRevenue;

	memset(m_lastScore,0,sizeof(m_lastScore));
	memset(m_total,0,sizeof(m_total));

	memset(m_MaxScore,0,sizeof(m_MaxScore));
	memset(m_totalFirstTurn,0,sizeof(m_totalFirstTurn));
	memset(m_totalDuPai,0,sizeof(m_totalDuPai));
	memset(m_whoTotal8Xi,0,sizeof(m_whoTotal8Xi));
	memset(m_whoTotal7Xi,0,sizeof(m_whoTotal7Xi));
	memset(m_whoTotalGonglong,0,sizeof(m_whoTotalGonglong));

	StartNextGame();

	//发送随机任务
	//SendTaskID(true);
}

void CGameLogic::StartPlay( BYTE whoplay )
{
	m_score = 0;
	// 开始

	DWORD dwPower = CMD_S_Power_CB::p_Out;
	SendPower(whoplay,dwPower,FIRST_START_PLAY_TIME);
}
//发送声音
void CGameLogic::SendPlaySoundMsg(BYTE seat,BYTE type,BYTE flag)
{
    CMD_CS_msgPlaySound_CB soundmsg;
	//牌数为1的玩家都要显示插底
	for ( int iSeat = 0;iSeat < MAX_PLAYER;iSeat++)
	{
		if (1 == m_thePaiCount[iSeat])
		{
			soundmsg.theSeat[iSeat] = 1;;
		}
	}
 
    soundmsg.thePaiType = type;
	soundmsg.theFlag = flag;

    SEND_TABLE_DATA_ALL(SUB_CS_PLAYSOUND,soundmsg);
}

// 发送权限
void CGameLogic::SendPower( BYTE whoplay,DWORD aPower,DWORD dwWaitTime /*= 0*/ )
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	CMD_S_Power_CB power;

	DWORD nTime = dwWaitTime ? dwWaitTime : 0;
	power.theWhoPlay	= whoplay;
	power.thePower		= aPower;
	if(m_TuoGuanPlayer[whoplay-1])
	{
		if(nTime > m_nAutoOutTime)
		{
			nTime = m_nAutoOutTime;
		}
	}
	power.theDownTime	= nTime;

	//详细日志
	if (g_iLog > 0)
	{
		char buf[64];
		memset(buf, 0 ,64);
		sprintf(buf, "牌权： seat=%d power=%d,time=%u ", power.theWhoPlay, power.thePower, power.theDownTime);

		OnWriteGameRecord(power.theWhoPlay-1, buf);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	SEND_TABLE_DATA_ALL(SUB_S_POWER,power);


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	if (m_GameState == gsPlay)
		SetActionStep(AS_PLAY,nTime + 1);//设置等待时间，服务端多等一下
	else if(m_GameState == gsRoarPai)
		SetActionStep(AS_ROAR,nTime + 1);//设置等待时间，服务端多等一下
}


int CGameLogic::AutoTuoGuan(BYTE theSeat)
{
	CMD_S_Tuoguan_CB msgtg;
	msgtg.theFlag = CMD_S_Tuoguan_CB::T_TUOGUAN;
	msgtg.theSeat = theSeat;

	if(m_GameState == gsNull)
		return 0;

	//详细日志
	if (g_iLog > 0)
	{
		char buf[128];
		memset(buf, 0 ,128);
		sprintf(buf, "自动托管： AutoTuoGuan msgtg.theFlag=%d msgtg.theSeat=%d ", msgtg.theFlag, msgtg.theSeat);

		OnWriteGameRecord(msgtg.theSeat, buf);
	}

	if (m_GameState == gsPlay || m_GameState == gsRoarPai)
	{
		if (CMD_S_Tuoguan_CB::T_TUOGUAN == msgtg.theFlag)
		{
			m_TuoGuanPlayer[theSeat] = TRUE;
			m_TrustCounts[theSeat]++;
			if( theSeat+1 == m_whoplay)
			{//如果是当前的玩家，那么重新设置一下开始时间
				m_tDownTime = GetCPUTickCount()+m_nAutoOutTime;
			}
			SEND_TABLE_DATA_ALL(SUB_S_TUOGUAN,msgtg);

			if (m_TrustCounts[theSeat] < m_nTrustCounts)
			{
				char buf[128];
				memset(buf, 0 ,128);
				sprintf(buf, "托管： 您已经托管%d次, 托管%d次将算逃跑！seat:%d ", m_TrustCounts[theSeat], m_nTrustCounts, msgtg.theSeat);

				OnWriteGameRecord(msgtg.theSeat, buf);
			}
			else
			{
				char buf[128];
				memset(buf, 0 ,128);
				sprintf(buf, "托管： 您第%d次进入托管，已经达到%d次的上限，算逃跑处理！seat:%d ", m_TrustCounts[theSeat],m_nTrustCounts,msgtg.theSeat);

				OnWriteGameRecord(msgtg.theSeat, buf);
				
				OnEventGameEnd(msgtg.theSeat,NULL,GER_USER_LEFT);
				return 0;
			}
		}
		else if (CMD_S_Tuoguan_CB::T_CANCEL == msgtg.theFlag)
		{
			m_TuoGuanPlayer[theSeat] = FALSE;
			SEND_TABLE_DATA_ALL(SUB_S_TUOGUAN,msgtg);
		}
		else
			return 0;
	}
	return 1;
}

void CGameLogic::SetActionStep(ActionStep as, unsigned long nSecond)
{
	if (as == AS_NULL || as >= AS_COUNT)
	{
		m_theActionStep = AS_NULL;
		m_nowActionStep = AS_NULL;
		m_tDownTime = 0;
	}
	else
	{
		if (nSecond > 0)
		{
			m_theActionStep = as;
			m_nowActionStep = as;
			m_tPowerStartTime = GetCPUTickCount();
			m_tDownTime = GetCPUTickCount() + (time_t)nSecond;
		}
		else
		{
			m_theActionStep = AS_NULL;
			m_nowActionStep = as;
			m_tPowerStartTime = 0;
			m_tDownTime = 0;
			OnActionStep(as);
		}
	}
}
void CGameLogic::OnActionStep(ActionStep as)
{
	if (as == AS_GAMESTART)
	{
		//开场动画播放结束，开始发牌
		StartPlay(m_whoplay);
	}
	else if(as == AS_PLAY)
	{
		if(m_whoplay > 0 && m_whoplay <= MAX_PLAYER)
		{
			AutoTuoGuan(m_whoplay-1);
		}
		TuoGuanOutCard();
	}
}

//托管出牌
//规则：1，首出牌时必须出牌，跟出牌时按需出牌，优先出一张非赖子牌
//规则：2，避免玩家最后只剩一个单王
//规则：3，避免玩家包赔，即下家只剩单牌时，自己有2必须出牌，而不分首出或跟出
void CGameLogic::TuoGuanOutCard()
{
	BYTE buf[MAXCARD] = {0};
	BYTE bufMagicNoKing[MAXCARD] = {0};//非王的赖子
	BYTE bufKing[MAXCARD] = {0};//王
	BYTE byHandHas2 = 0,byHandHasK = 0,byHandMagicNK = 0;
	int n = 0;
	for(int i=0;i<MAXCARD;i++) 
	{
		if(m_dbplay[m_whoplay-1][i] > 0 && m_dbplay[m_whoplay-1][i] < 55)
		{
			if(m_dagun.GetCardLevel(m_dbplay[m_whoplay-1][i]) == m_dagun.GetCardLevel(2))
			{
				byHandHas2 = m_dbplay[m_whoplay-1][i];
			}
			if(m_dagun.GetCardLevel(m_dbplay[m_whoplay-1][i]) >= m_dagun.GetCardLevel(SMA_KING))
			{
				bufKing[byHandHasK++] = m_dbplay[m_whoplay-1][i];
				continue;
			}
			if(m_dagun.GetCardLevel(m_dbplay[m_whoplay-1][i]) == m_dagun.GetCardLevel(3))//目前非王的赖子只有3
			{
				bufMagicNoKing[byHandMagicNK++] = m_dbplay[m_whoplay-1][i];
				continue;
			}
			buf[n++] = m_dbplay[m_whoplay-1][i];
		}
	}
	//排序，赖子放后面，王放最后面
	m_dagun.SortByIndex(buf,n);
	for (int j = 0;j<byHandMagicNK && j < MAXCARD;j++)
	{
		buf[n++] = bufMagicNoKing[j];

	}
	for (int k = 0;k<byHandHasK && k < MAXCARD;k++)
	{
		buf[n++] = bufKing[k];
	}


	CMD_OutCard_CB outmsg;
	outmsg.theSeat = m_whoplay-1;
	//先默认首出一张最小的牌
	if(m_whoplayout == 0)
	{
		outmsg.theCount = 1;
		outmsg.thePai[0] = buf[0];
		outmsg.thePaiType = TYPE_ONE;
	}
	else
	{
		// 跟出牌
		BYTE lastPaiNoMagic[MAXCARD] = {0};
		BYTE lastMagicCnt = 0;
		for (int k = 0, n = 0; k < MAXCARD; k++)
		{
			if (m_allPaiOut[m_whoplayout-1][k] <= 0) continue;

			bool bMagicPai = false;
			for (int m = 0; m < 8; m++) 
			{
				if (m_OutPaifakeking[m_whoplayout-1][m].index == m_allPaiOut[m_whoplayout-1][k]) {
					bMagicPai = true; lastMagicCnt++; break;
				}
			}
			if (bMagicPai) continue;

			lastPaiNoMagic[n++] = m_allPaiOutNoMagic[m_whoplayout-1][k];
		}

		TCARDS handCards;
		for (int k = 0; k < MAXCARD; k++)
		{
			handCards.push_back(buf[k]);
		}
		m_dagun.GetGroupType(handCards);

		vector<TPokerGroup2> beepOut;
		m_dagun.BeepCardOut(lastPaiNoMagic, m_lastOutType, beepOut, lastMagicCnt);

		if (beepOut.size() == 0) 
		{
			outmsg.theCount = 0;
		} 
		else 
		{
			for (int k = 0; k < beepOut[0].count; k++)
			{
				outmsg.thePai[k] = beepOut[0].index[k];
			}
			outmsg.theCount = beepOut[0].count;
			outmsg.thePaiType = m_lastOutType;
		}
	}
	
	//避免包赔
	BYTE byNexter = m_whoplay % MAX_PLAYER + 1;
	for (int iSeat = 0;iSeat < MAX_PLAYER;iSeat++)
	{	
		if(m_thePlayerState[byNexter - 1] == OX_GS_PLAYING)
		{
			break;
		}
		byNexter = byNexter % MAX_PLAYER + 1;
	}
	//下家是否只有一张牌了
	bool bNextOnlyOne = (1 == m_thePaiCount[(byNexter-1)% MAX_PLAYER]? true:false);
	if (bNextOnlyOne && 0 != byHandHas2)
	{
		outmsg.thePai[0] = byHandHas2;
		outmsg.theCount = 1;
	}

	//如果首出，避免玩家只剩单王
	//如果是首出，并且一手可以出完的牌，就一次出完。这个可以避免单王，还能快速出完
	if(m_whoplayout == 0)
	{
		//TCardType tCType = m_dagun.GetType(m_dbplay[m_whoplay-1],n,byHandMagicNK+byHandHasK);
		//if (tCType.type != TYPE_NULL && tCType.type != TYPE_ERROR)
		//{
		//	memcpy(outmsg.thePai,buf,n);
		//	outmsg.theCount = n;
		if (GetCardPoint(buf[0]) >= CP_BJ_S)
		{
			if (GetCardPoint(buf[1]) >= CP_BJ_S)//说明只剩双王了，一次出完
			{
				outmsg.theCount = 2;
				outmsg.thePai[0] = buf[0];
				outmsg.thePai[1] = buf[1];
				outmsg.thePaiType = TYPE_BOMB_NOMORL;
			}
			else
				outmsg.theCount = 0;//单王不允许出牌
		}
	}

	OnWriteGameRecord(m_whoplay-1, _T("托管出牌"));
	AutoOutCard(m_whoplay-1,outmsg);
}

long CGameLogic::GetCPUTickCount( void )
{
	time_t now;
	time(&now);
	return now;
}

void CGameLogic::GoNextPlayer()
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	BYTE byCount = 0;
	while (TRUE)
	{
		if (m_whoplay==MAX_PLAYER) 
		{
			m_whoplay = 1;
		}
		else 
		{
			m_whoplay++;
		}
		
		IServerUserItem * pIServerUserItem = GetServerUserItem(m_whoplay - 1);
		if(pIServerUserItem == NULL || m_thePlayerState[m_whoplay - 1] != OX_GS_PLAYING)
		{
			continue;
		}

		if (byCount > MAX_PLAYER) break; //避免死循环
		byCount++ ;

		//如果当前玩家出完了
		if(m_whoAllOutted[m_whoplay-1])
		{
			continue;
		}
		else
		{//没出完？
			break;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	if(m_whoplayout == m_whoplay)
	{
		EndTurn();//清理数据
		SendPai();//发牌
	}
	if(m_GameState == gsPlay)
	{
		DWORD dwPower = CMD_S_Power_CB::p_Out;
		SendPower(m_whoplay,dwPower,m_nPlayTime);
		time(&nowTime);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int i =0; i< MAXCARD; i++)
	{
		m_allPaiOutNoMagic[m_whoplay-1][i] = 0;
		m_allPaiOut[m_whoplay-1][i]	= 0;
	}
	memset(m_OutPaifakeking[m_whoplay-1],0,sizeof(m_OutPaifakeking[m_whoplay-1]));
}

//出牌动作
int CGameLogic::AutoOutCard(BYTE theSeat,CMD_OutCard_CB& msgout)
{
	if( theSeat != m_whoplay -1)
	{
		char buf[256] = {0};
		sprintf(buf, "%d: AutoOutCard error: 出牌玩家不是当前玩家", theSeat);
		TraceMessage(buf);
		return 0;
	}

	if (g_iLog > 0)
	{
		char buf[128];
		memset(buf, 0 ,128);
		sprintf(buf, "出牌： theCardsCount=%d %s",  msgout.theCount,(msgout.theCount>0?"":"不要"));
		string tmp(buf);
		for (size_t i = 0; i<msgout.theCount; i++)
		{
			memset(buf, 0 ,64);
			sprintf(buf, "0x%02x,", switchCard2Ox(msgout.thePai[i]));
			tmp += buf;
		}

		OnWriteGameRecord(msgout.theSeat, tmp.c_str());
	}
	m_theCanNotOut[theSeat] = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	BYTE byTempCards[MAXCARD] = {0};
	for(int i = 0 ; i < msgout.theCount ; i++)
	{
		byTempCards[i] = msgout.thePai[i];//保存出牌数据
	}

	//出牌数目为0，则为放弃的情况
	if(msgout.theCount == 0 || msgout.theCount > MAXCARD)
	{
		//记录过牌
		Replay_Order order;
		order.chair_id = theSeat;
		order.operation = E_OutCard;
		//order.value.push_back(0);
		m_sReplayRecord.vecOrder.push_back(order);
		
		if(/*m_whoplayout != 0 && */m_whoplay == theSeat + 1)//肉挨肉中，首出牌也可能PASS。比如单王不能出的情况
		{
			CMD_OutCard_CB outmsg;
			outmsg.theCount = 0;
			outmsg.theSeat = msgout.theSeat;
			for(int i = 0; i < MAXCARD; i ++)
			{
				outmsg.thePai[i] = 0;
				m_allPaiOutNoMagic[m_whoplay-1][i] = 0;
				m_allPaiOut[m_whoplay-1][i]	= 0;
				m_lastPaiOut[m_whoplay-1][i] = 0;
			}
			memset(m_OutPaifakeking[m_whoplay-1],0,sizeof(m_OutPaifakeking[m_whoplay-1]));

			SEND_TABLE_DATA_ALL(SUB_CS_OUT,outmsg);

			//判断是否流局
			if (m_whoplayout == 0)
			{
				m_theCanNotOut[theSeat] = 1;
				BYTE byPlayerCnt = 0,byCanNotOut = 0;
				for(int k=0; k < MAX_PLAYER; k++)  //发牌
				{
					IServerUserItem * pIServerUserItem = GetServerUserItem(k);
					if(pIServerUserItem != NULL && m_thePlayerState[k] == OX_GS_PLAYING)
					{
						if(m_theCanNotOut[k] == 1) 
						{
							byCanNotOut++;
						}
						byPlayerCnt++;
					}
				}
				if(byPlayerCnt <= byCanNotOut)
				{
					if (m_cbLeftCardCount == 0)
					{
						m_pITableFrame->KillGameTimer(GAME_TIMER);
						GameOver(theSeat,GOT_ZHONGTU);//流局
					}
					else
					{
						SendPai();//发牌			
						OnWriteGameRecord(INVALID_CHAIR,_T("所有人都无法出牌，重新发牌......"));
						GoNextPlayer();
					}
					return 1;//每次结束后都要return，否则在游戏结束后，服务器还发送消息，服务器会挂死
				}
			}

			//如果出单牌,下家只有一张牌时，需要判断出牌是否有2没有出
			if (TYPE_ONE == m_lastOutType)
			{
				IsBaoPei(byTempCards,msgout.theCount);
			}

			m_whoPass[m_whoplay-1] = TRUE;
			GoNextPlayer();
		}

		return 1;
	}

	BYTE buf[MAXCARD] = {0};
	for(int i = 0 ; i < MAXCARD ; i++)
		buf[i] = m_dbplay[m_whoplay-1][i];
	int z = 0;
	for(int i = 0 ; i < msgout.theCount ; i++)
	{
		for(int j = 0 ; j < MAXCARD ; j++)
		{
			if(msgout.thePai[i] == buf[j] && msgout.thePai[i] > 0)
			{
				buf[j] = 0;//删除打出的牌
				z++;
				break;
			}
		}
	}
	if(z == msgout.theCount)
	{
		TCardType re1,re2;
		int iNumOfKing = 0;
		BYTE byMagicNum = m_dagun.GetMagicNum(byTempCards,msgout.theCount);
		if (byMagicNum > 0)
		{
			memcpy(m_OutPaifakeking[m_whoplay-1],msgout.fakeking,sizeof(m_OutPaifakeking[m_whoplay-1]));//注意不要越界
		}
		BYTE byFKed[8]={0};//做牌时可能会做出多个相同的赖子，会找错，需要这个开关
		//判断是否有赖子代替的值
		for(int i=0;i<MAXCARD && i < msgout.theCount;i++)
		{
			m_allPaiOut[m_whoplay-1][i] = msgout.thePai[i];//存原始牌数据，可能有赖子
			int j = 0;
			for (j = 0;j < byMagicNum && j < 8;j++)
			{
				if (msgout.fakeking[j].index == msgout.thePai[i] && byFKed[j] == 0)
				{
					byFKed[j] = 1;
					m_allPaiOutNoMagic[m_whoplay-1][i] = msgout.fakeking[j].fakeindex;
					break;
				}			
			}
			if(j >= byMagicNum)
				m_allPaiOutNoMagic[m_whoplay-1][i] = msgout.thePai[i];
		}

		//获取上次和这次出牌的类型
		//TYPE_NULL代表第一个出
		if(m_whoplayout==0)
		{
			re1.type = TYPE_NULL;
			m_lastOutType = TYPE_NULL;
		}
		else 
		{
			int len = m_dagun.GetCardNum(m_allPaiOutNoMagic[m_whoplayout-1]);
			BYTE byLastMagicCnt = (m_OutPaifakeking[m_whoplayout-1][0].index != 0?1:0);
			re1 = m_dagun.GetType(m_allPaiOutNoMagic[m_whoplayout-1],len,byLastMagicCnt,1);
			//这里为什么要重新设置下呢？因为很可能出现不同的判断
			//比如A走了334455,B走了44王王王5,那么当C走的时候，GetType很可能把B的牌型判断为444555这样的大牌型
			//所以，在这里，一定要把牌型设置回来，根据客户端传过来的为依据
			re1.type = m_lastOutType;
		}
		re2 = m_dagun.GetType(m_allPaiOutNoMagic[m_whoplay-1],msgout.theCount,byMagicNum,1,m_lastOutType);
		iNumOfKing = m_dagun.GetKingNum(byTempCards,msgout.theCount);

		//比较是否真的可以出牌
		m_whoPass[m_whoplay-1] = FALSE;
		if(m_dagun.Compare(re1,re2))
		{	
			//记录过牌
			Replay_Order order;
			order.chair_id = theSeat;
			order.operation = E_OutCard;
			for (int i= 0; i< msgout.theCount; i++)
			{
				BYTE _card= msgout.thePai[i];
				if(_card >0 && _card < 55)
				{
					order.value.push_back(_card);
				}
			}
			//回放里记录牌型，否则带癞子的THREESTR和TWOSTR有时无法区分
			Replay_Order_Ext orderExtPx;
			orderExtPx.ext_type = Replay_Ext_Type::E_Ext_PaiXing; //牌型
			orderExtPx.ext_value = re2.type;
			order.vecOrderExt.push_back(orderExtPx);

			msgout.thePaiType = re2.type;
			int iTempFan = m_iCurrentFanShu;
			//特效牌型日志记录，管得起才能算特殊牌型
			if(re2.type == TYPE_BOMB_NOMORL)
			{
				if( re2.card >= SMA_KING && re2.len == 2)
				{
					msgout.thePaiType = TYPE_KING;
					m_whoHasKingBomb = m_whoplay;//王炸
					m_iCurrentFanShu += 4;
					//详细日志
					if (g_iLog > 0)
					{
						CString szGameRecord = _T("打出了");
						szGameRecord.AppendFormat("天炸(2王)");
						OnWriteGameRecord(m_whoplay-1, szGameRecord);
					}
				}
				else if( byMagicNum > 0 && byMagicNum < 4)
				{
					m_playSoftBomb[m_whoplay-1] ++;//软炸
					m_iCurrentFanShu += 2;
					//详细日志
					if (g_iLog > 0)
					{
						CString szGameRecord = _T("打出了");
						szGameRecord.AppendFormat("第%d个软炸",m_playSoftBomb[m_whoplay-1]);
						OnWriteGameRecord(m_whoplay-1, szGameRecord);
					}
				}
				else if( byMagicNum == 0 && re2.len == 4)
				{
					msgout.thePaiType = TYPE_BOMB_HARD;
					m_playHardBomb[m_whoplay-1] ++;//硬炸
					m_iCurrentFanShu += 4;
					//详细日志
					if (g_iLog > 0)
					{
						CString szGameRecord = _T("打出了");
						szGameRecord.AppendFormat("第%d个硬炸",m_playHardBomb[m_whoplay-1]);
						OnWriteGameRecord(m_whoplay-1, szGameRecord);
					}
				}
				else if( byMagicNum == 4 && iNumOfKing == 0)
				{
					msgout.thePaiType = TYPE_BOMB_MAGIC;
					m_playMagicBomb[m_whoplay-1] ++;//赖子炸
					m_iCurrentFanShu += 8;
					//详细日志
					if (g_iLog > 0)
					{
						CString szGameRecord = _T("打出了");
						szGameRecord.AppendFormat("第%d个赖子炸",m_playMagicBomb[m_whoplay-1]);
						OnWriteGameRecord(m_whoplay-1, szGameRecord);
					}
				}
			}

			//实时番数有更新，需要发送
			if (iTempFan != m_iCurrentFanShu)
			{
				SendFanShu();
			}

			m_score = 0;
			m_lastOutType = re2.type;

			//bugid 6125 ，包赔判断，如果出单牌,下家只有一张牌时，需要判断出牌是否有2没有出//游戏结束了，不用再判断包赔，
			int iLeftCardNum = 0;//m_thePaiCount[]有时候会出问题，所以用其他方式计算剩余牌数
			for(int i=0;i<MAXCARD;i++) 
			{
				if (buf[i] > 0 && buf[i] < CARDINDEX_BACK)
				{
					iLeftCardNum++;
				}
			}
			if (1 == z && iLeftCardNum > 0)//iLeftCardNum为0时游戏就结束了，不要在计算包赔了
			{
				IsBaoPei(byTempCards,msgout.theCount);
			}
			if(1 < z) m_bBaoPei = 0;//不包赔

			//在这里，re2.type 是一定要等于lpMsg->thePaiType的，否则就是错误的
			if(re2.type != msgout.thePaiType && m_whoplayout != 0)
			{
				char buf[125] = {0};
				sprintf(buf, "UserID=%d: error:re2.type != lpMsg->thePaiType", theSeat);
				TraceMessage(buf);
				//详细日志
				if (g_iLog > 0)
				{
					CString szGameRecord = _T("UserID=");
					szGameRecord.AppendFormat("%d: error:re2.type != lpMsg->thePaiType",theSeat);
					OnWriteGameRecord(theSeat, szGameRecord);
				}
			}
			
			//更新牌数量，记录回放
			m_sReplayRecord.vecOrder.push_back(order);
			m_thePaiCount[m_whoplay-1] -= msgout.theCount;
			m_whoplayout = m_whoplay;

			//插底提示 //牌出完了就结束了,不要在开报警提示了,所有添加iLeftCardNum > 0条件
			if(z == 1 && iLeftCardNum > 0 && IsSamePlayerOneCard(MAX_PLAYER))
			{
				SendPlaySoundMsg(m_whoplay-1,CMD_CS_msgPlaySound_CB::TY_ChaDi);
			}
			else 
				SendPlaySoundMsg(m_whoplay-1,CMD_CS_msgPlaySound_CB::TY_ChaDi,0);

			//删除出的牌
			int zz = 0;
			memset(m_dbplay[m_whoplay-1],0,sizeof(m_dbplay[m_whoplay-1]));
			for(int i=0;i<MAXCARD;i++) 
			{
				if (buf[i] > 0 && buf[i] < CARDINDEX_BACK)
				{
					m_dbplay[m_whoplay-1][zz++] = buf[i];
				}
			}
			SendPaiCount();

			SEND_TABLE_DATA_ALL(SUB_CS_OUT, msgout);

			//全关和硬杀数据更新
			m_byEveryOneOutCnt[m_whoplay-1]++;
			m_byEveryOneCurlunOutCnt[m_whoplay-1]++;//当前轮出牌次数

			//判断任务是否完成
			IsTaskFinished(re2, theSeat, iNumOfKing);
			//end 

			//有一个没有牌了就结束游戏
			//结束游戏
			if(zz==0)
			{
				//判断最后一手的任务是否完成
				IsTaskFinishedOfLastHand(re2, theSeat, iNumOfKing);
				//end
				//硬杀：玩家摸起的牌能跟现有手牌一次性出完并且没有赖子牌或赖子牌作为本身点数打出。
				//有王不可能硬杀
				if (m_byEveryOneCurlunOutCnt[m_whoplay-1] == 1 && iNumOfKing == 0)
				{
					m_whoHardKill = m_whoplay;
					if (byMagicNum != 0)
					{
						for (int j = 0;j < byMagicNum;j++)
						{
							if (GetCardPoint(msgout.fakeking[j].index) != GetCardPoint(msgout.fakeking[j].fakeindex) )
							{
								m_whoHardKill = 0;
								break;
							}			
						}
					}
				}
				m_nextbanker = m_whoplay;
				GameOver(m_whoplay-1,GOT_NORMAL);
			}
			else
			{
				GoNextPlayer();
			}
		}

		//压不住就过
		else
		{
			OnWriteGameRecord(m_whoplay-1,_T("客户端判断可以大过上家，服务器判断不能大过上家，pass"));

			m_whoPass[m_whoplay-1] = TRUE;
			//记录过牌
			Replay_Order order;
			order.chair_id = theSeat;
			order.operation = E_OutCard;
			//order.value.push_back(0);
			m_sReplayRecord.vecOrder.push_back(order);

			if(m_whoplayout != 0 && m_whoplay == theSeat + 1)
			{
				CMD_OutCard_CB outmsg;
				outmsg.theCount = 0;
				outmsg.theSeat = msgout.theSeat;
				for(int i = 0; i < MAXCARD; i ++)
				{
					outmsg.thePai[i] = 0;
					m_allPaiOutNoMagic[m_whoplay-1][i] = 0;
					m_allPaiOut[m_whoplay-1][i] = 0;
					m_lastPaiOut[m_whoplay-1][i] = 0;
				}
				memset(m_OutPaifakeking[m_whoplay-1],0,sizeof(m_OutPaifakeking[m_whoplay-1]));

				SEND_TABLE_DATA_ALL(SUB_CS_OUT,outmsg);

				m_whoPass[m_whoplay-1] = TRUE;
				GoNextPlayer();
			}
		}
	}
	return 1;
}

//判断是否包赔，返回值暂时没有使用,返回值1-MAX_PLAYRE ,0表示不包赔
BYTE CGameLogic::IsBaoPei(BYTE followCard[MAXPAI],BYTE outLen)
{
	//找下家
	BYTE byNexter = m_whoplay % MAX_PLAYER + 1;
	for (int iSeat = 0;iSeat < MAX_PLAYER;iSeat++)
	{	
		if(m_thePlayerState[byNexter - 1] == OX_GS_PLAYING)
		{
			break;
		}
		byNexter = byNexter % MAX_PLAYER + 1;
	}
	bool bLastNot2 = true;//上一个出牌玩家不是出的2
	if (m_whoplayout > 0 && GetCardPoint(m_allPaiOutNoMagic[m_whoplayout-1][0]) == 2)
	{
		bLastNot2 = false;
	}
	//下家是否只有一张牌了
	bool bNextOnlyOne = (1 == m_thePaiCount[(byNexter-1)% MAX_PLAYER]? true:false);
	if (bNextOnlyOne && bLastNot2)
	{
		bool bHandHas2 = false,bHas2 = false;
		for(int j = 0 ; j < MAXCARD ; j++)
		{
			if(m_dagun.GetCardLevel(m_dbplay[m_whoplay-1][j]) == m_dagun.GetCardLevel(2))
			{
				bHandHas2 = true;
				break;
			}
		}
		if(outLen != 0 && 0 != m_dagun.GetCardNum(followCard))
		{
			for(int j = 0 ; j < MAXCARD && bHandHas2; j++)
			{
				if(m_dagun.GetCardLevel(followCard[j]) == m_dagun.GetCardLevel(2))
				{
					bHas2 = true;
					break;
				}
			}
		}
		
		if (bHandHas2 && !bHas2)
		{
			m_bBaoPei = m_whoplay;
			OnWriteGameRecord(m_whoplay-1,_T("当前出单牌，下家只剩一张牌，当前玩家有2但没有出2"));
		}
		else if(!bHandHas2 || bHas2) m_bBaoPei = 0;
	}
	else m_bBaoPei = 0;

	return m_bBaoPei;
}

//是否有玩家只有一张牌,自己除外//参数byWho 0-- MAX_PLAYER-1,为MAX_PLAYER表示查询所有玩家是否剩一张牌
BOOL CGameLogic::IsSamePlayerOneCard(BYTE byWho)
{
	//下家是否只有一张牌了
	for ( int iSeat = 0;iSeat < MAX_PLAYER;iSeat++)
	{
		if (iSeat != byWho && 1 == m_thePaiCount[iSeat])
		{
			return true;
		}
	}
	return false;
}
//  半笼（1分）：一三游一方，抓105分或以上，对方有抓分；一四游一方，抓105分以上，对方有抓分；二三游一方，抓105分或以上，对方有抓分；
//	一笼（2分）：一二游一方，对方有抓分；前面半笼的情况时，对方有手抓分，但把4游的抓分给1游、手分给3游后，对方没有分数了，我方200分，算一笼。
//	干笼（4分）：一二游一方，抓200分或对方没有抓分；二三游一方，抓200分或对方没有抓分；一三游一方，抓200分或对方没有抓分；二四游一方，抓200分或对方没有抓分；
//	四游手上没有出的分算对方抓分（固定算在三游抓分）；四游抓的分不为0，则给一游，如果四游最终算成了干笼输，则不能算干笼。
//	小结算面板里面的抓分和手分都只显示没有加四游分的分数

void CGameLogic::GameOver(BYTE winner,GameOverType type)
{
	if((winner < 0 || winner >= MAX_PLAYER) &&( type != GOT_ESCAPE && type != GOT_DISMISS) )
		return;

	long iScore[MAX_PLAYER];
	memset(iScore,0,sizeof(iScore));
	memset(m_xiScore,0,sizeof(m_xiScore));

	CMD_S_EndGame_CB endgameMsg;
	BYTE byGongType = CMD_S_EndGame_CB::g_Normal;
	int fan = 1;
	endgameMsg.cbTheOrder = m_CurCompleteCount;
	endgameMsg.cbEndStatus = 0;
	//endgameMsg.huoPaiChair = m_WhoRoar;//暂时没有使用
	endgameMsg.theBank = m_banker;
	//endgameMsg.theParter = m_parter;//暂时没有使用

	//结算数据
	int iTmepFan = m_iCurrentFanShu;//公共番数
	for(int i = 0; i < MAX_PLAYER; i++)
	{
		//庄家没有全关，删除庄家相关代码
		if ((i != m_banker - 1 && m_byEveryOneOutCnt[i] == 0 && m_thePlayerState[i] == OX_GS_PLAYING) /*|| (i == m_banker && m_byEveryOneOutCnt[i] == 1)*/)
		{
			m_whoQuanGuan[i] = true;
		}
	}
	fan = (iTmepFan > 1?iTmepFan:1) *(m_whoHardKill > 0?2:1);

	//游戏中的人数
	BYTE byPlayerCnt = 0;
	for(int k=0; k < MAX_PLAYER; k++)  //发牌
	{
		IServerUserItem * pIServerUserItem = GetServerUserItem(k);
		if(pIServerUserItem != NULL && m_thePlayerState[k] == OX_GS_PLAYING)
		{
			byPlayerCnt++;
		}
	}

	//有人逃跑，游戏结束
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	if(type == GOT_ESCAPE)
	{
		endgameMsg.theEndType = CMD_S_EndGame_CB::GT_ESCAPE;
		endgameMsg.theWhoEscape = winner + 1;//风格要统一，都加1吧

		endgameMsg.theWinLose[winner] = 0;//逃跑的人输
		endgameMsg.theFan[winner] = m_iJiangOfTao * (byPlayerCnt - 1);//自己不要算在里面
		for(int i = 0; i < MAX_PLAYER; i++)
		{
			IServerUserItem * pIServerUserItem = GetServerUserItem(i);
			if(pIServerUserItem != NULL && m_thePlayerState[i] == OX_GS_PLAYING)
			{
				if(i != winner)
				{
					iScore[i] = (m_thePaiCount[winner] <= 1?1:m_thePaiCount[winner]) *m_nBase*m_iBaseScore*(m_iJiangOfTao);
					endgameMsg.theWinLose[i] = 1;
					//endgameMsg.theFan[i] = m_iJiangOfTao;
					iScore[winner] += -iScore[i];
				}
			}	
		}
		
		//memset(iScore,0,sizeof(iScore));
		for(int i = 0; i < MAX_PLAYER; i++)
		{
			AddSpecailScore(iScore,i,m_nBase*m_iBaseScore);
		}
	}

	//普通类型
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	else if(type == GOT_NORMAL)
	{
		endgameMsg.theEndType = CMD_S_EndGame_CB::GT_NORMAL;
		endgameMsg.theWinLose[winner] = 1;
		endgameMsg.theFan[winner] = 0;
		for(int i = 0; i < MAX_PLAYER; i++)
		{
			IServerUserItem * pIServerUserItem = GetServerUserItem(i);
			if(pIServerUserItem != NULL && m_thePlayerState[i] == OX_GS_PLAYING)
			{
				if(i != winner)
				{
					int iTempShuFan = fan * (m_thePaiCount[i]<1?1:m_thePaiCount[i]) * (m_whoQuanGuan[i]<1?1:2);
					iTempShuFan = (iTempShuFan == 1?0:iTempShuFan);//番数为1时，说明玩家剩余一张牌，而且没有特殊倍数，这时不能扣分
					//bugid 6122,剩余牌数的番数不显示在倍数里面
					//endgameMsg.theFan[i] = iTempShuFan;
					endgameMsg.theFan[i] = fan * (m_whoQuanGuan[i]<1?1:2);
					endgameMsg.theFan[i] = (endgameMsg.theFan[i] == 1?0:endgameMsg.theFan[i]);//番数为1时，说明没有特殊倍数，这时不能扣分
					iScore[i] = -iTempShuFan*m_nBase*m_iBaseScore;
					endgameMsg.theWinLose[i] = 0;
					iScore[winner] += -iScore[i];
				}
			}
		}
		for(int i = 0; i < MAX_PLAYER; i++)
		{
			IServerUserItem * pIServerUserItem = GetServerUserItem(i);
			if(pIServerUserItem != NULL && m_thePlayerState[i] == OX_GS_PLAYING)
			{
				if(i != winner && 0 == iScore[i])
				{
					endgameMsg.theWinLose[i] = 2;//平局
				}
			}
		}
		//包赔
		if (0 < m_bBaoPei && MAX_PLAYER >= m_bBaoPei)
		{
			byGongType = CMD_S_EndGame_CB::g_BaoPei;
			for(int i = 0; i < MAX_PLAYER; i++)
			{
				IServerUserItem * pIServerUserItem = GetServerUserItem(i);
				if(pIServerUserItem != NULL && m_thePlayerState[i] == OX_GS_PLAYING)
				{
					if(i != winner && i != m_bBaoPei - 1 && endgameMsg.theWinLose[i] == 0)
					{
						//bugid 6125 包赔时“倍数”要按照不包赔来显示，只是分数要包赔
						//endgameMsg.theFan[m_bBaoPei - 1] += endgameMsg.theFan[i];
						iScore[m_bBaoPei - 1] += iScore[i];
						//endgameMsg.theFan[i] = 0;
						iScore[i] = 0;
					}
				}
			}
			endgameMsg.theWhoBaoPei = m_bBaoPei;
		}
		for(int i = 0; i < MAX_PLAYER; i++)
		{
			AddSpecailScore(iScore,i,m_nBase*m_iBaseScore);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	else if(type == GOT_ZHONGTU)
	{
		endgameMsg.theEndType = CMD_S_EndGame_CB::GT_NORMAL;

		//流局后，所有人都显示输，但都不扣分
		for(int i = 0; i < MAX_PLAYER; i++)
		{
			IServerUserItem * pIServerUserItem = GetServerUserItem(i);
			if(pIServerUserItem != NULL && m_thePlayerState[i] == OX_GS_PLAYING)
			{
				iScore[i] = 0;
				endgameMsg.theWinLose[i] = 0;
				endgameMsg.theFan[i] = 0;
			}	
		}
		for(int i = 0; i < MAX_PLAYER; i++)
		{
			AddSpecailScore(iScore,i,m_nBase*m_iBaseScore);
		}
	}
	if(type == GOT_DISMISS)
	{
		endgameMsg.theEndType = CMD_S_EndGame_CB::GT_DISMISS;
		for(int i = 0; i < MAX_PLAYER; i++)
		{
			AddSpecailScore(iScore,i,m_nBase*m_iBaseScore);
		}
	}
	//强退和解散，当局分数不算
	if (type == GOT_ESCAPE || type == GOT_DISMISS || type == GOT_ZHONGTU)
	{
		//memset(endgameMsg.theFan,0,sizeof(endgameMsg.theFan));//番数清零
		memset(m_whoQuanGuan,0,sizeof(m_whoQuanGuan));//
		m_bBaoPei = 0;
		if (type == GOT_ESCAPE)
		{
			OnWriteGameRecord(winner,_T("强退ConcludeGame()......"));
		}
		else if (type == GOT_ZHONGTU)
		{
			OnWriteGameRecord(INVALID_CHAIR,_T("所有人都无法出牌，流局ConcludeGame()......"));
		}
		else{
			OnWriteGameRecord(winner,_T("解散游戏ConcludeGame()......"));
		}
	}else{
		OnWriteGameRecord(INVALID_CHAIR,_T("游戏正常结束ConcludeGame()......"));
	}

	for (BYTE i=0;i<MAX_PLAYER;i++)
	{
		endgameMsg.theScore[i] = iScore[i];
		int cn = 0;
		for(int j = 0; j < MAXCARD; j++)
		{
			if(m_dbplay[i][j] > CARDINDEX_NULL && m_dbplay[i][j] < CARDINDEX_BACK)
				endgameMsg.theLeftPai[i][cn++] = m_dbplay[i][j];
		}
		endgameMsg.byLeftCardsCount[i]= cn;//余牌数目
		//endgameMsg.iHandScore[i] = m_dagun.GetScore(endgameMsg.theLeftPai[i]);//暂时没有使用
		m_lastScore[i] = endgameMsg.theScore[i];
		m_total[i] += endgameMsg.theScore[i];
		endgameMsg.theTotalScore[i] = m_total[i];

		if (m_MaxScore[i]< m_playerscore[i])
		{
			m_MaxScore[i] = m_playerscore[i];
		}

		//endgameMsg.getScore[i] = m_playerscore[i];//暂时没有使用

	}

	if (type == GOT_ESCAPE)
	{
		endgameMsg.cbEndStatus = 2;
	}else if (type == GOT_DISMISS)
	{
		endgameMsg.cbEndStatus = 1;
	}

	//结算数据
	endgameMsg.theWhoKingBomb = m_whoHasKingBomb;
	endgameMsg.theWhoHardKill = m_whoHardKill;
	for(int i = 0; i < MAX_PLAYER; i++)
	{
		endgameMsg.theHardBomb[i] = m_playHardBomb[i];
		endgameMsg.theSoftBomb[i] = m_playSoftBomb[i];
		endgameMsg.theMagicBomb[i] = m_playMagicBomb[i];
		endgameMsg.theQuanGuan[i] = m_whoQuanGuan[i];

		endgameMsg.theToTalHardBomb += m_playHardBomb[i];
		endgameMsg.theToTalSoftBomb += m_playSoftBomb[i];
		endgameMsg.theToTalMagicBomb += m_playMagicBomb[i];
	}
	endgameMsg.theToTalKingBomb = (m_whoHasKingBomb > 0?1:0);
	endgameMsg.theGongType = byGongType;
	endgameMsg.cbType = 0;
	endgameMsg.addSpecialFlag = m_byAddSepcialFlag;
	//memcpy(endgameMsg.xiScore,m_xiScore,sizeof(endgameMsg.xiScore));//暂时没有使用
	
	//是否有不够输或不够赢的情况
	for(int i = 0; i < MAX_PLAYER; i++)
	{
		IServerUserItem * pIServUserItem = m_pITableFrame->GetServerUserItem(i);
		if (pIServUserItem != NULL && m_thePlayerState[i] == OX_GS_PLAYING)
		{
			long lMyScore = pIServUserItem->GetUserScore()->lScore;
			if (lMyScore > 0 && endgameMsg.theScore[i] < 0) //不够输
			{
				if(endgameMsg.theScore[i] < -(lMyScore - m_spay))
				{
					endgameMsg.theScore[i] = -(lMyScore - m_spay);
				}
			}
			else if (lMyScore > 0 &&  endgameMsg.theScore[i] > 0) //不够赢
			{
				if( endgameMsg.theScore[i] > lMyScore - m_spay)
				{
					endgameMsg.theScore[i] = lMyScore - m_spay;
				}
			}
		}	
	}

	//检查下是否不平衡
	GetFinalWinLoseScore(endgameMsg.theScore);

	//theWinLose只用来表示干笼、半笼的正负，不用来表示总分的输赢；总分输赢客户端用总分的正负来判断
	////调整输赢，正分为赢，负分为输，0分为平局
	//for (WORD i=0;i<GetPlayerCount();i++)
	//{
	//	endgameMsg.theWinLose[i] = 2;
	//	if (endgameMsg.theScore[i]>0)
	//	{
	//		endgameMsg.theWinLose[i] = 1;
	//	}
	//	else
	//	{
	//		endgameMsg.theWinLose[i] = 0;
	//	}
	//}

	SEND_TABLE_DATA_ALL(SUB_S_ENDGAME, endgameMsg);

	m_vecGameEnd.push_back(endgameMsg);  //保存，用于汇总计算

	//记录每个玩家开始游戏时所携带的分数
	for(int seat = 0; seat < MAX_PLAYER; seat++)
	{
		IServerUserItem * pIServerUserItem = m_pITableFrame->GetServerUserItem(seat);
		if(pIServerUserItem == NULL || pIServerUserItem->GetUserScore() == NULL|| m_thePlayerState[seat] != OX_GS_PLAYING)
		{
			continue;
		}
		//写日志记录 每个用户的输赢分数
		CString szCardRecord = _T("ID:");
		szCardRecord.AppendFormat("%d,输赢分数为:%d ",pIServerUserItem->GetUserID(),endgameMsg.theScore[seat]);	
		OnWriteGameRecord(seat,szCardRecord);
	}

	//记录过牌
	Replay_Order order;
	order.chair_id = winner;
	order.operation = E_EndGame;
	if (type == GOT_ESCAPE || type == GOT_DISMISS)
	{
		order.operation = E_GameJieSan;
	}

	m_sReplayRecord.vecOrder.push_back(order);

	//// 数据库写出牌记录
	//if ( m_cbGameEndStatus == GS_MJ_PLAY  || ( type != GOT_ESCAPE && type != GOT_DISMISS) )
	//{
	//	m_pITableFrame->TableWriteOutDate(m_CurCompleteCount, getWriteReplayRecordCString(1), getWriteReplayRecordCString(2));
	//}
	// 写完后清除数据
	m_sReplayRecord.reset();


	//数据库写分
	for (WORD i=0;i<GetPlayerCount();i++)
	{
		enScoreKind sktype = enScoreKind_Draw;
		if (endgameMsg.theScore[i]>0)
		{
			sktype = enScoreKind_Win;
		}
		else
		{
			sktype = enScoreKind_Lost;
		}
		if ( m_cbGameEndStatus == GS_MJ_PLAY) 
			//m_pITableFrame->TableWriteGameDate(m_CurCompleteCount, i, sktype, endgameMsg.theScore[i]);
			m_pITableFrame->WriteUserScore(i, endgameMsg.theScore[i] - m_spay,m_spay, sktype);
	}

	if (type != GOT_ESCAPE && type != GOT_DISMISS)
	{
		m_cbGameEndStatus = GS_MJ_END;
	}
	////结束游戏
	//if (m_CurCompleteCount >= m_rule.iJuShu || type == GOT_ESCAPE || type == GOT_DISMISS) //局数够了
	//{
	//	CalculateResultTotal(type); //计算总发送总结算

	//
	//	UpdateOtherFriendDate(endgameMsg, (type == GOT_ESCAPE || type == GOT_DISMISS));
	//	m_cbGameEndStatus = GS_MJ_END;
		//通知框架结束游戏
		m_pITableFrame->SetGameStatus(GS_MJ_FREE);
		m_pITableFrame->ConcludeGame(); 
	//}
	//else
	//{
	//	m_cbGameEndStatus = GS_MJ_END;
	//	//CalculateResultTotal(GER_NORMAL, false); //保存当前战绩，避免服务器出现异常中断导致战绩丢失
	//}

	////扣房卡
	//if (m_CurCompleteCount == 1 && type != GOT_ESCAPE && type != GOT_DISMISS)
	//{
	//	m_pITableFrame->TableDeleteFangKa();
	//}

	//下一局游戏，不准备，踢出房间
	//SetTimerGameStart(MAX_PLAYER, false);
	Reset();
}

void CGameLogic::UpdateOtherFriendDate(CMD_S_EndGame_CB& GameEnd, bool bEnd)
{
	int _jushu = m_CurCompleteCount;
	//4864 通山打拱的扣卡方式和斗棋一致
	//if (m_cbGameEndStatus != GS_MJ_END && m_cbGameEndStatus != GS_MJ_FREE)
	//{
	//	_jushu--;
	//}
	//m_pITableFrame->TableDeleteFangKa(_jushu);

	if ( m_rule.wCreateType != 0)
	{
		int _jushu2 = _jushu/m_pGameServiceOption->wGameJuShu;
		if (_jushu%m_pGameServiceOption->wGameJuShu > 0)
		{
			_jushu2 ++;
		}

		tag_OtherFriendCreate _info;
		ZeroMemory(&_info, sizeof(_info));
		_info.dwUserID = m_rule.dwFangZhuID;//req->dwUserID;
		_info.dwRoomNum = m_rule.iJuShu;//req->dwRoomID;
		_info.wKindID = KIND_ID;
		_info.wCreateType = m_rule.wCreateType;
		_info.wCurGameCount = _jushu2;

		bool bNOka= false;
		for (int i=0; i<m_vecGameEnd.size(); i++)
		{
			for (int j=0; j<GetPlayerCount(); j++)
			{
				_info.dwWinScore[j] += m_vecGameEnd[i].theScore[j];   //总分

				if (_info.dwWinScore[j] != 0)
				{
					if (m_cbGameEndStatus == GS_MJ_FREE)
					{
						bNOka = true;
					}

				}
			}
		}

		_info.wType = 2;

		//if (m_CurCompleteCount == 1 && bEnd && !bNOka)
		if (m_CurCompleteCount == 1 && m_cbGameEndStatus != GS_MJ_END && m_cbGameEndStatus != GS_MJ_FREE)//开始就解散时不加，每局结束后游戏状态会复位为GS_MJ_FREE
		{
			_info.wType = 3;
		}

		m_pITableFrame->TableAddCreateOtherFriend(&_info);
	}
	if (!bEnd)
	{
		tag_OtherFriendCreate _info;
		ZeroMemory(&_info, sizeof(_info));
		_info.dwUserID = m_rule.dwFangZhuID;//req->dwUserID;
		_info.dwRoomNum = m_rule.iJuShu;//req->dwRoomID;
		_info.wKindID = KIND_ID;
		_info.wCreateType = m_rule.wCreateType;

		_info.wType = 101;
		for (int i = 0; i < GetPlayerCount(); ++i)
		{
			_info.dwUserPlayerID[i] = m_pITableFrame->GetServerUserItem(i)->GetUserID();
		}
		m_pITableFrame->TableAddCreateOtherFriend(&_info);
	}
}

//计算总发送总结算
void CGameLogic::CalculateResultTotal(BYTE cbReason, bool bSendData)
{
	// 给客户端发送总结算数据
	//bool bNOka = true;
	CMD_S_BALANCE_GAME balanceGame; 
	balanceGame.userid = m_rule.dwFangZhuID;
	balanceGame.curTotalCount = m_CurCompleteCount;  //总盘数

	int _jushu = m_CurCompleteCount;
	if (m_cbGameEndStatus != GS_MJ_END && m_cbGameEndStatus != GS_MJ_FREE)
	{
		_jushu--;
	}
	balanceGame.cbTheCost = _jushu;

	for (int i=0; i<m_vecGameEnd.size(); i++)
	{
		for (int j=0; j<GetPlayerCount(); j++)
		{
			balanceGame.lGameScore[j] += m_vecGameEnd[i].theScore[j];   //总分

			//if (balanceGame.lGameScore[j] != 0 &&  (m_cbGameEndStatus == GS_MJ_FREE))
			//{
			//	bNOka = false;
			//}
		}
	}

	//bugid 4997 通山打拱添加大赢家支付功能，有大赢家
	int iMaxScore = 0;
	int iMaxScoreCount = 0;
	int iChairID = 0;
	for (int i = 0; i < GetPlayerCount();++i )
	{
		if (iMaxScore < balanceGame.lGameScore[i])
		{
			iMaxScore = balanceGame.lGameScore[i];
		}
	}

	// 遍历一下最大值的数量
	for (int j = 0; j < GetPlayerCount();++j)
	{
		if (iMaxScore == balanceGame.lGameScore[j])
		{
			iChairID = j;
			iMaxScoreCount++;
		}
	}
	if (iMaxScoreCount == 1 && m_rule.wCreateType == 3) // 大赢家只有一个并且是大赢家支付模式下，大赢家支付
	{
		IServerUserItem * pIServerUserItem = m_pITableFrame->GetServerUserItem(iChairID);
		DWORD userid = pIServerUserItem->GetUserID();
		m_pITableFrame->TableDeleteDaYingJiaFangKa(userid);
	}

	for ( int i  = 0; i < GetPlayerCount();++i)
	{
		balanceGame.wZMHuUserCount[i] = 0;//m_ZMHuUserCount[i];
		balanceGame.wJPHuUserCount[i] = 0;//m_PHuUserCount[i];
		balanceGame.wMGangUserCount[i] = 0;//m_MGangUserCount[i];
		balanceGame.wAGangUserCount[i] = 0;//m_AnGangUserCount[i];

		balanceGame.wChiHuUserCount[i] = 0;//m_ChiHuUserCount[i];
		balanceGame.wRoarCount[i] = m_totalDuPai[i];
		balanceGame.wFirstTurnCount[i] = m_totalFirstTurn[i];
		balanceGame.wMaxGetScore[i] = m_MaxScore[i];
		balanceGame.w7XiCount[i] = m_whoTotal7Xi[i];
		balanceGame.w8XiCount[i] = m_whoTotal8Xi[i];
		balanceGame.wLongZhaCount[i] = m_whoTotalGonglong[i];

		enScoreKind type = enScoreKind_Draw;
		if (balanceGame.lGameScore[i]>0)
		{
			type = enScoreKind_Win;
		}
		else
		{
			type = enScoreKind_Lost;
		}

		if (m_CurCompleteCount == 1 && m_cbGameEndStatus != GS_MJ_END && m_cbGameEndStatus != GS_MJ_FREE)//开始就解散时不加，每局结束后游戏状态会复位为GS_MJ_FREE
		{
			type = enScoreKind_pass;
		}

		//写记录
		m_pITableFrame->TableWriteGameDateTotal(m_CurCompleteCount, i,  type, balanceGame.lGameScore[i]);
	}

	//发消息
	if (bSendData) SEND_TABLE_DATA(INVALID_CHAIR,SUB_S_GAME_BALANCE_GAME,balanceGame);
}

// 结束一轮
bool CGameLogic::EndTurn()
{
	for(int i = 0; i < MAXCARD; i++)
	{
		m_lastPaiOut[m_whoplayout-1][i] = m_allPaiOutNoMagic[m_whoplayout-1][i];
	}
	for(int i =0;i<MAX_PLAYER;i++)
	{
		m_whoPass[i] = 0;
		m_byEveryOneCurlunOutCnt[i] = 0;
	}
	memset(m_allPaiOutNoMagic,0,sizeof(m_allPaiOutNoMagic));
	memset(m_allPaiOut,0,sizeof(m_allPaiOut));
	memset(m_OutPaifakeking,0,sizeof(m_OutPaifakeking));
	m_lastOutType = TYPE_NULL;
	m_whoplayout = 0;
	m_bBaoPei = 0;

	//结束一轮时，要关闭插底提示，因为这个时候不知道会不会出单张牌
	SendPlaySoundMsg(0,CMD_CS_msgPlaySound_CB::TY_ChaDi,0);

	EndOut();//结束一轮
	return false;
}

//必须发生结束一轮的消息，否则客户端不知道什么时候更新一轮结束标记
void CGameLogic::EndOut()
{
	m_lastOutType = TYPE_NULL;

	CMD_S_EndOut_CB endout;

	endout.theWhoPlay = m_whoplay;

	SEND_TABLE_DATA_ALL(SUB_S_ENDOUT, endout);
}

//发牌
void CGameLogic::SendPai()
{
	if (m_cbLeftCardCount > 0)
	{
		CMD_S_SendPoker_OX sendpokerInfo;
		sendpokerInfo.thelunshu = 0;
		sendpokerInfo.theSeat = 0;
		sendpokerInfo.theType = TYPE_ONE;
		sendpokerInfo.theXianshou = m_whoplay;//客户端用来控制谁先发牌
		sendpokerInfo.theIsKanpai = false;

		//发送牌数据给玩家
		for(int i = 0; i < MAX_PLAYER; i++)
		{	
			//先给先手发牌
			int seat = (i + m_whoplay - 1)%MAX_PLAYER;
			IServerUserItem * pIServerUserItem = GetServerUserItem(seat);
			//需要给旁观玩家发牌
			if(pIServerUserItem == NULL || m_thePlayerState[seat] != OX_GS_PLAYING /*|| !m_cbPlayStatus[seat]*/)
			{
				continue;
			}
			//写日志记录 
			CString szCardRecord = _T("肉挨肉游戏，");

			if (m_cbLeftCardCount > 0)
			{
				sendpokerInfo.theCardsCount[seat] = 1;
				sendpokerInfo.theCards[seat][0] = m_dbp[--m_cbLeftCardCount];
				BYTE byTempCardNum = (m_thePaiCount[seat]>= MAXCARD? MAXCARD - 1:m_thePaiCount[seat]);
				m_dbplay[seat][byTempCardNum] = sendpokerInfo.theCards[seat][0];
				m_thePaiCount[seat] += sendpokerInfo.theCardsCount[seat];

				//记录发牌
				Replay_Order order;
				order.chair_id = seat;
				order.operation = E_SendCard;
				order.value.push_back(sendpokerInfo.theCards[seat][0]);
				m_sReplayRecord.vecOrder.push_back(order);

				szCardRecord.AppendFormat("发牌数据为:0x%02x,",switchCard2Ox(sendpokerInfo.theCards[seat][0]));	
			}
			else
			{
				szCardRecord.AppendFormat("牌已发完，无发牌数据,");	
			}
			szCardRecord.AppendFormat("玩家椅子id:%d ,【当前牌数量:%d 】",seat,m_thePaiCount[seat]);
			//后记录日志
			OnWriteGameRecord(seat,szCardRecord);

		}
		sendpokerInfo.theLeftCardsCount = m_cbLeftCardCount;
		SEND_TABLE_DATA_ALL(SUB_S_SEND_POKER_OX,sendpokerInfo);

		SendPaiCount();
	}
}


//计算特殊牌型加分，不包括笼炸分数，笼炸分数另外算
void CGameLogic::AddSpecailScore(long Score[MAX_PLAYER],int seat,int base)
{
	if(seat < 0 && seat >= MAX_PLAYER)
		return;
	if (0 == m_byAddSepcialFlag)//特殊牌型不加分
	{
		return;
	}
}
void CGameLogic::GetFinalWinLoseScore( long long score[MAX_PLAYER] )
{
	int wintotal=0,losetotal=0;
	int total[MAX_PLAYER] = {0};
	for(int i = 0; i < MAX_PLAYER; i++)
	{
		total[i] = score[i];
		if(score[i] <= 0)
		{
			losetotal += score[i];
		}
		else
		{
			wintotal += score[i];
		}
	}
	if(wintotal == 0 || losetotal == 0)
		return;
	if(wintotal > -losetotal)
	{//赢的分比输的分多
		//float scale = -1.0f * losetotal / wintotal;//修改小数部分截断导致的误差超过1的问题

		int fixIndex = 0;
		//重新计算赢的分数
		int iTempwintotal = 0;
		for(int i = 0; i < MAX_PLAYER; i++)
		{
			if(score[i] > 0)
			{
				total[i] = -score[i] * losetotal / wintotal;
				iTempwintotal += total[i];
				fixIndex = i;
			}
		}

		//调整小数点误差
		total[fixIndex] -= iTempwintotal + losetotal;
	}
	else if (wintotal < -losetotal)
	{//赢的分比输的分少
		//float scale = -1.0f * wintotal / losetotal;//修改小数部分截断导致的误差超过1的问题

		int fixIndex = 0;
		//重新计算输的分数
		int iTemplosetotal = 0;
		for(int i = 0; i < MAX_PLAYER; i++)
		{
			if(score[i] < 0)
			{
				total[i] = -score[i] * wintotal / losetotal;
				iTemplosetotal += total[i];
				fixIndex = i;
			}
		}

		//调整小数点误差
		total[fixIndex] -= wintotal + iTemplosetotal;
	}

	for(int i =0; i < MAX_PLAYER; i++)
	{
		score[i] = total[i];
	}
}


void CGameLogic::SendTurnScore(int wChairID)
{
	CMD_CS_TurnScore_CB turnScore;

	turnScore.theScore = m_score;

	if(wChairID == INVALID_CHAIR)
		SEND_TABLE_DATA_ALL(SUB_S_TURNSCORE,turnScore);
	else if(wChairID>=0&&wChairID<MAX_PLAYER)
		SEND_TABLE_DATA(wChairID,SUB_S_TURNSCORE,turnScore);
}

void CGameLogic::SendPlayerScore(int wChairID, int _ichair, int _score)
{
	CMD_CS_PLAYSCORE_CB playScore;
	playScore.iChair = _ichair;
	playScore.getScore = _score;
	
	for(int i = 0;i < MAX_PLAYER;i++)
	{
		playScore.theScore[i] = m_playerscore[i];
	}

	if(wChairID == INVALID_CHAIR)
		SEND_TABLE_DATA_ALL(SUB_S_PLAYERSCORE,playScore);
	else if(wChairID>=0&&wChairID<MAX_PLAYER)
		SEND_TABLE_DATA(wChairID,SUB_S_PLAYERSCORE,playScore);
}

void CGameLogic::SendPaiCount(int wChairID)
{
	CMD_CS_SendCount_CB paiCount;

	for(int i = 0; i < MAX_PLAYER; i++)
		paiCount.thePaiCount[i] = m_thePaiCount[i];

	if(wChairID == INVALID_CHAIR)
		SEND_TABLE_DATA_ALL(SUB_S_SENDCOUNT,paiCount);
	else if(wChairID>=0&&wChairID<MAX_PLAYER)
		SEND_TABLE_DATA(wChairID,SUB_S_SENDCOUNT,paiCount);
}

void CGameLogic::SendFanShu(int wChairID)
{
	CMD_CS_FanShu_CB fanShu;

	fanShu.theCurFanShu = m_iCurrentFanShu;

	if(wChairID == INVALID_CHAIR)
		SEND_TABLE_DATA_ALL(SUB_S_FANSHU,fanShu);
	else if(wChairID>=0&&wChairID<MAX_PLAYER)
		SEND_TABLE_DATA(wChairID,SUB_S_FANSHU,fanShu);
}

void CGameLogic::sendGameStatus(WORD wChair ,bool isReLink, IServerUserItem * pIServerUserItem)
{
	WORD theSeat = wChair;
	//if(isReLink)//断线重连
	{
		//if(!IsGamePlaying())
		//	return;
		

		//发送底分
		CMD_CS_GameRule msgRule;
		msgRule.theBase = m_pGameServiceOption->lCellScore * m_iBaseScore;
		msgRule.theSeverCharge = m_spay;
		msgRule.iFaOfTao = m_iFaOfTao;
		msgRule.iJiangOfTao = m_iJiangOfTao;
		msgRule.theMinGameScore = m_pGameServiceOption->lLessScore;//进入房间的最小财富
		msgRule.theMaxGameScore = m_pGameServiceOption->lMaxScore;//进入房间的最大财富
		msgRule.isShowChardCount = m_byIsShowChardCount;
		msgRule.iFakeKingValue = m_byFakeKingValue;
		msgRule.iMaxKingNum = m_byMaxKingNum;

		SEND_TABLE_DATA(wChair,SUB_CS_GAMERULE,msgRule);			

		m_whoBreak[theSeat] = FALSE;//重连嘛，所以取消断线

		//旁观者坐下收到游戏状态消息
		if (m_thePlayerState[theSeat] == OX_GS_SITDOWN)
		{
			if (m_GameState != gsNull)
			{
				CMD_S_GAME_STATE_OX stateInfo;
				stateInfo.theGameState = m_GameState;
				stateInfo.theBanker = m_banker;
				if(m_tDownTime-GetCPUTickCount() > 0)
					stateInfo.theLeftTime	= m_tDownTime - GetCPUTickCount();
				else
					stateInfo.theLeftTime	= 0;

				stateInfo.theLastPaiType  = m_lastOutType;//上一次出牌的类型，可能没用？
				stateInfo.theGameState	= m_GameState;//游戏状态
				stateInfo.theWhoPlay	= m_whoplay;//当前玩家
				stateInfo.theWhoPlayOut	= m_whoplayout;//上一个玩家

				for(int i = 0; i < MAX_PLAYER; i++)
				{
					stateInfo.theWhoBreak[i]	= m_whoBreak[i];//掉线的有那些人
					stateInfo.theTuoGuan[i]	= m_TuoGuanPlayer[i];//托管的有那些人
					stateInfo.thePass[i]		= m_whoPass[i];//谁放弃
					stateInfo.thePaiCount[i]	= m_thePaiCount[i];
					for(int j = 0; j < MAXCARD; j++)
					{
						stateInfo.theOutCard[i][j] = m_allPaiOut[i][j];//刚才出的牌
						stateInfo.theLastOutCard[i][j] = m_lastPaiOut[i][j];//上一轮出的牌，（这个其实可以不要）
					}
				}
				memcpy(stateInfo.theOutPaifakeking,m_OutPaifakeking,sizeof(m_OutPaifakeking));//注意，不要越界
				stateInfo.theLeftCardCount = m_cbLeftCardCount;
				stateInfo.theFanShu = m_iCurrentFanShu;
				SEND_TABLE_DATA(theSeat,SUB_S_GAME_STATE_OX, stateInfo);

				//插底提示 
				if(m_lastOutType == TYPE_ONE && IsSamePlayerOneCard(MAX_PLAYER))
				{
					SendPlaySoundMsg(0,CMD_CS_msgPlaySound_CB::TY_ChaDi);
				}

				//剩余牌数量
				//SendPaiCount();
			}
			return;
		}

		//提示其他玩家，我又回来了！
		CMD_CS_msgReLinkTip msgTip;
		msgTip.theSeat = theSeat;
		msgTip.theFlag = 0;
		SEND_TABLE_DATA_OTHER(theSeat,msgTip.XY_ID,msgTip);

		CMD_CS_msgReLink reLinkMsg;
		reLinkMsg.theChair = theSeat;
		reLinkMsg.cbTheOrder = m_CurCompleteCount;

		if(m_tDownTime-GetCPUTickCount() > 0)
			reLinkMsg.theLeftTime	= m_tDownTime - GetCPUTickCount();
		else
			reLinkMsg.theLeftTime	= 0;

		reLinkMsg.theLastPaiType  = m_lastOutType;//上一次出牌的类型，可能没用？
		reLinkMsg.theGameState	= m_GameState;//游戏状态
		reLinkMsg.theWhoPlay	= m_whoplay;//当前玩家
		reLinkMsg.theWhoPlayOut	= m_whoplayout;//上一个玩家
		//reLinkMsg.theTurnScore	= m_score;//本轮分 暂时没有使用
		reLinkMsg.theBanker       = m_banker;//庄家
		//reLinkMsg.theRoarPai		= m_RoarPai;//叫的什么牌 暂时没有使用

		for(int i = 0; i < MAX_PLAYER; i++)
		{
			reLinkMsg.theWhoBreak[i]	= m_whoBreak[i];//掉线的有那些人
			reLinkMsg.theTuoGuan[i]	= m_TuoGuanPlayer[i];//托管的有那些人
			//reLinkMsg.theLast[i]		= m_lastScore[i];//上一轮输赢 暂时没有使用
			reLinkMsg.theTotal[i]		= m_total[i];//总输赢
			reLinkMsg.thePass[i]		= m_whoPass[i];//谁放弃
			reLinkMsg.theWhoReady[i]	= m_thePlayerState[i];//是否游戏中
			reLinkMsg.thePaiCount[i]	= m_thePaiCount[i];
			//reLinkMsg.theWhoRoar      = m_WhoRoar;//谁叫了牌 暂时没有使用
			//reLinkMsg.Score[i] = m_playerscore[i];//每个人的分 暂时没有使用
			//if(m_bMingJi)
			//	reLinkMsg.theWhoMJ    = m_parter;//谁鸣鸡 暂时没有使用
			for(int j = 0; j < MAXCARD; j++)
			{
				reLinkMsg.theOutCard[i][j] = m_allPaiOut[i][j];//刚才出的牌
				reLinkMsg.theLastOutCard[i][j] = m_lastPaiOut[i][j];//上一轮出的牌，（这个其实可以不要）
			}
		}
		memcpy(reLinkMsg.theOutPaifakeking,m_OutPaifakeking,sizeof(m_OutPaifakeking));//注意，不要越界
		//自己有什么样的牌
		memcpy(reLinkMsg.theCards,m_dbplay[theSeat],sizeof(reLinkMsg.theCards));
		reLinkMsg.theTGTime = m_TrustCounts[theSeat];
		reLinkMsg.theLeftCardCount = m_cbLeftCardCount;
		reLinkMsg.theFanShu = m_iCurrentFanShu;

		SEND_TABLE_DATA(theSeat,reLinkMsg.XY_ID,reLinkMsg);

		//插底提示 
		if(m_lastOutType == TYPE_ONE && IsSamePlayerOneCard(MAX_PLAYER))
		{
			SendPlaySoundMsg(0,CMD_CS_msgPlaySound_CB::TY_ChaDi);
		}

		//剩余牌数量
		//SendPaiCount(wChair);

		////自己有什么样的牌
		//CMD_S_GameStart_CB sendpaimsg;

	 //   sendpaimsg.theIsGameStart = FALSE;
	 //   sendpaimsg.theBanker = m_whoplay;
		//sendpaimsg.theSeat = theSeat;
		//sendpaimsg.theType = CMD_S_GameStart_CB::GAME_RELINK;
		//BYTE count = 0;
		//for(int i = 0;i < MAXCARD; i++)
		//{
		//	if(m_dbplay[theSeat][i] > 0 && m_dbplay[theSeat][i] < 55)
		//	{
		//		sendpaimsg.theCards[count] = m_dbplay[theSeat][i];
		//		count++;
		//	}
		//}
		//sendpaimsg.theCount = count;
		//sendpaimsg.theLeftCardsCount = m_cbLeftCardCount;

		//SEND_TABLE_DATA(theSeat,SUB_S_GAME_START,sendpaimsg);

		SendTaskID(false, theSeat);

		 if(m_GameState ==gsPlay)
		{
			SendPower(m_whoplay,CMD_S_Power_CB::p_Out,reLinkMsg.theLeftTime);
		}

		//发小结消息
		if (m_vecGameEnd.size() == m_CurCompleteCount && m_CurCompleteCount != 0 && theSeat < GetPlayerCount() && theSeat >= 0)
		{
			//发消息
			CMD_S_EndGame_CB gamend = m_vecGameEnd[m_CurCompleteCount-1];
			//gamend.bBirdCard = 1;  //表示为断线重连
			gamend.cbType = 1;

			SEND_TABLE_DATA(theSeat,SUB_S_ENDGAME ,gamend);
		}

		//发送解散房间所有玩家的反应
		m_pITableFrame->SendAllPlayerDissmissInfo(pIServerUserItem);

	}
}


BOOL CGameLogic::IsGamePlaying()
{
	return  (m_GameState != gsNull)? TRUE : FALSE;
}


//解析配置的任务,格式： "1@5/2@5/33@10"
void CGameLogic::ParseTaskConfig(const string& strTaskID)
{
	if (strTaskID.size() == 0)
	{
		return;
	}

	vector<string> vecID;
	stovs(strTaskID, "/", vecID);
	for (int i=0; i<vecID.size(); i++)
	{
		vector<string> details;
		stovs(vecID[i], "@", details);
		if (details.size() == 2)
		{
			int id = atoi(details[0].c_str());
			int fans = atoi(details[1].c_str());
			if (id > 0 && fans > 0)
			{
				m_mapAllTask[id] = fans;

				//特殊处理下：有3个任务不能作为随机选择项
				if (id == TASK_ZHUA_TIAN || id == TASK_ZHUA_7_XI || id == TASK_ZHUA_8_XI)
				{
					//nothing
				}
				else
				{
					m_vecAllTaskID.push_back(id);
				}
			}
		}
	}
}

//发送随机任务
void CGameLogic::SendTaskID (bool bFirst, BYTE nSeat)
{
	int iSize = m_vecAllTaskID.size();
	if (iSize > 0)
	{
		//生成随机数
		if(bFirst)
		{
			if (g_iDebug > 0)
			{
				if (100 == g_iDebug)
				{
					m_iRandomTask = (++m_iRandomTask)%iSize;
				}
				else
				{
					m_iRandomTask = g_iDebug - 1;
				}
			}
			else
			{
				m_iRandomTask = rand()%iSize;
			}
		}

		if (m_iRandomTask < iSize)
		{
			if (m_mapAllTask.find(m_vecAllTaskID[m_iRandomTask]) != m_mapAllTask.end())
			{
				//发送给客户端
				CMD_CS_msgTaskID msgTask;
				//InitMsg(taskID);
				memset(&msgTask, 0, sizeof(msgTask));
				msgTask.theID = m_vecAllTaskID[m_iRandomTask];
				msgTask.theAward = m_mapAllTask[msgTask.theID];
				//m_iRandomTask = taskID.theID;

				if(bFirst)
				{
					SEND_TABLE_DATA_ALL(SUB_CS_RAND_TASK_ID , msgTask);
				}
				else
				{
					SEND_TABLE_DATA(nSeat, SUB_CS_RAND_TASK_ID, msgTask);
				}
			}
			else
			{
				//:-( 应该永远不会执行这句
				m_iRandomTask = -1;
			}
		}
		else
		{
			//:-( 应该永远不会执行这句
			m_iRandomTask = -1;
		}
	}

	//如果是抓牌就奖励的任务，也在这里处理
	//if (m_whoHasKingBomb > 0 && m_whoHasKingBomb <= MAX_PLAYER)
	//{
	//	m_vecFinishedTask[m_whoHasKingBomb-1].push_back(TASK_ZHUA_TIAN);
	//	SendFinishTask(m_whoHasKingBomb-1, TASK_ZHUA_TIAN, 1, false);  //只发给自己
	//}
	//for(int i = 0; i < MAX_PLAYER; i++)
	//{
	//	if (m_who8Xi[i] > 0)
	//	{
	//		m_vecFinishedTask[i].insert(m_vecFinishedTask[i].end(), m_who8Xi[i], TASK_ZHUA_8_XI);
	//		SendFinishTask(i, TASK_ZHUA_8_XI, m_who8Xi[i], false); //只发给自己
	//	}
	//}
	//for(int i = 0; i < MAX_PLAYER; i++)
	//{
	//	if (m_who7Xi[i] > 0)
	//	{
	//		m_vecFinishedTask[i].insert(m_vecFinishedTask[i].end(), m_who7Xi[i], TASK_ZHUA_7_XI);
	//		SendFinishTask(i, TASK_ZHUA_7_XI, m_who7Xi[i], false); //只发给自己
	//	}
	//}
}

//判断任务是否完成
#define TASK_FINISH(seat,id)  do{if (m_iRandomTask < m_vecAllTaskID.size() && m_vecAllTaskID[m_iRandomTask] == id){m_vecFinishedTask[seat].push_back(id);SendFinishTask(seat,id);m_bHaveOutCard = true;}}while(0)
void CGameLogic::IsTaskFinished(const TCardType& re, int iSeat, int iNumOfKing)
{
	if (re.type == TYPE_BOMB_510K && iNumOfKing == 0)
	{
		switch (re.color)
		{
		case CC_SPADE_S:
			{
				TASK_FINISH(iSeat,TASK_HEI_510K);
			}
			break;
		case CC_HEART_S:
			{
				TASK_FINISH(iSeat,TASK_HONG_510K);
			}
			break;
		case CC_CLUB_S:
			{
				TASK_FINISH(iSeat,TASK_MEI_510K);
			}
			break;
		case CC_DIAMOND_S:
			{
				TASK_FINISH(iSeat,TASK_FANG_510K);
			}
			break;
		default:
			break;
		}
	}
	else if (re.type == TYPE_BOMB_NOMORL && re.len == 4 && iNumOfKing == 0)
	{	
		switch (GetCardPoint(re.card))
		{
		case CP_2_S:
			{
				TASK_FINISH(iSeat,TASK_4_2);
			}
			break;
		case CP_5_S:
			{
				TASK_FINISH(iSeat,TASK_4_5);
			}
			break;
		case CP_10_S:
			{
				TASK_FINISH(iSeat,TASK_4_10);
			}
			break;
		case CP_K_S:
			{
				TASK_FINISH(iSeat,TASK_4_K);
			}
			break;
		default:
			break;
		}
	}
	else if (re.type == TYPE_BOMB_STR)
	{
		TASK_FINISH(iSeat,TASK_YAO_BAI);
	}
	else if (m_bHaveOutCard == false && re.type == TYPE_TWOSTR && iNumOfKing == 0)
	{
		//首次打出连对
		if (re.len > 7)
		{
			TASK_FINISH(iSeat,TASK_FIRST_4_STR);
		}
		else if (re.len == 6)
		{
			switch (GetCardPoint(re.card))
			{
			case CP_8_S:
				{
					TASK_FINISH(iSeat,TASK_FIRST_STR_678);
				}
				break;
			case CP_9_S:
				{
					TASK_FINISH(iSeat,TASK_FIRST_STR_789);
				}
				break;
			case CP_J_S:
				{
					TASK_FINISH(iSeat,TASK_FIRST_STR_910J);
				}
				break;
			case CP_Q_S:
				{
					TASK_FINISH(iSeat,TASK_FIRST_STR_10JQ);
				}
				break;
			case CP_K_S:
				{
					TASK_FINISH(iSeat,TASK_FIRST_STR_JQK);
				}
				break;
			case CP_A_S:
				{
					TASK_FINISH(iSeat,TASK_FIRST_STR_QKA);
				}
				break;
			default:
				break;
			}
		}
	}
}

void CGameLogic::IsTaskFinishedOfLastHand(const TCardType& re, int iSeat, int iNumOfKing)
{
	if (re.type == TYPE_BOMB_510K  && iNumOfKing == 0)
	{
		switch (re.color)
		{
		case CC_SPADE_S:
			{
				TASK_FINISH(iSeat,TASK_LAST_HEI_510K);
			}
			break;
		case CC_HEART_S:
			{
				TASK_FINISH(iSeat,TASK_LAST_HONG_510K);
			}
			break;
		case CC_CLUB_S:
			{
				TASK_FINISH(iSeat,TASK_LAST_MEI_510K);
			}
			break;
		default:
			break;
		}
	}
	else if (re.type == TYPE_TWO && iNumOfKing == 0)
	{
		switch (GetCardPoint(re.card))
		{
		case CP_5_S:
			{
				TASK_FINISH(iSeat,TASK_LAST_DOUBLE_5);
			}
			break;
		case CP_10_S:
			{
				TASK_FINISH(iSeat,TASK_LAST_DOUBLE_10);
			}
			break;
		case CP_K_S:
			{
				TASK_FINISH(iSeat,TASK_LAST_DOUBLE_K);
			}
			break;
		default:
			break;
		}
	}
	else if (re.type == TYPE_TWOSTR && iNumOfKing == 0)
	{
		//打出连对
		if (re.len > 7)
		{
			TASK_FINISH(iSeat,TASK_LAST_4_STR);
		}
		else if (re.len == 6)
		{
			switch (GetCardPoint(re.card))
			{
			case CP_8_S:
				{
					TASK_FINISH(iSeat,TASK_LAST_STR_678);
				}
				break;
			case CP_9_S:
				{
					TASK_FINISH(iSeat,TASK_LAST_STR_789);
				}
				break;
			case CP_J_S:
				{
					TASK_FINISH(iSeat,TASK_LAST_STR_910J);
				}
				break;
			case CP_Q_S:
				{
					TASK_FINISH(iSeat,TASK_LAST_STR_10JQ);
				}
				break;
			case CP_K_S:
				{
					TASK_FINISH(iSeat,TASK_LAST_STR_JQK);
				}
				break;
			case CP_A_S:
				{
					TASK_FINISH(iSeat,TASK_LAST_STR_QKA);
				}
				break;
			default:
				break;
			}
		}
	}
	else if (re.type == TYPE_ONE && GetCardPoint(re.card) == CP_3_S && iNumOfKing == 0)
	{
		TASK_FINISH(iSeat,TASK_LAST_3);
	}
}

//发送完成了的任务
void CGameLogic::SendFinishTask (int iSeat, int id, int cnt,bool bToAll)
{
	if (m_mapAllTask.find(id) != m_mapAllTask.end())
	{
		//发送给客户端
		CMD_CS_msgFinishedTaskID msgFinishedTask;
		//InitMsg(msgFinishedTask);
		memset(&msgFinishedTask, 0, sizeof(msgFinishedTask));
		msgFinishedTask.theID = id;
		msgFinishedTask.theSeat = iSeat;
		msgFinishedTask.theCnt = cnt;
		msgFinishedTask.theTotal = m_mapAllTask[id] * msgFinishedTask.theCnt;

		if (bToAll)
		{
			SEND_TABLE_DATA_ALL(SUB_CS_RAND_FINISHED_TASK , msgFinishedTask);
		}
		else
		{
			SEND_TABLE_DATA(iSeat , SUB_CS_RAND_FINISHED_TASK , msgFinishedTask);
		}

		//发放奖励的详细描述直接写到日志文件中去
		//m_pITableFrame->WriteUserScore(wChairID, lScore, lRevenue, ScoreKind, lPlayTimeCount=-1, lAward=0);
		//写日志文件 
		//TraceMessage(GetTaskAwardDetails(iSeat).c_str());
	}
}

//获取奖励数
int CGameLogic::GetTaskAward(int iSeat)
{
	int iTotal = 0;
	for (int i=0; i<m_vecFinishedTask[iSeat].size(); i++)
	{
		int id = m_vecFinishedTask[iSeat][i];
		if (m_mapAllTask.find(id) != m_mapAllTask.end())
		{
			iTotal += m_mapAllTask[id];
		}
	}

	return iTotal;
}

//获取奖励详细.必须小于255
string CGameLogic::GetTaskAwardDetails(int iSeat)
{
	string details;
	for (int i=0; i<m_vecFinishedTask[iSeat].size(); i++)
	{
		char id[16];
		memset(id, 0, 16);
		sprintf(id, "AwardCount=%d|", m_vecFinishedTask[iSeat][i]);

		details += id;
	}

	if (details.size() > 255)
	{
		details.resize(255);
	}
	return details;
}

}; //end of namespace
///////////////////////////////////////////////////////////////////////////////////////////////////////

