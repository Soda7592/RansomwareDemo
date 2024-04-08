BOOL TargetExt(LPTSTR lpFileName) {
    const LPCTSTR TargetMap[] = {
        _T("doc"), _T("docx"), _T("xls"), _T("xlsx"), _T("ppt"), _T("pptx"), _T("pst"), _T("ost"), _T("msg"), _T("eml"), _T("vsd"), _T("vsdx"), _T("txt"),
        _T("csv"), _T("rtf"), _T("wks"), _T("wkl"), _T("pdf"), _T("dwg"), _T("onetoc2"), _T("snt"), _T("jpeg"), _T("jpg"), _T("docb"), _T("docm"), _T("dot"),
        _T("dotm"), _T("dotx"), _T("xlsm"), _T("pptm"), _T("pot"), _T("pps"), _T("ppsm"), _T("ppsx"), _T("ppam"), _T("potx"), _T("potm"), _T("edb"), _T("hwp"),
        _T("602"), _T("sxi"), _T("sti"), _T("sldx"), _T("sldm"), _T("vdi"), _T("vmdk"), _T("vmx"), _T("gpg"), _T("aes"), _T("ARC"), _T("PAQ"), _T("bz2"), _T("tbk"),
        _T("bak"), _T("tar"), _T("tgz"), _T("gz"), _T("7z"), _T("rar"), _T("zip"), _T("backup"), _T("iso"), _T("vcd"), _T("bmp"), _T("png"), _T("gif"), _T("raw"), 
        _T("cgm"), _T("tif"), _T("tiff"), _T("nef"), _T("psd"), _T("ai"), _T("svg"), _T("djvu"), _T("m4u"), _T("m3u"), _T("mid"), _T("wma"), _T("flv"), _T("3g2"),
        _T("mkv"), _T("3gp"), _T("mp4"), _T("mov"), _T("avi"), _T("asf"), _T("mpeg"), _T("vob"), _T("mpg"), _T("wmv"), _T("fla"), _T("swf"), _T("wav"), _T("mp3"),
        _T("sh"), _T("class"), _T("jar"), _T("java"), _T("rb"), _T("asp"), _T("php"), _T("jsp"), _T("brd"), _T("sch"), _T("dch"), _T("dip"), _T("pl"), _T("vb"),
        _T("vbs"), _T("ps1"), _T("bat"), _T("cmd"), _T("js"), _T("asm"), _T("h"), _T("pas"), _T("cpp"), _T("c"), _T("cs"), _T("suo"), _T("sln"), _T("ldf"), _T("mdf"),
        _T("ibd"), _T("myi"), _T("myd"), _T("frm"), _T("odb"), _T("dbf"), _T("db"), _T("mdb"), _T("accdb"), _T("sql"), _T("sqlitedb"), _T("sqlite3"), _T("asc"),
        _T("lay6"), _T("lay"), _T("mml"), _T("sxm"), _T("otg"), _T("odg"), _T("uop"), _T("std"), _T("sxd"), _T("otp"), _T("odp"), _T("wb2"), _T("slk"), _T("dif"),
        _T("stc"), _T("sxc"), _T("ots"), _T("ods"), _T("3dm"), _T("max"), _T("3ds"), _T("uot"), _T("stw"), _T("sxw"), _T("ott"), _T("odt"), _T("pem"), _T("p12"),
        _T("csr"), _T("crt"), _T("key"), _T("pfx"), _T("der"), NULL
    };
    TCHAR *ptr = _tcsrchr(lpFileName, '.');
    if(ptr) {
        ptr++;
        for(DWORD i=0;TargetMap[i]; i++) {
            if(!_tcsicmp(ptr, TargetMap[i])) 
                return TRUE;
        }
    }
    return FALSE;
}