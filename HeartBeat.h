#pragma once

#include "utils/MyMutex.h"
#include "network/NetBase.h"

const char ALIVE_TIME_OUT	=	5;    //发送心跳5次没有回应，认定超时
const int  ALIVE_TIME_SPACE	=	50;  //每循环多少次发送一次心跳

class HeartBeat
{
private:
	char m_timeOutCount;
	int  m_sendHearBeatCount;
	MyMutex m_mutex;
	ISvrNetEvent	*m_pNetAdapter;
	bool m_bIsVisible;

public:
	HeartBeat(ISvrNetEvent *pAdapter);
	~HeartBeat();

	void setVisible(bool var);
	void resetTimeOutCount();
	void registAdapter(ISvrNetEvent *adapter);
	bool onRecvAlive();    //收到server发回的心跳协议，进行处理
	void onLoop();        //主线程循环一次处理
};