#include <windows.h>
#include <sstream>

const wchar_t gClassName[] = L"MyWindowClass";
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
/*
    1. 윈도우 클래스 등록
    2. 윈도우를 생성
    3. 윈도우 메세지 처리
    4. 윈도우 프로시저 작성
*/

// entrt point
int WINAPI WinMain(_In_ HINSTANCE hInstance,
                _In_opt_ HINSTANCE hPrevInstance,
                _In_ LPSTR lpCmdLine,
                _In_ int nCmdShow)
{
       //1. 윈도우 클래스 등록
    WNDCLASSEX wc{};
    // important
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = gClassName;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WindowProc;
    wc.cbSize = sizeof(WNDCLASSEX);

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(nullptr, L"Failed to register", L"Error", MB_OK);
        return 0;
    }
       //2. 윈도우를 생성
    HWND hwnd;
    hwnd = CreateWindowEx(
        0,
        gClassName,
        L"Hello World",
        WS_EX_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        640,
        480,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd)
    {
        MessageBox(nullptr, L"Failed to register", L"Error", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd); // 쇼 윈도우와 업데이트 윈도우랑 한 세트


    //3. 윈도우 메세지 처리
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam; // 윈도우에서는 반드시 리턴해줘야함
}
void OnPAint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    HPEN redpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    HBRUSH hatchbrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));

    SelectObject(hdc, redpen);
    SelectObject(hdc, hatchbrush);
    Rectangle(hdc, 0, 0, 100, 100);

    DeleteObject(hatchbrush);
    DeleteObject(redpen);
    EndPaint(hwnd, &ps);
}
/*
    4. 윈도우 프로시저 작성
*/

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        OnPAint(hwnd);
        break;
    }
    case WM_KEYDOWN:
    {
        std::ostringstream oss;
        oss << "virtual keycode" << wParam << std::endl;
        OutputDebugStringA(oss.str().c_str());
        break;
    }
    case WM_LBUTTONDOWN:
    {
        std::ostringstream oss;
        oss << "x : " << LOWORD(lParam) << ", y : " << HIWORD(lParam) << std::endl;
        OutputDebugStringA(oss.str().c_str());
        break;
    }
 
        

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
        break;
    }
    return 0;
}