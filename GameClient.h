#ifndef _GAME_CLIENT_H
#define _GAME_CLIENT_H

#include "utils/CThread.h"
#include "ODSocket.h"
#include "utils/MyMutex.h"
#include "network/NetBase.h"
#include "MsgHead.h"

#include <iostream>
#include <string>

#ifdef _WIN32
#include <hash_map>
using namespace stdext;
#else
#include <ext/hash_map>
using namespace __gnu_cxx;
#endif

using namespace std;


enum SocketState
{
	SOCKET_CLOSE = 0,     //未链接状态
	SOCKET_CONNECTED,     //已经链接状态
	SOCKET_CONNECTING     //正在链接状态         
};

const int MAX_RECV_BUF_SIZE  = 61440;  //接收协议缓冲区60k
const int MAX_SEND_BUF_SIZE = 61440; //协议发送缓冲区60k

class GameClient : public CThread
{
public:
	GameClient(string ip, int port, int timeOut, ISvrNetEvent *pAdapter);
	~GameClient();
private:
	string	m_ip;
	int		m_port;
	int		m_timeOut;
	bool	m_bReceive;
	char	m_bufferRecv[MAX_RECV_BUF_SIZE];   //协议接收缓冲区
	char    m_bufferSend[MAX_SEND_BUF_SIZE];   //协议发送缓冲区
	int		m_bufRecv_len;       //接收缓冲区已有协议长度  
	int		m_bufSend_len;      //发送缓冲区已有协议长度

	int		m_sockfd;   //用于记录socket连接成功返回值

	ISvrNetEvent	*m_pAdapter;
	SocketState	m_socketState;  //网络链接状态
	ODSocket *m_pSocket;
    MyMutex m_mutex;
	hash_map<int, MessageLite*> m_pMessages;
private:
	bool	parseMessage();
	bool	recvMsg();

	void	Run();
public:
	void	relocation(string ip, int port, int timeOut, ISvrNetEvent *pAdapter);
    void    setGameServer(ISvrNetEvent *pAdapter){m_pAdapter = pAdapter;}
	int     sendMsg(const char *sendBuff, int bufLen);  //把协议放到发送缓冲区
	void	onConnect();   //socket链接
	int     close(bool isUp = false);  //主动断开与server的链接
	void	registerMessage(int cmdId, MessageLite *pMessage);

	int		sendMessage();    //将缓冲区协议发送出去
	void	recvMessage();    //接收协议，并解析协议
};

#endif