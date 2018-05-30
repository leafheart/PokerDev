#ifndef TABLE_FRAME_SINK_HEAD_FILE
#define TABLE_FRAME_SINK_HEAD_FILE

#pragma once


#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

//#include "GameLogic.h"
#include "../XY/CMD_DaGong4.h"
#include "GameServiceExport.h"

#include <string>
#include <vector>
using namespace std;
//////////////////////////////////////////////////////////////////////////

#define GAME_TIMER				1

typedef enum _Replay_Operation
{
	E_HuoPai,			//吼牌
	E_EndHouPai,		//结束吼牌
	E_OutCard,			//出牌
	E_SendCard,			//发牌
	E_EndGame,			//结束游戏
	E_GameJieSan,		//游戏解散
	E_TurnOver,			//本轮结算
}Replay_Operation;

typedef enum _Replay_Ext_Type
{
	E_Ext_HouPai,		//吼牌
	E_Ext_MingJi,		//明鸡
	E_Ext_TurnScore,	//本轮分
	E_Ext_GetScore,		//抓分
	E_Ext_GLongShu,		//笼数
	E_Ext_PaiXing,		//牌型
}Replay_Ext_Type;

struct Replay_Order_Ext
{
	Replay_Ext_Type		ext_type;		//操作类型
	int					ext_value;		//操作值
};

struct Replay_Order
{
	unsigned short				chair_id;
	Replay_Operation			operation;
	vector<BYTE>				value;
	vector<Replay_Order_Ext>	vecOrderExt;	//该操作的额外数据

	void reset() 
	{ 
		memset(this, 0, sizeof(*this)); 
	}
	Replay_Order() { reset(); }
};

struct Replay_Record
{
	vector<BYTE>					vecHandCard[MAX_PLAYER];					//用户最初手上的牌
	vector<Replay_Order>			vecOrder;									//用户操作
	BYTE							cbBigHuKind;								//标记大胡类型
	WORD							wProvideUser;								//点炮用户
	BYTE							cbPiziCard;
	int								iScore[MAX_PLAYER];							//游戏积分

	void reset()
	{
		memset((void*)iScore, 0, sizeof(iScore));
		for (int i = 0; i < MAX_PLAYER; i++)
		{
			vecHandCard[i].clear();
		}
		vecOrder.clear();
		cbBigHuKind = 2;	//0用来表示将一色了
		wProvideUser = 9;
		cbPiziCard = 0;
	}
	Replay_Record() { reset(); }
};

//游戏桌子类
class CTableFrameSink : public ITableFrameSink, public ITableUserAction
{

	//玩家变量
protected:
	WORD							m_wDUser;								//D玩家
	WORD							m_wCurrentUser;							//当前玩家
	Replay_Record					m_sReplayRecord;						//回放记录

	//玩家状态
protected:
	BYTE							m_cbPlayStatus[GAME_PLAYER];			//游戏状态

	//组件变量
protected:
//	CGameLogic						m_GameLogic;							//游戏逻辑
	ITableFrame						* m_pITableFrame;						//框架接口
	const tagGameServiceOption		* m_pGameServiceOption;					//配置参数

	//属性变量
protected:
	static const WORD				m_wPlayerCount;							//游戏人数
	static const enStartMode		m_GameStartMode;						//开始模式

protected:
	//创建游戏记录目录
	virtual void CreateGameRecordFile(const bool bStatus = false){};

	virtual void OnStartGame() {};
	virtual void OnGameAction(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize,IServerUserItem * pIServerUserItem) {};

	bool SendTableData(WORD wChairID, WORD wSubCmdID, void * pData, WORD wDataSize);
	bool SendTableDataToAll(WORD wSubCmdID, void * pData, WORD wDataSize);
	void SendTableDataToOther(WORD wChairID, WORD wSubCmdID, void * pData, WORD wDataSize);

	IServerUserItem * GetServerUserItem(WORD wChairID);

	void stovs( const string& s, const string& sp, vector<string>& sa );
	//函数定义
public:
	//构造函数
	CTableFrameSink();
	//析构函数
	virtual ~CTableFrameSink();

	//基础接口
	//WORD GetPlayerCount() { return m_pITableFrame->GetGameServiceOption()->wPlayerCount; }
	WORD GetPlayerCount() { return MAX_PLAYER; }
public:
	//释放对象
	virtual VOID __cdecl Release() { }
	//是否有效
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CTableFrameSink))?true:false; }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//管理接口
public:
	//初始化
	virtual bool __cdecl InitTableFrameSink(IUnknownEx * pIUnknownEx);
	//复位桌子
	virtual void __cdecl RepositTableFrameSink();

	//信息接口
public:
	//开始模式
	virtual enStartMode __cdecl GetGameStartMode();
	//游戏状态
	virtual bool __cdecl IsUserPlaying(WORD wChairID);

	//动作事件 
public:
	//用户断线
	virtual bool __cdecl OnActionUserOffLine(WORD wChairID, IServerUserItem * pIServerUserItem) { return true; }
	//用户重入
	virtual bool __cdecl OnActionUserReConnect(WORD wChairID, IServerUserItem * pIServerUserItem) { return true; }
	//用户坐下
	virtual bool __cdecl OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//用户起来
	virtual bool __cdecl OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//用户同意
	virtual bool __cdecl OnActionUserReady(WORD wChairID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize) { return true; }

	//游戏事件
public:
	//游戏开始
	virtual bool __cdecl OnEventGameStart();
	//游戏结束
	virtual bool __cdecl OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);
	//发送场景
	virtual bool __cdecl SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret);

	//消息事件
protected:
	//放弃事件
	bool OnUserGiveUp(WORD wChairID);
	//加注事件
	bool OnUserAddScore(WORD wChairID, LONG lScore, bool bGiveUp);

	//事件接口
public:
	//定时器事件
	virtual bool __cdecl OnTimerMessage(WORD wTimerID, WPARAM wBindParam);
	//游戏消息处理
	virtual bool __cdecl OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
	//框架消息处理
	virtual bool __cdecl OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
};

//////////////////////////////////////////////////////////////////////////

#endif