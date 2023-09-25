#include <windows.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance,
                _In_opt_ HINSTANCE hPrevInstance,
                _In_ LPSTR lpCmdLine,
                _In_ int nCmdShow)
{
    MessageBox(nullptr, L"Hello World", L"MyWindow", MB_ICONEXCLAMATION | MB_OK);

    return 0; // 윈도우에서는 반드시 리턴해줘야함
}
