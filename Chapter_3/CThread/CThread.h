#ifndef __CTHREAD_H__
#define __CTHREAD_H__

#include <windows.h>

#define STATE_RUNNING		0x0001
#define STATE_READY			0x0002
#define STATE_BLOCKED		0x0004
#define STATE_ALIVE			0x0008
#define STATE_ASYNC			0x0010
#define STATE_SYNC			0x0020
#define STATE_CONTINUE		0x0040

class CLock
{
public:
	CLock();
	~CLock();

private:
	HANDLE _hMutex;
};

class CThread
{
public:
	CThread() : _hThread(0), _dwThreadId(0), _dwState(0), _lpUserData(0), _lpParameter(0) {}
	HANDLE Create(LPVOID lpParamter, DWORD dwInitialState = STATE_ASYNC, DWORD dwCreationFlag = 0);
	void Join(DWORD dwWaitInterval = INFINITE);
	DWORD Suspend();
	DWORD Resume();
	void SetUserData(void* lpUserData);
	void* GetUserData() const;
	DWORD GetId() const;
	HANDLE GetHandle() const;
	DWORD GetAsyncState() const;
	DWORD GetState() const;
	void SetState(DWORD dwNewState);
	BOOL Alert();

protected:
	virtual void Run(LPVOID lpParameter = 0) = 0;
	LPVOID _lpParameter;

private:
	static DWORD WINAPI StartAddress(LPVOID lpParameter);

	HANDLE _hThread;
	DWORD _dwThreadId;
	DWORD _dwState;
	void* _lpUserData;
	HANDLE _hEvent;
};

inline DWORD CThread::GetId() const
{
	return _dwThreadId;
}

inline HANDLE CThread::GetHandle() const
{
	return _hThread;
}

#endif
