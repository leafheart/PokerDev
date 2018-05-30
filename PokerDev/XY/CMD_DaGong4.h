#ifndef CMD_HSDAGUN_HEAD_FILE
#define CMD_HSDAGUN_HEAD_FILE

#include "biostream.h"

namespace nsRouAiRou
{
//////////////////////////////////////////////////////////////////////////
//公共宏定义

#define KIND_ID							935								//游戏 I D
#define GAME_PLAYER						5									//游戏人数
#define GAME_NAME						TEXT("大冶肉挨肉")					//游戏名字
#define GAME_GENRE						(GAME_GENRE_GOLD|GAME_GENRE_MATCH)	//游戏类型

///////////////////////////////////
	//游戏状态
#define GS_MJ_FREE					GS_FREE								//空闲状态
#define GS_MJ_PLAY					(GS_PLAYING+1)						//游戏状态
#define GS_MJ_HAI_DI				(GS_PLAYING+2)						//海底状态
#define GS_MJ_END					(GS_PLAYING+3)						//结束状态

//玩家状态
#define OX_GS_NULL		0	//没人
#define OX_GS_SITDOWN	1	//玩家坐下
#define OX_GS_READY		2	//玩家同意（准备）
#define OX_GS_PLAYING	3	//玩家在游戏中
	
///////////////////////////////////
#define ALLCARD							54
#define MAXCARD							27
#define FIRSTCARD						5
#define MAX_PLAYER						GAME_PLAYER					
//////////////////////////////////////////////////////////////////////////
//服务器命令结构
#define SUB_S_GAME_START				100									//游戏开始
#define SUB_S_TIMER_START				101									//开始倒计时
#define SUB_S_POWER						102									//权限
#define SUB_S_SEND_POKER_OX				103									//发送扑克
#define SUB_S_GAME_STATE_OX				104									//游戏状态(包括各玩家状态，针对旁观者)
#define SUB_S_ENDROAR					105									//结束吼牌
#define SUB_S_RELINK					106									//重连
#define SUB_S_ENDOUT					107									//结束一轮
#define SUB_S_TEAMERPAI					108									//发送队友的牌
#define SUB_S_PLAYERSCORE				109									//发送每个人得的分数
#define SUB_S_SENDCOUNT					110									//发送牌数
#define SUB_S_TURNSCORE					111									//发送局分
#define SUB_S_SENDTURN					112									//发送顺序
#define SUB_S_ENDGAME					113									//游戏结束
#define SUB_S_SHOW						114									//显示叫的牌或者其他信息

#define SUB_CS_OUT						115									//出牌
#define SUB_CS_ROAR						116									//吼牌
#define SUB_S_TUOGUAN					117									//托管
#define SUB_CS_PLAYSOUND				118									//播放声音
#define SUB_CS_TEAMERPAI				119									//队友的牌
#define SUB_CS_GAMERULE					120									//底银
#define SUB_C_RELINK_TIP				121									//断线重连提示，提示其它三个人

#define SUB_CS_RAND_TASK_ID				122									//游戏随机任务
#define SUB_CS_RAND_FINISHED_TASK		123									//游戏随机任务完成

#define SUB_S_GAME_BALANCE_GAME			127									// 总结算

#define SUB_C_GOON_NEXT_GAME			128									//下一局
#define SUB_S_SENDGLONGCOUNT			129									//发送拱笼的笼数
#define SUB_S_FANSHU					130								//显示叫的牌或者其他信息

struct CMD_C_GoOnNextGame   // 一局完成后点击再来一局
{
	enum {XY_ID = SUB_C_GOON_NEXT_GAME};
	unsigned int userId;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_C_GoOnNextGame(){reset();}

	friend bostream& operator<<(bostream& bos,const CMD_C_GoOnNextGame& pl)
	{
		bos << pl.userId;

		return  bos;
	}

	friend bistream& operator>>(bistream& bis,CMD_C_GoOnNextGame& pl)
	{
		pl.reset();
		bis >> pl.userId;

		return bis;
	}
};

//游戏状态
struct CMD_S_StatusFree
{
	unsigned char					cbStatus;							//当前状态
	int								lCellMinScore;						//最小下注
	int								lCellMaxScore;						//最大下注
};


//游戏状态
struct CMD_S_StatusPlay
{
	unsigned char					cbStatus;							//当前状态
	int								lCellMinScore;						//最小下注
	int								lCellMaxScore;						//最大下注
	//标志变量
	//unsigned char								bShowHand[GAME_PLAYER];				//梭哈标志
	//unsigned char								bAddScore;							//加注标志

	//加注信息
	int								lCellScore;							//单元下注
	int								lTurnMaxScore;						//最大下注
	int								lTurnLessScore;						//最小下注
//	int								lCellMaxScore;						//最大下注
	int								lAddLessScore;						//加最小注
	int								lTableScore[GAME_PLAYER];			//下注数目
	int								lTotalScore[GAME_PLAYER];			//累计下注
	int								lCenterScore;						//中心筹码

	//状态信息
	unsigned short					wDUser;								//D玩家
	unsigned short				 	wCurrentUser;						//当前玩家
	unsigned char					cbPlayStatus[GAME_PLAYER];			//游戏状态
	unsigned char					cbBalanceCount;						//平衡次数

	//扑克信息
//	unsigned char					cbCenterCardData[MAX_CENTERCOUNT];	//扑克数目
	unsigned char					cbHandCardData[MAXCARD];			//桌面扑克
};

//发送扑克
struct CMD_S_GameStart_CB
{
	enum {S_ID = SUB_S_GAME_START};
	//theType,之前没有用到，现在增加一个枚举
	enum {GAME_START,GAME_RELINK};

	unsigned char		theIsGameStart;
	unsigned char		theBanker;					// 庄家
	unsigned char		theType;					// 类型(开始游戏或是重连）
	unsigned char		theSeat;					// 谁的牌
	unsigned char		theLeftCardsCount;			// 牌区剩余牌数
	unsigned char		theCount;					// 牌数
	unsigned char		theCards[MAXCARD];			// 牌数据

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_S_GameStart_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_S_GameStart_CB& pl)
	{
		bos << pl.theIsGameStart;
		bos << pl.theBanker;
		bos << pl.theType;
		bos << pl.theSeat;
		bos << pl.theLeftCardsCount;
		bos << pl.theCount;

		bos.write((char*)pl.theCards, sizeof(pl.theCards));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_S_GameStart_CB& pl)
	{	
		pl.reset();
		bis >> pl.theIsGameStart;
		bis >> pl.theBanker;
		bis >> pl.theType;
		bis >> pl.theSeat;
		bis >> pl.theLeftCardsCount;
		bis >> pl.theCount;

		bis.read((char*)pl.theCards, sizeof(pl.theCards));

		return bis;
	}
};

// 权限
struct CMD_S_Power_CB
{
	enum { XY_ID = SUB_S_POWER };

	enum tagPower
	{
		p_Null   = 0x00,
		p_Roar	 = 0x01,
		p_Out	 = 0x02,		// 出牌权限
	};

	unsigned char		theWhoPlay;		// 谁的权限
	unsigned int		theDownTime;	// 定时器时间（单位秒）
	unsigned int		thePower;		// 什么权限

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_S_Power_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_S_Power_CB& pl)
	{
		bos << pl.theWhoPlay;
		bos << pl.theDownTime;
		bos << pl.thePower;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_S_Power_CB& pl)
	{	
		pl.reset();
		bis >> pl.theWhoPlay;
		bis >> pl.theDownTime;
		bis >> pl.thePower;

		return bis;
	}
};

// 结束吼牌
struct CMD_S_EndRoar_CB
{
	enum { XY_ID = SUB_S_ENDROAR };

	unsigned char		theWhoRoar; // 1-4,0表示没有吼牌
	unsigned char       theBanker;	// 庄家
	unsigned char		thePai;		// 叫牌

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_S_EndRoar_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_S_EndRoar_CB& pl)
	{
		bos << pl.theWhoRoar;
		bos << pl.theBanker;
		bos << pl.thePai;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_S_EndRoar_CB& pl)
	{	
		pl.reset();
		bis >> pl.theWhoRoar;
		bis >> pl.theBanker;
		bis >> pl.thePai;

		return bis;
	}
};

// 游戏结束_添加了喜钱
struct CMD_S_EndGame_CB
{
	enum {XY_ID = SUB_S_ENDGAME}; 
	enum{
		GT_NULL,
		GT_NORMAL,		// 正常结束
		GT_ESCAPE,		// 有人逃跑
		GT_DISMISS,		// 解散
	};

	enum tagGongType
	{
		g_Null		= 0x00,		//无效拱型
		g_Normal	= 0x01,		// 正常
		g_BaoPei	= 0x02,		// 包赔
	};

	unsigned char	theEndType;	    // 游戏模式	，吼牌、找朋友
	unsigned char	theWhoKingBomb; // 谁有天炸?
	int				theFan[MAX_PLAYER];			// 多少番
	unsigned char	theGongType;	// 什么类型结束的，比如清拱、干边,赋值请参考enum tagGongType

	unsigned char	byLeftCardsCount[MAX_PLAYER];//余牌数目
	unsigned char	theLeftPai[MAX_PLAYER][MAXCARD];//剩余牌
	unsigned char	theWinLose[MAX_PLAYER];			// 输还是赢？0输，1赢，2平局
	unsigned char	theHardBomb[MAX_PLAYER];		// 每个玩家硬炸弹个数 暂时没有使用
	unsigned char	theSoftBomb[MAX_PLAYER];		// 每个玩家软炸弹个数 暂时没有使用
	unsigned char	theMagicBomb[MAX_PLAYER];		// 每个玩家赖子炸弹个数    暂时没有使用
	unsigned char	theQuanGuan[MAX_PLAYER];		// 是否被全关，1表示被全关了 
	long long		theScore[MAX_PLAYER];			// 得分
	int				theTotalScore[MAX_PLAYER];		// 之前的所有局的总积分，比如现在第3局，这个就是1、2局的积分和

	unsigned char	theToTalHardBomb;		//总硬炸弹个数
	unsigned char	theToTalSoftBomb;		// 总软炸弹个数
	unsigned char	theToTalMagicBomb;		// 总赖子炸弹个数   
	unsigned char	theToTalKingBomb;		// 总的王炸个数 
	unsigned char	theWhoHardKill;					// 谁硬杀  

	unsigned char	cbTheOrder; //第几局
	unsigned char	cbEndStatus;						//表示是哪种结束方式：0正常 1游戏解散 2玩家强退
	unsigned char	cbType;//1为断线重连

	unsigned short	theBank;//庄家
	unsigned short	theWhoEscape;//谁逃跑，椅子号加过1了
	unsigned short	theWhoBaoPei;//谁包赔，椅子号加过1了

	unsigned int	getScore[MAX_PLAYER];//当局抓分
	int				xiScore[MAX_PLAYER];//喜钱
	unsigned char	addSpecialFlag;		//是否特殊牌型加分
	int				iHandScore[MAX_PLAYER];//手分
	
	int				iParaEXT;				//扩展参数(预留)
	int				iszParaEXT[MAX_PLAYER];//扩展参数2(预留)

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_S_EndGame_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_S_EndGame_CB& pl)
	{
		bos << pl.theEndType;
		bos << pl.theWhoKingBomb;
		bos.write((char*)pl.theFan, sizeof(pl.theFan));
		bos << pl.theGongType;

		bos.write((char*)pl.byLeftCardsCount, sizeof(pl.byLeftCardsCount));
		bos.write((char*)pl.theLeftPai, sizeof(pl.theLeftPai));
		bos.write((char*)pl.theWinLose, sizeof(pl.theWinLose));
		bos.write((char*)pl.theHardBomb, sizeof(pl.theHardBomb));
		bos.write((char*)pl.theSoftBomb, sizeof(pl.theSoftBomb));
		bos.write((char*)pl.theMagicBomb, sizeof(pl.theMagicBomb));
		bos.write((char*)pl.theQuanGuan, sizeof(pl.theQuanGuan));
		bos.write((char*)pl.theScore, sizeof(pl.theScore));
		bos.write((char*)pl.theTotalScore, sizeof(pl.theTotalScore));

		bos << pl.theToTalHardBomb;
		bos << pl.theToTalSoftBomb;
		bos << pl.theToTalMagicBomb;
		bos << pl.theToTalKingBomb;
		bos << pl.theWhoHardKill;
		bos << pl.cbTheOrder;
		bos << pl.cbEndStatus;
		bos << pl.cbType;
		bos << pl.theBank;
		bos << pl.theWhoEscape;
		bos << pl.theWhoBaoPei;

		bos.write((char*)pl.getScore, sizeof(pl.getScore));
		bos.write((char*)pl.xiScore, sizeof(pl.xiScore));
		bos << pl.addSpecialFlag;
		bos.write((char*)pl.iHandScore, sizeof(pl.iHandScore));
		bos << pl.iParaEXT;
		bos.write((char*)pl.iszParaEXT, sizeof(pl.iszParaEXT));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_S_EndGame_CB& pl)
	{	
		pl.reset();
		bis >> pl.theEndType;
		bis >> pl.theWhoKingBomb;
		bis.read((char*)pl.theFan, sizeof(pl.theFan));
		bis >> pl.theGongType;

		bis.read((char*)pl.byLeftCardsCount, sizeof(pl.byLeftCardsCount));
		bis.read((char*)pl.theLeftPai, sizeof(pl.theLeftPai));
		bis.read((char*)pl.theWinLose, sizeof(pl.theWinLose));
		bis.read((char*)pl.theHardBomb, sizeof(pl.theHardBomb));
		bis.read((char*)pl.theSoftBomb, sizeof(pl.theSoftBomb));
		bis.read((char*)pl.theMagicBomb, sizeof(pl.theMagicBomb));
		bis.read((char*)pl.theQuanGuan, sizeof(pl.theQuanGuan));
		bis.read((char*)pl.theScore, sizeof(pl.theScore));
		bis.read((char*)pl.theTotalScore, sizeof(pl.theTotalScore));

		bis >> pl.theToTalHardBomb;
		bis >> pl.theToTalSoftBomb;
		bis >> pl.theToTalMagicBomb;
		bis >> pl.theToTalKingBomb;
		bis >> pl.theWhoHardKill;
		bis >> pl.cbTheOrder;
		bis >> pl.cbEndStatus;
		bis >> pl.cbType;
		bis >> pl.theBank;
		bis >> pl.theWhoEscape;
		bis >> pl.theWhoBaoPei;

		bis.read((char*)pl.getScore, sizeof(pl.getScore));
		bis.read((char*)pl.xiScore, sizeof(pl.xiScore));
		bis >> pl.addSpecialFlag;
		bis.read((char*)pl.iHandScore, sizeof(pl.iHandScore));
		bis >> pl.iParaEXT;
		bis.read((char*)pl.iszParaEXT, sizeof(pl.iszParaEXT));

		return bis;
	}
};

// 服务器发给客户端 总结算
struct CMD_S_BALANCE_GAME
{
	enum {XY_ID = SUB_S_GAME_BALANCE_GAME};

	unsigned int							userid;										//userid房主
	int										lGameScore[MAX_PLAYER];						//游戏积分
	
	unsigned short							wChiHuUserCount[MAX_PLAYER];				//胡牌总数(预留字段)

	unsigned short							wMaxGetScore[MAX_PLAYER];					//最高抓分
	unsigned short							wFirstTurnCount[MAX_PLAYER];				//一游次数
	unsigned short							wRoarCount[MAX_PLAYER];						//独牌次数
	unsigned short							w7XiCount[MAX_PLAYER];						//7喜次数
	unsigned short							w8XiCount[MAX_PLAYER];						//8喜次数
	unsigned short							wLongZhaCount[MAX_PLAYER];					//笼炸次数

	unsigned short							wZMHuUserCount[MAX_PLAYER];					//自摸(预留字段)
	unsigned short							wJPHuUserCount[MAX_PLAYER];					//接炮(预留字段)
	unsigned short							wMGangUserCount[MAX_PLAYER];				//明杠(预留字段)
	unsigned short							wAGangUserCount[MAX_PLAYER];				//暗杠(预留字段)

	unsigned char							curTotalCount;								//当前总局数 
	unsigned char							cbTheCost;//扣了多少局的房卡

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_S_BALANCE_GAME() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_S_BALANCE_GAME& pl)
	{
		bos << pl.userid;
		bos.write((char*)pl.lGameScore, sizeof(pl.lGameScore));
		bos.write((char*)pl.wChiHuUserCount, sizeof(pl.wChiHuUserCount));
		bos.write((char*)pl.wMaxGetScore, sizeof(pl.wMaxGetScore));
		bos.write((char*)pl.wFirstTurnCount, sizeof(pl.wFirstTurnCount));
		bos.write((char*)pl.wRoarCount, sizeof(pl.wRoarCount));
		bos.write((char*)pl.w7XiCount, sizeof(pl.w7XiCount));
		bos.write((char*)pl.w8XiCount, sizeof(pl.w8XiCount));
		bos.write((char*)pl.wLongZhaCount, sizeof(pl.wLongZhaCount));
		bos.write((char*)pl.wZMHuUserCount, sizeof(pl.wZMHuUserCount));
		bos.write((char*)pl.wJPHuUserCount, sizeof(pl.wJPHuUserCount));
		bos.write((char*)pl.wMGangUserCount, sizeof(pl.wMGangUserCount));
		bos.write((char*)pl.wAGangUserCount, sizeof(pl.wAGangUserCount));
		bos << pl.curTotalCount;
		bos << pl.cbTheCost;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_S_BALANCE_GAME& pl)
	{
		pl.reset();
		bis >> pl.userid;
		bis.read((char*)pl.lGameScore, sizeof(pl.lGameScore));
		bis.read((char*)pl.wChiHuUserCount, sizeof(pl.wChiHuUserCount));
		bis.read((char*)pl.wMaxGetScore, sizeof(pl.wMaxGetScore));
		bis.read((char*)pl.wFirstTurnCount, sizeof(pl.wFirstTurnCount));
		bis.read((char*)pl.wRoarCount, sizeof(pl.wRoarCount));
		bis.read((char*)pl.w7XiCount, sizeof(pl.w7XiCount));
		bis.read((char*)pl.w8XiCount, sizeof(pl.w8XiCount));
		bis.read((char*)pl.wLongZhaCount, sizeof(pl.wLongZhaCount));
		bis.read((char*)pl.wZMHuUserCount, sizeof(pl.wZMHuUserCount));
		bis.read((char*)pl.wJPHuUserCount, sizeof(pl.wJPHuUserCount));
		bis.read((char*)pl.wMGangUserCount, sizeof(pl.wMGangUserCount));
		bis.read((char*)pl.wAGangUserCount, sizeof(pl.wAGangUserCount));
		bis >> pl.curTotalCount;
		bis >> pl.cbTheCost;

		return bis;
	}
};


// 权限
struct CMD_S_Show_CB
{
	enum { XY_ID = SUB_S_SHOW };

	enum{
		F_NULL,
		F_JIAOPAI,				// 叫牌
		F_MINGJI,				// 明鸡
	};
	unsigned char		theFlag;
	unsigned char		thePai;
	unsigned char		theSeat;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_S_Show_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_S_Show_CB& pl)
	{
		bos << pl.theFlag;
		bos << pl.thePai;
		bos << pl.theSeat;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_S_Show_CB& pl)
	{	
		pl.reset();
		bis >> pl.theFlag;
		bis >> pl.thePai;
		bis >> pl.theSeat;

		return bis;
	}
};

// 结束一轮
struct CMD_S_EndOut_CB
{
	enum {XY_ID = SUB_S_ENDOUT}; 

	unsigned char theWhoPlay;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_S_EndOut_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_S_EndOut_CB& pl)
	{
		bos << pl.theWhoPlay;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_S_EndOut_CB& pl)
	{	
		pl.reset();
		bis >> pl.theWhoPlay;

		return bis;
	}
};

//////////////////////////////////////////////////////////////////////////
//客户端命令结构


// 吼牌
struct CMD_Roar_CB
{
	enum { XY_ID = SUB_CS_ROAR};
	unsigned char		theSeat;
	unsigned char		theFlag;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_Roar_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_Roar_CB& pl)
	{
		bos << pl.theSeat;
		bos << pl.theFlag;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_Roar_CB& pl)
	{	
		bis >> pl.theSeat;
		bis >> pl.theFlag;

		return bis;
	}
};

typedef struct TFakeKing_CB
{
	unsigned char        index;		//原来的值
	unsigned char		fakeindex;	//替代值	

	void reset() { memset(this, 0, sizeof(*this)); }
	TFakeKing_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const TFakeKing_CB& pl)
	{
		bos << pl.index;
		bos << pl.fakeindex;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,TFakeKing_CB& pl)
	{	
		bis >> pl.index;
		bis >> pl.fakeindex;

		return bis;
	}
}TFakeKing;

//出牌
struct CMD_OutCard_CB
{
	enum {S_ID = SUB_CS_OUT};

	unsigned char		theSeat;					// 谁出的牌
	unsigned char		theCount;					// 牌数
	unsigned short		theNoSound;					// 是否禁止本身的声音？
	// add 2010-01-06,这里之所以要加个牌型，是因为跟的牌里面，很可能是多重牌型，单纯判断，是不可靠的
	// 比如A走了334455,B走了44王王王5，C无法判断B走的是444555呢，还是445566，默认是把他识别为444555,会出现bug
	unsigned char		thePaiType; 
	unsigned char		thePai[MAXCARD];		// 扑克
	TFakeKing			fakeking[8];

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_OutCard_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_OutCard_CB& pl)
	{
		bos << pl.theSeat;
		bos << pl.theCount;
		bos << pl.theNoSound;
		bos << pl.thePaiType;

		bos.write((char*)pl.thePai, sizeof(pl.thePai));
		bos.write((char*)pl.fakeking, sizeof(pl.fakeking));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_OutCard_CB& pl)
	{	
		bis >> pl.theSeat;
		bis >> pl.theCount;
		bis >> pl.theNoSound;
		bis >> pl.thePaiType;

		bis.read((char*)pl.thePai, sizeof(pl.thePai));
		bis.read((char*)pl.fakeking, sizeof(pl.fakeking));

		return bis;
	}
};

// 托管
struct CMD_S_Tuoguan_CB
{
	enum { XY_ID = SUB_S_TUOGUAN };

	enum
	{
		T_NULL		= 0x00,
		T_TUOGUAN	= 0x01,
		T_CANCEL	= 0x02,
	};

	unsigned char theSeat;
	unsigned char theFlag;		// 托管标志
	unsigned int theTime;	// 定时器时间（单位秒）

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_S_Tuoguan_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_S_Tuoguan_CB& pl)
	{
		bos << pl.theSeat;
		bos << pl.theFlag;
		bos << pl.theTime;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_S_Tuoguan_CB& pl)
	{	
		pl.reset();
		bis >> pl.theSeat;
		bis >> pl.theFlag;
		bis >> pl.theTime;

		return bis;
	}
};

// 播放声音
struct CMD_CS_msgPlaySound_CB
{
	enum{XY_ID = SUB_CS_PLAYSOUND};
	enum
	{
		TY_KING_BEEP = 1,		//拆开天炸的提示
		TY_8Xi_BEEP,
		TY_7Xi_BEEP,
		TY_JieFeng,				//接风
		TY_ChaDi,				//插底
	};
	unsigned char thePaiType;
	unsigned char theSeat[MAX_PLAYER];
	unsigned char theFlag;		//为1时播放声音，0时关闭
	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_msgPlaySound_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_CS_msgPlaySound_CB& pl)
	{
		bos << pl.thePaiType;
		bos.write((char*)pl.theSeat, sizeof(pl.theSeat));
		bos << pl.theFlag;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_CS_msgPlaySound_CB& pl)
	{	
		pl.reset();
		bis >> pl.thePaiType;
		bis.read((char*)pl.theSeat, sizeof(pl.theSeat));
		bis >> pl.theFlag;

		return bis;
	}
};

//实时番数
struct CMD_CS_FanShu_CB
{
	enum { XY_ID = SUB_S_FANSHU };

	int theCurFanShu; //实时番数

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_FanShu_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_CS_FanShu_CB& pl)
	{
		bos << pl.theCurFanShu;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_CS_FanShu_CB& pl)
	{	
		pl.reset();
		bis >> pl.theCurFanShu;
		return bis;
	}
};

//本轮分
struct CMD_CS_TurnScore_CB
{
	enum { XY_ID = SUB_S_TURNSCORE };

	int theScore; //抓分

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_TurnScore_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_CS_TurnScore_CB& pl)
	{
		bos << pl.theScore;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_CS_TurnScore_CB& pl)
	{	
		pl.reset();
		bis >> pl.theScore;
		return bis;
	}
};

struct CMD_CS_PLAYSCORE_CB
{
	enum { XY_ID = SUB_S_PLAYERSCORE };

	int getScore; //抓分
	unsigned int iChair;//玩家
	int theScore[MAX_PLAYER]; //抓分

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_PLAYSCORE_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_CS_PLAYSCORE_CB& pl)
	{
		bos << pl.getScore;
		bos << pl.iChair;
	
		bos.write((char*)pl.theScore, sizeof(pl.theScore));
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_CS_PLAYSCORE_CB& pl)
	{	
		pl.reset();	
		bis >> pl.getScore;
		bis >> pl.iChair;
		
		bis.read((char*)pl.theScore, sizeof(pl.theScore));
		return bis;
	}
};

//发送扑克
struct CMD_S_SendPoker_OX
{
	enum {XY_ID = SUB_S_SEND_POKER_OX};

	unsigned char		thelunshu;						// 发牌次数
	unsigned char		theSeat;						// 谁的牌, 暂时没有使用，1--MAX_PLAYER
	unsigned char		theType;						// 牌型
	unsigned char		theLeftCardsCount;				// 牌区剩余牌数目
	unsigned char		theXianshou;					// 先手,即从他开始发牌,1--MAX_PLAYER 
	bool				theIsKanpai;					// 是否是看牌阶段发牌，1表示是看牌，0表示普通发牌
	unsigned char		theCardsCount[MAX_PLAYER];					// 发牌数目
	unsigned char		theCards[MAX_PLAYER][FIRSTCARD];			// 牌数据，每次最多发多少张牌，目前没人每次只发一张牌

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_S_SendPoker_OX() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_S_SendPoker_OX& pl)
	{
		bos << pl.thelunshu;
		bos << pl.theSeat;
		bos << pl.theType;
		bos << pl.theLeftCardsCount;
		bos << pl.theXianshou;
		bos << pl.theIsKanpai;

		bos.write((char*)pl.theCardsCount, sizeof(pl.theCardsCount));
		bos.write((char*)pl.theCards, sizeof(pl.theCards));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_S_SendPoker_OX& pl)
	{
		pl.reset();
		bis >> pl.thelunshu;
		bis >> pl.theSeat;
		bis >> pl.theType;
		bis >> pl.theLeftCardsCount;
		bis >> pl.theXianshou;
		bis >> pl.theIsKanpai;

		bis.read((char*)pl.theCardsCount, sizeof(pl.theCardsCount));
		bis.read((char*)pl.theCards, sizeof(pl.theCards));

		return bis;
	}
};

struct CMD_CS_SendCount_CB
{
	enum { XY_ID = SUB_S_SENDCOUNT };

	int thePaiCount[MAX_PLAYER];

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_SendCount_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_CS_SendCount_CB& pl)
	{
		bos.write((char*)pl.thePaiCount, sizeof(pl.thePaiCount));
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_CS_SendCount_CB& pl)
	{	
		pl.reset();
		bis.read((char*)pl.thePaiCount, sizeof(pl.thePaiCount));
		return bis;
	}
};
struct CMD_CS_SendGLongCount_CB
{
	enum { XY_ID = SUB_S_SENDGLONGCOUNT };
	
	unsigned short wChair;
	int   theGLongCount;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_SendGLongCount_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_CS_SendGLongCount_CB& pl)
	{
		bos << pl.wChair;
		bos << pl.theGLongCount;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_CS_SendGLongCount_CB& pl)
	{	
		pl.reset();
		bis >> pl.wChair;
		bis >> pl.theGLongCount;
		return bis;
	}
};

struct CMD_CS_SendTurn_CB
{
	enum { XY_ID = SUB_S_SENDTURN };

	bool isFirst;//如果是重连，会再发一次这东西，就置为false
    unsigned char	theTurn[MAX_PLAYER];

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_SendTurn_CB(){ reset();isFirst = true; }
	friend bostream& operator<<(bostream& bos,const CMD_CS_SendTurn_CB& pl)
	{
		bos<<pl.isFirst;
		bos.write((char*)pl.theTurn, sizeof(pl.theTurn));
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_CS_SendTurn_CB& pl)
	{	
		pl.reset();
		bis>>pl.isFirst;
		bis.read((char*)pl.theTurn, sizeof(pl.theTurn));
		return bis;
	}
};

struct CMD_CS_TeamerPai
{
	enum { XY_ID = SUB_CS_TEAMERPAI };
	unsigned char theSeat;
	unsigned char theCount;
	unsigned char thePai[MAXCARD];

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_TeamerPai() { reset(); }

	friend bostream& operator<<(bostream& bos,const CMD_CS_TeamerPai& pl)
	{

		bos << pl.theSeat;
		bos << pl.theCount;

		bos.write((char*)pl.thePai, sizeof(pl.thePai));
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_CS_TeamerPai& pl)
	{	
		pl.reset();

		bis >> pl.theSeat;
		bis >> pl.theCount;

		bis.read((char*)pl.thePai, sizeof(pl.thePai));
		return bis;
	}
};

struct CMD_CS_GameRule
{
	
    enum { XY_ID = SUB_CS_GAMERULE };
	int bPlaySR;			// 是否是财富游戏
	int theGiveGift;		// 是否可以领奖
	int theMakePai;		// 是否做牌
	unsigned char nTrustCounts;		// 允许托管的次数	
	unsigned char theSpecial;		// 0，普通，1方言
	int theBase;			// 底
	int theSeverCharge;			// 茶水
	int	theMinGameScore;	// 进入房间最小的欢乐豆数
	int	theMaxGameScore;	// 进入房间最大的欢乐豆数
	int iFaOfTao ;			//逃跑处罚倍数	
	int iJiangOfTao ;		//别人逃跑奖励给你的倍数			
	int isShowChardCount; // 是否显示手牌数量
	int iFakeKingValue; // 王单出算几，2或3
	int iMaxKingNum;	// 王数量，4或8

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_GameRule() { reset(); }

	friend bostream& operator<<(bostream& bos,const CMD_CS_GameRule& pl)
	{
		bos << pl.bPlaySR;
		bos << pl.theGiveGift;
		bos << pl.theMakePai;
		bos << pl.nTrustCounts;
		bos << pl.theSpecial;
		bos << pl.theBase;
		bos << pl.theSeverCharge;
		bos << pl.theMinGameScore;
		bos << pl.theMaxGameScore;
		bos << pl.iFaOfTao;
		bos << pl.iJiangOfTao;
		bos << pl.isShowChardCount;
		bos << pl.iFakeKingValue;
		bos << pl.iMaxKingNum;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_CS_GameRule& pl)
	{	
		pl.reset();
		bis >> pl.bPlaySR;
		bis >> pl.theGiveGift;
		bis >> pl.theMakePai;
		bis >> pl.nTrustCounts;
		bis >> pl.theSpecial;
		bis >> pl.theBase;
		bis >> pl.theSeverCharge;
		bis >> pl.theMinGameScore;
		bis >> pl.theMaxGameScore;
		bis >> pl.iFaOfTao;
		bis >> pl.iJiangOfTao;
		bis >> pl.isShowChardCount;
		bis >> pl.iFakeKingValue;
		bis >> pl.iMaxKingNum;
		return bis;
	}
};


struct CMD_S_GAME_STATE_OX
{
	enum {XY_ID = SUB_S_GAME_STATE_OX};
	enum
	{
		GSTATE_NULL,
		GSTATE_SITDOWN,	//坐下
		GSTATE_READY,	//准备
		GSTATE_PLAYING	//游戏中
	};

	unsigned char theGameState;
	unsigned char theBanker; // 庄家
	unsigned char theBeiShu[MAX_PLAYER]; //玩家倍数
	unsigned char thePlayerState[MAX_PLAYER];//玩家状态
	unsigned char theWhoBreak[MAX_PLAYER];// 谁断线了
	unsigned char theTuoGuan[MAX_PLAYER]; // 谁托管了？
	unsigned char		thePass[MAX_PLAYER];	// 谁放弃了？
	unsigned char       theLastOutCard[MAX_PLAYER][MAXCARD];//上一次出的牌
	unsigned char		theOutCard[MAX_PLAYER][MAXCARD];// 出的牌
	TFakeKing			theOutPaifakeking[MAX_PLAYER][8];  //出的牌中的赖子替换值信息
	unsigned char		thePaiCount[MAX_PLAYER];		  // 牌数
	unsigned char       theWhoPlayOut;			// 上一次谁出的牌
	unsigned char		theLeftTime;			// 剩余时间
	unsigned char		theWhoPlay;				// 当前人
	int					theLastPaiType;			// 最后出牌的类型
	unsigned char		theLeftCardCount;		// 牌区剩余牌数
	int					theFanShu;				// 当前倍数

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_S_GAME_STATE_OX(){reset();}

	friend bostream& operator<<(bostream& bos,const CMD_S_GAME_STATE_OX& pl)
	{
		bos << pl.theGameState;
		bos << pl.theBanker;
		bos.write((char*)pl.theBeiShu, sizeof(pl.theBeiShu));
		bos.write((char*)pl.thePlayerState, sizeof(pl.thePlayerState));
		bos.write((char*)pl.theWhoBreak, sizeof(pl.theWhoBreak));
		bos.write((char*)pl.theTuoGuan, sizeof(pl.theTuoGuan));
		bos.write((char*)pl.thePass, sizeof(pl.thePass));
		bos.write((char*)pl.theLastOutCard, sizeof(pl.theLastOutCard));
		bos.write((char*)pl.theOutCard, sizeof(pl.theOutCard));
		bos.write((char*)pl.theOutPaifakeking, sizeof(pl.theOutPaifakeking));
		bos.write((char*)pl.thePaiCount, sizeof(pl.thePaiCount));
		bos << pl.theWhoPlayOut;
		bos << pl.theLeftTime;
		bos << pl.theWhoPlay;
		bos << pl.theLastPaiType;
		bos << pl.theLeftCardCount;
		bos << pl.theFanShu;

		return  bos;
	}

	friend bistream& operator>>(bistream& bis,CMD_S_GAME_STATE_OX& pl)
	{
		pl.reset();
		bis >> pl.theGameState;
		bis >> pl.theBanker;
		bis.read((char*)pl.theBeiShu, sizeof(pl.theBeiShu));
		bis.read((char*)pl.thePlayerState, sizeof(pl.thePlayerState));
		bis.read((char*)pl.theWhoBreak, sizeof(pl.theWhoBreak));
		bis.read((char*)pl.theTuoGuan, sizeof(pl.theTuoGuan));
		bis.read((char*)pl.thePass, sizeof(pl.thePass));
		bis.read((char*)pl.theLastOutCard, sizeof(pl.theLastOutCard));
		bis.read((char*)pl.theOutCard, sizeof(pl.theOutCard));
		bis.read((char*)pl.theOutPaifakeking, sizeof(pl.theOutPaifakeking));
		bis.read((char*)pl.thePaiCount, sizeof(pl.thePaiCount));
		bis >> pl.theWhoPlayOut;
		bis >> pl.theLeftTime;
		bis >> pl.theWhoPlay;
		bis >> pl.theLastPaiType;
		bis >> pl.theLeftCardCount;
		bis >> pl.theFanShu;
		return bis;
	}

};

struct CMD_CS_msgReLink
{
	enum {XY_ID = SUB_S_RELINK};
	unsigned short      theChair;                 //玩家的座位号，用于初始化座位号，不然转化为location会出问题
	unsigned char	    theGameState;			// 游戏状态(GameState)
	unsigned char		theBanker;				// 庄家
	unsigned char		theLeftTime;			// 剩余时间
	unsigned char		theWhoPlay;				// 当前人
	unsigned char       theWhoPlayOut;			// 上一次谁出的牌
	unsigned char		theTGTime;			    // 已经托管的次数

	unsigned char		thePass[MAX_PLAYER];	// 谁放弃了？
	unsigned char        theWhoBreak[MAX_PLAYER];// 谁断线了
	unsigned char        theTuoGuan[MAX_PLAYER]; // 谁托管了？
	unsigned char        theLastOutCard[MAX_PLAYER][MAXCARD];//上一次出的牌
	unsigned char		theOutCard[MAX_PLAYER][MAXCARD];// 出的牌
	TFakeKing			theOutPaifakeking[MAX_PLAYER][8];  //出的牌中的赖子替换值信息
	unsigned char		theCards[MAXCARD];			// 自己的牌数据
	unsigned char		thePaiCount[MAX_PLAYER];		  // 牌数
	bool				theWhoReady[MAX_PLAYER];// 谁已经完成了叫牌过程
	int					theLast[MAX_PLAYER];	// 上一局
	int					theTotal[MAX_PLAYER];	// 总输赢
	int					theTurnScore;			// 本轮分
	unsigned char	    Score[MAX_PLAYER];      //每个玩家的得分
	int					theLastPaiType;			// 最后出牌的类型
	unsigned char		theLeftCardCount;		// 牌区剩余牌数
	int					theFanShu;				// 当前倍数
	unsigned char		cbTheOrder;				//当前局数
	
	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_msgReLink(){reset();}

	friend bostream& operator<<(bostream& bos,const CMD_CS_msgReLink& pl)
	{
		bos << pl.theChair;
		bos << pl.theGameState;
		bos << pl.theBanker;
		bos << pl.theLeftTime;
		bos << pl.theWhoPlay;
		bos << pl.theWhoPlayOut;
		bos << pl.theTGTime;

		bos.write((char*)pl.thePass, sizeof(pl.thePass));
		bos.write((char*)pl.theWhoBreak, sizeof(pl.theWhoBreak));
		bos.write((char*)pl.theTuoGuan, sizeof(pl.theTuoGuan));
		bos.write((char*)pl.theLastOutCard, sizeof(pl.theLastOutCard));
		bos.write((char*)pl.theOutCard, sizeof(pl.theOutCard));
		bos.write((char*)pl.theOutPaifakeking, sizeof(pl.theOutPaifakeking));
		bos.write((char*)pl.theCards, sizeof(pl.theCards));
		bos.write((char*)pl.thePaiCount, sizeof(pl.thePaiCount));
		bos.write((char*)pl.theWhoReady, sizeof(pl.theWhoReady));
		bos.write((char*)pl.theLast, sizeof(pl.theLast));
		bos.write((char*)pl.theTotal, sizeof(pl.theTotal));
		bos << pl.theTurnScore;
		bos.write((char*)pl.Score, sizeof(pl.Score));
		bos << pl.theLastPaiType;
		bos << pl.theLeftCardCount;
		bos << pl.theFanShu;
		bos << pl.cbTheOrder;
		
		return bos;
	}

	friend bistream& operator>>(bistream& bis,CMD_CS_msgReLink& pl)
	{	
		pl.reset();
		bis >> pl.theChair;
		bis >> pl.theGameState;
		bis >> pl.theBanker;
		bis >> pl.theLeftTime;
		bis >> pl.theWhoPlay;
		bis >> pl.theWhoPlayOut;
		bis >> pl.theTGTime;
	
		bis.read((char*)pl.thePass, sizeof(pl.thePass));
		bis.read((char*)pl.theWhoBreak, sizeof(pl.theWhoBreak));
		bis.read((char*)pl.theTuoGuan, sizeof(pl.theTuoGuan));
		bis.read((char*)pl.theLastOutCard, sizeof(pl.theLastOutCard));
		bis.read((char*)pl.theOutCard, sizeof(pl.theOutCard));
		bis.read((char*)pl.theOutPaifakeking, sizeof(pl.theOutPaifakeking));
		bis.read((char*)pl.theCards, sizeof(pl.theCards));
		bis.read((char*)pl.thePaiCount, sizeof(pl.thePaiCount));
		bis.read((char*)pl.theWhoReady, sizeof(pl.theWhoReady));
		bis.read((char*)pl.theLast, sizeof(pl.theLast));
		bis.read((char*)pl.theTotal, sizeof(pl.theTotal));
		bis >> pl.theTurnScore;
		bis.read((char*)pl.Score, sizeof(pl.Score));
		bis >> pl.theLastPaiType;
		bis >> pl.theLeftCardCount;
		bis >> pl.theFanShu;
		bis >> pl.cbTheOrder;

		return bis;

	}

};

//提示其他玩家，我又回来了！
struct CMD_CS_msgReLinkTip
{
	enum {XY_ID = SUB_C_RELINK_TIP};
	unsigned char	theSeat;
	unsigned char	theFlag;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_msgReLinkTip(){reset();}

	friend bostream& operator<<(bostream& bos,const CMD_CS_msgReLinkTip& pl)
	{
		bos << pl.theSeat;
		bos << pl.theFlag;
		return  bos;
	}

	friend bistream& operator>>(bistream& bis,CMD_CS_msgReLinkTip& pl)
	{	
		pl.reset();
		bis >> pl.theSeat;
		bis >> pl.theFlag;

		return bis;
	}

};

//本局选中的游戏任务
struct CMD_CS_msgTaskID
{
	enum { XY_ID = SUB_CS_RAND_TASK_ID};
	unsigned char		theID;
	int					theAward;	//奖励数
	
	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_msgTaskID(){reset();}

	friend bostream& operator<<(bostream& bos,const CMD_CS_msgTaskID& pl)
	{
		bos << pl.theID;
		bos << pl.theAward;
		return  bos;
	}

	friend bistream& operator>>(bistream& bis,CMD_CS_msgTaskID& pl)
	{	
		pl.reset();
		bis >> pl.theID;
		bis >> pl.theAward;

		return bis;
	}
};

//游戏任务完成状态
struct CMD_CS_msgFinishedTaskID
{
	enum { XY_ID = SUB_CS_RAND_FINISHED_TASK};
	unsigned char	theSeat;		//谁
	unsigned char	theID;			//完成了哪个任务
	unsigned char	theFlag;		//标志位：目前用1来标志是重连后发送的
	int				theCnt;			//完成了几次
	int				theTotal;		//奖励总数

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_CS_msgFinishedTaskID(){reset();}

	friend bostream& operator<<(bostream& bos,const CMD_CS_msgFinishedTaskID& pl)
	{
		bos << pl.theSeat;
		bos << pl.theID;
		bos << pl.theFlag;
		bos << pl.theCnt;
		bos << pl.theTotal;
		return  bos;
	}

	friend bistream& operator>>(bistream& bis,CMD_CS_msgFinishedTaskID& pl)
	{	
		pl.reset();
		bis >> pl.theSeat;
		bis >> pl.theID;
		bis >> pl.theFlag;
		bis >> pl.theCnt;
		bis >> pl.theTotal;

		return bis;
	}
};

}; //end of namespace

#endif

