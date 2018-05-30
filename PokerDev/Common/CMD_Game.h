#ifndef CMD_GAME_HEAD_FILE
#define CMD_GAME_HEAD_FILE

#include "biostream.h"

//////////////////////////////////////////////////////////////////////////
//登录数据包定义

#define MDM_GR_LOGON				1									//房间登录

#define SUB_GR_LOGON_ACCOUNTS		1									//帐户登录
#define SUB_GR_LOGON_USERID			2									//I D 登录
#define SUB_GR_LOGON_USERID_V2		3									//I D 登录
#define SUB_GR_LOGON_USERID_V3		4									//I D 登录

#define SUB_GR_HEART_BEAT			10									//心跳

#define SUB_GR_LOGON_SUCCESS		100									//登录成功
#define SUB_GR_LOGON_ERROR			101									//登录失败
#define SUB_GR_LOGON_FINISH			102									//登录完成

#define SUB_GR_LOGON_CHECK_ROOM		103									//登录完成后，校验房间号是否存在

//房间帐号登录
struct CMD_GR_LogonByAccounts
{
	enum {M_ID = MDM_GR_LOGON};
	enum {S_ID = SUB_GR_LOGON_ACCOUNTS};

	unsigned int							dwPlazaVersion;						//广场版本
	unsigned int							dwProcessVersion;					//进程版本
	char							szAccounts[NAME_LEN];				//登录帐号
	char							szPassWord[PASS_LEN];				//登录密码

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_LogonByAccounts() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_LogonByAccounts& pl)
	{
		bos << pl.dwPlazaVersion;
		bos << pl.dwProcessVersion;

		bos.write((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_LogonByAccounts& pl)
	{	
		pl.reset();
		bis >> pl.dwPlazaVersion;
		bis >> pl.dwProcessVersion;

		bis.read((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));

		return bis;
	}
};

//房间 ID 登录
struct CMD_GR_LogonByUserID
{
	enum {M_ID = MDM_GR_LOGON};
	enum {S_ID = SUB_GR_LOGON_USERID};

	unsigned int							dwPlazaVersion;						//广场版本
	unsigned int							dwProcessVersion;					//进程版本
	unsigned int							dwUserID;							//用户 I D
	char									szPassWord[PASS_LEN];				//登录密码

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_LogonByUserID() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_LogonByUserID& pl)
	{
		bos << pl.dwPlazaVersion;
		bos << pl.dwProcessVersion;
		bos << pl.dwUserID;

		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_LogonByUserID& pl)
	{	
		pl.reset();
		bis >> pl.dwPlazaVersion;
		bis >> pl.dwProcessVersion;
		bis >> pl.dwUserID;

		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));

		return bis;
	}
};

struct CMD_GR_LogonByUserID_V2
{
	enum {M_ID = MDM_GR_LOGON};
	enum {S_ID = SUB_GR_LOGON_USERID_V2};

	unsigned int							dwPlazaVersion;						//广场版本
	unsigned int							dwProcessVersion;					//进程版本
	unsigned int							dwUserID;							//用户 I D
	char									szPassWord[PASS_LEN];				//登录密码
	char									szIP[PASS_LEN];				//IP

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_LogonByUserID_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_LogonByUserID_V2& pl)
	{
		bos << pl.dwPlazaVersion;
		bos << pl.dwProcessVersion;
		bos << pl.dwUserID;

		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bos.write((char*)pl.szIP,sizeof(pl.szIP));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_LogonByUserID_V2& pl)
	{	
		pl.reset();
		bis >> pl.dwPlazaVersion;
		bis >> pl.dwProcessVersion;
		bis >> pl.dwUserID;

		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bis.read((char*)pl.szIP,sizeof(pl.szIP));

		return bis;
	}
};

struct CMD_GR_LogonByUserID_V3
{
	enum {M_ID = MDM_GR_LOGON};
	enum {S_ID = SUB_GR_LOGON_USERID_V3};

	unsigned int							dwPlazaVersion;						//广场版本
	unsigned int							dwProcessVersion;					//进程版本
	unsigned int							dwUserID;							//用户 I D
	char									szPassWord[PASS_LEN];				//登录密码
	char									szIP[PASS_LEN];						//IP

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_LogonByUserID_V3() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_LogonByUserID_V3& pl)
	{
		bos << pl.dwPlazaVersion;
		bos << pl.dwProcessVersion;
		bos << pl.dwUserID;

		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bos.write((char*)pl.szIP,sizeof(pl.szIP));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_LogonByUserID_V3& pl)
	{	
		pl.reset();
		bis >> pl.dwPlazaVersion;
		bis >> pl.dwProcessVersion;
		bis >> pl.dwUserID;

		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bis.read((char*)pl.szIP,sizeof(pl.szIP));

		return bis;
	}
};

//登录成功消息
struct CMD_GR_LogonSuccess
{
	enum {M_ID = MDM_GR_LOGON};
	enum {S_ID = SUB_GR_LOGON_SUCCESS};

	unsigned int							dwUserID;							//用户 I D

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_LogonSuccess() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_LogonSuccess& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_LogonSuccess& pl)
	{	
		pl.reset();

		bis >> pl.dwUserID;

		return bis;
	}
};

//登录失败
struct CMD_GR_LogonError
{
	enum {M_ID = MDM_GR_LOGON};
	enum {S_ID = SUB_GR_LOGON_ERROR};

	int							lErrorCode;							//错误代码
	char							szErrorDescribe[128];				//错误消息

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_LogonError() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_LogonError& pl)
	{
		bos << pl.lErrorCode;

		bos.write((char*)pl.szErrorDescribe,sizeof(pl.szErrorDescribe));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_LogonError& pl)
	{	
		pl.reset();
		bis >> pl.lErrorCode;

		bis.read((char*)pl.szErrorDescribe,sizeof(pl.szErrorDescribe));

		return bis;
	}
};

//校验房号是否存在
struct CMD_GR_LogonCheckRoom
{
	enum { M_ID = MDM_GR_LOGON };
	enum { S_ID = SUB_GR_LOGON_CHECK_ROOM };

	unsigned int							dwUserID;							//用户 I D
	unsigned int							dwRoomID;							//房间号
	unsigned int							dwTableID;							//桌号

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_LogonCheckRoom() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_LogonCheckRoom& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwRoomID;
		bos << pl.dwTableID;
		
		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_LogonCheckRoom& pl)
	{
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.dwRoomID;
		bis >> pl.dwTableID;

		return bis;
	}
};

//////////////////////////////////////////////////////////////////////////
//用户数据包定义

#define MDM_GR_USER					2									//用户信息

#define SUB_GR_USER_SIT_REQ			1									//坐下请求
#define SUB_GR_USER_SIT_REQ_V2		5									//坐下请求
#define SUB_GR_USER_LOOKON_REQ		2									//旁观请求
#define SUB_GR_USER_STANDUP_REQ		3									//起立请求
#define SUB_GR_USER_LEFT_GAME_REQ	4									//离开游戏
#define SUB_GR_USER_SIT_REQ_V3		6									//坐下请求

#define SUB_GR_USER_STATUS_REQ		10									//查询玩家状态，可作心跳使用
#define SUB_GR_USER_STATUS_REP		11									//查询玩家状态，可作心跳使用

#define SUB_GR_USER_STATUS_HAOYOU	12									//好友房用户暂时离开状态

#define SUB_GR_USER_COME			100									//用户进入
#define SUB_GR_USER_STATUS			101									//用户状态
#define SUB_GR_USER_SCORE			102									//用户分数
#define SUB_GR_SIT_FAILED			103									//坐下失败
#define SUB_GR_USER_RIGHT			104									//用户权限
#define SUB_GR_MEMBER_ORDER			105									//会员等级

#define SUB_GR_USER_CHAT			200									//聊天消息
#define SUB_GR_USER_WISPER			201									//私语消息
#define SUB_GR_USER_RULE			202									//用户规则

#define SUB_GR_USER_INVITE			300									//邀请消息
#define SUB_GR_USER_INVITE_REQ		301									//邀请请求

#define SUB_GR_USER_SPEAKER_MSG_REP		302								//接收到喇叭消息

#define SUB_GR_USER_SEND_LABA_REQ				304							//请求发送喇叭
#define SUB_GR_USER_SEND_LABA_REP				305							//请求发送喇叭结果

#define SUB_GR_USER_CHECK_LABA_REQ				306							//请求校验喇叭内容
#define SUB_GR_USER_CHECK_LABA_REP				307							//校验喇叭结果


#define SUB_GR_USER_MASTER_DISMISS_FRIEND_REQ			408						//房主要求解散好友房
#define SUB_GR_USER_MASTER_DISMISS_FRIEND_REP			409						//房主要求解散好友房广播

#define SUB_GR_USER_GUEST_DISMISS_FRIEND_REQ			410						//游戏中请求提前结束好友房
#define SUB_GR_USER_GUEST_DISMISS_FRIEND_RESULT			411						//游戏中请求提前结束好友房的用户选择

#define SUB_GR_USER_FACE_URL							420						//玩家自定义头像
#define SUB_GR_USER_OFFLINE_REMAIN_TIME					421						//玩家断线剩余时间
#define SUB_GR_USER_OFFLINE_REMAIN_TIME_V2				423						//玩家断线剩余时间
#define SUB_GR_USER_EXT_INFO			422								//玩家附加信息

#define SUB_GR_USER_YY_SEQ			430									//玩家发送语音
#define SUB_GR_USER_YY_REP			431									//玩家语音广播

#define SUB_GR_USER_HB_SEQ			432									//红包
#define SUB_GR_USER_HB_REP			433									//红包广播

#define SUB_GR_USER_WEIHU_REP			434									//维护广播

#define SUB_GR_USER_GPS_REQ			436								//GPS
#define SUB_GR_USER_GPS_REP			437								//GPS

#define SUB_GR_USER_GPS_REQ_V2			472							//GPS
#define SUB_GR_USER_GPS_REP_V2			473							//GPS

#define SUB_S_GAME_DISSMISS_ROOM			438						//所有玩家对解散房间的响应
#define SUB_S_GAME_DISSMISS_TIME            439                     //解散房间倒计时
#define SUB_S_GAME_PLAYER_REDYE_STATE       440                     //玩家准备状态

#define SUB_GR_TABLE_LIST_QUERY				441						// 查询房间桌子列表
#define SUB_GR_TABLE_LIST_REP				442						// 查询房间桌子列表结果（只返回桌子上已坐下玩家数据）
#define SUB_GR_TABLE_LIST_REP_END			443						// 查询房间桌子列表结果结束
#define SUB_GR_TABLE_LIST_TABLE_UPDATE		444						// 房间桌子数据更新（服务端主动同步）
#define SUB_GR_TABLE_LIST_USER_INFO_QUERY	445						// 查看房间桌子上玩家信息
#define SUB_GR_TABLE_LIST_USER_INFO_REP		446						// 查看房间桌子上玩家信息结果
#define SUB_GR_TABLE_LOCK_REQ				447						// 桌子锁设置请求
#define SUB_GR_TABLE_LOCK_REP				448						// 桌子锁设置结果
#define SUB_GR_TABLE_LOCK_STATE_SYN			449						// 桌子锁状态同步给同桌成员
#define SUB_GR_TABLE_LIST_LABA_QUERY		450						// 查询喇叭数量
#define SUB_GR_TABLE_LIST_LABA_REP			451						// 查询喇叭数量返回
 
#define SUB_GR_USER_BBS_SCROLL_REP			452						// 滚动公告信息结果
#define SUB_GR_ROOM_FLAG					453						// 房间标识数据
#define SUB_GR_USER_COME_EX					454						// 玩家进入后的补充数据
#define SUB_GR_SIT_FAILED_EX				455						// 坐下失败
#define SUB_GR_KICK_OFF_TABLE				457						// 将玩家踢下桌


#define SUB_GR_USER_SEND_START_REQ			470						//房主发送开始游戏按钮
#define SUB_GR_USER_SEND_START_REP			471						//房主发送开始游戏按钮结果

//断线重连服务器推送过来的玩家准备信息
struct CMD_GR_PLAYER_REDEAY_STATE
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_S_GAME_PLAYER_REDYE_STATE };

	bool redy_situation[MAX_CHAIR_NORMAL];  //玩家的准备状态 

	void reset() { memset(this, 0, sizeof(*this)); for (int i = 0; i < sizeof(redy_situation) / sizeof(redy_situation[0]); i++){ redy_situation[i] = 0; } };

	friend bostream& operator<<(bostream& bos, const CMD_GR_PLAYER_REDEAY_STATE& pl)
	{

		bos.write((char*)pl.redy_situation, sizeof(pl.redy_situation));
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_PLAYER_REDEAY_STATE& pl)
	{
		pl.reset();
		bis.read((char *)pl.redy_situation, sizeof(pl.redy_situation));
		return bis;
	}
};

//断线重连服务器推送过来的解散房间的信息（如果有）
struct CMD_GR_DISSMISS_ROOM
{
	enum { AGREE=1, DISAGREE, DISMISS_CREATOR, WATING, DISSMISS_MAX };  //同意 不同意 解散房间发起者  等待中（尚未决定同意与否）

	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_S_GAME_DISSMISS_ROOM };

	unsigned int  player_situation[MAX_CHAIR_NORMAL];  //其他玩家对解散房间的反应 (其中下标 0 1 2 3表示椅子编号)
	unsigned int  dissmiss_timer;  //自动结算倒计时时间


	void reset() { memset(this, 0, sizeof(*this)); for (int i = 0; i < sizeof(player_situation)/sizeof(player_situation[0]); i++){ player_situation[i] = DISSMISS_MAX; } };

	friend bostream& operator<<(bostream& bos, const CMD_GR_DISSMISS_ROOM& pl)
	{

		bos.write((char*)pl.player_situation, sizeof(pl.player_situation));
		bos << pl.dissmiss_timer;
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_DISSMISS_ROOM& pl)
	{
		pl.reset();
		bis.read((char *)pl.player_situation, sizeof(pl.player_situation));
		bis >> pl.dissmiss_timer;
		return bis;
	}
};


struct CMD_GR_DISSMISS_TIME_RSP
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_S_GAME_DISSMISS_TIME };

	unsigned int  dissmiss_timer;   //服务器计算出来的解散计时时间的剩余秒数

	void reset() { memset(this, 0, sizeof(*this)); dissmiss_timer = 0;}
	friend bostream& operator<<(bostream& bos, const CMD_GR_DISSMISS_TIME_RSP& pl)
	{

		bos << pl.dissmiss_timer;
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_DISSMISS_TIME_RSP& pl)
	{
		pl.reset();
		bis >> pl.dissmiss_timer;
		return bis;
	}
};



struct CMD_GR_UserGPSReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_GPS_REQ };

	unsigned int			dwType;
	unsigned int			dwUserID;
	double					fLongitude;
	double					fLatitude;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserGPSReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserGPSReq& pl)
	{
		bos << pl.dwType;
		bos << pl.dwUserID;
		bos << pl.fLongitude;
		bos << pl.fLatitude;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserGPSReq& pl)
	{
		bis >> pl.dwType;
		bis >> pl.dwUserID;
		bis >> pl.fLongitude;
		bis >> pl.fLatitude;

		return bis;
	}
};


struct CMD_GR_UserGPSRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_GPS_REP };

	unsigned int			dwType;
	unsigned int			dwUserID;
	double					fLongitude;
	double					fLatitude;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserGPSRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserGPSRep& pl)
	{
		bos << pl.dwType;
		bos << pl.dwUserID;
		bos << pl.fLongitude;
		bos << pl.fLatitude;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserGPSRep& pl)
	{
		bis >> pl.dwType;
		bis >> pl.dwUserID;
		bis >> pl.fLongitude;
		bis >> pl.fLatitude;

		return bis;
	}
};

struct CMD_GR_UserGPSReq_V2
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_GPS_REQ_V2 };

	unsigned int			dwType;
	unsigned int			dwUserID;
	double					fLongitude;
	double					fLatitude;
	unsigned short			nAddrLen;
	char					szAddr[255];

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserGPSReq_V2() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserGPSReq_V2& pl)
	{
		bos << pl.dwType;
		bos << pl.dwUserID;
		bos << pl.fLongitude;
		bos << pl.fLatitude;

		bos << pl.nAddrLen;
		bos.write((char*)pl.szAddr,pl.nAddrLen);


		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserGPSReq_V2& pl)
	{
		bis >> pl.dwType;
		bis >> pl.dwUserID;
		bis >> pl.fLongitude;
		bis >> pl.fLatitude;

		bis >> pl.nAddrLen;
		bis.read((char*)pl.szAddr,pl.nAddrLen);

		return bis;
	}
};

struct CMD_GR_UserGPSRep_V2
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_GPS_REP_V2 };

	unsigned int			dwType;
	unsigned int			dwUserID;
	double					fLongitude;
	double					fLatitude;
	unsigned short			nAddrLen;
	char					szAddr[255];

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserGPSRep_V2() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserGPSRep_V2& pl)
	{
		bos << pl.dwType;
		bos << pl.dwUserID;
		bos << pl.fLongitude;
		bos << pl.fLatitude;

		bos << pl.nAddrLen;
		bos.write((char*)pl.szAddr,pl.nAddrLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserGPSRep_V2& pl)
	{
		bis >> pl.dwType;
		bis >> pl.dwUserID;
		bis >> pl.fLongitude;
		bis >> pl.fLatitude;

		bis >> pl.nAddrLen;
		bis.read((char*)pl.szAddr,pl.nAddrLen);

		return bis;
	}
};

//玩家发送红包
struct CMD_GR_UserWEIHURep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_WEIHU_REP };

	unsigned int	dwType;		//维护类型
	unsigned short	nLen;
	char			szExtInfo[256];	//用户名
	//float			price;			//红包数量

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserWEIHURep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserWEIHURep& pl)
	{
		bos << pl.dwType;
		bos << pl.nLen;
		bos.write((char*)pl.szExtInfo, sizeof(pl.szExtInfo));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserWEIHURep& pl)
	{
		bis >> pl.dwType;
		bis >> pl.nLen;
		bis.read((char*)pl.szExtInfo, sizeof(pl.szExtInfo));

		return bis;
	}
};

//玩家发送红包
struct CMD_GR_UserHBRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_HB_REP };

	unsigned int	dwUserID;		//数据库 ID	
	//char			szExtInfo[32];	//用户名
	float			price;			//红包数量

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserHBRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserHBRep& pl)
	{
		bos << pl.dwUserID;
		//bos.write((char*)pl.szExtInfo, sizeof(pl.szExtInfo));
		bos << pl.price;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserHBRep& pl)
	{
		bis >> pl.dwUserID;
		//bis.read((char*)pl.szExtInfo, sizeof(pl.szExtInfo));
		bis >> pl.price;

		return bis;
	}
};
//发送游戏开始消息
struct CMD_GR_UserStartGameReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SEND_START_REQ };

	unsigned int dwUserID;	//数据库 ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserStartGameReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserStartGameReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserStartGameReq& pl)
	{
		bis >> pl.dwUserID;

		return bis;
	}
};

//房主发送开始游戏按钮结果
struct CMD_GR_UserStartGameRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SEND_START_REP };

	unsigned int dwtype;	//返回类型 0：成功；1：玩家数量不足；2：有玩家没有准备；3:玩家掉线

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserStartGameRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserStartGameRep& pl)
	{
		bos << pl.dwtype;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserStartGameRep& pl)
	{
		bis >> pl.dwtype;

		return bis;
	}
};
//玩家发送语音
struct CMD_GR_UserYYInfo
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_YY_SEQ };

	unsigned int dwUserID;	//数据库 ID
	unsigned short	nLen;			
	char			szExtInfo[256];	//语音地址

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserYYInfo() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserYYInfo& pl)
	{
		bos << pl.dwUserID;
		bos << pl.nLen;
		bos.write((char*)pl.szExtInfo, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserYYInfo& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.nLen;
		bis.read((char*)pl.szExtInfo, pl.nLen);

		return bis;
	}
};

//玩家语音广播
struct CMD_GR_UserYYREPInfo
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_YY_REP };

	unsigned int dwUserID;	//数据库 ID
	unsigned short	nLen;			
	char			szExtInfo[256];	//语音地址

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserYYREPInfo() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserYYREPInfo& pl)
	{
		bos << pl.dwUserID;
		bos << pl.nLen;
		bos.write((char*)pl.szExtInfo, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserYYREPInfo& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.nLen;
		bis.read((char*)pl.szExtInfo, pl.nLen);

		return bis;
	}
};

//玩家附加信息
struct CMD_GR_UserExtInfo
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_EXT_INFO };

	unsigned int dwUserID;	//数据库 ID
	unsigned short	nLen;			
	char			szExtInfo[256];	//附加信息，格式 k:v|k:v,  目前支持ip信息

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserExtInfo() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserExtInfo& pl)
	{
		bos << pl.dwUserID;
		bos << pl.nLen;
		bos.write((char*)pl.szExtInfo, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserExtInfo& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.nLen;
		bis.read((char*)pl.szExtInfo, pl.nLen);

		return bis;
	}
};

//好友房用户暂时离开状态
struct CMD_GR_UserStatus_HaoYou
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_STATUS_HAOYOU };

	unsigned int	dwUserID;							//数据库 ID
	unsigned short	wChairID;							//椅子位置
	unsigned char	cbUserStatus;						//用户状态: 1离开 2回来

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserStatus_HaoYou() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserStatus_HaoYou& pl)
	{
		bos << pl.dwUserID;
		bos << pl.wChairID;
		bos << pl.cbUserStatus;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserStatus_HaoYou& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.wChairID;
		bis >> pl.cbUserStatus;

		return bis;
	}
};


//玩家断线的剩余时间
struct CMD_GR_UserOfflineRemainTime
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_OFFLINE_REMAIN_TIME };
		
	unsigned short	nRemainTime[8];				//最多8个玩家，每个人的剩余时间。单位： 分钟

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserOfflineRemainTime() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserOfflineRemainTime& pl)
	{
		bos.write((char*)pl.nRemainTime, sizeof(pl.nRemainTime));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserOfflineRemainTime& pl)
	{
		bis.read((char*)pl.nRemainTime, sizeof(pl.nRemainTime));

		return bis;
	}
};

//玩家断线的剩余时间
struct CMD_GR_UserOfflineRemainTimeV2
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_OFFLINE_REMAIN_TIME_V2 };

	unsigned short	nRemainTime[8];				//最多8个玩家，每个人的剩余时间。单位： 秒

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserOfflineRemainTimeV2() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserOfflineRemainTimeV2& pl)
	{
		bos.write((char*)pl.nRemainTime, sizeof(pl.nRemainTime));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserOfflineRemainTimeV2& pl)
	{
		bis.read((char*)pl.nRemainTime, sizeof(pl.nRemainTime));

		return bis;
	}
};

//玩家自定义头像
struct CMD_GR_UserFaceUrl
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_FACE_URL };

	unsigned int dwUserID;	//数据库 ID
	unsigned short	nLen;			
	char			szFaceUrl[256];	//头像地址

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserFaceUrl() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserFaceUrl& pl)
	{
		bos << pl.dwUserID;
		bos << pl.nLen;
		bos.write((char*)pl.szFaceUrl, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserFaceUrl& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.nLen;
		bis.read((char*)pl.szFaceUrl, pl.nLen);

		return bis;
	}
};

//房主要求解散好友房
struct CMD_GR_UserMasterDismissFriendReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_MASTER_DISMISS_FRIEND_REQ };

	unsigned short	nTableID;			//桌号
	char			szRoomID[NAME_LEN];	//房间号

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserMasterDismissFriendReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserMasterDismissFriendReq& pl)
	{
		bos << pl.nTableID;
		bos.write((char*)pl.szRoomID, sizeof(pl.szRoomID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserMasterDismissFriendReq& pl)
	{
		bis >> pl.nTableID;
		bis.read((char*)pl.szRoomID, sizeof(pl.szRoomID));

		return bis;
	}
};

//房主要求解散好友房广播
struct CMD_GR_UserMasterDismissFriendRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_MASTER_DISMISS_FRIEND_REP };

	unsigned short nCode;		//0-允许解散，1-不允许解散游戏已经开始
	char szContent[NAME_LEN];	//描述信息

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserMasterDismissFriendRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserMasterDismissFriendRep& pl)
	{
		bos << pl.nCode;
		bos.write((char*)pl.szContent, sizeof(pl.szContent));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserMasterDismissFriendRep& pl)
	{
		bis >> pl.nCode;
		bis.read((char*)pl.szContent, sizeof(pl.szContent));

		return bis;
	}
};


//游戏中请求提前结束好友房
struct CMD_GR_UserGuestDismissFriendReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_GUEST_DISMISS_FRIEND_REQ };

	unsigned int dwUserID;	//玩家 ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserGuestDismissFriendReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserGuestDismissFriendReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserGuestDismissFriendReq& pl)
	{
		bis >> pl.dwUserID;

		return bis;
	}
};

//游戏中请求提前结束好友房的用户选择
struct CMD_GR_UserGuestDismissFriendResult
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_GUEST_DISMISS_FRIEND_RESULT };

	unsigned int	dwUserID;	//数据库 ID
	char			bFlag;		//1:同意  0：拒绝

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserGuestDismissFriendResult() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserGuestDismissFriendResult& pl)
	{
		bos << pl.dwUserID;
		bos << pl.bFlag;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserGuestDismissFriendResult& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.bFlag;

		return bis;
	}
};


//会员等级
struct CMD_GR_MemberOrder
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_MEMBER_ORDER};

	unsigned int							dwUserID;							//数据库 ID
	unsigned char							cbMemberOrder;						//会员等级

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_MemberOrder() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_MemberOrder& pl)
	{
		bos << pl.dwUserID;
		bos << pl.cbMemberOrder;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_MemberOrder& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.cbMemberOrder;

		return bis;
	}
};

//用户权限
struct CMD_GR_UserRight
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_RIGHT};

	unsigned int							dwUserID;							//数据库 ID
	unsigned int							dwUserRight;						//用户权限

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserRight() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_UserRight& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwUserRight;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_UserRight& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.dwUserRight;

		return bis;
	}
};

//用户状态
struct CMD_GR_UserStatus
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_STATUS};

	unsigned int							dwUserID;							//数据库 ID
	unsigned short							wTableID;							//桌子位置
	unsigned short							wChairID;							//椅子位置
	unsigned char							cbUserStatus;						//用户状态

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserStatus() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_UserStatus& pl)
	{
		bos << pl.dwUserID;
		bos << pl.wTableID;
		bos << pl.wChairID;
		bos << pl.cbUserStatus;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_UserStatus& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.wTableID;
		bis >> pl.wChairID;
		bis >> pl.cbUserStatus;

		return bis;
	}
};

//用户分数
struct CMD_GR_UserScore
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_SCORE};

	int							lLoveliness;						//用户魅力
	//LONG							lInsureScore;						//消费金币
	//LONG							lGameGold;							//游戏金币
	unsigned int							dwUserID;							//用户 I D
	tagUserScore					UserScore;							//积分信息

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserScore() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_UserScore& pl)
	{
		bos << pl.lLoveliness;
		bos << pl.dwUserID;
		bos << pl.UserScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_UserScore& pl)
	{	
		pl.reset();
		bis >> pl.lLoveliness;
		bis >> pl.dwUserID;
		bis >> pl.UserScore;

		return bis;
	}
};

//请求坐下
struct CMD_GR_UserSitReq
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_SIT_REQ};
	
	unsigned short							wTableID;							//桌子位置
	unsigned short							wChairID;							//椅子位置
	unsigned char							cbPassLen;							//密码长度
	char							szTablePass[PASS_LEN];				//桌子密码

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserSitReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_UserSitReq& pl)
	{
		bos << pl.wTableID;
		bos << pl.wChairID;
		bos << pl.cbPassLen;

		bos.write((char*)pl.szTablePass,sizeof(pl.cbPassLen));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_UserSitReq& pl)
	{	
		pl.reset();
		bis >> pl.wTableID;
		bis >> pl.wChairID;
		bis >> pl.cbPassLen;

		bis.read((char*)pl.szTablePass,sizeof(pl.cbPassLen));

		return bis;
	}
};


//请求坐下。因为原协议有bug，只能传1位的密码
struct CMD_GR_UserSitReq_V2
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SIT_REQ_V2 };

	unsigned short							wTableID;							//桌子位置
	unsigned short							wChairID;							//椅子位置
	unsigned char							cbPassLen;							//密码长度
	char							szTablePass[PASS_LEN];				//桌子密码

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserSitReq_V2() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserSitReq_V2& pl)
	{
		bos << pl.wTableID;
		bos << pl.wChairID;
		bos << pl.cbPassLen;

		bos.write((char*)pl.szTablePass, pl.cbPassLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserSitReq_V2& pl)
	{
		pl.reset();
		bis >> pl.wTableID;
		bis >> pl.wChairID;
		bis >> pl.cbPassLen;

		bis.read((char*)pl.szTablePass, pl.cbPassLen);

		return bis;
	}
};

// 请求坐指定桌子指定椅子
struct CMD_GR_UserSitReq_V3
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SIT_REQ_V3 };

	unsigned short							wTableID;							//桌子位置
	unsigned short							wChairID;							//椅子位置
	unsigned char							cbPassLen;							//密码长度
	char									szTablePass[PASS_LEN];				//桌子密码

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserSitReq_V3() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserSitReq_V3& pl)
	{
		bos << pl.wTableID;
		bos << pl.wChairID;
		bos << pl.cbPassLen;

		bos.write((char*)pl.szTablePass, pl.cbPassLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserSitReq_V3& pl)
	{
		pl.reset();
		bis >> pl.wTableID;
		bis >> pl.wChairID;
		bis >> pl.cbPassLen;

		bis.read((char*)pl.szTablePass, pl.cbPassLen);

		return bis;
	}
};

//邀请用户 
struct CMD_GR_UserInviteReq
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_INVITE_REQ};

	unsigned short							wTableID;							//桌子号码
	unsigned int							dwUserID;							//用户 I D

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserInviteReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_UserInviteReq& pl)
	{
		bos << pl.wTableID;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_UserInviteReq& pl)
	{	
		pl.reset();
		bis >> pl.wTableID;
		bis >> pl.dwUserID;

		return bis;
	}
};

//坐下失败
struct CMD_GR_SitFailed
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_SIT_FAILED};

	char							szFailedDescribe[256];				//错误描述

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_SitFailed() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_SitFailed& pl)
	{
		bos.write((char*)pl.szFailedDescribe,sizeof(pl.szFailedDescribe));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_SitFailed& pl)
	{	
		pl.reset();
		
		bis.read((char*)pl.szFailedDescribe,sizeof(pl.szFailedDescribe));

		return bis;
	}
};

// 坐下失败错误码
struct CMD_GR_SitFailedEx
{
	enum {HAD_SIT = 1, TABLE_LOCKED = 2, MONEY_LESS = 3, MONEY_OVER_LIMIT = 4, STOP_SERVICE = 5};
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_SIT_FAILED_EX};

	unsigned short			sCode;				// 坐下失败原因（1位置有人2房间上锁3金币不够4金币超限5房间维护）
	unsigned short			sData1;				// 保留参数1
	unsigned int			usData2;			// 保留参数2

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_SitFailedEx() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_SitFailedEx& pl)
	{
		bos << pl.sCode;
		bos << pl.sData1;
		bos << pl.usData2;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_SitFailedEx& pl)
	{	
		bis >> pl.sCode;
		bis >> pl.sData1;
		bis >> pl.usData2;
		return bis;
	}
};

// 服务器将玩家踢下桌子
struct CMD_GR_KickOffTable
{
	enum {KICK_REASON_TIME_OUT = 1, KICK_REASON_VIP_KICKED = 2};
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_KICK_OFF_TABLE};

	unsigned short			sCode;			// 踢下桌子原因（1挂机超时2被其他vip玩家踢）
	unsigned short			sData1;			// 保留参数1
	unsigned short			usData2;		// 保留参数2

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_KickOffTable() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_KickOffTable& pl)
	{
		bos << pl.sCode;
		bos << pl.sData1;
		bos << pl.usData2;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_KickOffTable& pl)
	{	
		bis >> pl.sCode;
		bis >> pl.sData1;
		bis >> pl.usData2;
		return bis;
	}
};

//聊天结构 
struct CMD_GR_UserChat
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_CHAT};

	unsigned short							wChatLength;						//信息长度
	unsigned int						crFontColor;						//信息颜色
	unsigned int							dwSendUserID;						//发送用户
	unsigned int							dwTargetUserID;						//目标用户
	char							szChatMessage[MAX_CHAT_LEN];		//聊天信息

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserChat() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_UserChat& pl)
	{
		bos << pl.wChatLength;
		bos << pl.crFontColor;
		bos << pl.dwSendUserID;
		bos << pl.dwTargetUserID;

		bos.write((char*)pl.szChatMessage,sizeof(pl.szChatMessage));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_UserChat& pl)
	{	
		pl.reset();
		bis >> pl.wChatLength;
		bis >> pl.crFontColor;
		bis >> pl.dwSendUserID;
		bis >> pl.dwTargetUserID;

		bis.read((char*)pl.szChatMessage,sizeof(pl.szChatMessage));

		return bis;
	}
};

//私语结构 
struct CMD_GR_Wisper
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_WISPER};

	unsigned short							wChatLength;						//信息长度
	unsigned int						crFontColor;						//信息颜色
	unsigned int							dwSendUserID;						//发送用户
	unsigned int							dwTargetUserID;						//目标用户
	char							szChatMessage[MAX_CHAT_LEN];		//聊天信息

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_Wisper() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_Wisper& pl)
	{
		bos << pl.wChatLength;
		bos << pl.crFontColor;
		bos << pl.dwSendUserID;
		bos << pl.dwTargetUserID;

		bos.write((char*)pl.szChatMessage,sizeof(pl.szChatMessage));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_Wisper& pl)
	{	
		pl.reset();
		bis >> pl.wChatLength;
		bis >> pl.crFontColor;
		bis >> pl.dwSendUserID;
		bis >> pl.dwTargetUserID;

		bis.read((char*)pl.szChatMessage,sizeof(pl.szChatMessage));

		return bis;
	}
};

//用户规则
struct CMD_GR_UserRule
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_RULE};

	bool							bPassword;							//设置密码
	bool							bLimitWin;							//限制胜率
	bool							bLimitFlee;							//限制断线
	bool							bLimitScore;						//限制分数
	bool							bCheckSameIP;						//效验地址
	unsigned short							wWinRate;							//限制胜率
	unsigned short							wFleeRate;							//限制逃跑
	int							lMaxScore;							//最高分数 
	int							lLessScore;							//最低分数
	char							szPassword[PASS_LEN];				//桌子密码

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserRule() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_UserRule& pl)
	{
		bos << pl.bPassword;
		bos << pl.bLimitWin;
		bos << pl.bLimitFlee;
		bos << pl.bLimitScore;
		bos << pl.bCheckSameIP;
		bos << pl.wWinRate;
		bos << pl.wFleeRate;
		bos << pl.lMaxScore;
		bos << pl.lLessScore;

		bos.write((char*)pl.szPassword,sizeof(pl.szPassword));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_UserRule& pl)
	{	
		pl.reset();
		bis >> pl.bPassword;
		bis >> pl.bLimitWin;
		bis >> pl.bLimitFlee;
		bis >> pl.bLimitScore;
		bis >> pl.wWinRate;
		bis >> pl.wFleeRate;
		bis >> pl.lMaxScore;
		bis >> pl.lLessScore;

		bis.read((char*)pl.szPassword,sizeof(pl.szPassword));

		return bis;
	}
};

//邀请用户 
struct CMD_GR_UserInvite
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_INVITE};

	unsigned short							wTableID;							//桌子号码
	unsigned int							dwUserID;							//用户 I D

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserInvite() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_UserInvite& pl)
	{
		bos << pl.wTableID;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_UserInvite& pl)
	{	
		pl.reset();
		bis >> pl.wTableID;
		bis >> pl.dwUserID;

		return bis;
	}
};


// 请求校验发送喇叭内容
struct CMD_GR_UserCheckLabaReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_CHECK_LABA_REQ };
	
	short			iLen;
	char			strLabaInfo[256];	// 喇叭内容

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserCheckLabaReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserCheckLabaReq& pl)
	{
		bos << pl.iLen;
		bos.write((char*)pl.strLabaInfo, pl.iLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserCheckLabaReq& pl)
	{
		bis >> pl.iLen;
		bis.read((char*)pl.strLabaInfo, pl.iLen);

		return bis;
	}
};

//校验喇叭结果
struct CMD_GR_UserCheckLabaRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_CHECK_LABA_REP };

	short			nCode;				// 返回码：0为成功
	short			nLen;
	char			strLabaInfo[256];	// 喇叭内容

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserCheckLabaRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserCheckLabaRep& pl)
	{
		bos << pl.nCode;
		bos << pl.nLen;
		bos.write((char*)pl.strLabaInfo, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserCheckLabaRep& pl)
	{
		bis >> pl.nCode;
		bis >> pl.nLen;
		bis.read((char*)pl.strLabaInfo, pl.nLen);

		return bis;
	}
};

struct CMD_GR_UserBbsScrollResult
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_BBS_SCROLL_REP};

	short	nBbsScroll;				//滚动公告的条数.最多10条
	char	szBbsScroll[10][100];	//滚动公告内容

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserBbsScrollResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_UserBbsScrollResult& pl)
	{
		bos << pl.nBbsScroll;

		bos.write((char*)pl.szBbsScroll,sizeof(pl.szBbsScroll));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_UserBbsScrollResult& pl)
	{	
		pl.reset();
		bis >> pl.nBbsScroll;

		bis.read((char*)pl.szBbsScroll,sizeof(pl.szBbsScroll));

		return bis;
	}
};

// 坐桌模式标志
struct CMD_GR_RoomFlag
{
	enum { SIT_FLAG = 0, LOCK_FLAG = 1};
	enum { M_ID = MDM_GR_USER};
	enum { S_ID = SUB_GR_ROOM_FLAG};

	unsigned int					usFlag;			// 标志位（0位坐桌标志1位加锁标志）

	void reset()	{ memset(this, 0, sizeof(*this));}
	CMD_GR_RoomFlag(){reset();}
	friend bostream& operator<<(bostream& bos, const CMD_GR_RoomFlag& pl)
	{
		bos << pl.usFlag;
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_RoomFlag& pl)
	{
		bis >> pl.usFlag;
		return bis;
	}
};

// 玩家进入游戏桌子补充数据协议
struct CMD_GR_UserComeEx
{
	enum { M_ID = MDM_GR_USER};
	enum { S_ID = SUB_GR_USER_COME_EX};

	unsigned int						dwData1;					// 备用字段(玩家ID)
	char								szDescribe[128];			// 个性签名

	void reset() { memset(this, 0, sizeof(*this));}
	CMD_GR_UserComeEx(){reset();}
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserComeEx& pl)
	{
		bos << pl.dwData1;
		bos.write((char*)pl.szDescribe, sizeof(pl.szDescribe));
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_UserComeEx& pl)
	{
		bis >> pl.dwData1;
		bis.read(pl.szDescribe, sizeof(pl.szDescribe));
		return bis;
	}
				
};

// 请求发送喇叭
struct CMD_GR_UserSendLabaReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SEND_LABA_REQ};

	unsigned int					dwUserID;		//玩家 ID
	short							nLen;
	char							strLabaInfo[256];	// 喇叭内容

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserSendLabaReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserSendLabaReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.nLen;

		bos.write((char*)pl.strLabaInfo, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserSendLabaReq& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.nLen;

		bis.read((char*)pl.strLabaInfo, pl.nLen);
		return bis;
	}
};

// 发送喇叭结果
struct CMD_GR_UserSendLabaRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SEND_LABA_REP };

	short							nCode;			// 返回码：0为成功
	unsigned int					dwUserID;		//玩家 ID
	unsigned int					dwCurScore;		//成功后的结果：当前带的游戏分数

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserSendLabaRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserSendLabaRep& pl)
	{
		bos << pl.nCode;
		bos << pl.dwUserID;
		bos << pl.dwCurScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserSendLabaRep& pl)
	{
		bis >> pl.nCode;
		bis >> pl.dwUserID;
		bis >> pl.dwCurScore;

		return bis;
	}
};

//接收到喇叭消息
struct CMD_GR_SpeakerMsgRep
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_SPEAKER_MSG_REP};

	unsigned short						nType;					//消息类型
	unsigned short						nLen;					//消息长度
	char								szMsg[256];				//消息内容

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_SpeakerMsgRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_SpeakerMsgRep& pl)
	{
		bos << pl.nType;
		bos << pl.nLen;

		bos.write((char*)pl.szMsg, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_SpeakerMsgRep& pl)
	{	
		pl.reset();
		bis >> pl.nType;
		bis >> pl.nLen;

		bis.read((char*)pl.szMsg, pl.nLen);

		return bis;
	}
};

// 查询房间桌子列表消息
struct CMD_GR_TableListQuery
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_QUERY};

	unsigned short						sBeginTableIndex;			// 查询起始桌子id
	unsigned short						sEndTableIndex;				// 查询结束桌子id
	unsigned short						sUserTableIndex;			// 玩家查询参照桌子id(暂时保留不用)
	unsigned short						sUserAOI;					// 玩家监视桌子数据变化范围（暂时保留不用）
	unsigned short						sData1;						// 保留参数1
	unsigned short						sData2;						// 保留参数2
	// 

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_TableListQuery() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_TableListQuery& pl)
	{

		bos << pl.sBeginTableIndex;
		bos << pl.sEndTableIndex;
		bos << pl.sUserTableIndex;
		bos << pl.sUserAOI;
		bos << pl.sData1;
		bos << pl.sData2;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_TableListQuery& pl)
	{	
		pl.reset();
		bis >> pl.sBeginTableIndex;
		bis >> pl.sEndTableIndex;
		bis >> pl.sUserTableIndex;
		bis >> pl.sUserAOI;
		bis >> pl.sData1;
		bis >> pl.sData2;
		return bis;
	}
};

// 查询房间桌子列表结果消息（只返回桌子上已坐下玩家数据）
struct CMD_GR_TableListRep
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_REP};

	unsigned short						sResult;					// 查询结果（0表示成功1表示失败）
	unsigned short						sTableID;					// 桌子ID
	unsigned short						sLockState;					// 上锁状态（0没锁1有锁)
	unsigned short						sData1;						// 保留参数1
	// 桌子上玩家数据
	unsigned int						usPlayerID;					// 桌上玩家ID
	unsigned short						sChairID;					// 椅子ID
	unsigned short						sGender;					// 玩家性别
	unsigned short						sVip;						// VIP标识
	unsigned short						sData2;						// 保留参数2
	unsigned int						usGoldScore;				// 金币数量

	char								szNickname[NAME_LEN];		// 玩家昵称
	char								szFaceURL[256];				// 头像


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_TableListRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_TableListRep& pl)
	{
		bos << pl.sResult;
		bos << pl.sTableID;
		bos << pl.sLockState;
		bos << pl.sData1;
		bos << pl.usPlayerID;
		bos << pl.sChairID;
		bos << pl.sGender;
		bos << pl.sVip;
		bos << pl.sData2;
		bos << pl.usGoldScore;

		bos.write((char*)pl.szNickname, sizeof(pl.szNickname));
		bos.write((char*)pl.szFaceURL, sizeof(pl.szFaceURL));
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_TableListRep& pl)
	{	
		pl.reset();
		bis >> pl.sResult;
		bis >> pl.sTableID;
		bis >> pl.sLockState;
		bis >> pl.sData1;
		bis >> pl.usPlayerID;
		bis >> pl.sChairID;
		bis >> pl.sGender;
		bis >> pl.sVip;
		bis >> pl.sData2;
		bis >> pl.usGoldScore;

		bis.read((char*)pl.szNickname, sizeof(pl.szNickname));
		bis.read((char*)pl.szFaceURL, sizeof(pl.szFaceURL));

		return bis;
	}
};

// 查询房间桌子列表结果结束消息
struct CMD_GR_TableListRepEnd
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_REP_END};

	unsigned int						usUserID;					// 查询玩家id

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_TableListRepEnd() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_TableListRepEnd& pl)
	{
		bos << pl.usUserID;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_TableListRepEnd& pl)
	{	
		pl.reset();
		bis >> pl.usUserID;
		return bis;
	}
};

// 房间桌子数据更新
struct CMD_GR_TableListUpdate
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_TABLE_UPDATE};

	unsigned short						sUpdateType;				// 变更类型(1桌子上锁2桌子解锁3玩家坐下4玩家离开5金币变更)
	unsigned short						sTableID;					// 变更桌子ID
	unsigned short						sLockState;					// 上锁状态（0没锁1有锁)
	unsigned short						sData1;						// 保留参数1

	// 桌子上玩家数据
	unsigned int						usPlayerID;					// 桌上玩家ID
	unsigned short						sChairID;					// 椅子ID
	unsigned short						sGender;					// 玩家性别
	unsigned short						sVip;						// VIP标识
	unsigned short						sData2;						// 保留参数2
	unsigned int						usGoldScore;				// 金币数量

	char								szNickname[NAME_LEN];		// 玩家昵称
	char								szFaceURL[256];				// 头像 

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_TableListUpdate() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_TableListUpdate& pl)
	{
		bos << pl.sUpdateType;
		bos << pl.sTableID;
		bos << pl.sLockState;
		bos << pl.sData1;
		bos << pl.usPlayerID;
		bos << pl.sChairID;
		bos << pl.sGender;
		bos << pl.sVip;
		bos << pl.sData2;
		bos << pl.usGoldScore;

		bos.write((char*)pl.szNickname, sizeof(pl.szNickname));
		bos.write((char*)pl.szFaceURL, sizeof(pl.szFaceURL));
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_TableListUpdate& pl)
	{	
		pl.reset();
		bis >> pl.sUpdateType;
		bis >> pl.sTableID;
		bis >> pl.sLockState;
		bis >> pl.sData1;
		bis >> pl.usPlayerID;
		bis >> pl.sChairID;
		bis >> pl.sGender;
		bis >> pl.sVip;
		bis >> pl.sData2;
		bis >> pl.usGoldScore;

		bis.read((char*)pl.szNickname, sizeof(pl.szNickname));
		bis.read((char*)pl.szFaceURL, sizeof(pl.szFaceURL));

		return bis;
	}
};

enum E_TABLE_UPDATE_TYPE
{
	E_TABLE_UPDATE_TYPE_BEGIN				= 0,
	E_TABLE_UPDATE_TYPE_LOCKED				= 1,	// 上锁
	E_TABLE_UPDATE_TYPE_UNLOCK				= 2,	// 解锁
	E_TABLE_UPDATE_TYPE_USER_SIT			= 3,	// 玩家坐下
	E_TABLE_UPDATE_TYPE_USER_LEAVE			= 4,	// 玩家离开
	E_TABLE_UPDATE_TYPE_USER_MONEY_UPDATE	= 5,	// 玩家金币变更
	E_TABLE_UPDATE_TYPE_END,
};

// 查看房间桌子上玩家信息
struct CMD_GR_TableListUserInfoQuery 
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_USER_INFO_QUERY};

	unsigned short						sTableID;				// 桌上ID
	unsigned short						sChairID;				// 椅子ID
	unsigned int						usData1;				// 保留参数1

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_TableListUserInfoQuery() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_TableListUserInfoQuery& pl)
	{
		bos << pl.sTableID;
		bos << pl.sChairID;
		bos << pl.usData1;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_TableListUserInfoQuery& pl)
	{	
		pl.reset();
		bis >> pl.sTableID;
		bis >> pl.sChairID;
		bis >> pl.usData1;
		return bis;
	}
};

// 查看房间桌子上玩家信息
struct CMD_GR_TableListUserInfoRep 
{
	enum {SUCC = 0, FAIL = 1, NO_PLAYER = 2};
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_USER_INFO_REP};

	unsigned short						sResult;					// 查询结果（0表示成功1失败2座位上没人）
	unsigned short						sData1;						// 保留参数1

	unsigned short						sTableID;					// 桌上ID
	unsigned short						sChairID;					// 椅子ID
	unsigned int						usPlayerID;					// 桌上玩家ID
	unsigned short						sGender;					// 玩家性别
	unsigned short						sVip;						// VIP标识
	unsigned int						usWinCount;					// 胜利盘数
	unsigned int						usLostCount;				// 失败盘数
	unsigned int						usDrawCount;				// 和局盘数
	unsigned int						usFleeCount;				// 断线数目
	unsigned int						usData2;					// 保留参数2

	char								szNickname[NAME_LEN];		// 玩家昵称
	char								szDescribe[128];			// 个性签名
	char								szFaceURL[256];				// 头像

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_TableListUserInfoRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_TableListUserInfoRep& pl)
	{
		bos << pl.sResult;
		bos << pl.sData1;
		bos << pl.sTableID;
		bos << pl.sChairID;
		bos << pl.usPlayerID;
		bos << pl.sGender;
		bos << pl.sVip;
		bos << pl.usWinCount;
		bos << pl.usLostCount;
		bos << pl.usDrawCount;
		bos << pl.usFleeCount;
		bos << pl.usData2;
		bos.write((char*)pl.szNickname, sizeof(pl.szNickname));
		bos.write((char*)pl.szDescribe, sizeof(pl.szDescribe));
		bos.write((char*)pl.szFaceURL, sizeof(pl.szFaceURL));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_TableListUserInfoRep& pl)
	{	
		pl.reset();
		bis >> pl.sResult;
		bis >> pl.sData1;
		bis >> pl.sTableID;
		bis >> pl.sChairID;
		bis >> pl.usPlayerID;
		bis >> pl.sGender;
		bis >> pl.sVip;
		bis >> pl.usWinCount;
		bis >> pl.usLostCount;
		bis >> pl.usDrawCount;
		bis >> pl.usFleeCount;
		bis >> pl.usData2;

		bis.read((char*)pl.szNickname, sizeof(pl.szNickname));
		bis.read((char*)pl.szDescribe, sizeof(pl.szDescribe));
		bis.read((char*)pl.szFaceURL, sizeof(pl.szFaceURL));

		return bis;
	}
};

// 桌子锁设置请求
struct CMD_GR_TableLockReq
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LOCK_REQ};

	unsigned short						sLockState;					// 锁状态（0不锁1锁）
	unsigned short						sData1;						// 保留参数1

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_TableLockReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_TableLockReq& pl)
	{
		bos << pl.sLockState;
		bos << pl.sData1;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_TableLockReq& pl)
	{	
		pl.reset();
		bis >> pl.sLockState;
		bis >> pl.sData1;
		return bis;
	}
};

// 桌子锁设置结果
struct CMD_GR_TableLockRep
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LOCK_REP};

	unsigned short						sResult;					// 操作结果（0成功1失败2不是VIP  3需要2个玩家在桌才可以锁)
	unsigned short						sLockState;					// 锁状态（0不锁1锁）

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_TableLockRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_TableLockRep& pl)
	{
		bos << pl.sResult;
		bos << pl.sLockState;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_TableLockRep& pl)
	{	
		pl.reset();
		bis >> pl.sResult;
		bis >> pl.sLockState;
		return bis;
	}
};

// 桌子锁状态同步
struct CMD_GR_TableLockSyn
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LOCK_STATE_SYN};

	unsigned short						sLockState;					// 锁状态（0不锁1锁）
	unsigned short						sData1;						// 保留参数1

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_TableLockSyn() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_TableLockSyn& pl)
	{
		bos << pl.sLockState;
		bos << pl.sData1;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_TableLockSyn& pl)
	{	
		pl.reset();
		bis >> pl.sLockState;
		bis >> pl.sData1;
		return bis;
	}
};

// 查询喇叭数量
struct CMD_GR_LabaCountQuery 
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_LABA_QUERY};

	unsigned int					dwUserID;				// 玩家ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_LabaCountQuery() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_LabaCountQuery& pl)
	{
		bos << pl.dwUserID;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_LabaCountQuery& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;
		return bis;
	}
};

// 查询喇叭数量返回
struct CMD_GR_LabaCountRep
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_LABA_REP};

	unsigned int					usLabaCount;				// 喇叭数量

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_LabaCountRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_LabaCountRep& pl)
	{
		bos << pl.usLabaCount;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_LabaCountRep& pl)
	{	
		pl.reset();
		bis >> pl.usLabaCount;
		return bis;
	}
};

enum E_TABLE_LOCK_RES
{
	E_TABLE_LOCK_RES_BEGIN			= 0,
	E_TABLE_LOCK_RES_SUCC			= E_TABLE_LOCK_RES_BEGIN,	// 成功
	E_TABLE_LOCK_RES_FAIL			= 1,						// 失败
	E_TABLE_LOCK_RES_NOT_VIP		= 2,						// 不是vip
	E_TABLE_LOCK_RES_NEED_2_PLAYER	= 3,						// 需要2个玩家在桌才可以锁
	E_TABLE_LOCK_RES_END,
};




//////////////////////////////////////////////////////////////////////////
//配置信息数据包

#define MDM_GR_INFO					3									//配置信息

#define SUB_GR_SERVER_INFO			100									//房间配置
#define SUB_GR_ORDER_INFO			101									//等级配置
#define SUB_GR_MEMBER_INFO			102									//会员配置
#define SUB_GR_COLUMN_INFO			103									//列表配置
#define SUB_GR_CONFIG_FINISH		104									//配置完成

//游戏房间信息
struct CMD_GR_ServerInfo
{
	enum {M_ID = MDM_GR_INFO};
	enum {S_ID = SUB_GR_SERVER_INFO};

	//房间属性
	unsigned short							wKindID;							//类型 I D
	unsigned short							wTableCount;						//桌子数目
	unsigned short							wChairCount;						//椅子数目
	unsigned int							dwVideoAddr;						//视频地址

	//扩展配置
	unsigned short							wGameGenre;							//游戏类型
	unsigned char							cbHideUserInfo;						//隐藏信息

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_ServerInfo() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_ServerInfo& pl)
	{
		bos << pl.wKindID;
		bos << pl.wTableCount;
		bos << pl.wChairCount;
		bos << pl.dwVideoAddr;
		bos << pl.wGameGenre;
		bos << pl.cbHideUserInfo;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_ServerInfo& pl)
	{	
		pl.reset();
		bis >> pl.wKindID;
		bis >> pl.wTableCount;
		bis >> pl.wChairCount;
		bis >> pl.dwVideoAddr;
		bis >> pl.wGameGenre;
		bis >> pl.cbHideUserInfo;

		return bis;
	}
};

//分数描述信息
struct CMD_GR_ScoreInfo_CB
{
	unsigned short							wDescribeCount;						//描述数目
	unsigned short							wDataDescribe[16];					//数据标志
};

//等级描述结构
struct tagOrderItem
{
	int							lScore;								//等级积分
	unsigned short							wOrderDescribe[16];					//等级描述

	void reset() { memset(this, 0, sizeof(*this)); }
	tagOrderItem() { reset(); }
	friend bostream& operator<<(bostream& bos,const tagOrderItem& pl)
	{
		bos << pl.lScore;

		bos.write((char*)pl.wOrderDescribe,sizeof(pl.wOrderDescribe));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,tagOrderItem& pl)
	{	
		pl.reset();
		bis >> pl.lScore;

		bis.read((char*)pl.wOrderDescribe,sizeof(pl.wOrderDescribe));

		return bis;
	}
};

//等级描述信息
struct CMD_GR_OrderInfo
{
	enum {M_ID = MDM_GR_INFO};
	enum {S_ID = SUB_GR_ORDER_INFO};

	unsigned short							wOrderCount;						//等级数目
	tagOrderItem					OrderItem[128];						//等级描述

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_OrderInfo() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_OrderInfo& pl)
	{
		bos << pl.wOrderCount;

		bos.write((char*)pl.OrderItem,sizeof(pl.OrderItem));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_OrderInfo& pl)
	{	
		pl.reset();
		bis >> pl.wOrderCount;

		bis.read((char*)pl.OrderItem,sizeof(pl.OrderItem));

		return bis;
	}
};

//列表项描述结构
struct tagColumnItem
{
	unsigned short							wColumnWidth;						//列表宽度
	unsigned short							wDataDescribe;						//字段类型
	char							szColumnName[16];					//列表名字
};

//列表描述信息
struct CMD_GR_ColumnInfo
{
	enum {M_ID = MDM_GR_INFO};
	enum {S_ID = SUB_GR_COLUMN_INFO};

	unsigned short							wColumnCount;						//列表数目
	tagColumnItem					ColumnItem[32];						//列表描述

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_ColumnInfo() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_ColumnInfo& pl)
	{
		bos << pl.wColumnCount;
		for (int i=0; i<pl.wColumnCount ; i++ )
		{
			bos << pl.ColumnItem[i].wColumnWidth;
			bos << pl.ColumnItem[i].wDataDescribe;

			bos.write((char*)pl.ColumnItem[i].szColumnName,16);
		}

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_ColumnInfo& pl)
	{	
		pl.reset();
		bis >> pl.wColumnCount;
		for (int i=0; i<pl.wColumnCount ; i++ )
		{
			bis >> pl.ColumnItem[i].wColumnWidth;
			bis >> pl.ColumnItem[i].wDataDescribe;

			bis.read((char*)pl.ColumnItem[i].szColumnName,16);
		}

		return bis;
	}
};

//////////////////////////////////////////////////////////////////////////
//房间状态数据包

#define MDM_GR_STATUS				4									//状态信息

#define SUB_GR_TABLE_INFO			100									//桌子信息
#define SUB_GR_TABLE_STATUS			101									//桌子状态

//桌子状态结构
struct tagTableStatus
{
	unsigned char							bTableLock;							//锁定状态
	unsigned char							bPlayStatus;						//游戏状态

	void reset() { memset(this, 0, sizeof(*this)); }
	tagTableStatus() { reset(); }
	friend bostream& operator<<(bostream& bos,const tagTableStatus& pl)
	{
		bos << pl.bTableLock;
		bos << pl.bPlayStatus;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,tagTableStatus& pl)
	{	
		pl.reset();
		bis >> pl.bTableLock;
		bis >> pl.bPlayStatus;

		return bis;
	}
};

//桌子状态数组
struct CMD_GR_TableInfo
{
	enum {M_ID = MDM_GR_STATUS};
	enum {S_ID = SUB_GR_TABLE_INFO};

	unsigned short							wTableCount;						//桌子数目
	tagTableStatus					TableStatus[512];					//状态数组

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_TableInfo() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_TableInfo& pl)
	{
		bos << pl.wTableCount;
		for (int i=0; i<pl.wTableCount ; i++ )
		{
			bos << pl.TableStatus[i];
		}

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_TableInfo& pl)
	{	
		pl.reset();
		bis >> pl.wTableCount;
		for (int i=0; i<pl.wTableCount ; i++ )
		{
			bis >> pl.TableStatus[i];
		}

		return bis;
	}
};

//桌子状态信息
struct CMD_GR_TableStatus
{
	enum {M_ID = MDM_GR_STATUS};
	enum {S_ID = SUB_GR_TABLE_STATUS};

	unsigned short							wTableID;							//桌子号码
	unsigned char							bTableLock;							//锁定状态
	unsigned char							bPlayStatus;						//游戏状态

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_TableStatus() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_TableStatus& pl)
	{
		bos << pl.wTableID;
		bos << pl.bTableLock;
		bos << pl.bPlayStatus;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_TableStatus& pl)
	{	
		pl.reset();
		bis >> pl.wTableID;
		bis >> pl.bTableLock;
		bis >> pl.bPlayStatus;

		return bis;
	}
};

//////////////////////////////////////////////////////////////////////////
//管理数据包

#define MDM_GR_MANAGER				5									//管理命令

#define SUB_GR_SEND_WARNING			1									//发送警告
#define SUB_GR_SEND_MESSAGE			2									//发送消息
#define SUB_GR_LOOK_USER_IP			3									//查看地址
#define SUB_GR_KILL_USER			4									//踢出用户
#define SUB_GR_LIMIT_ACCOUNS		5									//禁用帐户
#define SUB_GR_SET_USER_RIGHT		6									//权限设置
#define SUB_GR_OPTION_SERVER		7									//房间设置

//发送警告
struct CMD_GR_SendWarning
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_SEND_WARNING};

	unsigned short							wChatLength;						//信息长度
	unsigned int							dwTargetUserID;						//目标用户
	char							szWarningMessage[MAX_CHAT_LEN];		//警告消息

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_SendWarning() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_SendWarning& pl)
	{
		bos << pl.wChatLength;
		bos << pl.dwTargetUserID;

		bos.write((char*)pl.szWarningMessage,sizeof(pl.szWarningMessage));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_SendWarning& pl)
	{	
		pl.reset();
		bis >> pl.wChatLength;
		bis >> pl.dwTargetUserID;

		bis.read((char*)pl.szWarningMessage,sizeof(pl.szWarningMessage));

		return bis;
	}
};

//系统消息
struct CMD_GR_SendMessage
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_SEND_MESSAGE};

	unsigned char							cbGame;								//游戏消息
	unsigned char							cbRoom;								//游戏消息
	unsigned short							wChatLength;						//信息长度
	char							szSystemMessage[MAX_CHAT_LEN];		//系统消息

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_SendMessage() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_SendMessage& pl)
	{
		bos << pl.cbGame;
		bos << pl.cbRoom;
		bos << pl.wChatLength;

		bos.write((char*)pl.szSystemMessage,sizeof(pl.szSystemMessage));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_SendMessage& pl)
	{	
		pl.reset();
		bis >> pl.cbGame;
		bis >> pl.cbRoom;
		bis >> pl.wChatLength;

		bis.read((char*)pl.szSystemMessage,sizeof(pl.szSystemMessage));

		return bis;
	}
};

//查看地址
struct CMD_GR_LookUserIP
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_LOOK_USER_IP};

	unsigned int							dwTargetUserID;						//目标用户

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_LookUserIP() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_LookUserIP& pl)
	{
		bos << pl.dwTargetUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_LookUserIP& pl)
	{	
		pl.reset();
		bis >> pl.dwTargetUserID;

		return bis;
	}
};

//踢出用户
struct CMD_GR_KillUser
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_KILL_USER};

	unsigned int							dwTargetUserID;						//目标用户

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_KillUser() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_KillUser& pl)
	{
		bos << pl.dwTargetUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_KillUser& pl)
	{	
		pl.reset();
		bis >> pl.dwTargetUserID;

		return bis;
	}
};

//禁用帐户
struct CMD_GR_LimitAccounts
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_LIMIT_ACCOUNS};

	unsigned int							dwTargetUserID;						//目标用户

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_LimitAccounts() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_LimitAccounts& pl)
	{
		bos << pl.dwTargetUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_LimitAccounts& pl)
	{	
		pl.reset();
		bis >> pl.dwTargetUserID;

		return bis;
	}
};

//权限设置
struct CMD_GR_SetUserRight
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_SET_USER_RIGHT};

	//目标用户
	unsigned int							dwTargetUserID;						//目标用户

	//绑定变量
	unsigned char							cbGameRight;						//帐号权限
	unsigned char							cbAccountsRight;					//帐号权限

	//权限变化
	unsigned char							cbLimitRoomChat;					//大厅聊天
	unsigned char							cbLimitGameChat;					//游戏聊天
	unsigned char							cbLimitPlayGame;					//游戏权限
	unsigned char							cbLimitSendWisper;					//发送消息
	unsigned char							cbLimitLookonGame;					//旁观权限

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_SetUserRight() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_SetUserRight& pl)
	{
		bos << pl.dwTargetUserID;
		bos << pl.cbGameRight;
		bos << pl.cbAccountsRight;
		bos << pl.cbLimitRoomChat;
		bos << pl.cbLimitGameChat;
		bos << pl.cbLimitPlayGame;
		bos << pl.cbLimitSendWisper;
		bos << pl.cbLimitLookonGame;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_SetUserRight& pl)
	{	
		pl.reset();
		bis >> pl.dwTargetUserID;
		bis >> pl.cbGameRight;
		bis >> pl.cbAccountsRight;
		bis >> pl.cbLimitRoomChat;
		bis >> pl.cbLimitGameChat;
		bis >> pl.cbLimitPlayGame;
		bis >> pl.cbLimitSendWisper;
		bis >> pl.cbLimitLookonGame;

		return bis;
	}

};

//设置标志
#define OSF_ROOM_CHAT				1									//大厅聊天
#define OSF_GAME_CHAT				2									//游戏聊天
#define OSF_ROOM_WISPER				3									//大厅私聊
#define OSF_ENTER_GAME				4									//进入游戏
#define OSF_ENTER_ROOM				5									//进入房间
#define OSF_SHALL_CLOSE				6									//即将关闭

//房间设置
struct CMD_GR_OptionServer
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_OPTION_SERVER};

	unsigned char							cbOptionFlags;						//设置标志
	unsigned char							cbOptionValue;						//设置标志

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_OptionServer() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_OptionServer& pl)
	{
		bos << pl.cbOptionFlags;
		bos << pl.cbOptionValue;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_OptionServer& pl)
	{	
		pl.reset();
		bis >> pl.cbOptionFlags;
		bis >> pl.cbOptionValue;

		return bis;
	}
};

//////////////////////////////////////////////////////////////////////////
//系统数据包

#define MDM_GR_SYSTEM				10									//系统信息

#define SUB_GR_MESSAGE				100									//系统消息

//消息类型
#define SMT_INFO					0x0001								//信息消息
#define SMT_EJECT					0x0002								//弹出消息
#define SMT_GLOBAL					0x0004								//全局消息
#define SMT_CLOSE_ROOM				0x1000								//关闭房间
#define SMT_SYS_KICK				0x2000								//系统踢人
#define SMT_INTERMIT_LINE			0x4000								//中断连接(目前用于VIP踢人)
#define SMT_ROOM_WEIHU				0x0010								//维护公告
#define SMT_ROOM_MAXSCORE			0x0020									//输赢限制

//消息数据包
struct CMD_GR_Message
{
	enum {M_ID = MDM_GR_SYSTEM};
	enum {S_ID = SUB_GR_MESSAGE};

	unsigned short							wMessageType;						//消息类型
	unsigned short							wMessageLength;						//消息长度
	char							szContent[1024];					//消息内容

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_Message() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GR_Message& pl)
	{
		bos << pl.wMessageType;
		bos << pl.wMessageLength;

		bos.write((char*)pl.szContent,sizeof(pl.szContent));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GR_Message& pl)
	{	
		pl.reset();
		bis >> pl.wMessageType;
		bis >> pl.wMessageLength;

		bis.read((char*)pl.szContent,sizeof(pl.szContent));

		return bis;
	}
};

//////////////////////////////////////////////////////////////////////////
//房间数据包

#define MDM_GR_SERVER_INFO			11									//房间信息

#define SUB_GR_ONLINE_COUNT_INFO	100									//在线信息

//人数信息
struct tagOnLineCountInfo
{
	enum {M_ID = MDM_GR_SERVER_INFO};
	enum {S_ID = SUB_GR_ONLINE_COUNT_INFO};

	unsigned short							wKindID;							//类型标识
	unsigned int							dwOnLineCount;						//在线人数

	void reset() { memset(this, 0, sizeof(*this)); }
	tagOnLineCountInfo() { reset(); }
	friend bostream& operator<<(bostream& bos,const tagOnLineCountInfo& pl)
	{
		bos << pl.wKindID;
		bos << pl.dwOnLineCount;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,tagOnLineCountInfo& pl)
	{	
		pl.reset();
		bis >> pl.wKindID;
		bis >> pl.dwOnLineCount;

		return bis;
	}
};

//////////////////////////////////////////////////////////////////////////

#endif