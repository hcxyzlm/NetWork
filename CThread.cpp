#include "utils/CThread.h"


CThread::CThread(bool release /* = true */)
	:m_thread(0)
	,m_running(true)
	,m_release(false)
	,m_b_delete_on_exit(false)
	,m_b_destructor(false)
{
	m_release = release;
}

CThread::~CThread()
{
	m_b_destructor = true;
	if (m_running)
	{
		SetRelease(true);
		SetRunning(false);
#ifdef _WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}
#ifdef _WIN32
	//if (m_thread)
	//	::CloseHandle(m_thread);
#endif
}

void CThread::onStart()
{
#ifdef _WIN32
	m_thread = (HANDLE)_beginthreadex(NULL, 0, &StartThread, this, 0, &m_dwThreadId);
#else
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	if (pthread_create(&m_thread,&attr, StartThread,this) == -1)
	{
		//perror("Thread: create failed");
		SetRunning(false);
	}
#endif
}

#ifdef _WIN32
unsigned _stdcall CThread::StartThread(threadparam_t id)
#else
void * CThread::StartThread(threadparam_t id)
#endif
{

	CThread *p = (CThread *)id;

	while (p -> m_running && !p -> m_release)
	{
#ifdef _WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}
	if (p -> m_running)
	{
		p -> Run();
	}
	p -> SetRunning(false); // if return
	if (p -> DeleteOnExit() && !p -> IsDestructor())
	{
		delete p;
	}
#ifdef _WIN32
	_endthreadex(0);
	return (unsigned)NULL;
#else
	return (void *)NULL;
#endif
	
}

bool CThread::IsRunning()
{
	return m_running; 
}

void CThread::SetRunning(bool x)
{
	m_running = x;
}

bool CThread::IsRelease()
{
	return m_release;
}

void CThread::SetRelease(bool x)
{
	m_release = x;
}

bool CThread::DeleteOnExit()
{
	return m_b_delete_on_exit;
}

void CThread::SetDeleteOnExit(bool x)
{
	m_b_delete_on_exit = x;
}


bool CThread::IsDestructor()
{
	return m_b_destructor;
}
