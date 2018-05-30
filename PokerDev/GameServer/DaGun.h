#ifndef _DAGUN_H
#define _DAGUN_H
#pragma once
#include <vector>
using namespace std;
#include "PokerDefine.h"

typedef BYTE TCARD;
typedef vector<TCARD> TCARDS;

#define	MAXPAI					27		//每个人最多27张
#define TYPE_ERROR				-1
#define	TYPE_NULL				0
#define TYPE_ONE				1		//单张
#define TYPE_TWO				2		//对子
#define TYPE_THREE				3       //三只
#define TYPE_ONESTR				4		//顺子，比如456
#define TYPE_TWOSTR				5		//连对，比如3344,445566... 2除外
#define TYPE_THREESTR			6       //三连对，比如333444,333444555... 2除外
#define TYPE_BOMB_510K			7		//510k炸弹
#define TYPE_BOMB_NOMORL		8		//普通炸弹,发给客户端时表示软炸
#define TYPE_BOMB_STR			9		//连炸，摇摆
#define TYPE_BOMB_7XI			10		//7喜炸弹，7张相同的牌，不带大小王
#define TYPE_BOMB_8XI			11		//8喜炸弹，8张相同的牌，不带大小王
#define TYPE_BOMB_FOUR_KING		12      //四张大小王
#define TYPE_KING               13      //王
#define TYPE_BOMB_GONGLONG		14		// 拱拢类型
#define TYPE_BOMB_HARD          15      //硬炸
#define TYPE_BOMB_MAGIC         16      //硬炸

#define SMA_KING				53		//小王
#define BIG_KING				54		//大王

#define MIN_ONESTR_NUM         3       // 最少3单连,干瞪眼单连最少3张，比如456

#define IS_GANDENGYANG         1       // 是干瞪眼

	//一张牌
	typedef struct tagPOKER
	{
		BYTE		point;	// 1-15;
		BYTE		index;	// 1-54
		BYTE		color;  // 0-4
		void		Set(int n)
		{
			if (n > 0 && n < 55)
				index = n;
			if (n <= 0) { point = 0; color = 0; return; }
			if (n <= 13){ point = n; color = 1; return; }
			if (n <= 26){ point = n - 13; color = 2; return; }
			if (n <= 39){ point = n - 26; color = 3; return; }
			if (n <= 52){ point = n - 39; color = 4; return; }
			if (n == 53){ point = 14; color = 0; return; }
			if (n == 54){ point = 15; color = 0; return; }
			if (n > 54) { point = 0; color = 0; return; }
		}
	}TPoker;
	typedef struct tagCARDTYPE
	{
		int		type;		//牌类型
		int     len;		//牌长度
		BYTE	card;
		BYTE	color;		//花色，这个只针对510k炸弹	0表示杂 4 表示黑桃 5表示大小王组成的对王 6 表示对小王 7 对大王
		int    count;		//这个只针对连炸中，最大炸弹的张数
		void reset() { memset(this, 0, sizeof(*this)); }
		tagCARDTYPE() { reset(); }
	}TCardType;

//一幅牌型
typedef struct tagPOKERGROUP
{
	BYTE			point;		//牌型值1-54
	BYTE            count;
	vector<BYTE>	index;		//1-54
}TPokerGroup;
//用来替换王的
typedef struct tagFakePoker
{
	BYTE        index;		//原来的值
	BYTE		fakeindex;	//替代值	
	void reset() { memset(this, 0, sizeof(*this)); }
	tagFakePoker() { reset(); }
}TFakePoker;
typedef struct tagFakeType
{
	TFakePoker   fakeking[8];
	TCardType	 cardtype;
}FakeType;

////做提示用
//typedef struct tagPOKERGROUP2
//{
//	BYTE			point;		//牌型值1-15,k105无效
//	BYTE            color;      //花色，这个只针对k105、对王
//	BYTE            count;		//张数
//	vector<BYTE>	index;		//牌列表
//}TPokerGroup2;

//在里面有赖子替换值信息
typedef struct tagPOKERGROUP2
{
	BYTE			point;		//牌型值1-15,k105无效
	BYTE            color;      //花色，这个只针对k105、对王
	int				type;		//牌类型
	BYTE            count;		//张数
	vector<BYTE>	index;		//牌列表
	TFakePoker		fakeking[MAXPAI];

	void reset() { memset(this, 0, sizeof(*this)); }
	tagPOKERGROUP2() { reset(); }
}TPokerGroup2;

typedef struct tagBOMBSTR
{//连炸结构(拱拢结构)
	int nBombCount;//炸弹数（拱拢为拢数）
	BYTE nMaxCount; //最大炸弹的张数
	BYTE nCount;	//所有的张数
	BYTE nPoint;	//最大炸弹的值
	vector<BYTE> index;//牌列表
	TFakePoker		fakeking[MAXPAI];
	void reset() { memset(this, 0, sizeof(*this)); }
	tagBOMBSTR() { reset(); }
}TBombStr;

	enum tagPATCOUNID
	{
		pai_null = 0,
		pai_1,
		pai_2,
		pai_3,
		pai_4,
		pai_5,
		pai_6,
		pai_7,
		pai_8,
		pai_king,
		pai_max
	};
typedef struct tagThree
{
	BYTE kingcount;		//这个用来代表index里面，有几个王
	BYTE point;			//点数
	BYTE index1;
	BYTE index2;
	BYTE index3;
}TThree;
typedef struct tagTwo
{
	BYTE kingcount;		//这个用来代表index里面，有几个王
	BYTE point;			//点数
	BYTE index1;
	BYTE index2;
}TTwo;
	//算法类
	class CDaGun
	{
	public:
		CDaGun(void);
		~CDaGun(void);
	public:
		vector<TPokerGroup2>	m_vOne;
		vector<TPokerGroup2>	m_vTwo;
		vector<TPokerGroup2>	m_vThree;
		vector<TPokerGroup2>	m_vFour;
		vector<TPokerGroup2>	m_vFive;
		vector<TPokerGroup2>	m_vSix;
		vector<TPokerGroup2>	m_vSeven;
		vector<TPokerGroup2>	m_vEight;
		vector<TPokerGroup2>	m_vK105;//k105,比较特殊，
		vector<TPokerGroup2>	m_vKing;//一般是打出牌中的所有王
		vector<TPokerGroup2>	m_vAllHandKing;//手牌中的所有王
		vector<TPokerGroup2>	m_vMagic;//一般是打出牌中的所有赖子
		vector<TPokerGroup2>	m_vAllHandMagic;//手牌中的所有赖子
		vector<TPokerGroup2>	m_allCard;	//所有的3，所有的4...依次入队列3<4<...<2<王
		vector<TPokerGroup2>	m_allHandCards;	//所有的3，所有的4...依次入队列3<4<...<2<王
		vector<BYTE>			m_allMagicPoint;	//所有的赖子，初始化时需要设置好
		BYTE		m_byFakeKingValue;// 王单出算几，2或3
		BYTE		m_byIsHasHardBomb;// 是否有软硬炸弹之分
		BYTE		m_byHandCardsNum;// 手牌数目
	public:
		//一张牌大小card_id = 1-54
		int			GetCardLevel(BYTE card_id);	
		//得到这组牌的类型,card_list不能有赖子了，需要新的参数传入上一次出牌的赖子数outMagicNum,byType为0表示有赖子模式
		TCardType	GetType(BYTE card_list[MAXPAI], int cardlen = MAXPAI, BYTE outMagicNum = 0, BYTE byType = 0, int outtype = TYPE_NULL, TFakePoker* refakepoker = NULL);		//得到这组牌的类型
		//有赖子的情况下，得出他的牌型，这个只针对三连对或者2连对
		FakeType	IsStrByMagic(int cardlen,int iMagicNum,int iZhaNum,TFakePoker fakepoker[8]);
		//fakepoker里面是这个赖子的替代值
		FakeType    GetTypeByMagic(BYTE card_list[MAXPAI],int cardlen,int iMagicNum,TFakePoker fakepoker[8],int outtype=TYPE_NULL);
		//牌数量
		BYTE		GetCardNum(BYTE card_list[MAXPAI], int cardlen = MAXPAI);
		//按大小排列,smalltobig=ture,从小到大
		void		SortByIndex(BYTE card_list[MAXPAI], int cardlen = MAXPAI, bool smalltobig = true);
		//按照牌的多少来排
		void		SortByCount(BYTE card_list[MAXPAI], int cardlen = MAXPAI);
		//初始化赖子列表
		void		InitMagicPoint(BYTE byMagicPoint);
		//设置赖子列表,从小到大给赖子赋值保证小赖子先使用
		void		AddMagicPoint(BYTE byMagicPoint);
		//设置是否有软硬炸弹之分
		void		SetHardBomb(BYTE byIsHard);
		//是否有软硬炸弹之分
		bool		IsHasHardBomb();
		//设置王单出算几
		void		SetFakeKingValue(BYTE byFakeKingValue);
		//获取王单出算几
		BYTE		GetFakeKingValue();
		//设置手牌数目
		void		SetHandCardsNum(BYTE byHandCardsNum);
		//获取手牌数目
		int			GetHandCardsNum();
		//是否是王
		bool		IsKing(BYTE card_id);
		//是否全部是王
		bool		IsAllKing(BYTE card_list[MAXPAI], int cardlen = MAXPAI);
		//得到王的个数
		int			GetKingNum(BYTE card_list[MAXPAI],int cardlen = MAXPAI,TFakePoker* fakepoker=NULL);
		//是否是赖子
		bool		IsMagic(BYTE card_id);
		//是否全部是赖子
		bool		IsAllMagic(BYTE card_list[MAXPAI], int cardlen = MAXPAI);
		//得到赖子的个数
		int			GetMagicNum(BYTE card_list[MAXPAI],int cardlen = MAXPAI,TFakePoker* fakepoker=NULL);
		//非赖子的情况下，其他牌是不是都相等？如果相等，返回最大序列值和数
		bool		IsAllEqualExceptMagic(BYTE& card,/*int& num,*/BYTE card_list[MAXPAI], int cardlen = MAXPAI);
		//判断是不是普通炸弹，如果是，返回值
		bool		IsNormalBomb(BYTE& card,/*int& num,*/BYTE card_list[MAXPAI], int cardlen = MAXPAI);
		//判断是不是四个王
		bool		IsKingBomb(BYTE card_list[MAXPAI], int cardlen = MAXPAI);
		//判断是否能出牌
		bool        CanOut(BYTE outCard[MAXPAI],BYTE followCard[MAXPAI],int outtype,int& followtype,bool isfirst = false,TFakePoker* fakepoker = NULL);
		//比较大小， typeFollow > typeFirst 返回真
		bool		Compare(TCardType typeFirst, TCardType typeFollow);
		//得到牌里的分数
		int         GetScore(BYTE card_list[MAXPAI], int cardlen = MAXPAI);
		//是否得到了4王
		int			HasKingBomb(BYTE card_list[MAXPAI]);
		//检查出的牌里面，是否是拆开天炸来出的
		int         CheckBeep(BYTE card_list[MAXPAI], BYTE outCard[MAXPAI], int outlen = MAXPAI);
		// 提示顺序
		void        SortBeepCardList(vector<TPokerGroup2>& combinelist);
		//分类成基本的牌形
		void		GetGroupType(TCARDS mycard,bool bCanOut = false);
		//将牌按照点数分类//此函数可以用于m_allHandCards和m_allCard
		void		GetGroupTypeByPoint(TCARDS mycard,vector<TPokerGroup2> & allCard,vector<TPokerGroup2>&	vMagic,vector<TPokerGroup2>& vKing);
		//此函数可以用于m_allHandCards和m_allCard
		void		GetGroupTypeByPointNoMagic(TCARDS mycard,vector<TPokerGroup2> & allCard,vector<TPokerGroup2>&	vKing);
		//提示出牌
		bool        BeepCardOut(BYTE otherout[MAXPAI], int outtype, vector<TPokerGroup2>& mybeepout, BYTE otherOutMagicNum = 0);//提示出牌,otherOutMagicNum为上家出的赖子数
		//首出牌提示
		bool		BeepFirstCardOut(vector<TPokerGroup2>& mybeepout);
		//选择出牌
		bool        SelectCardOut(BYTE otherout[MAXPAI], int outtype, BYTE byCardlist[MAXPAI], BYTE byCardLen, vector<TPokerGroup2>& CanOutList, BYTE otherOutMagicNum = 0);//选择出牌,otherOutMagicNum为上家出的赖子数
		//最后一手牌，全是赖子且含王
		bool		AllLastMagicOutWithKing(BYTE byCardLen);

	private:
		//获取所有同张的拱笼，比如软8个3 ，或4个王
		void		GetAllXiGL(vector<TBombStr>& mybombstr);
		//求m的n次幂
		int			GetPower(int m,int n);
		//计算2连对和3连对的函数。使用StrTool请确保GetGroupType函数被调用过，这样才能保证m_allHandCards 是最新的。
		bool		StrTool(const BYTE outpoint,const int iLianNum, const int iZhaNum,vector<TPokerGroup2>& combinelist );
		//干瞪眼游戏使用的。计算2连对和3连对的函数。使用StrTool请确保GetGroupType函数被调用过，这样才能保证m_allHandCards 是最新的。
		bool		StrTool_GDY(const BYTE outpoint,const int iLianNum, const int iZhaNum,vector<TPokerGroup2>& combinelist );
		//获取包含2的两只或3只，比如：22或222、22赖。
		bool		Get2Str_GDY(const BYTE outpoint,const int iLianNum, const int iZhaNum,vector<TPokerGroup2>& combinelist );
		//得到所有和出牌长度一样的三连对，包括用王组合的,outpoint 为1-54
		void        GetCombineThreeStr(BYTE outpoint,int outlen,vector<TPokerGroup2>& combinelist,BYTE byIsGanDengYang = 1);
		//得到所有和出牌长度一样的两连对，包括用王组合的，outpoint为1-54
		void        GetCombineTwoStr(BYTE outpoint, int outlen, vector<TPokerGroup2>& combinelist,BYTE byIsGanDengYang = 1);
		//得到所有和出牌长度一样的顺子，包括用王组合的，outpoint为1-54
		void		GetCombineOneStr( BYTE outpoint,int outlen,vector<TPokerGroup2>& combinelist ,BYTE byIsGanDengYang = 1);
		//得到所有的三对，包括用王组合的
		void        GetCombineThree(BYTE outpoint,vector<TPokerGroup2>& combinelist,BYTE byIsGanDengYang = 1);
		//得到所有的对子
		void        GetCombineTwo(BYTE outpoint, vector<TPokerGroup2>& combinelist,BYTE byIsGanDengYang = 1);
		//得到所有大过outpoint的单牌
		void        GetAllOne(BYTE outpoint, vector<TPokerGroup2>& combinelist, BYTE byIsGanDengYang = 1);
};
#endif
