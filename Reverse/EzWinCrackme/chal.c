#include <windows.h>

#define ID_EDIT 101
#define ID_BUTTON 102

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int checkFlag(char* flag) {
    char* magic = "TNSDHI|0o6tXN2XT6jw64XU4q4u24z";
    int   len   = strlen(magic);
    if (strlen(flag) != len)
        return 0;

    for (int i = 0; i < len; i++) {
        if ((flag[i] ^ 0x7) != magic[i])
            return 0;
    }
    return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    char const CLASS_NAME[] = "MyWindowClass";

    WNDCLASS wc      = {};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0,
                               CLASS_NAME,
                               "EzWinCrackme",
                               WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT,
                               CW_USEDEFAULT,
                               400,
                               200,
                               NULL,
                               NULL,
                               hInstance,
                               NULL);

    if (!hwnd)
        return 0;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit, hButton;
    char        textBuffer[256];

    switch (uMsg) {
        case WM_CREATE:
            hEdit   = CreateWindowEx(WS_EX_CLIENTEDGE,
                                   "EDIT",
                                   "",
                                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                   50,
                                   50,
                                   200,
                                   25,
                                   hwnd,
                                   (HMENU)ID_EDIT,
                                   GetModuleHandle(NULL),
                                   NULL);
            hButton = CreateWindow("BUTTON",
                                   "Check my license",
                                   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                   50,
                                   90,
                                   150,
                                   30,
                                   hwnd,
                                   (HMENU)ID_BUTTON,
                                   GetModuleHandle(NULL),
                                   NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == ID_BUTTON) {
                GetWindowText(hEdit, textBuffer, sizeof(textBuffer));
                if (checkFlag(textBuffer)) {
                    MessageBox(hwnd, "Correct! Good hacker", "License", MB_OK | MB_ICONINFORMATION);
                } else {
                    MessageBox(
                        hwnd, "Invalid license. Bad hacker...", "License", MB_OK | MB_ICONERROR);
                }
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
