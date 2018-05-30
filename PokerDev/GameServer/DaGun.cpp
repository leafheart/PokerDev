#include "DaGun.h"
#include <string>
using namespace PokerDef;

CDaGun::CDaGun(void)
{
	m_byIsHasHardBomb = 1;//默认有软硬炸弹之分
	m_byFakeKingValue = 3;//赖子单出算3
	m_allMagicPoint.clear();
	InitMagicPoint(CP_3_S);//3是赖子 ，从小到大给赖子赋值保证小赖子先使用
	AddMagicPoint(CARDINDEX_SMALL);//小王是赖子//王必须用牌数值
	AddMagicPoint(CARDINDEX_BIG);//大王是赖子
}

CDaGun::~CDaGun(void)
{
	m_allMagicPoint.clear();
}
//初始化赖子列表
void CDaGun::InitMagicPoint(BYTE byMagicPoint)
{
	m_allMagicPoint.clear();
	if (byMagicPoint >= 1 && byMagicPoint <= CARDINDEX_BIG)
	{
		m_allMagicPoint.push_back(byMagicPoint);
	}
}
//设置赖子列表,从小到大给赖子赋值保证小赖子先使用
void CDaGun::AddMagicPoint(BYTE byMagicPoint)
{
	if (byMagicPoint >= 1 && byMagicPoint <= CARDINDEX_BIG)
	{
		m_allMagicPoint.push_back(byMagicPoint);
	}
}
//设置王单出算几
void CDaGun::SetFakeKingValue(BYTE byFakeKingValue)
{
	if(byFakeKingValue != 2 && byFakeKingValue != 3)
		return ;
	m_byFakeKingValue = byFakeKingValue;
}
//获取王单出算几
BYTE CDaGun::GetFakeKingValue()
{
	return m_byFakeKingValue;
}
//设置是否有软硬炸弹之分
void CDaGun::SetHardBomb(BYTE byIsHard)
{
	m_byIsHasHardBomb = byIsHard;
}
//是否有软硬炸弹之分
bool CDaGun::IsHasHardBomb()
{
	return m_byIsHasHardBomb;
}
//设置手牌数目
void CDaGun::SetHandCardsNum(BYTE byHandCardsNum)
{
	m_byHandCardsNum = byHandCardsNum;
}
//获取手牌数目
int CDaGun::GetHandCardsNum()
{
	return m_byHandCardsNum;
}
bool CDaGun::IsKing(BYTE card_id)
{
	if(card_id == BIG_KING || card_id == SMA_KING)
		return true;
	else
		return false;
}
bool CDaGun::IsAllKing(BYTE card_list[MAXPAI],int cardlen /* = MAXPAI */)
{
	for(int i = 0; i < cardlen; i ++)
	{
		if(!IsKing(card_list[i]))
			return false;
	}
	return true;
}
int CDaGun::GetKingNum(BYTE card_list[MAXPAI],int cardlen /* = MAXPAI */,TFakePoker* fakepoker/*= NULL*/)
{
	int num =0;
	for(int i = 0; i < cardlen; i++)
	{
		if(IsKing(card_list[i]))
		{
			if(fakepoker != NULL)
				fakepoker[num].index = card_list[i];
			num++;
		}
		if(num >= 8)
			break;
	}
	return num;
}
bool CDaGun::IsMagic(BYTE card_id)
{
	for (vector<BYTE>::iterator i_result = m_allMagicPoint.begin();i_result != m_allMagicPoint.end();i_result++)
	{
		if (GetCardPoint(card_id) == GetCardPoint(*i_result))
		{
			return true;
		}
	}
	return false;
}
bool CDaGun::IsAllMagic(BYTE card_list[MAXPAI],int cardlen /* = MAXPAI */)
{
	for(int i = 0; i < cardlen; i ++)
	{
		if(card_list[i] > 0 && !IsMagic(card_list[i]))
			return false;
	}
	return true;
}
int CDaGun::GetMagicNum(BYTE card_list[MAXPAI],int cardlen /* = MAXPAI */,TFakePoker* fakepoker/*= NULL*/)
{
	int num =0;
	for(int i = 0; i < cardlen; i++)
	{
		if(IsMagic(card_list[i]))
		{
			if(fakepoker != NULL)
				fakepoker[num].index = card_list[i];
			num++;
		}
		if(num >= 8)
			break;
	}
	return num;
}
bool CDaGun::IsAllEqualExceptMagic(BYTE& card,/*int& num,*/BYTE card_list[MAXPAI],int cardlen /* = MAXPAI */)
{
	card = 0;
	//num = 0;
	if(cardlen > MAXPAI)
		return false;
	BYTE k = 0;
//	SortByIndex(card_list,cardlen);
	for(int i = cardlen-1; i >=0; i--)
	{
		if(IsMagic(card_list[i]))
			continue;
		k = card_list[i];
		break;
	}
	if(k == 0)
		return false;//全是王
	int n = 0;
	for(int i = cardlen-1; i >=0; i--)
	{
		if (IsMagic(card_list[i]))
			continue;
		if(GetCardLevel(k) != GetCardLevel(card_list[i]))
			return false;
		//num++;
	}
	card = k;
	return true;
}
bool CDaGun::IsNormalBomb(BYTE& card,/*int& num,*/BYTE card_list[MAXPAI],int cardlen /* = MAXPAI */)
{
	card = 0;
//	num = 0;
	if(cardlen != 4)//7张以下(含王)，才认为是普通炸弹
		return false;
	if (IsAllMagic(card_list) && GetKingNum(card_list) > 0  && GetHandCardsNum() == 4)
	{
		//全是赖子，并且有一个是王，类型错误
		return false;
	}
	if (IsAllMagic(card_list))
	{
		//全是赖子，并且不是最后一手
		card = 3;
		return true;
	}

	BYTE p =0;
	//全是王是笼炸
	//if(IsAllKing(card_list,cardlen))
	//{//如果都是王
	//	if(cardlen == 4)
	//	{
	//		card = 2;  //当2
	//		return true;
	//	}
	//}
	if(IsAllEqualExceptMagic(p,card_list,cardlen))
	{
		card = p;
//		num = cardlen;
		return true;
	}
	else
	{

	}
	return false;
}
bool CDaGun::IsKingBomb(BYTE card_list[MAXPAI],int cardlen /* = MAXPAI */)
{
	//return false;

	if(cardlen < 4)
		return false;
	return IsAllKing(card_list,cardlen);

	//if(IsKing(card_list[0]) && IsKing(card_list[1])
	//	&& IsKing(card_list[2]) && IsKing(card_list[3]) )
	//	return true;
	//return false;
}

int CDaGun::GetCardLevel(BYTE card_id)
{
	int level = 0;
	int tmpid = card_id - 1;
	level = tmpid%13+1 + 100;
	if(card_id%13==1) //Ａ
		level = 114;
	if(card_id%13==2) //2
		level = 116;
	if(card_id==SMA_KING)  //小王
		level = 118;
	if(card_id==BIG_KING)  //大王
		level = 120;
	if(card_id > 55)   //未知牌
		level = 200;
	if(card_id==0)   //无牌
		level = 0;

	return level;
}
void CDaGun::SortByIndex(BYTE card_list[MAXPAI],int cardlen /* = MAX_CARD_NUM */,bool smalltobig/*=true*/)
{
	if(smalltobig)
	{
		for(int i = 0; i < cardlen-1; i++)
		{
			for(int j = i+1;j < cardlen; j++)
			{
				if(card_list[j] > 0)
				{
					if(GetCardLevel(card_list[i]) > GetCardLevel(card_list[j]))
					{
						BYTE temp = card_list[i];
						card_list[i] = card_list[j];
						card_list[j] = temp;
					}
					else if(GetCardLevel(card_list[i]) == GetCardLevel(card_list[j]))
					{
						if(card_list[i] > card_list[j])
						{
							BYTE temp = card_list[i];
							card_list[i] = card_list[j];
							card_list[j] = temp;
						}
					}
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < cardlen-1; i++)
		{
			for(int j = i+1;j < cardlen; j++)
			{
				if(card_list[j] > 0)
				{
					if(GetCardLevel(card_list[i]) < GetCardLevel(card_list[j]))
					{
						BYTE temp = card_list[i];
						card_list[i] = card_list[j];
						card_list[j] = temp;
					}
					else if(GetCardLevel(card_list[i]) == GetCardLevel(card_list[j]))
					{
						if(card_list[i] < card_list[j])
						{
							BYTE temp = card_list[i];
							card_list[i] = card_list[j];
							card_list[j] = temp;
						}
					}
				}
			}
		}
	}
}
void CDaGun::SortByCount(BYTE card_list[MAXPAI],int cardlen /* = MAXPAI */)
{
	if(cardlen <= 1 || cardlen > MAXPAI)
		return;

	vector<TPokerGroup> vClassList[9];//0放王，1-8放1-8张牌的
	for(int i = 0; i < 9;i ++)
	{
		vClassList[i].clear();
	}

	TPokerGroup group;
	group.point = 0;
	group.index.clear();
	group.count = 0;

	BYTE pai[MAXPAI];
	memset(pai,0,sizeof(pai));

	SortByIndex(card_list,cardlen);
	BYTE PointIndex[15] = {CP_3_S,CP_4_S,CP_5_S,CP_6_S,CP_7_S,CP_8_S,CP_9_S,CP_10_S,CP_J_S,CP_Q_S,CP_K_S,CP_A_S,CP_2_S,CARDINDEX_SMALL,CARDINDEX_BIG};
	
	for(int i = 0; i < 15; i++)
	{
		int num = 0 ;
		int indexM[8];
		memset(indexM,0,sizeof(indexM));
		
		if(i == 13)
			int a = 0;
		for(int j = 0; j < MAXPAI; j++)
		{
			if(GetCardPoint(card_list[j]) == GetCardPoint(PointIndex[i]) )
			{
				if(num >= 8)
					break;
				indexM[num] = card_list[j];
				num++;
			}
		}
		if(num > 0)
		{
			group.point = indexM[0];
			group.count = num;
			group.index.clear();
			for(int k = 0; k < num; k++)
			{
				if(indexM[k] == 0)
					continue;
				group.index.push_back(indexM[k]);
			}
			if(PointIndex[i] != CARDINDEX_SMALL && PointIndex[i] != CARDINDEX_BIG )
				vClassList[num].push_back(group);
			else
			{
				vClassList[0].push_back(group);//放王的
			}
		}
	}
	int count = 0;
	//先放王的
	for(int i = (int)vClassList[0].size()-1; i >= 0; i--)
	{
		TPokerGroup Temp = vClassList[0][i];
		for(int j = 0; j < (int)Temp.index.size(); j++)
			pai[count++] = Temp.index[j];
	}
	//然后依次从多到少放
	for(int k = 8; k >= 1; k--)
	{
		for(int i = (int)vClassList[k].size()-1; i >=0 ; i--)
		{
			TPokerGroup Temp = vClassList[k][i];
			for(int j =(int)Temp.index.size()-1; j >= 0 ;j--)
			{
				pai[count++] = Temp.index[j];
			}
		}
	}
	for(int i = 0; i < MAXPAI; i++)
	{
		card_list[i] = pai[i];
	}
}
BYTE CDaGun::GetCardNum(BYTE card_list[MAXPAI],int cardlen /* = MAXPAI */)
{
	int iNum = 0;
	for(int i=0;i< cardlen && i< MAXPAI; i++)
	{
		if(card_list[i] > 0 && card_list[i] <= 55)
			iNum ++;
	}
	return iNum;
}

//是否存在天炸？
int CDaGun::HasKingBomb(BYTE card_list[MAXPAI])
{
	int nCount = 0;

	if (GetKingNum(card_list,MAXPAI) >= 2)
	{
		nCount++;
	}
	return nCount;
}
FakeType CDaGun::IsStrByMagic(int cardlen,int iMagicNum,int iZhaNum,TFakePoker fakepoker[8])
{
	FakeType temptype;
	memset(&temptype,0,sizeof(temptype));

	//修改iZhaNum < 2为iZhaNum < 1，让它适用于顺子
	if (m_allCard.size() < 24 || m_allCard[12].count != 0 || iZhaNum < 1 || iZhaNum > 12 || cardlen%iZhaNum != 0)
	{
		//有2，不可能组成连对
		temptype.cardtype.type = TYPE_ERROR;
		return temptype;//需要return 
	}

	int  byLeftMagicNum = iMagicNum;
	BYTE templist[MAXPAI];
	memset(templist,0,sizeof(templist));

	bool bLianFlag = true;
	int iLianNum = 0;
	int iNewcardlen = 0;
	int iUseMagicCount = 0;
	for (int iIndex = 0; iIndex < 12 && iNewcardlen < cardlen; iIndex++)
	{
		if (iLianNum == 0 && m_allCard[iIndex].count == 0 )
		{
			continue;
		}
		iLianNum++;
		//构造数据		
		for (int iCardCount = 0;iCardCount < iZhaNum && iCardCount < m_allCard[iIndex].count;iCardCount++)
		{
			templist[iNewcardlen++] = m_allCard[iIndex].index[iCardCount];
			temptype.cardtype.card = m_allCard[iIndex].point;//存放最大点数，暂时赋值
		}
		if (m_allCard[iIndex].count <= iZhaNum && byLeftMagicNum >= iZhaNum - m_allCard[iIndex].count)
		{
			int  byNeedMagicNum = iZhaNum - m_allCard[iIndex].count;
			byLeftMagicNum -= byNeedMagicNum;
			for (BYTE byMagic = 0;byMagic < byNeedMagicNum && byLeftMagicNum >= 0;byMagic++)
			{
				templist[iNewcardlen++] = m_vMagic[iUseMagicCount].index[0];
				temptype.cardtype.card = m_allCard[iIndex].point;//存放最大点数，暂时赋值
				//temptype.fakeking[iUseMagicCount].fakeindex = iIndex;//代替的值
				//temptype.fakeking[iUseMagicCount].index = fakepoker[iUseMagicCount++].index;//存放原来的值，就是王
				temptype.fakeking[iUseMagicCount].fakeindex = m_allCard[iIndex].point;//代替的值
				temptype.fakeking[iUseMagicCount].index = m_vMagic[iUseMagicCount++].index[0];//存放原来的值，就是赖子
			}
		}
		else
		{
			bLianFlag = false;
			break;
			//不能组成连对
		}
	}
	//可以组成连对
	if (bLianFlag && byLeftMagicNum % iZhaNum == 0)
	{
		temptype.cardtype.type = (iZhaNum==2?TYPE_TWOSTR:TYPE_THREESTR);
		temptype.cardtype.type = (iZhaNum==1?TYPE_ONESTR:temptype.cardtype.type);
		if (cardlen <= 3 && TYPE_ONESTR != temptype.cardtype.type)
		{
			temptype.cardtype.type = (iZhaNum==2?TYPE_TWO:TYPE_THREE);
			temptype.cardtype.type = (iZhaNum==1?TYPE_ONE:temptype.cardtype.type);
		}
	}
	else
		temptype.cardtype.type = TYPE_ERROR;

	return temptype;
}
FakeType CDaGun::GetTypeByMagic(BYTE card_list[MAXPAI],int cardlen,int iMagicNum,TFakePoker fakepoker[8],int outtype/*=TYPE_NULL*/)
{
	FakeType reType;
	memset(reType.fakeking,0,sizeof(reType.fakeking));
	if(iMagicNum >= 0)
	{//有1-4个王
		vector<FakeType> vTypeList;

		//构造m_allCard变量的数据
		TCARDS vec;
		for (BYTE byCard = 0;byCard < cardlen;byCard++)
		{
			if (card_list[byCard] > 0)
			{
				vec.push_back(card_list[byCard]);
			}
		}
		if (iMagicNum == 0)
		{
			GetGroupTypeByPointNoMagic(vec,m_allCard,m_vKing);
		}
		else
			GetGroupTypeByPoint(vec,m_allCard,m_vMagic,m_vKing);
		
		vTypeList.clear();
		FakeType temptypeOne = IsStrByMagic(cardlen,iMagicNum,1,fakepoker);
		if (temptypeOne.cardtype.type != TYPE_ERROR)
		{
			vTypeList.push_back(temptypeOne);
		}
		FakeType temptypeTwo = IsStrByMagic(cardlen,iMagicNum,2,fakepoker);
		if (temptypeTwo.cardtype.type != TYPE_ERROR)
		{
			vTypeList.push_back(temptypeTwo);
		}
		FakeType temptypeThree = IsStrByMagic(cardlen,iMagicNum,3,fakepoker);
		if (temptypeThree.cardtype.type != TYPE_ERROR)
		{
			vTypeList.push_back(temptypeThree);
		}
	
		if((int)vTypeList.size() > 0)
		{
			FakeType max_re;
			memset(&max_re.fakeking,0,sizeof(max_re.fakeking));
			if(outtype == TYPE_THREESTR || outtype == TYPE_TWOSTR || outtype == TYPE_ONESTR ||outtype == TYPE_THREE || outtype == TYPE_TWO || outtype == TYPE_ONE)
			{//说明手先出的人已经指定了出牌类型，那么跟的就是出牌类型
				int first = 0;
				for(int i = 0; i < (int)vTypeList.size(); i++)
				{
					if(vTypeList[i].cardtype.type == outtype)
					{
						max_re = vTypeList[i];
						first = i;
						break;
					}
				}
				for(int i = first; i < (int)vTypeList.size(); i++)
				{
					if(vTypeList[i].cardtype.type == max_re.cardtype.type)
					{
						if(Compare(max_re.cardtype,vTypeList[i].cardtype))
						{
							max_re = vTypeList[i];
						}
					}
				}
			}
			else
			{
				max_re = vTypeList[0];
				for(int i = 1; i < (int)vTypeList.size(); i++)
				{
					if(vTypeList[i].cardtype.type > max_re.cardtype.type)
					{
						max_re = vTypeList[i];
					}
					else if(vTypeList[i].cardtype.type == max_re.cardtype.type)
					{
						if(Compare(max_re.cardtype,vTypeList[i].cardtype))
						{
							max_re = vTypeList[i];
						}
					}
				}
			}
			
			reType = max_re;
		}
		else
		{
			reType.cardtype.type = TYPE_ERROR;
		}
	}
	else
	{
		reType.cardtype.type = TYPE_ERROR;
	}
	return reType;
}

TCardType CDaGun::GetType(BYTE card_list[MAXPAI], int cardlen/* =MAXPAI */, BYTE outMagicNum/*=0*/,BYTE byType/* = 0*/,  int outtype/* = TYPE_NULL*/, TFakePoker* refakepoker/* = NULL*/)
{
	TCardType re;	
	re.len	= 0;
	re.card	= 0;
	re.color= 0;
	re.type	= TYPE_NULL;
	re.count= 0;//借用为拱笼数
	SortByIndex(card_list,cardlen);
	re.len	= GetCardNum(card_list,cardlen);
	if(re.len == 0) return re;
	re.card = card_list[re.len-1];
	BYTE color = 0;

	switch(re.len)
	{
	case 0:
		re.type = TYPE_NULL;
		return re;
	case 1:
		re.type = TYPE_ONE;
		if(IsKing(re.card) && GetHandCardsNum() != 1)
		{
			//re.card = m_byFakeKingValue;//王单出算3
			re.type	= TYPE_NULL;//王不允许单出
		}
		else if (IsAllMagic(card_list) && GetKingNum(card_list) == 0)
		{
			re.card = m_byFakeKingValue;//赖子单出算3
		}
		return re;
	case 2:
		if( !IsMagic(card_list[0]) && !IsMagic(card_list[1]) )
		{//没有大小王
			if(GetCardLevel(card_list[0]) == GetCardLevel(card_list[1]))
				re.type = TYPE_TWO;
			else
				re.type = TYPE_ERROR;
		}
		else if(IsKing(card_list[0]) && IsKing(card_list[1]))
		{//全是王
			re.card = SMA_KING;
			re.type = TYPE_BOMB_NOMORL;
			re.count = GetCardLevel(SMA_KING) + 200;//
		}
		else if (IsAllMagic(card_list) && GetKingNum(card_list) == 0)
		{
			//全是非王的赖子
			re.card = m_byFakeKingValue;
			re.type = TYPE_TWO;
		}
		else
		{//有一张赖子
			re.card = IsMagic(card_list[0]) ? card_list[1] : card_list[0];
			re.type = TYPE_TWO;
			if (IsAllMagic(card_list) && GetKingNum(card_list) > 0  && GetHandCardsNum() == 2)
			{
				//全是赖子，并且有一个是王，最后一手时类型错误
				re.type = TYPE_NULL;
			}
		}
		return re;
	case 3:
		{
			if (IsAllMagic(card_list) && GetKingNum(card_list) > 0  && GetHandCardsNum() == 3)
			{
				//全是赖子，并且有一个是王，最后一手时类型错误
				re.type = TYPE_NULL;
				return re;
			}
			else if (IsAllMagic(card_list) && GetKingNum(card_list) == 0)
			{
				//全是非王的赖子
				re.card = m_byFakeKingValue;
				re.type = TYPE_THREE;
				return re;
			}
			else if (GetCardLevel(card_list[0]) == GetCardLevel(card_list[1]) && GetCardLevel(card_list[2]))
			{
				//全是普通牌
				re.card = card_list[0];;
				re.type = TYPE_THREE;
				return re;
			}
			TFakePoker fakepoker[8];
			memset(fakepoker,0,sizeof(fakepoker));

			int iMagicNum = GetMagicNum(card_list,cardlen,fakepoker);
			if(byType != 0 ) iMagicNum= 0;//非0表示没有赖子模式，给服务器用
			if(iMagicNum >= 0)
			{//有1-4个王
				FakeType ty = GetTypeByMagic(card_list,cardlen,iMagicNum,fakepoker,outtype);
				re.type = ty.cardtype.type;
				re.card = ty.cardtype.card;
				if(refakepoker != NULL)
				{
					for(int i = 0; i < 8; i++)
					{
						refakepoker[i] = ty.fakeking[i];
					}
				}
			}
			else
			{
				re.type = TYPE_ERROR;
			}
		}
		return re;
	default:// >= 4张
		if (IsAllMagic(card_list) && GetKingNum(card_list) > 0  && GetHandCardsNum() == re.len)
		{
			//全是赖子，并且有一个是王，最后一手时类型错误
			re.type = TYPE_NULL;
			return re;
		}
		if(re.len == 4)
		{
			int iMagicNum = GetMagicNum(card_list,cardlen);
			if(byType != 0 ) iMagicNum= 0;//非0表示没有赖子模式，给服务器用
			BYTE card = 0;
			if(IsNormalBomb(card,card_list,cardlen))
			{//普通4炸弹
				re.card = card;
				re.type = TYPE_BOMB_NOMORL;
				//re.count = GetCardLevel(card)+ (IsHasHardBomb() && iMagicNum == 0? 200 : 0);
				re.count = GetCardLevel(card)+ (IsHasHardBomb() && outMagicNum == 0? 200 : 0);
			}
			else
			{
				TFakePoker fakepoker[8];
				memset(fakepoker,0,sizeof(fakepoker));

				if(iMagicNum >= 0)
				{//有1-4个王
					FakeType ty = GetTypeByMagic(card_list,cardlen,iMagicNum,fakepoker,outtype);
					re.type = ty.cardtype.type;
					re.card = ty.cardtype.card;
					if(refakepoker != NULL)
					{
						for(int i = 0; i < 8; i++)
						{
							refakepoker[i] = ty.fakeking[i];
						}
					}
				}
				else
				{
					re.type = TYPE_ERROR;
				}
			}
			return re;
		}
		else if(re.len > 4 )
		{
			TFakePoker fakepoker[8];
			memset(fakepoker,0,sizeof(fakepoker));
			int iMagicNum = GetMagicNum(card_list,cardlen,fakepoker);
			if(byType != 0 ) iMagicNum= 0;//非0表示没有赖子模式，给服务器用
			if(iMagicNum >= 0)
			{//有1-4个王
				FakeType ty = GetTypeByMagic(card_list,cardlen,iMagicNum,fakepoker,outtype);
				re.type = ty.cardtype.type;
				re.card = ty.cardtype.card;
				if(refakepoker != NULL)
				{
					for(int i = 0; i < 8; i++)
					{
						refakepoker[i] = ty.fakeking[i];
					}
				}
			}
			return re;
		}
	}
	return re;
}
int CDaGun::GetScore(BYTE card_list[MAXPAI],int cardlen /* = MAXPAI */)
{
	int score = 0;
	for(int i=0;i<cardlen;i++)
	{
		if(GetCardLevel(card_list[i]) == GetCardLevel(5))
			score += 5;
		else if(GetCardLevel(card_list[i]) == GetCardLevel(10))
			score += 10;
		else if(GetCardLevel(card_list[i]) == GetCardLevel(13))
			score += 10;
	}
	return score;
}
bool CDaGun::CanOut(BYTE outCard[MAXPAI],BYTE followCard[MAXPAI],int outtype,int& followtype,bool isfirst/* = false*/,TFakePoker* fakepoker/* = NULL*/)
{
	int len1 = GetCardNum(outCard);
	TCardType cardtype1 = GetType(outCard,len1);
	int len2 = GetCardNum(followCard);
	TCardType cardtype2 = GetType(followCard,len2,0,0,outtype/*cardtype1.type*/,fakepoker);
	
	followtype = 0;
//	type = followtype.type;//得到出的牌的type;
	if(isfirst)
	{
		if(cardtype2.type != TYPE_ERROR && cardtype2.type != TYPE_NULL)
		{
			followtype = cardtype2.type;
			return true;
		}
		else
			return false;
	}
	cardtype1.type = outtype;//cardtype1.type得出来的不一定正确
	if(Compare(cardtype1,cardtype2))
	{
		followtype = cardtype2.type;
		return true;
	}
	return false;
}
//比较大小， typeFollow > typeFirst 返回真
bool CDaGun::Compare( TCardType typeFirst,TCardType typeFollow )
{
	// by sam  不允许出天炸 也就不存在比较 如果想要出天炸牌型直接返回false 那么Canout返回false 
	//															那么judgeCardOut也就返回false
	//if(typeFirst.type == TYPE_BOMB_KING) return false;//天炸直接返回
	//if(typeFollow.type == TYPE_BOMB_KING) return true;//天炸直接返回

	if(typeFirst.type == TYPE_ERROR) return false;

	if(typeFollow.type == TYPE_ERROR || typeFollow.type == TYPE_NULL) return false;

	if(typeFirst.type == TYPE_NULL)
	{
		if(typeFollow.type == TYPE_ONE
			|| typeFollow.type == TYPE_TWO
			|| typeFollow.type == TYPE_THREE
			|| typeFollow.type == TYPE_ONESTR
			|| typeFollow.type == TYPE_TWOSTR
			|| typeFollow.type == TYPE_THREESTR
			|| typeFollow.type == TYPE_BOMB_510K
			|| typeFollow.type == TYPE_BOMB_NOMORL
			|| typeFollow.type == TYPE_BOMB_GONGLONG)	//拱拢
			return true;
		else
			return false;
	}
	else if (typeFirst.type == TYPE_BOMB_NOMORL)
	{
		if (typeFollow.type == TYPE_BOMB_NOMORL)
		{
			if (typeFollow.count > typeFirst.count)
			{
				return true;
			}
			else if (typeFollow.count == typeFirst.count)
			{
				if (GetCardLevel(typeFollow.card) > GetCardLevel(typeFirst.card)) return true;
				else return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
	{//其他牌的比较，非炸弹
		if(typeFollow.type == TYPE_BOMB_510K
			|| typeFollow.type == TYPE_BOMB_NOMORL
			|| typeFollow.type == TYPE_BOMB_GONGLONG)
			return true;
		else if(typeFollow.type == typeFirst.type)
		{
			if(typeFollow.len == typeFirst.len && GetCardLevel(typeFollow.card) > GetCardLevel(typeFirst.card))
			{
				if (GetCardLevel(typeFollow.card) == GetCardLevel(2))
				{
					return true;
				}
				else if (GetCardLevel(typeFollow.card) == GetCardLevel(typeFirst.card) + 1)
				{
					return true;
				}
				return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	return false;
}

int CDaGun::CheckBeep( BYTE card_list[MAXPAI],BYTE outCard[MAXPAI],int outlen/*=MAXPAI*/ )
{
	//if(GetCardNum(card_list) < 4)
	//	return 0;
	if(outlen <= 0)
		return 0;
	int num = 0;
	int index[15],outindex[15];
	memset(index,0,sizeof(index));
	memset(outindex,0,sizeof(outindex));

	for(int i = 1; i <= 15; i++)
	{
		for(int j = 0; j < MAXPAI; j++)
		{
			if(card_list[j] >0 && card_list[j] < 55)
			{
				TPoker poker;
				poker.Set(card_list[j]);
				if(poker.point == i)
				{
					index[i-1]++;
				}
			}
		}
	}
	for(int i = 1; i <= 15; i++)
	{
		for(int j = 0; j < outlen; j++)
		{
			if(outCard[j] >0 && outCard[j] < 55)
			{
				TPoker poker;
				poker.Set(outCard[j]);
				if(poker.point == i)
				{
					outindex[i-1]++;
				}
			}
		}
	}
	bool isKingBeep = false;
	bool is7XiBeep  = false;
	bool is8XiBeep  = false;

	if(outlen < 7)
	{//出的牌小于7张
		for(int i = 0; i < 13; i++)
		{
			if(outindex[i] + index[i] == 7 && outindex[i] > 0 && !is7XiBeep)
			{//7喜
				is7XiBeep = true;
			}
			else if(outindex[i] + index[i] == 8 && outindex[i] > 0 && !is8XiBeep)
			{
				is8XiBeep = true;
			}
		}
		if(outlen < 4)
		{
			if(outindex[13] + outindex[14] + index[13] + index[14] == 4
				&& outindex[13] + outindex[14] > 0 && !isKingBeep)
			{
				isKingBeep = true;
			}
		}
		else if(outlen == 4)
		{
			if(outindex[13] + outindex[14] + index[13] + index[14] == 4
				&& outindex[13] + outindex[14] != 4 && outindex[13] + outindex[14] > 0 && !isKingBeep)
			{
				isKingBeep = true;
			}
		}
		else
		{
			if(outindex[13] + outindex[14] + index[13] + index[14] == 4
				&& outindex[13] + outindex[14] > 0 && !isKingBeep)
			{
				isKingBeep = true;
			}
		}
	}
	else if(outlen == 7)
	{
		for(int i = 0; i < 13; i++)
		{
			if(outindex[i] + index[i] == 7 && outindex[i] != 7 && outindex[i] > 0 && !is7XiBeep)
			{//7喜
				is7XiBeep = true;
			}
			else if(outindex[i] + index[i] == 8 && outindex[i] > 0 && !is8XiBeep)
			{
				is8XiBeep = true;
			}
		}
	}
	else if(outlen == 8)
	{
		for(int i = 0; i < 13; i++)
		{
			if(outindex[i] + index[i] == 7 && outindex[i] != 7 && outindex[i] > 0 && !is7XiBeep)
			{//7喜
				is7XiBeep = true;
			}
			else if(outindex[i] + index[i] == 8 && outindex[i] != 8 && outindex[i] > 0 && !is8XiBeep)
			{
				is8XiBeep = true;
			}
		}
	}
	else if(outlen > 8)
	{
		for(int i = 0; i < 13; i++)
		{
			if(outindex[i] + index[i] == 7 && outindex[i] >0 && !is7XiBeep)
			{//7喜
				is7XiBeep = true;
			}
			else if(outindex[i] + index[i] == 8 && outindex[i] > 0 && !is8XiBeep)
			{
				is8XiBeep = true;
			}
		}
	}
	if(isKingBeep)
		return 3;
	if(is8XiBeep)
		return 2;
	if(is7XiBeep)
		return 1;
	return 0;
}
///////////////////////////////////////////////////////
void CDaGun::GetGroupType( TCARDS mycard , bool bCanOut)
{
	if (!bCanOut) m_byHandCardsNum = 0;//当GetGroupType用于OnButtonJudgeCanOut函数时，传来的mycard并不是全部手牌数据，不能用来计算手牌数

	m_vOne.clear();
	m_vTwo.clear();
	m_vThree.clear();
	m_vFour.clear();
	m_vFive.clear();
	m_vSix.clear();
	m_vSeven.clear();
	m_vEight.clear();
	m_vKing.clear();
	m_vAllHandKing.clear();
	m_vMagic.clear();
	m_vAllHandMagic.clear();
	m_vK105.clear();
	TPoker tempPoker[MAXPAI];
	memset(tempPoker,0,sizeof(tempPoker));
	for(int i = 0; i < mycard.size(); i++)
	{
		tempPoker[i].Set(mycard[i]);
		if (!bCanOut) m_byHandCardsNum++;
	}
	TPokerGroup2 group;
	group.point = 0;
	group.index.clear();
	group.count = 0;
	group.color = 0;
	//首先找王
	for(int i = 14;i<= 15;i++)
	{
		for(int j = 0; j < MAXPAI; j++)
		{
			if(tempPoker[j].point == i)
			{
				group.point = tempPoker[j].point;
				group.index.clear();
				group.index.push_back(tempPoker[j].index);
				group.count = 1;
				group.color = 0;
				m_vKing.push_back(group);
			}
		}
	}
	//找赖子
	for(int i = 0;i< m_allMagicPoint.size();i++)
	{
		for(int j = 0; j < MAXPAI; j++)
		{
			if(tempPoker[j].point == m_allMagicPoint[i])
			{
				group.point = tempPoker[j].point;
				group.index.clear();
				group.index.push_back(tempPoker[j].index);
				group.count = 1;
				group.color = 0;
				m_vMagic.push_back(group);
			}
		}
	}
	
	//找其他的
	int pokerIndex[13]={3,4,5,6,7,8,9,10,11,12,13,1,2};
	
	for(int i = 0; i < 13; i++)
	{
		//赖子不重复放，只放在m_vMagic和mm_vAllHandMagic中
		bool bIsMagic = false;
		for (vector<BYTE>::iterator i_result = m_allMagicPoint.begin();i_result != m_allMagicPoint.end();i_result++)
		{
			if (GetCardPoint(pokerIndex[i]) == GetCardPoint(*i_result))
			{
				bIsMagic = true;
				break;
			}
		}
		if (bIsMagic) continue;

		int num = 0 ;
		int indexM[10] = {0,0,0,0,0,0,0,0,0,0};
		
		for(int j = 0; j < MAXPAI; j++)
		{
			if(tempPoker[j].point == pokerIndex[i])
			{
				indexM[num] = tempPoker[j].index;
				num++;
				if(pokerIndex[i] == 5 || pokerIndex[i] == 10 || pokerIndex[i] == 13)
				{
					group.point = pokerIndex[i];
					group.color = tempPoker[j].color;
					group.count = 1;
					group.index.clear();
					group.index.push_back(tempPoker[j].index);
					m_vK105.push_back(group);
				}
			}
		}
		group.point = pokerIndex[i];
		group.color = 0;//只针对k105
		group.count = num;
		group.index.clear();
		for(int k = 0; k < 8; k++)
		{
			if(indexM[k] == 0)
				continue;
			group.index.push_back(indexM[k]);
		}
		group.point = pokerIndex[i];
		if(num == 8) m_vEight.push_back(group);
		else if(num == 7) m_vSeven.push_back(group);
		else if(num == 6) m_vSix.push_back(group);
		else if(num == 5) m_vFive.push_back(group);
		else if(num == 4) m_vFour.push_back(group);
		else if(num == 3) m_vThree.push_back(group);
		else if(num == 2) m_vTwo.push_back(group);
		else if(num == 1) m_vOne.push_back(group);
	}
	//构造m_allHandCards变量的数据
	GetGroupTypeByPoint(mycard,m_allHandCards,m_vAllHandMagic,m_vAllHandKing);
}

//选择出牌 ,otherout不能有赖子，即赖子必须变成替换值
bool CDaGun::SelectCardOut(BYTE otherout[MAXPAI], int outtype,BYTE byCardlist[MAXPAI],BYTE byCardLen, vector<TPokerGroup2>& CanOutList, BYTE otherOutMagicNum)//选择出牌
{
	CanOutList.clear();
	byCardLen = GetCardNum(byCardlist,byCardLen);
	if (0 == byCardLen)
	{
		return false;
	}
	TCardType cardtype1;
	int outlevel = 0;
	if (outtype == TYPE_NULL || 0 == GetCardNum(otherout))
	{
		//首出牌
		cardtype1.type = TYPE_NULL;
		cardtype1.card = 0;
		outlevel = 0;
	}
	else
	{
		int len1 = GetCardNum(otherout);
		cardtype1 = GetType(otherout, len1, otherOutMagicNum,1, outtype);
		cardtype1.type = outtype;//重新设置下
		outlevel = GetCardLevel(cardtype1.card);

		if(outtype == TYPE_NULL || outtype == TYPE_ERROR)
		{
			//也当做首出牌
			cardtype1.type = TYPE_NULL;
			cardtype1.card = 0;
			outlevel = 0;
		}
	}
	TCARDS vec;
	vec.clear();
	for (BYTE byCard = 0;byCard < MAXPAI;byCard++)
	{
		if (byCardlist[byCard] > 0)
		{
			vec.push_back(byCardlist[byCard]);
		}
	}
	GetGroupType(vec,true);

	TPokerGroup2 group;
	group.color = 0;
	
	if(outtype == TYPE_BOMB_NOMORL || cardtype1.type == TYPE_NULL)
	{//普通炸弹，后面处理

	}
	if((outtype == TYPE_THREESTR || cardtype1.type == TYPE_NULL) && byCardLen >= 6)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetCombineThreeStr(cardtype1.card,byCardLen,templist,0);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			if (AllLastMagicOutWithKing(byCardLen) || byCardLen != it->count)//最后一手全赖子含王不允许出完
			{
			}
			else
				CanOutList.push_back(*it);
		}
	}
	if((outtype == TYPE_TWOSTR || cardtype1.type == TYPE_NULL) && byCardLen >= 4)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetCombineTwoStr(cardtype1.card,byCardLen,templist,0);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			if (AllLastMagicOutWithKing(byCardLen) || byCardLen != it->count)//最后一手全赖子含王不允许出完
			{
			}
			else
				CanOutList.push_back(*it);
		}
	}
	if((outtype == TYPE_ONESTR || cardtype1.type == TYPE_NULL) && byCardLen >= 3)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetCombineOneStr(cardtype1.card,byCardLen,templist,0);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			if (AllLastMagicOutWithKing(byCardLen) || byCardLen != it->count)//最后一手全赖子含王不允许出完
			{
			}
			else
				CanOutList.push_back(*it);
		}
	}
	if((outtype == TYPE_THREE || cardtype1.type == TYPE_NULL) && byCardLen == 3)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetCombineThree(cardtype1.card,templist,0);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			if (AllLastMagicOutWithKing(byCardLen) || byCardLen != it->count)//最后一手全赖子含王不允许出完
			{
			}
			else
				CanOutList.push_back(*it);
		}
	}
	//对子和单牌不用选择,//20180514 放开限制，首出要用这个函数判断是否符合牌型规则
	if((outtype == TYPE_TWO || cardtype1.type == TYPE_NULL) && byCardLen == 2)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetCombineTwo(cardtype1.card,templist,0);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			if (AllLastMagicOutWithKing(byCardLen) || byCardLen != it->count)//最后一手全赖子含王不允许出完
			{
			}
			else
				CanOutList.push_back(*it);
		}
	}
	if((outtype == TYPE_ONE || cardtype1.type == TYPE_NULL) && byCardLen == 1)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetAllOne(cardtype1.card,templist,0);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			if (AllLastMagicOutWithKing(byCardLen) || byCardLen != it->count)//最后一手全赖子含王不允许出完
			{
			}
			else
				CanOutList.push_back(*it);
		}
	}

	//找拱拢
	if (byCardLen == 4 || byCardLen == 2)
	{
		vector<TBombStr> mybombstr;
		GetAllXiGL(mybombstr);
		for(int i =0; i < (int)mybombstr.size(); i++)
		{
			//非拱笼类型的cardtype1.count =0,//防止4张牌里有双王时，双王拿出来当王炸了，别人出4张牌，就是不想当王炸，加上牌数限制
			if (/*byCardLen == mybombstr[i].nCount &&*/ (mybombstr[i].nBombCount > cardtype1.count
				|| (mybombstr[i].nBombCount == cardtype1.count && GetCardLevel(mybombstr[i].nPoint) > outlevel)))
			{
				group.index.clear();
				group.type = TYPE_BOMB_NOMORL;
				group.count = mybombstr[i].nCount;
				group.point = mybombstr[i].nPoint;
				group.index = mybombstr[i].index;
				memcpy(group.fakeking, mybombstr[i].fakeking, sizeof(group.fakeking));
				CanOutList.push_back(group);
			}
		}
	}
	
	if(CanOutList.size() > 0)//只有1种牌型或非法牌型时不用选择
		return true;
	else
		return false;
}
//最后一手牌，全是赖子且含王
bool CDaGun::AllLastMagicOutWithKing(BYTE byCardLen)
{
	if (GetHandCardsNum() == byCardLen)
	{
		if (m_vAllHandMagic.size() == byCardLen && m_vAllHandKing.size() > 0)
		{
			return true;
		}
	}
	return false;
}
bool CDaGun::BeepFirstCardOut(vector<TPokerGroup2>& mybeepout)
{
	TPokerGroup2 group;
	mybeepout.clear();
	
	vector<TPokerGroup2> templist;
	templist.clear();

	for(vector<TPokerGroup2>::iterator it = m_vOne.begin(); it != m_vOne.end(); it++)
	{//1
		group.index.clear();
		group.count = 1;
		group.point = it->point;
		group.index = it->index;
		group.type = TYPE_ONE;
		templist.push_back(group);
	}
	for(vector<TPokerGroup2>::iterator it = m_vTwo.begin(); it != m_vTwo.end(); it++)
	{//2
		group.index.clear();
		group.count = 2;
		group.point = it->point;
		group.index = it->index;
		group.type = TYPE_TWO;
		templist.push_back(group);
	}
	for(vector<TPokerGroup2>::iterator it = m_vThree.begin(); it != m_vThree.end(); it++)
	{//3
		group.index.clear();
		group.count = 3;
		group.point = it->point;
		group.index = it->index;
		group.type = TYPE_THREE;
		templist.push_back(group);
	}
	//3个以内的，都用最小的提示
	
	int size = (int)templist.size();
	for(int i =0; i < size-1; i++)
	{
		for(int j = i+1; j < size; j++)
		{
			if(GetCardLevel(templist[i].point) > GetCardLevel(templist[j].point) && templist[j].point > 0)
			{
				TPokerGroup2 temp = templist[i];
				templist[i] = templist[j];
				templist[j] = temp;
			}
		}
	}
	if(size > 0)
	{
		TPokerGroup2 temp = templist[0];
		mybeepout.push_back(temp);
		return true;
	}
	mybeepout.clear();
	vector<TBombStr> mybombstr;
	GetAllXiGL(mybombstr);
	for(int i =0; i < (int)mybombstr.size(); i++)
	{
		group.index.clear();
		group.count = mybombstr[i].nCount;
		group.point = mybombstr[i].nPoint; 
		group.index = mybombstr[i].index;
		group.type = TYPE_BOMB_NOMORL;
		mybeepout.push_back(group);
		return true;
	}
	//最后只剩下赖子的话
	if (m_vAllHandMagic.size() > 0)
	{
		mybeepout.clear();
		int iMagicCount = m_vAllHandMagic.size() - m_vAllHandKing.size();//优先出非王的赖子
		iMagicCount = (iMagicCount == 0?m_vAllHandMagic.size():iMagicCount);//如果赖子全是王，就把王都出了
		group.index.clear();
		for (int i = 0;i < iMagicCount && i < 4;i++)
		{
			
			group.count = iMagicCount;
			group.point = GetCardPoint(m_vAllHandMagic[i].index[0]); 
			group.index.push_back(m_vAllHandMagic[i].index[0]);	
		}
		group.type = (iMagicCount == 4 ? TYPE_BOMB_NOMORL : TYPE_THREE);
		group.type = (iMagicCount == 2 ? TYPE_TWO : group.type);
		group.type = (iMagicCount == 1 ? TYPE_ONE : group.type);
		if (iMagicCount == 2 && m_vAllHandKing.size() == 2)
		{
			group.type = TYPE_BOMB_NOMORL;//双王
		}
		if (m_vAllHandMagic.size() == 1 && m_vAllHandKing.size() == 1)
		{
			group.type = TYPE_ERROR;//单王，不允许出
			return false;
		}
		mybeepout.push_back(group);
	}

	return false;
}
//otherOutMagicNum为上家出的赖子数,otherout不能包含赖子，无法区分软硬炸，所以赖子数多用一个参数传
bool CDaGun::BeepCardOut(BYTE otherout[MAXPAI], int outtype, vector<TPokerGroup2>& mybeepout, BYTE outMagicNum)
{
	mybeepout.clear();
	TPokerGroup2 group;
	group.color = 0;
	int len1 = GetCardNum(otherout);
	TCardType cardtype1 = GetType(otherout, len1, outMagicNum,1);
	
	cardtype1.type = outtype;//重新设置下

	int outlevel = GetCardLevel(cardtype1.card);
	if(outtype == TYPE_NULL || outtype == TYPE_ERROR)
		return false;//不需要提示
	// by sam  不存在连炸牌型
	else if(outtype == TYPE_BOMB_NOMORL)
	{//普通炸弹，这里面就有王可以作为任何牌来搭配了

	}
	else if(outtype == TYPE_THREESTR)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetCombineThreeStr(cardtype1.card,cardtype1.len,templist);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			mybeepout.push_back(*it);
		}
	}
	else if(outtype == TYPE_TWOSTR)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetCombineTwoStr(cardtype1.card,cardtype1.len,templist);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			mybeepout.push_back(*it);
		}
	}
	else if(outtype == TYPE_ONESTR)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetCombineOneStr(cardtype1.card,cardtype1.len,templist);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			mybeepout.push_back(*it);
		}
	}
	else if(outtype == TYPE_THREE)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetCombineThree(cardtype1.card,templist);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			mybeepout.push_back(*it);
		}
	}
	else if(outtype == TYPE_TWO)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetCombineTwo(cardtype1.card,templist);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			mybeepout.push_back(*it);
		}
	}
	else if(outtype == TYPE_ONE)
	{
		vector<TPokerGroup2> templist;
		templist.clear();
		GetAllOne(cardtype1.card,templist);
		for(vector<TPokerGroup2>::iterator it = templist.begin(); it != templist.end(); it++)
		{
			mybeepout.push_back(*it);
		}
	}

	//找拱拢
	vector<TBombStr> mybombstr;
	GetAllXiGL(mybombstr);
	for(int i =0; i < (int)mybombstr.size(); i++)
	{
		//非拱笼类型的cardtype1.count =0,
		if(mybombstr[i].nBombCount > cardtype1.count 
			|| (mybombstr[i].nBombCount == cardtype1.count && GetCardLevel(mybombstr[i].nPoint) > outlevel))
		{
			group.type = TYPE_BOMB_NOMORL;
			group.index.clear();
			group.count = mybombstr[i].nCount;
			group.point = mybombstr[i].nPoint;
			group.index = mybombstr[i].index;
			memcpy(group.fakeking, mybombstr[i].fakeking, sizeof(group.fakeking));
			mybeepout.push_back(group);
		}
	}
	if(mybeepout.size() > 0)
		return true;
	else
		return false;
}

//此函数可以用于m_allHandCards和m_allCard
void CDaGun::GetGroupTypeByPoint(TCARDS mycard,vector<TPokerGroup2> & allCard,vector<TPokerGroup2>&	vMagic,vector<TPokerGroup2>& vKing)
{
	allCard.clear();
	TPoker tempPoker[MAXPAI];
	memset(tempPoker,0,sizeof(tempPoker));
	for(int i = 0; i < mycard.size(); i++)
	{
		tempPoker[i].Set(mycard[i]);
	}

	int pokerIndex[24]={3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13};
	for(int i = 0; i < 24; i++)
	{
		//赖子不重复放，只放在m_vMagic和mm_vAllHandMagic中
		bool bIsMagic = false;
		for (vector<BYTE>::iterator i_result = m_allMagicPoint.begin();i_result != m_allMagicPoint.end();i_result++)
		{
			if (GetCardPoint(pokerIndex[i]) == GetCardPoint(*i_result))
			{
				bIsMagic = true;
				break;
			}
		}

		TPokerGroup2 group;
		group.point = pokerIndex[i];
		group.index.clear();
		group.count = 0;
		group.color = 0;
		for(int j = 0; !bIsMagic && j < MAXPAI; j++)
		{
			if(tempPoker[j].point == pokerIndex[i])
			{
				group.count ++;
				group.index.push_back(tempPoker[j].index);
			}
		}
		allCard.push_back(group);
	}
	
	//要重新找王
	vKing.clear();
	TPokerGroup2 group;
	group.point = 0;
	group.index.clear();
	group.count = 0;
	group.color = 0;
	for (int i = 14; i <= 15; i++)
	{
		for (int j = 0; j < MAXPAI; j++)
		{
			if (tempPoker[j].point == i)
			{
				group.point = tempPoker[j].point;
				group.index.clear();
				group.index.push_back(tempPoker[j].index);
				group.count = 1;
				group.color = 0;
				vKing.push_back(group);
			}
		}
	}
	
	//找赖子
	vMagic.clear();
	for(int i = 0;i< m_allMagicPoint.size();i++)
	{
		for(int j = 0; j < MAXPAI; j++)
		{
			if(tempPoker[j].point == GetCardPoint(m_allMagicPoint[i]))
			{
				group.point = tempPoker[j].point;
				group.index.clear();
				group.index.push_back(tempPoker[j].index);
				group.count = 1;
				group.color = 0;
				vMagic.push_back(group);
			}
		}
	}
}

//此函数可以用于m_allHandCards和m_allCard
void CDaGun::GetGroupTypeByPointNoMagic(TCARDS mycard,vector<TPokerGroup2> & allCard,vector<TPokerGroup2>&	vKing)
{
	allCard.clear();
	TPoker tempPoker[MAXPAI];
	memset(tempPoker,0,sizeof(tempPoker));
	for(int i = 0; i < mycard.size(); i++)
	{
		tempPoker[i].Set(mycard[i]);
	}

	int pokerIndex[24]={3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13};
	for(int i = 0; i < 24; i++)
	{
		TPokerGroup2 group;
		group.point = pokerIndex[i];
		group.index.clear();
		group.count = 0;
		group.color = 0;
		for(int j = 0; j < MAXPAI; j++)
		{
			if(tempPoker[j].point == pokerIndex[i])
			{
				group.count ++;
				group.index.push_back(tempPoker[j].index);
			}
		}
		allCard.push_back(group);
	}

	//要重新找王
	vKing.clear();
	TPokerGroup2 group;
	group.point = 0;
	group.index.clear();
	group.count = 0;
	group.color = 0;
	for (int i = 14; i <= 15; i++)
	{
		for (int j = 0; j < MAXPAI; j++)
		{
			if (tempPoker[j].point == i)
			{
				group.point = tempPoker[j].point;
				group.index.clear();
				group.index.push_back(tempPoker[j].index);
				group.count = 1;
				group.color = 0;
				vKing.push_back(group);
			}
		}
	}
}

//获取所有同张的炸弹，比如软4个5 ，或2个王
void CDaGun::GetAllXiGL(vector<TBombStr>& mybombstr)
{
	int iMagicNum = m_vAllHandMagic.size();	//癞子的数量
	if (iMagicNum > 8 || iMagicNum < 0) return;	
	if (m_allHandCards.size() < 24) return;

	for (int i = 0; i <= iMagicNum && i < 4; i++)//全由赖子组成的炸弹后面处理
	{
		//for (int j = 0; j < m_allHandCards.size(); j++)//有重复数据
		for (int j = 0; j < 13; j++)
		{
			int itemsize = m_allHandCards[j].index.size();
			if (itemsize == 0) continue;	//数目为0不能组成喜
			TBombStr item;
			item.index.clear();
			if (i + itemsize == 4||(i == 0 && itemsize > 4)) //限定为必须4张//做牌时肯能可能现牌数大于4的情况，要能选出硬炸
			{
				TFakePoker	fakeking[MAXPAI];
				for (int k = 0; k < itemsize && k < 4; k++)
				{
					item.index.push_back(m_allHandCards[j].index[k]);
				}
				for (int k = 0; k < i; k++)
				{
					if (i != 4)
					{
						fakeking[k].fakeindex = GetCardPoint(m_allHandCards[j].index[0]);//替换的值
						fakeking[k].index = m_vAllHandMagic[k].index[0];//替换前的值,这个要保证是唯一的
					}
					item.index.push_back(m_vAllHandMagic[k].index[0]);
				}
				item.nBombCount = GetCardLevel(m_allHandCards[j].point) + (IsHasHardBomb() && i == 0? 200:0);//用nBombCount表示炸弹大小，硬炸+200，
				item.nPoint = m_allHandCards[j].point;
				//item.nMaxCount = i + itemsize;
				//item.nCount = i + itemsize;
				item.nMaxCount = 4;
				item.nCount = 4;
				memcpy(item.fakeking,fakeking,sizeof(item.fakeking));
				mybombstr.push_back(item);
			}
		}
	}
	//非王的癞子有4个，可以组成炸弹
	if (m_vAllHandMagic.size() - m_vAllHandKing.size() >= 4)
	{
		BYTE byCard = 0;
		BYTE byCount = 0;
		TBombStr item;
		item.index.clear();
		for (int k = 0; k < m_vAllHandMagic.size() && byCount < 4; k++)
		{
			if (!IsKing(m_vAllHandMagic[k].index[0]))
			{
				byCount++;
				byCard = m_vAllHandMagic[k].index[0];
				item.index.push_back(m_vAllHandMagic[k].index[0]);
			}	
		}
		if (byCard > 0 && byCard < CARDINDEX_BIG)
		{
			item.nBombCount = GetCardLevel(byCard) + (IsHasHardBomb() ? 200 : 0);
			item.nPoint = GetCardLevel(byCard);
			//item.nBombCount = 117+ (IsHasHardBomb()? 200:0);//4个3比4个2大，定为117
			//item.nPoint = 117;
			item.nMaxCount = 4;
			item.nCount = 4;
			mybombstr.push_back(item);
		}	
	}
	//最后手牌不是4个，全是赖子且含王
	if (GetHandCardsNum() != 4 && m_vAllHandMagic.size() >= 4 && m_vAllHandKing.size() > 0)
	{
		BYTE byCard = 0;
		TBombStr item;
		item.index.clear();
		BYTE byKingCnt = 0;
		for (int k = 0; k < m_vAllHandMagic.size() && k < 4; k++)
		{
			if (!IsKing(m_vAllHandMagic[k].index[0]))
			{
				byCard = m_vAllHandMagic[k].index[0];			
			}
			else 
			{
				item.fakeking[byKingCnt].fakeindex = 3;
				item.fakeking[byKingCnt++].index = m_vAllHandMagic[k].index[0];
			}
			item.index.push_back(m_vAllHandMagic[k].index[0]);
		}
		if (byCard > 0 && byCard < CARDINDEX_BIG)
		{
			item.nBombCount = GetCardLevel(byCard);
			item.nPoint = GetCardLevel(byCard);
			item.nMaxCount = 4;
			item.nCount = 4;
			mybombstr.push_back(item);
		}
	}
	//王炸
	int kingNum = m_vAllHandKing.size();	//王的数量
	for (int i = 2; i <= kingNum && i <= 2 ; i++)//2个王以上才是王炸，实际上只有2个王,//防止做牌时有多个王，这里限制最多2个王
	{
		TBombStr item;
		item.index.clear();
		for (int k = 0; k < i; k++)
		{
			item.index.push_back(m_vAllHandKing[k].index[0]);
		}
		item.nBombCount = GetCardLevel(SMA_KING) + 200;//
		item.nPoint = CP_BJ_S;
		item.nMaxCount = i ;
		item.nCount = i ;
		mybombstr.push_back(item);
	}
}

//求m的n次幂
int CDaGun::GetPower(int m,int n)
{
	int iTotal = 1;
	if (m <= 0||n < 0)
	{
		return iTotal;
	}

	for (int i = 0;i < n ;i++)
	{
		iTotal *= m;
	}
	return iTotal;
}

void CDaGun::GetCombineThreeStr( BYTE outpoint,int outlen,vector<TPokerGroup2>& combinelist ,BYTE byIsGanDengYang)
{
	int iMagicNum = (int)m_vAllHandMagic.size();
	if (outlen%3)
	{
		return;
	}

	if (byIsGanDengYang)
	{
		StrTool_GDY(outpoint,outlen/3,3,combinelist);
	} 
	else
	{
		StrTool(outpoint,outlen/3,3,combinelist);

		//最后可以做一次优化，让没有王的先提示，有王的后提示
		if(iMagicNum >0)SortBeepCardList(combinelist);
	}
}//end GetCombineThreeStr

//计算2连对和3连对、单连、三只、两只的函数。使用StrTool请确保GetGroupType函数被调用过，这样才能保证m_allHandCards 是最新的。
bool CDaGun::StrTool(const BYTE outpoint,const int iLianNum, const int iZhaNum,vector<TPokerGroup2>& combinelist )
{
	//添加代码让它适用于顺子
	if ((iZhaNum == 1 && (iLianNum < MIN_ONESTR_NUM  || iLianNum > 13)) || iZhaNum < 1 || iZhaNum > 12 ||iLianNum < 1 || iLianNum >12)
	{
		return false;
	}
	int iMagicNum = (int)m_vAllHandMagic.size();
	if (iMagicNum < 0 || iMagicNum > 8)
	{
		return false;
	}
	BYTE byOutPoint = GetCardPoint(outpoint);
	if (byOutPoint != 0 && ( byOutPoint - iLianNum  + 1 < 3 || (iLianNum > 1 && byOutPoint == 1) || (iLianNum <= 1 && byOutPoint == 2)))//他自己已经通天了，别人不可能比它大,连时A最大，非连时(2只或3只)2最大
	{
		return false;
	}
	if (m_allHandCards.size() < 24) return false;	

	BYTE byPoint = 0;
	bool bHasStr = false;

	//从比outpoint - iLianNum + 1大一点的牌开始遍历。跟GetAllGL相比，2不能组成连对这里是<12（从3到A共12个牌型）
	if (1 == byOutPoint ) byOutPoint = 14;//A的point是1，但索引是11，比它大一点索引是12
	int iIndex = (byOutPoint == 0?0:byOutPoint - iLianNum -1);//byOutPoint - iLianNum + 2 - 3:byOutPoint - iLianNum + 2为point起点，索引要减3
	for (; (iIndex + iLianNum - 1< 12) || (iLianNum == 1 &&iIndex == 12); iIndex++)//非连对时要能找到22或222
	{
		//肉挨肉选牌时要遍历所有可能，这里去掉
		//if (m_allHandCards[iIndex].count == 0 && (iIndex + iLianNum - 1 < 11))//确保遍历了最大的连对，跟GetAllGL相比，2不能组成连对这里是<11
		//{
		//	continue;
		//}
		//构造数据
		TFakePoker	fakeking[MAXPAI];
		BYTE card_list[MAXPAI]={0};
		int cardlen = 0,card_fk_len = 0;
		for (int idx = iIndex;idx < iIndex + iLianNum;idx++)
		{
			BYTE byTmepHaveNum = 0;//手中有这个牌的数量
			for (int iCardCount = 0;iCardCount < iZhaNum && iCardCount<m_allHandCards[idx].count;iCardCount++)
			{
				card_list[cardlen++] = m_allHandCards[idx].index[iCardCount];
				byTmepHaveNum++;
			}
			byPoint = m_allHandCards[idx].point;//直接获取最大的byPoint
			//这些牌将来需要用赖子替换的，肉挨肉需要保存
			if (byTmepHaveNum < iZhaNum)
			{
				for (int i = 0;i<iZhaNum - byTmepHaveNum;i++)
				{
					fakeking[card_fk_len++].fakeindex = byPoint;
				}	
			}
		}
		if (cardlen == 0)//必须至少有一个非赖子牌,但全是赖子且含3首出时可以当3(对3、3个3)出
		{
			if(!(iLianNum == 1 && iIndex == 0 && m_vAllHandMagic.size() > m_vAllHandKing.size()))
				continue;
		}
		//判断需要几个赖子
		if (cardlen + iMagicNum >= iLianNum * iZhaNum)//可以组成连对
		{
			BYTE byNeedMagicNum = iLianNum * iZhaNum - cardlen;
			for (BYTE byMagic = 0;byMagic < byNeedMagicNum;byMagic++)
			{
				fakeking[byMagic].index = m_vAllHandMagic[byMagic].index[0];//替换前的值,这个要保证是唯一的
				card_list[cardlen++] = m_vAllHandMagic[byMagic].index[0];
			}
			//是否是连对
			if (cardlen == iLianNum * iZhaNum)
			{
				bHasStr = true;
				//保存数据
				TPokerGroup2 tPKstr;
				tPKstr.index.clear();
				for (int t = 0; t < cardlen; t++)
				{
					tPKstr.index.push_back(card_list[t]);
				}
				tPKstr.count = cardlen;
				tPKstr.color = 0;
				tPKstr.point = byPoint;
				memcpy(tPKstr.fakeking,fakeking,sizeof(tPKstr.fakeking));
				tPKstr.type = (iZhaNum==2?TYPE_TWOSTR:TYPE_THREESTR);
				tPKstr.type = (iZhaNum==1?TYPE_ONESTR:tPKstr.type);
				if (iLianNum == 1)
				{
					tPKstr.type = (iZhaNum == 2 ? TYPE_TWO : TYPE_THREE);
					tPKstr.type = (iZhaNum == 1 ? TYPE_ONE : tPKstr.type);
				}
				combinelist.push_back(tPKstr);
			}
		}
	}
	return bHasStr;
}

//计算2连对和3连对、单连、三只、两只的函数。使用StrTool请确保GetGroupType函数被调用过，这样才能保证m_allHandCards 是最新的。
bool CDaGun::StrTool_GDY(const BYTE outpoint,const int iLianNum, const int iZhaNum,vector<TPokerGroup2>& combinelist )
{
	//添加代码让它适用于顺子
	if ((iZhaNum == 1 && (iLianNum < MIN_ONESTR_NUM || iLianNum > 13)) || iZhaNum < 1 || iZhaNum > 12 ||iLianNum < 1 || iLianNum >12)
	{
		return false;
	}
	int iMagicNum = (int)m_vAllHandMagic.size();
	if (iMagicNum < 0 || iMagicNum > 8)
	{
		return false;
	}
	BYTE byOutPoint = GetCardPoint(outpoint);
	if (byOutPoint != 0 && ((iLianNum <= 1 && byOutPoint == 2) || (iLianNum > 1 && byOutPoint == 1) || (byOutPoint >= 3 && byOutPoint - iLianNum + 1 < 3)))//他自己已经通天了，别人不可能比它大,连时A最大，非连时(2只或3只)2最大
	{
		return false;
	}
	if (m_allHandCards.size() < 24) return false;	

	BYTE byPoint = 0;
	bool bHasStr = false;

	//从比outpoint - iLianNum + 1大一点的牌开始遍历。跟GetAllGL相比，2不能组成连对这里是<12（从3到A共12个牌型）
	int iIndex = (byOutPoint == 0?0:byOutPoint - iLianNum -1);//byOutPoint - iLianNum + 2 - 3:byOutPoint - iLianNum + 2为point起点，索引要减3
	if (1 == byOutPoint ) iIndex = 12;//A的point是1，但索引是11，比它大一点索引是12
	//for (; iIndex + iLianNum - 1< 12 && iIndex <= byOutPoint + 1 - iLianNum; iIndex++)
	{
		//构造数据
		TFakePoker	fakeking[MAXPAI];
		BYTE card_list[MAXPAI]={0};
		int cardlen = 0,card_fk_len = 0;
		for (int idx = iIndex;idx < iIndex + iLianNum;idx++)
		{
			BYTE byTmepHaveNum = 0;//手中有这个牌的数量
			for (int iCardCount = 0;iCardCount < iZhaNum && iCardCount<m_allHandCards[idx].count;iCardCount++)
			{
				card_list[cardlen++] = m_allHandCards[idx].index[iCardCount];
				byTmepHaveNum++;
			}
			byPoint = m_allHandCards[idx].point;//直接获取最大的byPoint
			//这些牌将来需要用赖子替换的，肉挨肉需要保存
			if (byTmepHaveNum < iZhaNum)
			{
				for (int i = 0;i<iZhaNum - byTmepHaveNum;i++)
				{
					fakeking[card_fk_len++].fakeindex = byPoint;
				}	
			}
		}
		if (cardlen == 0 /*&& (m_vAllHandMagic.size() - m_vAllHandKing.size() < iLianNum * iZhaNum)*/)
		{
			if (iLianNum > 1)
			{
				//没有普通牌，并且必须用到王，不能出牌
				return false;
			}
			else
			{
				//判断是否还有2
				return Get2Str_GDY(outpoint,iLianNum,iZhaNum,combinelist);
			}
		}
		//判断需要几个赖子
		if (cardlen + iMagicNum >= iLianNum * iZhaNum)//可以组成连对
		{
			BYTE byNeedMagicNum = iLianNum * iZhaNum - cardlen;
			for (BYTE byMagic = 0;byMagic < byNeedMagicNum;byMagic++)
			{
				fakeking[byMagic].index = m_vAllHandMagic[byMagic].index[0];//替换前的值,这个要保证是唯一的
				card_list[cardlen++] = m_vAllHandMagic[byMagic].index[0];
			}
			//是否是连对
			if (cardlen == iLianNum * iZhaNum)
			{
				bHasStr = true;
				//保存数据
				TPokerGroup2 tPKstr;
				tPKstr.index.clear();
				for (int t = 0; t < cardlen; t++)
				{
					tPKstr.index.push_back(card_list[t]);
				}
				tPKstr.count = cardlen;
				tPKstr.color = 0;
				tPKstr.point = byPoint;
				memcpy(tPKstr.fakeking,fakeking,sizeof(tPKstr.fakeking));
				tPKstr.type = (iZhaNum==2?TYPE_TWOSTR:TYPE_THREESTR);
				tPKstr.type = (iZhaNum==1?TYPE_ONESTR:tPKstr.type);
				if (iLianNum == 1)
				{
					tPKstr.type = (iZhaNum == 2 ? TYPE_TWO : TYPE_THREE);
					tPKstr.type = (iZhaNum == 1 ? TYPE_ONE : tPKstr.type);
				}
				combinelist.push_back(tPKstr);
			}
		}
	}
	if (iLianNum > 1)
	{
		//没有普通牌，并且必须用到王，不能出牌
		return bHasStr;
	}
	else
	{
		//判断是否还有2//byOutPoint == 1时，前面已经找过2了，不用重复找
		if (1 != byOutPoint)
			return Get2Str_GDY(outpoint,iLianNum,iZhaNum,combinelist);
	}
	return bHasStr;
}

//获取包含2的三只、两只的函数。使用StrTool请确保GetGroupType函数被调用过，这样才能保证m_allHandCards 是最新的。
bool CDaGun::Get2Str_GDY(const BYTE outpoint,const int iLianNum, const int iZhaNum,vector<TPokerGroup2>& combinelist )
{
	if (iLianNum != 1 || iZhaNum < 1)
	{
		return false;
	}
	int iMagicNum = (int)m_vAllHandMagic.size();
	if (iMagicNum < 0 || iMagicNum > 8)
	{
		return false;
	}
	BYTE byOutPoint = GetCardPoint(outpoint);
	if ( byOutPoint == 2)
	{
		return false;
	}
	if (m_allHandCards.size() < 24 || m_allHandCards[12].count == 0) return false;	

	BYTE byPoint = 0;
	bool bHasStr = false;

	//从比outpoint - iLianNum + 1大一点的牌开始遍历。跟GetAllGL相比，2不能组成连对这里是<12（从3到A共12个牌型）
	int iIndex = 12;
	//for (; iIndex + iLianNum - 1< 12 && iIndex <= byOutPoint + 1 - iLianNum; iIndex++)
	{
		//构造数据
		TFakePoker	fakeking[MAXPAI];
		BYTE card_list[MAXPAI]={0};
		int cardlen = 0;
		for (int idx = iIndex;idx < iIndex + iLianNum;idx++)
		{
			for (int iCardCount = 0;iCardCount < iZhaNum && iCardCount<m_allHandCards[idx].count;iCardCount++)
			{
				card_list[cardlen++] = m_allHandCards[idx].index[iCardCount];
			}
			byPoint = m_allHandCards[idx].point;//直接获取最大的byPoint
		}
		if (cardlen == 0 && (m_vAllHandMagic.size() - m_vAllHandKing.size() < iLianNum * iZhaNum))
		{
			//没有普通牌，并且必须用到王，不能出牌
			return false;
		}
		//判断需要几个赖子
		if (cardlen + iMagicNum >= iLianNum * iZhaNum)//可以组成连对
		{
			BYTE byNeedMagicNum = iLianNum * iZhaNum - cardlen;
			for (BYTE byMagic = 0;byMagic < byNeedMagicNum;byMagic++)
			{
				fakeking[byMagic].fakeindex = 2;//替换的值,这个就是找2的函数，所以这里固定是2
				fakeking[byMagic].index = m_vAllHandMagic[byMagic].index[0];//替换前的值,这个要保证是唯一的
				card_list[cardlen++] = m_vAllHandMagic[byMagic].index[0];
			}
			//是否是连对
			if (cardlen == iLianNum * iZhaNum)
			{
				bHasStr = true;
				//保存数据
				TPokerGroup2 tPKstr;
				tPKstr.index.clear();
				for (int t = 0; t < cardlen; t++)
				{
					tPKstr.index.push_back(card_list[t]);
				}
				tPKstr.count = cardlen;
				tPKstr.color = 0;
				tPKstr.point = byPoint;
				memcpy(tPKstr.fakeking,fakeking,sizeof(tPKstr.fakeking));
				tPKstr.type = (iZhaNum==2?TYPE_TWO:TYPE_THREE);
				tPKstr.type = (iZhaNum==1?TYPE_ONE:tPKstr.type);
				combinelist.push_back(tPKstr);
			}
		}
	}
	return bHasStr;
}

void CDaGun::GetCombineTwoStr( BYTE outpoint,int outlen,vector<TPokerGroup2>& combinelist ,BYTE byIsGanDengYang)
{
	int iMagicNum = (int)m_vAllHandMagic.size();

	if (outlen%2)
	{
		return;
	}
	
	if (byIsGanDengYang)
	{
		StrTool_GDY(outpoint,outlen/2,2,combinelist);
	} 
	else
	{
		StrTool(outpoint,outlen/2,2,combinelist);
		if(iMagicNum >0) SortBeepCardList(combinelist);
	}
}//end GetCombineTwoStr

void CDaGun::GetCombineOneStr( BYTE outpoint,int outlen,vector<TPokerGroup2>& combinelist,BYTE byIsGanDengYang)
{
	int iMagicNum = (int)m_vAllHandMagic.size();

	if (outlen < 3 ||outlen > 12)
	{
		return;
	}

	if (byIsGanDengYang)
	{
		StrTool_GDY(outpoint,outlen,1,combinelist);
	} 
	else
	{
		StrTool(outpoint,outlen,1,combinelist);
		if(iMagicNum >0) SortBeepCardList(combinelist);
	}
}//end GetCombineTwoStr

void CDaGun::GetCombineThree( BYTE outpoint,vector<TPokerGroup2>& combinelist ,BYTE byIsGanDengYang)
{
	combinelist.clear();
	int iMagicNum = m_vAllHandMagic.size();
	//if (outlen != 3)
	//{
	//	return;
	//}
	if (byIsGanDengYang)
	{
		StrTool_GDY(outpoint,1,3,combinelist);
	} 
	else
	{
		StrTool(outpoint,1,3,combinelist);
		if(iMagicNum >0) SortBeepCardList(combinelist);
	}
}

void CDaGun::GetCombineTwo( BYTE outpoint,vector<TPokerGroup2>& combinelist ,BYTE byIsGanDengYang)
{
	combinelist.clear();
	int iMagicNum = m_vAllHandMagic.size();

	//if (outlen != 2)
	//{
	//	return;
	//}

	if (byIsGanDengYang)
	{
		StrTool_GDY(outpoint,1,2,combinelist);
	} 
	else
	{
		StrTool(outpoint,1,2,combinelist);
		if(iMagicNum >0) SortBeepCardList(combinelist);
	}
}

void CDaGun::GetAllOne( BYTE outpoint,vector<TPokerGroup2>& combinelist , BYTE byIsGanDengYang)
{

	int iMagicNum = (int)m_vAllHandMagic.size();
	if (iMagicNum < 0 || iMagicNum > 8)
	{
		return ;
	}
	BYTE byOutPoint = GetCardPoint(outpoint);
	if (m_allHandCards.size() < 24 || 2 == byOutPoint) return;
	//首出牌时，3可以出
	if (0 == byOutPoint && 1 == iMagicNum && 0 == m_vAllHandKing.size())
	{
		//保存数据
		TPokerGroup2 tPKone;
		tPKone.index.clear();
		for (int t = 0; t < m_vAllHandMagic.size(); t++)
		{
			if (3 == GetCardPoint(m_vAllHandMagic[t].index[0]))
			{
				tPKone.index.push_back(m_vAllHandMagic[t].index[0]);
				break;
			}
		}
		tPKone.count = 1;
		tPKone.color = 0;
		tPKone.point = 3;
		tPKone.type = TYPE_ONE;
		combinelist.push_back(tPKone);
	}

	BYTE byCnt = 0;
	int iIndex = (byOutPoint == 0?0:byOutPoint + 1 - 3);//索引要减3
	if (1 == byOutPoint ) iIndex = 12;//A的point是1，但索引是11，比它大一点索引是12
	for (; iIndex < 13; iIndex++)
	{	
		byCnt++;
		if (byIsGanDengYang && byCnt > 1 && 12 != iIndex) //肉挨肉玩法时，只能找到一个紧挨着的牌
		{
			continue;
		}
		if (m_allHandCards[iIndex].count == 0 )
		{
			continue;
		}
		//构造数据
		BYTE card_list[MAXPAI]={0};
		int cardlen = 0;
		int iZhaNum = 1;
		for (int iCardCount = 0;iCardCount < iZhaNum && iCardCount<m_allHandCards[iIndex].count;iCardCount++)
		{
			card_list[cardlen++] = m_allHandCards[iIndex].index[iCardCount];
		}
		BYTE byPoint = m_allHandCards[iIndex].point;

		//保存数据
		TPokerGroup2 tPKone;
		tPKone.index.clear();
		for (int t = 0; t < cardlen; t++)
		{
			tPKone.index.push_back(card_list[t]);
		}
		tPKone.count = cardlen;
		tPKone.color = 0;
		tPKone.point = byPoint;
		tPKone.type = TYPE_ONE;
		combinelist.push_back(tPKone);
	}
}

void CDaGun::SortBeepCardList( vector<TPokerGroup2>& combinelist )
{
	vector<TPokerGroup2> templist0;
	vector<TPokerGroup2> templist1;
	vector<TPokerGroup2> templist2;
	vector<TPokerGroup2> templist3;
	vector<TPokerGroup2> templist4;
	vector<TPokerGroup2> templist5;
	vector<TPokerGroup2> templist6;
	vector<TPokerGroup2> templist7;
	vector<TPokerGroup2> templist8;
	templist0.clear();
	templist1.clear();
	templist2.clear();
	templist3.clear();
	templist4.clear();
	templist5.clear();
	templist6.clear();
	templist7.clear();
	templist8.clear();

	for(int i =0; i < combinelist.size(); i++)
	{
		int nNum = 0;
		for(int j = 0; j < combinelist[i].index.size(); j++)
		{
			if(IsKing(combinelist[i].index[j]))
			{
				nNum++;
			}
		}
		if(nNum == 0)
		{
			templist0.push_back(combinelist[i]);
		}
		else if(nNum == 1)
		{
			templist1.push_back(combinelist[i]);
		}
		else if(nNum == 2)
		{
			templist2.push_back(combinelist[i]);
		}
		else if(nNum == 3)
		{
			templist3.push_back(combinelist[i]);
		}
		else if(nNum == 4)
		{
			templist4.push_back(combinelist[i]);
		}
		else if(nNum == 5)
		{
			templist5.push_back(combinelist[i]);
		}
		else if(nNum == 6)
		{
			templist6.push_back(combinelist[i]);
		}
		else if(nNum == 7)
		{
			templist7.push_back(combinelist[i]);
		}
		else if(nNum == 8)
		{
			templist8.push_back(combinelist[i]);
		}
	}
	combinelist.clear();
	for(int i = 0; i < templist0.size(); i++)
		combinelist.push_back(templist0[i]);
	for(int i = 0; i < templist1.size(); i++)
		combinelist.push_back(templist1[i]);
	for(int i = 0; i < templist2.size(); i++)
		combinelist.push_back(templist2[i]);
	for(int i = 0; i < templist3.size(); i++)
		combinelist.push_back(templist3[i]);
	for(int i = 0; i < templist4.size(); i++)
		combinelist.push_back(templist4[i]);
	for(int i = 0; i < templist5.size(); i++)
		combinelist.push_back(templist5[i]);
	for(int i = 0; i < templist6.size(); i++)
		combinelist.push_back(templist6[i]);
	for(int i = 0; i < templist7.size(); i++)
		combinelist.push_back(templist7[i]);
	for(int i = 0; i < templist8.size(); i++)
		combinelist.push_back(templist8[i]);
}