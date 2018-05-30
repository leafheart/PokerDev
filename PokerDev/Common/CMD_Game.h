#ifndef CMD_GAME_HEAD_FILE
#define CMD_GAME_HEAD_FILE

#include "biostream.h"

//////////////////////////////////////////////////////////////////////////
//��¼���ݰ�����

#define MDM_GR_LOGON				1									//�����¼

#define SUB_GR_LOGON_ACCOUNTS		1									//�ʻ���¼
#define SUB_GR_LOGON_USERID			2									//I D ��¼
#define SUB_GR_LOGON_USERID_V2		3									//I D ��¼
#define SUB_GR_LOGON_USERID_V3		4									//I D ��¼

#define SUB_GR_HEART_BEAT			10									//����

#define SUB_GR_LOGON_SUCCESS		100									//��¼�ɹ�
#define SUB_GR_LOGON_ERROR			101									//��¼ʧ��
#define SUB_GR_LOGON_FINISH			102									//��¼���

#define SUB_GR_LOGON_CHECK_ROOM		103									//��¼��ɺ�У�鷿����Ƿ����

//�����ʺŵ�¼
struct CMD_GR_LogonByAccounts
{
	enum {M_ID = MDM_GR_LOGON};
	enum {S_ID = SUB_GR_LOGON_ACCOUNTS};

	unsigned int							dwPlazaVersion;						//�㳡�汾
	unsigned int							dwProcessVersion;					//���̰汾
	char							szAccounts[NAME_LEN];				//��¼�ʺ�
	char							szPassWord[PASS_LEN];				//��¼����

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

//���� ID ��¼
struct CMD_GR_LogonByUserID
{
	enum {M_ID = MDM_GR_LOGON};
	enum {S_ID = SUB_GR_LOGON_USERID};

	unsigned int							dwPlazaVersion;						//�㳡�汾
	unsigned int							dwProcessVersion;					//���̰汾
	unsigned int							dwUserID;							//�û� I D
	char									szPassWord[PASS_LEN];				//��¼����

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

	unsigned int							dwPlazaVersion;						//�㳡�汾
	unsigned int							dwProcessVersion;					//���̰汾
	unsigned int							dwUserID;							//�û� I D
	char									szPassWord[PASS_LEN];				//��¼����
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

	unsigned int							dwPlazaVersion;						//�㳡�汾
	unsigned int							dwProcessVersion;					//���̰汾
	unsigned int							dwUserID;							//�û� I D
	char									szPassWord[PASS_LEN];				//��¼����
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

//��¼�ɹ���Ϣ
struct CMD_GR_LogonSuccess
{
	enum {M_ID = MDM_GR_LOGON};
	enum {S_ID = SUB_GR_LOGON_SUCCESS};

	unsigned int							dwUserID;							//�û� I D

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

//��¼ʧ��
struct CMD_GR_LogonError
{
	enum {M_ID = MDM_GR_LOGON};
	enum {S_ID = SUB_GR_LOGON_ERROR};

	int							lErrorCode;							//�������
	char							szErrorDescribe[128];				//������Ϣ

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

//У�鷿���Ƿ����
struct CMD_GR_LogonCheckRoom
{
	enum { M_ID = MDM_GR_LOGON };
	enum { S_ID = SUB_GR_LOGON_CHECK_ROOM };

	unsigned int							dwUserID;							//�û� I D
	unsigned int							dwRoomID;							//�����
	unsigned int							dwTableID;							//����

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
//�û����ݰ�����

#define MDM_GR_USER					2									//�û���Ϣ

#define SUB_GR_USER_SIT_REQ			1									//��������
#define SUB_GR_USER_SIT_REQ_V2		5									//��������
#define SUB_GR_USER_LOOKON_REQ		2									//�Թ�����
#define SUB_GR_USER_STANDUP_REQ		3									//��������
#define SUB_GR_USER_LEFT_GAME_REQ	4									//�뿪��Ϸ
#define SUB_GR_USER_SIT_REQ_V3		6									//��������

#define SUB_GR_USER_STATUS_REQ		10									//��ѯ���״̬����������ʹ��
#define SUB_GR_USER_STATUS_REP		11									//��ѯ���״̬����������ʹ��

#define SUB_GR_USER_STATUS_HAOYOU	12									//���ѷ��û���ʱ�뿪״̬

#define SUB_GR_USER_COME			100									//�û�����
#define SUB_GR_USER_STATUS			101									//�û�״̬
#define SUB_GR_USER_SCORE			102									//�û�����
#define SUB_GR_SIT_FAILED			103									//����ʧ��
#define SUB_GR_USER_RIGHT			104									//�û�Ȩ��
#define SUB_GR_MEMBER_ORDER			105									//��Ա�ȼ�

#define SUB_GR_USER_CHAT			200									//������Ϣ
#define SUB_GR_USER_WISPER			201									//˽����Ϣ
#define SUB_GR_USER_RULE			202									//�û�����

#define SUB_GR_USER_INVITE			300									//������Ϣ
#define SUB_GR_USER_INVITE_REQ		301									//��������

#define SUB_GR_USER_SPEAKER_MSG_REP		302								//���յ�������Ϣ

#define SUB_GR_USER_SEND_LABA_REQ				304							//����������
#define SUB_GR_USER_SEND_LABA_REP				305							//���������Ƚ��

#define SUB_GR_USER_CHECK_LABA_REQ				306							//����У����������
#define SUB_GR_USER_CHECK_LABA_REP				307							//У�����Ƚ��


#define SUB_GR_USER_MASTER_DISMISS_FRIEND_REQ			408						//����Ҫ���ɢ���ѷ�
#define SUB_GR_USER_MASTER_DISMISS_FRIEND_REP			409						//����Ҫ���ɢ���ѷ��㲥

#define SUB_GR_USER_GUEST_DISMISS_FRIEND_REQ			410						//��Ϸ��������ǰ�������ѷ�
#define SUB_GR_USER_GUEST_DISMISS_FRIEND_RESULT			411						//��Ϸ��������ǰ�������ѷ����û�ѡ��

#define SUB_GR_USER_FACE_URL							420						//����Զ���ͷ��
#define SUB_GR_USER_OFFLINE_REMAIN_TIME					421						//��Ҷ���ʣ��ʱ��
#define SUB_GR_USER_OFFLINE_REMAIN_TIME_V2				423						//��Ҷ���ʣ��ʱ��
#define SUB_GR_USER_EXT_INFO			422								//��Ҹ�����Ϣ

#define SUB_GR_USER_YY_SEQ			430									//��ҷ�������
#define SUB_GR_USER_YY_REP			431									//��������㲥

#define SUB_GR_USER_HB_SEQ			432									//���
#define SUB_GR_USER_HB_REP			433									//����㲥

#define SUB_GR_USER_WEIHU_REP			434									//ά���㲥

#define SUB_GR_USER_GPS_REQ			436								//GPS
#define SUB_GR_USER_GPS_REP			437								//GPS

#define SUB_GR_USER_GPS_REQ_V2			472							//GPS
#define SUB_GR_USER_GPS_REP_V2			473							//GPS

#define SUB_S_GAME_DISSMISS_ROOM			438						//������ҶԽ�ɢ�������Ӧ
#define SUB_S_GAME_DISSMISS_TIME            439                     //��ɢ���䵹��ʱ
#define SUB_S_GAME_PLAYER_REDYE_STATE       440                     //���׼��״̬

#define SUB_GR_TABLE_LIST_QUERY				441						// ��ѯ���������б�
#define SUB_GR_TABLE_LIST_REP				442						// ��ѯ���������б�����ֻ����������������������ݣ�
#define SUB_GR_TABLE_LIST_REP_END			443						// ��ѯ���������б�������
#define SUB_GR_TABLE_LIST_TABLE_UPDATE		444						// �����������ݸ��£����������ͬ����
#define SUB_GR_TABLE_LIST_USER_INFO_QUERY	445						// �鿴���������������Ϣ
#define SUB_GR_TABLE_LIST_USER_INFO_REP		446						// �鿴���������������Ϣ���
#define SUB_GR_TABLE_LOCK_REQ				447						// ��������������
#define SUB_GR_TABLE_LOCK_REP				448						// ���������ý��
#define SUB_GR_TABLE_LOCK_STATE_SYN			449						// ������״̬ͬ����ͬ����Ա
#define SUB_GR_TABLE_LIST_LABA_QUERY		450						// ��ѯ��������
#define SUB_GR_TABLE_LIST_LABA_REP			451						// ��ѯ������������
 
#define SUB_GR_USER_BBS_SCROLL_REP			452						// ����������Ϣ���
#define SUB_GR_ROOM_FLAG					453						// �����ʶ����
#define SUB_GR_USER_COME_EX					454						// ��ҽ����Ĳ�������
#define SUB_GR_SIT_FAILED_EX				455						// ����ʧ��
#define SUB_GR_KICK_OFF_TABLE				457						// �����������


#define SUB_GR_USER_SEND_START_REQ			470						//�������Ϳ�ʼ��Ϸ��ť
#define SUB_GR_USER_SEND_START_REP			471						//�������Ϳ�ʼ��Ϸ��ť���

//�����������������͹��������׼����Ϣ
struct CMD_GR_PLAYER_REDEAY_STATE
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_S_GAME_PLAYER_REDYE_STATE };

	bool redy_situation[MAX_CHAIR_NORMAL];  //��ҵ�׼��״̬ 

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

//�����������������͹����Ľ�ɢ�������Ϣ������У�
struct CMD_GR_DISSMISS_ROOM
{
	enum { AGREE=1, DISAGREE, DISMISS_CREATOR, WATING, DISSMISS_MAX };  //ͬ�� ��ͬ�� ��ɢ���䷢����  �ȴ��У���δ����ͬ�����

	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_S_GAME_DISSMISS_ROOM };

	unsigned int  player_situation[MAX_CHAIR_NORMAL];  //������ҶԽ�ɢ����ķ�Ӧ (�����±� 0 1 2 3��ʾ���ӱ��)
	unsigned int  dissmiss_timer;  //�Զ����㵹��ʱʱ��


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

	unsigned int  dissmiss_timer;   //��������������Ľ�ɢ��ʱʱ���ʣ������

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

//��ҷ��ͺ��
struct CMD_GR_UserWEIHURep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_WEIHU_REP };

	unsigned int	dwType;		//ά������
	unsigned short	nLen;
	char			szExtInfo[256];	//�û���
	//float			price;			//�������

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

//��ҷ��ͺ��
struct CMD_GR_UserHBRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_HB_REP };

	unsigned int	dwUserID;		//���ݿ� ID	
	//char			szExtInfo[32];	//�û���
	float			price;			//�������

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
//������Ϸ��ʼ��Ϣ
struct CMD_GR_UserStartGameReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SEND_START_REQ };

	unsigned int dwUserID;	//���ݿ� ID

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

//�������Ϳ�ʼ��Ϸ��ť���
struct CMD_GR_UserStartGameRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SEND_START_REP };

	unsigned int dwtype;	//�������� 0���ɹ���1������������㣻2�������û��׼����3:��ҵ���

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
//��ҷ�������
struct CMD_GR_UserYYInfo
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_YY_SEQ };

	unsigned int dwUserID;	//���ݿ� ID
	unsigned short	nLen;			
	char			szExtInfo[256];	//������ַ

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

//��������㲥
struct CMD_GR_UserYYREPInfo
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_YY_REP };

	unsigned int dwUserID;	//���ݿ� ID
	unsigned short	nLen;			
	char			szExtInfo[256];	//������ַ

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

//��Ҹ�����Ϣ
struct CMD_GR_UserExtInfo
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_EXT_INFO };

	unsigned int dwUserID;	//���ݿ� ID
	unsigned short	nLen;			
	char			szExtInfo[256];	//������Ϣ����ʽ k:v|k:v,  Ŀǰ֧��ip��Ϣ

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

//���ѷ��û���ʱ�뿪״̬
struct CMD_GR_UserStatus_HaoYou
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_STATUS_HAOYOU };

	unsigned int	dwUserID;							//���ݿ� ID
	unsigned short	wChairID;							//����λ��
	unsigned char	cbUserStatus;						//�û�״̬: 1�뿪 2����

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


//��Ҷ��ߵ�ʣ��ʱ��
struct CMD_GR_UserOfflineRemainTime
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_OFFLINE_REMAIN_TIME };
		
	unsigned short	nRemainTime[8];				//���8����ң�ÿ���˵�ʣ��ʱ�䡣��λ�� ����

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

//��Ҷ��ߵ�ʣ��ʱ��
struct CMD_GR_UserOfflineRemainTimeV2
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_OFFLINE_REMAIN_TIME_V2 };

	unsigned short	nRemainTime[8];				//���8����ң�ÿ���˵�ʣ��ʱ�䡣��λ�� ��

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

//����Զ���ͷ��
struct CMD_GR_UserFaceUrl
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_FACE_URL };

	unsigned int dwUserID;	//���ݿ� ID
	unsigned short	nLen;			
	char			szFaceUrl[256];	//ͷ���ַ

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

//����Ҫ���ɢ���ѷ�
struct CMD_GR_UserMasterDismissFriendReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_MASTER_DISMISS_FRIEND_REQ };

	unsigned short	nTableID;			//����
	char			szRoomID[NAME_LEN];	//�����

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

//����Ҫ���ɢ���ѷ��㲥
struct CMD_GR_UserMasterDismissFriendRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_MASTER_DISMISS_FRIEND_REP };

	unsigned short nCode;		//0-�����ɢ��1-�������ɢ��Ϸ�Ѿ���ʼ
	char szContent[NAME_LEN];	//������Ϣ

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


//��Ϸ��������ǰ�������ѷ�
struct CMD_GR_UserGuestDismissFriendReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_GUEST_DISMISS_FRIEND_REQ };

	unsigned int dwUserID;	//��� ID

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

//��Ϸ��������ǰ�������ѷ����û�ѡ��
struct CMD_GR_UserGuestDismissFriendResult
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_GUEST_DISMISS_FRIEND_RESULT };

	unsigned int	dwUserID;	//���ݿ� ID
	char			bFlag;		//1:ͬ��  0���ܾ�

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


//��Ա�ȼ�
struct CMD_GR_MemberOrder
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_MEMBER_ORDER};

	unsigned int							dwUserID;							//���ݿ� ID
	unsigned char							cbMemberOrder;						//��Ա�ȼ�

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

//�û�Ȩ��
struct CMD_GR_UserRight
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_RIGHT};

	unsigned int							dwUserID;							//���ݿ� ID
	unsigned int							dwUserRight;						//�û�Ȩ��

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

//�û�״̬
struct CMD_GR_UserStatus
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_STATUS};

	unsigned int							dwUserID;							//���ݿ� ID
	unsigned short							wTableID;							//����λ��
	unsigned short							wChairID;							//����λ��
	unsigned char							cbUserStatus;						//�û�״̬

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

//�û�����
struct CMD_GR_UserScore
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_SCORE};

	int							lLoveliness;						//�û�����
	//LONG							lInsureScore;						//���ѽ��
	//LONG							lGameGold;							//��Ϸ���
	unsigned int							dwUserID;							//�û� I D
	tagUserScore					UserScore;							//������Ϣ

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

//��������
struct CMD_GR_UserSitReq
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_SIT_REQ};
	
	unsigned short							wTableID;							//����λ��
	unsigned short							wChairID;							//����λ��
	unsigned char							cbPassLen;							//���볤��
	char							szTablePass[PASS_LEN];				//��������

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


//�������¡���ΪԭЭ����bug��ֻ�ܴ�1λ������
struct CMD_GR_UserSitReq_V2
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SIT_REQ_V2 };

	unsigned short							wTableID;							//����λ��
	unsigned short							wChairID;							//����λ��
	unsigned char							cbPassLen;							//���볤��
	char							szTablePass[PASS_LEN];				//��������

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

// ������ָ������ָ������
struct CMD_GR_UserSitReq_V3
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SIT_REQ_V3 };

	unsigned short							wTableID;							//����λ��
	unsigned short							wChairID;							//����λ��
	unsigned char							cbPassLen;							//���볤��
	char									szTablePass[PASS_LEN];				//��������

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

//�����û� 
struct CMD_GR_UserInviteReq
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_INVITE_REQ};

	unsigned short							wTableID;							//���Ӻ���
	unsigned int							dwUserID;							//�û� I D

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

//����ʧ��
struct CMD_GR_SitFailed
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_SIT_FAILED};

	char							szFailedDescribe[256];				//��������

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

// ����ʧ�ܴ�����
struct CMD_GR_SitFailedEx
{
	enum {HAD_SIT = 1, TABLE_LOCKED = 2, MONEY_LESS = 3, MONEY_OVER_LIMIT = 4, STOP_SERVICE = 5};
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_SIT_FAILED_EX};

	unsigned short			sCode;				// ����ʧ��ԭ��1λ������2��������3��Ҳ���4��ҳ���5����ά����
	unsigned short			sData1;				// ��������1
	unsigned int			usData2;			// ��������2

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

// �������������������
struct CMD_GR_KickOffTable
{
	enum {KICK_REASON_TIME_OUT = 1, KICK_REASON_VIP_KICKED = 2};
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_KICK_OFF_TABLE};

	unsigned short			sCode;			// ��������ԭ��1�һ���ʱ2������vip����ߣ�
	unsigned short			sData1;			// ��������1
	unsigned short			usData2;		// ��������2

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

//����ṹ 
struct CMD_GR_UserChat
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_CHAT};

	unsigned short							wChatLength;						//��Ϣ����
	unsigned int						crFontColor;						//��Ϣ��ɫ
	unsigned int							dwSendUserID;						//�����û�
	unsigned int							dwTargetUserID;						//Ŀ���û�
	char							szChatMessage[MAX_CHAT_LEN];		//������Ϣ

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

//˽��ṹ 
struct CMD_GR_Wisper
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_WISPER};

	unsigned short							wChatLength;						//��Ϣ����
	unsigned int						crFontColor;						//��Ϣ��ɫ
	unsigned int							dwSendUserID;						//�����û�
	unsigned int							dwTargetUserID;						//Ŀ���û�
	char							szChatMessage[MAX_CHAT_LEN];		//������Ϣ

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

//�û�����
struct CMD_GR_UserRule
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_RULE};

	bool							bPassword;							//��������
	bool							bLimitWin;							//����ʤ��
	bool							bLimitFlee;							//���ƶ���
	bool							bLimitScore;						//���Ʒ���
	bool							bCheckSameIP;						//Ч���ַ
	unsigned short							wWinRate;							//����ʤ��
	unsigned short							wFleeRate;							//��������
	int							lMaxScore;							//��߷��� 
	int							lLessScore;							//��ͷ���
	char							szPassword[PASS_LEN];				//��������

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

//�����û� 
struct CMD_GR_UserInvite
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_INVITE};

	unsigned short							wTableID;							//���Ӻ���
	unsigned int							dwUserID;							//�û� I D

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


// ����У�鷢����������
struct CMD_GR_UserCheckLabaReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_CHECK_LABA_REQ };
	
	short			iLen;
	char			strLabaInfo[256];	// ��������

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

//У�����Ƚ��
struct CMD_GR_UserCheckLabaRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_CHECK_LABA_REP };

	short			nCode;				// �����룺0Ϊ�ɹ�
	short			nLen;
	char			strLabaInfo[256];	// ��������

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

	short	nBbsScroll;				//�������������.���10��
	char	szBbsScroll[10][100];	//������������

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

// ����ģʽ��־
struct CMD_GR_RoomFlag
{
	enum { SIT_FLAG = 0, LOCK_FLAG = 1};
	enum { M_ID = MDM_GR_USER};
	enum { S_ID = SUB_GR_ROOM_FLAG};

	unsigned int					usFlag;			// ��־λ��0λ������־1λ������־��

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

// ��ҽ�����Ϸ���Ӳ�������Э��
struct CMD_GR_UserComeEx
{
	enum { M_ID = MDM_GR_USER};
	enum { S_ID = SUB_GR_USER_COME_EX};

	unsigned int						dwData1;					// �����ֶ�(���ID)
	char								szDescribe[128];			// ����ǩ��

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

// ����������
struct CMD_GR_UserSendLabaReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SEND_LABA_REQ};

	unsigned int					dwUserID;		//��� ID
	short							nLen;
	char							strLabaInfo[256];	// ��������

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

// �������Ƚ��
struct CMD_GR_UserSendLabaRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_SEND_LABA_REP };

	short							nCode;			// �����룺0Ϊ�ɹ�
	unsigned int					dwUserID;		//��� ID
	unsigned int					dwCurScore;		//�ɹ���Ľ������ǰ������Ϸ����

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

//���յ�������Ϣ
struct CMD_GR_SpeakerMsgRep
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_USER_SPEAKER_MSG_REP};

	unsigned short						nType;					//��Ϣ����
	unsigned short						nLen;					//��Ϣ����
	char								szMsg[256];				//��Ϣ����

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

// ��ѯ���������б���Ϣ
struct CMD_GR_TableListQuery
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_QUERY};

	unsigned short						sBeginTableIndex;			// ��ѯ��ʼ����id
	unsigned short						sEndTableIndex;				// ��ѯ��������id
	unsigned short						sUserTableIndex;			// ��Ҳ�ѯ��������id(��ʱ��������)
	unsigned short						sUserAOI;					// ��Ҽ����������ݱ仯��Χ����ʱ�������ã�
	unsigned short						sData1;						// ��������1
	unsigned short						sData2;						// ��������2
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

// ��ѯ���������б�����Ϣ��ֻ����������������������ݣ�
struct CMD_GR_TableListRep
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_REP};

	unsigned short						sResult;					// ��ѯ�����0��ʾ�ɹ�1��ʾʧ�ܣ�
	unsigned short						sTableID;					// ����ID
	unsigned short						sLockState;					// ����״̬��0û��1����)
	unsigned short						sData1;						// ��������1
	// �������������
	unsigned int						usPlayerID;					// �������ID
	unsigned short						sChairID;					// ����ID
	unsigned short						sGender;					// ����Ա�
	unsigned short						sVip;						// VIP��ʶ
	unsigned short						sData2;						// ��������2
	unsigned int						usGoldScore;				// �������

	char								szNickname[NAME_LEN];		// ����ǳ�
	char								szFaceURL[256];				// ͷ��


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

// ��ѯ���������б���������Ϣ
struct CMD_GR_TableListRepEnd
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_REP_END};

	unsigned int						usUserID;					// ��ѯ���id

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

// �����������ݸ���
struct CMD_GR_TableListUpdate
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_TABLE_UPDATE};

	unsigned short						sUpdateType;				// �������(1��������2���ӽ���3�������4����뿪5��ұ��)
	unsigned short						sTableID;					// �������ID
	unsigned short						sLockState;					// ����״̬��0û��1����)
	unsigned short						sData1;						// ��������1

	// �������������
	unsigned int						usPlayerID;					// �������ID
	unsigned short						sChairID;					// ����ID
	unsigned short						sGender;					// ����Ա�
	unsigned short						sVip;						// VIP��ʶ
	unsigned short						sData2;						// ��������2
	unsigned int						usGoldScore;				// �������

	char								szNickname[NAME_LEN];		// ����ǳ�
	char								szFaceURL[256];				// ͷ�� 

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
	E_TABLE_UPDATE_TYPE_LOCKED				= 1,	// ����
	E_TABLE_UPDATE_TYPE_UNLOCK				= 2,	// ����
	E_TABLE_UPDATE_TYPE_USER_SIT			= 3,	// �������
	E_TABLE_UPDATE_TYPE_USER_LEAVE			= 4,	// ����뿪
	E_TABLE_UPDATE_TYPE_USER_MONEY_UPDATE	= 5,	// ��ҽ�ұ��
	E_TABLE_UPDATE_TYPE_END,
};

// �鿴���������������Ϣ
struct CMD_GR_TableListUserInfoQuery 
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_USER_INFO_QUERY};

	unsigned short						sTableID;				// ����ID
	unsigned short						sChairID;				// ����ID
	unsigned int						usData1;				// ��������1

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

// �鿴���������������Ϣ
struct CMD_GR_TableListUserInfoRep 
{
	enum {SUCC = 0, FAIL = 1, NO_PLAYER = 2};
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_USER_INFO_REP};

	unsigned short						sResult;					// ��ѯ�����0��ʾ�ɹ�1ʧ��2��λ��û�ˣ�
	unsigned short						sData1;						// ��������1

	unsigned short						sTableID;					// ����ID
	unsigned short						sChairID;					// ����ID
	unsigned int						usPlayerID;					// �������ID
	unsigned short						sGender;					// ����Ա�
	unsigned short						sVip;						// VIP��ʶ
	unsigned int						usWinCount;					// ʤ������
	unsigned int						usLostCount;				// ʧ������
	unsigned int						usDrawCount;				// �;�����
	unsigned int						usFleeCount;				// ������Ŀ
	unsigned int						usData2;					// ��������2

	char								szNickname[NAME_LEN];		// ����ǳ�
	char								szDescribe[128];			// ����ǩ��
	char								szFaceURL[256];				// ͷ��

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

// ��������������
struct CMD_GR_TableLockReq
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LOCK_REQ};

	unsigned short						sLockState;					// ��״̬��0����1����
	unsigned short						sData1;						// ��������1

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

// ���������ý��
struct CMD_GR_TableLockRep
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LOCK_REP};

	unsigned short						sResult;					// ���������0�ɹ�1ʧ��2����VIP  3��Ҫ2����������ſ�����)
	unsigned short						sLockState;					// ��״̬��0����1����

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

// ������״̬ͬ��
struct CMD_GR_TableLockSyn
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LOCK_STATE_SYN};

	unsigned short						sLockState;					// ��״̬��0����1����
	unsigned short						sData1;						// ��������1

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

// ��ѯ��������
struct CMD_GR_LabaCountQuery 
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_LABA_QUERY};

	unsigned int					dwUserID;				// ���ID

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

// ��ѯ������������
struct CMD_GR_LabaCountRep
{
	enum {M_ID = MDM_GR_USER};
	enum {S_ID = SUB_GR_TABLE_LIST_LABA_REP};

	unsigned int					usLabaCount;				// ��������

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
	E_TABLE_LOCK_RES_SUCC			= E_TABLE_LOCK_RES_BEGIN,	// �ɹ�
	E_TABLE_LOCK_RES_FAIL			= 1,						// ʧ��
	E_TABLE_LOCK_RES_NOT_VIP		= 2,						// ����vip
	E_TABLE_LOCK_RES_NEED_2_PLAYER	= 3,						// ��Ҫ2����������ſ�����
	E_TABLE_LOCK_RES_END,
};




//////////////////////////////////////////////////////////////////////////
//������Ϣ���ݰ�

#define MDM_GR_INFO					3									//������Ϣ

#define SUB_GR_SERVER_INFO			100									//��������
#define SUB_GR_ORDER_INFO			101									//�ȼ�����
#define SUB_GR_MEMBER_INFO			102									//��Ա����
#define SUB_GR_COLUMN_INFO			103									//�б�����
#define SUB_GR_CONFIG_FINISH		104									//�������

//��Ϸ������Ϣ
struct CMD_GR_ServerInfo
{
	enum {M_ID = MDM_GR_INFO};
	enum {S_ID = SUB_GR_SERVER_INFO};

	//��������
	unsigned short							wKindID;							//���� I D
	unsigned short							wTableCount;						//������Ŀ
	unsigned short							wChairCount;						//������Ŀ
	unsigned int							dwVideoAddr;						//��Ƶ��ַ

	//��չ����
	unsigned short							wGameGenre;							//��Ϸ����
	unsigned char							cbHideUserInfo;						//������Ϣ

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

//����������Ϣ
struct CMD_GR_ScoreInfo_CB
{
	unsigned short							wDescribeCount;						//������Ŀ
	unsigned short							wDataDescribe[16];					//���ݱ�־
};

//�ȼ������ṹ
struct tagOrderItem
{
	int							lScore;								//�ȼ�����
	unsigned short							wOrderDescribe[16];					//�ȼ�����

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

//�ȼ�������Ϣ
struct CMD_GR_OrderInfo
{
	enum {M_ID = MDM_GR_INFO};
	enum {S_ID = SUB_GR_ORDER_INFO};

	unsigned short							wOrderCount;						//�ȼ���Ŀ
	tagOrderItem					OrderItem[128];						//�ȼ�����

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

//�б��������ṹ
struct tagColumnItem
{
	unsigned short							wColumnWidth;						//�б���
	unsigned short							wDataDescribe;						//�ֶ�����
	char							szColumnName[16];					//�б�����
};

//�б�������Ϣ
struct CMD_GR_ColumnInfo
{
	enum {M_ID = MDM_GR_INFO};
	enum {S_ID = SUB_GR_COLUMN_INFO};

	unsigned short							wColumnCount;						//�б���Ŀ
	tagColumnItem					ColumnItem[32];						//�б�����

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
//����״̬���ݰ�

#define MDM_GR_STATUS				4									//״̬��Ϣ

#define SUB_GR_TABLE_INFO			100									//������Ϣ
#define SUB_GR_TABLE_STATUS			101									//����״̬

//����״̬�ṹ
struct tagTableStatus
{
	unsigned char							bTableLock;							//����״̬
	unsigned char							bPlayStatus;						//��Ϸ״̬

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

//����״̬����
struct CMD_GR_TableInfo
{
	enum {M_ID = MDM_GR_STATUS};
	enum {S_ID = SUB_GR_TABLE_INFO};

	unsigned short							wTableCount;						//������Ŀ
	tagTableStatus					TableStatus[512];					//״̬����

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

//����״̬��Ϣ
struct CMD_GR_TableStatus
{
	enum {M_ID = MDM_GR_STATUS};
	enum {S_ID = SUB_GR_TABLE_STATUS};

	unsigned short							wTableID;							//���Ӻ���
	unsigned char							bTableLock;							//����״̬
	unsigned char							bPlayStatus;						//��Ϸ״̬

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
//�������ݰ�

#define MDM_GR_MANAGER				5									//��������

#define SUB_GR_SEND_WARNING			1									//���;���
#define SUB_GR_SEND_MESSAGE			2									//������Ϣ
#define SUB_GR_LOOK_USER_IP			3									//�鿴��ַ
#define SUB_GR_KILL_USER			4									//�߳��û�
#define SUB_GR_LIMIT_ACCOUNS		5									//�����ʻ�
#define SUB_GR_SET_USER_RIGHT		6									//Ȩ������
#define SUB_GR_OPTION_SERVER		7									//��������

//���;���
struct CMD_GR_SendWarning
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_SEND_WARNING};

	unsigned short							wChatLength;						//��Ϣ����
	unsigned int							dwTargetUserID;						//Ŀ���û�
	char							szWarningMessage[MAX_CHAT_LEN];		//������Ϣ

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

//ϵͳ��Ϣ
struct CMD_GR_SendMessage
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_SEND_MESSAGE};

	unsigned char							cbGame;								//��Ϸ��Ϣ
	unsigned char							cbRoom;								//��Ϸ��Ϣ
	unsigned short							wChatLength;						//��Ϣ����
	char							szSystemMessage[MAX_CHAT_LEN];		//ϵͳ��Ϣ

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

//�鿴��ַ
struct CMD_GR_LookUserIP
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_LOOK_USER_IP};

	unsigned int							dwTargetUserID;						//Ŀ���û�

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

//�߳��û�
struct CMD_GR_KillUser
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_KILL_USER};

	unsigned int							dwTargetUserID;						//Ŀ���û�

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

//�����ʻ�
struct CMD_GR_LimitAccounts
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_LIMIT_ACCOUNS};

	unsigned int							dwTargetUserID;						//Ŀ���û�

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

//Ȩ������
struct CMD_GR_SetUserRight
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_SET_USER_RIGHT};

	//Ŀ���û�
	unsigned int							dwTargetUserID;						//Ŀ���û�

	//�󶨱���
	unsigned char							cbGameRight;						//�ʺ�Ȩ��
	unsigned char							cbAccountsRight;					//�ʺ�Ȩ��

	//Ȩ�ޱ仯
	unsigned char							cbLimitRoomChat;					//��������
	unsigned char							cbLimitGameChat;					//��Ϸ����
	unsigned char							cbLimitPlayGame;					//��ϷȨ��
	unsigned char							cbLimitSendWisper;					//������Ϣ
	unsigned char							cbLimitLookonGame;					//�Թ�Ȩ��

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

//���ñ�־
#define OSF_ROOM_CHAT				1									//��������
#define OSF_GAME_CHAT				2									//��Ϸ����
#define OSF_ROOM_WISPER				3									//����˽��
#define OSF_ENTER_GAME				4									//������Ϸ
#define OSF_ENTER_ROOM				5									//���뷿��
#define OSF_SHALL_CLOSE				6									//�����ر�

//��������
struct CMD_GR_OptionServer
{
	enum {M_ID = MDM_GR_MANAGER};
	enum {S_ID = SUB_GR_OPTION_SERVER};

	unsigned char							cbOptionFlags;						//���ñ�־
	unsigned char							cbOptionValue;						//���ñ�־

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
//ϵͳ���ݰ�

#define MDM_GR_SYSTEM				10									//ϵͳ��Ϣ

#define SUB_GR_MESSAGE				100									//ϵͳ��Ϣ

//��Ϣ����
#define SMT_INFO					0x0001								//��Ϣ��Ϣ
#define SMT_EJECT					0x0002								//������Ϣ
#define SMT_GLOBAL					0x0004								//ȫ����Ϣ
#define SMT_CLOSE_ROOM				0x1000								//�رշ���
#define SMT_SYS_KICK				0x2000								//ϵͳ����
#define SMT_INTERMIT_LINE			0x4000								//�ж�����(Ŀǰ����VIP����)
#define SMT_ROOM_WEIHU				0x0010								//ά������
#define SMT_ROOM_MAXSCORE			0x0020									//��Ӯ����

//��Ϣ���ݰ�
struct CMD_GR_Message
{
	enum {M_ID = MDM_GR_SYSTEM};
	enum {S_ID = SUB_GR_MESSAGE};

	unsigned short							wMessageType;						//��Ϣ����
	unsigned short							wMessageLength;						//��Ϣ����
	char							szContent[1024];					//��Ϣ����

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
//�������ݰ�

#define MDM_GR_SERVER_INFO			11									//������Ϣ

#define SUB_GR_ONLINE_COUNT_INFO	100									//������Ϣ

//������Ϣ
struct tagOnLineCountInfo
{
	enum {M_ID = MDM_GR_SERVER_INFO};
	enum {S_ID = SUB_GR_ONLINE_COUNT_INFO};

	unsigned short							wKindID;							//���ͱ�ʶ
	unsigned int							dwOnLineCount;						//��������

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