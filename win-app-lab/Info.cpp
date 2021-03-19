#define _CRT_SECURE_NO_WARNINGS
#define UNICODE
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

extern "C" _declspec(dllexport) int Information(char* InfoString) 
{

	SYSTEMTIME st;
	GetSystemTime(&st);

	sprintf(InfoString, "%i", st.wYear);

	return 0;

}