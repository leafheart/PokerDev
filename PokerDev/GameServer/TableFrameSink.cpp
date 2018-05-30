

#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
const WORD			CTableFrameSink::m_wPlayerCount=GAME_PLAYER;			//��Ϸ����
const enStartMode	CTableFrameSink::m_GameStartMode=enStartMode_AllReady;	//��ʼģʽ

//////////////////////////////////////////////////////////////////////////

void TraceMessage(LPCTSTR pszMessage);

//���캯��
CTableFrameSink::CTableFrameSink()
{
	//�������
	m_pITableFrame=NULL;
	m_pGameServiceOption=NULL;

	return;
}

//��������
CTableFrameSink::~CTableFrameSink(void)
{
}

//�ӿڲ�ѯ
void * __cdecl CTableFrameSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITableFrameSink,Guid,dwQueryVer);
	QUERYINTERFACE(ITableUserAction,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameSink,Guid,dwQueryVer);

	return NULL;
}

IServerUserItem *  CTableFrameSink::GetServerUserItem(WORD wChairID)
{
	if (m_pITableFrame) return m_pITableFrame->GetServerUserItem(wChairID);

	return NULL;
}

bool CTableFrameSink::SendTableData(WORD wChairID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	if (m_pITableFrame) return m_pITableFrame->SendTableData(wChairID, wSubCmdID, pData, wDataSize);

	return false;
}

bool CTableFrameSink::SendTableDataToAll(WORD wSubCmdID, void * pData, WORD wDataSize)
{
	if (m_pITableFrame) return m_pITableFrame->SendTableData(INVALID_CHAIR, wSubCmdID, pData, wDataSize);

	return false;
}

void CTableFrameSink::SendTableDataToOther(WORD wChairID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		if(i==wChairID)continue;

		IServerUserItem * pIServerUserItem = m_pITableFrame->GetServerUserItem(i);
		if (pIServerUserItem != NULL)
		{
			m_pITableFrame->SendUserData(pIServerUserItem, wSubCmdID, pData, wDataSize);
		}
	}
}

//��ʼ��
bool __cdecl CTableFrameSink::InitTableFrameSink(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	ASSERT(pIUnknownEx!=NULL);
	m_pITableFrame=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrame);
	if (m_pITableFrame==NULL) return false;

	//��ȡ����
	m_pGameServiceOption=m_pITableFrame->GetGameServiceOption();
	ASSERT(m_pGameServiceOption!=NULL);
	
	//������¼�ļ�
	CreateGameRecordFile(true);

	return true;
}

//��λ����
void __cdecl CTableFrameSink::RepositTableFrameSink()
{
	
	return;
}

//��ʼģʽ
enStartMode __cdecl CTableFrameSink::GetGameStartMode()
{
	return m_GameStartMode;
}

//��Ϸ״̬
bool __cdecl CTableFrameSink::IsUserPlaying(WORD wChairID)
{
	ASSERT(wChairID<m_wPlayerCount);
	return (m_cbPlayStatus[wChairID]==TRUE)?true:false;
}

//�û����� 
bool __cdecl CTableFrameSink::OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	return true;
}

//�û�����
bool __cdecl CTableFrameSink::OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{	
	if(bLookonUser || m_wDUser==INVALID_CHAIR)return true;
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		if(i==wChairID)continue;
		if (m_pITableFrame->GetServerUserItem(i)!=NULL)
		{
			break;
		}
	}


	return true;
}

//��Ϸ��ʼ
bool __cdecl CTableFrameSink::OnEventGameStart()
{
	//����״̬
	m_pITableFrame->SetGameStatus(GS_MJ_PLAY);

	//��Ϸ����
	WORD wUserCount=0;
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		//��ȡ�û�
		IServerUserItem * pIServerUserItem=m_pITableFrame->GetServerUserItem(i);

		//��Ч�û�
		if (pIServerUserItem==NULL) continue;

		//��ȡ����
		const tagUserScore * pUserScore=pIServerUserItem->GetUserScore();
		ASSERT(pUserScore->lScore>=m_pGameServiceOption->lCellScore);

		//����״̬
		m_cbPlayStatus[i]=TRUE;
		wUserCount++;
	}

//	CMD_S_GameStart_CB GameStart;
//	m_pITableFrame->SendTableData(0,SUB_S_GAME_START,cbBuffer,bos.length());

//	m_GameLogic.OnStartGame(GameStart);

	m_pITableFrame->SetGameTimer(GAME_TIMER, 1000, -1, 0);

	OnStartGame();
/*
	//��������
	char cbBuffer[SOCKET_PACKET];
	memset(cbBuffer, 0, SOCKET_PACKET);
	bostream bos;
	bos.attach(cbBuffer, SOCKET_PACKET);
	bos << GameStart;

	m_pITableFrame->SendTableData(0,SUB_S_GAME_START,cbBuffer,bos.length());
*/
	return true;
}

//��Ϸ����
bool __cdecl CTableFrameSink::OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	switch (cbReason)
	{
	case GER_NORMAL:		//�������
		{
			return true;
		}
		break;
	case GER_USER_LEFT:
		{
			//Ч�����
			ASSERT(pIServerUserItem!=NULL);
			ASSERT(wChairID<m_wPlayerCount);

			//ǿ�˴���
//			OnUserGiveUp(wChairID);
			return true;
		}
		break;
	case GER_DISMISS:
		{

		}
		break;
	}

	return false;
}

//���ͳ���
bool __cdecl CTableFrameSink::SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret)
{
	switch (cbGameStatus)
	{
	case GS_FREE:		//����״̬
		{
			//��������
			nsRouAiRou::CMD_S_StatusFree StatusFree;
			ZeroMemory(&StatusFree,sizeof(StatusFree));

			//��Ϸ����
			StatusFree.cbStatus=cbGameStatus;
			StatusFree.lCellMinScore=m_pGameServiceOption->lCellScore;
			StatusFree.lCellMaxScore=m_pGameServiceOption->lRestrictScore;

			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));	
		}
	//case GS_PLAYING:	//��Ϸ״̬
	case GS_MJ_PLAY:	//��Ϸ״̬
		{
			/* 
			����������ȫ�棬��ʱ����

			//��������
			CMD_S_StatusPlay StatusPlay;
			ZeroMemory(&StatusPlay,sizeof(StatusPlay));

			StatusPlay.cbStatus=cbGameStatus;
			StatusPlay.lCellMinScore=m_pGameServiceOption->lCellScore;
			StatusPlay.lCellMaxScore=m_pGameServiceOption->lRestrictScore;
			
			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));
			*/

			WORD chairID = wChiarID;
			BOOL isReLink = TRUE;//���������ʱ��д���������ڿ��ǿ��Ƶ������
			
			unsigned char * buff = new unsigned char[sizeof(BOOL)+sizeof(WORD)];
			memcpy(buff,0,sizeof(BOOL)+sizeof(WORD));
			
			bostream bos;
			bos.attach((char*)buff, sizeof(BOOL)+sizeof(WORD));
			bos << chairID;
			bos << isReLink;

			OnGameAction(SUB_S_RELINK,buff,bos.length(),pIServerUserItem);//��Ϊ��Ϸ�߼���Ϣ������sendGameStatusȥ����
			delete []buff;
			return true;

		}

	default :
		return true;

	}
	//Ч����
	ASSERT(FALSE);
	return false;
}

//��ʱ���¼�
bool __cdecl CTableFrameSink::OnTimerMessage(WORD wTimerID, WPARAM wBindParam)
{
	return false;
}

//��Ϸ��Ϣ����
bool __cdecl CTableFrameSink::OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	switch(wSubCmdID)
	{
	case SUB_CS_OUT:		//����
		{
			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_PLAY) return true;

			//״̬�ж�
			ASSERT(m_cbPlayStatus[pUserData->wChairID]==TRUE);
			if (m_cbPlayStatus[pUserData->wChairID]==FALSE) return false;

			//Ч������
			//ASSERT(wDataSize==sizeof(nsRouAiRou::CMD_OutCard_CB));
			//if (wDataSize!=sizeof(nsRouAiRou::CMD_OutCard_CB)) return false;

/*			//��������
			CMD_OutCard_CB outCards;
			bistream bis;
			bis.attach((char*)pDataBuffer, wDataSize);
			bis >> outCards;
*/
			//��Ϣ����
			OnGameAction(SUB_CS_OUT, pDataBuffer, wDataSize,pIServerUserItem);
/*
			//�ɹ��󷢸��������
			//��������
			char cbBuffer[SOCKET_PACKET];
			memset(cbBuffer, 0, SOCKET_PACKET);
			bostream bos;
			bos.attach(cbBuffer, SOCKET_PACKET);
			bos << outCards;

			m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_CS_OUT, cbBuffer, bos.length());
			m_pITableFrame->SendLookonData(INVALID_CHAIR, SUB_CS_OUT, cbBuffer, bos.length());

			//for test
			//������Ϸ
			m_pITableFrame->ConcludeGame();
*/

			//��Ϣ����
			return true;
		}
	case SUB_CS_ROAR:	//�û�����
		{
			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_PLAY) return true;
			//״̬�ж�
			ASSERT(m_cbPlayStatus[pUserData->wChairID]==TRUE);
			if (m_cbPlayStatus[pUserData->wChairID]==FALSE) return false;

			//��Ϣ����
			OnGameAction(SUB_CS_ROAR, pDataBuffer, wDataSize,pIServerUserItem);

			return true;
		}
	case SUB_S_TUOGUAN:
		{
			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_PLAY) return true;
			
			//״̬�ж�
			ASSERT(m_cbPlayStatus[pUserData->wChairID]==TRUE);
			if (m_cbPlayStatus[pUserData->wChairID]==FALSE) return false;

			//��Ϣ����
			OnGameAction(SUB_S_TUOGUAN, pDataBuffer, wDataSize,pIServerUserItem);
			return true;
		}
	case SUB_C_GOON_NEXT_GAME:
		{
			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_PLAY) return true;

			//״̬�ж�
			ASSERT(m_cbPlayStatus[pUserData->wChairID]==TRUE);
			if (m_cbPlayStatus[pUserData->wChairID]==FALSE) return false;

			//��Ϣ����
			OnGameAction(SUB_C_GOON_NEXT_GAME, pDataBuffer, wDataSize, pIServerUserItem);
			return true;
		}
	default:
		return true;
	}
	return false;
}

//�����Ϣ����
bool __cdecl CTableFrameSink::OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	return false;
}

void CTableFrameSink::stovs( const string& s, const string& sp, vector<string>& sa )
{
	sa.clear();
	if (sp.length() == 0) return;
	if (s.length() == 0)
	{
		/*sa.push_back("");*/
		return;
	}

	size_t szsp = sp.length();
	string tmps = s + sp;
	size_t start = 0;
	while( true )
	{
		if( tmps.length() < sp.length() )
		{
			break;
		}
		if( tmps.length() < start + sp.length() )
		{
			break;
		}

		size_t idx = tmps.find_first_of( sp[0], start );
		string sub = tmps.substr( idx, szsp );
		if( sub == sp )
		{
			string item = tmps.substr( 0, idx );
			sa.push_back( item );
			start = 0;
			tmps = tmps.substr( idx + szsp, tmps.length() - ( idx + szsp ) );
		}
		else
		{
			start += idx;
		}
	}
}


//�����Ϣ
void TraceMessage(LPCTSTR pszMessage)
{
	if(0 == lstrlen(pszMessage))
	{
		return;
	}

	CFile File;
	if ((File.Open(TEXT("TraceData_Dagong4_haoyou.txt"),CFile::modeWrite)==FALSE)&&
		(File.Open(TEXT("TraceData_Dagong4_haoyou.txt"),CFile::modeWrite|CFile::modeCreate)==FALSE))
	{
		ASSERT(FALSE);
		return;
	}

	SYSTEMTIME sys; 
	GetLocalTime( &sys ); 
	char buf[128];
	memset(buf, 0, 128);
	sprintf(buf, "%4d/%02d/%02d %02d:%02d:%02d.%03d ",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds);

	File.SeekToEnd();
	File.Write(buf,lstrlen(buf));
	File.Write(pszMessage,lstrlen(pszMessage));
	File.Write(TEXT("\r\n"),lstrlen(TEXT("\r\n")));

	File.Flush();
	File.Close();

	return;
}


//�����Ϣ
void TraceMessageDetails(LPCTSTR pszMessage, LPCTSTR pszFile)
{
	if(0 == lstrlen(pszMessage) || 0 == lstrlen(pszFile) )
	{
		return;
	}

	SYSTEMTIME sys; 
	GetLocalTime( &sys ); 
	char buf[128];
	memset(buf, 0, 128);
	sprintf(buf, "%4d/%02d/%02d %02d:%02d:%02d.%03d ",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds);

	//�ļ���
	char fnBuf[128];
	memset(fnBuf, 0, 128);
	sprintf(fnBuf, "Log//%4d%02d%02d_%s",sys.wYear,sys.wMonth,sys.wDay, pszFile);
	
	CFile File;
	if ((File.Open(fnBuf,CFile::modeWrite)==FALSE)&&
		(File.Open(fnBuf,CFile::modeWrite|CFile::modeCreate)==FALSE))
	{
		ASSERT(FALSE);
		return;
	}

	File.SeekToEnd();
	File.Write(buf,lstrlen(buf));
	File.Write(pszMessage,lstrlen(pszMessage));
	File.Write(TEXT("\r\n"),lstrlen(TEXT("\r\n")));

	File.Flush();
	File.Close();

	return;
}
//////////////////////////////////////////////////////////////////////////
