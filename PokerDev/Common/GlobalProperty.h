#ifndef GLOBAL_PROPERTY_HEAD_FILE
#define GLOBAL_PROPERTY_HEAD_FILE

////////////////////////////////////////////////////////////////////////////////////////////////

//�ʻ�����
#define FLOWER_1					0
#define FLOWER_2					1
#define FLOWER_3					2
#define FLOWER_4					3
#define FLOWER_5					4
#define FLOWER_6					5
#define FLOWER_7					6
#define FLOWER_8					7
#define FLOWER_9					8
#define FLOWER_10					9
#define FLOWER_11					10

unsigned char const g_FlowerTypeList[]=
{
	FLOWER_1,
	FLOWER_2,
	FLOWER_3,
	FLOWER_4,
	FLOWER_5,
	FLOWER_6,
	FLOWER_7,
	FLOWER_8,
	FLOWER_9,
	FLOWER_10,
	FLOWER_11,
};

//�ʻ���Ŀ
#define FLOWER_COUNT		(sizeof(g_FlowerTypeList)/sizeof(g_FlowerTypeList[0]))//������Ŀ

//////////////////////////////////////////////////////////////////////////
//�궨��
#define CHARM_EXCHANGE_RATE			50									//�һ�����
#define MAX_FLOWER_COUNT			100									//�����Ŀ

//�ʻ��ṹ
struct tagGiftInfo
{
	char							szName[64];							//�ʻ�����
	char							szAction[128];						//��������
	char							szQuantifier1[20];					//������
	char							szResult[128];						//�������
	char							szQuantifier2[6];					//������
	char							szCharmResult[128];					//�������
};

//�ʻ�����
tagGiftInfo const g_FlowerDescribe[FLOWER_COUNT]=
{
	{("����"),(" ��������� "),(" ����1��"),("����ϲ "),("�� "),(" ����ֵ���� %ld �㣡")},
	{("����"),(" ��������� "),(" ����1��"),("����ϲ "),("�� "),(" ����ֵ���� %ld �㣡")},
	{("�ʻ�"),(" ��������� "),(" �ʻ�1��"),("����ϲ "),("�� "),(" ����ֵ���� %ld �㣡")},
	{("ơ��"),(" ��������� "),(" ơ��1��"),("����ϲ "),("�� "),(" ����ֵ���� %ld �㣡")},
	{("����"),(" ��������� "),(" ����1��"),("����ϲ "),("�� "),(" ����ֵ���� %ld �㣡")},
	{("���"),(" ��������� "),(" ���1ö"),("����ϲ "),("ö "),(" ����ֵ���� %ld �㣡")},
	{("�γ�"),(" ��������� "),(" �γ�1��"),("����ϲ "),("�� "),(" ����ֵ���� %ld �㣡")},
	{("����"),(" ��������� "),(" ����1��"),("����ϲ "),("�� "),(" ����ֵ���� %ld �㣡")},
	{("����"),(" �ݺݵ����� "),(" ����1��"),("����Ǹ "),("�� "),(" ����ֵ���� %ld �㣡")},
	{("שͷ"),(" �ݺݵ����� "),(" שͷ1��"),("����Ǹ "),("�� "),(" ����ֵ���� %ld �㣡")},
	{("ը��"),(" �ݺݵ����� "),(" ը��1ö"),("����Ǹ "),("ö "),(" ����ֵ���� %ld �㣡")}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//��������
#define PROP_DOUBLE						0									//˫�����ֿ�
#define PROP_FOURDOLD					1									//�ı����ֿ�
#define PROP_NEGAGIVE					2									//��������
#define PROP_FLEE						3									//��������
#define PROP_BUGLE						4									//С����
#define PROP_KICK						5									//���߿�
#define PROP_SHIELD						6									//�����
#define PROP_MEMBER_1					7									//��Ա����
#define PROP_MEMBER_2					8									//��Ա����
#define PROP_MEMBER_3					9									//��Ա����
#define PROP_MEMBER_4					10									//��Ա����
#define PROP_MEMBER_5					11									//��Ա����
#define PROP_MEMBER_6					12									//��Ա����
#define PROP_MEMBER_7					13									//��Ա����
#define PROP_MEMBER_8					14									//��Ա����
unsigned char const g_PropTypeList[]=
{
	PROP_DOUBLE	,
	PROP_FOURDOLD,
	PROP_NEGAGIVE,
	PROP_FLEE	,
	PROP_BUGLE	,
	PROP_KICK	,
	PROP_SHIELD	,
	PROP_MEMBER_1,
	PROP_MEMBER_2,
	PROP_MEMBER_3,
	PROP_MEMBER_4,
	PROP_MEMBER_5,
	PROP_MEMBER_6,
	PROP_MEMBER_7,
	PROP_MEMBER_8,
};
#define PROPERTY_COUNT			(sizeof(g_PropTypeList)/sizeof(g_PropTypeList[0]))//������Ŀ

//���߶���
#define MAX_PROPERTY_COUNT				100									//�����Ŀ
#define BUGLE_MAX_CHAR					120									//���ȸ���
#define BULESSING_MAX_CHAR				100									//ף������

//��������
struct tagPropertyDescribe
{
	char							szName[32];							//��������
	char							szDescribe[255];					//���߼�ֵ
};

tagPropertyDescribe const g_PropertyDescribe[PROPERTY_COUNT] =
{
	{("˫�����ֿ�"),("ӵ����˫�����ֿ�������ϷӮ�ַ��������˲���ۣ�������Ч����ι���ʱ���ۼӡ���ע��ֻ���ڹ������Ϸ����ʹ�á���")},
	{("�ı����ֿ�"),("ӵ�����ı����ֿ�������ϷӮ�ַ��ı������˲���ۣ�������Ч����ι���ʱ���ۼӡ���ע��ֻ���ڹ������Ϸ����ʹ�á���")},
	{("��������"),("ʹ�øõ��ߺ�������Ϸ���ֽ��ָ���ʼ״̬������Ϊ���ֶ����գ�")},
	{("��������"),("ʹ�øõ��ߺ����������ʽ��ָ���ʼ״̬������Ϊ���ܶ����գ�")},
	{("С����"),("�����͵���Ϣ���ڷ��估�����ڵ�������Ϸ����������Ŀ�ķ�ʽ��ʾ��")},	
	{("���߿�"),("����õ��ߺ������ٵ��ı���Ա�߳���Ϸ����")},
	{("�����"),("����õ��ߺ�����ֲ��۷֣�����Ϊ���ֶ����գ���ע��ֻ���ڹ������Ϸ����ʹ�á���")},
	{("�����Ա��"),("��������/����ʱ������9���Żݣ�������ͨ��ң��к����Ա�����ǣ���Ա�ڼ䣬����ID�ڴ����������к�ɫ������ʾ,���Ƚ����������䣡")},
	{("�����Ա��"),("��������/����ʱ������9���Żݣ�������ͨ�������Ա���������Ա�����ǣ���Ա�ڼ䣬����ID�ڴ����������к�ɫ������ʾ�����Ƚ����������䣡")},
	{("�����Ա��"),("��������/����ʱ������9���Żݣ�������ͨ�����ꡢ������ң��л�Ա�����ǣ���Ա�ڼ䣬����ID�ڴ����������к�ɫ������ʾ�����Ƚ����������䣡")},
	{("�����Ա��"),("��������/����ʱ������9���Żݣ�������ͨ�����ꡢ���ꡢ������ң��л�Ա�����ǣ���Ա�ڼ䣬����ID�ڴ����������к�ɫ������ʾ�����Ƚ����������䣡")},

	{("�����Ա��"),("��Ա���д����ʺź�ɫ��ʾ������ͷ�����˹��ܣ����߹�����ۣ����Ƚ����������䣡")},
	{("�����Ա��"),("��Ա���д����ʺź�ɫ��ʾ������ͷ�����˹��ܣ����߹�����ۣ����Ƚ����������䣡")},
	{("7�����Ա��"),("��Ա���д����ʺź�ɫ��ʾ������ͷ�����˹��ܣ����߹�����ۣ����Ƚ����������䣡")},
	{("������Ա��"),("��Ա���д����ʺź�ɫ��ʾ������ͷ�����˹��ܣ����߹�����ۣ����Ƚ����������䣡")}
};

//������Ϣ�ṹ
struct tagPropertyInfo
{
	int							nPropertyID;						//����ID
	unsigned int						dwPropCount1;						//������Ŀ
	unsigned int						dwPropCount2;						//������Ŀ
	unsigned int						dwPropCount3;						//������Ŀ
	unsigned int						dwPropCount4;						//������Ŀ
	unsigned int						dwPropCount5;						//������Ŀ
	unsigned int						dwPropCount6;						//������Ŀ
	unsigned int						dwPropCount7;						//������Ŀ
	unsigned int						dwPropCount8;						//������Ŀ
	unsigned int						dwPropCount9;						//������Ŀ
	unsigned int						dwPropCount10;						//������Ŀ
	int						lPrice1;							//���߼۸�
	int						lPrice2;							//���߼۸�
	int						lPrice3;							//���߼۸�
	int						lPrice4;							//���߼۸�
	int						lPrice5;							//���߼۸�
	int						lPrice6;							//���߼۸�
	int						lPrice7;							//���߼۸�
	int						lPrice8;							//���߼۸�
	int						lPrice9;							//���߼۸�
	int						lPrice10;							//���߼۸�
	unsigned char				cbDiscount;							//��Ա�ۿ�
	bool						bNullity;							//��ֹ��ʶ
};

//�ʻ���Ϣ�ṹ
struct tagFlowerInfo
{
	int							nFlowerID;							//�ʻ�ID
	long						lPrice;								//�ʻ��۸�
	long						lSendUserCharm;						//��������
	long						lRcvUserCharm;						//��������
	unsigned char				cbDiscount;							//��Ա�ۿ�
	bool						bNullity;							//��ֹ��ʶ
};

//////////////////////////////////////////////////////////////////////////////

#endif