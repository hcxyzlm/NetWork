#ifndef _NET_BASE_H_
#define _NET_BASE_H_

#include "MsgHead.h"
#include <google/protobuf/message_lite.h>
using namespace google::protobuf;


struct HttpDetail
{
	char*	head;
	int		headLen;
	char*	message;
	int		messageLen;
};

class ServerKey
{
private:
	int m_serverid;
	int m_gameid;
public:
	ServerKey(int id, int gameid)
	{
		m_serverid = id;
		m_gameid = gameid;
	}
	int getServerId() const
	{
		return m_serverid;
	}
	int getGameId() const
	{
		return m_gameid;
	}

	bool operator <(const ServerKey& other) const
	{
		if (this->getGameId()<other.getGameId())
		{
			return true;
		}
		else if (this->getGameId() == other.getGameId())
		{
			return (this->getServerId()<other.getServerId());
		}
		return false;
	}

	bool operator == (const ServerKey& other) const
	{
		return (getGameId()==other.getGameId()) && (getServerId()==other.getServerId());
	}
};

class ISvrNetEvent
{
public:
	//协议消息
	virtual void onGameserverMsg(MsgHead msgHead, MessageLite *pMessage) = 0;
	//协议解析失败
	virtual void onDecodeError(MsgHead msgHead) = 0;   
	//网络链接消息,true成功，false失败
	virtual void onNetConnect(bool connectRet) = 0;
	//网络异常,socket断开
	virtual void onNetClose() = 0;
	//错误协议
	virtual void onError(MsgHead msgHead, const char *buffer, int len) = 0;
	//心跳请求
	virtual void onHeartReq() = 0;
};

#endif