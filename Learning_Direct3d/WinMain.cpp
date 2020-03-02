// ������ ��� ���������� ����� �������� ������ � ���������
// https://docs.microsoft.com/en-us/windows/win32/controls/cookbook-overview
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include "WindowsMessageMap.h"
#include <locale>
#include <codecvt>
#include <string>

// ��������� ��� �������������� string � wstring � �������
// https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t

// �������� ������� ��������� ��������� � ���������������� ���������:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, // ���������� (� �.�. ����� �������������) ���������� ����������
                   HINSTANCE,
                   LPSTR lpCmdLine,
                   // ��������� �� ������ � ����������� ���������� ������ (� ������ ���� ����. �������� �� ���������� ������)
                   int nCmdShow) // ����� ����������� ����
{
	MSG msg{}; // ��������� ������� ����� ��������� �� �������� � ���� ����������
	HWND hwnd{}; // ���������� ���� ������ ���������� ��� ����, ����� ������� ����� �������� � ��� 

	// Initialize window class, and feel it start properties
	WNDCLASSEX wc{
		.cbSize = sizeof(WNDCLASSEX) // ����� ������ ������� ����� ��������������� ��� ���������.
	};
	// ������������� ����� �������������� ����, ������� ����������� ����� �� ���������� ������ ����. ������� �������������� ��� ����� ������.
	wc.cbClsExtra = 0;
	// ������������� ����� �������������� ������, ������� ����������� ����� �� ����������� ����. ������� �������������� ����� ������.
	wc.cbWndExtra = 0;
	// wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)); // ���������� ����� ���� ������.
	wc.hbrBackground = nullptr;
	wc.hCursor = nullptr;
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	// wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	// wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	// wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	wc.hInstance = hInstance; // ���������� ����������, ������� �������� ������� ��������� ��� ������.
	wc.lpfnWndProc = WndProc; // ��������� �� ���������������� �������
	wc.lpszClassName = L"MyAppClass"; // ��� ������ ����
	wc.lpszMenuName = nullptr; // ������������� ��� ������� ���� ������
	// ������������� �����(�) ������. ���� ���� ��������� ����� ���� ����� ����������� ������ ������.
	wc.style = CS_VREDRAW | CS_HREDRAW;


	// Register window class
	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;

	// Create window instance
	hwnd = CreateWindowEx(0,
	                      wc.lpszClassName,
	                      L"Header",
	                      WS_OVERLAPPEDWINDOW,
	                      CW_USEDEFAULT, // ��������� ���� �� ��� � (�� ���������)
	                      NULL, // ������� ���� �� ��� � (��� ������ � �, �� ������ �� �����)
	                      640,
	                      480,
	                      nullptr,
	                      nullptr,
	                      wc.hInstance,
	                      nullptr);

	if (hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Run loop for handling messages
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg); // ������ ���������
		DispatchMessage(&msg); // �������� ��������� � ������� ���������
	}

	return static_cast<int>(msg.wParam);
}

// ������� ��������� ��� ��������� ���������
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap mm;
	auto outString = mm(uMsg, lParam, wParam);

	// Convert from string to wstring. Don't forget "delete[] wstr;" after using wstring
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, outString.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wchars_num];
	MultiByteToWideChar(CP_UTF8, 0, outString.c_str(), -1, wstr, wchars_num);
	
	OutputDebugString(wstr);
	delete[] wstr;
	
	switch (uMsg)
	{
	case WM_KEYDOWN:
		{
			if(wParam == 'F')
			{
				SetWindowText(hWnd, L"FFFFFFFF");
			}
		}
		return 0;

	case WM_KEYUP:
		{
		SetWindowText(hWnd, L"Header");
		}
		return 0;
		
	case WM_DESTROY:
		{
			// ����������� ���� ���������� ��������� � ��������� ��� �������� ����� ���������
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;
	default: DefWindowProc(hWnd, uMsg, wParam, lParam);;
	}
}
