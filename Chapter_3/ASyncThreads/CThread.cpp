#include "CThread.h"

CLock::CLock()
{
	_hMutex = CreateMutex(NULL, FALSE, TEXT("_tmp_mutex_lock_"));
	WaitForSingleObject(_hMutex, INFINITE);
}

CLock::~CLock()
{
	ReleaseMutex(_hMutex);
	CloseHandle(_hMutex);
}

HANDLE CThread::Create(LPVOID lpParamter, DWORD dwInitialState, DWORD dwCreationFlag)
{
	_dwState |= dwInitialState;
	_lpParameter = lpParamter;

	if (_dwState & STATE_ALIVE)
		return _hThread;

	_hThread = CreateThread(NULL, 0, StartAddress, this, dwCreationFlag, &_dwThreadId);
	_dwState |= STATE_ALIVE;

	if (_dwState & STATE_CONTINUE)
	{
		_hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("__tmp_event__"));
	}

	return _hThread;
}

void CThread::Join(DWORD dwWaitInterval)
{
	if (_dwState & STATE_BLOCKED)
		return;

	if (_dwState & STATE_READY)
		return;

	_dwState |= STATE_READY;
	WaitForSingleObject(_hThread, dwWaitInterval);
	_dwState ^= STATE_READY;
}

DWORD CThread::Suspend()
{
	if (_dwState & STATE_BLOCKED)
		return DWORD(-1);

	if (_dwState & STATE_READY)
		return DWORD(-1);

	DWORD dwSuspendCount = SuspendThread(_hThread);
	_dwState |= STATE_BLOCKED;

	return dwSuspendCount;
}

DWORD CThread::Resume()
{
	if (_dwState & STATE_RUNNING)
	{
		return DWORD(-1);
	}

	DWORD dwResumeCount = ResumeThread(_hThread);
	_dwState ^= STATE_BLOCKED;

	return dwResumeCount;
}

void CThread::SetUserData(void* lpUserData)
{
	_lpUserData = lpUserData;
}

void* CThread::GetUserData() const
{
	return _lpUserData;
}

DWORD CThread::GetAsyncState() const
{
	if (_dwState & STATE_ASYNC)
		return STATE_ASYNC;
	return STATE_SYNC;
}

DWORD CThread::GetState() const
{
	return _dwState;
}

void CThread::SetState(DWORD dwNewState)
{
	_dwState = 0;
	_dwState |= dwNewState;
}

BOOL CThread::Alert()
{
	return SetEvent(_hEvent);
}

DWORD WINAPI CThread::StartAddress(LPVOID lpParameter)
{
	CThread* cThread = (CThread*)lpParameter;
	if (cThread->GetAsyncState() == STATE_SYNC)
	{
		if (cThread->_dwState & STATE_CONTINUE)
		{
			DWORD dwWaitStatus = 0;
			while (TRUE)
			{
				cThread->Run();

				dwWaitStatus = WaitForSingleObject(cThread->_hEvent, 10);

				if (dwWaitStatus == WAIT_OBJECT_0)
				{
					break;
				}
			}
			return 0;
		}

		cThread->Run();
		return 0;
	}

	if (cThread->_dwState & STATE_CONTINUE)
	{
		DWORD dwWaitStatus = 0;
		while (TRUE)
		{
			CLock lock;
			{
				cThread->Run();
			}
			

			dwWaitStatus = WaitForSingleObject(cThread->_hEvent, 10);

			if (dwWaitStatus == WAIT_OBJECT_0)
			{
				break;
			}
		}
		return 0;
	}

	//CLock lock;
	{
		cThread->Run();
	}

	return 0;
}