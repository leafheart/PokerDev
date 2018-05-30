#ifndef CMD_PLAZA_HEAD_FILE
#define CMD_PLAZA_HEAD_FILE

#include "biostream.h"

#include "GlobalDef.h"

//////////////////////////////////////////////////////////////////////////

//�㳡�汾
#define VER_PLAZA_LOW					1								//�㳡�汾
#define VER_PLAZA_HIGH					1								//�㳡�汾
#define VER_PLAZA_FRAME					MAKELONG(VER_PLAZA_LOW,VER_PLAZA_HIGH)

//////////////////////////////////////////////////////////////////////////
//��¼�����ʶ

#define ERC_GP_LOGON_SUCCESS			0								//��½�ɹ�
#define ERC_GP_ACCOUNTS_NOT_EXIST		1								//�ʺŲ�����
#define ERC_GP_LONG_NULLITY				2								//��ֹ��¼
#define ERC_GP_PASSWORD_ERCOR			3								//�������

//////////////////////////////////////////////////////////////////////////
//��¼������

#define MDM_GP_LOGON					1								//�㳡��¼

#define SUB_GP_LOGON_ACCOUNTS			1								//�ʺŵ�¼
#define SUB_GP_LOGON_USERID				2								//I D ��¼
#define SUB_GP_REGISTER_ACCOUNTS		3								//ע���ʺ�
#define SUB_GP_UPLOAD_CUSTOM_FACE		4								//����ͷ��

#define SUB_GP_REGISTER_ACCOUNTS_V2		7								//ע���ʺ�
#define SUB_GP_LOGON_WX					8								//΢��
#define SUB_GP_HEART_BEAT				10								//����

#define SUB_GP_LOGON_SUCCESS			100								//��½�ɹ�
#define SUB_GP_LOGON_ERROR				101								//��½ʧ��
#define SUB_GP_LOGON_FINISH				102								//��½���

#define SUB_GP_LOGON_SUCCESS_V2			103								//��½�ɹ� //V1.21�汾��������
#define SUB_GP_LOGON_SUCCESS_V3			104								//��¼�ɹ�
#define SUB_GP_LOGON_ACCOUNTS_V2		5								//�ʺŵ�¼
#define SUB_GP_LOGON_SUCCESS_V4			105								//��¼�ɹ�

//΢����Ϣ��¼
struct CMD_GP_LogonByWX
{
	enum { M_ID = MDM_GP_LOGON };
	enum { S_ID = SUB_GP_LOGON_WX };
	unsigned int						dwPlazaVersion;					//�㳡�汾
	char								cSex;							//�Ա�
	unsigned short						cUrlSize;						//URL����
	char								szFaceUrl[256];					//ͷ���ַ
	char								szSpreader[NAME_LEN];			//�ƹ�����
	char								szNickName[NAME_LEN];			//�ǳ�
	char								szOpenID[32];					//΢��Ψһ��ʶ
	char								szUnionID[64];					//΢��Ψһ��ʶ
	char								szAccounts[NAME_LEN];			//��¼�ʺ�
	char								szPassWord[PASS_LEN];			//��¼����
	char								szComputerID[COMPUTER_ID_LEN];			//Ӳ����ʶ
	char								szMachineSerialID[COMPUTER_ID_LEN];		//�ο�Ӳ����ʶ


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_LogonByWX() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_LogonByWX& pl)
	{
		bos << pl.dwPlazaVersion;
		bos << pl.cSex;
		bos << pl.cUrlSize;

		bos.write((char*)pl.szFaceUrl, pl.cUrlSize);
		bos.write((char*)pl.szSpreader, sizeof(pl.szSpreader));
		bos.write((char*)pl.szNickName, sizeof(pl.szNickName));
		bos.write((char*)pl.szOpenID, sizeof(pl.szOpenID));
		bos.write((char*)pl.szUnionID, sizeof(pl.szUnionID));
		bos.write((char*)pl.szAccounts, sizeof(pl.szAccounts));
		bos.write((char*)pl.szPassWord, sizeof(pl.szPassWord));
		bos.write((char*)pl.szComputerID, sizeof(pl.szComputerID));
		bos.write((char*)pl.szMachineSerialID, sizeof(pl.szMachineSerialID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_LogonByWX& pl)
	{
		pl.reset();
		bis >> pl.dwPlazaVersion;
		bis >> pl.cSex;
		bis >> pl.cUrlSize;

		bis.read((char*)pl.szFaceUrl, pl.cUrlSize);
		bis.read((char*)pl.szSpreader, sizeof(pl.szSpreader));
		bis.read((char*)pl.szNickName, sizeof(pl.szNickName));
		bis.read((char*)pl.szOpenID, sizeof(pl.szOpenID));
		bis.read((char*)pl.szUnionID, sizeof(pl.szUnionID));
		bis.read((char*)pl.szAccounts, sizeof(pl.szAccounts));
		bis.read((char*)pl.szPassWord, sizeof(pl.szPassWord));
		bis.read((char*)pl.szComputerID, sizeof(pl.szComputerID));
		bis.read((char*)pl.szMachineSerialID, sizeof(pl.szMachineSerialID));

		return bis;
	}
};
//�ʺŵ�¼
struct CMD_GP_LogonByAccounts_CB
{
	enum {M_ID = MDM_GP_LOGON};
	enum {S_ID = SUB_GP_LOGON_ACCOUNTS};
	unsigned int						dwPlazaVersion;					//�㳡�汾
	char								szAccounts[NAME_LEN];			//��¼�ʺ�
	char								szPassWord[PASS_LEN];			//��¼����
	char								szComputerID[COMPUTER_ID_LEN];			//Ӳ����ʶ
	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_LogonByAccounts_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_LogonByAccounts_CB& pl)
	{
		bos << pl.dwPlazaVersion;

		bos.write((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bos.write((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_LogonByAccounts_CB& pl)
	{	
		pl.reset();
		bis >> pl.dwPlazaVersion;

		bis.read((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bis.read((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bis;
	}
};

//�ʺŵ�¼
struct CMD_GP_LogonByAccounts_CB_V2
{
	enum {M_ID = MDM_GP_LOGON};
	enum {S_ID = SUB_GP_LOGON_ACCOUNTS_V2};
	unsigned int						dwPlazaVersion;					//�㳡�汾
	char								szAccounts[NAME_LEN];			//��¼�ʺ�
	char								szPassWord[PASS_LEN];			//��¼����
	char								szComputerID[COMPUTER_ID_LEN];			//Ӳ����ʶ


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_LogonByAccounts_CB_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_LogonByAccounts_CB_V2& pl)
	{
		bos << pl.dwPlazaVersion;

		bos.write((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bos.write((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_LogonByAccounts_CB_V2& pl)
	{	
		pl.reset();
		bis >> pl.dwPlazaVersion;

		bis.read((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bis.read((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bis;
	}
};

//I D ��¼
struct CMD_GP_LogonByUserID_CB
{
	enum {M_ID = MDM_GP_LOGON};
	enum {S_ID = SUB_GP_LOGON_USERID};

	unsigned int						dwPlazaVersion;					//�㳡�汾
	unsigned int						dwUserID;						//�û� I D
	char								szPassWord[PASS_LEN];			//��¼����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_LogonByUserID_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_LogonByUserID_CB& pl)
	{
		bos << pl.dwPlazaVersion;
		bos << pl.dwUserID;

		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_LogonByUserID_CB& pl)
	{	
		pl.reset();
		bis >> pl.dwPlazaVersion;
		bis >> pl.dwUserID;

		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));

		return bis;
	}
};

//ע���ʺ�
struct CMD_GP_RegisterAccounts_CB
{
	enum {M_ID = MDM_GP_LOGON};
	enum {S_ID = SUB_GP_REGISTER_ACCOUNTS_V2};

	unsigned short						wFaceID;						//ͷ���ʶ
	unsigned char						cbGender;						//�û��Ա�
	unsigned int						dwPlazaVersion;					//�㳡�汾
	char								szSpreader[NAME_LEN];			//�ƹ�����
	char								szAccounts[NAME_LEN];			//��¼�ʺ�
	char								szPassWord[PASS_LEN];			//��¼����
	char								szComputerID[COMPUTER_ID_LEN];			//Ӳ����ʶ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_RegisterAccounts_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_RegisterAccounts_CB& pl)
	{
		bos << pl.wFaceID;
		bos << pl.cbGender;
		bos << pl.dwPlazaVersion;

		bos.write((char*)pl.szSpreader,sizeof(pl.szSpreader));
		bos.write((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bos.write((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_RegisterAccounts_CB& pl)
	{	
		pl.reset();
		bis >> pl.wFaceID;
		bis >> pl.cbGender;
		bis >> pl.dwPlazaVersion;

		bis.read((char*)pl.szSpreader,sizeof(pl.szSpreader));
		bis.read((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bis.read((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bis;
	}
};

//��½�ɹ�
struct CMD_GP_LogonSuccess_CB
{
	enum {M_ID = MDM_GP_LOGON};
	enum {S_ID = SUB_GP_LOGON_SUCCESS};

	char										szAccounts[NAME_LEN];			//�ο�ע��ʱ���ص�¼�ʺ�
	char										szNickName[NAME_LEN];			//�����ǳ�
	char										szPassWord[PASS_LEN];			//�ο�ע��ʱ�������ĵ�¼����

	unsigned short								wFaceID;						//ͷ������
	unsigned char								cbGender;						//�û��Ա�
	unsigned char								cbIsGuest;						//�Ƿ��ο�
	unsigned char								cbMember;						//��Ա�ȼ�
	unsigned int								dwUserID;						//�û� I D
	unsigned int								dwGameID;						//��Ϸ I D
	unsigned int								dwExperience;					//�û�����
	unsigned int								dwGoldScore;					//�û��Ƹ�
	int											lWelfare;						//�û��ͱ�
	unsigned short								wWelfareLost;					//�û��ͱ�ʣ�����
	
	//��չ��Ϣ
	unsigned int								dwCustomFaceVer;				//ͷ��汾

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_LogonSuccess_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_LogonSuccess_CB& pl)
	{

		bos.write((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));
		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));

		bos << pl.wFaceID;
		bos << pl.cbGender;
		bos << pl.cbIsGuest;
		bos << pl.cbMember;
		bos << pl.dwUserID;
		bos << pl.dwGameID;
		bos << pl.dwExperience;
		bos << pl.dwGoldScore;
		bos << pl.lWelfare;
		bos << pl.wWelfareLost;
		bos << pl.dwCustomFaceVer;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_LogonSuccess_CB& pl)
	{	
		pl.reset(); 


		bis.read((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));
		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));

		bis >> pl.wFaceID;
		bis >> pl.cbGender;
		bis >> pl.cbIsGuest;
		bis >> pl.cbMember;
		bis >> pl.dwUserID;
		bis >> pl.dwGameID;
		bis >> pl.dwExperience;
		bis >> pl.dwGoldScore;
		bis >> pl.lWelfare;
		bis >> pl.wWelfareLost;
		bis >> pl.dwCustomFaceVer;

		return bis;
	}
};


//��½�ɹ�
struct CMD_GP_LogonSuccess_CB_V2
{
	enum {M_ID = MDM_GP_LOGON};
	enum {S_ID = SUB_GP_LOGON_SUCCESS_V2};

	char										szAccounts[NAME_LEN];			//�ο�ע��ʱ���ص�¼�ʺ�
	char										szNickName[NAME_LEN];			//�����ǳ�
	char										szPassWord[PASS_LEN];			//�ο�ע��ʱ�������ĵ�¼����

	unsigned short								wFaceID;						//ͷ������
	unsigned char								cbGender;						//�û��Ա�
	unsigned char								cbIsGuest;						//�Ƿ��ο�
	unsigned char								cbMember;						//��Ա�ȼ�
	unsigned int								dwUserID;						//�û� I D
	unsigned int								dwGameID;						//��Ϸ I D
	unsigned int								dwExperience;					//�û�����
	unsigned int								dwGoldScore;					//�û��Ƹ�
	int											lWelfare;						//�û��ͱ�
	unsigned short								wWelfareLost;					//�û��ͱ�ʣ�����
	char										szDescribeInfo[128];			//����ǩ����Ϣ
	//��չ��Ϣ
	unsigned int								dwCustomFaceVer;				//ͷ��汾

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_LogonSuccess_CB_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_LogonSuccess_CB_V2& pl)
	{

		bos.write((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));
		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));

		bos << pl.wFaceID;
		bos << pl.cbGender;
		bos << pl.cbIsGuest;
		bos << pl.cbMember;
		bos << pl.dwUserID;
		bos << pl.dwGameID;
		bos << pl.dwExperience;
		bos << pl.dwGoldScore;
		bos << pl.lWelfare;
		bos << pl.wWelfareLost;
		bos.write((char*)pl.szDescribeInfo,sizeof(pl.szDescribeInfo));
		bos << pl.dwCustomFaceVer;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_LogonSuccess_CB_V2& pl)
	{	
		pl.reset(); 


		bis.read((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));
		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));

		bis >> pl.wFaceID;
		bis >> pl.cbGender;
		bis >> pl.cbIsGuest;
		bis >> pl.cbMember;
		bis >> pl.dwUserID;
		bis >> pl.dwGameID;
		bis >> pl.dwExperience;
		bis >> pl.dwGoldScore;
		bis >> pl.lWelfare;
		bis >> pl.wWelfareLost;
		bis.read((char*)pl.szDescribeInfo,sizeof(pl.szDescribeInfo));
		bis >> pl.dwCustomFaceVer;

		return bis;
	}
};

//��½�ɹ�
struct CMD_GP_LogonSuccess_CB_V3
{
	enum {M_ID = MDM_GP_LOGON};
	enum {S_ID = SUB_GP_LOGON_SUCCESS_V3};

	char										szAccounts[NAME_LEN];			//�ο�ע��ʱ���ص�¼�ʺ�
	char										szNickName[NAME_LEN];			//�����ǳ�
	char										szPassWord[PASS_LEN];			//�ο�ע��ʱ�������ĵ�¼����

	unsigned short								wFaceID;						//ͷ������
	unsigned char								cbGender;						//�û��Ա�
	unsigned char								cbIsGuest;						//�Ƿ��ο�
	unsigned char								cbMember;						//��Ա�ȼ�
	unsigned int								dwUserID;						//�û� I D
	unsigned int								dwGameID;						//��Ϸ I D
	unsigned int								dwExperience;					//�û�����
	unsigned int								dwGoldScore;					//�û��Ƹ�
	int											lWelfare;						//�û��ͱ�
	unsigned short								wWelfareLost;					//�û��ͱ�ʣ�����
	char										szDescribeInfo[128];			//����ǩ����Ϣ
	//��չ��Ϣ
	unsigned int								dwCustomFaceVer;				//ͷ��汾
	unsigned int								dwFankaScore;					//��������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_LogonSuccess_CB_V3() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_LogonSuccess_CB_V3& pl)
	{

		bos.write((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));
		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));

		bos << pl.wFaceID;
		bos << pl.cbGender;
		bos << pl.cbIsGuest;
		bos << pl.cbMember;
		bos << pl.dwUserID;
		bos << pl.dwGameID;
		bos << pl.dwExperience;
		bos << pl.dwGoldScore;
		bos << pl.lWelfare;
		bos << pl.wWelfareLost;
		bos.write((char*)pl.szDescribeInfo,sizeof(pl.szDescribeInfo));
		bos << pl.dwCustomFaceVer;
		bos << pl.dwFankaScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_LogonSuccess_CB_V3& pl)
	{	
		pl.reset(); 


		bis.read((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));
		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));

		bis >> pl.wFaceID;
		bis >> pl.cbGender;
		bis >> pl.cbIsGuest;
		bis >> pl.cbMember;
		bis >> pl.dwUserID;
		bis >> pl.dwGameID;
		bis >> pl.dwExperience;
		bis >> pl.dwGoldScore;
		bis >> pl.lWelfare;
		bis >> pl.wWelfareLost;
		bis.read((char*)pl.szDescribeInfo,sizeof(pl.szDescribeInfo));
		bis >> pl.dwCustomFaceVer;
		bis >> pl.dwFankaScore;

		return bis;
	}
};

//��½�ɹ�
struct CMD_GP_LogonSuccess_CB_V4
{
	enum {M_ID = MDM_GP_LOGON};
	enum {S_ID = SUB_GP_LOGON_SUCCESS_V4};

	char										szAccounts[NAME_LEN];			//�ο�ע��ʱ���ص�¼�ʺ�
	char										szNickName[NAME_LEN];			//�����ǳ�
	char										szPassWord[PASS_LEN];			//�ο�ע��ʱ�������ĵ�¼����

	unsigned short								wFaceID;						//ͷ������
	unsigned char								cbGender;						//�û��Ա�
	unsigned char								cbIsGuest;						//�Ƿ��ο�
	unsigned char								cbMember;						//��Ա�ȼ�
	unsigned int								dwUserID;						//�û� I D
	unsigned int								dwGameID;						//��Ϸ I D
	unsigned int								dwExperience;					//�û�����
	unsigned int								dwGoldScore;					//�û��Ƹ�
	int											lWelfare;						//�û��ͱ�
	unsigned short								wWelfareLost;					//�û��ͱ�ʣ�����
	char										szDescribeInfo[128];			//����ǩ����Ϣ
	//��չ��Ϣ
	unsigned int								dwCustomFaceVer;				//ͷ��汾
	unsigned int								dwFankaScore;					//��������
	unsigned short								wIsNewGuest;					//�Ƿ������ο�,1Ϊ���ο�0Ϊ���ο�
	unsigned short								wIsBuyPoChan;					//�Ƿ����Ʋ����,1Ϊ����0Ϊδ����
	unsigned int								wBuyPoChanCount;				//�����˹������Ʋ����
	unsigned int								wPoChanFlag;					//�Ʋ���ʶ,0����δ�Ʋ�1�����Ʋ�

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_LogonSuccess_CB_V4() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_LogonSuccess_CB_V4& pl)
	{

		bos.write((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));
		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));

		bos << pl.wFaceID;
		bos << pl.cbGender;
		bos << pl.cbIsGuest;
		bos << pl.cbMember;
		bos << pl.dwUserID;
		bos << pl.dwGameID;
		bos << pl.dwExperience;
		bos << pl.dwGoldScore;
		bos << pl.lWelfare;
		bos << pl.wWelfareLost;
		bos.write((char*)pl.szDescribeInfo,sizeof(pl.szDescribeInfo));
		bos << pl.dwCustomFaceVer;
		bos << pl.dwFankaScore;
		bos << pl.wIsNewGuest;
		bos << pl.wBuyPoChanCount;
		bos << pl.wIsBuyPoChan;
		bos << pl.wPoChanFlag;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_LogonSuccess_CB_V4& pl)
	{	
		pl.reset(); 


		bis.read((char*)pl.szAccounts,sizeof(pl.szAccounts));
		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));
		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));

		bis >> pl.wFaceID;
		bis >> pl.cbGender;
		bis >> pl.cbIsGuest;
		bis >> pl.cbMember;
		bis >> pl.dwUserID;
		bis >> pl.dwGameID;
		bis >> pl.dwExperience;
		bis >> pl.dwGoldScore;
		bis >> pl.lWelfare;
		bis >> pl.wWelfareLost;
		bis.read((char*)pl.szDescribeInfo,sizeof(pl.szDescribeInfo));
		bis >> pl.dwCustomFaceVer;
		bis >> pl.dwFankaScore;
		bis >> pl.wIsNewGuest;
		bis >> pl.wBuyPoChanCount;
		bis >> pl.wIsBuyPoChan;
		bis >> pl.wPoChanFlag;

		return bis;
	}
};

//��½ʧ��
struct CMD_GP_LogonError_CB
{
	enum {M_ID = MDM_GP_LOGON};
	enum {S_ID = SUB_GP_LOGON_ERROR};

	int								lErrorCode;						//�������
	char							szErrorDescribe[128];			//������Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_LogonError_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_LogonError_CB& pl)
	{
		bos << pl.lErrorCode;

		bos.write((char*)pl.szErrorDescribe,sizeof(pl.szErrorDescribe));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_LogonError_CB& pl)
	{	
		pl.reset();
		bis >> pl.lErrorCode;

		bis.read((char*)pl.szErrorDescribe,sizeof(pl.szErrorDescribe));

		return bis;
	}
};

//////////////////////////////////////////////////////////////////////////
//��Ϸ�б�������

#define MDM_GP_SERVER_LIST				2								//�б���Ϣ

#define SUB_GP_LIST_TYPE				100								//�����б�
#define SUB_GP_LIST_KIND				101								//�����б�
#define SUB_GP_LIST_STATION				102								//վ���б�
#define SUB_GP_LIST_SERVER				103								//�����б�
#define SUB_GP_LIST_FINISH				104								//�������
#define SUB_GP_LIST_CONFIG				105								//�б�����
#define SUB_GP_CREATE_SELF_REQ			106								//���󴴽��Խ���
#define SUB_GP_CREATE_SELF_REP			107								//�����Խ������
#define SUB_GP_QUERY_SELF_REQ			108								//�����ѯ�Խ���
#define SUB_GP_QUERY_SELF_REP			109								//��ѯ�Խ������
#define SUB_GP_CHECK_PWD_SELF_REQ		110								//�����Խ���У������
#define SUB_GP_CHECK_PWD_SELF_REP		111								//�Խ���У��������
#define SUB_GP_LIST_CONFIG_V2			112								//�б�����

#define SUB_GP_CREATE_FRIEND_REQ		120								//���󴴽����ѷ�
#define SUB_GP_CREATE_FRIEND_REP		121								//�������ѷ����
#define SUB_GP_ENTER_FRIEND_REQ			122								//���������ѷ�
#define SUB_GP_ENTER_FRIEND_REP			123								//������ѷ����

#define SUB_GP_CREATE_OTHER_FRIEND_REQ			124								//���뿪��
#define SUB_GP_CREATE_VIP_FRIEND_REQ			125								//VIP���뿪��


//���󴴽����ѷ�
struct CMD_GP_CreateFriend
{
	enum { M_ID = MDM_GP_SERVER_LIST };
	enum { S_ID = SUB_GP_CREATE_FRIEND_REQ };

	unsigned short						nKindID;					//��Ϸ����
	unsigned short						nRoomCount;					//��������
	unsigned short						nLen;						//���򳤶�
	char								szRule[512];				//���ò���:��ֵ�ԣ�������̫��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CreateFriend() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_CreateFriend& pl)
	{
		bos << pl.nKindID;
		bos << pl.nRoomCount;
		bos << pl.nLen;

		bos.write((char*)pl.szRule, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_CreateFriend& pl)
	{
		pl.reset();
		bis >> pl.nKindID;
		bis >> pl.nRoomCount;
		bis >> pl.nLen;

		bis.read((char*)pl.szRule, pl.nLen);

		return bis;
	}
};

//���󴴽����ѷ�
struct CMD_GP_CreateVIPFriend
{
	enum { M_ID = MDM_GP_SERVER_LIST };
	enum { S_ID = SUB_GP_CREATE_VIP_FRIEND_REQ };

	unsigned short						nKindID;					//��Ϸ����
	unsigned short						nRoomCount;					//��������
	unsigned short						nLen;						//���򳤶�
	char								szRule[512];				//���ò���:��ֵ�ԣ�������̫��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CreateVIPFriend() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_CreateVIPFriend& pl)
	{
		bos << pl.nKindID;
		bos << pl.nRoomCount;
		bos << pl.nLen;

		bos.write((char*)pl.szRule, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_CreateVIPFriend& pl)
	{
		pl.reset();
		bis >> pl.nKindID;
		bis >> pl.nRoomCount;
		bis >> pl.nLen;

		bis.read((char*)pl.szRule, pl.nLen);

		return bis;
	}
};

//���󿪷�
struct CMD_GP_CreateOtherFriend
{
	enum { M_ID = MDM_GP_SERVER_LIST };
	enum { S_ID = SUB_GP_CREATE_OTHER_FRIEND_REQ };

	unsigned short						nKindID;					//��Ϸ����
	unsigned short						nRoomCount;					//��������
	unsigned short						nLen;						//���򳤶�
	char								szRule[512];				//���ò���:��ֵ�ԣ�������̫��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CreateOtherFriend() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_CreateOtherFriend& pl)
	{
		bos << pl.nKindID;
		bos << pl.nRoomCount;
		bos << pl.nLen;

		bos.write((char*)pl.szRule, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_CreateOtherFriend& pl)
	{
		pl.reset();
		bis >> pl.nKindID;
		bis >> pl.nRoomCount;
		bis >> pl.nLen;

		bis.read((char*)pl.szRule, pl.nLen);

		return bis;
	}
};

//�������ѷ����
struct CMD_GP_CreateFriendRep
{
	enum { M_ID = MDM_GP_SERVER_LIST };
	enum { S_ID = SUB_GP_CREATE_FRIEND_REP };

	unsigned short						nCode;					//���0���ɹ��� 1��ʧ�ܣ� 2���û����ڷ�����
	unsigned int						dwUserID;				//����id
	unsigned short						nServerID;				//����ID
	unsigned short						nTableID;				//����
	char								szRoomID[NAME_LEN];		//����ΨһID
	unsigned short						nLen;					//���򳤶�
	char								szRule[512];			//���ò���:��ֵ�ԣ�������̫��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CreateFriendRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_CreateFriendRep& pl)
	{
		bos << pl.nCode;
		bos << pl.dwUserID;
		bos << pl.nServerID;
		bos << pl.nTableID;

		bos.write((char*)pl.szRoomID, sizeof(pl.szRoomID));

		bos << pl.nLen;
		bos.write((char*)pl.szRule, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_CreateFriendRep& pl)
	{
		pl.reset();
		bis >> pl.nCode;
		bis >> pl.dwUserID;
		bis >> pl.nServerID;
		bis >> pl.nTableID;

		bis.read((char*)pl.szRoomID, sizeof(pl.szRoomID));

		bis >> pl.nLen;
		bis.read((char*)pl.szRule, pl.nLen);

		return bis;
	}
};


//���������ѷ�
struct CMD_GP_EnterFriend
{
	enum { M_ID = MDM_GP_SERVER_LIST };
	enum { S_ID = SUB_GP_ENTER_FRIEND_REQ };

	char								szRoomID[NAME_LEN];			//����ΨһID
	char								szPassword[PASS_LEN];		//����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_EnterFriend() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_EnterFriend& pl)
	{
		bos.write((char*)pl.szRoomID, sizeof(pl.szRoomID));
		bos.write((char*)pl.szPassword, sizeof(pl.szPassword));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_EnterFriend& pl)
	{
		pl.reset();

		bis.read((char*)pl.szRoomID, sizeof(pl.szRoomID));
		bis.read((char*)pl.szPassword, sizeof(pl.szPassword));

		return bis;
	}
};

//������ѷ����
struct CMD_GP_EnterFriendRep
{
	enum { M_ID = MDM_GP_SERVER_LIST };
	enum { S_ID = SUB_GP_ENTER_FRIEND_REP };

	unsigned short						nCode;					//���0���ɹ��� 1��ʧ�ܣ� 2���û����ڷ�����
	char								cType;					//��ʾ��Ϣ�ķ����ߡ�1����ʾΪ��¼��̨�Զ�����
	unsigned int						dwUserID;				//����id
	unsigned short						nServerID;				//����ID
	unsigned short						nTableID;				//����
	char								szRoomID[NAME_LEN];		//����ΨһID
	unsigned short						nLen;					//���򳤶�
	char								szRule[512];			//���ò���:��ֵ�ԣ�������̫��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_EnterFriendRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_EnterFriendRep& pl)
	{
		bos << pl.nCode;
		bos << pl.cType;
		bos << pl.dwUserID;
		bos << pl.nServerID;
		bos << pl.nTableID;

		bos.write((char*)pl.szRoomID, sizeof(pl.szRoomID));
		bos << pl.nLen;
		bos.write((char*)pl.szRule, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_EnterFriendRep& pl)
	{
		pl.reset();
		bis >> pl.nCode;
		bis >> pl.cType;
		bis >> pl.dwUserID;
		bis >> pl.nServerID;
		bis >> pl.nTableID;

		bis.read((char*)pl.szRoomID, sizeof(pl.szRoomID));
		bis >> pl.nLen;
		bis.read((char*)pl.szRule, pl.nLen);

		return bis;
	}
};


//���󴴽��Խ���
struct CMD_GP_CreateSelf
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_CREATE_SELF_REQ};

	unsigned short						nServerID;					//����ID
	char								szName[NAME_LEN];			//��������
	char								szPassword[PASS_LEN];		//����
	char								szRule[128];				//���ò���:��ֵ�ԣ�������̫��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CreateSelf() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_CreateSelf& pl)
	{
		bos << pl.nServerID;

		bos.write((char*)pl.szName,sizeof(pl.szName));
		bos.write((char*)pl.szPassword,sizeof(pl.szPassword));
		bos.write((char*)pl.szRule,sizeof(pl.szRule));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_CreateSelf& pl)
	{	
		pl.reset();
		bis >> pl.nServerID;

		bis.read((char*)pl.szName,sizeof(pl.szName));
		bis.read((char*)pl.szPassword,sizeof(pl.szPassword));
		bis.read((char*)pl.szRule,sizeof(pl.szRule));

		return bis;
	}
};

//�����Խ������
struct CMD_GP_CreateSelfRep
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_CREATE_SELF_REP};

	unsigned short						nCode;					//���
	unsigned short						nServerID;				//����ID
	char								szName[NAME_LEN];		//��������
	char								szRoomID[NAME_LEN];		//����ΨһID
	char								szRule[128];			//���ò���:��ֵ�ԣ�������̫��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CreateSelfRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_CreateSelfRep& pl)
	{
		bos << pl.nCode;
		bos << pl.nServerID;

		bos.write((char*)pl.szName,sizeof(pl.szName));
		bos.write((char*)pl.szRoomID,sizeof(pl.szRoomID));
		bos.write((char*)pl.szRule,sizeof(pl.szRule));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_CreateSelfRep& pl)
	{	
		pl.reset();
		bis >> pl.nCode;
		bis >> pl.nServerID;

		bis.read((char*)pl.szName,sizeof(pl.szName));
		bis.read((char*)pl.szRoomID,sizeof(pl.szRoomID));
		bis.read((char*)pl.szRule,sizeof(pl.szRule));

		return bis;
	}
};

//����У�鷿������
struct CMD_GP_CheckPwdSelf
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_CHECK_PWD_SELF_REQ};

	unsigned short						nServerID;					//����ID
	char								szRoomID[NAME_LEN];			//����ΨһID
	char								szPassword[PASS_LEN];		//����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CheckPwdSelf() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_CheckPwdSelf& pl)
	{
		bos << pl.nServerID;

		bos.write((char*)pl.szRoomID,sizeof(pl.szRoomID));
		bos.write((char*)pl.szPassword,sizeof(pl.szPassword));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_CheckPwdSelf& pl)
	{	
		pl.reset();
		bis >> pl.nServerID;

		bis.read((char*)pl.szRoomID,sizeof(pl.szRoomID));
		bis.read((char*)pl.szPassword,sizeof(pl.szPassword));

		return bis;
	}
};

//����У�鷿��������
struct CMD_GP_CheckPwdSelfRep
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_CHECK_PWD_SELF_REP};

	unsigned short						nCode;						//���
	unsigned short						nServerID;					//����ID
	char								szRoomID[NAME_LEN];			//����ΨһID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CheckPwdSelfRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_CheckPwdSelfRep& pl)
	{
		bos << pl.nCode;
		bos << pl.nServerID;

		bos.write((char*)pl.szRoomID,sizeof(pl.szRoomID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_CheckPwdSelfRep& pl)
	{	
		pl.reset();
		bis >> pl.nCode;
		bis >> pl.nServerID;

		bis.read((char*)pl.szRoomID,sizeof(pl.szRoomID));

		return bis;
	}
};

//�����ѯ�Խ���
struct CMD_GP_QuerySelf
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_QUERY_SELF_REQ};

	unsigned short						nServerID;					//��ϷID
	unsigned short						nPage;						//��ҳ������0��ʼ��ÿҳ���������ɷ���˿���
	char								szName[NAME_LEN];			//�������ƣ�ģ����ѯ����
	char								szRoomID[NAME_LEN];			//�����ţ�ģ����ѯ����
	char								szFilter[128];				//��չ�Ĳ�ѯ����:��ֵ�ԣ�������̫��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_QuerySelf() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_QuerySelf& pl)
	{
		bos << pl.nServerID;
		bos << pl.nPage;

		bos.write((char*)pl.szName,sizeof(pl.szName));
		bos.write((char*)pl.szRoomID,sizeof(pl.szRoomID));
		bos.write((char*)pl.szFilter,sizeof(pl.szFilter));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_QuerySelf& pl)
	{	
		pl.reset();
		bis >> pl.nServerID;
		bis >> pl.nPage;

		bis.read((char*)pl.szName,sizeof(pl.szName));
		bis.read((char*)pl.szRoomID,sizeof(pl.szRoomID));
		bis.read((char*)pl.szFilter,sizeof(pl.szFilter));

		return bis;
	}
};

//��ѯ�Խ������
struct CMD_GP_QuerySelfRep
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_QUERY_SELF_REP};

	unsigned short						nCode;					//���
	unsigned short						nServerID;				//����ID
	unsigned short						nPage;					//ҳ��
	unsigned short						nTotal;						//�ܵļ�¼����
	unsigned short						nCount;					//���ص�ʵ�ʼ�¼��������಻�ܳ���10��
	char								szName[10][NAME_LEN];	//�������ơ�������������Ϊ�����б����ַ�
	char								szExtend[640];			//���Ӳ�������ʽ��id:1,min:100,max:20000,key:1|id:2,min:100,max:20000,key:0|id:5,min:200,max:20000,key:1
																//��|�ָ���ͬ�ķ��䣬�ö��ŷָ���ͬ������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_QuerySelfRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_QuerySelfRep& pl)
	{
		bos << pl.nCode;
		bos << pl.nServerID;
		bos << pl.nPage;
		bos << pl.nTotal;
		bos << pl.nCount;

		bos.write((char*)pl.szName,sizeof(pl.szName));
		bos.write((char*)pl.szExtend,sizeof(pl.szExtend));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_QuerySelfRep& pl)
	{	
		pl.reset();
		bis >> pl.nCode;
		bis >> pl.nServerID;
		bis >> pl.nPage;
		bis >> pl.nTotal;
		bis >> pl.nCount;

		bis.read((char*)pl.szName,sizeof(pl.szName));
		bis.read((char*)pl.szExtend,sizeof(pl.szExtend));

		return bis;
	}
};

//�б�����
struct CMD_GP_ListConfig_CB
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_LIST_CONFIG};

	unsigned char						bShowOnLineCount;		//��ʾ����
	char								szRule[512];			//���ò�����Ŀǰ��΢�ŷ�������ǩ����ÿ���������ã��ƹ�

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_ListConfig_CB() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_ListConfig_CB& pl)
	{
		bos << pl.bShowOnLineCount;

		bos.write((char*)pl.szRule,sizeof(pl.szRule));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_ListConfig_CB& pl)
	{	
		pl.reset();
		bis >> pl.bShowOnLineCount;

		bis.read((char*)pl.szRule,sizeof(pl.szRule));

		return bis;
	}
};

//�б�����
struct CMD_GP_ListConfig_CB_V2
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_LIST_CONFIG_V2};
	
	char								szRule[2048];			//���ò�����Ŀǰ��΢�ŷ�������ǩ����ÿ���������ã��ƹ�

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_ListConfig_CB_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_ListConfig_CB_V2& pl)
	{
		bos.write((char*)pl.szRule,sizeof(pl.szRule));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_ListConfig_CB_V2& pl)
	{	
		pl.reset();

		bis.read((char*)pl.szRule,sizeof(pl.szRule));

		return bis;
	}
};
//////////////////////////////////////////////////////////////////////////



//��Ϸ���ͽṹ
struct tagGameType
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_LIST_TYPE};

	unsigned short								wSortID;							//�������
	unsigned short								wTypeID;							//�������
	char								szTypeName[TYPE_LEN];				//��������

	void reset() { memset(this, 0, sizeof(*this)); }
	tagGameType() { reset(); }
	friend bostream& operator<<(bostream& bos,const tagGameType& pl)
	{
		bos << pl.wSortID;
		bos << pl.wTypeID;

		bos.write((char*)pl.szTypeName,sizeof(pl.szTypeName));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,tagGameType& pl)
	{	
		pl.reset();
		bis >> pl.wSortID;
		bis >> pl.wTypeID;

		bis.read((char*)pl.szTypeName,sizeof(pl.szTypeName));

		return bis;
	}
};

//��Ϸ���ƽṹ
struct tagGameKind
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_LIST_KIND};

	unsigned short								wSortID;							//�������
	unsigned short								wTypeID;							//���ͺ���
	unsigned short								wKindID;							//���ƺ���
	unsigned int								dwMaxVersion;						//���°汾
	unsigned int								dwOnLineCount;						//������Ŀ
	char								szKindName[KIND_LEN];				//��Ϸ����
	char								szProcessName[MODULE_LEN];			//��������

	void reset() { memset(this, 0, sizeof(*this)); }
	tagGameKind() { reset(); }
	friend bostream& operator<<(bostream& bos,const tagGameKind& pl)
	{
		bos << pl.wSortID;
		bos << pl.wTypeID;
		bos << pl.wKindID;
		bos << pl.dwMaxVersion;
		bos << pl.dwOnLineCount;

		bos.write((char*)pl.szKindName,sizeof(pl.szKindName));
		bos.write((char*)pl.szProcessName,sizeof(pl.szProcessName));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,tagGameKind& pl)
	{	
		pl.reset();
		bis >> pl.wSortID;
		bis >> pl.wTypeID;
		bis >> pl.wKindID;
		bis >> pl.dwMaxVersion;
		bis >> pl.dwOnLineCount;

		bis.read((char*)pl.szKindName,sizeof(pl.szKindName));
		bis.read((char*)pl.szProcessName,sizeof(pl.szProcessName));

		return bis;
	}
};

//��Ϸվ��ṹ
struct tagGameStation
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_LIST_STATION};

	unsigned short								wSortID;							//�������
	unsigned short								wKindID;							//���ƺ���
	unsigned short								wJoinID;							//�ҽӺ���
	unsigned short								wStationID;							//վ�����
	char								szStationName[STATION_LEN];			//վ������

	void reset() { memset(this, 0, sizeof(*this)); }
	tagGameStation() { reset(); }
	friend bostream& operator<<(bostream& bos,const tagGameStation& pl)
	{
		bos << pl.wSortID;
		bos << pl.wKindID;
		bos << pl.wJoinID;
		bos << pl.wStationID;

		bos.write((char*)pl.szStationName,sizeof(pl.szStationName));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,tagGameStation& pl)
	{	
		pl.reset();
		bis >> pl.wSortID;
		bis >> pl.wKindID;
		bis >> pl.wJoinID;
		bis >> pl.wStationID;

		bis.read((char*)pl.szStationName,sizeof(pl.szStationName));

		return bis;
	}
};

//��Ϸ�����б�ṹ
struct tagGameServer
{
	enum {M_ID = MDM_GP_SERVER_LIST};
	enum {S_ID = SUB_GP_LIST_SERVER};

	unsigned short								wSortID;							//�������
	unsigned short								wKindID;							//���ƺ���
	unsigned short								wServerID;							//�������
	unsigned short								wStationID;							//վ�����
	unsigned int								dwOnLineCount;						//��������
	unsigned short								wServerPort;						//����˿�
	unsigned int								dwServerAddr;						//�����ַ
	char								szServerAddr[SERVER_LEN];			//�����ַ
	char								szServerName[SERVER_LEN];			//��������
	char								szRule[128];				//��������

	void reset() { memset(this, 0, sizeof(*this)); }
	tagGameServer() { reset(); }
	friend bostream& operator<<(bostream& bos,const tagGameServer& pl)
	{
		bos << pl.wSortID;
		bos << pl.wKindID;
		bos << pl.wServerID;
		bos << pl.wStationID;
		bos << pl.wServerPort;
		bos << pl.dwServerAddr;
		bos << pl.dwOnLineCount;

		bos.write((char*)pl.szServerAddr,sizeof(pl.szServerAddr));
		bos.write((char*)pl.szServerName,sizeof(pl.szServerName));
		bos.write((char*)pl.szRule,sizeof(pl.szRule));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,tagGameServer& pl)
	{	
		pl.reset();
		bis >> pl.wSortID;
		bis >> pl.wKindID;
		bis >> pl.wServerID;
		bis >> pl.wStationID;
		bis >> pl.wServerPort;
		bis >> pl.dwServerAddr;
		bis >> pl.dwOnLineCount;

		bis.read((char*)pl.szServerAddr,sizeof(pl.szServerAddr));
		bis.read((char*)pl.szServerName,sizeof(pl.szServerName));
		bis.read((char*)pl.szRule,sizeof(pl.szRule));

		return bis;
	}
};

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//ϵͳ������

#define MDM_GP_SYSTEM					3								//ϵͳ����

#define SUB_GP_VERSION					100								//�汾֪ͨ
//#define SUB_SP_SYSTEM_MSG				101								//ϵͳ��Ϣ

//�汾֪ͨ
struct CMD_GP_Version
{
	enum {M_ID = MDM_GP_SYSTEM};
	enum {S_ID = SUB_GP_VERSION};

	unsigned char								bNewVersion;					//���°汾
	unsigned char								bAllowConnect;					//��������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_Version() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_Version& pl)
	{
		bos << pl.bNewVersion;
		bos << pl.bAllowConnect;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_Version& pl)
	{	
		pl.reset();
		bis >> pl.bNewVersion;
		bis >> pl.bAllowConnect;

		return bis;
	}
};

//////////////////////////////////////////////////////////////////////////

#define MDM_GP_USER						4								//�û���Ϣ

#define SUB_GP_USER_UPLOAD_FACE			100								//�ϴ�ͷ��
#define SUB_GP_USER_DOWNLOAD_FACE		101								//����ͷ��
#define SUB_GP_UPLOAD_FACE_RESULT		102								//�ϴ����
#define SUB_GP_DELETE_FACE_RESULT		103								//ɾ�����
#define SUB_GP_CUSTOM_FACE_DELETE		104								//ɾ��ͷ��
#define SUB_GP_MODIFY_INDIVIDUAL		105								//��������
#define SUB_GP_MODIFY_INDIVIDUAL_RESULT	106								//�޸Ľ��

#define SUB_GP_CHECK_ID_REQ				107								//У��ID
#define SUB_GP_CHECK_ID_REP				108								//У��ID���
#define SUB_GP_CHECK_NICKNAME_REQ		109								//У���ǳ�
#define SUB_GP_CHECK_NICKNAME_REP		110								//У���ǳƽ��
#define SUB_GP_REGISTER_REQ				111								//ע��
#define SUB_GP_REGISTER_REP				112								//ע����
#define SUB_GP_ID_UPDATE_REQ			113								//�˺�����
#define SUB_GP_ID_UPDATE_REP			114								//�˺��������
#define SUB_GP_RESET_PWD_REQ			115								//��������
#define SUB_GP_RESET_PWD_REP			116								//����������
#define SUB_GP_USER_INFO_REQ			117								//��ѯ�û���Ϣ
#define SUB_GP_USER_INFO_REP			118								//��ѯ�û���Ϣ���
#define SUB_GP_REGISTER_CHANNEL_REQ		119								//ע��--��������

#define SUB_GP_MODIFY_DESCRIBE_INFO		120									//�޸ĸ���ǩ��
//#define SUB_GP_MODIFY_DESCRIBE_INFO_RESULT	121								//�޸�ǩ�����

#define SUB_GP_USER_SIGNIN				200								//ǩ����Ϣ
#define SUB_GP_USER_SIGNIN_REQ			201								//ǩ������
#define SUB_GP_USER_GETAWARD			202								//�콱��Ϣ
#define SUB_GP_USER_GETAWARD_REQ		203								//�콱����

#define SUB_GP_USER_CAN_SPREAD_REQ		204								//��ѯ�û��Ƿ������ƹ㽱��
#define SUB_GP_USER_CAN_SPREAD_REP		205								//��ѯ�û��Ƿ������ƹ㽱�����
#define SUB_GP_USER_GET_SPREAD_REQ		206								//�û����ƹ㽱��
#define SUB_GP_USER_GET_SPREAD_REP		207								//�û����ƹ㽱�����
#define SUB_GP_USER_SPREADER_INFO_REQ	208								//��ѯ�ƹ���Ϣ
#define SUB_GP_USER_SPREADER_INFO_REP	209								//��ѯ�ƹ���Ϣ���

#define SUB_GP_USER_BBS_POP_REQ			210								//���������ѯ
#define SUB_GP_USER_BBS_POP_REP			211								//����������Ϣ���
#define SUB_GP_USER_BBS_SCROLL_REQ		212								//���������ѯ
#define SUB_GP_USER_BBS_SCROLL_REP		213								//����������Ϣ���
#define SUB_GP_USER_BBS_LIST_REQ		214								//�б����ѯ
#define SUB_GP_USER_BBS_LIST_REP		215								//�б�����Ϣ���
#define SUB_GP_USER_BBS_POP_REQ_V2		230								//���������ѯV2
#define SUB_GP_USER_BBS_SCROLL_REQ_V2	231								//���������ѯV2
#define SUB_GP_USER_BBS_LIST_REQ_V2		232								//�б����ѯV2

#define SUB_GP_USER_TASK_INFO_REQ		216								//���������Ϣ��ѯ
#define SUB_GP_USER_TASK_INFO_REP		217								//���������Ϣ���

#define SUB_GP_USER_RANKING_REQ					220							//������а��ѯ
#define SUB_GP_USER_RANKING_RECORD				221							//������а���ϸ
#define SUB_GP_USER_RANKING_RECORD_FINISH		222							//������а����

#define SUB_GP_USER_RANKING_REQ_V2					235							//������а��ѯ
#define SUB_GP_USER_RANKING_RECORD_V2				236							//������а���ϸ

#define SUB_GP_USER_FEEDBACK_REQ				223							//�ύ���ⷴ��
#define SUB_GP_USER_FEEDBACK_REP				224							//�ύ���ⷴ�����
#define SUB_GP_USER_GET_FEEDBACK_REQ			225							//��ѯ���ⷴ��
#define SUB_GP_USER_FEEDBACK_RECORD				226							//��ѯ���ⷴ����ϸ
#define SUB_GP_USER_FEEDBACK_RECORD_FINISH		227							//��ѯ���ⷴ������

#define SUB_GP_USER_EXCHANGE_INFO				300							//�һ�������Ϣ�����ؽ𶹡��ֻ��ţ�
#define SUB_GP_USER_EXCHANGE_INFO_REQ			301							//�һ�������Ϣ���󣨲�ѯ�𶹡��ֻ��š������ֻ��ţ�
#define SUB_GP_USER_EXCHANGE_PRODUCT			302							//�һ���Ʒ�б� 
#define SUB_GP_USER_EXCHANGE_PRODUCT_REQ		303							//�һ���Ʒ��ѯ����
#define SUB_GP_USER_EXCHANGE_PRODUCT_FINISH		304							//�һ���Ʒ�б����
#define SUB_GP_USER_EXCHANGE					305							//�һ���Ʒ�б� 
#define SUB_GP_USER_EXCHANGE_REQ				306							//�һ���Ʒ��ѯ����
#define SUB_GP_USER_EXCHANGE_RECORD				307							//�һ���¼�б� 
#define SUB_GP_USER_EXCHANGE_RECORD_REQ			308							//�һ���¼��ѯ����
#define SUB_GP_USER_EXCHANGE_RECORD_FINISH		309							//�һ���¼�б����

#define SUB_GP_USER_EXCHANGE_PRODUCT_REQ_V2		340							//�һ���Ʒ��ѯ����v2
#define SUB_GP_USER_EXCHANGE_PRODUCT_V2			341							//�һ���Ʒ�б� V2
#define SUB_GP_USER_EXCHANGE_REQ_V2				342							//�һ���Ʒ��ѯ����V2
#define SUB_GP_USER_EXCHANGE_V2					343							//�һ���Ʒ�б� V2

#define SUB_GP_USER_INFO_ID_CARD_REQ			310							//��ѯ�û����֤�˺���Ϣ
#define SUB_GP_USER_INFO_ID_CARD_REP			311							//��ѯ�û����֤�˺���Ϣ���

#define SUB_GP_USER_AUTHENTICA_REQ				312
#define SUB_GP_USER_AUTHENTICA_REP				313

#define SUB_GP_USER_MODIFY_RANKINGSTATUS		314							//��������Ƿ������а�
#define SUB_GP_USER_REP_MODIFY_RANKINGSTATUS	315							//��������Ƿ������а񷵻���Ϣ���
#define SUB_GP_USER_REP_RANKINGSTATUS			316							//����Ƿ������а���Ϣ���

#define SUB_GP_USER_MALL_PRODUCT_REQ			317							//�̳���Ʒ����
#define SUB_GP_USER_MALL_PRODUCT_RESP			318							//�̳���Ʒ�б�
#define SUB_GP_USER_MALL_PRODUCT_RESP_FINISH	319							//�̳���Ʒ�б����
#define SUB_GP_USER_MALL_PLACE_ORDER_REQ		320							//������Ʒ�¶�������
#define SUB_GP_USER_MALL_PLACE_ORDER_RESP		321							//������Ʒ�¶������ؽ��
#define SUB_GP_USER_CANCEL_ORDER_REQ			322							//ȡ������������
#define SUB_GP_USER_CANCEL_ORDER_REP			323							//ȡ���������
#define SUB_GP_USER_MALL_BUY_REQ				324							//��������Ʒ���
#define SUB_GP_USER_MALL_BUY_RESP				325							//������Ʒ���
#define SUB_GP_USER_MALL_UPDATE_REQ				326							//��������Ʒ���
#define SUB_GP_USER_MALL_UPDATE_RESP			327							//������Ʒ���
#define SUB_GP_USER_MALL_PRODUCT_REQ_IOS		328							//�̳���Ʒ����

#define SUB_GP_USER_BANK_INFO_REQ				330							//��ѯ�û�������Ϣ
#define SUB_GP_USER_BANK_INFO_REP				331							//��ѯ�û�������Ϣ���
#define SUB_GP_USER_BANK_CHARGE_REQ				332							//�û�������������
#define SUB_GP_USER_BANK_CHARGE_REP				333							//�û���������������


#define SUB_GP_USER_MALL_PRODUCT_REQ_V2			360							//�̳���Ʒ����
#define SUB_GP_USER_MALL_PRODUCT_RESP_V2		361							//�̳���Ʒ�б�

#define SUB_GP_USER_ACTIVITY_LIST_REQ			350							//��ѯ��б���Ϣ
#define SUB_GP_USER_ACTIVITY_LIST_REP			351							//��ѯ��б���Ϣ���
#define SUB_GP_USER_ACTIVITY_REQ				352							//��ѯָ�����Ϣ
#define SUB_GP_USER_ACTIVITY_REP				353							//��ѯָ�����Ϣ���
#define SUB_GP_USER_ACTIVITY_LUCKY_REQ			354							//��齱
#define SUB_GP_USER_ACTIVITY_LUCKY_REP			355							//��齱���
#define SUB_GP_USER_ACTIVITY_RECORD				356							//�н���¼�б� 
#define SUB_GP_USER_ACTIVITY_RECORD_REQ			357							//�н���¼��ѯ����
#define SUB_GP_USER_ACTIVITY_RECORD_FINISH		358							//�н���¼�б����

#define SUB_GP_USER_SEND_LABA_REQ				362							//����������
#define SUB_GP_USER_SEND_LABA_REP				363							//���������Ƚ��

#define SUB_GP_USER_CHECK_LABA_REQ				364							//����У����������
#define SUB_GP_USER_CHECK_LABA_REP				365							//У�����Ƚ��

#define SUB_GP_USER_SPEAKER_MSG_REP				366							//���յ�������Ϣ

#define SUB_GP_USER_QUERY_CONFIG_REQ			368							//��ѯĳ������
#define SUB_GP_USER_QUERY_CONFIG_REP			369							//����ĳ������

#define SUB_GP_USER_MALL_ComBo_RESP				375							//�̳�VIP�ײͽ��

#define SUB_GP_USER_MALL_ComBo_FINISH			376							//�̳���Ʒ�б����


#define SUB_GR_USER_VIP_REQ				382							//����VIP
#define SUB_GR_USER_VIP_REP				383							//VIP���

#define SUB_GR_USER_REST_FLEE_REQ		384							// ��������
#define SUB_GR_USER_REST_FLEE_REP		385							// ������

#define SUB_GP_USER_FRIEND_RESULT_REQ				470						//����ս�����а��ѯ
#define SUB_GP_USER_FRIEND_RESULT_RECORD			471						//����ս�����а��¼
#define SUB_GP_USER_FRIEND_RESULT_RECORD_FINISH		472						//����ս�����а����
#define SUB_GP_USER_FRIEND_RESULT_DETAIL_REQ		473						//����ս�����η����ѯ
#define SUB_GP_USER_FRIEND_RESULT_DETAIL_REP		474						//����ս�����η����ѯ���
#define SUB_GP_USER_FRIEND_RESULT_DETAIL_REQ_V2		475						//����ս�����η����ѯ
#define SUB_GP_USER_FRIEND_RESULT_DETAIL_REP_V2		476						//����ս�����η����ѯ���(���ӷ������ֶ�)

#define SUB_GP_USER_FRIEND_RESULT_REPLAY_REQ			477						//���䵥�ֻطż�¼��ѯ����
#define SUB_GP_USER_FRIEND_RESULT_REPLAY_USER_REP		478						//���䵥�ֻطż�¼��ѯ������û���Ϣ
#define SUB_GP_USER_FRIEND_RESULT_REPLAY_RULE_REP		479						//���䵥�ֻطż�¼��ѯ�������������
#define SUB_GP_USER_FRIEND_RESULT_REPLAY_REP			480						//���䵥�ֻطż�¼��ѯ��������ƹ���

#define SUB_GP_USER_OTHER_FRIEND_RESULT_REQ				481					//�˵����ݲ�ѯ
#define SUB_GP_USER_OTHER_FRIEND_RESULT_REP				482					//�˵����ݲ�ѯ�ص�
#define SUB_GP_USER_OTHER_FRIEND_RESULT_RECORD_FINISH	483					//��ѯ����

#define SUB_GP_USER_OTHER_FRIEND_RESULT_DETAIL_REQ		484					//�����˵�
#define SUB_GP_USER_OTHER_FRIEND_RESULT_DETAIL_REP		485					//�����˵��ص�

#define SUB_GP_USER_HONGBAO_RESULT_GET_REQ				486					//��ȡ���
#define SUB_GP_USER_HONGBAO_RESULT_GET_REP				487					//��ȡ����ص�


#define SUB_GP_USER_HONGBAO_RESULT_GET_DETAIL_REQ				488					//��ȡ�����¼
#define SUB_GP_USER_HONGBAO_RESULT_GET_DETAIL_REP				489					//��ȡ�����¼�ص�
#define SUB_GP_USER_HONGBAO_RESULT_GET_DETAIL_FINISH			500

#define SUB_GP_USER_HONGBAO_RESULT_OTHER_GET_DETAIL_REQ				501					//������ȡ�����¼
#define SUB_GP_USER_HONGBAO_RESULT_OTHER_GET_DETAIL_REP				502					//������ȡ�����¼�ص�
#define SUB_GP_USER_HONGBAO_RESULT_OTHER_GET_DETAIL_FINISH			503					//������ȡ�����¼�ص�

#define SUB_GP_USER_HONGBAO_RESULT_REWAED_REQ				504					//����н���¼
#define SUB_GP_USER_HONGBAO_RESULT_REWAED_REP				505					//����н���¼�ص�
#define SUB_GP_USER_HONGBAO_RESULT_REWAED_FINISH			506					//����н���¼�ص�

#define SUB_GP_USER_HONGBAO_ACTIVITY_REQ				507					//����״̬
#define SUB_GP_USER_HONGBAO_ACTIVITY_REP				508					//����״̬�ص�

#define SUB_SP_USER_FENX_ACTIVITY_REQ				509					//��������
#define SUB_SP_USER_FENX_ACTIVITY_REP				510					//�������

#define SUB_SP_USER_FENX_ACTIVITY_DETAIL_REQ				511					//�����б�����
#define SUB_SP_USER_FENX_ACTIVITY_DETAIL_REP				512					//�����б���
#define SUB_SP_USER_FENX_ACTIVITY_DETAIL_FINISH				513					//�����б���

#define SUB_SP_USER_FENX_ACTIVITY_OTHER_DETAIL_REQ				514					//���˷����б�����
#define SUB_SP_USER_FENX_ACTIVITY_OTHER_DETAIL_REP				515					//���˷����б���
#define SUB_SP_USER_FENX_ACTIVITY_OTHER_DETAIL_FINISH				516					//���˷����б���

#define SUB_GP_USER_FENX_RESULT_GET_REQ				517					//��ȡ�����
#define SUB_GP_USER_FENX_RESULT_GET_REP				518					//��ȡ�����ص�

#define SUB_GP_USER_FENX_ACTIVITY_REQ				519					//�齱���ݲ�ѯ
#define SUB_GP_USER_FENX_ACTIVITY_REP				520					//�齱���ݲ�ѯ

#define SUB_GP_USER_PAY_ORDER_REQ					521					//�Ƿ�󶨺ϻ���
#define SUB_GP_USER_PAY_ORDER_REP					522					//�Ƿ��

#define SUB_GP_USER_PAY_ORDER_SEND_REQ				523					//�󶨺ϻ���
#define	SUB_GP_USER_PAY_ORDER_SEND_REP				524					//�󶨺ϻ���

#define SUB_GP_USER_PARTNER_REP						526					//VIP��Ϣ

#define SUB_GP_USER_UESER_STATUS_REQ					527					//�����Ϣ����
#define SUB_GP_USER_UESER_STATUS_REP					528					//�����Ϣ�ص�

#define SUB_GP_USER_UESER_STATUS_REP_2					529					//�Ƿ�����֤

#define SUB_GP_USER_PHONE_INFO_CHANGE					530					//�����ֻ��û�����

#define SUB_GP_USER_MALL_FANKA_ORDER_RESP				531					//�����һ�

#define SUB_GP_USER_PHONE_FACEURL_INFO					532					//��ȡ�ֻ��û�ͷ������

#define SUB_GP_USER_GAMEROOM_LOCKER_INFO					533					//��ͳ���Զ����뷿��

#define SUB_GP_USER_WELFARE_REQ							534					//�û���ȡ�ͱ�
#define SUB_GP_USER_WELFARE_REP							535					//�û���ȡ�ͱ��ص�


#define SUB_GP_USER_ACTION_COUNT_REQ				536						//ͳ������
#define SUB_GP_USER_ACTION_COUNT_REP				537						//ͳ����Ӧ

#define SUB_GP_CHECK_CHANGE_NICKNAME_REQ			538						//�޸��ǳƼ������
#define SUB_GP_CHECK_CHANGE_NICKNAME_REP			539						//�޸��ǳƼ����Ӧ

#define SUB_GP_USER_SEND_WONDERFUL_REQ          700                    //��ȡ���ʻ����
#define SUB_GP_USER_SEND_WONDERFUL_REP          701                    //��ȡ���ʻ���൥��
#define SUB_GP_USER_SEND_WONDERFUL_FINISH       702                    //��ȡ���ʻ����������

#define SUB_GP_USER_GET_WONDERFUL_ITEM_REQ      703                    //��ȡ���ʻ���������С��
#define SUB_GP_USER_GET_WONDERFUL_ITEM_REP      704                    //���ʻ���������С���
#define SUB_GP_USER_GET_WONDERFUL_ITEM_FINISH   705                    //���ʻ���������С��ؽ�����־

#define SUB_GP_USER_GET_WONDERFUL_AWARD_REQ      706                    //��ȡ��������
#define SUB_GP_USER_GET_WONDERFUL_AWARD_REP      707                    //��ȡ�������

#define SUB_GP_USER_GET_WONDERFUL_NOTICE_REQ     708                    //��ȡ���ʻ��������
#define SUB_GP_USER_GET_WONDERFUL_NOTICE_REP     709                    //��ȡ���ʻ���淵�ؽ��    
#define SUB_GP_USER_GET_WONDERFUL_FINISH         710                    //���ʻ����������

struct CMD_GR_Wonderfull_NoticeReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_GET_WONDERFUL_NOTICE_REQ };
	int dwUserid;           //���ID

	void reset() { memset(this, 0, sizeof(*this));}
	friend bostream& operator<<(bostream& bos, const CMD_GR_Wonderfull_NoticeReq& pl)
	{
		bos << pl.dwUserid;
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_Wonderfull_NoticeReq& pl)
	{
		pl.reset();
		bis >> pl.dwUserid;
		return bis;
	}
};

struct CMD_GR_Wonderfull_NoticeRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_GET_WONDERFUL_NOTICE_REP };
	enum {TEXT=0,PHOTO};
	enum {TO_URL=0,TO_ROOM,TO_CREATEROOM,TO_SHOP};

	int  index;				//����
	char tagTitle[32];     //ҳǩ����(��ť�ϵ�����)
	char noticeTitle[32];   //�������
	char noticeContex[512]; //�������ݣ���������ֹ����������������ֹ���,�����ͼƬ�����������ͼƬ��ַ��
	int  noticeType;		//�������� 0�����ֹ��棬1��ͼƬ����
	int  functionType;      //ͼƬ����������������0��ʾ��ת����ַ 1��ת��ĳ�������淨 2��ת�����ѷ����� 3��ת���̳� ��ͼƬ������Ҫ����������������ֶ�������
	int  kind;              //��functionType=TO_ROOMʱ���ֶα�ʾ��ת���ķ����KINDID ����������ֶ������壬������
	char linkUrl[32];		//��functionType=TO_URLʱ��ʾ��ת����ҳ ����������ֶ�������,�������
	int huobao;             //0�� 1�ǻ�
	int addNew;             //0������ 1����
	int sequenceIndex;      //��������

	void reset() { memset(this, 0, sizeof(*this)); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_Wonderfull_NoticeRep& pl)
	{
		bos << pl.index;
		bos.write((char*)pl.tagTitle, sizeof(pl.tagTitle));
		bos.write((char*)pl.noticeTitle, sizeof(pl.noticeTitle));
		bos.write((char*)pl.noticeContex, sizeof(pl.noticeContex));
		bos << pl.noticeType;
		bos << pl.functionType;
		bos.write((char*)pl.linkUrl, sizeof(pl.linkUrl));
		bos << pl.huobao;
		bos << pl.addNew;
		bos << pl.sequenceIndex;
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_Wonderfull_NoticeRep& pl)
	{
		pl.reset();
		bis >> pl.index;
		bis.read((char*)pl.tagTitle, sizeof(pl.tagTitle));
		bis.read((char*)pl.noticeTitle, sizeof(pl.noticeTitle));
		bis.read((char*)pl.noticeContex, sizeof(pl.noticeContex));
		bis >> pl.noticeType;
		bis >> pl.functionType;
		bis.read((char*)pl.linkUrl, sizeof(pl.linkUrl));
		bis >> pl.huobao;
		bis >> pl.addNew;
		bis >> pl.sequenceIndex;
		return bis;
	}
};

struct CMD_GR_Wonderfull_NoticeFinish
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_GET_WONDERFUL_FINISH };
	enum {SUCC,ERROR_1};
	unsigned short sCode;
	int len; // һ���ж��ٸ�

	void reset() { memset(this, 0, sizeof(*this)); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_Wonderfull_NoticeFinish& pl)
	{
		bos << pl.sCode;
		bos << pl.len;
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_Wonderfull_NoticeFinish& pl)
	{
		pl.reset();
		bis >> pl.sCode;
		bis >> pl.len;
		return bis;
	}
};

struct CMD_GR_Wonderfull_award_req
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_GET_WONDERFUL_AWARD_REQ };

	int wonderfullItemId;   //��ȡ�����ĵ�������ֵ
	int WonderFulId;        //���ʻ����ID
	int dwUserid;           //���ID

	void reset() { memset(this, 0, sizeof(*this));}
	friend bostream& operator<<(bostream& bos, const CMD_GR_Wonderfull_award_req& pl)
	{
		bos << pl.wonderfullItemId;
		bos << pl.WonderFulId;
		bos << pl.dwUserid;
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_Wonderfull_award_req& pl)
	{
		pl.reset();
		bis >> pl.wonderfullItemId;
		bis >> pl.WonderFulId;
		bis >> pl.dwUserid;
		return bis;
	}
};

struct CMD_GR_Wonderfull_award_rep
{
	enum{SUCC=0,ERROR_1,ERROR_2,ERROR_3,ERROR_4,ERROR_5,ERROR_6};  //0�ɹ� 1û��������ID 2û������ 3��ѹر�  4�������Чʱ�䷶Χ  5���ý������͸������������ݲ�ƥ�� 6�Ѿ���ȡ����������������ظ���ȡ
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_GET_WONDERFUL_AWARD_REQ };

	unsigned short sCode;  //�ɹ���ʱ��Ž�����������ݣ�ʧ���������������ݶ�����Ч��
	int huanledou;   //���ֶ� -1��ʾû�л��ֶ����� ��-1��ʾ�л��ֶ����������ص�����ҵ�ǰ���콱�Ժ�Ļ��ֶ�����
	int fangka;      //����   -1��ʾû�з������� ��-1��ʾ�з������������ص�����ҵ�ǰ���콱�Ժ�ķ�������
	int gold;        //��   -1��ʾû�н𶹽��� ��-1��ʾ�з������������ص�����ҵ�ǰ���콱�Ժ�ķ�������
	int laba;        //��������
	int wonderfullItemId;   //��ȡ�����ĵ�������ֵ
	int WonderFulId;        //���ʻ����ID
	char vipEndTime[32]; //VIPʱ�� strlen()����0��ʾû��VIP�������ܿ��¿��� ������0���Ǹ��º�Ľ�ֹʱ��
	char awardTypeStr[64];
	char awardNumStr[128];

	void reset() { memset(this, 0, sizeof(*this));}
	friend bostream& operator<<(bostream& bos, const CMD_GR_Wonderfull_award_rep& pl)
	{
		bos << pl.sCode;
		bos << pl.huanledou;
		bos << pl.fangka;
		bos << pl.gold;
		bos << pl.laba;
		bos << pl.wonderfullItemId;
		bos << pl.WonderFulId;
		bos.write((char*)pl.vipEndTime, sizeof(pl.vipEndTime));
		bos.write((char*)pl.awardTypeStr, sizeof(pl.awardTypeStr));
		bos.write((char*)pl.awardNumStr, sizeof(pl.awardNumStr));
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_Wonderfull_award_rep& pl)
	{
		pl.reset();
		bis >> pl.sCode;
		bis >> pl.huanledou;
		bis >> pl.fangka;
		bis >> pl.gold;
		bis >> pl.laba;
		bis >> pl.wonderfullItemId;
		bis >> pl.WonderFulId;
		bis.read((char*)pl.vipEndTime, sizeof(pl.vipEndTime));
		bis.read((char*)pl.awardTypeStr, sizeof(pl.awardTypeStr));
		bis.read((char*)pl.awardNumStr, sizeof(pl.awardNumStr));
		return bis;
	}
};


//�ǳ��޸�У������
struct CMD_GP_CheckChangeNickNameReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_CHECK_CHANGE_NICKNAME_REQ};

	unsigned int					dwUserID;		//��� ID	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CheckChangeNickNameReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_CheckChangeNickNameReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_CheckChangeNickNameReq& pl)
	{	
		pl.reset();

		bis >> pl.dwUserID;
		return bis;
	}
};

//�ǳ��޸�У��������
struct CMD_GP_CheckChangeNickNameRep
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_CHECK_CHANGE_NICKNAME_REP};

	short			nCode;					//���0����ɹ�1����ʧ��
	unsigned int	dwUserID;				//�û�ID
	unsigned int	nIsFree;				//�Ƿ����,0�����1���
	unsigned int	dwGoldScore;			//�޸��ǳ���Ҫ֧������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CheckChangeNickNameRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_CheckChangeNickNameRep& pl)
	{
		bos << pl.nCode;
		bos << pl.dwUserID;
		bos << pl.nIsFree;
		bos << pl.dwGoldScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_CheckChangeNickNameRep& pl)
	{	
		pl.reset();

		bis >> pl.nCode;
		bis >> pl.dwUserID;
		bis >> pl.nIsFree;
		bis >> pl.dwGoldScore;
		return bis;
	}
};

struct CMD_GP_UserActionCount_Req //ͳ������
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_ACTION_COUNT_REQ};

	enum {
		ACTIONCOUNT_CHANGENICKNAME = 1,	//�޸��ǳư�ť
		ACTIONCOUNT_UNDOCHANGE,			//�޸��ǳƷ������İ�ť
		ACTIONCOUNT_LOBBYACTIVITY,		//��������ť
		ACTIONCOUNT_WONDERFULACTIVITY,	//���ʻ��ť
		ACTIONCOUNT_GAMENOTICE,			//��Ϸ���水ť
		ACTIONCOUNT_EXIT_POP			//�˳���������һ�°�ť
	};

	unsigned int							dwUserId;//�û�ID
	unsigned int							dwCountId;//ͳ��ID

	void reset() { memset(this, 0, sizeof(*this)); }  
	CMD_GP_UserActionCount_Req() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserActionCount_Req& pl)
	{
		bos << pl.dwUserId;
		bos << pl.dwCountId;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserActionCount_Req& pl)
	{
		pl.reset();
		bis >> pl.dwUserId;
		bis >> pl.dwCountId;

		return bis;
	}
};

struct CMD_GP_UserActionCount_Rep //ͳ����Ӧ
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_ACTION_COUNT_REP };

	unsigned short								nCode;	  //��� 0�ɹ�
	unsigned int								dwUserId; //�û�ID
	unsigned int								dwCountId;//ͳ��ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserActionCount_Rep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserActionCount_Rep& pl)
	{
		bos << pl.nCode;
		bos << pl.dwUserId;
		bos << pl.dwCountId;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserActionCount_Rep& pl)
	{
		pl.reset();

		bis >> pl.nCode;
		bis >> pl.dwUserId;
		bis >> pl.dwCountId;

		return bis;
	}
};

struct CMD_GR_WONDERFULL_ITEM_REQ
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_GET_WONDERFUL_ITEM_REQ };

	int WonderFulId;

	void reset() { memset(this, 0, sizeof(*this)); WonderFulId = 0; }
	friend bostream& operator<<(bostream& bos, const CMD_GR_WONDERFULL_ITEM_REQ& pl)
	{
		bos << pl.WonderFulId;
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_WONDERFULL_ITEM_REQ& pl)
	{
		pl.reset();
		bis >> pl.WonderFulId;
		return bis;
	}
};

struct CMD_GR_WONDERFULL_ITEM_REP
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_GET_WONDERFUL_ITEM_REP };
	enum { MISSON, RECHARGE, SHARE, PHOTO, FRIEND }; //����� ���� ��ֵ ���� ͼƬ ���ѷ�
	enum{ CAN_GET = 0,ALREADY_GET,NOT_GET };         //����ȡ ����ȡ δ��ɣ�û�дﵽ������������ȡ��

	int WonderFulId;		    //�ID
	int WonderfulItemIndex;     //���������
	int Condition1;		 	    //����1
	int Condition2;			    //����2
	int awardState;             //0������ȡ������û�ﵽ�� 1����ȡ 2����ȡ
	int conditionComplete;      //��ȡ��Ʒ�Ѵ�ɵ����� ���˶��پ֣����˶���Ǯ ����MissionTypeȥ����
	int MissionType;            //�������� ���� ��ֵ ���� ͼƬ ���ѷ� ��Ӧ�����ö��ֵ
	char awardTypeStr[32];     //��Ʒ
	char awardNum[128];        //��Ʒ����
	char share_title[64];      //�������
	char share_content[128];   //��������
	char share_url[192];       //����ͼƬ��ַ
	char share_link_url[192];  //����ͼƬ����
	char kind_str[128];        //��Ϸ����KIND
	char content[192];         //����˵��

	
	

	void reset() { memset(this, 0, sizeof(*this)); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_WONDERFULL_ITEM_REP& pl)
	{
		bos << pl.WonderFulId;
		bos << pl.WonderfulItemIndex;
		bos << pl.Condition1;
		bos << pl.Condition2;
		bos << pl.awardState;
		bos << pl.conditionComplete;
		bos << pl.MissionType;
		bos.write((char*)pl.awardTypeStr, sizeof(pl.awardTypeStr));
		bos.write((char*)pl.awardNum, sizeof(pl.awardNum));
		bos.write((char*)pl.share_title, sizeof(pl.share_title));
		bos.write((char*)pl.share_content, sizeof(pl.share_content));
		bos.write((char*)pl.share_url, sizeof(pl.share_url));
		bos.write((char*)pl.share_link_url, sizeof(pl.share_link_url));
		bos.write((char*)pl.kind_str, sizeof(pl.kind_str));
		bos.write((char*)pl.content, sizeof(pl.content));
		
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_WONDERFULL_ITEM_REP& pl)
	{
		pl.reset();
		bis >> pl.WonderFulId;
		bis >> pl.WonderfulItemIndex;
		bis >> pl.Condition1;
		bis >> pl.Condition2;
		bis >> pl.awardState;
		bis >> pl.conditionComplete;
		bis >> pl.MissionType;
		bis.read((char*)pl.awardTypeStr, sizeof(pl.awardTypeStr));
		bis.read((char*)pl.awardNum, sizeof(pl.awardNum));
		bis.read((char*)pl.share_title, sizeof(pl.share_title));
		bis.read((char*)pl.share_content, sizeof(pl.share_content));
		bis.read((char*)pl.share_url, sizeof(pl.share_url));
		bis.read((char*)pl.share_link_url, sizeof(pl.share_link_url));
		bis.read((char*)pl.kind_str, sizeof(pl.kind_str));
		bis.read((char*)pl.content, sizeof(pl.content));
		
		return bis;
	}
};


struct CMD_GR_WONDERFULL_ITEM_FINISH
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_GET_WONDERFUL_ITEM_FINISH };
	enum { SUCC, ERROR_1, ERROR_2 };  //ERROR_1�������ݴ��� ERROR_2û��������

	unsigned short sCode;   //���
	int WonderFulId;        //����ʱ�Ļ����
	int wonderfullIemLen;	//һ�������˶��ٸ��(������ֵ����0 ��ʾ��ǰ��������û��С��)

	void reset() { memset(this, 0, sizeof(*this)); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_WONDERFULL_ITEM_FINISH& pl)
	{
		bos << pl.sCode;
		bos << pl.WonderFulId;
		bos << pl.wonderfullIemLen;
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_WONDERFULL_ITEM_FINISH& pl)
	{
		pl.reset();
		bis >> pl.sCode;
		bis >> pl.WonderFulId;
		bis >> pl.wonderfullIemLen;
		return bis;
	}
};


struct CMD_GR_WONDERFULL_REQ
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_SEND_WONDERFUL_REQ };

	unsigned long  dwUserId;

	void reset() { memset(this, 0, sizeof(*this)); dwUserId = 0; }
	friend bostream& operator<<(bostream& bos, const CMD_GR_WONDERFULL_REQ& pl)
	{
		bos << pl.dwUserId;
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_WONDERFULL_REQ& pl)
	{
		pl.reset();
		bis >> pl.dwUserId;
		return bis;
	}
};

struct CMD_GR_WONDERFULL_REP
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_SEND_WONDERFUL_REP };

	int	  wondefful_id;			 //���ʻ����ID���ͻ��˻�ȡ��������ľ���ֵʱ�ش�����������
	int   sequenceIndex;         //��������   
	int   huobao;                //�Ƿ�� 0�� 1����
	int   newAdd;                //�Ƿ����� 0������ 1����
	char activityTitle[128];	 //�����
	char activityStartTime[32]; //��ʼʱ��
	char activityEndTime[32];   //����ʱ��
	char activityContent[192];  //�˵��


	void reset() { memset(this, 0, sizeof(*this)); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_WONDERFULL_REP& pl)
	{
		bos << pl.wondefful_id;
		bos << pl.sequenceIndex;
		bos << pl.huobao;
		bos << pl.newAdd;
		bos.write((char*)pl.activityTitle, sizeof(pl.activityTitle));
		bos.write((char*)pl.activityStartTime, sizeof(pl.activityStartTime));
		bos.write((char*)pl.activityEndTime, sizeof(pl.activityEndTime));
		bos.write((char*)pl.activityContent, sizeof(pl.activityContent));
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_WONDERFULL_REP& pl)
	{
		pl.reset();
		bis >> pl.wondefful_id;
		bis >> pl.sequenceIndex;
		bis >> pl.huobao;
		bis >> pl.newAdd;
		bis.read((char*)pl.activityTitle, sizeof(pl.activityTitle));
		bis.read((char*)pl.activityStartTime, sizeof(pl.activityStartTime));
		bis.read((char*)pl.activityEndTime, sizeof(pl.activityEndTime));
		bis.read((char*)pl.activityContent, sizeof(pl.activityContent));
		return bis;
	}
};

struct CMD_GR_WONDERFULL_FINISH
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_SEND_WONDERFUL_FINISH };
	enum { SUCC, ERROR_1, ERROR_2 };  //ERROR_1�������ݴ��� ERROR_2û��������

	unsigned short sCode;   //���
	int wonderfullIemLen;	//һ�������˶��ٸ��(������ֵ����0 ��ʾ��ǰû���κξ��ʻ)

	void reset() { memset(this, 0, sizeof(*this)); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_WONDERFULL_FINISH& pl)
	{
		bos << pl.sCode;
		bos << pl.wonderfullIemLen;
		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_WONDERFULL_FINISH& pl)
	{
		pl.reset();
		bis >> pl.sCode;
		bis >> pl.wonderfullIemLen;
		return bis;
	}
};

struct CMD_GP_UserWelfare_Req //�û���ȡ�ͱ�			
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_WELFARE_REQ };

	unsigned int								dwUserId;//�û�ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserWelfare_Req() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserWelfare_Req& pl)
	{
		bos << pl.dwUserId;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserWelfare_Req& pl)
	{
		pl.reset();
		bis >> pl.dwUserId;

		return bis;
	}

};

struct CMD_GP_UserWelfare_Rep //�û���ȡ�ͱ��ص�
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_WELFARE_REP };

	unsigned int								dwUserId;//�û�ID
	unsigned int								dwType; //0����ȡ�ɹ���-1����ȡʧ�ܣ�-3:������ȡ(���û������Ѿ�û����ȡ�ʸ�)

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserWelfare_Rep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserWelfare_Rep& pl)
	{
		bos << pl.dwUserId;
		bos << pl.dwType;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserWelfare_Rep& pl)
	{
		pl.reset();
		bis >> pl.dwUserId;
		bis >> pl.dwType;

		return bis;
	}
};

struct CMD_GP_UserGameRoomJionAutoReq //��ͳ���Զ����뷿��
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_GAMEROOM_LOCKER_INFO };

	unsigned int								dwUserId;//�û�ID
	int											iServerId;
	int											iKindId;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserGameRoomJionAutoReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserGameRoomJionAutoReq& pl)
	{
		bos << pl.dwUserId;
		bos << pl.iServerId;
		bos << pl.iKindId;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserGameRoomJionAutoReq& pl)
	{
		pl.reset();
		bis >> pl.dwUserId;
		bis >> pl.iServerId;
		bis >> pl.iKindId;

		return bis;
	}
};

struct CMD_GP_UserPhoneInfoChangeReq //�����ֻ��û�����
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PHONE_INFO_CHANGE };

	unsigned int								dwUserId;//�û�ID
	char										szUserName[NAME_LEN];		//����
	char										szFaceURL[256];				//ͷ��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserPhoneInfoChangeReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserPhoneInfoChangeReq& pl)
	{
		bos << pl.dwUserId;

		bos.write((char*)pl.szUserName, sizeof(pl.szUserName));
		bos.write((char*)pl.szFaceURL, sizeof(pl.szFaceURL));


		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserPhoneInfoChangeReq& pl)
	{
		pl.reset();
		bis >> pl.dwUserId;

		bis.read((char*)pl.szUserName, sizeof(pl.szUserName));
		bis.read((char*)pl.szFaceURL, sizeof(pl.szFaceURL));

		return bis;
	}
};


struct CMD_GP_UserPhoneFaceInfoReq //�����ֻ��û�����
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PHONE_FACEURL_INFO };

//	unsigned int								dwUserId;//�û�ID
	char										szUserName[NAME_LEN];		//����
	char										szFaceURL[256];				//ͷ��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserPhoneFaceInfoReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserPhoneFaceInfoReq& pl)
	{
//		bos << pl.dwUserId;

		bos.write((char*)pl.szUserName, sizeof(pl.szUserName));
		bos.write((char*)pl.szFaceURL, sizeof(pl.szFaceURL));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserPhoneFaceInfoReq& pl)
	{
		pl.reset();
//		bis >> pl.dwUserId;

		bis.read((char*)pl.szUserName, sizeof(pl.szUserName));
		bis.read((char*)pl.szFaceURL, sizeof(pl.szFaceURL));

		return bis;
	}
};

struct CMD_GP_UserStatusDetailReq //�����֤
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_UESER_STATUS_REQ };

	unsigned int								dwUserId;//�û�ID
	char										szUserName[NAME_LEN];				//����
	char										szUserNumber[20];				//���֤����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserStatusDetailReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserStatusDetailReq& pl)
	{
		bos << pl.dwUserId;

		bos.write((char*)pl.szUserName, sizeof(pl.szUserName));
		bos.write((char*)pl.szUserNumber, sizeof(pl.szUserNumber));
		

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserStatusDetailReq& pl)
	{
		pl.reset();
		bis >> pl.dwUserId;

		bis.read((char*)pl.szUserName, sizeof(pl.szUserName));
		bis.read((char*)pl.szUserNumber, sizeof(pl.szUserNumber));
		
		return bis;
	}
};


struct CMD_GP_UserStatusDetailRep //��ݰ󶨻ص� 
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_UESER_STATUS_REP };

	unsigned int								dwType; //0���󶨣�1��û�а�
	char										szUserName[NAME_LEN];				//����
	char										szUserNumber[20];				//���֤����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserStatusDetailRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserStatusDetailRep& pl)
	{
		bos << pl.dwType;
		if (pl.dwType == 0)
		{
			bos.write((char*)pl.szUserName, sizeof(pl.szUserName));
			bos.write((char*)pl.szUserNumber, sizeof(pl.szUserNumber));
		}

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserStatusDetailRep& pl)
	{
		pl.reset();
		bis >> pl.dwType;
		if (pl.dwType == 0)
		{
			bis.read((char*)pl.szUserName, sizeof(pl.szUserName));
			bis.read((char*)pl.szUserNumber, sizeof(pl.szUserNumber));
		}
		return bis;
	}
};

struct CMD_GP_UserStatusDetailRep_2 //�Ƿ�����֤
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_UESER_STATUS_REP_2 };

	unsigned int								dwType; //0���󶨣�1��û�а�
	char										szUserName[NAME_LEN];				//����
	char										szUserNumber[20];				//���֤����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserStatusDetailRep_2() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserStatusDetailRep_2& pl)
	{
		bos << pl.dwType;
		if (pl.dwType == 0)
		{
			bos.write((char*)pl.szUserName, sizeof(pl.szUserName));
			bos.write((char*)pl.szUserNumber, sizeof(pl.szUserNumber));
		}
		
		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserStatusDetailRep_2& pl)
	{
		pl.reset();
		bis >> pl.dwType;
		if (pl.dwType == 0)
		{
			bis.read((char*)pl.szUserName, sizeof(pl.szUserName));
			bis.read((char*)pl.szUserNumber, sizeof(pl.szUserNumber));
		}
		return bis;
	}
};

struct CMD_GP_UserPartnerDetailReq //�Ƿ�VIP
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PARTNER_REP };

	unsigned int								dwType; //0����VIP��1��VIP��ң�......5��û�а�

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserPartnerDetailReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserPartnerDetailReq& pl)
	{
		bos << pl.dwType;
		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserPartnerDetailReq& pl)
	{
		pl.reset();
		bis >> pl.dwType;

		return bis;
	}

};

struct CMD_GP_UserPayOrderDetailReq //�Ƿ�󶨺ϻ���
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PAY_ORDER_REQ };

	unsigned int								dwUserID;			//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserPayOrderDetailReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserPayOrderDetailReq& pl)
	{
		bos << pl.dwUserID;
		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserPayOrderDetailReq& pl)
	{
		pl.reset();
		bis >> pl.dwUserID;

		return bis;
	}

};

struct CMD_GP_UserPayOrderDetailRep //�Ƿ�󶨺ϻ��˷���
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PAY_ORDER_REP };

	bool										bBinder;			//�Ƿ��
	unsigned int								dwUserID;			//�ϻ���ID


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserPayOrderDetailRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserPayOrderDetailRep& pl)
	{
		bos << pl.bBinder;
		bos << pl.dwUserID;
		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserPayOrderDetailRep& pl)
	{
		pl.reset();
		bis >> pl.bBinder;
		bis >> pl.dwUserID;

		return bis;
	}

};


struct CMD_GP_UserPayOrderSendReq //�󶨺ϻ���
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PAY_ORDER_SEND_REQ };

	unsigned int								dwUserID;			//��� ID
	unsigned int								dwHeHuoUserID;		//�ϻ���ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserPayOrderSendReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserPayOrderSendReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwHeHuoUserID;
		
		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserPayOrderSendReq& pl)
	{
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.dwHeHuoUserID;
		
		return bis;
	}

};

struct CMD_GP_UserPayOrderSendRep //�󶨺ϻ��˷���
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PAY_ORDER_SEND_REP };

	unsigned int								dwType;			//�ɹ���0��ʧ�ܣ�1���Ѿ��󶨹���2

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserPayOrderSendRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserPayOrderSendRep& pl)
	{
		bos << pl.dwType;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserPayOrderSendRep& pl)
	{
		pl.reset();
		bis >> pl.dwType;


		return bis;
	}
};

//��ȡ�������
struct CMD_GP_UserFenxResultReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FENX_RESULT_GET_REQ };

	unsigned int								dwUserID;			//��� ID
	unsigned int								priceID;			//����һ�����ID��
	unsigned int								price;				//���
	unsigned int								price2;				//���Ѻ����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxResultReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxResultReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.priceID;
		bos << pl.price;
		bos << pl.price2;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxResultReq& pl)
	{
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.priceID;
		bis >> pl.price;
		bis >> pl.price2;

		return bis;
	}
};

//��ȡ������󷵻�
struct CMD_GP_UserFenxResultRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FENX_RESULT_GET_REP };

	unsigned int					dwUserID;					//��� ID
	unsigned int					iGoodsID;					//����ID
	unsigned int					price;						//���
	unsigned int					price2;						//���Ѻ����
	unsigned int					iType;						//���� 0:�ޣ�1��������2�������3�������4��ʵ��
	unsigned int					dwCode;						//���ز����� 0���ɹ���1������������㣻2:û�й�ע��Ȩ��3����ȡ�������� 4��ʧ��
	char							szOrderId[20];				//�ƾֵ�ȫ��Ψһ���
	char							token[128];


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxResultRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxResultRep& pl)
	{
		bos << pl.dwUserID;
		bos << pl.iGoodsID;
		bos << pl.price;
		bos << pl.price2;
		bos << pl.iType;
		bos << pl.dwCode;
		bos.write((char*)pl.szOrderId, sizeof(pl.szOrderId));
		bos.write((char*)pl.token, sizeof(pl.token));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxResultRep& pl)
	{
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.iGoodsID;
		bis >> pl.price;
		bis >> pl.price2;
		bis >> pl.iType;
		bis >> pl.dwCode;
		bis.read((char*)pl.szOrderId, sizeof(pl.szOrderId));
		bis.read((char*)pl.token, sizeof(pl.token));

		return bis;
	}
};

//������ѯ����
struct CMD_GP_UserFenxRewardResultReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_SP_USER_FENX_ACTIVITY_DETAIL_REQ };

	unsigned int					nPage;			//ҳ��	
	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxRewardResultReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxRewardResultReq& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxRewardResultReq& pl)
	{
		pl.reset();
		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};


//�����б�
struct CMD_GP_UserFenxRewardResultRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_SP_USER_FENX_ACTIVITY_DETAIL_REP };

	char							szDate[32];				//ʱ��
	unsigned int					nPage;					//ҳ��	
	float							dKaPrice;
	unsigned int					iType;					//���� 0���鵽�Ľ�Ʒ�� 1:�һ����͵ĺ�� 
	unsigned int					iType2;					//����״̬
	//char							szName[32];				//����
	char							cPriceName[50];
	//char							faceUrl[256];
	char							szOrderId[20];				//�ƾֵ�ȫ��Ψһ���
	char							token[20];


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxRewardResultRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxRewardResultRep& pl)
	{
		bos.write((char*)pl.szDate, sizeof(pl.szDate));

		bos << pl.nPage;
		bos << pl.dKaPrice;

		bos << pl.iType;
		bos << pl.iType2;

		//bos.write((char*)pl.szName, sizeof(pl.szName));
		bos.write((char*)pl.cPriceName, sizeof(pl.cPriceName));

		bos.write((char*)pl.szOrderId, sizeof(pl.szOrderId));
		bos.write((char*)pl.token, sizeof(pl.token));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxRewardResultRep& pl)
	{
		pl.reset();

		bis.read((char*)pl.szDate, sizeof(pl.szDate));

		bis >> pl.nPage;
		bis >> pl.dKaPrice;

		bis >> pl.iType;
		bis >> pl.iType2;

		//bis.read((char*)pl.szName, sizeof(pl.szName));
		bis.read((char*)pl.cPriceName, sizeof(pl.cPriceName));

		bis.read((char*)pl.szOrderId, sizeof(pl.szOrderId));
		bis.read((char*)pl.token, sizeof(pl.token));

		return bis;
	}
};

//�����б����
struct CMD_GP_UserFenxRewardResultFinish
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_SP_USER_FENX_ACTIVITY_DETAIL_FINISH };

	unsigned int					dwTotal;					//����
	unsigned int					dwTotalofCurPage;			//��ǰҳ����
	unsigned int					dwUserID;					//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxRewardResultFinish() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxRewardResultFinish& pl)
	{
		bos << pl.dwTotal;
		bos << pl.dwTotalofCurPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxRewardResultFinish& pl)
	{
		pl.reset();

		bis >> pl.dwTotal;
		bis >> pl.dwTotalofCurPage;
		bis >> pl.dwUserID;

		return bis;
	}
};
//���˷�����ѯ����
struct CMD_GP_UserFenxOtherRewardResultReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_SP_USER_FENX_ACTIVITY_OTHER_DETAIL_REQ };

	unsigned int					nPage;			//ҳ��	
	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxOtherRewardResultReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxOtherRewardResultReq& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxOtherRewardResultReq& pl)
	{
		pl.reset();
		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};


//���˷����б�
struct CMD_GP_UserFenxOtherRewardResultRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_SP_USER_FENX_ACTIVITY_OTHER_DETAIL_REP };

	char							szDate[32];				//ʱ��
	unsigned int					nPage;					//ҳ��	
	float							dKaPrice;
	char							szName[32];				//����
	char							cPriceName[50];
	//char							faceUrl[256];


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxOtherRewardResultRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxOtherRewardResultRep& pl)
	{
		bos.write((char*)pl.szDate, sizeof(pl.szDate));

		bos << pl.nPage;
		bos << pl.dKaPrice;

		bos.write((char*)pl.szName, sizeof(pl.szName));
		bos.write((char*)pl.cPriceName, sizeof(pl.cPriceName));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxOtherRewardResultRep& pl)
	{
		pl.reset();

		bis.read((char*)pl.szDate, sizeof(pl.szDate));

		bis >> pl.nPage;
		bis >> pl.dKaPrice;

		bis.read((char*)pl.szName, sizeof(pl.szName));
		bis.read((char*)pl.cPriceName, sizeof(pl.cPriceName));

		return bis;
	}
};

//���˷����б����
struct CMD_GP_UserFenxOtherRewardResultFinish
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_SP_USER_FENX_ACTIVITY_OTHER_DETAIL_FINISH };

	unsigned int					dwTotal;					//����
	unsigned int					dwTotalofCurPage;			//��ǰҳ����
	unsigned int					dwUserID;					//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxOtherRewardResultFinish() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxOtherRewardResultFinish& pl)
	{
		bos << pl.dwTotal;
		bos << pl.dwTotalofCurPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxOtherRewardResultFinish& pl)
	{
		pl.reset();

		bis >> pl.dwTotal;
		bis >> pl.dwTotalofCurPage;
		bis >> pl.dwUserID;

		return bis;
	}
};


//��������
struct CMD_GP_UserFenxiangActivityReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_SP_USER_FENX_ACTIVITY_REQ };

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwActivityId;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxiangActivityReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxiangActivityReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwActivityId;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxiangActivityReq& pl)
	{
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.dwActivityId;

		return bis;
	}
};

//��������
struct CMD_GP_UserFenxiangActivityRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_SP_USER_FENX_ACTIVITY_REP };

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwActivityId;
	unsigned int					iGetID;			//�������ID
	unsigned int					iprice;
	unsigned int					priceType;
	unsigned int					iCode;		//0:�ɹ���1��ʧ�ܣ������Ѿ�������ˣ�
	char							szOrderId[20];				//�ƾֵ�ȫ��Ψһ���
	char							token[128];

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxiangActivityRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxiangActivityRep& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwActivityId;
		bos << pl.iGetID;
		bos << pl.iprice;
		bos << pl.priceType;
		bos << pl.iCode;

		bos.write((char*)pl.szOrderId, sizeof(pl.szOrderId));
		bos.write((char*)pl.token, sizeof(pl.token));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxiangActivityRep& pl)
	{
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.dwActivityId;
		bis >> pl.iGetID;
		bis >> pl.iprice;
		bis >> pl.priceType;
		bis >> pl.iCode;

		bis.read((char*)pl.szOrderId, sizeof(pl.szOrderId));
		bis.read((char*)pl.token, sizeof(pl.token));

		return bis;
	}
};

//�����н���¼��ѯ����
struct CMD_GP_UserHongbaoOtherRewardResultReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_RESULT_OTHER_GET_DETAIL_REQ };

	unsigned int					nPage;			//ҳ��	
	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoOtherRewardResultReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoOtherRewardResultReq& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoOtherRewardResultReq& pl)
	{
		pl.reset();
		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};


//�����н���¼�б�
struct CMD_GP_UserHongbaoOtherRewardResultRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_RESULT_OTHER_GET_DETAIL_REP };

	char							szDate[32];				//��սʱ��
	unsigned int					nPage;					//ҳ��	
	float							dKaPrice;
	char							szName[32];				//����
	char							faceUrl[256];


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoOtherRewardResultRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoOtherRewardResultRep& pl)
	{
		bos.write((char*)pl.szDate, sizeof(pl.szDate));

		bos << pl.nPage;
		bos << pl.dKaPrice;

		bos.write((char*)pl.szName, sizeof(pl.szName));
		bos.write((char*)pl.faceUrl, sizeof(pl.faceUrl));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoOtherRewardResultRep& pl)
	{
		pl.reset();

		bis.read((char*)pl.szDate, sizeof(pl.szDate));

		bis >> pl.nPage;
		bis >> pl.dKaPrice;

		bis.read((char*)pl.szName, sizeof(pl.szName));
		bis.read((char*)pl.faceUrl, sizeof(pl.faceUrl));

		return bis;
	}
};

//�����н���¼�б����
struct CMD_GP_UserHongbaoOtherRewardResultFinish
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_RESULT_OTHER_GET_DETAIL_FINISH };

	unsigned int					dwTotal;					//����
	unsigned int					dwTotalofCurPage;			//��ǰҳ����
	unsigned int					dwUserID;					//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoOtherRewardResultFinish() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoOtherRewardResultFinish& pl)
	{
		bos << pl.dwTotal;
		bos << pl.dwTotalofCurPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoOtherRewardResultFinish& pl)
	{
		pl.reset();

		bis >> pl.dwTotal;
		bis >> pl.dwTotalofCurPage;
		bis >> pl.dwUserID;

		return bis;
	}
};


//�齱���ݲ�ѯ����
struct CMD_GP_UserFenxActivityReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FENX_ACTIVITY_REQ };

	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxActivityReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxActivityReq& pl)
	{
		//		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxActivityReq& pl)
	{
		pl.reset();
		//		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};

//�齱���ݲ�ѯ���󷵻�
struct CMD_GP_UserFenxActivityRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FENX_ACTIVITY_REP };

	unsigned int					iType; //0:δ������1������
	float							hongbaoj;
	unsigned int					iGoodsLenth;
	unsigned int					igoodsId[12];
	char							cUrl[50];
	
	char							cName[12][50];
	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFenxActivityRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFenxActivityRep& pl)
	{
		bos << pl.iType;
		bos << pl.hongbaoj;
		bos << pl.iGoodsLenth;

		bos.write((char*)pl.igoodsId, sizeof(pl.igoodsId));
		bos.write((char*)pl.cUrl, sizeof(pl.cUrl));
		bos.write((char*)pl.cName, 12*50);
		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFenxActivityRep& pl)
	{
		pl.reset();
		bis >> pl.iType;
		bis >> pl.hongbaoj;
		bis >> pl.iGoodsLenth;

		bis.read((char*)pl.igoodsId, sizeof(pl.igoodsId));
		bis.read((char*)pl.cUrl, sizeof(pl.cUrl));
		bis.read((char*)pl.cName, 12*50);
		return bis;
	}
};


//��ȡ�����¼��ѯ����
struct CMD_GP_UserHongbaoActivityReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_ACTIVITY_REQ };

	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoActivityReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoActivityReq& pl)
	{
//		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoActivityReq& pl)
	{
		pl.reset();
//		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};

//��ȡ�����¼��ѯ����
struct CMD_GP_UserHongbaoActivityRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_ACTIVITY_REP };

	unsigned int					iType; //0:δ������1������
	float							hongbao;
	unsigned int					infolen;
	char							extenInfo[256];


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoActivityRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoActivityRep& pl)
	{
		bos << pl.iType;
		bos << pl.hongbao;
		bos << pl.infolen;

		bos.write((char*)pl.extenInfo, pl.infolen);
		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoActivityRep& pl)
	{
		pl.reset();
		bis >> pl.iType;
		bis >> pl.hongbao;
		bis >> pl.infolen;

		bis.read((char*)pl.extenInfo, pl.infolen);
		return bis;
	}
};

//��ȡ�����¼��ѯ����
struct CMD_GP_UserHongbaoDetailResultReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_RESULT_GET_DETAIL_REQ };

	unsigned int					nPage;			//ҳ��	
	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoDetailResultReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoDetailResultReq& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoDetailResultReq& pl)
	{
		pl.reset();
		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};


//��ȡ�����¼�б�
struct CMD_GP_UserHongbaoDetailResultRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_RESULT_GET_DETAIL_REP };

	char							szDate[32];				//��սʱ��
	unsigned int					nPage;					//ҳ��	
	unsigned int					dType;					//�˵�״̬
	unsigned int					dKaPrice;


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoDetailResultRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoDetailResultRep& pl)
	{
		bos.write((char*)pl.szDate, sizeof(pl.szDate));

		bos << pl.nPage;
		bos << pl.dType;
		bos << pl.dKaPrice;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoDetailResultRep& pl)
	{
		pl.reset();

		bis.read((char*)pl.szDate, sizeof(pl.szDate));

		bis >> pl.nPage;
		bis >> pl.dType;
		bis >> pl.dKaPrice;

		return bis;
	}
};

//��ȡ�����¼�б����
struct CMD_GP_UserHongbaoDetailResultFinish
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_RESULT_GET_DETAIL_FINISH };

	unsigned int					dwTotal;					//����
	unsigned int					dwTotalofCurPage;			//��ǰҳ����
	unsigned int					dwUserID;					//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoDetailResultFinish() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoDetailResultFinish& pl)
	{
		bos << pl.dwTotal;
		bos << pl.dwTotalofCurPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoDetailResultFinish& pl)
	{
		pl.reset();

		bis >> pl.dwTotal;
		bis >> pl.dwTotalofCurPage;
		bis >> pl.dwUserID;

		return bis;
	}
};

//�н���¼��ѯ����
struct CMD_GP_UserHongbaoRewardResultReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_RESULT_REWAED_REQ };

	unsigned int					nPage;			//ҳ��	
	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoRewardResultReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoRewardResultReq& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoRewardResultReq& pl)
	{
		pl.reset();
		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};


//�н���¼�б�
struct CMD_GP_UserHongbaoRewardResultRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_RESULT_REWAED_REP };

	char							szDate[32];				//��սʱ��
	unsigned int					nPage;					//ҳ��	
	float							dKaPrice;


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoRewardResultRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoRewardResultRep& pl)
	{
		bos.write((char*)pl.szDate, sizeof(pl.szDate));

		bos << pl.nPage;
		bos << pl.dKaPrice;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoRewardResultRep& pl)
	{
		pl.reset();

		bis.read((char*)pl.szDate, sizeof(pl.szDate));

		bis >> pl.nPage;
		bis >> pl.dKaPrice;

		return bis;
	}
};

//�н���¼�б����
struct CMD_GP_UserHongbaoRewardResultFinish
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_RESULT_REWAED_FINISH };

	unsigned int					dwTotal;					//����
	unsigned int					dwTotalofCurPage;			//��ǰҳ����
	unsigned int					dwUserID;					//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoRewardResultFinish() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoRewardResultFinish& pl)
	{
		bos << pl.dwTotal;
		bos << pl.dwTotalofCurPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoRewardResultFinish& pl)
	{
		pl.reset();

		bis >> pl.dwTotal;
		bis >> pl.dwTotalofCurPage;
		bis >> pl.dwUserID;

		return bis;
	}
};

//��ȡ�������
struct CMD_GP_UserHongbaoResultReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_RESULT_GET_REQ };

	unsigned int					dwUserID;					//��� ID
	unsigned int								price;				//���

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoResultReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoResultReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.price;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoResultReq& pl)
	{
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.price;

		return bis;
	}
};

//��ȡ������󷵻�
struct CMD_GP_UserHongbaoResultRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_HONGBAO_RESULT_GET_REP };

	unsigned int					dwUserID;					//��� ID
	unsigned int					price;						//���
	unsigned int					dwCode;						//���ز����� 0���ɹ���1������������㣻2:û�й�ע��Ȩ��3����ȡ�������� 4��ʧ��
	char							szOrderId[20];				//�ƾֵ�ȫ��Ψһ���
	char							token[128];
	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserHongbaoResultRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserHongbaoResultRep& pl)
	{
		bos << pl.dwUserID;
		bos << pl.price;
		bos << pl.dwCode;
		bos.write((char*)pl.szOrderId, sizeof(pl.szOrderId));
		bos.write((char*)pl.token, sizeof(pl.token));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserHongbaoResultRep& pl)
	{
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.price;
		bis >> pl.dwCode;
		bis.read((char*)pl.szOrderId, sizeof(pl.szOrderId));
		bis.read((char*)pl.token, sizeof(pl.token));

		return bis;
	}
};

//�˵���¼��ѯ����
struct CMD_GP_UserOtherFriendResultReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_OTHER_FRIEND_RESULT_REQ };

	unsigned int					nPage;			//ҳ��	
	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserOtherFriendResultReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserOtherFriendResultReq& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserOtherFriendResultReq& pl)
	{
		pl.reset();
		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};


//�˵���¼�б�
struct CMD_GP_UserOtherFriendResultRecord
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_OTHER_FRIEND_RESULT_REP };

	char							szGameNum[32];			//�ƾֵ�ȫ��Ψһ���	
	char							szDate[32];				//��սʱ��
//	int								nPlayLen;				//�����:���֧��8�����
//	char							szPlayName[8][32];		//�������:���֧��8�����
//	unsigned int					dwTotalScore[8];		//��������ܻ���:���֧��8�����
	unsigned int					nPage;					//ҳ��	
	int								dwRoomID;				//�����
	unsigned int					dType;					//�˵�״̬
	unsigned int					dKaPrice;
	unsigned int					nRuleLen;
	unsigned int					dKindId;
	char							szRule[512];			//����	


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserOtherFriendResultRecord() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserOtherFriendResultRecord& pl)
	{
		bos.write((char*)pl.szGameNum, sizeof(pl.szGameNum));
		bos.write((char*)pl.szDate, sizeof(pl.szDate));

		//bos << pl.nPlayLen;
		//bos.write((char*)pl.szPlayName, pl.nPlayLen * 32);
		//bos.write((char*)pl.dwTotalScore, pl.nPlayLen * sizeof(int));

		bos << pl.nPage;
		bos << pl.dwRoomID;
		bos << pl.dType;
		bos << pl.dKaPrice;
		bos << pl.nRuleLen;
		bos << pl.dKindId;
		bos.write((char*)pl.szRule, pl.nRuleLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserOtherFriendResultRecord& pl)
	{
		pl.reset();

		bis.read((char*)pl.szGameNum, sizeof(pl.szGameNum));
		bis.read((char*)pl.szDate, sizeof(pl.szDate));

		//bis >> pl.nPlayLen;
		//bis.read((char*)pl.szPlayName, pl.nPlayLen * 32);
		//bis.read((char*)pl.dwTotalScore, pl.nPlayLen * sizeof(int));

		bis >> pl.nPage;
		bis >> pl.dwRoomID;
		bis >> pl.dType;
		bis >> pl.dKaPrice;
		bis >> pl.nRuleLen;
		bis >> pl.dKindId;
		bis.read((char*)pl.szRule, pl.nRuleLen);

		return bis;
	}
};

//������¼�б����
struct CMD_GP_UserOTherFriendResultRecordFinish
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_OTHER_FRIEND_RESULT_RECORD_FINISH };

	unsigned int					dwTotal;					//����
	unsigned int					dwTotalofCurPage;			//��ǰҳ����
	unsigned int					dwUserID;					//��� ID
	int								dwGoldScore;				//����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserOTherFriendResultRecordFinish() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserOTherFriendResultRecordFinish& pl)
	{
		bos << pl.dwTotal;
		bos << pl.dwTotalofCurPage;
		bos << pl.dwUserID;
		bos << pl.dwGoldScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserOTherFriendResultRecordFinish& pl)
	{
		pl.reset();

		bis >> pl.dwTotal;
		bis >> pl.dwTotalofCurPage;
		bis >> pl.dwUserID;
		bis >> pl.dwGoldScore;

		return bis;
	}
};


//�˵����η����ѯ����
struct CMD_GP_UserOtherFriendResultDetailReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_OTHER_FRIEND_RESULT_DETAIL_REQ};

	unsigned int							iType;				//���� ���� 1     ɾ�� 2
	char							szGameNum[32];		//�ƾֵ�ȫ��Ψһ���

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserOtherFriendResultDetailReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserOtherFriendResultDetailReq& pl)
	{
		bos << pl.iType;
		bos.write((char*)pl.szGameNum, sizeof(pl.szGameNum));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserOtherFriendResultDetailReq& pl)
	{
		pl.reset();
		bis >> pl.iType;
		bis.read((char*)pl.szGameNum, sizeof(pl.szGameNum));

		return bis;
	}
};


//�����˵���¼�б�
struct CMD_GP_UserOtherFriendResultDetail
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_OTHER_FRIEND_RESULT_DETAIL_REP };

	int								nPlayLen;				//�����:���֧��8�����
	char							szPlayName[8][32];		//�������:���֧��8�����
	int								dwTotalScore[8];		//��������ܻ���:���֧��8�����
	char							szFaceUrl[8][256];		//���ͷ��


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserOtherFriendResultDetail() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserOtherFriendResultDetail& pl)
	{

		bos << pl.nPlayLen;
		bos.write((char*)pl.szPlayName, pl.nPlayLen * 32);
		bos.write((char*)pl.dwTotalScore, pl.nPlayLen * sizeof(int));
		bos.write((char*)pl.szFaceUrl, pl.nPlayLen * 256);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserOtherFriendResultDetail& pl)
	{
		pl.reset();

		bis >> pl.nPlayLen;
		bis.read((char*)pl.szPlayName, pl.nPlayLen * 32);
		bis.read((char*)pl.dwTotalScore, pl.nPlayLen * sizeof(int));
		bis.read((char*)pl.szFaceUrl, pl.nPlayLen * 256);

		return bis;
	}
};


//����ս����¼��ѯ����
struct CMD_GP_UserFriendResultReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FRIEND_RESULT_REQ };

	unsigned int					nPage;			//ҳ��	
	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFriendResultReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFriendResultReq& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFriendResultReq& pl)
	{
		pl.reset();
		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};

//����ս����¼�б�
struct CMD_GP_UserFriendResultRecord
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FRIEND_RESULT_RECORD };

	char							szGameNum[32];			//�ƾֵ�ȫ��Ψһ���	
	char							szDate[32];				//��սʱ��
	int								nPlayLen;				//�����:���֧��8�����
	char							szPlayName[8][32];		//�������:���֧��8�����
	unsigned int					dwTotalScore[8];		//��������ܻ���:���֧��8�����
	unsigned int					nPage;					//ҳ��	
	unsigned int					dwRoomID;				//�����


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFriendResultRecord() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFriendResultRecord& pl)
	{
		bos.write((char*)pl.szGameNum, sizeof(pl.szGameNum));
		bos.write((char*)pl.szDate, sizeof(pl.szDate));

		bos << pl.nPlayLen;
		bos.write((char*)pl.szPlayName, pl.nPlayLen * 32);
		bos.write((char*)pl.dwTotalScore, pl.nPlayLen * sizeof(int));

		bos << pl.nPage;
		bos << pl.dwRoomID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFriendResultRecord& pl)
	{
		pl.reset();

		bis.read((char*)pl.szGameNum, sizeof(pl.szGameNum));
		bis.read((char*)pl.szDate, sizeof(pl.szDate));

		bis >> pl.nPlayLen;
		bis.read((char*)pl.szPlayName, pl.nPlayLen * 32);
		bis.read((char*)pl.dwTotalScore, pl.nPlayLen * sizeof(int));

		bis >> pl.nPage;
		bis >> pl.dwRoomID;

		return bis;
	}
};

//����ս����¼�б����
struct CMD_GP_UserFriendResultRecordFinish
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FRIEND_RESULT_RECORD_FINISH };

	unsigned int					dwTotal;					//����
	unsigned int					dwTotalofCurPage;			//��ǰҳ����
	unsigned int					dwUserID;					//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFriendResultRecordFinish() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFriendResultRecordFinish& pl)
	{
		bos << pl.dwTotal;
		bos << pl.dwTotalofCurPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFriendResultRecordFinish& pl)
	{
		pl.reset();

		bis >> pl.dwTotal;
		bis >> pl.dwTotalofCurPage;
		bis >> pl.dwUserID;

		return bis;
	}
};

//����ս�����η����ѯ����
struct CMD_GP_UserFriendResultDetailReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FRIEND_RESULT_DETAIL_REQ };

	char							szGameNum[32];		//�ƾֵ�ȫ��Ψһ���

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFriendResultDetailReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFriendResultDetailReq& pl)
	{
		bos.write((char*)pl.szGameNum, sizeof(pl.szGameNum));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFriendResultDetailReq& pl)
	{
		pl.reset();
		bis.read((char*)pl.szGameNum, sizeof(pl.szGameNum));

		return bis;
	}
};

//����ս�����η����ѯ���
struct CMD_GP_UserFriendResultDetailRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FRIEND_RESULT_DETAIL_REP };

	unsigned int					dwRoomID;			//�����

	int								nPlayLen;			//�����:���֧��8�����
	int								nDetailLen;			//��¼����:���32�ּ�¼

	char							szPlayName[8][32];	//�������:���֧��8�����
	char							szGameNum[32];		//�ƾֵ�ȫ��Ψһ���
	char							szDate[32][32];		//��սʱ��:���32�ּ�¼
	int								dwScore[32][8];		//ÿ����Ӯ����:���32�ּ�¼�����֧��8�����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFriendResultDetailRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFriendResultDetailRep& pl)
	{
		bos << pl.dwRoomID;
		bos << pl.nPlayLen;
		bos << pl.nDetailLen;

		bos.write((char*)pl.szPlayName, pl.nPlayLen * 32);
		bos.write((char*)pl.szGameNum, sizeof(pl.szGameNum));

		bos.write((char*)pl.szDate, pl.nDetailLen * 32);
		for (int i = 0; i < pl.nDetailLen; i++)
		{
			bos.write((char*)pl.dwScore[i], pl.nPlayLen * sizeof(int));
		}

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFriendResultDetailRep& pl)
	{
		pl.reset();

		bis >> pl.dwRoomID;
		bis >> pl.nPlayLen;
		bis >> pl.nDetailLen;

		bis.read((char*)pl.szPlayName, pl.nPlayLen * 32);
		bis.read((char*)pl.szGameNum, sizeof(pl.szGameNum));

		bis.read((char*)pl.szDate, pl.nDetailLen * 32);
		for (int i = 0; i < pl.nDetailLen; i++)
		{
			bis.read((char*)pl.dwScore[i], pl.nPlayLen * sizeof(int));
		}

		return bis;
	}
};

//����ս�����η����ѯ����
struct CMD_GP_UserFriendResultDetailReq_V2
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FRIEND_RESULT_DETAIL_REQ_V2 };

	char							szGameNum[32];		//�ƾֵ�ȫ��Ψһ���

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFriendResultDetailReq_V2() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFriendResultDetailReq_V2& pl)
	{
		bos.write((char*)pl.szGameNum, sizeof(pl.szGameNum));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFriendResultDetailReq_V2& pl)
	{
		pl.reset();
		bis.read((char*)pl.szGameNum, sizeof(pl.szGameNum));

		return bis;
	}
};

//����ս�����η����ѯ���
struct CMD_GP_UserFriendResultDetailRep_V2
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FRIEND_RESULT_DETAIL_REP_V2 };

	unsigned int					dwRoomID;			//�����

	int								nPlayLen;			//�����:���֧��8�����
	int								nDetailLen;			//��¼����:���32�ּ�¼

	char							szPlayName[8][32];	//�������:���֧��8�����
	char							szGameNum[32];		//�ƾֵ�ȫ��Ψһ���
	char							szDate[32][32];		//��սʱ��:���32�ּ�¼
	int								dwScore[32][8];		//ÿ����Ӯ����:���32�ּ�¼�����֧��8�����
	int								iReplayID[32];		//ÿ�ֵķ�����ID�����֧��32��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFriendResultDetailRep_V2() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFriendResultDetailRep_V2& pl)
	{
		bos << pl.dwRoomID;
		bos << pl.nPlayLen;
		bos << pl.nDetailLen;

		bos.write((char*)pl.szPlayName, pl.nPlayLen * 32);
		bos.write((char*)pl.szGameNum, sizeof(pl.szGameNum));

		bos.write((char*)pl.szDate, pl.nDetailLen * 32);
		for (int i = 0; i < pl.nDetailLen; i++)
		{
			bos.write((char*)pl.dwScore[i], pl.nPlayLen * sizeof(int));
		}
		bos.write((char*)pl.iReplayID, pl.nDetailLen * sizeof(int));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFriendResultDetailRep_V2& pl)
	{
		pl.reset();

		bis >> pl.dwRoomID;
		bis >> pl.nPlayLen;
		bis >> pl.nDetailLen;

		bis.read((char*)pl.szPlayName, pl.nPlayLen * 32);
		bis.read((char*)pl.szGameNum, sizeof(pl.szGameNum));

		bis.read((char*)pl.szDate, pl.nDetailLen * 32);
		for (int i = 0; i < pl.nDetailLen; i++)
		{
			bis.read((char*)pl.dwScore[i], pl.nPlayLen * sizeof(int));
		}
		bis.read((char*)pl.iReplayID, pl.nDetailLen * sizeof(int));

		return bis;
	}
};


//���䵥�ֻطż�¼��ѯ����
struct CMD_GP_UserFriendResultReplayReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FRIEND_RESULT_REPLAY_REQ };

	unsigned int					iReplayID;			//Ψһ������ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFriendResultReplayReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFriendResultReplayReq& pl)
	{
		bos << pl.iReplayID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFriendResultReplayReq& pl)
	{
		pl.reset();

		bis >> pl.iReplayID;

		return bis;
	}
};

//���䵥�ֻطż�¼��ѯ������û���Ϣ
struct CMD_GP_UserFriendResultReplayUserRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FRIEND_RESULT_REPLAY_USER_REP };

	unsigned int					iReplayID;			//Ψһ������ID

	int								nPlayLen;			//�����:���֧��8�����
	unsigned int					dwUserID[8];		//�û�id
	unsigned char					cGender[8];			//�û��Ա�
	int								iScore[8];			//�û�������Ӯ����
	char							szPlayName[8][32];	//�������:���֧��8�����
	char							szFaceUrl[8][256];	//���ͷ�����ص�ַ:���֧��8�����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFriendResultReplayUserRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFriendResultReplayUserRep& pl)
	{
		bos << pl.iReplayID;

		bos << pl.nPlayLen;
		bos.write((char*)pl.dwUserID, sizeof(pl.dwUserID));
		bos.write((char*)pl.cGender, sizeof(pl.cGender));
		bos.write((char*)pl.iScore, sizeof(pl.iScore));
		bos.write((char*)pl.szPlayName, pl.nPlayLen * 32);
		bos.write((char*)pl.szFaceUrl, pl.nPlayLen * 256);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFriendResultReplayUserRep& pl)
	{
		pl.reset();

		bis >> pl.iReplayID;

		bis >> pl.nPlayLen;
		bis.read((char*)pl.dwUserID, sizeof(pl.dwUserID));
		bis.read((char*)pl.cGender, sizeof(pl.cGender));
		bis.read((char*)pl.iScore, sizeof(pl.iScore));
		bis.read((char*)pl.szPlayName, pl.nPlayLen * 32);
		bis.read((char*)pl.szFaceUrl, pl.nPlayLen * 256);
		
		return bis;
	}
};

//���䵥�ֻطż�¼��ѯ�������������
struct CMD_GP_UserFriendResultReplayRuleRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FRIEND_RESULT_REPLAY_RULE_REP };

	unsigned int					iReplayID;			//Ψһ������ID

	unsigned int					dwRoomID;			//�����
	unsigned int					dwKindID;			//��Ϸ����

	unsigned short					nRuleLen;			//���ó���
	char							szRule[512];		//���ò���:��ֵ�ԣ�������̫��

	unsigned short					nHandDataLen;		//�������ݳ���
	char							szHandData[512];	//��������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFriendResultReplayRuleRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFriendResultReplayRuleRep& pl)
	{
		bos << pl.iReplayID;

		bos << pl.dwRoomID;
		bos << pl.dwKindID;

		bos << pl.nRuleLen;
		bos.write((char*)pl.szRule, pl.nRuleLen);

		bos << pl.nHandDataLen;
		bos.write((char*)pl.szHandData, pl.nHandDataLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFriendResultReplayRuleRep& pl)
	{
		pl.reset();

		bis >> pl.iReplayID;

		bis >> pl.dwRoomID;
		bis >> pl.dwKindID;
		
		bis >> pl.nRuleLen;
		bis.read((char*)pl.szRule, pl.nRuleLen);

		bis >> pl.nHandDataLen;
		bis.read((char*)pl.szHandData, pl.nHandDataLen);

		return bis;
	}
};

//���䵥�ֻطż�¼��ѯ���
struct CMD_GP_UserFriendResultReplayRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_FRIEND_RESULT_REPLAY_REP };
	
	unsigned int					iCode;			//0��ȷ��>0������

	unsigned int					iReplayID;			//Ψһ������ID

	unsigned short					nOrderDataLen;		//�������ݳ���
	char							szOrderData[1920];	//��������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFriendResultReplayRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserFriendResultReplayRep& pl)
	{
		bos << pl.iCode;
		bos << pl.iReplayID;

		bos << pl.nOrderDataLen;
		bos.write((char*)pl.szOrderData, pl.nOrderDataLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserFriendResultReplayRep& pl)
	{
		pl.reset();

		bis >> pl.iCode;
		bis >> pl.iReplayID;

		bis >> pl.nOrderDataLen;
		bis.read((char*)pl.szOrderData, pl.nOrderDataLen);

		return bis;
	}
};
//��ѯ��б���Ϣ
struct CMD_GP_UserActivityListReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_ACTIVITY_LIST_REQ};

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserActivityListReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserActivityListReq& pl)
	{
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserActivityListReq& pl)
	{	
		pl.reset();
		return bis;
	}
};

struct stUserActivity
{
	unsigned short	wType;				//���ͣ�1-web 2-�齱
	unsigned short	wStatus;				//�״̬��1��ʼǰ��2�����У�3�ѽ���
	unsigned int	dwActivityID;		//ID
	char			szTitle[50];			//����
	char			szText[100];			//���ݼ��
	char			szLinkUrl[50];		//���ӵ�ַ
	char			szIconUrl[50];		//ͼ���ַ

	void reset() { memset(this, 0, sizeof(*this)); }
	stUserActivity() { reset(); }
	friend bostream& operator<<(bostream& bos,const stUserActivity& pl)
	{
		bos << pl.wType;
		bos << pl.wStatus;
		bos << pl.dwActivityID;

		bos.write((char*)pl.szTitle,sizeof(pl.szTitle));
		bos.write((char*)pl.szText,sizeof(pl.szText));
		bos.write((char*)pl.szLinkUrl,sizeof(pl.szLinkUrl));
		bos.write((char*)pl.szIconUrl,sizeof(pl.szIconUrl));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,stUserActivity& pl)
	{	
		pl.reset();

		bis >> pl.wType;
		bis >> pl.wStatus;
		bis >> pl.dwActivityID;

		bis.read((char*)pl.szTitle,sizeof(pl.szTitle));
		bis.read((char*)pl.szText,sizeof(pl.szText));
		bis.read((char*)pl.szLinkUrl,sizeof(pl.szLinkUrl));
		bis.read((char*)pl.szIconUrl,sizeof(pl.szIconUrl));

		return bis;
	}
};

//��ѯ��б���Ϣ���
struct CMD_GP_UserActivityList
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_ACTIVITY_LIST_REP};
	
	unsigned short	wCode;					//���ز�ѯ�����0�ɹ�������������
	unsigned short	wCount;					//��¼���������5��
	stUserActivity	activity[5];			//���5��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserActivityList() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserActivityList& pl)
	{
		bos << pl.wCode;
		bos << pl.wCount;
		for (int i=0; i<pl.wCount; i++)
		{
			bos << pl.activity[i];
		}

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserActivityList& pl)
	{	
		pl.reset();

		bis >> pl.wCode;
		bis >> pl.wCount;
		for (int i=0; i<pl.wCount; i++)
		{
			bis >> pl.activity[i];
		}

		return bis;
	}
};

//��ѯָ�����Ϣ
struct CMD_GP_UserActivityReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_ACTIVITY_REQ};

	unsigned int	dwActivityID;	//�id
	unsigned int	dwUserID;		//�û�id

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserActivityReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserActivityReq& pl)
	{
		bos << pl.dwActivityID;
		bos << pl.dwUserID;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserActivityReq& pl)
	{	
		pl.reset();

		bis >> pl.dwActivityID;
		bis >> pl.dwUserID;
		return bis;
	}
};

//��ѯָ�����Ϣ���
struct CMD_GP_UserActivity
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_ACTIVITY_REP};
	
	unsigned int	dwActivityID;			//�id
	unsigned int	dwUserID;				//�û�id
	unsigned short	wCode;					//���ز�ѯ�����0�ɹ�������������
	unsigned short	wCount;					//��������������5��
	char			szText[5][100];			//���������
	char			szResourceUrl[50];		//��Դ���ص�ַ
	char			szParam[128];			//������n:v|n:v��ʽ��Ŀǰ֧��m:10|n:5|t:200|u:30 ����m��ʾ�ҵ��ܳ齱������n��ʾ�ѳ������t��ʾ�ܾ�����u��ʾ���پֵ�һ��


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserActivity() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserActivity& pl)
	{
		bos << pl.dwActivityID;
		bos << pl.dwUserID;
		bos << pl.wCode;
		bos << pl.wCount;
		bos.write((char*)pl.szText,sizeof(pl.szText[0])*pl.wCount);
		bos.write((char*)pl.szResourceUrl,sizeof(pl.szResourceUrl));
		bos.write((char*)pl.szParam,sizeof(pl.szParam));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserActivity& pl)
	{	
		pl.reset();

		bis >> pl.dwActivityID;
		bis >> pl.dwUserID;
		bis >> pl.wCode;
		bis >> pl.wCount;
		bis.read((char*)pl.szText,sizeof(pl.szText[0])*pl.wCount);
		bis.read((char*)pl.szResourceUrl,sizeof(pl.szResourceUrl));
		bis.read((char*)pl.szParam,sizeof(pl.szParam));

		return bis;
	}
};

//��齱
struct CMD_GP_UserActivityLuckyReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_ACTIVITY_LUCKY_REQ};

	unsigned int	dwActivityID;	//�id
	unsigned int	dwUserID;		//�û�id

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserActivityLuckyReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserActivityLuckyReq& pl)
	{
		bos << pl.dwActivityID;
		bos << pl.dwUserID;
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserActivityLuckyReq& pl)
	{	
		pl.reset();

		bis >> pl.dwActivityID;
		bis >> pl.dwUserID;
		return bis;
	}
};

//��齱���
struct CMD_GP_UserActivityLucky
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_ACTIVITY_LUCKY_REP};
	
	unsigned int	dwActivityID;			//�id
	unsigned int	dwUserID;				//�û�id
	unsigned short	wCode;					//�齱����� 0�ɹ��������Ǵ�����
	unsigned int	dwPrizeID;				//��Ʒid
	unsigned int	dwPrice;				//��Ʒ��ֵ��ָ���ֶ������>0ʱ����Ҫͬ�����½���ĲƸ���Ϣ
	char			szImageUrl[50];			//��ƷͼƬ���ص�ַ
	char			szPrizeName[50];		//��Ʒ����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserActivityLucky() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserActivityLucky& pl)
	{
		bos << pl.dwActivityID;
		bos << pl.dwUserID;
		bos << pl.wCode;
		bos << pl.dwPrizeID;
		bos << pl.dwPrice;

		bos.write((char*)pl.szImageUrl,sizeof(pl.szImageUrl));
		bos.write((char*)pl.szPrizeName,sizeof(pl.szPrizeName));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserActivityLucky& pl)
	{	
		pl.reset();

		bis >> pl.dwActivityID;
		bis >> pl.dwUserID;
		bis >> pl.wCode;
		bis >> pl.dwPrizeID;
		bis >> pl.dwPrice;

		bis.read((char*)pl.szImageUrl,sizeof(pl.szImageUrl));
		bis.read((char*)pl.szPrizeName,sizeof(pl.szPrizeName));

		return bis;
	}
};

//�н���¼��ѯ����
struct CMD_GP_UserActivityRecordReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_ACTIVITY_RECORD_REQ};
	
	unsigned int					nPage;			//ҳ��	
	unsigned int					dwUserID;		//��� ID
	unsigned int					dwActivityID;	//� ID	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserActivityRecordReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserActivityRecordReq& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;
		bos << pl.dwActivityID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserActivityRecordReq& pl)
	{	
		bis >> pl.nPage;
		bis >> pl.dwUserID;
		bis >> pl.dwActivityID;

		return bis;
	}
};

//�н���¼�б�
struct CMD_GP_UserActivityRecord
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_ACTIVITY_RECORD};
	
	char							szStatus[32];		//״̬	
	char							szPrizename[32];	//��Ʒ����	
	char							szExchangeDate[32];	//ʱ��	
	unsigned int					dwID;				//ID
	unsigned int					dwPrizeID;			//��Ʒ ID
	unsigned int					dwTotal;			//��Ʒ����
	unsigned int					dwUserID;			//��� ID
	unsigned int					dwActivityID;		//� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserActivityRecord() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserActivityRecord& pl)
	{
		bos.write((char*)pl.szStatus,sizeof(pl.szStatus));
		bos.write((char*)pl.szPrizename,sizeof(pl.szPrizename));
		bos.write((char*)pl.szExchangeDate,sizeof(pl.szExchangeDate));

		bos << pl.dwID;
		bos << pl.dwPrizeID;
		bos << pl.dwTotal;
		bos << pl.dwUserID;
		bos << pl.dwActivityID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserActivityRecord& pl)
	{	
		pl.reset();

		bis.read((char*)pl.szStatus,sizeof(pl.szStatus));
		bis.read((char*)pl.szPrizename,sizeof(pl.szPrizename));
		bis.read((char*)pl.szExchangeDate,sizeof(pl.szExchangeDate));

		bis >> pl.dwID;
		bis >> pl.dwPrizeID;
		bis >> pl.dwTotal;
		bis >> pl.dwUserID;
		bis >> pl.dwActivityID;

		return bis;
	}
};

//�н���¼�б����
struct CMD_GP_UserActivityRecordFinish
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_ACTIVITY_RECORD_FINISH};

	unsigned int					dwTotal;					//��Ʒ����
	unsigned int					dwTotalofCurPage;			//��ǰҳ��Ʒ����
	unsigned int					dwUserID;					//��� ID
	unsigned int					dwActivityID;				//� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserActivityRecordFinish() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserActivityRecordFinish& pl)
	{
		bos << pl.dwTotal;
		bos << pl.dwTotalofCurPage;
		bos << pl.dwUserID;
		bos << pl.dwActivityID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserActivityRecordFinish& pl)
	{	
		pl.reset();

		bis >> pl.dwTotal;
		bis >> pl.dwTotalofCurPage;
		bis >> pl.dwUserID;
		bis >> pl.dwActivityID;

		return bis;
	}
};

//ǩ��
struct CMD_GP_UserSignInReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_SIGNIN_REQ};

	unsigned int					dwUserID;							//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserSignInReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserSignInReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserSignInReq& pl)
	{	
		bis >> pl.dwUserID;

		return bis;
	}
};

//ǩ�����
struct CMD_GP_UserSignIn
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_SIGNIN};

	unsigned short							wRankAward;
	unsigned short							wRankNum;							
	unsigned short							wAllSend;						
	unsigned short							wTodaySend;						
	unsigned short							wTimes;			//����ǩ���˶��ٴ�	
	unsigned char							cbTodaySign;	//�����Ƿ�ǩ��		
	unsigned int							dwGoldScore;							

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserSignIn() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserSignIn& pl)
	{
		bos << pl.wRankAward;
		bos << pl.wRankNum;
		bos << pl.wAllSend;
		bos << pl.wTodaySend;
		bos << pl.wTimes;
		bos << pl.cbTodaySign;
		bos << pl.dwGoldScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserSignIn& pl)
	{	
		pl.reset();

		bis >> pl.wRankAward;
		bis >> pl.wRankNum;
		bis >> pl.wAllSend;
		bis >> pl.wTodaySend;
		bis >> pl.wTimes;
		bis >> pl.cbTodaySign;
		bis >> pl.dwGoldScore;

		return bis;
	}
};

//�콱
struct CMD_GP_UserGetAwardReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_GETAWARD_REQ};

	unsigned int					dwUserID;							//��� ID
	unsigned int					dwTaskID;							//���� ID:1-����Ȧ��2-���ѣ�3~5���˹���ÿ������3���׶Σ�6~8���˹���ÿ������3���׶�
																		// 10~22Ϊ���˹�ϵͳ����13���׶�  30~42Ϊ���˹�ϵͳ����13���׶�

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserGetAwardReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserGetAwardReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwTaskID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserGetAwardReq& pl)
	{	
		bis >> pl.dwUserID;
		bis >> pl.dwTaskID;

		return bis;
	}
};

//�콱���
struct CMD_GP_UserGetAward
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_GETAWARD};

	unsigned int					dwTaskID;		//���� ID		
	unsigned int					dwScore;		//������
	unsigned char					cbStatus;		//�Ƿ��콱			

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserGetAward() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserGetAward& pl)
	{
		bos << pl.dwTaskID;
		bos << pl.dwScore;
		bos << pl.cbStatus;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserGetAward& pl)
	{	
		pl.reset();

		bis >> pl.dwTaskID;
		bis >> pl.dwScore;
		bis >> pl.cbStatus;

		return bis;
	}
};

//�һ�������Ϣ���󣨲�ѯ�𶹡��ֻ��š������ֻ��ţ�
struct CMD_GP_UserExchangeInfoReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_INFO_REQ};

	unsigned int					dwUserID;		//��� ID
	char							szPhone[64];	//�绰	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeInfoReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeInfoReq& pl)
	{
		bos << pl.dwUserID;

		bos.write((char*)pl.szPhone,sizeof(pl.szPhone));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeInfoReq& pl)
	{	
		bis >> pl.dwUserID;

		bis.read((char*)pl.szPhone,sizeof(pl.szPhone));

		return bis;
	}
};

//�һ�������Ϣ�����ؽ𶹡��ֻ��ţ�
struct CMD_GP_UserExchangeInfo
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_INFO};

	char									szPhone[64];	//�绰	
	unsigned int							dwGold;			//��		
	short									nCode;			//���		

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeInfo() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeInfo& pl)
	{
		bos << pl.dwGold;
		bos << pl.nCode;

		bos.write((char*)pl.szPhone,sizeof(pl.szPhone));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeInfo& pl)
	{	
		pl.reset();

		bis >> pl.dwGold;
		bis >> pl.nCode;

		bis.read((char*)pl.szPhone,sizeof(pl.szPhone));

		return bis;
	}
};

//�һ���Ʒ��ѯ����
struct CMD_GP_UserExchangeProductReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_PRODUCT_REQ};

	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeProductReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeProductReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeProductReq& pl)
	{	
		bis >> pl.dwUserID;

		return bis;
	}
};

//�һ���Ʒ�б�
struct CMD_GP_UserExchangeProduct
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_PRODUCT};

	unsigned int					dwAwardID;			//��Ʒ ID
	unsigned int					dwPrice;			//�۸�		
	unsigned int					dwLeft;				//ʣ������	
	char							szAwardname[64];	//��Ʒ����	
	char							szAwardImage[128];	//��ƷͼƬ	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeProduct() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeProduct& pl)
	{
		bos << pl.dwAwardID;
		bos << pl.dwPrice;
		bos << pl.dwLeft;

		bos.write((char*)pl.szAwardname,sizeof(pl.szAwardname));
		bos.write((char*)pl.szAwardImage,sizeof(pl.szAwardImage));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeProduct& pl)
	{	
		pl.reset();

		bis >> pl.dwAwardID;
		bis >> pl.dwPrice;
		bis >> pl.dwLeft;

		bis.read((char*)pl.szAwardname,sizeof(pl.szAwardname));
		bis.read((char*)pl.szAwardImage,sizeof(pl.szAwardImage));

		return bis;
	}
};


//�һ���Ʒ��ѯ����
struct CMD_GP_UserExchangeProductReq_V2
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_PRODUCT_REQ_V2};

	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeProductReq_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeProductReq_V2& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeProductReq_V2& pl)
	{	
		bis >> pl.dwUserID;

		return bis;
	}
};

//�һ���Ʒ�б�
struct CMD_GP_UserExchangeProduct_V2
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_PRODUCT_V2};

	unsigned int					dwAwardID;			//��Ʒ ID
	unsigned int					dwPrice;			//�۸�		
	unsigned int					dwLeft;				//ʣ������	
	unsigned int					dwType;				//��Ʒ����:1Ϊ���Զ����ŵģ�Ĭ��Ϊ0	
	char							szAwardname[64];	//��Ʒ����	
	char							szAwardImage[128];	//��ƷͼƬ	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeProduct_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeProduct_V2& pl)
	{
		bos << pl.dwAwardID;
		bos << pl.dwPrice;
		bos << pl.dwLeft;
		bos << pl.dwType;

		bos.write((char*)pl.szAwardname,sizeof(pl.szAwardname));
		bos.write((char*)pl.szAwardImage,sizeof(pl.szAwardImage));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeProduct_V2& pl)
	{	
		pl.reset();

		bis >> pl.dwAwardID;
		bis >> pl.dwPrice;
		bis >> pl.dwLeft;
		bis >> pl.dwType;

		bis.read((char*)pl.szAwardname,sizeof(pl.szAwardname));
		bis.read((char*)pl.szAwardImage,sizeof(pl.szAwardImage));

		return bis;
	}
};

//�һ���Ʒ�б����
struct CMD_GP_UserExchangeProductFinish
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_PRODUCT_FINISH};

	unsigned int					dwTotal;		//����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeProductFinish() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeProductFinish& pl)
	{
		bos << pl.dwTotal;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeProductFinish& pl)
	{	
		pl.reset();

		bis >> pl.dwTotal;

		return bis;
	}
};


//�һ���Ʒ����
struct CMD_GP_UserExchangeReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_REQ};

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwAwardID;		//��Ʒ ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwAwardID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeReq& pl)
	{	
		bis >> pl.dwUserID;
		bis >> pl.dwAwardID;

		return bis;
	}
};

//�һ���Ʒ
struct CMD_GP_UserExchange
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE};

	short							nCode;				//���				
	unsigned int					dwAwardID;			//��Ʒ ID
	unsigned int					dwGold;				//��ǰ����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchange() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchange& pl)
	{
		bos << pl.nCode;
		bos << pl.dwAwardID;
		bos << pl.dwGold;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchange& pl)
	{	
		pl.reset();

		bis >> pl.nCode;
		bis >> pl.dwAwardID;
		bis >> pl.dwGold;

		return bis;
	}
};


//�һ���Ʒ����
struct CMD_GP_UserExchangeReq_V2
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_REQ_V2};

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwAwardID;		//��Ʒ ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeReq_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeReq_V2& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwAwardID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeReq_V2& pl)
	{	
		bis >> pl.dwUserID;
		bis >> pl.dwAwardID;

		return bis;
	}
};

//�һ���Ʒ
struct CMD_GP_UserExchange_V2
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_V2};

	short							nCode;				//���				
	unsigned int					dwAwardID;			//��Ʒ ID
	unsigned int					dwGold;				//��ǰ����
	unsigned int					dwScore;			//��ǰ���ֶ�����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchange_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchange_V2& pl)
	{
		bos << pl.nCode;
		bos << pl.dwAwardID;
		bos << pl.dwGold;
		bos << pl.dwScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchange_V2& pl)
	{	
		pl.reset();

		bis >> pl.nCode;
		bis >> pl.dwAwardID;
		bis >> pl.dwGold;
		bis >> pl.dwScore;

		return bis;
	}
};

//�һ���¼��ѯ����
struct CMD_GP_UserExchangeRecordReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_RECORD_REQ};

	
	unsigned int					nPage;			//ҳ��	
	unsigned int					dwUserID;		//��� ID	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeRecordReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeRecordReq& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeRecordReq& pl)
	{	
		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};

//�һ���¼�б�
struct CMD_GP_UserExchangeRecord
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_RECORD};
	
	char							szStatus[32];		//״̬	
	char							szAwardname[32];	//��Ʒ����	
	char							szExchangeDate[32];	//ʱ��	
	unsigned int					dwID;				//ID
	unsigned int					dwAwardID;			//��Ʒ ID
	unsigned int					dwTotal;			//��Ʒ����
//	unsigned int					dwExchangeDate;		//ʱ��	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeRecord() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeRecord& pl)
	{
		bos.write((char*)pl.szStatus,sizeof(pl.szStatus));
		bos.write((char*)pl.szAwardname,sizeof(pl.szAwardname));
		bos.write((char*)pl.szExchangeDate,sizeof(pl.szExchangeDate));

		bos << pl.dwID;
		bos << pl.dwAwardID;
		bos << pl.dwTotal;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeRecord& pl)
	{	
		pl.reset();

		bis.read((char*)pl.szStatus,sizeof(pl.szStatus));
		bis.read((char*)pl.szAwardname,sizeof(pl.szAwardname));
		bis.read((char*)pl.szExchangeDate,sizeof(pl.szExchangeDate));

		bis >> pl.dwID;
		bis >> pl.dwAwardID;
		bis >> pl.dwTotal;

		return bis;
	}
};

//�һ���¼�б����
struct CMD_GP_UserExchangeRecordFinish
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_EXCHANGE_RECORD_FINISH};

	unsigned int					dwTotal;					//��Ʒ����
	unsigned int					dwTotalofCurPage;			//��ǰҳ��Ʒ����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserExchangeRecordFinish() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserExchangeRecordFinish& pl)
	{
		bos << pl.dwTotal;
		bos << pl.dwTotalofCurPage;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserExchangeRecordFinish& pl)
	{	
		pl.reset();

		bis >> pl.dwTotal;
		bis >> pl.dwTotalofCurPage;

		return bis;
	}
};

//����У��
struct CMD_GP_CheckIDReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_CHECK_ID_REQ};
	
	char	szAccount[NAME_LEN];				//���ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CheckIDReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_CheckIDReq& pl)
	{
		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_CheckIDReq& pl)
	{	
		pl.reset();

		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));

		return bis;
	}
};

struct CMD_GP_CheckIDRep
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_CHECK_ID_REP};
	
	short	nCode;					//���
	char	szAccount[NAME_LEN];	//���ID
	char	szDescribeMsg[64];		//������Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CheckIDRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_CheckIDRep& pl)
	{
		bos << pl.nCode;

		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));
		bos.write((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_CheckIDRep& pl)
	{	
		pl.reset();

		bis >> pl.nCode;

		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));
		bis.read((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bis;
	}
};

//�ǳ�У��
struct CMD_GP_CheckNickNameReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_CHECK_NICKNAME_REQ};
	
	char	szNickName[NAME_LEN];				//����ǳ�

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CheckNickNameReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_CheckNickNameReq& pl)
	{
		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_CheckNickNameReq& pl)
	{	
		pl.reset();

		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));

		return bis;
	}
};

struct CMD_GP_CheckNickNameRep
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_CHECK_NICKNAME_REP};
	
	short	nCode;					//���
	char	szNickName[NAME_LEN];	//����ǳ�
	char	szDescribeMsg[64];		//������Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CheckNickNameRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_CheckNickNameRep& pl)
	{
		bos << pl.nCode;

		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));
		bos.write((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_CheckNickNameRep& pl)
	{	
		pl.reset();

		bis >> pl.nCode;

		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));
		bis.read((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bis;
	}
};

//ע��
struct CMD_GP_RegisterReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_REGISTER_REQ};
	
	short	nGender;						//����Ա�
	char	szAccount[NAME_LEN];			//���ID
	char	szNickName[NAME_LEN];			//����ǳ�
	char	szPassWord[PASS_LEN];			//��¼����
	char	szComputerID[COMPUTER_ID_LEN];	//Ӳ����ʶ
	char	szPhone[NAME_LEN];			//����ֻ���

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_RegisterReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_RegisterReq& pl)
	{
		bos << pl.nGender;

		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));
		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));
		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bos.write((char*)pl.szComputerID,sizeof(pl.szComputerID));
		bos.write((char*)pl.szPhone,sizeof(pl.szPhone));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_RegisterReq& pl)
	{	
		pl.reset();

		bis >> pl.nGender;

		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));
		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));
		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bis.read((char*)pl.szComputerID,sizeof(pl.szComputerID));
		bis.read((char*)pl.szPhone,sizeof(pl.szPhone));

		return bis;
	}
};

//ע��,��������ʶ
struct CMD_GP_RegisterWithChannelReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_REGISTER_CHANNEL_REQ};
	
	short	nGender;						//����Ա�
	char	szAccount[NAME_LEN];			//���ID
	char	szNickName[NAME_LEN];			//����ǳ�
	char	szPassWord[PASS_LEN];			//��¼����
	char	szComputerID[COMPUTER_ID_LEN];	//Ӳ����ʶ
	char	szPhone[NAME_LEN];			//����ֻ���
	char	szChannel[NAME_LEN];			//�ͻ���������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_RegisterWithChannelReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_RegisterWithChannelReq& pl)
	{
		bos << pl.nGender;

		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));
		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));
		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bos.write((char*)pl.szComputerID,sizeof(pl.szComputerID));
		bos.write((char*)pl.szPhone,sizeof(pl.szPhone));
		bos.write((char*)pl.szChannel,sizeof(pl.szChannel));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_RegisterWithChannelReq& pl)
	{	
		pl.reset();

		bis >> pl.nGender;

		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));
		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));
		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bis.read((char*)pl.szComputerID,sizeof(pl.szComputerID));
		bis.read((char*)pl.szPhone,sizeof(pl.szPhone));
		bis.read((char*)pl.szChannel,sizeof(pl.szChannel));

		return bis;
	}
};

struct CMD_GP_RegisterRep
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_REGISTER_REP};
	
	short	nCode;					//���
	char	szAccount[NAME_LEN];	//�������
	char	szDescribeMsg[64];		//������Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_RegisterRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_RegisterRep& pl)
	{
		bos << pl.nCode;

		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));
		bos.write((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_RegisterRep& pl)
	{	
		pl.reset();

		bis >> pl.nCode;

		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));
		bis.read((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bis;
	}
};

//����
struct CMD_GP_IDUpdateReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_ID_UPDATE_REQ};
	
	short	nGender;						//����Ա�
	char	szAccountOld[NAME_LEN];			//�ɵ��������
	char	szAccount[NAME_LEN];			//�������
	char	szNickName[NAME_LEN];			//����ǳ�
	char	szPassWord[PASS_LEN];			//��¼����
	char	szComputerID[COMPUTER_ID_LEN];	//Ӳ����ʶ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_IDUpdateReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_IDUpdateReq& pl)
	{
		bos << pl.nGender;

		bos.write((char*)pl.szAccountOld,sizeof(pl.szAccountOld));
		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));
		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));
		bos.write((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bos.write((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_IDUpdateReq& pl)
	{	
		pl.reset();

		bis >> pl.nGender;

		bis.read((char*)pl.szAccountOld,sizeof(pl.szAccountOld));
		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));
		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));
		bis.read((char*)pl.szPassWord,sizeof(pl.szPassWord));
		bis.read((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bis;
	}
};

struct CMD_GP_IDUpdateRep
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_ID_UPDATE_REP};
	
	short	nCode;					//���
	char	szAccount[NAME_LEN];	//�������
	char	szDescribeMsg[128];		//������Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_IDUpdateRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_IDUpdateRep& pl)
	{
		bos << pl.nCode;

		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));
		bos.write((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_IDUpdateRep& pl)
	{	
		pl.reset();

		bis >> pl.nCode;

		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));
		bis.read((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bis;
	}
};

//��ѯ�û���Ϣ
struct CMD_GP_UserInfoReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_INFO_REQ};

	unsigned int	dwUserID;		//���ID
	char	szAccount[NAME_LEN];			//�������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserInfoReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserInfoReq& pl)
	{
		bos << pl.dwUserID;

		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserInfoReq& pl)
	{	
		pl.reset();

		bis >> pl.dwUserID;

		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));

		return bis;
	}
};

struct CMD_GP_UserInfoRep
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_INFO_REP};
	
	short	nCode;					//���
	short	nGender;				//����Ա�
	unsigned int	dwUserID;		//���ID
	char	szAccount[NAME_LEN];	//�������
	char	szNickname[NAME_LEN];	//����ǳ�
	char	szPhone[NAME_LEN];		//�󶨵��ֻ���
	char	szExt[128];				//������Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserInfoRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserInfoRep& pl)
	{
		bos << pl.nCode;
		bos << pl.nGender;
		bos << pl.dwUserID;

		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));
		bos.write((char*)pl.szNickname,sizeof(pl.szNickname));
		bos.write((char*)pl.szPhone,sizeof(pl.szPhone));
		bos.write((char*)pl.szExt,sizeof(pl.szExt));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserInfoRep& pl)
	{	
		pl.reset();

		bis >> pl.nCode;
		bis >> pl.nGender;
		bis >> pl.dwUserID;

		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));
		bis.read((char*)pl.szNickname,sizeof(pl.szNickname));
		bis.read((char*)pl.szPhone,sizeof(pl.szPhone));
		bis.read((char*)pl.szExt,sizeof(pl.szExt));

		return bis;
	}
};

//��ѯ�û����֤�˺���Ϣ
struct CMD_GP_UserInfoIDCARDReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_INFO_ID_CARD_REQ };

	unsigned int	dwUserID;		//���ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserInfoIDCARDReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserInfoIDCARDReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserInfoIDCARDReq& pl)
	{
		pl.reset();

		bis >> pl.dwUserID;

		return bis;
	}
};

// ��ѯ���֤�Ž��
struct CMD_GP_UserInfoIDCARDRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_INFO_ID_CARD_REP };

	unsigned int	dwUserID;					//���ID
	char	szIdNum[128];				//���֤�˺���Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserInfoIDCARDRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserInfoIDCARDRep& pl)
	{
		bos << pl.dwUserID;
		bos.write((char*)pl.szIdNum, sizeof(pl.szIdNum));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserInfoIDCARDRep& pl)
	{
		pl.reset();

		bis >> pl.dwUserID;

		bis.read((char*)pl.szIdNum, sizeof(pl.szIdNum));

		return bis;
	}
};

//�����ύ���֤��Ϣ(���������֤��)
struct CMD_GP_UserAuthenticationReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_AUTHENTICA_REQ };

	unsigned int	dwUserID;				//��������˺�
	char	szName[NAME_LEN];				// �������
	char	szIdCardNum[32];				// ������֤�˺�

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserAuthenticationReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserAuthenticationReq& pl)
	{
		bos << pl.dwUserID;

		bos.write((char*)pl.szName, sizeof(pl.szName));
		bos.write((char*)pl.szIdCardNum, sizeof(pl.szIdCardNum));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserAuthenticationReq& pl)
	{
		pl.reset();

		bis >> pl.dwUserID;

		bis.read((char*)pl.szName, sizeof(pl.szName));
		bis.read((char*)pl.szIdCardNum, sizeof(pl.szIdCardNum));

		return bis;
	}
};

// ��ѯ���֤�Ž��
struct CMD_GP_UserAuthenticationRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_AUTHENTICA_REP };

	unsigned int	dwUserID;				//��������˺�
	short resultCode;						// �����Ϣ				

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserAuthenticationRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserAuthenticationRep& pl)
	{
		bos << pl.dwUserID;
		bos << pl.resultCode;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserAuthenticationRep& pl)
	{
		pl.reset();

		bis >> pl.dwUserID;
		bis >> pl.resultCode;

		return bis;
	}
};

struct CMD_GP_ResetPwdReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_RESET_PWD_REQ};

	unsigned int	dwUserID;		//���ID
	char			szAccount[NAME_LEN];				//���ID
	char			szPassword[PASS_LEN];				//�������
	char			szCode[NAME_LEN];					//У����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_ResetPwdReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_ResetPwdReq& pl)
	{
		bos << pl.dwUserID;

		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));
		bos.write((char*)pl.szPassword,sizeof(pl.szPassword));
		bos.write((char*)pl.szCode,sizeof(pl.szCode));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_ResetPwdReq& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;

		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));
		bis.read((char*)pl.szPassword,sizeof(pl.szPassword));
		bis.read((char*)pl.szCode,sizeof(pl.szCode));

		return bis;
	}
};

//�޸Ľ��
struct CMD_GP_ResetPwdRep
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_RESET_PWD_REP};
	
	short	nCode;					//���
	char	szDescribeMsg[128];		//������Ϣ
	char	szAccount[NAME_LEN];	//���ID
	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_ResetPwdRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_ResetPwdRep& pl)
	{
		bos << pl.nCode;

		bos.write((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));
		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_ResetPwdRep& pl)
	{	
		pl.reset();
		bis >> pl.nCode;

		bis.read((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));
		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));

		return bis;
	}
};

//��������
struct CMD_GP_ModifyIndividual
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_MODIFY_INDIVIDUAL};

	short							nGender;							//����Ա�
	char							szNickname[NAME_LEN];				//����ǳ�
	char							szPhone[NAME_LEN];					//�绰
	char							szAccount[NAME_LEN];				//У����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_ModifyIndividual() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_ModifyIndividual& pl)
	{
		bos << pl.nGender;

		bos.write((char*)pl.szNickname,sizeof(pl.szNickname));
		bos.write((char*)pl.szPhone,sizeof(pl.szPhone));
		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_ModifyIndividual& pl)
	{	
		pl.reset();
		bis >> pl.nGender;

		bis.read((char*)pl.szNickname,sizeof(pl.szNickname));
		bis.read((char*)pl.szPhone,sizeof(pl.szPhone));
		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));

		return bis;
	}
};


//�޸Ľ��
struct CMD_GP_ModifyIndividualResult
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_MODIFY_INDIVIDUAL_RESULT};
	
	short	nCode;					//���
	char	szAccount[NAME_LEN];	//���ID
	char	szDescribeMsg[128];		//������Ϣ
	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_ModifyIndividualResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_ModifyIndividualResult& pl)
	{
		bos << pl.nCode;

		bos.write((char*)pl.szAccount,sizeof(pl.szAccount));
		bos.write((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_ModifyIndividualResult& pl)
	{	
		pl.reset();
		
		bis >> pl.nCode;
		bis.read((char*)pl.szAccount,sizeof(pl.szAccount));
		bis.read((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bis;
	}
};

//����ǩ��
struct CMD_GP_ModifyDescribeInfo
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_MODIFY_DESCRIBE_INFO };

	unsigned int					dwUserID;		//���ID
	char							szDescribe[128];				//����ǩ��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_ModifyDescribeInfo() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_ModifyDescribeInfo& pl)
	{
		bos << pl.dwUserID;
		bos.write((char*)pl.szDescribe, sizeof(pl.szDescribe));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_ModifyDescribeInfo& pl)
	{
		pl.reset();
		bis >> pl.dwUserID;
		bis.read((char*)pl.szDescribe, sizeof(pl.szDescribe));

		return bis;
	}
};

//��ѯ�û��Ƿ������ƹ㽱��
struct CMD_GP_UserCanSpread
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_CAN_SPREAD_REQ};

	unsigned int	dwUserID;		//���ID
	char	szComputerID[COMPUTER_ID_LEN];	//Ӳ����ʶ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserCanSpread() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserCanSpread& pl)
	{
		bos << pl.dwUserID;
		bos.write((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserCanSpread& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;
		bis.read((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bis;
	}
};

struct CMD_GP_UserCanSpreadResult
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_CAN_SPREAD_REP};

	unsigned int	dwUserID;		//���ID
	short	nCode;					//���
	char	szDescribeMsg[128];		//������Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserCanSpreadResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserCanSpreadResult& pl)
	{
		bos << pl.dwUserID;
		bos << pl.nCode;
		
		bos.write((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserCanSpreadResult& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.nCode;

		bis.read((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bis;
	}
};

//��ѯ�û��Ƿ������ƹ㽱��
struct CMD_GP_UserGetSpread
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_GET_SPREAD_REQ};

	unsigned int	dwUserID;		//���ID
	unsigned int	dwSpreaderID;	//�ƹ�ԱID
	char	szComputerID[COMPUTER_ID_LEN];	//Ӳ����ʶ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserGetSpread() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserGetSpread& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwSpreaderID;

		bos.write((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserGetSpread& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.dwSpreaderID;
		
		bis.read((char*)pl.szComputerID,sizeof(pl.szComputerID));

		return bis;
	}
};

struct CMD_GP_UserGetSpreadResult
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_GET_SPREAD_REP};

	unsigned int	dwUserID;		//���ID
	unsigned int	dwSpreaderID;	//�ƹ�ԱID
	unsigned int	dwAmount;		//������
	unsigned int	dwType;			//��������
	short	nCode;					//���
	char	szDescribeMsg[128];		//������Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserGetSpreadResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserGetSpreadResult& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwSpreaderID;
		bos << pl.dwAmount;
		bos << pl.dwType;
		bos << pl.nCode;
		
		bos.write((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserGetSpreadResult& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.dwSpreaderID;
		bis >> pl.dwAmount;
		bis >> pl.dwType;
		bis >> pl.nCode;

		bis.read((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bis;
	}
};

//��ѯ�ƹ���Ϣ
struct CMD_GP_UserGetSpreaderInfo
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_SPREADER_INFO_REQ};

	unsigned int	dwSpreaderID;	//�ƹ�ԱID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserGetSpreaderInfo() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserGetSpreaderInfo& pl)
	{
		bos << pl.dwSpreaderID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserGetSpreaderInfo& pl)
	{	
		pl.reset();
		bis >> pl.dwSpreaderID;

		return bis;
	}
};

struct CMD_GP_UserGetSpreaderInfoResult
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_SPREADER_INFO_REP};

	unsigned int	dwSpreaderID;	//�ƹ�ԱID
	unsigned int	dwAmount;		//��������
	unsigned int	dwUsers;			//����������
	short	nCount;					//��������������Ϊ10
	short	nCode;					//���
	short	nAward[10];				//�ѷ��ŵĽ����������֧��10��
	char	szNickName[10][NAME_LEN];		//�ǳơ����֧��10��
	char	szDescribeMsg[128];		//������Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserGetSpreaderInfoResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserGetSpreaderInfoResult& pl)
	{
		bos << pl.dwSpreaderID;
		bos << pl.dwAmount;
		bos << pl.dwUsers;
		bos << pl.nCount;
		bos << pl.nCode;
		
		bos.write((char*)pl.nAward,sizeof(pl.nAward));
		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));
		bos.write((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserGetSpreaderInfoResult& pl)
	{	
		pl.reset();
		bis >> pl.dwSpreaderID;
		bis >> pl.dwAmount;
		bis >> pl.dwUsers;
		bis >> pl.nCount;
		bis >> pl.nCode;

		bis.read((char*)pl.nAward,sizeof(pl.nAward));
		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));
		bis.read((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bis;
	}
};




//����ͷ��
struct CMD_GP_UploadCustomFace
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_UPLOAD_FACE};

	unsigned int								dwUserID;						//��� ID
	unsigned short								wCurrentSize;					//��ǰ��С
	bool										bLastPacket;					//����ʶ
	bool										bFirstPacket;					//��һ����ʶ
	unsigned char								bFaceData[2048];				//ͷ������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UploadCustomFace() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UploadCustomFace& pl)
	{
		bos << pl.dwUserID;
		bos << pl.wCurrentSize;
		bos << pl.bLastPacket;
		bos << pl.bFirstPacket;

		bos.write((char*)pl.bFaceData,sizeof(pl.bFaceData));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UploadCustomFace& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.wCurrentSize;
		bis >> pl.bLastPacket;
		bis >> pl.bFirstPacket;

		bis.read((char*)pl.bFaceData,sizeof(pl.bFaceData));

		return bis;
	}
};

//���سɹ�
struct CMD_GP_DownloadFaceSuccess
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_DOWNLOAD_FACE};

	unsigned int							dwToltalSize;						//�ܹ���С
	unsigned int							dwCurrentSize;						//��ǰ��С
	unsigned int							dwUserID;							//��� ID
	unsigned char							bFaceData[2048];					//ͷ������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_DownloadFaceSuccess() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_DownloadFaceSuccess& pl)
	{
		bos << pl.dwToltalSize;
		bos << pl.dwCurrentSize;
		bos << pl.dwUserID;

		bos.write((char*)pl.bFaceData,sizeof(pl.bFaceData));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_DownloadFaceSuccess& pl)
	{	
		pl.reset();
		bis >> pl.dwToltalSize;
		bis >> pl.dwCurrentSize;
		bis >> pl.dwUserID;

		bis.read((char*)pl.bFaceData,sizeof(pl.bFaceData));

		return bis;
	}
};

//����ͷ��
struct CMD_GP_DownloadFace
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_DOWNLOAD_FACE};

	unsigned int							dwUserID;							//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_DownloadFace() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_DownloadFace& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_DownloadFace& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;

		return bis;
	}
};

//�ϴ����
struct CMD_GP_UploadFaceResult
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_UPLOAD_FACE_RESULT};

	unsigned int							dwFaceVer;							//ͷ��汾
	bool							bOperateSuccess;					//�ɹ���ʶ
	char							szDescribeMsg[128];					//������Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UploadFaceResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UploadFaceResult& pl)
	{
		bos << pl.dwFaceVer;
		bos << pl.bOperateSuccess;

		bos.write((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UploadFaceResult& pl)
	{	
		pl.reset();
		bis >> pl.dwFaceVer;
		bis >> pl.bOperateSuccess;

		bis.read((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bis;
	}
};

//ɾ�����
struct CMD_GP_DeleteFaceResult
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_DELETE_FACE_RESULT};

	unsigned int							dwFaceVer;							//ͷ��汾
	bool							bOperateSuccess;					//�ɹ���ʶ
	char							szDescribeMsg[128];					//������Ϣ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_DeleteFaceResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_DeleteFaceResult& pl)
	{
		bos << pl.dwFaceVer;
		bos << pl.bOperateSuccess;

		bos.write((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_DeleteFaceResult& pl)
	{	
		pl.reset();
		bis >> pl.dwFaceVer;
		bis >> pl.bOperateSuccess;

		bis.read((char*)pl.szDescribeMsg,sizeof(pl.szDescribeMsg));

		return bis;
	}
};

//ɾ����Ϣ
struct CMD_GP_CustomFaceDelete
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_CUSTOM_FACE_DELETE};

	unsigned int							dwUserID;							//��� ID
	unsigned int							dwFaceVer;							//ͷ��汾

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_CustomFaceDelete() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_CustomFaceDelete& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwFaceVer;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_CustomFaceDelete& pl)
	{	
		pl.reset();
		bis >> pl.dwUserID;
		bis >> pl.dwFaceVer;

		return bis;
	}
};

////////////////////////////////////////////////////////////////

//��ѯ��������
struct CMD_GP_UserBbsPop
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_BBS_POP_REQ};

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBbsPop() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserBbsPop& pl)
	{
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserBbsPop& pl)
	{
		return bis;
	}
};

//��ѯ��������
struct CMD_GP_UserBbsPop_V2
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_BBS_POP_REQ_V2};
	
	char	szChannel[NAME_LEN];			//������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBbsPop_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserBbsPop_V2& pl)
	{
		bos.write((char*)pl.szChannel,sizeof(pl.szChannel));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserBbsPop_V2& pl)
	{	
		bis.read((char*)pl.szChannel,sizeof(pl.szChannel));

		return bis;
	}
};

struct CMD_GP_UserBbsPopResult
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_BBS_POP_REP};

	//���ܰ�ť��ö��ֵnAction
	enum {	ACTION_IKNOW = 1,		//֪����
			ACTION_CHANGE,			//�һ�
			ACTION_ACTIVE,			//�
			ACTION_EVERYDAYTASK,	//ÿ������
			ACTION_SYSTASK,			//ϵͳ����
			ACTION_INVITE,			//����
			ACTION_USERCENTER,		//��������
			ACTION_FEEDBACK,		//�������
			ACTION_DAGONG3,			//���˹�
			ACTION_DAGONG4,			//���˹�
			ACTION_WEB_MAJIANG,		//�齫web ҳ��
			ACTION_NULL
	};

	short	nBbsScroll;				//������������������ڴ˽ӿ���Ϊ����������
	char	nAction;				//��ť����
	char	szBbsListIDs[64];		//�б���IDֵ��|�ָ�����
	char	szBbsPop[512];		//������������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBbsPopResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserBbsPopResult& pl)
	{
		bos << pl.nBbsScroll;
		bos << pl.nAction;
		
		bos.write((char*)pl.szBbsListIDs,sizeof(pl.szBbsListIDs));
		bos.write((char*)pl.szBbsPop,sizeof(pl.szBbsPop));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserBbsPopResult& pl)
	{	
		pl.reset();
		bis >> pl.nBbsScroll;
		bis >> pl.nAction;

		bis.read((char*)pl.szBbsListIDs,sizeof(pl.szBbsListIDs));
		bis.read((char*)pl.szBbsPop,sizeof(pl.szBbsPop));

		return bis;
	}
};

//��ѯ��������
struct CMD_GP_UserBbsScroll
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_BBS_SCROLL_REQ_V2};

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBbsScroll() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserBbsScroll& pl)
	{
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserBbsScroll& pl)
	{
		return bis;
	}
};

//��ѯ��������
struct CMD_GP_UserBbsScroll_V2
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_BBS_SCROLL_REQ};

	char	szChannel[NAME_LEN];			//������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBbsScroll_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserBbsScroll_V2& pl)
	{
		bos.write((char*)pl.szChannel,sizeof(pl.szChannel));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserBbsScroll_V2& pl)
	{	
		bis.read((char*)pl.szChannel,sizeof(pl.szChannel));

		return bis;
	}
};

struct CMD_GP_UserBbsScrollResult
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_BBS_SCROLL_REP};

	short	nBbsScroll;				//�������������.���10��
	char	szBbsScroll[10][100];	//������������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBbsScrollResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserBbsScrollResult& pl)
	{
		bos << pl.nBbsScroll;

		bos.write((char*)pl.szBbsScroll,sizeof(pl.szBbsScroll));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserBbsScrollResult& pl)
	{	
		pl.reset();
		bis >> pl.nBbsScroll;

		bis.read((char*)pl.szBbsScroll,sizeof(pl.szBbsScroll));

		return bis;
	}
};

//��ѯ�б���
struct CMD_GP_UserBbsList
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_BBS_LIST_REQ_V2};

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBbsList() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserBbsList& pl)
	{
		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserBbsList& pl)
	{
		return bis;
	}
};

//��ѯ�б���
struct CMD_GP_UserBbsList_V2
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_BBS_LIST_REQ};

	char	szChannel[NAME_LEN];			//������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBbsList_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserBbsList_V2& pl)
	{
		bos.write((char*)pl.szChannel,sizeof(pl.szChannel));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserBbsList_V2& pl)
	{	
		bis.read((char*)pl.szChannel,sizeof(pl.szChannel));

		return bis;
	}
};

struct CMD_GP_UserBbsListResult
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_BBS_LIST_REP};

	short	nBbsList;			//�б��������.���3��
	short	iType[3];			//��������
	int		iID[3];				//����ID
	char	szTitle[3][100];	//�������
	char	szDate[3][64];		//����ʱ��
	char	szBbsList[3][512];	//��������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBbsListResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserBbsListResult& pl)
	{
		bos << pl.nBbsList;

		bos.write((char*)pl.iType,sizeof(pl.iType));
		bos.write((char*)pl.iID,sizeof(pl.iID));
		bos.write((char*)pl.szTitle,sizeof(pl.szTitle));
		bos.write((char*)pl.szDate,sizeof(pl.szDate));
		bos.write((char*)pl.szBbsList,sizeof(pl.szBbsList));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserBbsListResult& pl)
	{	
		pl.reset();
		bis >> pl.nBbsList;

		bis.read((char*)pl.iType,sizeof(pl.iType));
		bis.read((char*)pl.iID,sizeof(pl.iID));
		bis.read((char*)pl.szTitle,sizeof(pl.szTitle));
		bis.read((char*)pl.szDate,sizeof(pl.szDate));
		bis.read((char*)pl.szBbsList,sizeof(pl.szBbsList));

		return bis;
	}
};

////////////////////////////////////////////////////
//��ѯ���������Ϣ
struct CMD_GP_UserTaskInfo
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_TASK_INFO_REQ};
	
	unsigned int	dwUserID;		//���ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserTaskInfo() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserTaskInfo& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserTaskInfo& pl)
	{	
		pl.reset();

		bis >> pl.dwUserID;

		return bis;
	}
};

struct CMD_GP_UserTaskInfoResult
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_TASK_INFO_REP};

	unsigned int	dwUserID;		//���ID
	char	szRule[512];		//�������������ǵ�����Ķ����ԣ����Դ˴�����Ϊ�ַ������������ݸ�����Ҫ�Զ��塣
								//Ŀǰ������У�t3:1|a3:5|t4:0|a4:10|st3:1|st4:0|sa3:1|sa4:2
								//���庬�壺t3��ʾ���˹��Ľ�������
								//			t4��ʾ���˹��Ľ�������
								//			a3��ʾ���˹���������
								//			a4��ʾ���˹���������
								//			st3��ʾ���˹���ÿ����������콱���׶Σ�����Ϊ0,1,2,3
								//			st4��ʾ���˹���ÿ����������콱���׶Σ�����Ϊ0,1,2,3
								//			sa3��ʾ���˹���ϵͳ��������콱���׶Σ�����Ϊ0,1,2,3....13
								//			sa4��ʾ���˹���ϵͳ��������콱���׶Σ�����Ϊ0,1,2,3....13
								//			fkt��ʾ�������������
								//			fka��ʾ������ϵͳ��������콱�׶�
	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserTaskInfoResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserTaskInfoResult& pl)
	{
		bos << pl.dwUserID;

		bos.write((char*)pl.szRule,sizeof(pl.szRule));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserTaskInfoResult& pl)
	{	
		pl.reset();

		bis >> pl.dwUserID;

		bis.read((char*)pl.szRule,sizeof(pl.szRule));

		return bis;
	}
};

///////////////////////////////////////////////////////

//���а��ѯ����.���÷�ҳ��ѯ
struct CMD_GP_UserRankingReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_RANKING_REQ};
	
	unsigned int					nPage;			//ҳ��,��1��ʼ
	unsigned int					dwUserID;		//��� ID	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserRankingReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserRankingReq& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserRankingReq& pl)
	{	
		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};

//���а��ѯ����.���÷�ҳ��ѯ
struct CMD_GP_UserRankingReq_V2
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_RANKING_REQ_V2};

	unsigned int					nPage;			//ҳ��,��1��ʼ
	unsigned int					dwUserID;		//��� ID	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserRankingReq_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserRankingReq_V2& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserRankingReq_V2& pl)
	{	
		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};


//���а���ϸ
struct CMD_GP_UserRankingRecord
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_RANKING_RECORD};
	
	short							wIndex;				//����
	unsigned char					cbGender;			//�û��Ա�
	unsigned int					dwGoldScore;		//�û��Ƹ�	
	unsigned int					dwUserID;			//��� ID	
	char							szNickName[32];		//�ǳ�	


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserRankingRecord() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserRankingRecord& pl)
	{
		bos << pl.wIndex;
		bos << pl.cbGender;
		bos << pl.dwGoldScore;
		bos << pl.dwUserID;

		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserRankingRecord& pl)
	{	
		pl.reset();

		bis >> pl.wIndex;
		bis >> pl.cbGender;
		bis >> pl.dwGoldScore;
		bis >> pl.dwUserID;

		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));

		return bis;
	}
};


//���а���ϸ
struct CMD_GP_UserRankingRecord_V2
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_RANKING_RECORD_V2};

	short							wIndex;				//����
	unsigned char					cbGender;			//�û��Ա�
	unsigned int					dwGoldScore;		//�û��Ƹ�	
	unsigned int					dwUserID;			//��� ID	
	char							szNickName[32];		//�ǳ�
	char							szDescribeInfo[128];//����ǩ��


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserRankingRecord_V2() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserRankingRecord_V2& pl)
	{
		bos << pl.wIndex;
		bos << pl.cbGender;
		bos << pl.dwGoldScore;
		bos << pl.dwUserID;

		bos.write((char*)pl.szNickName,sizeof(pl.szNickName));
		bos.write((char*)pl.szDescribeInfo,sizeof(pl.szDescribeInfo));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserRankingRecord_V2& pl)
	{	
		pl.reset();

		bis >> pl.wIndex;
		bis >> pl.cbGender;
		bis >> pl.dwGoldScore;
		bis >> pl.dwUserID;

		bis.read((char*)pl.szNickName,sizeof(pl.szNickName));
		bis.read((char*)pl.szDescribeInfo,sizeof(pl.szDescribeInfo));

		return bis;
	}
};

//���а��б����
struct CMD_GP_UserRankingRecordFinish
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_RANKING_RECORD_FINISH};

	short				nCode;						//���
	unsigned int		dwTotal;					//������������������������ǰҳ����Ϊ0�����������ֶ�Ҳ�����壬��Ϊ0
	unsigned int		dwTotalofCurPage;			//��ǰҳ�������	
	int					dwMyRanking;				//�ҵ�������Ϊ0ʱ����ʾδ���
	unsigned int		dwUserID;					//��� ID	
	char				szDate[64];					//���а�����ʱ��	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserRankingRecordFinish() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserRankingRecordFinish& pl)
	{
		bos << pl.dwTotal;
		bos << pl.dwTotalofCurPage;
		bos << pl.dwMyRanking;
		bos << pl.dwUserID;

		bos.write((char*)pl.szDate,sizeof(pl.szDate));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserRankingRecordFinish& pl)
	{	
		pl.reset();

		bis >> pl.dwTotal;
		bis >> pl.dwTotalofCurPage;
		bis >> pl.dwMyRanking;
		bis >> pl.dwUserID;

		bis.read((char*)pl.szDate,sizeof(pl.szDate));

		return bis;
	}
};

//������а�״̬��Ϣ���
struct CMD_GP_UserRepRankingStatus
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_REP_RANKINGSTATUS };

	unsigned int		dwUserID;					//��� ID
	char				isInRanking;				//����Ƿ����Ϊ1ʱ�μ�������Ϊ0ʱ���μ�����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserRepRankingStatus() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserRepRankingStatus& pl)
	{
		bos << pl.dwUserID;
		bos << pl.isInRanking;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserRepRankingStatus& pl)
	{
		pl.reset();

		bis >> pl.dwUserID;
		bis >> pl.isInRanking;

		return bis;
	}
};

//��������Ƿ������а�
struct CMD_GP_UserModifyRankingStatus
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MODIFY_RANKINGSTATUS };

	unsigned int		dwUserID;					//��� ID
	char				isInRanking;				//����Ƿ����Ϊ1ʱ�μ�������Ϊ0ʱ���μ�����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserModifyRankingStatus() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserModifyRankingStatus& pl)
	{
		bos << pl.dwUserID;
		bos << pl.isInRanking;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserModifyRankingStatus& pl)
	{
		pl.reset();

		bis >> pl.dwUserID;
		bis >> pl.isInRanking;

		return bis;
	}
};

//������������Ƿ������а���
struct CMD_GP_UserRepModifyRankingStatus
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_REP_MODIFY_RANKINGSTATUS };

	short				nCode;					//���
	unsigned int		dwUserID;				//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserRepModifyRankingStatus() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserRepModifyRankingStatus& pl)
	{
		bos << pl.nCode;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserRepModifyRankingStatus& pl)
	{
		pl.reset();

		bis >> pl.nCode;
		bis >> pl.dwUserID;

		return bis;
	}
};
////////////////////////////////////////////////////////

//�ύ���ⷴ������
struct CMD_GP_UserFeedBackReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_FEEDBACK_REQ};

	unsigned int		dwUserID;			//��� ID
	char				szPicture[128];		//ͼƬ��ַ	
	char				szContent[372];		//�������	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFeedBackReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserFeedBackReq& pl)
	{
		bos << pl.dwUserID;
		
		bos.write((char*)pl.szPicture,sizeof(pl.szPicture));
		bos.write((char*)pl.szContent,sizeof(pl.szContent));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserFeedBackReq& pl)
	{	
		bis >> pl.dwUserID;

		bis.read((char*)pl.szPicture,sizeof(pl.szPicture));
		bis.read((char*)pl.szContent,sizeof(pl.szContent));

		return bis;
	}
};

//�ύ���ⷴ���Ľ��
struct CMD_GP_UserFeedBackResult
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_FEEDBACK_REP};

	short				nCode;				//���	
	char				szDetails[128];		//����		

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFeedBackResult() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserFeedBackResult& pl)
	{
		bos << pl.nCode;
		
		bos.write((char*)pl.szDetails,sizeof(pl.szDetails));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserFeedBackResult& pl)
	{	
		pl.reset();

		bis >> pl.nCode;

		bis.read((char*)pl.szDetails,sizeof(pl.szDetails));

		return bis;
	}
};

//���ⷴ���Ľ��.���÷�ҳ��ѯ
struct CMD_GP_UserGetFeedBackReq
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_GET_FEEDBACK_REQ};
	
	unsigned int					nPage;			//ҳ��,��1��ʼ
	unsigned int					dwUserID;		//��� ID	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserGetFeedBackReq() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserGetFeedBackReq& pl)
	{
		bos << pl.nPage;
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserGetFeedBackReq& pl)
	{	
		bis >> pl.nPage;
		bis >> pl.dwUserID;

		return bis;
	}
};

//���ⷴ������ϸ
struct CMD_GP_UserFeedBackRecord
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_FEEDBACK_RECORD};
	
	short							wIndex;				//��ʾ˳��
	unsigned char					cbHavePic;			//�Ƿ���ͼƬ		
	char							szPicture[128];		//ͼƬ��ַ	
	char							szDate[32];			//�����ύʱ��
	unsigned char					szQuestion[372];	//��������
	unsigned char					szAnswer[256];		//��ά�ظ�

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFeedBackRecord() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserFeedBackRecord& pl)
	{
		bos << pl.wIndex;
		bos << pl.cbHavePic;

		bos.write((char*)pl.szPicture,sizeof(pl.szPicture));
		bos.write((char*)pl.szDate,sizeof(pl.szDate));
		bos.write((char*)pl.szQuestion,sizeof(pl.szQuestion));
		bos.write((char*)pl.szAnswer,sizeof(pl.szAnswer));

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserFeedBackRecord& pl)
	{	
		pl.reset();

		bis >> pl.wIndex;
		bis >> pl.cbHavePic;

		bis.read((char*)pl.szPicture,sizeof(pl.szPicture));
		bis.read((char*)pl.szDate,sizeof(pl.szDate));
		bis.read((char*)pl.szQuestion,sizeof(pl.szQuestion));
		bis.read((char*)pl.szAnswer,sizeof(pl.szAnswer));

		return bis;
	}
};

//���ⷴ���б����
struct CMD_GP_UserFeedBackRecordFinish
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_FEEDBACK_RECORD_FINISH};

	short				nCode;						//���	
	unsigned int		dwUserID;					//��� ID	
	unsigned int		dwTotal;					//�������������ǰҳ����Ϊ0�����������ֶ�Ҳ�����壬��Ϊ0
	unsigned int		dwTotalofCurPage;			//��ǰҳ����	

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserFeedBackRecordFinish() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_UserFeedBackRecordFinish& pl)
	{
		bos << pl.nCode;
		bos << pl.dwUserID;
		bos << pl.dwTotal;
		bos << pl.dwTotalofCurPage;

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_UserFeedBackRecordFinish& pl)
	{	
		pl.reset();

		bis >> pl.nCode;
		bis >> pl.dwUserID;
		bis >> pl.dwTotal;
		bis >> pl.dwTotalofCurPage;

		return bis;
	}
};


//�����̳���Ʒ
struct CMD_GP_UserMallProductReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_PRODUCT_REQ };

	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallProductReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallProductReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallProductReq& pl)
	{
		bis >> pl.dwUserID;

		return bis;
	}
};

//�����̳���Ʒ
struct CMD_GP_UserMallProductReq_IOS
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_PRODUCT_REQ_IOS };

	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallProductReq_IOS() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallProductReq_IOS& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallProductReq_IOS& pl)
	{
		bis >> pl.dwUserID;

		return bis;
	}
};

//�̳���Ʒ�б�
struct CMD_GP_UserMallProductResp
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_PRODUCT_RESP };

	unsigned int					productID;			//��Ʒ ID
	unsigned int					productPrice;			//�۸�
	char							szProductName[32];	//��Ʒ����
	char							szProductImage[128];	//��ƷͼƬ

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallProductResp() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallProductResp& pl)
	{
		bos << pl.productID;
		bos << pl.productPrice;

		bos.write((char*)pl.szProductName, sizeof(pl.szProductName));
		bos.write((char*)pl.szProductImage, sizeof(pl.szProductImage));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallProductResp& pl)
	{
		pl.reset();

		bis >> pl.productID;
		bis >> pl.productPrice;

		bis.read((char*)pl.szProductName, sizeof(pl.szProductName));
		bis.read((char*)pl.szProductImage, sizeof(pl.szProductImage));

		return bis;
	}


};


//�����̳���ƷV2
struct CMD_GP_UserMallProductReq_V2
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_PRODUCT_REQ_V2 };

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwVersion;		//�汾��Ϣ��1-android, 2-ios��������Ժ�Ҫ���°汾�أ�7�������һ��б�

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallProductReq_V2() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallProductReq_V2& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwVersion;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallProductReq_V2& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.dwVersion;

		return bis;
	}
};

//�̳���Ʒ�б�
struct CMD_GP_UserMallProductResp_V2
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_PRODUCT_RESP_V2 };

	unsigned int					dwVersion;		//�汾��Ϣ������Ժ�Ҫ���°汾��
	unsigned int					productID;			//��Ʒ ID
	unsigned int					productPrice;			//ԭ�۸�
	unsigned char					cbHotFlag;			//������ʶ��0~3
	char							szProductName[32];		//��Ʒ����
	char							szProductNameAdd[32];	//��������
	char							szProductImage[128];	//��ƷͼƬ
	char							szProductExt[64];		//Ԥ��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallProductResp_V2() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallProductResp_V2& pl)
	{
		bos << pl.dwVersion;
		bos << pl.productID;
		bos << pl.productPrice;
		bos << pl.cbHotFlag;

		bos.write((char*)pl.szProductName, sizeof(pl.szProductName));
		bos.write((char*)pl.szProductNameAdd, sizeof(pl.szProductNameAdd));
		bos.write((char*)pl.szProductImage, sizeof(pl.szProductImage));
		bos.write((char*)pl.szProductExt, sizeof(pl.szProductExt));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallProductResp_V2& pl)
	{
		pl.reset();

		bis >> pl.dwVersion;
		bis >> pl.productID;
		bis >> pl.productPrice;
		bis >> pl.cbHotFlag;

		bis.read((char*)pl.szProductName, sizeof(pl.szProductName));
		bis.read((char*)pl.szProductNameAdd, sizeof(pl.szProductNameAdd));
		bis.read((char*)pl.szProductImage, sizeof(pl.szProductImage));
		bis.read((char*)pl.szProductExt, sizeof(pl.szProductExt));

		return bis;
	}
};


//�̳���Ʒ�б�
struct CMD_GP_UserMallVipComBo
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_ComBo_RESP };

	unsigned int					dwVersion;		//�汾��Ϣ������Ժ�Ҫ���°汾��
	unsigned int					productID;			//��Ʒ ID
	unsigned int					productPrice;			//ԭ�۸�
	unsigned int					dwComBoId;
	unsigned char					cbHotFlag;			//������ʶ��0~3
	char							szProductName[32];		//��Ʒ����
	char							szProductNameAdd[32];	//��������
	char							szProductImage[128];	//��ƷͼƬ
	char							szProductExt[64];		//Ԥ��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallVipComBo() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallVipComBo& pl)
	{
		bos << pl.dwVersion;
		bos << pl.productID;
		bos << pl.productPrice;
		bos << pl.dwComBoId;
		bos << pl.cbHotFlag;

		bos.write((char*)pl.szProductName, sizeof(pl.szProductName));
		bos.write((char*)pl.szProductNameAdd, sizeof(pl.szProductNameAdd));
		bos.write((char*)pl.szProductImage, sizeof(pl.szProductImage));
		bos.write((char*)pl.szProductExt, sizeof(pl.szProductExt));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallVipComBo& pl)
	{
		pl.reset();

		bis >> pl.dwVersion;
		bis >> pl.productID;
		bis >> pl.productPrice;
		bis >> pl.dwComBoId;
		bis >> pl.cbHotFlag;

		bis.read((char*)pl.szProductName, sizeof(pl.szProductName));
		bis.read((char*)pl.szProductNameAdd, sizeof(pl.szProductNameAdd));
		bis.read((char*)pl.szProductImage, sizeof(pl.szProductImage));
		bis.read((char*)pl.szProductExt, sizeof(pl.szProductExt));

		return bis;
	}
};

//�̳���Ʒ�б����
struct CMD_GP_UserMallProductRespFinish
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_PRODUCT_RESP_FINISH };

	unsigned int					dwTotal;		//����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallProductRespFinish() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallProductRespFinish& pl)
	{
		bos << pl.dwTotal;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallProductRespFinish& pl)
	{
		pl.reset();

		bis >> pl.dwTotal;

		return bis;
	}

};

//�̳��ײ���Ʒ�б����
struct CMD_GP_UserMallComBotRespFinish
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_ComBo_FINISH };

	unsigned int					dwTotal;		//����
	unsigned int					dwProductId;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallComBotRespFinish() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallComBotRespFinish& pl)
	{
		bos << pl.dwTotal;
		bos << pl.dwProductId;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallComBotRespFinish& pl)
	{
		pl.reset();

		bis >> pl.dwTotal;
		bis >> pl.dwProductId;

		return bis;
	}

};
//�̳ǹ�����Ʒ�����¶���
struct CMD_GP_UserMallPlaceOrderReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_PLACE_ORDER_REQ };

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwProductID;	//��Ʒ ID
	char							szPayWay[10];	//����ʽ		

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallPlaceOrderReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallPlaceOrderReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwProductID;
		bos.write((char*)pl.szPayWay, sizeof(pl.szPayWay));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallPlaceOrderReq& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.dwProductID;
		bis.read((char*)pl.szPayWay, sizeof(pl.szPayWay));

		return bis;
	}
};

//���ض���
struct CMD_GP_UserMallPlaceOrderResp
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_PLACE_ORDER_RESP };

	short nResult;		//���				0:�ǲ� ��1���ɹ���2����������
	char dwOrderID[20];	//����ID
	char token[128];	//token��Ϣ
	char productName[32]; //��Ʒ����
	int productPrice; //��Ʒ�۸�
	char billingCode[20];	// ��Ʒ�Ʒ���

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallPlaceOrderResp() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallPlaceOrderResp& pl)
	{
		bos << pl.nResult;
		bos << pl.productPrice;

		bos.write((char*)pl.dwOrderID, sizeof(pl.dwOrderID));
		bos.write((char*)pl.token, sizeof(pl.token));
		bos.write((char*)pl.productName, sizeof(pl.productName));
		bos.write((char*)pl.billingCode, sizeof(pl.billingCode));
		
		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallPlaceOrderResp& pl)
	{
		pl.reset();

		bis >> pl.nResult;
		bis >> pl.productPrice;

		bis.read((char*)pl.dwOrderID, sizeof(pl.dwOrderID));
		bis.read((char*)pl.token, sizeof(pl.token));
		bis.read((char*)pl.productName, sizeof(pl.productName));
		bis.read((char*)pl.billingCode, sizeof(pl.billingCode));

		return bis;
	}

};

//�����һ����ض���
struct CMD_GP_UserMallFankaExchangeOrderResp
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_FANKA_ORDER_RESP };

	short nResult;		//��� 0��ʧ�ܣ�1���ɹ�
	int UserScore;		//��һ��ֶ�����
	int UserFangka;		//��������
	int productPrice; //��Ʒ�۸�


	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallFankaExchangeOrderResp() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallFankaExchangeOrderResp& pl)
	{
		bos << pl.nResult;
		bos << pl.UserScore;
		bos << pl.UserFangka;
		bos << pl.productPrice;


		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallFankaExchangeOrderResp& pl)
	{
		pl.reset();

		bis >> pl.nResult;
		bis >> pl.UserScore;
		bis >> pl.UserFangka;
		bis >> pl.productPrice;

		return bis;
	}

};

//����ȡ��������
struct CMD_GP_UserCancelOrderNumReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_CANCEL_ORDER_REQ };

	char dwOrderID[20];	//����ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserCancelOrderNumReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserCancelOrderNumReq& pl)
	{
		bos.write((char*)pl.dwOrderID, sizeof(pl.dwOrderID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserCancelOrderNumReq& pl)
	{
		bis.read((char*)pl.dwOrderID, sizeof(pl.dwOrderID));

		return bis;
	}
};

//����ȡ���������
struct CMD_GP_UserCancelOrderResp
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_CANCEL_ORDER_REP };

	short nResult;		//���		

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserCancelOrderResp() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserCancelOrderResp& pl)
	{
		bos << pl.nResult;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserCancelOrderResp& pl)
	{
		pl.reset();

		bis >> pl.nResult;

		return bis;
	}
};
//������Ʒ������
struct CMD_GP_UserMallBuyReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_BUY_REQ };

	//unsigned int userId;
	char dwOrderID[20];	//����ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallBuyReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallBuyReq& pl)
	{
		//bos << pl.userId;
		bos.write((char*)pl.dwOrderID, sizeof(pl.dwOrderID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallBuyReq& pl)
	{
		//bis >> pl.userId;
		bis.read((char*)pl.dwOrderID, sizeof(pl.dwOrderID));

		return bis;
	}
};
//������Ʒ������
struct CMD_GP_UserMallBuyResp
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_BUY_RESP };

	unsigned int productID;			//��Ʒ ID
	unsigned int nResult;	//������
	unsigned int dwGoldScore;	//�û��Ƹ�

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallBuyResp() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallBuyResp& pl)
	{
		bos << pl.nResult;
		bos << pl.productID;
		bos << pl.dwGoldScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallBuyResp& pl)
	{
		bis >> pl.nResult;
		bis >> pl.productID;
		bis >> pl.dwGoldScore;

		return bis;
	}
};
//���������Ʒ����״̬
struct CMD_GP_UserMallUpdateReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_UPDATE_REQ };

	//unsigned int userId;
	char dwOrderID[20];	//����ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallUpdateReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallUpdateReq& pl)
	{
		//bos << pl.userId;
		bos.write((char*)pl.dwOrderID, sizeof(pl.dwOrderID));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallUpdateReq& pl)
	{
		//bis >> pl.userId;
		bis.read((char*)pl.dwOrderID, sizeof(pl.dwOrderID));

		return bis;
	}
};
//���ظ�����Ʒ����״̬
struct CMD_GP_UserMallUpdateResp
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MALL_BUY_RESP };

	unsigned int productID;			//��Ʒ ID
	unsigned int nResult;	//������
	unsigned int dwGoldScore;	//�û��Ƹ�

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserMallUpdateResp() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserMallUpdateResp& pl)
	{
		bos << pl.nResult;
		bos << pl.productID;
		bos << pl.dwGoldScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserMallUpdateResp& pl)
	{
		bis >> pl.nResult;
		bis >> pl.productID;
		bis >> pl.dwGoldScore;

		return bis;
	}
};

//��ѯ�û���������Ϣ
struct CMD_GP_UserBankInfoReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_BANK_INFO_REQ };

	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBankInfoReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserBankInfoReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserBankInfoReq& pl)
	{
		bis >> pl.dwUserID;

		return bis;
	}
};

//��ѯ�û���������Ϣ�Ľ��
struct CMD_GP_UserBankInfoRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_BANK_INFO_REP };

	short							nCode;			//�����룺0Ϊ�ɹ�
	unsigned int					dwUserID;		//��� ID
	unsigned int					dwCurScore;		//��ǰ������Ϸ����
	unsigned int					dwBankScore;	//���з���

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBankInfoRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserBankInfoRep& pl)
	{
		bos << pl.nCode;
		bos << pl.dwUserID;
		bos << pl.dwCurScore;
		bos << pl.dwBankScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserBankInfoRep& pl)
	{
		bis >> pl.nCode;
		bis >> pl.dwUserID;
		bis >> pl.dwCurScore;
		bis >> pl.dwBankScore;

		return bis;
	}
};

//�û��������У�����˻�У�鼸������(�ܷ��Ƿ������ݿ�˱���һ�£����ʱ�Ƿ����з����������ݿ��з�����ȡ��ʱ�Ƿ��෴)
struct CMD_GP_UserBankChargeReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_BANK_CHARGE_REQ };

	short							nOpCode;		//�����룺1Ϊ�棬2Ϊȡ
	unsigned int					dwUserID;		//��� ID
	unsigned int					dwCurScore;		//������ϣ����������Ϸ����
	unsigned int					dwBankScore;	//������ϣ�������з���

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBankChargeReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserBankChargeReq& pl)
	{
		bos << pl.nOpCode;
		bos << pl.dwUserID;
		bos << pl.dwCurScore;
		bos << pl.dwBankScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserBankChargeReq& pl)
	{
		bis >> pl.nOpCode;
		bis >> pl.dwUserID;
		bis >> pl.dwCurScore;
		bis >> pl.dwBankScore;

		return bis;
	}
};

//�û��������еĽ��
struct CMD_GP_UserBankChargeRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_BANK_CHARGE_REP };

	short							nCode;			//�����룺0Ϊ�ɹ�
	unsigned int					dwUserID;		//��� ID
	unsigned int					dwCurScore;		//�ɹ���Ľ������ǰ������Ϸ����
	unsigned int					dwBankScore;	//�ɹ���Ľ�������з���

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserBankChargeRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserBankChargeRep& pl)
	{
		bos << pl.nCode;
		bos << pl.dwUserID;
		bos << pl.dwCurScore;
		bos << pl.dwBankScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserBankChargeRep& pl)
	{
		bis >> pl.nCode;
		bis >> pl.dwUserID;
		bis >> pl.dwCurScore;
		bis >> pl.dwBankScore;

		return bis;
	}
};

// ����У�鷢����������
struct CMD_GP_UserCheckLabaReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_CHECK_LABA_REQ };
	
	short			iLen;
	char			strLabaInfo[256];	// ��������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserCheckLabaReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserCheckLabaReq& pl)
	{
		bos << pl.iLen;
		bos.write((char*)pl.strLabaInfo, pl.iLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserCheckLabaReq& pl)
	{
		bis >> pl.iLen;
		bis.read((char*)pl.strLabaInfo, pl.iLen);

		return bis;
	}
};

//У�����Ƚ��
struct CMD_GP_UserCheckLabaRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_CHECK_LABA_REP };

	short			nCode;				// �����룺0Ϊ�ɹ�
	short			nLen;
	char			strLabaInfo[256];	// ��������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserCheckLabaRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserCheckLabaRep& pl)
	{
		bos << pl.nCode;
		bos << pl.nLen;
		bos.write((char*)pl.strLabaInfo, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserCheckLabaRep& pl)
	{
		bis >> pl.nCode;
		bis >> pl.nLen;
		bis.read((char*)pl.strLabaInfo, pl.nLen);

		return bis;
	}
};

// ����������
struct CMD_GP_UserSendLabaReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_SEND_LABA_REQ};

	unsigned int					dwUserID;		//��� ID
	short							nLen;
	char							strLabaInfo[256];	// ��������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserSendLabaReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserSendLabaReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.nLen;

		bos.write((char*)pl.strLabaInfo, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserSendLabaReq& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.nLen;

		bis.read((char*)pl.strLabaInfo, pl.nLen);
		return bis;
	}
};

// �������Ƚ��
struct CMD_GP_UserSendLabaRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_SEND_LABA_REP };

	short							nCode;			// �����룺0Ϊ�ɹ�
	unsigned int					dwUserID;		//��� ID
	unsigned int					dwCurScore;		//�ɹ���Ľ������ǰ������Ϸ����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserSendLabaRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserSendLabaRep& pl)
	{
		bos << pl.nCode;
		bos << pl.dwUserID;
		bos << pl.dwCurScore;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserSendLabaRep& pl)
	{
		bis >> pl.nCode;
		bis >> pl.dwUserID;
		bis >> pl.dwCurScore;

		return bis;
	}
};

//���յ�������Ϣ
struct CMD_GP_SpeakerMsgRep
{
	enum {M_ID = MDM_GP_USER};
	enum {S_ID = SUB_GP_USER_SPEAKER_MSG_REP};

	unsigned short						nType;					//��Ϣ����:1�û���Ϣ��2ϵͳ��Ϣ
	unsigned short						nLen;					//��Ϣ����
	char								szMsg[256];				//��Ϣ����

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_SpeakerMsgRep() { reset(); }
	friend bostream& operator<<(bostream& bos,const CMD_GP_SpeakerMsgRep& pl)
	{
		bos << pl.nType;
		bos << pl.nLen;

		bos.write((char*)pl.szMsg, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis,CMD_GP_SpeakerMsgRep& pl)
	{	
		pl.reset();
		bis >> pl.nType;
		bis >> pl.nLen;

		bis.read((char*)pl.szMsg, pl.nLen);

		return bis;
	}
};


// �û������ѯ���ò���
struct CMD_GP_UserQueryConfigReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_QUERY_CONFIG_REQ };

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwVersion;		//�汾��Ϣ:  major<<16 + minor
	unsigned int					dwConfigID;		//������ı��룺��λȡ��0��ʾ���û��˰汾������������
	char	szChannel[NAME_LEN];			//������

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserQueryConfigReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserQueryConfigReq& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwVersion;
		bos << pl.dwConfigID;
		
		bos.write((char*)pl.szChannel, sizeof(pl.szChannel));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserQueryConfigReq& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.dwVersion;
		bis >> pl.dwConfigID;

		bis.read((char*)pl.szChannel, sizeof(pl.szChannel));

		return bis;
	}
};

// ����ĳ������
struct CMD_GP_UserQueryConfigRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_QUERY_CONFIG_REP };

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwVersion;		//�汾��Ϣ
	unsigned short					nLen;			//��Ϣ���ȡ����Ϊ0��ʾ��������������ͽ���
	char							szConfig[256];		//��Ϣ����:key|value   ��1������ǰ��keyֵ�������ȫ���Ƕ�Ӧ��ֵ��Ҳ���������ߣ���ÿ����Ϣֻ����һ�顣

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GP_UserQueryConfigRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GP_UserQueryConfigRep& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwVersion;
		bos << pl.nLen;

		bos.write((char*)pl.szConfig, pl.nLen);

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GP_UserQueryConfigRep& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.dwVersion;
		bis >> pl.nLen;

		bis.read((char*)pl.szConfig, pl.nLen);

		return bis;
	}
};


// ����VIP
struct CMD_GR_UserVIPReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GR_USER_VIP_REQ };

	unsigned int					dwUserID;		//��� ID

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserVIPReq() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserVIPReq& pl)
	{
		bos << pl.dwUserID;

		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_UserVIPReq& pl)
	{
		bis >> pl.dwUserID;

		return bis;
	}
};

// �ظ�VIP
struct CMD_GR_UserVIPRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GR_USER_VIP_REP };

	unsigned int					dwVipLevel;		//VIP�ȼ�, 0-û��VIP, 1-��VIP, 2-��VIP
	char							szValidTime[32];	//����ʱ��

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserVIPRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserVIPRep& pl)
	{
		bos << pl.dwVipLevel;

		bos.write((char*)pl.szValidTime, sizeof(pl.szValidTime));

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserVIPRep& pl)
	{
		bis >> pl.dwVipLevel;

		bis.read((char*)pl.szValidTime, sizeof(pl.szValidTime));

		return bis;
	}
};

// ���㿨ʹ��
struct CMD_GR_UserRestFlee_REQ
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GR_USER_REST_FLEE_REQ };

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwKindId;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserRestFlee_REQ() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserRestFlee_REQ& pl)
	{
		bos << pl.dwUserID;
		bos << pl.dwKindId;

		return bos;
	}

	friend bistream& operator>>(bistream& bis, CMD_GR_UserRestFlee_REQ& pl)
	{
		bis >> pl.dwUserID;
		bis >> pl.dwKindId;

		return bis;
	}
};

// ��������
struct CMD_GR_UserRestFleeRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GR_USER_REST_FLEE_REP };

	short				nCode;// ������
	char				szDescribe[64];
	short				nRestCardNum;	// ���˿�����
	short				nKindId;

	void reset() { memset(this, 0, sizeof(*this)); }
	CMD_GR_UserRestFleeRep() { reset(); }
	friend bostream& operator<<(bostream& bos, const CMD_GR_UserRestFleeRep& pl)
	{
		bos << pl.nCode;
		bos.write((char*)pl.szDescribe, sizeof(pl.szDescribe));
		bos << pl.nRestCardNum;
		bos << pl.nKindId;

		return bos;
	}
	friend bistream& operator>>(bistream& bis, CMD_GR_UserRestFleeRep& pl)
	{
		bis >> pl.nCode;
		bis.read((char*)pl.szDescribe, sizeof(pl.szDescribe));
		bis >> pl.nRestCardNum;
		bis >> pl.nKindId;

		return bis;
	}
};
//////////////////////////////////////////////////////////////////////////

#endif
