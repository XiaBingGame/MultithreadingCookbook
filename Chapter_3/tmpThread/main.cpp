#include <windows.h>
#include <iostream>

using namespace std;

DWORD WINAPI StartAddress(LPVOID lpParameter)
{
	cout << "Hello. I am very simple thread."
		<< endl
		<< "I am used to demonstarte thread creation."
		<< endl;
	return 0;
}


int main(int argc, TCHAR* argv[])
{
	HANDLE hThread = CreateThread(NULL, 0, StartAddress, NULL, 0, NULL);

	STARTUPINFO startupInfo = { 0 };
	PROCESS_INFORMATION processInformation = { 0 };

	BOOL bSuccess = CreateProcess(TEXT("tmpProcess.exe"), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);
	
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	system("pause");
	return 0;
}