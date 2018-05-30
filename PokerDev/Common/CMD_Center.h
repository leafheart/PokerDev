#ifndef CMD_CENTER_HEAD_FILE
#define CMD_CENTER_HEAD_FILE

//
//��Ϸ�б�������
//

#define MDM_CS_SERVER_LIST				1								//�б���Ϣ

#define SUB_CS_GET_SERVER_LIST			1								//�����б�

#define SUB_CS_LIST_INFO				100								//�б���Ϣ
#define SUB_CS_LIST_TYPE				101								//�����б�
#define SUB_CS_LIST_KIND				102								//�����б�
#define SUB_CS_LIST_STATION				103								//վ���б�
#define SUB_CS_LIST_SERVER				104								//�����б�
#define SUB_CS_LIST_FINISH				105								//�б����

//�б���Ϣ
struct CMD_CS_ListInfo
{
	DWORD								dwTypeCount;					//������Ŀ
	DWORD								dwKindCount;					//������Ŀ
	DWORD								dwServerCount;					//������Ŀ
	DWORD								dwStationCount;					//վ����Ŀ
};

//
//�������������
//

#define MDM_CS_SERVER_MANAGER			2								//�������

#define SUB_CS_REG_GAME_SERVER			1								//ע�᷿��
#define SUB_CS_UNREG_GAME_SERVER		2								//ע������
#define SUB_CS_SERVER_ONLINE_COUNT		3								//��������
#define SUB_CS_CREATE_SELF_REQ			4								//���󴴽��Խ���
#define SUB_CS_CREATE_SELF_REP			5								//�����Խ������
#define SUB_CS_QUERY_SELF_REQ			6								//�����ѯ�Խ���
#define SUB_CS_QUERY_SELF_REP			7								//��ѯ�Խ������
#define SUB_CS_CHECK_PWD_SELF_REQ		8								//�����Խ���У������
#define SUB_CS_CHECK_PWD_SELF_REP		9								//�Խ���У��������
#define SUB_CS_SPEAKER_SEND_MSG_REQ		10								//����������Ϣ
#define SUB_CS_CREATE_FRIEND_REQ		11								//���󴴽����ѷ�
#define SUB_CS_CREATE_FRIEND_REP		12								//�������ѷ����
#define SUB_CS_ENTER_FRIEND_REQ			13								//���������ѷ�
#define SUB_CS_ENTER_FRIEND_REP			14								//������ѷ����
#define SUB_CS_QUERY_FRIEND_ROOMID_REQ			15						//��ѯ���ѷ�
#define SUB_CS_QUERY_FRIEND_ROOMID_REP			16						//��ѯ���ѷ����
#define SUB_CS_QUERY_NORMAL_ROOMID_REQ			17						//��ѯ��ͨ��
#define SUB_CS_QUERY_NORMAL_ROOMID_REP			18						//��ѯ��ͨ�����


//ע�᷿��
struct CMD_CS_RegGameServer
{
	tagGameServer						GameServer;						//������Ϣ
};

//ע������
struct CMD_CS_UnRegGameServer
{
	WORD								wKindID;						//���ƺ���
	WORD								wServerID;						//�������
};

//��������
struct CMD_CS_ServerOnLineCount
{
	WORD								wKindID;						//���ƺ���
	WORD								wServerID;						//�������
	DWORD								dwOnLineCount;					//��������
};
//�����ѯ���ѷ�
struct CMD_CS_QueryFriend
{
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	char								cType;						//��ѯ�����ԭ��1����Ϊ�Զ���¼����
	WORD								wKindID;					//kindid
	DWORD								dwUserID;					//�û�
	DWORD								dwRoomID;					//����ID
	char								szRule[512];				//���ò���:��ֵ�ԣ�������̫��
	WORD								wCenterID;					//���õ����ķ�����
	WORD								wCount;						//��ѯ����
};

//��ѯ���ѷ����
struct CMD_CS_QueryFriendRep
{
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	char								cType;						//��ѯ�����ԭ��1����Ϊ�Զ���¼����
	WORD								wKindID;					//kindid
	char								nCode;						//���
	DWORD								dwUserID;					//�û�
	DWORD								dwUserIDFangZhu;			//�����û�
	DWORD								dwRoomID;					//����ID
	WORD								wServerID;					//��ϷID
	WORD								wTableID;					//����ID
	char								szRule[512];				//���ò���:��ֵ�ԣ�������̫��
	WORD								wCenterID;					//���õ����ķ�����
	WORD								wCount;						//��ѯ����
};

//���󴴽����ѷ�
struct CMD_CS_CreateFriend
{
	WORD								wType;						//�����������ͣ�0����ͨ������1�������˿���
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	DWORD								dwUserID;					//�û�
	WORD								wKindID;					//��Ϸ����
	DWORD								dwRoomID;					//�����ķ���������
	char								szRule[512];				//���ò���:��ֵ�ԣ�������̫��
	WORD								wCenterID;					//���õ����ķ�����
	WORD								wCount;						//��ѯ����
	WORD								wRoomCount;
	WORD								wVesion;					//�ɰ��������, ��Ĭ�ϣ�1Ϊ�ɰ汾��0Ϊ�°汾
};

//�������ѷ����
struct CMD_CS_CreateFriendRep
{
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	unsigned short						nCode;						//���
	DWORD								dwUserID;					//�û�
	DWORD								nRoomID;					//RoomID
	unsigned short						nServerID;					//����ID
	unsigned short						nTableID;					//����ID
	char								szName[NAME_LEN];			//��������
	char								szRoomID[NAME_LEN];			//����ΨһID
	char								szRule[512];				//���ò���:��ֵ�ԣ�������̫��
	WORD								wCenterID;					//���õ����ķ�����
	WORD								wCount;						//��ѯ����
	WORD								wKindID;					//��Ϸ����
};

//���������ѷ�
struct CMD_CS_EnterFriend
{
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	char								cType;						//��ѯ�����ԭ��1����Ϊ�Զ���¼����
	DWORD								dwUserID;					//�û�
	unsigned short						nServerID;					//����ID
	char								szRoomID[NAME_LEN];			//����ΨһID
	char								szPassword[PASS_LEN];		//����
};

//������ѷ����
struct CMD_CS_EnterFriendRep
{
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	char								cType;						//��ѯ�����ԭ��1����Ϊ�Զ���¼����
	unsigned short						nCode;						//���
	DWORD								dwUserID;					//�û�
	DWORD								dwFangzhuID;				//����ID
	unsigned short						nServerID;					//����ID
	unsigned short						nTableID;					//����
	char								szRoomID[NAME_LEN];			//����ΨһID
	char								szRule[512];				//���ò���:��ֵ�ԣ�������̫��
	WORD								wKindID;					//kindid
	unsigned short						uJushu;						// ����
};

//���󴴽��Խ���
struct CMD_CS_CreateSelf
{
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	unsigned short						nServerID;					//����ID
	char								szName[NAME_LEN];			//��������
	char								szPassword[PASS_LEN];		//����
	char								szRule[128];				//���ò���:��ֵ�ԣ�������̫��
};

//�����Խ������
struct CMD_CS_CreateSelfRep
{
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	unsigned short						nCode;						//���
	unsigned short						nServerID;					//����ID
	char								szName[NAME_LEN];			//��������
	char								szRoomID[NAME_LEN];			//����ΨһID
	char								szRule[128];				//���ò���:��ֵ�ԣ�������̫��
};

//����У�鷿������
struct CMD_CS_CheckPwdSelf
{
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	unsigned short						nServerID;					//����ID
	char								szRoomID[NAME_LEN];			//����ΨһID
	char								szPassword[PASS_LEN];		//����
};

//����У�鷿��������
struct CMD_CS_CheckPwdSelfRep
{
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	unsigned short						nCode;						//���
	unsigned short						nServerID;					//����ID
	char								szRoomID[NAME_LEN];			//����ΨһID
};

//�����ѯ�Խ���
struct CMD_CS_QuerySelf
{
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	unsigned short						nServerID;					//��ϷID
	unsigned short						nPage;						//��ҳ������0��ʼ��ÿҳ���������ɷ���˿���
	char								szName[NAME_LEN];			//�������ƣ�ģ����ѯ����
	char								szRoomID[NAME_LEN];			//�����ţ�ģ����ѯ����
	char								szFilter[128];				//��չ�Ĳ�ѯ����:��ֵ�ԣ�������̫��
};

//��ѯ�Խ������
struct CMD_CS_QuerySelfRep
{
	DWORD								dwSocketID;					//LoginServer������ʶ�ͻ���
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	unsigned short						nCode;						//���
	unsigned short						nServerID;					//����ID
	unsigned short						nPage;						//ҳ��
	unsigned short						nTotal;						//�ܵļ�¼����
	unsigned short						nCount;						//���ص�ʵ�ʼ�¼��������಻�ܳ���10��
	char								szName[10][NAME_LEN];		//�������ơ�������������Ϊ�����б����ַ�
	char								szExtend[640];				//���Ӳ�������ʽ��id:1,c:100,m:3000,x:20000,k:1|id:2,m:100,x:20000|id:5,m:200,x:20000,k:1
																	//id��ʾ���ӱ�ʶ��cΪ��Ԫ���֣�mΪ��С�Ƹ���xΪ���Ƹ���kΪ�Ƿ�������
};

//�����ѯ��ͨ����������
struct CMD_CS_NormalRoomQuery
{
	DWORD								dwSocketIDLogin;			//CenterServer������ʶLoginServer
	DWORD								dwUserID;					//�û�
	unsigned short						sServerID;					//����ID
	unsigned short						sTableID;					//����ID
	unsigned short						sChairID;					//����ID
	unsigned short						sData1;						//��������1
	int									nData2;						//��������2
	int									nData3;						//��������3
};

//������������Ϣ
struct CMD_CS_SpeakerSendMsgReq
{
	unsigned short						nType;					//��Ϣ����
	unsigned short						nLen;					//��Ϣ����
	char								szMsg[256];				//��Ϣ����
};

//
//����������
//

#define MDM_CS_CONTROL_COMMAND			3								//��������
#define SUB_CS_CONTROL_COMMAND_REQ		1								//��������
#define SUB_CS_CONTROL_COMMAND_REP		2								//������Ӧ

struct CMD_CS_ControlCommandReq
{
	WORD								wCommandID;						//������
	DWORD								dwServerID;						//����ID
	DWORD								dwUserID;						//�û�
	TCHAR								szParam[128];					//����
};

struct CMD_CS_ControlCommandRep
{
	WORD								wCommandID;						//������
	WORD								wCode;							//����״̬
	DWORD								dwServerID;						//����ID
	DWORD								dwUserID;						//�û�
	TCHAR								szResult[128];					//����
};

#endif


//-----------------------------------------------
//					the end
//-----------------------------------------------
