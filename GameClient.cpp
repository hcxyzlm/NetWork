#include "network/GameClient.h"
#include "ODSocket.h"
#include "utils/Util.h"
#include <google/protobuf/io/gzip_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#define BUF_SIZE 65535

///////////////////////////////////////////////////////////
GameClient::GameClient(string ip, int port, int timeOut, ISvrNetEvent *pAdapter)
{
	m_sockfd = -1;
	m_bReceive = false;
	m_pAdapter = pAdapter;
	m_socketState = SOCKET_CLOSE;
	m_pSocket = new ODSocket();

	m_ip = ip;
	m_port = port;
	m_timeOut = timeOut;
	m_bufRecv_len = 0;
	m_bufSend_len = 0;
	memset(m_bufferRecv, 0, MAX_RECV_BUF_SIZE);
	memset(m_bufferSend, 0, MAX_SEND_BUF_SIZE);
}

GameClient::~GameClient()
{
    m_pAdapter = NULL;
	m_bReceive = false;
    m_bufRecv_len = 0;
	if (m_pSocket)
	{
        m_pSocket->Close();
		delete m_pSocket;
	}
}

void GameClient::onConnect()
{		
	onStart();
}

void GameClient::relocation(string ip, int port, int timeOut, ISvrNetEvent *pAdapter)
{
    m_mutex.Lock();
	m_ip = ip;
	m_port = port;
	m_timeOut = timeOut;
	m_pAdapter = pAdapter;
    m_mutex.Unlock();
}

int GameClient::sendMsg(const char *sendBuff, int bufLen)
{
    m_mutex.Lock();
	if (m_pSocket)
	{
		if (m_bufSend_len+bufLen > MAX_SEND_BUF_SIZE)
		{
           m_mutex.Unlock();
			return -1;
		}
		memcpy(&m_bufferSend[m_bufSend_len], sendBuff, bufLen);  //协议数据放到缓冲区
		m_bufSend_len += bufLen;
        m_mutex.Unlock();
		return bufLen;
	}
    m_mutex.Unlock();
	return -1;
}

bool GameClient::recvMsg()
{
    m_mutex.Lock();

	if (m_pSocket && m_bReceive)
	{
		int  recLenth=0;
		recLenth = m_pSocket->Recv(&m_bufferRecv[m_bufRecv_len], MAX_RECV_BUF_SIZE-m_bufRecv_len);  //非阻塞模式，返回-1，不做处理
		if (recLenth < 0 )  //服务器关闭
		{
			m_mutex.Unlock();
			close();
			m_mutex.Lock();
            m_socketState = SOCKET_CLOSE;
            m_mutex.Unlock();
			return false;
		}
		if (recLenth > 0)  //接收数据成功
		{

			m_bufRecv_len += recLenth;
            m_mutex.Unlock();
			return true;
		}
	}
    m_mutex.Unlock();
	return false;
}

void GameClient::Run()
{
    m_mutex.Lock();
	m_bufRecv_len=0;
	m_bufSend_len=0;
	memset(m_bufferRecv, 0, MAX_RECV_BUF_SIZE);
	memset(m_bufferSend, 0, MAX_SEND_BUF_SIZE);
	if (m_pSocket)
	{
		m_pSocket->Close();
	}
	m_pSocket->Init();
	m_pSocket->Create(AF_INET,SOCK_STREAM);

	if (m_pSocket->Connect(m_ip.c_str(), m_port, m_timeOut))
	{
		m_bReceive = true;    //链接成功，可以接收数据
		m_socketState = SOCKET_CONNECTED;
	}
	else
	{
        m_mutex.Unlock();
		if (m_pAdapter)
		{
			m_pAdapter->onNetConnect(false);
		}
		return;
	}
    m_mutex.Unlock();
	if (m_pAdapter)
	{
		m_pAdapter->onNetConnect(true);
	}
}


int GameClient::close(bool isUp)
{
    m_mutex.Lock();
	//与server断开链接
	if (!m_bReceive)
	{
        m_mutex.Unlock();
		return 0;
	}
	m_bReceive = false;
	if (!isUp && m_pAdapter)
	{
        m_mutex.Unlock();
		m_pAdapter->onNetClose();
	}
    m_mutex.Unlock();
	if (m_pSocket)
	{
		m_pSocket->Close();
	}
	return 0;
}

bool GameClient::parseMessage()
{
    m_mutex.Lock();
	int offset = 0;
	while (offset < m_bufRecv_len)
	{
		//解析协议头
		if (offset + sizeof(MsgHead) > m_bufRecv_len) //溢出
		{
			break;
		}

		MsgHead msgRecv;
		msgRecv.decodeHead(&m_bufferRecv[offset]);
		offset += sizeof(msgRecv);

		if (offset + msgRecv.msgLen - MSG_HEAD_LEN > m_bufRecv_len)   //溢出,获取协议body
        {
            m_mutex.Unlock();
            offset -= sizeof(msgRecv);
			break;
        }
        m_mutex.Unlock();
		if (msgRecv.msgType == MSG_ERROR)   //错误包
		{
			printf("message error cmdid:%d", msgRecv.cmdID);
			if (m_pAdapter)
			{
				m_pAdapter->onError(msgRecv, &m_bufferRecv[offset], msgRecv.msgLen-MSG_HEAD_LEN);
			}
		}
		else
		{
			MessageLite *pMessage = m_pMessages[msgRecv.cmdID];
			if (pMessage)   //已注册此协议
			{
				if ((msgRecv.option>>2)&1)
				{

					char	m_newbufferRecv[MAX_RECV_BUF_SIZE];   //协议接收缓冲区
					memset(m_newbufferRecv, 0, MAX_RECV_BUF_SIZE);

					memcpy(m_newbufferRecv, &m_bufferRecv[offset], msgRecv.msgLen-MSG_HEAD_LEN);

					io::ArrayInputStream input(m_newbufferRecv, msgRecv.msgLen-MSG_HEAD_LEN);
					io::GzipInputStream stream(&input,io::GzipInputStream::GZIP,-1);

					bool ret = pMessage->ParseFromZeroCopyStream(&stream);
					if (ret)  //解析成功
					{
						if (m_pAdapter)
							m_pAdapter->onGameserverMsg(msgRecv, pMessage);
					}
					else    //解析失败
					{
						if (m_pAdapter)
							m_pAdapter->onDecodeError(msgRecv);
					}

				}
				else
				{
					bool ret = pMessage->ParseFromArray(&m_bufferRecv[offset], msgRecv.msgLen-MSG_HEAD_LEN);

					if (ret)  //解析成功
					{
						if (m_pAdapter)
							m_pAdapter->onGameserverMsg(msgRecv, pMessage);
					}
					else    //解析失败
					{
						if (m_pAdapter)
							m_pAdapter->onDecodeError(msgRecv);
					}
				}
			}		
			else
			{
				if (m_pAdapter)
				{
					printf("No registration protocol ID");
				}
			}
		}			

		m_mutex.Lock();
		offset += msgRecv.msgLen-MSG_HEAD_LEN;
	}
	
	if (offset < 0)
	{
		offset = 0;
	}
	//缓冲区移位
	memcpy(m_bufferRecv, &m_bufferRecv[offset], m_bufRecv_len-offset);
	m_bufRecv_len -= offset;
	memset(&m_bufferRecv[m_bufRecv_len], 0, MAX_RECV_BUF_SIZE-m_bufRecv_len);
    m_mutex.Unlock();
	return true;
}

void GameClient::registerMessage(int cmdId, MessageLite *pMessage)
{
	m_pMessages[cmdId] = pMessage;
}

int GameClient::sendMessage()    //将缓冲区协议发送出去
{
    m_mutex.Lock();
	if (m_pSocket && m_socketState==SOCKET_CONNECTED)
	{
		int sendSize = m_pSocket->Send(m_bufferSend, m_bufSend_len);
		if (sendSize < 0)
		{
            m_mutex.Unlock();
			return -1;
		}
		memset(m_bufferSend, 0, MAX_SEND_BUF_SIZE);
		m_bufSend_len = 0;
        m_mutex.Unlock();
		return sendSize;
	}
    m_mutex.Unlock();
	return -1;
}

void GameClient::recvMessage()    //接收协议，并解析协议
{
	recvMsg();   //接收数据
	parseMessage();  //解析协议
}