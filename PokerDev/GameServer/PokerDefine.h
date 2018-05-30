#pragma once

#include "typedef.h"

namespace PokerDef
{
const BYTE MAX_POKER_COUNTS		= 54;							// 整副牌54张(含小王,大王) 
const BYTE CARDINDEX_SMALL		= 53;							// 小王牌索引 
const BYTE CARDINDEX_BIG		= 54;							// 大王牌索引 
const BYTE CARDINDEX_BACK		= 55;							// 背面牌索引 
const BYTE CARDINDEX_NULL		= 0;							// 无效牌索引 
//const BYTE CARDINDEX_FIRST	= 1;							// 有效牌索引第一张 
//const BYTE CARDINDEX_LAST		= CARDINDEX_BIG;				// 有效牌索引最后一张 


	///>==============================================
	///> 扑克牌花色
	///>==============================================
	typedef enum e_PokerColor
	{
		CC_NULL_S = 0,		/* 无色					*/
	    
		CC_DIAMOND_S,		/* 方块 => Diamond		*/
		CC_CLUB_S,			/* 梅花 => Club			*/
		CC_HEART_S,			/* 红心 => Heart		*/
		CC_SPADE_S,			/* 黑桃 => Spade		*/
	    
		CC_TOTAL_S,			/* TOTAL OF COLORS 		*/
	}TPOKERCOLOR;

	///>==============================================
	///> 扑克牌点数
	///>==============================================
	typedef enum e_CardPoint
	{
		CP_NULL_S = 0, 		/* 牌背					*/
	    
		CP_A_S,			 	/* A					*/
		CP_2_S,	 			/* 2					*/
		CP_3_S,		 		/* 3					*/
		CP_4_S,		 		/* 4					*/
		CP_5_S,		 		/* 5					*/
		CP_6_S,		 		/* 6					*/
		CP_7_S,		 		/* 7					*/
		CP_8_S,		 		/* 8					*/
		CP_9_S,		 		/* 9					*/
		CP_10_S,		 	/* 10					*/
		CP_J_S,		 		/* J	=> Jack			*/
		CP_Q_S,		 		/* Q	=> Queen		*/
		CP_K_S,		 		/* K	=> King			*/
	    
		CP_BJ_S,		 	/* 小王	=> Black Joker	*/
		CP_RJ_S,		 	/* 大王	=> Red Joker	*/
	    
		CP_TOTAL_S,	 		/* TOTAL OF POINTS		*/
	}TCARDPOINT;

	// 获取牌索引
	inline BYTE GetCard(BYTE nColor, BYTE nPoint)
	{
		//获取小王索引
		if (CP_BJ_S == nPoint)
		{
			return (CC_SPADE_S - 1) * 13 + CP_BJ_S;
		}
		//获取大王索引
		else if (CP_RJ_S == nPoint)
		{
			return (CC_SPADE_S - 1) * 13 + CP_RJ_S;
		}
		//获取普通牌索引
		else if (CP_A_S <= nPoint && nPoint <= CP_K_S)
		{
			if (CC_DIAMOND_S <= nColor && nColor <= CC_SPADE_S)
				return (nColor - 1) * 13 + nPoint;
		}
		return 0;
	}

	// 获取牌花色
	inline BYTE GetCardColor(BYTE nCard)
	{
		//处理获取普通牌花色
		if (CARDINDEX_NULL < nCard && nCard < CARDINDEX_SMALL)
			return (((nCard - 1) / 13) % 4) + 1;
		//处理王牌的花色
		else if (nCard == CARDINDEX_SMALL)
			return CC_NULL_S;//小王无花色
		else if (nCard == CARDINDEX_BIG)
			return CC_NULL_S;//大王无花色
		return 0;
	}

	// 获取牌点数
	inline BYTE GetCardPoint(BYTE nCard)
	{
		//处理获取普通牌的点数
		if (CARDINDEX_NULL < nCard && nCard < CARDINDEX_SMALL)
			return (nCard - 1) % 13 + 1;
		//处理获取王牌的点数
		else if (nCard == CARDINDEX_SMALL)
			return CP_BJ_S;
		else if (nCard == CARDINDEX_BIG)
			return CP_RJ_S;
		return 0;
	}
	
	// 根据牌值获取字符串
	inline std::string GetStringByCard(BYTE nCard)
	{
		std::string strColor = "";
		std::string strPoint = "";

		e_PokerColor color = (e_PokerColor)GetCardColor(nCard);
		e_CardPoint point = (e_CardPoint)GetCardPoint(nCard);

		if (point == CP_NULL_S) //牌背
		{
			return "00";
		}
		else if(point == CP_BJ_S) //小王
		{
			return "bj";
		}
		else if (point == CP_RJ_S) //大王
		{
			return "rj";
		}
		else
		{
			if (color == CC_SPADE_S)
			{
				strColor = "s";
			}
			else if (color == CC_HEART_S)
			{
				strColor = "h";
			}
			else if (color == CC_CLUB_S)
			{
				strColor = "c";
			}
			else if (color == CC_DIAMOND_S)
			{
				strColor = "d";
			}

			if (point == CP_A_S)
			{
				strPoint = "A";
			}
			else if (point == CP_2_S)
			{
				strPoint = "2";
			}
			else if (point == CP_3_S)
			{
				strPoint = "3";
			}
			else if (point == CP_4_S)
			{
				strPoint = "4";
			}
			else if (point == CP_5_S)
			{
				strPoint = "5";
			}
			else if (point == CP_6_S)
			{
				strPoint = "6";
			}
			else if (point == CP_7_S)
			{
				strPoint = "7";
			}
			else if (point == CP_8_S)
			{
				strPoint = "8";
			}
			else if (point == CP_9_S)
			{
				strPoint = "9";
			}
			else if (point == CP_10_S)
			{
				strPoint = "0";
			}
			else if (point == CP_J_S)
			{
				strPoint = "J";
			}
			else if (point == CP_Q_S)
			{
				strPoint = "Q";
			}
			else if (point == CP_K_S)
			{
				strPoint = "K";
			}
		}
		strColor += strPoint;
		return strColor;
	}


};
