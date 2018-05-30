#ifndef GLOBAL_SERVICE_HEAD_FILE
#define GLOBAL_SERVICE_HEAD_FILE

#pragma once

#include "biostream.h"

//////////////////////////////////////////////////////////////////////////

//���ݿ�����
const TCHAR szGameUserDB[]=TEXT("QPGameUserDB");						//�û����ݿ�
const TCHAR	szTreasureDB[]=TEXT("QPTreasureDB");						//�Ƹ����ݿ�
const TCHAR szServerInfoDB[]=TEXT("QPServerInfoDB");					//�������ݿ�

//////////////////////////////////////////////////////////////////////////

//���ݿ���Ϣ
struct tagDataBaseInfo
{
	WORD							wDataBasePort;						//���ݿ�˿�
	//DWORD							dwDataBaseAddr;						//���ݿ��ַ
	TCHAR							szDataBaseAddr[128];				//���ݿ��ַ
	TCHAR							szDataBaseUser[32];					//���ݿ��û�
	TCHAR							szDataBasePass[32];					//���ݿ�����
	TCHAR							szDataBaseName[32];					//���ݿ�����
};

//////////////////////////////////////////////////////////////////////////

//��Ϸ��������
struct tagGameServiceAttrib
{
	WORD							wKindID;							//���ƺ���
	WORD							wChairCount;						//������Ŀ
	BYTE							cbJoinInGame;						//��Ϸ����
	TCHAR							szDataBaseName[32];					//��Ϸ����
	TCHAR							szDescription[128];					//ģ������
	TCHAR							szKindName[KIND_LEN];				//��������
	TCHAR							szServerModuleName[MODULE_LEN];		//ģ������
	TCHAR							szClientModuleName[MODULE_LEN];		//ģ������
};

//��Ϸ��������
struct tagGameServiceOption
{
	//��������
	WORD							wKindID;							//���ͱ�ʶ
	WORD							wSortID;							//�����ʶ
	WORD							wNodeID;							//վ�����
	WORD							wServerID;							//�������
	WORD							wTableCount;						//������Ŀ
	WORD							wServerPort;						//����˿�
	WORD							wServerType;						//��������
	WORD							wMaxConnect;						//�������
	DWORD							dwServerAddr;						//�����ַ
	DWORD							dwVideoServer;						//��Ƶ��ַ
	//DWORD							dwDataBaseAddr;						//���ݵ�ַ
	TCHAR							szDataBaseAddr[128];				//���ݵ�ַ
	TCHAR							szDataBaseName[SERVER_LEN];			//��������
	TCHAR							szGameRoomName[SERVER_LEN];			//��������
	TCHAR							szServerAddr[SERVER_LEN];			//�����ַ
	
	TCHAR							szGameRoomRuleBak[RULE_LEN];			//�������
	TCHAR							szGameRoomRule[RULE_LEN];			//�������
	
	WORD							wPrivateType;						//�Խ�������
	TCHAR							szPrivateRule[96];					//�Խ�������
	WORD							wCreateType;
	TCHAR							szUserName[SERVER_LEN];				//��������
	WORD							wPlayerCount;						//��3��/4����Ϸ
	WORD							wGameJuShu;							//ÿ�ŷ�������پ�
	WORD							wGameStartType;						//��Ϸ��ʼ��ʽ��2����Ҫ�������Ϳ�ʼ��Ϣ
	WORD							wDissmissWaitTime;					//�����ɢʱ�ĵȴ�ʱ�䣬ʱ�䵽��ѡ��ͬ��/�ܾ����Զ���ɢ
	BYTE							cbJoinInGameByCreate;				//��������ѡ���Ϸ��ʼ���Ƿ�������룬��cbJoinInGameΪtrueʱ����Ч

	//��������
	WORD							wRevenue;							//��Ϸ˰��
	LONG							lCellScore;							//��λ����
	LONG							lLessScore;							//��ͻ���
	LONG							lMaxScore;							//��߻���
	LONG							lRestrictScore;						//���ƻ���

	//��������
	LONG							lMatchDraw;							//��������
	BYTE							cbControlStart;						//���ƿ�ʼ

	//��չ����
	BYTE							cbHideUserInfo;						//������Ϣ
	BYTE							cbUnLookOnTag;						//�����Թ�
	BYTE							cbUnSameIPPlay;						//����ͬIP
};

//����������
#define	LESS_CONNECT_COUNT			(50L)								//��������
//////////////////////////////////////////////////////////////////////////

#endif