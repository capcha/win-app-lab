// win-app-lab.cpp : Определяет точку входа для приложения.
//
// // При включении SDKDDKVer.h будет задана самая новая из доступных платформ Windows.
// Если вы планируете сборку приложения для предыдущей версии платформы Windows, включите WinSDKVer.h и
// задайте желаемую платформу в макросе _WIN32_WINNT, прежде чем включать SDKDDKVer.h.
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>
// Файлы заголовков среды выполнения C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <string>

#define BUF_SIZE 32
#define MAX_LOADSTRING 100
TCHAR  currentYear[BUF_SIZE];

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle0[] = _T("УРВС ВАРИАНТ 18 ФАДЕЙКИН");

// Отправить объявления функций, включенных в этот модуль кода:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR     lpCmdLine,
   _In_ int       nCmdShow
)
{
   WNDCLASSEX wcex;

   wcex.cbSize = sizeof(WNDCLASSEX);
   wcex.style = CS_HREDRAW | CS_VREDRAW;
   wcex.lpfnWndProc = WndProc;
   wcex.cbClsExtra = 0;
   wcex.cbWndExtra = 0;
   wcex.hInstance = hInstance;
   wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
   wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
   wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
   wcex.lpszMenuName = NULL;
   wcex.lpszClassName = szWindowClass;
   wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

   if (!RegisterClassEx(&wcex))
   {
      return 1;
   }

   hInst = hInstance;

   HWND hWnd = CreateWindow(
      szWindowClass,
      szTitle0,
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
      CW_USEDEFAULT, CW_USEDEFAULT,
      500, 100,
      HWND_DESKTOP,
      NULL,
      hInstance,
      NULL
   );

   if (!hWnd)
   {
      return 1;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   // Main message loop:
   MSG msg;
   while (GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

   return (int)msg.wParam;
}

DWORD WINAPI ThreadFunc(void*)
{

   // Подключение библиотеки 
   typedef int(*ImportFunction)(char*);

   ImportFunction DLLInfo;

   // Загрузка библиотеки
   HINSTANCE hinstLib = LoadLibrary(TEXT("info.dll"));

   // Загрузка Infrormation
   DLLInfo = (ImportFunction)GetProcAddress(hinstLib, "Information");

   char String[BUF_SIZE];

   // Вызов функции из динамической библиотеки
   int res = DLLInfo(String);

   // Освобождение дескриптора
   FreeLibrary(hinstLib);

   for (int i = 0; i < 4; ++i)
   {
      currentYear[i] = (TCHAR)String[i];
   }

   return 1;

}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message)
   {
   case WM_PAINT:
   {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);
      std::wstring result = L"Текущий год : ";
      // Вывод результата в окно
      TextOutW(hdc, 30, 30, result.c_str(), result.size());
      TextOut(hdc, 120 + result.size(), 30, currentYear, 4);
      EndPaint(hWnd, &ps);
   }
   break;
   case WM_DESTROY:
      PostQuitMessage(0);
      break;
   case WM_CREATE:
      HANDLE hThread;
      DWORD IDThread;
      hThread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, &IDThread);
      WaitForSingleObject(hThread, INFINITE);

      CloseHandle(hThread);
      break;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}