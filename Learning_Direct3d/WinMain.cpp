// Макрос для применения более красивых стилей к контролам
// https://docs.microsoft.com/en-us/windows/win32/controls/cookbook-overview
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#include <Windows.h>

int widthClientRegion{};
int heightClientRegion{};

// Прототип функции обработки сообщений с пользовательским названием:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, // дескриптор (в т.ч. некий идентификатор) экземпляра приложения
                   HINSTANCE,
                   LPSTR lpCmdLine,
                   // указатель на строку с аргументами коммандной строки (в случае если прил. стартует из коммандной строки)
                   int nCmdShow) // режим отображения окна
{
	MSG msg{}; // Сообщения которые будут поступать по конвееру в наше приложение
	HWND hwnd{}; // Дескриптор окна нашего приложения для того, чтобы система могла работать с ним 

	// Initialize window class, and feel it start properties
	WNDCLASSEX wc{
		.cbSize = sizeof(WNDCLASSEX) // Объем памяти который нужно зарезирвировать под структуру.
	};
	// Устанавливает число дополнительных байт, которые размещаются вслед за структурой класса окна. Система инициализирует эти байты нулями.
	wc.cbClsExtra = 0;
	// Устанавливает число дополнительных байтов, которые размещаются вслед за экземпляром окна. Система инициализирует байты нулями.
	wc.cbWndExtra = 0;
	// wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)); // Дескриптор кисти фона класса.
	wc.hbrBackground = nullptr;
	wc.hCursor = nullptr;
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	// wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	// wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	// wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	
	wc.hInstance = hInstance; // Дескриптор экземпляра, который содержит оконную процедуру для класса.
	wc.lpfnWndProc = WndProc; // указатель на пользовательскую функцию
	wc.lpszClassName = L"MyAppClass"; // Имя класса окна
	wc.lpszMenuName = nullptr; // Устанавливает имя ресурса меню класса
	// Устанавливает стиль(и) класса. Этот член структуры может быть любой комбинацией Стилей класса.
	wc.style = CS_VREDRAW | CS_HREDRAW;


	// Register window class
	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;

	// Create window instance
	hwnd = CreateWindowEx(0,
	                      wc.lpszClassName,
	                      L"Header",
	                      WS_OVERLAPPEDWINDOW,
	                      CW_USEDEFAULT, // положение окна по оси х (по умолчанию)
	                      NULL, // позиция окна по оси у (раз дефолт в х, то писать не нужно)
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
		TranslateMessage(&msg); // Разбор сообщения
		DispatchMessage(&msg); // Отправка сообщения в оконную процедуру
	}

	return static_cast<int>(msg.wParam);
}

// Оконная процедура для обработки сообщений
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	{
		switch (uMsg)
		{
		case WM_CREATE:
			{
				// MessageBox(hWnd, L"Hello!", L"OK", MB_ICONINFORMATION);
				// ВСЕ контролы являются WINDOW
				// Рисуем кнопку.
				HWND hButton = CreateWindow(
					L"BUTTON", // Имя класса
					L"OK!", // Текст кнопки
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // Стиль кнопки
					0, 0, 300, 30, // Позиция и размеры
					hWnd, // Ссылка на родительский объект
					reinterpret_cast<HMENU>(1555), // Уникальный идентификатор кнопки
					nullptr, nullptr
				);
			}
			return 0;

			// Обрабатываем нажатие кнопки
			// Происходит отправка сообщения родительскому окну о том что был задействован какой то дочерний контрол
		case WM_COMMAND:
			{
				switch (LOWORD(wParam))
					// обрабатываем только те сообщения которые имеют ссылку на кнопку из за которой было вызвано собщение
				{
				case 1555:
					{
						MessageBox(hWnd, L"DO", L"NE", MB_ICONINFORMATION);
					}
					break;
				}
			}
			return 0;

		case WM_SIZE:
			{
				widthClientRegion = LOWORD(lParam);
				heightClientRegion = HIWORD(lParam);
			}
			return 0;

		case WM_DESTROY:
			{
				// Закрываемое окно отправляет сообщение в программу для закрытия самой программы
				PostQuitMessage(EXIT_SUCCESS);
			}
			return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	};
}
