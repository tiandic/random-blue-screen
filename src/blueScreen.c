/*
 * @encode: utf-8
 * @Date: 2025-08-07 20:41:01
 * @LastEditTime: 2025-08-18 14:08:30
 * @FilePath: /random blue screen/src/blueScreen.c
 */
#include <windows.h>
#include <process.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "def.h"
#include "reg.h"

static unsigned char* imgData = NULL;
static int imgWidth, imgHeight, imgChannels;

void LoadImageWithStb(const char* filename)
{
    // 加载图像，强制4通道（RGBA）
    imgData = stbi_load(filename, &imgWidth, &imgHeight, &imgChannels, 4);
    imgChannels = 4; // 因为强制4通道了
    if (!imgData)
    {
        MessageBoxA(NULL, "Failed to load image", "Error", MB_OK);
        exit(1);
    }
}

void ConvertRGBAtoBGRA(unsigned char* data, int width, int height)
{
    int pixelCount = width * height;
    for (int i = 0; i < pixelCount; ++i)
    {
        unsigned char* px = data + i * 4;
        unsigned char r = px[0];
        px[0] = px[2]; // B
        px[2] = r;     // R
    }
}

void FreeImage()
{
    if (imgData) stbi_image_free(imgData);
    imgData = NULL;
}

void DrawImage(HDC hdc)
{
    if (!imgData) return;

    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = imgWidth;
    bmi.bmiHeader.biHeight = -imgHeight; // 负高度表示顶向下位图
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32; // 4通道 8位*4
    bmi.bmiHeader.biCompression = BI_RGB;

    StretchDIBits(
        hdc,
        0, 0, imgWidth, imgHeight,
        0, 0, imgWidth, imgHeight,
        imgData,
        &bmi,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}


unsigned __stdcall e(void* arg)
{
    HWND hwnd = (HWND)arg;
    while (TRUE)
    {
        // BlockInput(FALSE);
        BlockInput(TRUE);
        Sleep(1);
    }
    
}

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lparam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        BlockInput(TRUE);
        SetTimer(hwnd, 1, 1000, NULL);
        break;
    case WM_PAINT:{
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd,&ps);
        DrawImage(hdc);
        EndPaint(hwnd,&ps);
        }break;
    case WM_CLOSE:
        BlockInput(FALSE);
        DestroyWindow(hwnd);
        break;
    case WM_TIMER:
        if (wParam == 1)
            puts("Timer...\n");
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lparam);
}

WNDCLASSA init_window()
{
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
     wc.lpszClassName = "blue";
    if (!RegisterClassA(&wc))
        exit(1);
    return wc;
}

HWND create_window(WNDCLASSA wc)
{
    // 设置窗口为屏幕大小
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExA(
        0,                      // 去掉 WS_EX_LAYERED
        wc.lpszClassName,
        "blue Screen",
        WS_POPUP | WS_VISIBLE,
        0, 0, screenWidth, screenHeight,
        NULL,
        NULL,
        wc.hInstance,
        NULL
    );
    if (hwnd == NULL)
        exit(1);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    return hwnd;
}

void show_window(HWND hwnd)
{
    ShowWindow(hwnd,SW_SHOWMAXIMIZED);
    UpdateWindow(hwnd);
    unsigned int dwThreadID;
    _beginthreadex(NULL,0,e,(void*)hwnd,0,&dwThreadID);
}

void message_loop()
{
    MSG msg;
    while (GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSA wc = init_window();
    HWND hwnd = create_window(wc);
    char path[MAX_PATH];
    DWORD size = sizeof(path);
    reg_rw(IMAGE_PATH,path,&size,0);
    LoadImageWithStb(path);
    ConvertRGBAtoBGRA(imgData, imgWidth, imgHeight);
    show_window(hwnd);
    message_loop();
    return 0;
}
