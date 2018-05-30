
#ifndef _SYS_FUNC_H_
#define _SYS_FUNC_H_

#include <string>
#include <vector>
#include <map>
using namespace std;

#define SYSFUNC_DEBUG_LOG 0

class SysFunc {
    
public:
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  写Log
    static void PrintLog(const char* lpszLog);

    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  保存字符数据(必须UTF8编码 非UTF8可能不保存)
    static void SaveStringData(const char* lpszKey, const char* lpszData);
    
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  读取字符数据
    static bool LoadStringData(const char* lpszKey, string& strReturn);
	static bool LoadStringData(const char* lpszKey, char* strReturn);
    
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  保存整形数据
    static void SaveIntData(const char* lpszKey, int nData);
    
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  读取整形数据
    static int  LoadIntData(const char* lpszKey);
    
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  删除数据
    static void RemoveData(const char* lpszKey);
    
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  GB_18030_2000到UTF8编码转换
    static bool GB_18030_2000ToUTF_8(const char* lpszStr, string& strReturn);
	static bool GB_18030_2000ToUTF_8(const char* lpszStr, char* strReturn);
    static std::string GetGB_18030_2000ToUTF_8(const string& strReturn);
    
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  UTF8到GB_18030_2000编码转换
    static bool UTF_8ToGB_18030_2000(const char* lpszStr, string& strReturn);
	static bool UTF_8ToGB_18030_2000(const char* lpszStr, char* strReturn);
  
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  获取当前网络类型 type(0:无网络, 1:wifi, 2:GSM等其他), 等级 level, 总等级 alllevel
    static bool GetCurNet(int& type, int& level, int& alllevel);
	// 功能描述:  获取当前电量:0~1，-1表示未获取到
	static float GetBatteryLevel();
    ////////////////////////////////////////////////////////////////////////////
    //功能描述:  震动一次
    static bool QuakeOneTime();
    
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  获取当前年、月、日、时、分、秒
    static bool GetCurCalendar(int& year, int& month, int& day, int& hour, int& minute, int& second);   

    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  获取设备唯一标识
    static bool GetUniqueIdentifier(string& strReturn);
    
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述: 获取设备宽
    static int  GetScreenWidth();
    
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述: 获取设备高
    static int  GetScreenHeight();
    
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述: 分享 nType= 1 2 3 4   微信　朋友图　qq 　空间
	static bool SendShare(const char* lpszTitle, const char* lpszMsg, const char *lpszURL, const char* lpszPng, int nType);
	static bool SendShare(const char* lpszTitle, const char* lpszMsg);

	// 功能描述: 启动程序
	static bool StartApp(const char* lpszPackage, const char* lpszClass);

	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 读取房间人数配置 
    static bool GetRoomConfig(string& strRoomConfig);

	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 读取子游戏房间ID配置 
    static bool GetRoomID(string& strRoomID);

	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 读取功能配置
    static bool GetFunction(string& strFunction);

	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 读取版本信息
    static bool GetLobbyVersion(string& strVersion);

	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 读取更新信息,index从0开始依次为大厅及各组件
	static bool GetUpdateData(int index, string& strUpdateData);

	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 读取分包升级信息 index从0开始依次为大厅、资源、游戏
	//strSubUpdateInfo = "1|0|2089"，分别表示版本号、是否强制升级、升级包大小
	static bool GetSubUpdateInfo(int index, string& strSubUpdateInfo);

	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 读取大厅更新记录信息 如"1|0|300"分别表示版本号，是否强制升级，资源包大小(k)
	static bool GetLobbyRecordInfo(string& strResUpdateInfo);

	//////////////////////////////////////////////////////////////////////////
	//功能描述：解压缩zip
	static void InstallZip(int nCurUpdate);

	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 读取登录IP
    static bool GetLoginIP(string& strLoginIP);

	//功能描述：读取云信开关
	static bool GetYXFunc(string& strYXFunc);

	static bool LaunchUrl(const std::string& url);

	static std::string Utf16ToUtf8(const std::wstring& str_utf16_enc);

	static std::wstring Utf8ToUtf16(const std::string& str_utf8_enc);

	static std::string Utf16ToGBK(const std::wstring& str_utf16_enc);

	static std::wstring GBKToUtf16(const std::string& str_gbk_enc);

	static std::string GbkToUtf8(const std::string& str_gbk_enc);

	static std::string Utf8ToGbk(const std::string& str_utf8_enc);

	static bool CopyStringToClipboard(const std::string& str_utf8_enc);

	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 安装So，第一次时调用，下载完后自动加载
    static void InstallSo(const char* soid);

	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 启动升级
    static void BeginUpdate();

	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 中止升级
    static void AbortUpdate();
////////////////////////////////////////////////////////////////////////////
	// 功能描述: WebView回退
    static void WebViewGoBack();

	// 功能描述: 统计：进入页面
	static bool UMengOnPageStart(const char* lpszPage);

	// 功能描述: 统计：退出页面
	static bool UMengOnPageEnd(const char* lpszPage);

	// 功能描述: 统计：事件
	static bool UMengOnEvent(const char* lpszEvent);

	///////////////////////////////////////////////////////
	// 功能描述: 给手机发送短信验证码
	static void SendValideCode(const char* lpszPhone);

	// 功能描述: 判断用户输入的验证码是否有效
	static void IsValideCode(const char* lpszPhone, const char* lpszCode);

	////////////////////////////////////////////////////////////////////////////

	// 功能描述: 获取客户端渠道号 
	static bool GetChannel(string& strChannel);

	//进入相册 path--储存路径
	static void ShowPhotoDialog(const char * path);
    
	////////////////////////////////////////////////////////////////////////////
	// 功能描述: 读取图片地址 
	static bool GetPhotoPath(string& strPhotoPath);

	//支付<ping++>(订单号、渠道、token、金额<分>)
	static void PingRecharge(const char * orderNum, const char * token, const char * channel, const char * subject, const int amount);
	//支付<短代>（订单号、token、计费点）
	static void MsgRecharge(const char * orderNum, const char * token, const char * billingIndex);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//App内购
	static void AppRecharge(const char * appProductID, const char * orderNum, const char * token);
#endif

// 功能描述: 进入网易七鱼客服系统 
	/*参数：paralist：字符串参数合集  格式:"参数1|参数2|..."
			userJson：个人信息参数合集，发送给客服系统后台，为一个json数组

			* paraArray[0]:个人信息显示的url
			* paraArray[1]:个人信息显示的url的名称
			* paraArray[2]:聊天页面左上角的title
			* paraArray[3]:唯一标识符UserID
			* paraArray[4]:聊天页面客服头像的url //仅在客户端聊天页面显示，可为空
			* paraArray[5]:聊天页面玩家头像的url //仅在客户端聊天页面显示，可为空
	*/
	static void ShowSevenFishSys(const char *paralist, const char *userJsonData);

	//功能描述：玩家注销登录时，置空用户信息
	static void DeleteSevenFishInfo();
	//第三方登录
	static void LoginThird(int type);

	//登录云信
	static void LoginYX(const char* name, const char* password, int type);

	//打电话
	static void CallPhone(const char *code);

	static bool isLoactionOpen();

	//static void setLoactionGPS();

	static void getLoactionInfo(double & longLoc, double &latloc);

	static void starteVoice(const char* user1, const char* user2, const char* user3, int bRecord);

	static string GetAppName();

	static const char * removeEmoji(const char* str);
};

class MsgBoxListern
{
public:
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  本地系统通知按钮回调事件
    virtual void OnMessageBoxNotify(int nNotifyID, int nIndex) = 0;

	virtual void OnMessageBoxNotify2(int nNotifyId, int nIndex, double nLong, double nLat) = 0;
        
	//
	virtual void OnRechargeResultNotify(int nNotifyID, int nIndex, const char * msg) = 0;
};

class MsgBoxInvoke 
{
public:
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  本地系统通知（游戏时提醒用户）lspzBtns : 按钮文字字符串（按分割(|)顺序创建按钮） e.g. 确定|取消 e.g. 取消|更新 为NULL只创建确定按钮
    static void SysMessageBox(const char* lpszTitle, const char* lpszMsg, MsgBoxListern *lpListern = NULL, const char* lspzBtns = NULL, int nNotifyID = 0);

    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  本地系统通知回调监听(唯一ID:nNotifyID 匹配监听:lpListern)
    static void AttachListener(MsgBoxListern *lpListern, int nNotifyID);
    
    ////////////////////////////////////////////////////////////////////////////
	// 功能描述:  本地系统通知按钮回调释放(释放所有与监听:lpListern关联的)
	static void ReleaseListener(MsgBoxListern *lpListern);
	static bool SendtoObserverByNotifyID(int nNotifyID, int nIndex);
	static bool SendtoObserverByNotifyID2(int nNotifyID, int nIndex,double d1, double d2);
    static bool SendtoObserverByNotifyID(int nNotifyID, int nIndex,const char* msg);
};

class WebInvoke
{
public:
	//调用浏览器
	static void requestOpenUrl(const char* url);
    // 游戏内起视图显示 hor -1 0 1 left center right //ver -1 0 1 top center bottom //hormargin上下偏移 vermargin左右偏移
    static void requestWebPage(const char* url, int height, int width, int hor=0, int ver=-1, int vermargin=0, int hormargin=0);
    // 本地html  filename文件相对主目录的路径和名字 filetype文件类型（html。。）
    static void requestLocalWebPage( const char* filename, const char* filetype, const char* senddata, int width, int height, int hor=0, int ver=-1, int vermargin=0, int hormargin=0, bool bCanScale=false);
    static void cancelWebPage();
    static void refresh();
};

#endif
