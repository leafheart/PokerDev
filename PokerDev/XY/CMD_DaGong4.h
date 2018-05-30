#ifndef CMD_HSDAGUN_HEAD_FILE
#define CMD_HSDAGUN_HEAD_FILE

#include "biostream.h"

namespace nsRouAiRou
{
//////////////////////////////////////////////////////////////////////////
//�����궨��

#define KIND_ID							935								//��Ϸ I D
#define GAME_PLAYER						5									//��Ϸ����
#define GAME_NAME						TEXT("��ұ�Ⱔ��")					//��Ϸ����
#define GAME_GENRE						(GAME_GENRE_GOLD|GAME_GENRE_MATCH)	//��Ϸ����

///////////////////////////////////
	//��Ϸ״̬
#define GS_MJ_FREE					GS_FREE								//����״̬
#define GS_MJ_PLAY					(GS_PLAYING+1)						//��Ϸ״̬
#define GS_MJ_HAI_DI				(GS_PLAYING+2)						//����״̬
#define GS_MJ_END					(GS_PLAYING+3)						//����״̬

//���״̬
#define OX_GS_NULL		0	//û��
#define OX_GS_SITDOWN	1	//�������
#define OX_GS_READY		2	//���ͬ�⣨׼����
#define OX_GS_PLAYING	3	//�������Ϸ��
	
///////////////////////////////////
#define ALLCARD							54
#define MAXCARD							27
#define FIRSTCARD						5
#define MAX_PLAYER						GAME_PLAYER					
//////////////////////////////////////////////////////////////////////////
//����������ṹ
#define SUB_S_GAME_START				100									//��Ϸ��ʼ
#define SUB_S_TIMER_START				101									//��ʼ����ʱ
#define SUB_S_POWER						102									//Ȩ��
#define SUB_S_SEND_POKER_OX				103									//�����˿�
#define SUB_S_GAME_STATE_OX				104									//��Ϸ״̬(���������״̬������Թ���)
#define SUB_S_ENDROAR					105									//��������
#define SUB_S_RELINK					106									//����
#define SUB_S_ENDOUT					107									//����һ��
#define SUB_S_TEAMERPAI					108									//���Ͷ��ѵ���
#define SUB_S_PLAYERSCORE				109									//����ÿ���˵õķ���
#define SUB_S_SENDCOUNT					110									//��������
#define SUB_S_TURNSCORE					111									//���;ַ�
#define SUB_S_SENDTURN					112									//����˳��
#define SUB_S_ENDGAME					113									//��Ϸ����
#define SUB_S_SHOW						114									//��ʾ�е��ƻ���������Ϣ

#define SUB_CS_OUT						115									//����
#define SUB_CS_ROAR						116									//����
#define SUB_S_TUOGUAN					117									//�й�
#define SUB_CS_PLAYSOUND				118									//��������
#define SUB_CS_TEAMERPAI				119									//���ѵ���
#define SUB_CS_GAMERULE					120									//����
#define SUB_C_RELINK_TIP				121									//����������ʾ����ʾ����������

#define SUB_CS_RAND_TASK_ID				122									//��Ϸ�������
#define SUB_CS_RAND_FINISHED_TASK		123									//��Ϸ����������

#define SUB_S_GAME_BALANCE_GAME			127									// �ܽ���

#define SUB_C_GOON_NEXT_GAME			128									//��һ��
#define SUB_S_SENDGLONGCOUNT			129									//���͹���������
#define SUB_S_FANSHU					130								//��ʾ�е��ƻ���������Ϣ

struct CMD_C_GoOnNextGame   // һ����ɺ�������һ��
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

//��Ϸ״̬
struct CMD_S_StatusFree
{
	unsigned char					cbStatus;							//��ǰ״̬
	int								lCellMinScore;						//��С��ע
	int								lCellMaxScore;						//�����ע
};


//��Ϸ״̬
struct CMD_S_StatusPlay
{
	unsigned char					cbStatus;							//��ǰ״̬
	int								lCellMinScore;						//��С��ע
	int								lCellMaxScore;						//�����ע
	//��־����
	//unsigned char								bShowHand[GAME_PLAYER];				//�����־
	//unsigned char								bAddScore;							//��ע��־

	//��ע��Ϣ
	int								lCellScore;							//��Ԫ��ע
	int								lTurnMaxScore;						//�����ע
	int								lTurnLessScore;						//��С��ע
//	int								lCellMaxScore;						//�����ע
	int								lAddLessScore;						//����Сע
	int								lTableScore[GAME_PLAYER];			//��ע��Ŀ
	int								lTotalScore[GAME_PLAYER];			//�ۼ���ע
	int								lCenterScore;						//���ĳ���

	//״̬��Ϣ
	unsigned short					wDUser;								//D���
	unsigned short				 	wCurrentUser;						//��ǰ���
	unsigned char					cbPlayStatus[GAME_PLAYER];			//��Ϸ״̬
	unsigned char					cbBalanceCount;						//ƽ�����

	//�˿���Ϣ
//	unsigned char					cbCenterCardData[MAX_CENTERCOUNT];	//�˿���Ŀ
	unsigned char					cbHandCardData[MAXCARD];			//�����˿�
};

//�����˿�
struct CMD_S_GameStart_CB
{
	enum {S_ID = SUB_S_GAME_START};
	//theType,֮ǰû���õ�����������һ��ö��
	enum {GAME_START,GAME_RELINK};

	unsigned char		theIsGameStart;
	unsigned char		theBanker;					// ׯ��
	unsigned char		theType;					// ����(��ʼ��Ϸ����������
	unsigned char		theSeat;					// ˭����
	unsigned char		theLeftCardsCount;			// ����ʣ������
	unsigned char		theCount;					// ����
	unsigned char		theCards[MAXCARD];			// ������

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

// Ȩ��
struct CMD_S_Power_CB
{
	enum { XY_ID = SUB_S_POWER };

	enum tagPower
	{
		p_Null   = 0x00,
		p_Roar	 = 0x01,
		p_Out	 = 0x02,		// ����Ȩ��
	};

	unsigned char		theWhoPlay;		// ˭��Ȩ��
	unsigned int		theDownTime;	// ��ʱ��ʱ�䣨��λ�룩
	unsigned int		thePower;		// ʲôȨ��

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

// ��������
struct CMD_S_EndRoar_CB
{
	enum { XY_ID = SUB_S_ENDROAR };

	unsigned char		theWhoRoar; // 1-4,0��ʾû�к���
	unsigned char       theBanker;	// ׯ��
	unsigned char		thePai;		// ����

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

// ��Ϸ����_�����ϲǮ
struct CMD_S_EndGame_CB
{
	enum {XY_ID = SUB_S_ENDGAME}; 
	enum{
		GT_NULL,
		GT_NORMAL,		// ��������
		GT_ESCAPE,		// ��������
		GT_DISMISS,		// ��ɢ
	};

	enum tagGongType
	{
		g_Null		= 0x00,		//��Ч����
		g_Normal	= 0x01,		// ����
		g_BaoPei	= 0x02,		// ����
	};

	unsigned char	theEndType;	    // ��Ϸģʽ	�����ơ�������
	unsigned char	theWhoKingBomb; // ˭����ը?
	int				theFan[MAX_PLAYER];			// ���ٷ�
	unsigned char	theGongType;	// ʲô���ͽ����ģ������幰���ɱ�,��ֵ��ο�enum tagGongType

	unsigned char	byLeftCardsCount[MAX_PLAYER];//������Ŀ
	unsigned char	theLeftPai[MAX_PLAYER][MAXCARD];//ʣ����
	unsigned char	theWinLose[MAX_PLAYER];			// �仹��Ӯ��0�䣬1Ӯ��2ƽ��
	unsigned char	theHardBomb[MAX_PLAYER];		// ÿ�����Ӳը������ ��ʱû��ʹ��
	unsigned char	theSoftBomb[MAX_PLAYER];		// ÿ�������ը������ ��ʱû��ʹ��
	unsigned char	theMagicBomb[MAX_PLAYER];		// ÿ���������ը������    ��ʱû��ʹ��
	unsigned char	theQuanGuan[MAX_PLAYER];		// �Ƿ�ȫ�أ�1��ʾ��ȫ���� 
	long long		theScore[MAX_PLAYER];			// �÷�
	int				theTotalScore[MAX_PLAYER];		// ֮ǰ�����оֵ��ܻ��֣��������ڵ�3�֣��������1��2�ֵĻ��ֺ�

	unsigned char	theToTalHardBomb;		//��Ӳը������
	unsigned char	theToTalSoftBomb;		// ����ը������
	unsigned char	theToTalMagicBomb;		// ������ը������   
	unsigned char	theToTalKingBomb;		// �ܵ���ը���� 
	unsigned char	theWhoHardKill;					// ˭Ӳɱ  

	unsigned char	cbTheOrder; //�ڼ���
	unsigned char	cbEndStatus;						//��ʾ�����ֽ�����ʽ��0���� 1��Ϸ��ɢ 2���ǿ��
	unsigned char	cbType;//1Ϊ��������

	unsigned short	theBank;//ׯ��
	unsigned short	theWhoEscape;//˭���ܣ����Ӻżӹ�1��
	unsigned short	theWhoBaoPei;//˭���⣬���Ӻżӹ�1��

	unsigned int	getScore[MAX_PLAYER];//����ץ��
	int				xiScore[MAX_PLAYER];//ϲǮ
	unsigned char	addSpecialFlag;		//�Ƿ��������ͼӷ�
	int				iHandScore[MAX_PLAYER];//�ַ�
	
	int				iParaEXT;				//��չ����(Ԥ��)
	int				iszParaEXT[MAX_PLAYER];//��չ����2(Ԥ��)

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

// �����������ͻ��� �ܽ���
struct CMD_S_BALANCE_GAME
{
	enum {XY_ID = SUB_S_GAME_BALANCE_GAME};

	unsigned int							userid;										//userid����
	int										lGameScore[MAX_PLAYER];						//��Ϸ����
	
	unsigned short							wChiHuUserCount[MAX_PLAYER];				//��������(Ԥ���ֶ�)

	unsigned short							wMaxGetScore[MAX_PLAYER];					//���ץ��
	unsigned short							wFirstTurnCount[MAX_PLAYER];				//һ�δ���
	unsigned short							wRoarCount[MAX_PLAYER];						//���ƴ���
	unsigned short							w7XiCount[MAX_PLAYER];						//7ϲ����
	unsigned short							w8XiCount[MAX_PLAYER];						//8ϲ����
	unsigned short							wLongZhaCount[MAX_PLAYER];					//��ը����

	unsigned short							wZMHuUserCount[MAX_PLAYER];					//����(Ԥ���ֶ�)
	unsigned short							wJPHuUserCount[MAX_PLAYER];					//����(Ԥ���ֶ�)
	unsigned short							wMGangUserCount[MAX_PLAYER];				//����(Ԥ���ֶ�)
	unsigned short							wAGangUserCount[MAX_PLAYER];				//����(Ԥ���ֶ�)

	unsigned char							curTotalCount;								//��ǰ�ܾ��� 
	unsigned char							cbTheCost;//���˶��پֵķ���

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


// Ȩ��
struct CMD_S_Show_CB
{
	enum { XY_ID = SUB_S_SHOW };

	enum{
		F_NULL,
		F_JIAOPAI,				// ����
		F_MINGJI,				// ����
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

// ����һ��
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
//�ͻ�������ṹ


// ����
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
	unsigned char        index;		//ԭ����ֵ
	unsigned char		fakeindex;	//���ֵ	

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

//����
struct CMD_OutCard_CB
{
	enum {S_ID = SUB_CS_OUT};

	unsigned char		theSeat;					// ˭������
	unsigned char		theCount;					// ����
	unsigned short		theNoSound;					// �Ƿ��ֹ�����������
	// add 2010-01-06,����֮����Ҫ�Ӹ����ͣ�����Ϊ���������棬�ܿ����Ƕ������ͣ������жϣ��ǲ��ɿ���
	// ����A����334455,B����44������5��C�޷��ж�B�ߵ���444555�أ�����445566��Ĭ���ǰ���ʶ��Ϊ444555,�����bug
	unsigned char		thePaiType; 
	unsigned char		thePai[MAXCARD];		// �˿�
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

// �й�
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
	unsigned char theFlag;		// �йܱ�־
	unsigned int theTime;	// ��ʱ��ʱ�䣨��λ�룩

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

// ��������
struct CMD_CS_msgPlaySound_CB
{
	enum{XY_ID = SUB_CS_PLAYSOUND};
	enum
	{
		TY_KING_BEEP = 1,		//����ը����ʾ
		TY_8Xi_BEEP,
		TY_7Xi_BEEP,
		TY_JieFeng,				//�ӷ�
		TY_ChaDi,				//���
	};
	unsigned char thePaiType;
	unsigned char theSeat[MAX_PLAYER];
	unsigned char theFlag;		//Ϊ1ʱ����������0ʱ�ر�
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

//ʵʱ����
struct CMD_CS_FanShu_CB
{
	enum { XY_ID = SUB_S_FANSHU };

	int theCurFanShu; //ʵʱ����

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

//���ַ�
struct CMD_CS_TurnScore_CB
{
	enum { XY_ID = SUB_S_TURNSCORE };

	int theScore; //ץ��

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

	int getScore; //ץ��
	unsigned int iChair;//���
	int theScore[MAX_PLAYER]; //ץ��

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

//�����˿�
struct CMD_S_SendPoker_OX
{
	enum {XY_ID = SUB_S_SEND_POKER_OX};

	unsigned char		thelunshu;						// ���ƴ���
	unsigned char		theSeat;						// ˭����, ��ʱû��ʹ�ã�1--MAX_PLAYER
	unsigned char		theType;						// ����
	unsigned char		theLeftCardsCount;				// ����ʣ������Ŀ
	unsigned char		theXianshou;					// ����,��������ʼ����,1--MAX_PLAYER 
	bool				theIsKanpai;					// �Ƿ��ǿ��ƽ׶η��ƣ�1��ʾ�ǿ��ƣ�0��ʾ��ͨ����
	unsigned char		theCardsCount[MAX_PLAYER];					// ������Ŀ
	unsigned char		theCards[MAX_PLAYER][FIRSTCARD];			// �����ݣ�ÿ����෢�������ƣ�Ŀǰû��ÿ��ֻ��һ����

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

	bool isFirst;//��������������ٷ�һ���ⶫ��������Ϊfalse
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
	int bPlaySR;			// �Ƿ��ǲƸ���Ϸ
	int theGiveGift;		// �Ƿ�����콱
	int theMakePai;		// �Ƿ�����
	unsigned char nTrustCounts;		// �����йܵĴ���	
	unsigned char theSpecial;		// 0����ͨ��1����
	int theBase;			// ��
	int theSeverCharge;			// ��ˮ
	int	theMinGameScore;	// ���뷿����С�Ļ��ֶ���
	int	theMaxGameScore;	// ���뷿�����Ļ��ֶ���
	int iFaOfTao ;			//���ܴ�������	
	int iJiangOfTao ;		//�������ܽ�������ı���			
	int isShowChardCount; // �Ƿ���ʾ��������
	int iFakeKingValue; // �������㼸��2��3
	int iMaxKingNum;	// ��������4��8

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
		GSTATE_SITDOWN,	//����
		GSTATE_READY,	//׼��
		GSTATE_PLAYING	//��Ϸ��
	};

	unsigned char theGameState;
	unsigned char theBanker; // ׯ��
	unsigned char theBeiShu[MAX_PLAYER]; //��ұ���
	unsigned char thePlayerState[MAX_PLAYER];//���״̬
	unsigned char theWhoBreak[MAX_PLAYER];// ˭������
	unsigned char theTuoGuan[MAX_PLAYER]; // ˭�й��ˣ�
	unsigned char		thePass[MAX_PLAYER];	// ˭�����ˣ�
	unsigned char       theLastOutCard[MAX_PLAYER][MAXCARD];//��һ�γ�����
	unsigned char		theOutCard[MAX_PLAYER][MAXCARD];// ������
	TFakeKing			theOutPaifakeking[MAX_PLAYER][8];  //�������е������滻ֵ��Ϣ
	unsigned char		thePaiCount[MAX_PLAYER];		  // ����
	unsigned char       theWhoPlayOut;			// ��һ��˭������
	unsigned char		theLeftTime;			// ʣ��ʱ��
	unsigned char		theWhoPlay;				// ��ǰ��
	int					theLastPaiType;			// �����Ƶ�����
	unsigned char		theLeftCardCount;		// ����ʣ������
	int					theFanShu;				// ��ǰ����

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
	unsigned short      theChair;                 //��ҵ���λ�ţ����ڳ�ʼ����λ�ţ���Ȼת��Ϊlocation�������
	unsigned char	    theGameState;			// ��Ϸ״̬(GameState)
	unsigned char		theBanker;				// ׯ��
	unsigned char		theLeftTime;			// ʣ��ʱ��
	unsigned char		theWhoPlay;				// ��ǰ��
	unsigned char       theWhoPlayOut;			// ��һ��˭������
	unsigned char		theTGTime;			    // �Ѿ��йܵĴ���

	unsigned char		thePass[MAX_PLAYER];	// ˭�����ˣ�
	unsigned char        theWhoBreak[MAX_PLAYER];// ˭������
	unsigned char        theTuoGuan[MAX_PLAYER]; // ˭�й��ˣ�
	unsigned char        theLastOutCard[MAX_PLAYER][MAXCARD];//��һ�γ�����
	unsigned char		theOutCard[MAX_PLAYER][MAXCARD];// ������
	TFakeKing			theOutPaifakeking[MAX_PLAYER][8];  //�������е������滻ֵ��Ϣ
	unsigned char		theCards[MAXCARD];			// �Լ���������
	unsigned char		thePaiCount[MAX_PLAYER];		  // ����
	bool				theWhoReady[MAX_PLAYER];// ˭�Ѿ�����˽��ƹ���
	int					theLast[MAX_PLAYER];	// ��һ��
	int					theTotal[MAX_PLAYER];	// ����Ӯ
	int					theTurnScore;			// ���ַ�
	unsigned char	    Score[MAX_PLAYER];      //ÿ����ҵĵ÷�
	int					theLastPaiType;			// �����Ƶ�����
	unsigned char		theLeftCardCount;		// ����ʣ������
	int					theFanShu;				// ��ǰ����
	unsigned char		cbTheOrder;				//��ǰ����
	
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

//��ʾ������ң����ֻ����ˣ�
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

//����ѡ�е���Ϸ����
struct CMD_CS_msgTaskID
{
	enum { XY_ID = SUB_CS_RAND_TASK_ID};
	unsigned char		theID;
	int					theAward;	//������
	
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

//��Ϸ�������״̬
struct CMD_CS_msgFinishedTaskID
{
	enum { XY_ID = SUB_CS_RAND_FINISHED_TASK};
	unsigned char	theSeat;		//˭
	unsigned char	theID;			//������ĸ�����
	unsigned char	theFlag;		//��־λ��Ŀǰ��1����־���������͵�
	int				theCnt;			//����˼���
	int				theTotal;		//��������

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

