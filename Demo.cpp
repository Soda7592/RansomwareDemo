#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
BOOL EncryptFile(LPTSTR, LPVOID);
BOOL DecryptFile(LPTSTR, LPVOID);
DWORD ScanPath(LPTSTR);

// LPTSTR -> Pointer (TCHAR) String
// LPVOID -> void*
// LP -> Pointer
// C -> Constant
// T -> TCHAR
// STR -> String

int _tmain(int argc, _TCHAR* argv[]) {
    return 0;
}

int EncryptFile(LPTSTR lpFileName, LPVOID EncKey) {
    _tprintf(_T("encrypt"));
}

int DecryptFile(LPTSTR lpFileName, LPVOID DecKey) {
    _tprintf(_T("decrypt"));
}

DWORD ScanPath(LPTSTR lpPath) {
    WIN32_FIND_DATA ffd;
    TCHAR szDir[MAX_PATH];
    size_t length_of_arg;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError = 0;
    DWORD dwCount = 0;
    DWORD dwFileAttrib = GetFileAttributes(lpPath);

    if(dwFileAttrib & FILE_ATTRIBUTE_DIRECTORY) {
        StringCchLength(lpPath, MAX_PATH, &length_of_arg);
        if(length_of_arg > MAX_PATH-3) {
            return 0;
        }
        StringCchCopy(szDir, MAX_PATH, lpPath);
        StringCchCat(szDir, MAX_PATH, _T("\\*"));
        if((hFind = FindFirstFile(szDir, &ffd)) == INVALID_HANDLE_VALUE) {
            dwError = GetLastError();
            return 0;
        }
        do {
            _tprintf(_T("%s\n"), ffd.cFileName);

        }while(FindNextFile(hFind, &ffd) != 0);
        
        dwError = GetLastError();
        FindClose(hFind);
    }
    else {
        // Add encryption/decryption functions here;
        _tprintf(_T("%s\n"), lpPath);
        dwCount++;
    }
    return dwCount;
} 