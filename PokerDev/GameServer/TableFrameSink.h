#ifndef TABLE_FRAME_SINK_HEAD_FILE
#define TABLE_FRAME_SINK_HEAD_FILE

#pragma once


#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

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
	E_HuoPai,			//����
	E_EndHouPai,		//��������
	E_OutCard,			//����
	E_SendCard,			//����
	E_EndGame,			//������Ϸ
	E_GameJieSan,		//��Ϸ��ɢ
	E_TurnOver,			//���ֽ���
}Replay_Operation;

typedef enum _Replay_Ext_Type
{
	E_Ext_HouPai,		//����
	E_Ext_MingJi,		//����
	E_Ext_TurnScore,	//���ַ�
	E_Ext_GetScore,		//ץ��
	E_Ext_GLongShu,		//����
	E_Ext_PaiXing,		//����
}Replay_Ext_Type;

struct Replay_Order_Ext
{
	Replay_Ext_Type		ext_type;		//��������
	int					ext_value;		//����ֵ
};

struct Replay_Order
{
	unsigned short				chair_id;
	Replay_Operation			operation;
	vector<BYTE>				value;
	vector<Replay_Order_Ext>	vecOrderExt;	//�ò����Ķ�������

	void reset() 
	{ 
		memset(this, 0, sizeof(*this)); 
	}
	Replay_Order() { reset(); }
};

struct Replay_Record
{
	vector<BYTE>					vecHandCard[MAX_PLAYER];					//�û�������ϵ���
	vector<Replay_Order>			vecOrder;									//�û�����
	BYTE							cbBigHuKind;								//��Ǵ������
	WORD							wProvideUser;								//�����û�
	BYTE							cbPiziCard;
	int								iScore[MAX_PLAYER];							//��Ϸ����

	void reset()
	{
		memset((void*)iScore, 0, sizeof(iScore));
		for (int i = 0; i < MAX_PLAYER; i++)
		{
			vecHandCard[i].clear();
		}
		vecOrder.clear();
		cbBigHuKind = 2;	//0������ʾ��һɫ��
		wProvideUser = 9;
		cbPiziCard = 0;
	}
	Replay_Record() { reset(); }
};

//��Ϸ������
class CTableFrameSink : public ITableFrameSink, public ITableUserAction
{

	//��ұ���
protected:
	WORD							m_wDUser;								//D���
	WORD							m_wCurrentUser;							//��ǰ���
	Replay_Record					m_sReplayRecord;						//�طż�¼

	//���״̬
protected:
	BYTE							m_cbPlayStatus[GAME_PLAYER];			//��Ϸ״̬

	//�������
protected:
//	CGameLogic						m_GameLogic;							//��Ϸ�߼�
	ITableFrame						* m_pITableFrame;						//��ܽӿ�
	const tagGameServiceOption		* m_pGameServiceOption;					//���ò���

	//���Ա���
protected:
	static const WORD				m_wPlayerCount;							//��Ϸ����
	static const enStartMode		m_GameStartMode;						//��ʼģʽ

protected:
	//������Ϸ��¼Ŀ¼
	virtual void CreateGameRecordFile(const bool bStatus = false){};

	virtual void OnStartGame() {};
	virtual void OnGameAction(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize,IServerUserItem * pIServerUserItem) {};

	bool SendTableData(WORD wChairID, WORD wSubCmdID, void * pData, WORD wDataSize);
	bool SendTableDataToAll(WORD wSubCmdID, void * pData, WORD wDataSize);
	void SendTableDataToOther(WORD wChairID, WORD wSubCmdID, void * pData, WORD wDataSize);

	IServerUserItem * GetServerUserItem(WORD wChairID);

	void stovs( const string& s, const string& sp, vector<string>& sa );
	//��������
public:
	//���캯��
	CTableFrameSink();
	//��������
	virtual ~CTableFrameSink();

	//�����ӿ�
	//WORD GetPlayerCount() { return m_pITableFrame->GetGameServiceOption()->wPlayerCount; }
	WORD GetPlayerCount() { return MAX_PLAYER; }
public:
	//�ͷŶ���
	virtual VOID __cdecl Release() { }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CTableFrameSink))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//����ӿ�
public:
	//��ʼ��
	virtual bool __cdecl InitTableFrameSink(IUnknownEx * pIUnknownEx);
	//��λ����
	virtual void __cdecl RepositTableFrameSink();

	//��Ϣ�ӿ�
public:
	//��ʼģʽ
	virtual enStartMode __cdecl GetGameStartMode();
	//��Ϸ״̬
	virtual bool __cdecl IsUserPlaying(WORD wChairID);

	//�����¼� 
public:
	//�û�����
	virtual bool __cdecl OnActionUserOffLine(WORD wChairID, IServerUserItem * pIServerUserItem) { return true; }
	//�û�����
	virtual bool __cdecl OnActionUserReConnect(WORD wChairID, IServerUserItem * pIServerUserItem) { return true; }
	//�û�����
	virtual bool __cdecl OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�����
	virtual bool __cdecl OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�ͬ��
	virtual bool __cdecl OnActionUserReady(WORD wChairID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize) { return true; }

	//��Ϸ�¼�
public:
	//��Ϸ��ʼ
	virtual bool __cdecl OnEventGameStart();
	//��Ϸ����
	virtual bool __cdecl OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);
	//���ͳ���
	virtual bool __cdecl SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret);

	//��Ϣ�¼�
protected:
	//�����¼�
	bool OnUserGiveUp(WORD wChairID);
	//��ע�¼�
	bool OnUserAddScore(WORD wChairID, LONG lScore, bool bGiveUp);

	//�¼��ӿ�
public:
	//��ʱ���¼�
	virtual bool __cdecl OnTimerMessage(WORD wTimerID, WPARAM wBindParam);
	//��Ϸ��Ϣ����
	virtual bool __cdecl OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
	//�����Ϣ����
	virtual bool __cdecl OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
};

//////////////////////////////////////////////////////////////////////////

#endif