#include "network/HeartBeat.h"
#include "utils/Util.h"


HeartBeat::HeartBeat(ISvrNetEvent *pAdapter)
{
	m_pNetAdapter = pAdapter;
	m_timeOutCount = 0;
	m_sendHearBeatCount = ALIVE_TIME_OUT;
	m_bIsVisible = true;
}

HeartBeat::~HeartBeat()
{
	m_pNetAdapter = NULL;
}

void  HeartBeat::onLoop()
{
	if (m_timeOutCount <= ALIVE_TIME_SPACE && m_bIsVisible)
	{
		m_mutex.Lock();
		m_timeOutCount++;
		m_mutex.Unlock();
	}
	else if (m_timeOutCount >= ALIVE_TIME_SPACE && m_bIsVisible)
	{
		//心跳发送
		if (m_pNetAdapter)
		{
			m_pNetAdapter->onHeartReq();
		}
		m_mutex.Lock();
		m_timeOutCount = 0;
		m_sendHearBeatCount--;
		m_mutex.Unlock();
	}

	//心跳超时，认为断线了
	if (m_sendHearBeatCount <= 0 && m_bIsVisible && m_pNetAdapter)
	{
		m_mutex.Lock();
		m_bIsVisible = false;
		m_mutex.Unlock();
 		m_pNetAdapter->onNetClose();
	}
}

bool HeartBeat::onRecvAlive()
{
	Lock guard(m_mutex);
	//收到心跳协议
	m_sendHearBeatCount = ALIVE_TIME_OUT;
	return true;
}

void HeartBeat::registAdapter(ISvrNetEvent *adapter)
{
	m_mutex.Lock();
	m_pNetAdapter = adapter;
	m_timeOutCount = ALIVE_TIME_SPACE;
	m_sendHearBeatCount = ALIVE_TIME_OUT;
	m_mutex.Unlock();
}

void HeartBeat::resetTimeOutCount()
{
	m_mutex.Lock();
	m_timeOutCount = ALIVE_TIME_SPACE;
	m_sendHearBeatCount = ALIVE_TIME_OUT;
	m_mutex.Unlock();
}

void HeartBeat::setVisible(bool var)
{
	m_mutex.Lock();
	m_bIsVisible = var;
	m_mutex.Unlock();
}