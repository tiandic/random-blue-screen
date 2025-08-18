#include <windows.h>
#include <stdio.h>

#define PRO_NAME "Random Blue Screen"

typedef struct {
    const char *key;
    int line_num;
} KeyMap;

// mode: 0 = 读取字符串值，1 = 写入字符串值
// key: 子键名（键值名称）
// value: 读取时为输出缓冲区，写入时为输入数据
// value_size: 读取时为输入/输出缓冲区大小，写入时为字符串长度（包含'\0'）
// 返回 0 表示成功，否则返回 Windows API 错误码
int reg_rw(const char *key, char *value, DWORD *value_size, int mode) {
    HKEY hKey;
    LONG result;
    char reg_path[1024] = "SOFTWARE\\";
    strcat(reg_path,PRO_NAME);
    strcat(reg_path,"\\Config");
    if (mode == 0) {
        result = RegOpenKeyExA(HKEY_CURRENT_USER, reg_path, 0, KEY_READ, &hKey);
    } else {
        result = RegCreateKeyExA(
            HKEY_CURRENT_USER,
            reg_path,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_WRITE,
            NULL,
            &hKey,
            NULL
        );
    }

    if (result != ERROR_SUCCESS) {
        return (int)result;
    }

    if (mode == 0) {
        DWORD type = 0;
        result = RegQueryValueExA(hKey, key, NULL, &type, (LPBYTE)value, value_size);
        RegCloseKey(hKey);

        if (result == ERROR_SUCCESS) {
            if (type != REG_SZ) {
                return ERROR_INVALID_DATATYPE;
            }
            return 0;
        } else {
            return (int)result;
        }
    } else {
        result = RegSetValueExA(hKey, key, 0, REG_SZ, (const BYTE *)value, *value_size);
        RegCloseKey(hKey);
        return (int)result;
    }
}


void echo_error(char *message){
    int len = MultiByteToWideChar(CP_UTF8, 0, message, -1, NULL, 0);
    wchar_t* wstr = (wchar_t*)malloc(len * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, message, -1, wstr, len);
    MessageBoxW(NULL,wstr,L"error",MB_OK);
}

void remove_reg()
{
    HKEY hKey;
    char error_message[1024];
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE", 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        LONG result = RegDeleteTreeA(hKey, PRO_NAME);
        RegCloseKey(hKey);
        snprintf(error_message,sizeof(error_message),"Failed to delete registry entry.\nerror code: %ld",result);
        if (result != ERROR_SUCCESS)
            echo_error(error_message);
    }
}