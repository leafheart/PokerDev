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

// ��Ϸ״̬
typedef enum tagGameState
{
	gsNull = 0,
	gsRoarPai,	// ����
	gsPlay,		// ����
}GameState;

//���ѷ��������
struct st_FriendRule{
	int								iLocal;				//�ĸ��ط����淨
	DWORD							dwFangZhuID;		//����ID
	int								iJuShu;				//����
	int								iTypeLaizi;			//�������
	int								iWanFa;				//�淨
	int								iFengDing;			//�ⶥ����
	int								iFentDingStep1;		//�ⶥ�Ļ����ֱ���
	int								iFentDingStep2;		//�ⶥ�Ļ����ֱ���
	int								iFentDingStep3;		//�ⶥ�Ļ����ֱ���
	int								iFentDingStep4;		//�ⶥ�Ļ����ֱ���
	int								iMinFan;			//��С����
	bool							bKouKou;			//�Ƿ�ڿڷ�
	bool							b7Dui;				//�Ƿ��߶�
	bool							bNeedKaiKou;		//�Ƿ���Ҫ����
	int								iBird;				//ץ�����
	int								iBirdFan;			//ץ����㷬��
	bool							bOnlyZimo;			//ֻ������
	bool							bZhuangxian;		//�Ƿ�ׯ��
	bool							bHongZhongLai;		//�Ƿ��������
	bool                            bHongZhongPi;        //�Ƿ�Ϊ����Ƥ��
	int								iZhuangxianFan;		//ׯ��ʱׯ����Ӯ���ӵķ���
	int								iGangFan;			//��ܶ��ٷ�
	bool							bReChonHu;			//�Ƿ�������
	bool							bQiangGangBao;		//���ܺ�ʱ�Ƿ�һ��ȫ������ȫ���Ͱ���ͨ��良���
	bool                            bHongZhongFan;      //�����Ƿ���ź����㷬
	bool							bNoWan;				//�������ƣ������淨ʱ�����Թ�ѡ�Ƿ�ȥ��

	int								iDiFen;				//�׷�
	WORD							wCreateType	;
};


class CGameLogic : public CTableFrameSink
{
	//////////////////////////////////////////////////////////////////////////
	// ����
public:
	CGameLogic(void);
	virtual ~CGameLogic(void);

	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ�ӿ�
	//��ʱ���¼�
	virtual bool __cdecl OnTimerMessage(WORD wTimerID, WPARAM wBindParam);

	//����ж���Ϸ����
	virtual bool __cdecl OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);

	virtual bool __cdecl SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret);
	
	//�û�����
	virtual bool __cdecl OnActionUserOffLine(WORD wChairID, IServerUserItem * pIServerUserItem); 
	//�û�����
	virtual bool __cdecl OnActionUserReConnect(WORD wChairID, IServerUserItem * pIServerUserItem);
	//�û�����
	virtual bool __cdecl OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�����
	virtual bool __cdecl OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�ͬ��
	virtual bool __cdecl OnActionUserReady(WORD wChairID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize);

public:	
	//����������
	void  ProduceCards();
	//˭�����֣���һ��ʱʹ��,����ֵ 1-MAX_PLAYER
	BYTE GetXianShou();
	// ������һ��
	bool StartNextGame();							
	// ��Ϸ��ʼ
	void OnStartGame();	
	void OnGameAction(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
	
	//����
	void SetDebugCard(const string &_file);
	int	 getCardIndexByOx(BYTE _card);

	// �������״̬������,�˺�����������á�
	void Reset();
	void InitGame();
	long GetCPUTickCount( void );

public:
	/*һЩֽ����Ϸ���еķ���������*/
	enum ActionStep		// ��Ϸ����
	{//�޸Ĳ���
		AS_NULL = 0,
		AS_GAMESTART ,  //���ſ���ʱ���ƶ���
		AS_ROAR,		// Ӳ��
		AS_ENDROAR,		// ����Ӳ��
		AS_PLAY,		// ����
		AS_ENDPLAY,		// ���ƽ���
		AS_ENDGAME,		// ������Ϸ
		AS_COUNT
	};
	enum GameOverType
	{
		GOT_NULL = 0,
		GOT_ESCAPE,		//�������ܣ���Ϸ����
		GOT_NORMAL,		//�����Ľ�����Ϸ�������������ѵ�ģʽ�£��������꣬�ں���ģʽ�£�һ������
		GOT_ZHONGTU,    //��;������Ϸ��������һ������������������Ϸ
		GOT_DOUBLEKILL,	//���󡱣���Ϊ˫ɱ���������ѵ�ģʽ�£�һ��Ϊһ�κͶ�������
		GOT_TUOGUAN, // ÿ���йܴ�������Ϊ5��
		GOT_DISMISS,//��ɢ
	};

	GameState	m_GameState;			// ��Ϸ״̬//��Ϸ���ж���׶�ʱ��Ҫʹ�����������
	int			m_tDownTime;			// Ȩ��ֹͣʱ��
	int			m_tPowerStartTime;		// Ȩ�޿�ʼʱ��
	ActionStep	m_theActionStep;		// ����ʱ
	ActionStep	m_nowActionStep;	

	//һЩ���е���Ϸ����

	BYTE		m_byIsShowChardCount;   // �Ƿ���ʾ������Ŀ
	BYTE		m_byMaxKingNum;         // ����Ŀ��4����8��
	BYTE		m_byFakeKingValue;		// �������㼸��2��3
	BYTE		m_whoplay;              // ��ǰ���	1--MAXPLAYER
	BYTE		m_whoplayout;			// ��һ�����
	BYTE		m_banker;				// ׯ��
	BYTE		m_nextbanker;			// ��һ��ׯ��

	BYTE		m_whoMakeCards;			//˭����			

	//�й�����
	BYTE        m_TuoGuanPlayer[MAX_PLAYER];	  // ˭�й��ˣ�
	BYTE		m_TrustCounts[MAX_PLAYER];		  // �йܴ���
	int			m_nTrustCounts;					// �����йܵĴ���
	//��������
	BYTE        m_whoBreak[MAX_PLAYER];			  // ˭�����ˣ�
	int			m_WireBreakCounts[MAX_PLAYER];	  // ���ߴ���
	int			m_nWireBreakTimes;				// ������������Ĵ���

	//������
	BYTE		m_cbLeftCardCount;						//ʣ����Ŀ
	BYTE		m_tempdbp[ALLCARD];				  // ������ ��������
	BYTE		m_dbp[ALLCARD];					  // ������
	BYTE		m_dbplay[MAX_PLAYER][MAXCARD];    // �ֵ�����

	BYTE        m_allPaiOut[MAX_PLAYER][MAXCARD]; // ������,���������ӵ�
	BYTE        m_allPaiOutNoMagic[MAX_PLAYER][MAXCARD]; // ������,�����Ѿ�����滻ֵ��
	TFakeKing	m_OutPaifakeking[MAX_PLAYER][8];  //�������е������滻ֵ��Ϣ
	BYTE        m_lastPaiOut[MAX_PLAYER][MAXCARD];// ��һ�ֳ�����
	BYTE		m_thePaiCount[MAX_PLAYER];		  // ����
	BYTE		m_theCanNotOut[MAX_PLAYER];		  // �Ƿ����˲��ܳ��ƣ�����ֻʣһ������

	//���ӣ���������
	int			m_lastScore[MAX_PLAYER];		  // ��һ����Ӯ
	int			m_total[MAX_PLAYER];			  // ����Ӯ
	long		m_playerrich[MAX_PLAYER];		  // ��ҵĲƸ�
	int			m_iCurrentFanShu;				//��ǰ����
	//һЩ���еĹ���
	int			m_nAutoOutTime;					// �Զ�����ʱ�䣬�йܵ�ʱ�����ʱ��
	int			m_nTimeStart;					// ����֮�󣬰���ʼ�ĵȴ�ʱ��
	int			m_nPlayTime;					// ����ʱ��
	int			m_nSerPay;						// ��ˮ��ǧ�ֱ�

	time_t	    nowTime; 

	// ���ö���������ָ������
	void		SetActionStep(ActionStep as,unsigned long nSecond=0);  

	// ��������ָ������,
	void		OnActionStep(ActionStep as);

public://�Լ���ӵ�
	int			m_iBaseScore;				// �׷֣�ͨ���ͻ��˽������õĵ׷�
	long		m_nBase;					// ��

	CDaGun		m_dagun;

	int			m_score;					// ÿһ���Ƶķ�
	int			m_playerscore[MAX_PLAYER];	// ÿ�������ķ������п���û�����Ҳ�ӽ�ȥ��

	int			m_xiScore[MAX_PLAYER];//ϲǮ
	long		m_spay;						// �����

	BYTE		m_whoPass[MAX_PLAYER];			// ˭������
	BYTE        m_whoAllOutted[MAX_PLAYER];     // ˭�����ˣ�
	BYTE		m_thePlayerState[MAX_PLAYER];			// �û�״̬���Ƿ�������Ϸ��
	bool		m_bUserReady[MAX_PLAYER];			//��һ��׼���õ��û������׼���õ��û���

	int			m_whoTotal8Xi[MAX_PLAYER];		// ÿ���˴�ֵ�8ϲ����
	int			m_whoTotal7Xi[MAX_PLAYER];		// ÿ���˴�ֵ�7ϲ����
	int			m_whoTotalGonglong[MAX_PLAYER];	// ÿ���˴�ֵ���ը������(���)

	int			m_whoHasKingBomb;				// ˭����ը
	int			m_lastOutType;					// �����Ƶ�����
	BYTE		m_bBaoPei;						//������ң�1-MAX_PLAYER,0��ʾ���ð���

	int			m_playHardBomb[MAX_PLAYER];		// �����Ӳը��û������
	int			m_playSoftBomb[MAX_PLAYER];			// �������ը��������
	int         m_playMagicBomb[MAX_PLAYER];			// ����ը��
	int         m_whoHardKill;			// Ӳɱ
	int         m_whoQuanGuan[MAX_PLAYER];			// ȫ��
	BYTE		m_byEveryOneOutCnt[MAX_PLAYER];//ÿ���˵ĳ��ƴ���
	BYTE		m_byEveryOneCurlunOutCnt[MAX_PLAYER];//ÿ���˵�ǰ�ֵĳ��ƴ���

	int			m_MaxScore[MAX_PLAYER];			//���ץ��
	int			m_totalFirstTurn[MAX_PLAYER];	//һ�δ���
	int			m_totalDuPai[MAX_PLAYER];		//���ƴ���

	int			m_iFaOfTao;				//���ܵĳͷ�����
	int			m_iJiangOfTao;			//���ܵĲ�������
	int			m_iAddSpecailBeishu;	//�����������ƽ���ʱ����Ҫ�۳��ֵı���
	BYTE		m_byAddSepcialFlag;		//���������Ƿ�ӷ�

	int			m_iRandomTask;						//�������,�±�
	vector<int>	m_vecAllTaskID;	//���е�����ID
	map<int,int>	m_mapAllTask;	//��������: ID-������
	vector<int>	m_vecFinishedTask[MAX_PLAYER];		//��ɵ�����
	bool		m_bHaveOutCard;		//�Ƿ��Ѿ�������
	
	st_FriendRule	m_rule;

	vector<CMD_S_EndGame_CB>			m_vecGameEnd;							//��¼ÿһ�ֵĽ��

	BYTE							m_cbGameEndStatus;					//��ǰС����Ϸ��״̬
	int								m_CurCompleteCount;				// ��ǰ��һ������˼���		

	CString							m_szTimeGameRecord;                 //��¼��ǰ��־������
	CString							m_szNameGameRecord;                 //��¼�ļ���
public:
	//д����Ϸ��¼
	void		OnWriteGameRecord(unsigned int _seat, CString szGameRecord, const bool bStatus = true);

	//������Ϸ��¼Ŀ¼
	void		CreateGameRecordFile(const bool bStatus = false);
	CString		getWriteReplayRecordCString(BYTE recordType);	//�طż�¼��������
	void		ParseRule(const string& strRule);//�������
	void		CalculateResultTotal(BYTE cbReason, bool bSendData = true);

	void		GoNextPlayer();
	void		StartPlay(BYTE whoplay);		// ��ʼ��
	int			AutoOutCard(BYTE theSeat,nsRouAiRou::CMD_OutCard_CB& msgout);	//���ƶ���

	void		GameOver(BYTE winner,GameOverType type);

	//�޸�����ĺ�����ʵ���Զ��й�
	int			AutoTuoGuan(BYTE theSeat);
	//�йܳ���
	void		TuoGuanOutCard();

	bool EndTurn();// ����һ��
	void EndOut();
	void SendPai();//����
	void AddSpecailScore(long Score[MAX_PLAYER],int seat,int base);
	void GetFinalWinLoseScore( long long score[MAX_PLAYER] );
	void SendPower(BYTE whoplay,DWORD aPower,DWORD dwWaitTime = 0);	// ����Ȩ��
	void SendPlaySoundMsg(BYTE seat,BYTE type,BYTE flag = 1);						// ���Ͳ������ֵ���Ϣ

	void SendTurnScore(int wChairID = INVALID_CHAIR);				// ����ÿ�ֵķ���
	void SendPlayerScore(int wChairID = INVALID_CHAIR, int _ichair =INVALID_CHAIR, int _score =0);				// ����ÿ���˵ķ���
	void SendPaiCount(int wChairID = INVALID_CHAIR);				// ��������
	void SendFanShu(int wChairID = INVALID_CHAIR);						//����ʵʱ����
	void sendGameStatus(WORD wChair ,bool isReLink, IServerUserItem * pIServerUserItem);

	BOOL IsGamePlaying();
	BYTE IsBaoPei(BYTE followCard[MAXPAI],BYTE outLen = 0);//�ж��Ƿ���⣬����ֵ1-MAX_PLAYRE ,0��ʾ������
	BOOL IsSamePlayerOneCard(BYTE byWho);//�Ƿ������ֻ��һ����,�Լ�����

	void UpdateOtherFriendDate(CMD_S_EndGame_CB& GameEnd, bool bEnd = false);//�����˿�����VIP����������ݴ���

	void ParseTaskConfig(const string& strTaskID);	//�������õ�����
	void SendTaskID (bool bFirst, BYTE nSeat = -1); //�����������
	void IsTaskFinished(const TCardType& re1, int iSeat, int iNumOfKing);  //�ж������Ƿ����
	void IsTaskFinishedOfLastHand(const TCardType& re1, int iSeat, int iNumOfKing);  //�ж����һ�ֵ������Ƿ����
	void SendFinishTask (int iSeat, int id, int cnt = 1, bool bToAll = true); //��������˵�����
	int GetTaskAward(int iSeat); //��ȡ������
	string GetTaskAwardDetails(int iSeat);	//��ȡ������ϸ
};

}; //end of namespace
#endif//__GAMELOGIC_H__

