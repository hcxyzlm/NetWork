#ifndef _CTHREAD_H__
#define _CTHREAD_H__

#include <pthread.h>

#ifdef _WIN32
#include <process.h>
#include <winsock2.h>
#include <windows.h>
#define STDPREFIX _stdcall;
#else
#include <unistd.h>
#define STDPREFIX
#endif

typedef void * threadparam_t;

class CThread
{
public:
	CThread(const CThread &){}
	CThread(bool release = true);
	CThread& operator= (const CThread&){return *this;}
	virtual ~CThread();

	void onStart();
	virtual void Run() = 0;

#ifdef _WIN32
	static unsigned _stdcall StartThread(threadparam_t);
	HANDLE GetThread(){return m_thread;}
	unsigned GetThreadId(){return m_dwThreadId;}
#else
	static void * StartThread(threadparam_t);
	pthread_t GetThread(){return m_thread;}
#endif

	bool IsRunning();
	void SetRunning(bool x);
	bool IsRelease();
	void SetRelease(bool x);
	bool DeleteOnExit();
	void SetDeleteOnExit(bool x = true);
	bool IsDestructor();

protected:
#ifdef _WIN32
	HANDLE m_thread;
	unsigned m_dwThreadId;
#else
	pthread_t m_thread;
#endif

private:
	bool m_running;
	bool m_release;
	bool m_b_delete_on_exit;
	bool m_b_destructor;
};

#endif/*_THREAD_H__*/
