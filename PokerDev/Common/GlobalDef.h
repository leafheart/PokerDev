#ifndef GLOBAL_DEF_HEAD_FILE
#define GLOBAL_DEF_HEAD_FILE

#pragma once

#include "biostream.h"
#include "GlobalProperty.h"

//////////////////////////////////////////////////////////////////////////
//��������

//#define MAX_CHAIR						100								//�������
#define MAX_CHAIR_NORMAL				8								//�������
#define MAX_CHAIR						MAX_CHAIR_NORMAL				//�������

#define MAX_ANDROID						256								//������
#define MAX_CHAT_LEN					128								//���쳤��
#define LIMIT_CHAT_TIMES				1200							//��ʱ����

/////////////////////////////////////////////////////////////////////////////////////////
//�궨��

//�˿ڶ���
#define PORT_VIDEO_SERVER				7600								//��Ƶ������
#define PORT_LOGON_SERVER				9001								//��½������
#define PORT_CENTER_SERVER				9010								//���ķ�����

//�������ݶ���
#define SOCKET_VER						0x66								//����汾
#define SOCKET_BUFFER					8192								//���绺��
#define SOCKET_PACKET					(SOCKET_BUFFER-sizeof(CMD_Head)-2*sizeof(unsigned long))

/////////////////////////////////////////////////////////////////////////////////////////

//�ں�������
#define MDM_KN_COMMAND					0									//�ں�����
#define SUB_KN_DETECT_SOCKET			1									//�������
#define SUB_KN_SHUT_DOWN_SOCKET			2									//�ж�����

//�����ں�
struct CMD_Info
{
	unsigned char								cbVersion;							//�汾��ʶ
	unsigned char								cbCheckCode;						//Ч���ֶ�
	unsigned short								wPacketSize;						//���ݴ�С
};

//��������
struct CMD_Command
{
	unsigned short								wMainCmdID;							//��������
	unsigned short								wSubCmdID;							//��������
};

//�����ͷ
struct CMD_Head
{
	CMD_Info							CmdInfo;							//�����ṹ
	CMD_Command							CommandInfo;						//������Ϣ
};

//���������
struct CMD_Buffer
{
	CMD_Head							Head;								//���ݰ�ͷ
	unsigned char								cbBuffer[SOCKET_PACKET];			//���ݻ���
};

//���ṹ��Ϣ
struct CMD_KN_DetectSocket
{
	unsigned int								dwSendTickCount;					//����ʱ��
	unsigned int								dwRecvTickCount;					//����ʱ��
};

/////////////////////////////////////////////////////////////////////////////////////////

//IPC ���ݶ���
#define IPC_VER							0x0001								//IPC �汾
#define IPC_IDENTIFIER					0x0001								//��ʶ����
#define IPC_PACKAGE						4096								//��� IPC ��
#define IPC_BUFFER						(sizeof(IPC_Head)+IPC_PACKAGE)		//���峤��

//IPC ���ݰ�ͷ
struct IPC_Head
{
	unsigned short								wVersion;							//IPC �汾
	unsigned short								wDataSize;							//���ݴ�С
	unsigned short								wMainCmdID;							//��������
	unsigned short								wSubCmdID;							//��������
};

//IPC ����ṹ
struct IPC_Buffer
{
	IPC_Head							Head;								//���ݰ�ͷ
	unsigned char								cbBuffer[IPC_PACKAGE];				//���ݻ���
};


//���Ⱥ궨��
#define TYPE_LEN						32									//���೤��
#define KIND_LEN						32									//���ͳ���
#define STATION_LEN						32									//վ�㳤��
#define SERVER_LEN						32									//���䳤��
#define MODULE_LEN						32									//���̳���
#define RULE_LEN						512									//���򳤶�

//�Ա���
#define GENDER_NULL						0									//δ֪�Ա�
#define GENDER_BOY						1									//�����Ա�
#define GENDER_GIRL						2									//Ů���Ա�

//��Ϸ����
#define GAME_GENRE_SCORE				0x0001								//��ֵ����
#define GAME_GENRE_GOLD					0x0002								//�������
#define GAME_GENRE_MATCH				0x0004								//��������
#define GAME_GENRE_EDUCATE				0x0008								//ѵ������

//��Ϸ����ṹ
struct tagLevelItem
{
	int								lLevelScore;						//�������
	char								szLevelName[16];					//��������
};

//�û�״̬����
#define US_NULL							0x00								//û��״̬
#define US_FREE							0x01								//վ��״̬
#define US_SIT							0x02								//����״̬
#define US_READY						0x03								//ͬ��״̬
#define US_LOOKON						0x04								//�Թ�״̬
#define US_PLAY							0x05								//��Ϸ״̬
#define US_OFFLINE						0x06								//����״̬

//���Ⱥ궨��
#define NAME_LEN						32									//���ֳ���
#define PASS_LEN						33									//���볤��
#define EMAIL_LEN						32									//���䳤��
#define GROUP_LEN						32									//���ų���
#define COMPUTER_ID_LEN					33									//��������
#define UNDER_WRITE_LEN					32									//����ǩ��

//�û�������Ϣ
struct tagUserScore
{
	int								lScore;								//�û�����
	int								lGameGold;							//��Ϸ���//
	int								lInsureScore;						//�洢���
	int								lWinCount;							//ʤ������
	int								lLostCount;							//ʧ������
	int								lDrawCount;							//�;�����
	int								lFleeCount;							//������Ŀ
	int								lExperience;						//�û�����

	void reset() { memset(this, 0, sizeof(*this)); }
	tagUserScore() { reset(); }
	friend bostream& operator<<(bostream& bos,const tagUserScore& pl)
	{
		bos << pl.lScore;
		bos << pl.lGameGold;
		bos << pl.lInsureScore;
		bos << pl.lWinCount;
		bos << pl.lLostCount;
		bos << pl.lDrawCount;
		bos << pl.lFleeCount;
		bos << pl.lExperience;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,tagUserScore& pl)
	{	
		pl.reset();
		bis >> pl.lScore;
		bis >> pl.lGameGold;
		bis >> pl.lInsureScore;
		bis >> pl.lWinCount;
		bis >> pl.lLostCount;
		bis >> pl.lDrawCount;
		bis >> pl.lFleeCount;
		bis >> pl.lExperience;

		return bis;
	}
};

//�û�״̬��Ϣ
struct tagUserStatus
{
	unsigned short								wTableID;							//���Ӻ���
	unsigned short								wChairID;							//����λ��
	unsigned char								cbUserStatus;						//�û�״̬
};

//�û�������Ϣ�ṹ
struct tagUserInfoHead
{
	//�û�����
	unsigned short								wFaceID;							//ͷ������
	unsigned int								dwUserID;							//�û� I D
	unsigned int								dwGameID;							//��Ϸ I D
	unsigned int								dwGroupID;							//��������
	unsigned int								dwUserRight;						//�û��ȼ�
	int								lLoveliness;						//�û�����
	unsigned int								dwMasterRight;						//����Ȩ��

	char								szName[NAME_LEN];					//�û�����

	//�û�����
	unsigned char								cbGender;							//�û��Ա�
	unsigned char								cbMemberOrder;						//��Ա�ȼ�
	unsigned char								cbMasterOrder;						//����ȼ�

	//�û�״̬
	unsigned short								wTableID;							//���Ӻ���
	unsigned short								wChairID;							//����λ��
	unsigned char								cbUserStatus;						//�û�״̬

	//�û�����
	tagUserScore						UserScoreInfo;						//������Ϣ

	//��չ��Ϣ
	//long								lInsureScore;						//���ѽ��
	//long								lGameGold;							//��Ϸ���
	unsigned int								dwCustomFaceVer;					//�ϴ�ͷ��
	unsigned int								dwPropResidualTime[PROPERTY_COUNT];	//����ʱ��
};

//�û���Ϣ�ṹ
struct tagUserData
{
	//�û�����
	unsigned short								wFaceID;							//ͷ������
	unsigned int								dwCustomFaceVer;					//�ϴ�ͷ��
	unsigned int								dwUserID;							//�û� I D
	unsigned int								dwGroupID;							//��������
	unsigned int								dwGameID;							//�û� I D
	unsigned int								dwUserRight;						//�û��ȼ�
	int								lLoveliness;						//�û�����
	unsigned int								dwMasterRight;						//����Ȩ��
	char								szName[NAME_LEN];					//�û�����
	char								szGroupName[GROUP_LEN];				//��������
	char								szUnderWrite[UNDER_WRITE_LEN];		//����ǩ��

	//�û�����
	unsigned char								cbGender;							//�û��Ա�
	unsigned char								cbMemberOrder;						//��Ա�ȼ�
	unsigned char								cbMasterOrder;						//����ȼ�

	//�û�����
	int								lInsureScore;						//���ѽ��
	int								lGameGold;							//��Ϸ���
	int								lScore;								//�û�����
	int								lWinCount;							//ʤ������
	int								lLostCount;							//ʧ������
	int								lDrawCount;							//�;�����
	int								lFleeCount;							//������Ŀ
	int								lExperience;						//�û�����

	//�û�״̬
	unsigned short								wTableID;							//���Ӻ���
	unsigned short								wChairID;							//����λ��
	unsigned char								cbUserStatus;						//�û�״̬

	//������Ϣ
	unsigned char								cbCompanion;						//�û���ϵ
	unsigned int								dwPropResidualTime[PROPERTY_COUNT];	//����ʱ��
};

//////////////////////////////////////////////////////////////////////////

//�������кŽṹ
struct tagClientSerial
{
	unsigned int								dwSystemVer;						//ϵͳ�汾
	unsigned int								dwComputerID[3];					//��������
};

//���û���ṹ
struct tagOptionBuffer
{
	unsigned char								cbBufferLen;						//���ݳ���
	unsigned char								cbOptionBuf[32];					//���û���
};

//////////////////////////////////////////////////////////////////////////
#define CHECK(a)	if(false == (a))	return;
#define CHECKF(a)	if(false == (a))	return false;
#define CHECKF1(a)	if(false == (a))	return 1;
#define CHECKC(a)	if(false == (a))	continue;
#define CHECKBK(a)	if(false == (a))	break;

//////////////////////////////////////////////////////////////////////////

#endif