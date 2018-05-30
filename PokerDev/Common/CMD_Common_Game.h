#ifndef CMD_COMMON_GAME_H
#define CMD_COMMON_GAME_H

#include "CMD_Plaza.h"
#include "CMD_Game.h"
#include "biostream.h"

//////////////////////////////////////////////// GameService ////////////////////////////////////////////////
#define SUB_GR_USER_EXPRESSION_PROP_REQ				308							//��������б�
#define SUB_GR_USER_EXPRESSION_PROP_REP				309							//�����б���
#define SUB_GR_USER_USE_EXPRESSION_PROP_REQ			310							//����ʹ�õ���
#define SUB_GR_USER_USE_EXPRESSION_PROP_REP			311							//ʹ�õ��߽��
#define SUB_GR_USER_EXPRESSION_PROP_EFFECT_REP		312							//�㲥ʹ�õ���Ч��

#define SUB_GR_USER_KICKOUT_REQ					313							//�������˿�
#define SUB_GR_USER_KICKOUT_REP					314							//���˿����
#define SUB_GR_USER_USE_KICKOUT_REQ				315							//����ʹ�����˿�
#define SUB_GR_USER_USE_KICKOUT_REP				316							//ʹ�����˿����
#define SUB_GR_USER_KICKOUT_EFFECT_REP			317							//�㲥���˿�Ч��

#define SUB_GR_USER_TIPOFF_REQ				320							//����ٱ�
#define SUB_GR_USER_TIPOFF_REP				321							//�ٱ����

//////////////////////////////////////////////// LogonService ////////////////////////////////////////////////
#define SUB_GP_USER_COIN_COUNT_REQ				372  // ���������
#define SUB_GP_USER_COIN_COUNT_REP				373

#define SUB_GP_USER_PROP_REQ					377  // ���󱳰�����
#define SUB_GP_USER_PROP_REP					378

#define SUB_GP_USER_MATCH_INFO_REQ					379  // �����������
#define SUB_GP_USER_MATCH_INFO_REP					380
#define SUB_GP_USER_PROP_FINISH_REP					381
// ��������б�
struct CMD_GR_UserExpressionPropReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_EXPRESSION_PROP_REQ };

	unsigned int					dwUserID;		//��� ID

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
	unsigned int					dwPropID;		//���� ID
	unsigned int					dwPropPrice;	//���߼۸�
	char							szName[32];		//��������

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
// �ظ������б�
struct CMD_GR_UserExpressionPropRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_EXPRESSION_PROP_REP };

	short							nCode;		// ������ 0 ��ʾ�ɹ�
	unsigned int					totalCount;	// ������
	UserExpProp						Product[10];  // ������

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

// ����ʹ�õ���
struct CMD_GR_UserUseExpressionPropReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_USE_EXPRESSION_PROP_REQ };

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwToUserID;		//��ʹ����� ID
	unsigned int					dwPropID;		//���� ID
	unsigned int					dwPropCount;	//ʹ�õĵ������� ID

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

// �ظ�ʹ�õ���
struct CMD_GR_UserUseExpressionPropRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_USE_EXPRESSION_PROP_REP };

	short							dwSuccess;		//�Ƿ�ʹ�óɹ�,0 ��ʾ�ɹ�
	unsigned int					dwRemainCoin;	//��ǰʣ�໶�ֶ�

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

// �㲥ʹ�õ���Ч��
struct CMD_GR_UserUseExpressionPropEffectRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_EXPRESSION_PROP_EFFECT_REP };

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwToUserID;		//��ʹ����� ID
	unsigned int					dwPropID;		//���� ID
	unsigned int					dwCount;		//���ʹ���

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

// �������˿�
struct CMD_GR_UserKickOutReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_KICKOUT_REQ };

	unsigned int					dwUserID;		//��� ID

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

// �ظ����˿�
struct CMD_GR_UserKickOutRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_KICKOUT_REP };

	unsigned char					dwKickOutAuth;	//Ȩ��  0-û�У� 1-��
	unsigned int					dwCount;		//���˿�����
	short							dwMenberOrder;	// vip �ȼ�

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

// ʹ�����˿�
struct CMD_GR_UserUseKickOutReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_USE_KICKOUT_REQ };

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwToUserID;		//��ʹ����� ID

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

// �ظ�ʹ�����˿�
struct CMD_GR_UserUseKickOutRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_USE_KICKOUT_REP };

	unsigned char					dwSuccess;	//�ɹ�  0-�ɹ�
	unsigned int					dwCount; // ���˿�ʣ������

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

// ���˹㲥
struct CMD_GR_UserUseKickOutEffectRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_KICKOUT_EFFECT_REP };

	unsigned int					dwUserID;		//��� ID
	unsigned int					dwToUserID;		//��ʹ����� ID

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
// ����ٱ�
struct CMD_GR_UserTipOffReq
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_TIPOFF_REQ };

	unsigned int					dwUserID;		//�ٱ���� ID
	unsigned int					dwToUserID;		//���ٱ���� ID
	unsigned int 					dwKindID;
	unsigned char					dwTipOffType;	//�ٱ�����


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

// �ظ��ٱ�
struct CMD_GR_UserTipOffRep
{
	enum { M_ID = MDM_GR_USER };
	enum { S_ID = SUB_GR_USER_TIPOFF_REP };

	unsigned char					dwSuccess;		//VIP�ȼ�, 0-�ɹ�, 1-ʧ��
	unsigned int					dwUserID;		//�ٱ���ID

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

// �����
struct CMD_GP_UserCoinCountReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_COIN_COUNT_REQ };

	unsigned int					dwUserID;		//��� ID

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

// �ظ���
struct CMD_GP_UserCoinCountRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_COIN_COUNT_REP };

	unsigned int					dwCount;		//����

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

// ���󱳰�
struct CMD_GP_UserPropReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PROP_REQ };

	unsigned int					dwUserID;		//��� ID

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

// �ظ�����
struct CMD_GP_UserPropRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_PROP_REP };

	unsigned int					dwPropID;		//ID
	unsigned int					dwCount;		//����
	char							szPropName[64];	// ��������
	char							szPropUrl[64];	// ��������
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

// �ظ�����
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

// ���������Ϣ
struct CMD_GP_UserMatchInfoReq
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MATCH_INFO_REQ };

	unsigned int					dwUserID;		//��� ID

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

// �ظ�������Ϣ
struct CMD_GP_UserMatchInfoRep
{
	enum { M_ID = MDM_GP_USER };
	enum { S_ID = SUB_GP_USER_MATCH_INFO_REP };

	unsigned int					dwWinTimes;			//ʤ������
	unsigned int					dwLoseTimes;		//ʧ������
	unsigned int					dwTotalTimes;		//������

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