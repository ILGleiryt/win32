#include <windows.h>

static int left = 0;
static int top = 300;
static int right = 400;
static int bottom = 100;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/* [~] TODO: Add WM_PAINT to switch logic */
	/* [-] TODO: Add WM_KEYDOWN to switch	  */
	/* [-] TODO: Maybe use WM_SIZE(with static gloabal variables) and GetClientRect for easyer drawing images */
	/* [-] TODO: Make rectangle move just use of keyboard keys { *Use wm_keydown and another methods* }		  */

	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		right += 10;
		if (right >= 1000)
		{
			bottom += 10;
		}
		InvalidateRect(hwnd, nullptr, TRUE);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 2));
		SetDCBrushColor(hdc, RGB(255, 0, 0));
		SetDCPenColor(hdc, RGB(255, 0, 0));
		Rectangle(hdc, left, top, right, bottom);
		EndPaint(hwnd, &ps);
		break;
	}
	default:
		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
	return 0;
}

constexpr wchar_t CLASS_NAME[] = L"Window";

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, 
	LPWSTR cmdLine, int cmdShow)
{
	HWND hwnd{};
	MSG msg{};
	WNDCLASSEX wc{};

	wc.hInstance = hInst;
	wc.lpszClassName = CLASS_NAME;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszMenuName = nullptr;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.cbSize = sizeof(WNDCLASSEX);

	if(!RegisterClassExW(&wc)) return 0;

	if(hwnd = CreateWindowExW(0,CLASS_NAME, L"MyFirstWindow", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, hInst, nullptr); !hwnd)
	{
		MessageBoxW(nullptr, L"Error on window creation", L"Error", MB_OK);
		return 1;
	}

	ShowWindow(hwnd, cmdShow);
	UpdateWindow(hwnd); //use for update window immidiately
	SetTimer(hwnd, 1, 16, nullptr); //create timer that run every n milliseconds

	//BOOL receiver{};
	while(msg.message != WM_QUIT)
	{
		if(PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else
		{	//[-] TODO: Add two methods to render and update game in free time
			//update()
			//render()
		}
	}
	return msg.wParam;
}
