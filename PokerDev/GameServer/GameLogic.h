#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__

#include <vector>
#include <list>
#include <map>
#include "DaGun.h"
#include "../XY/CMD_DaGong4.h"
#include "TableFrameSink.h"

namespace nsRouAiRou
{
//#define INVALID_CHAIR 0xFFFF

// 游戏状态
typedef enum tagGameState
{
	gsNull = 0,
	gsRoarPai,	// 吼牌
	gsPlay,		// 打牌
}GameState;

//好友房相关属性
struct st_FriendRule{
	int								iLocal;				//哪个地方的玩法
	DWORD							dwFangZhuID;		//房主ID
	int								iJuShu;				//局数
	int								iTypeLaizi;			//癞子类型
	int								iWanFa;				//玩法
	int								iFengDing;			//封顶番数
	int								iFentDingStep1;		//封顶的基础分倍数
	int								iFentDingStep2;		//封顶的基础分倍数
	int								iFentDingStep3;		//封顶的基础分倍数
	int								iFentDingStep4;		//封顶的基础分倍数
	int								iMinFan;			//最小番数
	bool							bKouKou;			//是否口口番
	bool							b7Dui;				//是否七对
	bool							bNeedKaiKou;		//是否需要开口
	int								iBird;				//抓鸟个数
	int								iBirdFan;			//抓鸟结算番数
	bool							bOnlyZimo;			//只能自摸
	bool							bZhuangxian;		//是否庄闲
	bool							bHongZhongLai;		//是否红中赖子
	bool                            bHongZhongPi;        //是否为红中皮子
	int								iZhuangxianFan;		//庄闲时庄家输赢增加的分数
	int								iGangFan;			//点杠多少分
	bool							bReChonHu;			//是否可以热铳
	bool							bQiangGangBao;		//抢杠胡时是否一人全包，不全包就按普通放铳计算
	bool                            bHongZhongFan;      //杠牌是否跟着红中算番
	bool							bNoWan;				//无万字牌，三人玩法时，可以勾选是否去万

	int								iDiFen;				//底分
	WORD							wCreateType	;
};


class CGameLogic : public CTableFrameSink
{
	//////////////////////////////////////////////////////////////////////////
	// 构造
public:
	CGameLogic(void);
	virtual ~CGameLogic(void);

	//////////////////////////////////////////////////////////////////////////
	// 游戏接口
	//定时器事件
	virtual bool __cdecl OnTimerMessage(WORD wTimerID, WPARAM wBindParam);

	//框架判定游戏结束
	virtual bool __cdecl OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);

	virtual bool __cdecl SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret);
	
	//用户断线
	virtual bool __cdecl OnActionUserOffLine(WORD wChairID, IServerUserItem * pIServerUserItem); 
	//用户重入
	virtual bool __cdecl OnActionUserReConnect(WORD wChairID, IServerUserItem * pIServerUserItem);
	//用户坐下
	virtual bool __cdecl OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//用户起来
	virtual bool __cdecl OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//用户同意
	virtual bool __cdecl OnActionUserReady(WORD wChairID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize);

public:	
	//产生牌数据
	void  ProduceCards();
	//谁是先手，第一局时使用,返回值 1-MAX_PLAYER
	BYTE GetXianShou();
	// 开启下一局
	bool StartNextGame();							
	// 游戏开始
	void OnStartGame();	
	void OnGameAction(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
	
	//做牌
	void SetDebugCard(const string &_file);
	int	 getCardIndexByOx(BYTE _card);

	// 清空所有状态与数据,此函数请谨慎调用。
	void Reset();
	void InitGame();
	long GetCPUTickCount( void );

public:
	/*一些纸牌游戏共有的服务器数据*/
	enum ActionStep		// 游戏步骤
	{//修改步骤
		AS_NULL = 0,
		AS_GAMESTART ,  //播放开场时发牌动画
		AS_ROAR,		// 硬牌
		AS_ENDROAR,		// 结束硬牌
		AS_PLAY,		// 打牌
		AS_ENDPLAY,		// 打牌结束
		AS_ENDGAME,		// 结束游戏
		AS_COUNT
	};
	enum GameOverType
	{
		GOT_NULL = 0,
		GOT_ESCAPE,		//有人逃跑，游戏结束
		GOT_NORMAL,		//正常的结束游戏，即：在找朋友的模式下，三家走完，在吼牌模式下，一家走完
		GOT_ZHONGTU,    //中途结束游戏，即满足一定的条件，结束了游戏
		GOT_DOUBLEKILL,	//“绑”，意为双杀，在找朋友的模式下，一方为一游和二游走完
		GOT_TUOGUAN, // 每轮托管次数限制为5轮
		GOT_DISMISS,//解散
	};

	GameState	m_GameState;			// 游戏状态//游戏中有多个阶段时需要使用这个来区分
	int			m_tDownTime;			// 权限停止时间
	int			m_tPowerStartTime;		// 权限开始时间
	ActionStep	m_theActionStep;		// 倒计时
	ActionStep	m_nowActionStep;	

	//一些共有的游戏数据

	BYTE		m_byIsShowChardCount;   // 是否显示手牌数目
	BYTE		m_byMaxKingNum;         // 王数目，4王或8王
	BYTE		m_byFakeKingValue;		// 王单出算几，2或3
	BYTE		m_whoplay;              // 当前玩家	1--MAXPLAYER
	BYTE		m_whoplayout;			// 上一个玩家
	BYTE		m_banker;				// 庄家
	BYTE		m_nextbanker;			// 下一个庄家

	BYTE		m_whoMakeCards;			//谁做牌			

	//托管数据
	BYTE        m_TuoGuanPlayer[MAX_PLAYER];	  // 谁托管了？
	BYTE		m_TrustCounts[MAX_PLAYER];		  // 托管次数
	int			m_nTrustCounts;					// 允许托管的次数
	//断线数据
	BYTE        m_whoBreak[MAX_PLAYER];			  // 谁断线了？
	int			m_WireBreakCounts[MAX_PLAYER];	  // 断线次数
	int			m_nWireBreakTimes;				// 允许断线重连的次数

	//牌数据
	BYTE		m_cbLeftCardCount;						//剩余数目
	BYTE		m_tempdbp[ALLCARD];				  // 所有牌 做牌所用
	BYTE		m_dbp[ALLCARD];					  // 所有牌
	BYTE		m_dbplay[MAX_PLAYER][MAXCARD];    // 分到的牌

	BYTE        m_allPaiOut[MAX_PLAYER][MAXCARD]; // 出的牌,可能有赖子的
	BYTE        m_allPaiOutNoMagic[MAX_PLAYER][MAXCARD]; // 出的牌,赖子已经变成替换值了
	TFakeKing	m_OutPaifakeking[MAX_PLAYER][8];  //出的牌中的赖子替换值信息
	BYTE        m_lastPaiOut[MAX_PLAYER][MAXCARD];// 上一轮出的牌
	BYTE		m_thePaiCount[MAX_PLAYER];		  // 牌数
	BYTE		m_theCanNotOut[MAX_PLAYER];		  // 是否有人不能出牌，比如只剩一个王了

	//银子，积分数据
	int			m_lastScore[MAX_PLAYER];		  // 上一轮输赢
	int			m_total[MAX_PLAYER];			  // 总输赢
	long		m_playerrich[MAX_PLAYER];		  // 玩家的财富
	int			m_iCurrentFanShu;				//当前番数
	//一些共有的规则
	int			m_nAutoOutTime;					// 自动出牌时间，托管的时候出牌时间
	int			m_nTimeStart;					// 坐下之后，按开始的等待时间
	int			m_nPlayTime;					// 出牌时间
	int			m_nSerPay;						// 茶水费千分比

	time_t	    nowTime; 

	// 设置多少秒后进入指定动作
	void		SetActionStep(ActionStep as,unsigned long nSecond=0);  

	// 立即进入指定动作,
	void		OnActionStep(ActionStep as);

public://自己添加的
	int			m_iBaseScore;				// 底分，通过客户端界面配置的底分
	long		m_nBase;					// 底

	CDaGun		m_dagun;

	int			m_score;					// 每一轮牌的分
	int			m_playerscore[MAX_PLAYER];	// 每个人最后的分数，有可能没出完的也加进去了

	int			m_xiScore[MAX_PLAYER];//喜钱
	long		m_spay;						// 服务费

	BYTE		m_whoPass[MAX_PLAYER];			// 谁放弃了
	BYTE        m_whoAllOutted[MAX_PLAYER];     // 谁出完了，
	BYTE		m_thePlayerState[MAX_PLAYER];			// 用户状态，是否正在游戏中
	bool		m_bUserReady[MAX_PLAYER];			//下一局准备好的用户（点击准备好的用户）

	int			m_whoTotal8Xi[MAX_PLAYER];		// 每个人大局的8喜个数
	int			m_whoTotal7Xi[MAX_PLAYER];		// 每个人大局的7喜个数
	int			m_whoTotalGonglong[MAX_PLAYER];	// 每个人大局的笼炸的笼数(大局)

	int			m_whoHasKingBomb;				// 谁有天炸
	int			m_lastOutType;					// 最后出牌的类型
	BYTE		m_bBaoPei;						//包赔玩家，1-MAX_PLAYER,0表示不用包赔

	int			m_playHardBomb[MAX_PLAYER];		// 打出的硬炸，没有赖子
	int			m_playSoftBomb[MAX_PLAYER];			// 打出的软炸，有赖子
	int         m_playMagicBomb[MAX_PLAYER];			// 赖子炸弹
	int         m_whoHardKill;			// 硬杀
	int         m_whoQuanGuan[MAX_PLAYER];			// 全关
	BYTE		m_byEveryOneOutCnt[MAX_PLAYER];//每个人的出牌次数
	BYTE		m_byEveryOneCurlunOutCnt[MAX_PLAYER];//每个人当前轮的出牌次数

	int			m_MaxScore[MAX_PLAYER];			//最高抓分
	int			m_totalFirstTurn[MAX_PLAYER];	//一游次数
	int			m_totalDuPai[MAX_PLAYER];		//独牌次数

	int			m_iFaOfTao;				//逃跑的惩罚倍数
	int			m_iJiangOfTao;			//逃跑的补偿倍数
	int			m_iAddSpecailBeishu;	//别人有特殊牌奖励时，需要扣除分的倍数
	BYTE		m_byAddSepcialFlag;		//特殊牌型是否加分

	int			m_iRandomTask;						//随机任务,下标
	vector<int>	m_vecAllTaskID;	//所有的任务ID
	map<int,int>	m_mapAllTask;	//任务描述: ID-奖励数
	vector<int>	m_vecFinishedTask[MAX_PLAYER];		//完成的任务
	bool		m_bHaveOutCard;		//是否已经出牌了
	
	st_FriendRule	m_rule;

	vector<CMD_S_EndGame_CB>			m_vecGameEnd;							//记录每一局的结果

	BYTE							m_cbGameEndStatus;					//当前小局游戏的状态
	int								m_CurCompleteCount;				// 当前这一轮完成了几局		

	CString							m_szTimeGameRecord;                 //记录当前日志的日期
	CString							m_szNameGameRecord;                 //记录文件名
public:
	//写入游戏记录
	void		OnWriteGameRecord(unsigned int _seat, CString szGameRecord, const bool bStatus = true);

	//创建游戏记录目录
	void		CreateGameRecordFile(const bool bStatus = false);
	CString		getWriteReplayRecordCString(BYTE recordType);	//回放记录规则配置
	void		ParseRule(const string& strRule);//规则解析
	void		CalculateResultTotal(BYTE cbReason, bool bSendData = true);

	void		GoNextPlayer();
	void		StartPlay(BYTE whoplay);		// 开始玩
	int			AutoOutCard(BYTE theSeat,nsRouAiRou::CMD_OutCard_CB& msgout);	//出牌动作

	void		GameOver(BYTE winner,GameOverType type);

	//修改下面的函数来实现自动托管
	int			AutoTuoGuan(BYTE theSeat);
	//托管出牌
	void		TuoGuanOutCard();

	bool EndTurn();// 结束一轮
	void EndOut();
	void SendPai();//发牌
	void AddSpecailScore(long Score[MAX_PLAYER],int seat,int base);
	void GetFinalWinLoseScore( long long score[MAX_PLAYER] );
	void SendPower(BYTE whoplay,DWORD aPower,DWORD dwWaitTime = 0);	// 发送权限
	void SendPlaySoundMsg(BYTE seat,BYTE type,BYTE flag = 1);						// 发送播放音乐的信息

	void SendTurnScore(int wChairID = INVALID_CHAIR);				// 发送每轮的分数
	void SendPlayerScore(int wChairID = INVALID_CHAIR, int _ichair =INVALID_CHAIR, int _score =0);				// 发送每个人的分数
	void SendPaiCount(int wChairID = INVALID_CHAIR);				// 发送牌数
	void SendFanShu(int wChairID = INVALID_CHAIR);						//发送实时番数
	void sendGameStatus(WORD wChair ,bool isReLink, IServerUserItem * pIServerUserItem);

	BOOL IsGamePlaying();
	BYTE IsBaoPei(BYTE followCard[MAXPAI],BYTE outLen = 0);//判断是否包赔，返回值1-MAX_PLAYRE ,0表示不包赔
	BOOL IsSamePlayerOneCard(BYTE byWho);//是否有玩家只有一张牌,自己除外

	void UpdateOtherFriendDate(CMD_S_EndGame_CB& GameEnd, bool bEnd = false);//替他人开房，VIP开房相关数据处理

	void ParseTaskConfig(const string& strTaskID);	//解析配置的任务
	void SendTaskID (bool bFirst, BYTE nSeat = -1); //发送随机任务
	void IsTaskFinished(const TCardType& re1, int iSeat, int iNumOfKing);  //判断任务是否完成
	void IsTaskFinishedOfLastHand(const TCardType& re1, int iSeat, int iNumOfKing);  //判断最后一手的任务是否完成
	void SendFinishTask (int iSeat, int id, int cnt = 1, bool bToAll = true); //发送完成了的任务
	int GetTaskAward(int iSeat); //获取奖励数
	string GetTaskAwardDetails(int iSeat);	//获取奖励详细
};

}; //end of namespace
#endif//__GAMELOGIC_H__

