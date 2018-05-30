#ifndef CMD_COMMON_GAME_H
#define CMD_COMMON_GAME_H

#include "CMD_Plaza.h"
#include "CMD_Game.h"
#include "biostream.h"

//////////////////////////////////////////////// GameService ////////////////////////////////////////////////
#define SUB_GR_USER_EXPRESSION_PROP_REQ				308							//请求道具列表
#define SUB_GR_USER_EXPRESSION_PROP_REP				309							//道具列表结果
#define SUB_GR_USER_USE_EXPRESSION_PROP_REQ			310							//请求使用道具
#define SUB_GR_USER_USE_EXPRESSION_PROP_REP			311							//使用道具结果
#define SUB_GR_USER_EXPRESSION_PROP_EFFECT_REP		312							//广播使用道具效果

#define SUB_GR_USER_KICKOUT_REQ					313							//请求踢人卡
#define SUB_GR_USER_KICKOUT_REP					314							//踢人卡结果
#define SUB_GR_USER_USE_KICKOUT_REQ				315							//请求使用踢人卡
#define SUB_GR_USER_USE_KICKOUT_REP				316							//使用踢人卡结果
#define SUB_GR_USER_KICKOUT_EFFECT_REP			317							//广播踢人卡效果

#define SUB_GR_USER_TIPOFF_REQ				320							//请求举报
#define SUB_GR_USER_TIPOFF_REP				321							//举报结果

//////////////////////////////////////////////// LogonService ////////////////////////////////////////////////
#define SUB_GP_USER_COIN_COUNT_REQ				372  // 请求金豆数量
#define SUB_GP_USER_COIN_COUNT_REP				373

#define SUB_GP_USER_PROP_REQ					377  // 请求背包数据
#define SUB_GP_USER_PROP_REP					378

#define SUB_GP_USER_MATCH_INFO_REQ					379  // 请求比赛数据
#define SUB_GP_USER_MATCH_INFO_REP					380
#define SUB_GP_USER_PROP_FINISH_REP					381
// 请求道具列表
struct CMD_GR_UserExpressionPropReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_EXPRESSION_PROP_REQ };

	unsigned int					dwUserID;		//玩家 ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserExpressionPropReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserExpressionPropReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_UserExpressionPropReq& pl)
	{
		bis >> pl.dwUserID;

		return bis;
	}
};


struct UserExpProp
{
	unsigned int					dwPropID;		//道具 ID
	unsigned int					dwPropPrice;	//道具价格
	char							szName[32];		//道具名称

	void reset() { memset(this, 0, sizeof(*this)); }
	UserExpProp() { reset(); }
	friend bostream& operator<<(bostream& bos, const UserExpProp& pl)
	{
		bos << pl.dwPropID;
		bos << pl.dwPropPrice;

		bos.write((char*)pl.szName, sizeof(pl.szName));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, UserExpProp& pl)
	{
		bis >> pl.dwPropID;
		bis >> pl.dwPropPrice;

		bis.read((char*)pl.szName, sizeof(pl.szName));
		
		return bis;
	}
};
// 回复道具列表
struct CMD_GR_UserExpressionPropRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_EXPRESSION_PROP_REP };

	short							nCode;		// 返回码 0 表示成功
	unsigned int					totalCount;	// 总数量
	UserExpProp						Product[10];  // 总数据

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserExpressionPropRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserExpressionPropRep& pl)
	{
		bos << pl.nCode;
		bos << pl.totalCount;
		bos.write((char*)pl.Product, sizeof(pl.Product));
		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserExpressionPropRep& pl)
	{
		bis >> pl.nCode;
		bis >> pl.totalCount;
		bis.read((char*)pl.Product, sizeof(pl.Product));
		return bis;
	}
};

// 请求使用道具
struct CMD_GR_UserUseExpressionPropReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_USE_EXPRESSION_PROP_REQ };

	unsigned int					dwUserID;		//玩家 ID
	unsigned int					dwToUserID;		//被使用玩家 ID
	unsigned int					dwPropID;		//道具 ID
	unsigned int					dwPropCount;	//使用的道具数量 ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserUseExpressionPropReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserUseExpressionPropReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwToUserID;
		bos << pl.dwPropID;
		bos << pl.dwPropCount;

		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_UserUseExpressionPropReq& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.dwToUserID;
		bis >> pl.dwPropID;
		bis >> pl.dwPropCount;

		return bis;
	}
};

// 回复使用道具
struct CMD_GR_UserUseExpressionPropRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_USE_EXPRESSION_PROP_REP };

	short							dwSuccess;		//是否使用成功,0 表示成功
	unsigned int					dwRemainCoin;	//当前剩余欢乐豆

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserUseExpressionPropRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserUseExpressionPropRep& pl)
	{
		bos << pl.dwSuccess;
		bos << pl.dwRemainCoin;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserUseExpressionPropRep& pl)
	{
		bis >> pl.dwSuccess;
		bis >> pl.dwRemainCoin;

		return bis;
	}
};

// 广播使用道具效果
struct CMD_GR_UserUseExpressionPropEffectRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_EXPRESSION_PROP_EFFECT_REP };

	unsigned int					dwUserID;		//玩家 ID
	unsigned int					dwToUserID;		//被使用玩家 ID
	unsigned int					dwPropID;		//道具 ID
	unsigned int					dwCount;		//发送次数

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserUseExpressionPropEffectRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserUseExpressionPropEffectRep& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwToUserID;
		bos << pl.dwPropID;

		bos << pl.dwCount;
		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserUseExpressionPropEffectRep& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.dwToUserID;
		bis >> pl.dwPropID;
		bis >> pl.dwCount;

		return bis;
	}
};

// 请求踢人卡
struct CMD_GR_UserKickOutReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_KICKOUT_REQ };

	unsigned int					dwUserID;		//玩家 ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserKickOutReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserKickOutReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_UserKickOutReq& pl)
	{
		bis >> pl.dwUserID;

		return bis;
	}
};

// 回复踢人卡
struct CMD_GR_UserKickOutRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_KICKOUT_REP };

	unsigned char					dwKickOutAuth;	//权限  0-没有， 1-有
	unsigned int					dwCount;		//踢人卡数量
	short							dwMenberOrder;	// vip 等级

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserKickOutRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserKickOutRep& pl)
	{
		bos << pl.dwKickOutAuth;
		bos << pl.dwCount;
		bos << pl.dwMenberOrder;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserKickOutRep& pl)
	{
		bis >> pl.dwKickOutAuth;
		bis >> pl.dwCount;
		bis >> pl.dwMenberOrder;

		return bis;
	}
};

// 使用踢人卡
struct CMD_GR_UserUseKickOutReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_USE_KICKOUT_REQ };

	unsigned int					dwUserID;		//玩家 ID
	unsigned int					dwToUserID;		//被使用玩家 ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserUseKickOutReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserUseKickOutReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwToUserID;

		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_UserUseKickOutReq& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.dwToUserID;

		return bis;
	}
};

// 回复使用踢人卡
struct CMD_GR_UserUseKickOutRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_USE_KICKOUT_REP };

	unsigned char					dwSuccess;	//成功  0-成功
	unsigned int					dwCount; // 踢人卡剩余数量

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserUseKickOutRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserUseKickOutRep& pl)
	{
		bos << pl.dwSuccess;
		bos << pl.dwCount;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserUseKickOutRep& pl)
	{
		bis >> pl.dwSuccess;
		bis >> pl.dwCount;

		return bis;
	}
};

// 踢人广播
struct CMD_GR_UserUseKickOutEffectRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_KICKOUT_EFFECT_REP };

	unsigned int					dwUserID;		//玩家 ID
	unsigned int					dwToUserID;		//被使用玩家 ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserUseKickOutEffectRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserUseKickOutEffectRep& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwToUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserUseKickOutEffectRep& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.dwToUserID;

		return bis;
	}
};
// 请求举报
struct CMD_GR_UserTipOffReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_TIPOFF_REQ };

	unsigned int					dwUserID;		//举报玩家 ID
	unsigned int					dwToUserID;		//被举报玩家 ID
	unsigned int 					dwKindID;
	unsigned char					dwTipOffType;	//举报类型


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserTipOffReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserTipOffReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwToUserID;
		bos << pl.dwKindID;
		bos << pl.dwTipOffType;
		
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_UserTipOffReq& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.dwToUserID;
		bis >> pl.dwKindID;
		bis >> pl.dwTipOffType;
		
		return bis;
	}
};

// 回复举报
struct CMD_GR_UserTipOffRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_TIPOFF_REP };

	unsigned char					dwSuccess;		//VIP等级, 0-成功, 1-失败
	unsigned int					dwUserID;		//举报人ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserTipOffRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserTipOffRep& pl)
	{
		bos << pl.dwSuccess;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserTipOffRep& pl)
	{
		bis >> pl.dwSuccess;
		bis >> pl.dwUserID;

		return bis;
	}
};

// 请求金豆
struct CMD_GP_UserCoinCountReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_COIN_COUNT_REQ };

	unsigned int					dwUserID;		//玩家 ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserCoinCountReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserCoinCountReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GP_UserCoinCountReq& pl)
	{
		bis >> pl.dwUserID;

		return bis;
	}
};

// 回复金豆
struct CMD_GP_UserCoinCountRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_COIN_COUNT_REP };

	unsigned int					dwCount;		//数量

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserCoinCountRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserCoinCountRep& pl)
	{
		bos << pl.dwCount;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserCoinCountRep& pl)
	{
		bis >> pl.dwCount;

		return bis;
	}
};

// 请求背包
struct CMD_GP_UserPropReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PROP_REQ };

	unsigned int					dwUserID;		//玩家 ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserPropReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserPropReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GP_UserPropReq& pl)
	{
		bis >> pl.dwUserID;

		return bis;
	}
};

// 回复背包
struct CMD_GP_UserPropRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PROP_REP };

	unsigned int					dwPropID;		//ID
	unsigned int					dwCount;		//数量
	char							szPropName[64];	// 道具名称
	char							szPropUrl[64];	// 道具名称
	unsigned int					dwType;
	unsigned int					dwComBoId;		

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserPropRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserPropRep& pl)
	{
		bos << pl.dwPropID;
		bos << pl.dwCount;
		bos.write((char*)pl.szPropName, sizeof(pl.szPropName));
		bos.write((char*)pl.szPropUrl, sizeof(pl.szPropUrl));
		bos << pl.dwType;
		bos << pl.dwComBoId;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserPropRep& pl)
	{
		bis >> pl.dwPropID;
		bis >> pl.dwCount;
		bis.read((char*)pl.szPropName, sizeof(pl.szPropName));
		bis.read((char*)pl.szPropUrl, sizeof(pl.szPropUrl));
		bis >> pl.dwType;
		bis >> pl.dwComBoId;

		return bis;
	}
};

// 回复背包
struct CMD_GP_UserPropFinishRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PROP_FINISH_REP };

	unsigned int					dwCount;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserPropFinishRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserPropFinishRep& pl)
	{
		bos << pl.dwCount;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserPropFinishRep& pl)
	{
		bis >> pl.dwCount;

		return bis;
	}
};

// 请求比赛信息
struct CMD_GP_UserMatchInfoReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MATCH_INFO_REQ };

	unsigned int					dwUserID;		//玩家 ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMatchInfoReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMatchInfoReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GP_UserMatchInfoReq& pl)
	{
		bis >> pl.dwUserID;

		return bis;
	}
};

// 回复比赛信息
struct CMD_GP_UserMatchInfoRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MATCH_INFO_REP };

	unsigned int					dwWinTimes;			//胜利盘数
	unsigned int					dwLoseTimes;		//失败盘数
	unsigned int					dwTotalTimes;		//总盘数

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMatchInfoRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMatchInfoRep& pl)
	{
		bos << pl.dwWinTimes;
		bos << pl.dwLoseTimes;
		bos << pl.dwTotalTimes;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMatchInfoRep& pl)
	{
		bis >> pl.dwWinTimes;
		bis >> pl.dwLoseTimes;
		bis >> pl.dwTotalTimes;

		return bis;
	}
};

#endif