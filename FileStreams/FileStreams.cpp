#include "stdafx.h"
#include "Util.h"

void
EnumFileStreams(__in const TCHAR *Path);

void
CreateOrWriteFileStream(__in const TCHAR *Path,
                        __in const TCHAR *StreamName,
                        __in const TCHAR *StreamType,
                        __in const TCHAR *StreamContent);

void
DeleteFileStream(__in const TCHAR *Path,
                 __in const TCHAR *StreamName,
                 __in const TCHAR *StreamType);

void
AppendFileToString(__in const TCHAR *SourcePath,
                   __in const TCHAR *SourceStreamName,
                   __in const TCHAR *SourceStreamType,
                   __in const TCHAR *DestPath,
                   __in const TCHAR *DestStreamName,
                   __in const TCHAR *DestStreamType);

void
LaunchFileStream(__in const TCHAR *Path,
                 __in const TCHAR *StreamName,
                 __in const TCHAR *StreamType);

void
OutputCommandSupport()
{
    _tprintf_s(TEXT("---- Commands Supported ----\n"));
    _tprintf_s(TEXT("\n"));
    _tprintf_s(TEXT("create      Create file stream\n"));
    _tprintf_s(TEXT("enum        Enumerate file streams\n"));
    _tprintf_s(TEXT("delete      Delete file stream\n"));
    _tprintf_s(TEXT("write       Write to file stream\n"));
    _tprintf_s(TEXT("append      Append a file to stream"));
    _tprintf_s(TEXT("launch      Start process from file stream"));
}

void
OnEnumHelp()
{
    _tprintf_s(TEXT("Usage : FileStreams.exe enum <volume pathname>\n")
               TEXT("   Eg : FileStreams.exe enum C:\\stream.txt\n"));
}

int
OnEnum(int argc, TCHAR *argv[])
{
    if (argc == 3)
    {
        const TCHAR *Path = argv[2];

        EnumFileStreams(Path);

        return 0;
    }
    else
    {
        OnEnumHelp();

        return -1;
    }
}

void OnCreateHelp() 
{
    _tprintf_s(TEXT("Usage : FileStreams.exe create <volume pathname> <stream name> <stream type>\n")
               TEXT("   Eg : FileStreams.exe create C:\\stream.txt abc\n")
               TEXT("   Eg : FileStreams.exe create C:\\stream.txt abc $DATA\n"));
}

int
OnCreate(int argc, TCHAR* argv[])
{
    if (argc == 4)
    {
        CreateOrWriteFileStream(argv[2],
                         argv[3],
                         nullptr,
                         nullptr);

        return 0;
    }
    else if (argc == 5)
    {
        CreateOrWriteFileStream(argv[2],
                         argv[3],
                         argv[5],
                         nullptr);

        return 0;
    }
    else
    {
        OnCreateHelp();

        return -1;
    }    
}

void
OnDeleteHelp() 
{
    _tprintf_s(TEXT("Usage : FileStreams.exe delete <volume pathname> <stream name> <stream type>\n")
               TEXT("   Eg : FileStreams.exe delete C:\\stream.txt\n")
               TEXT("   Eg : FileStreams.exe delete C:\\stream.txt abc\n")
               TEXT("   Eg : FileStreams.exe delete C:\\stream.txt abc $DATA\n"));

}

int
OnDelete(int argc, TCHAR* argv[])
{
    if (argc == 3)
    {
        DeleteFileStream(argv[2], nullptr, nullptr);

        return 0;
    }
    else if (argc == 4)
    {
        DeleteFileStream(argv[2], argv[3], nullptr);

        return 0;
    }
    else if (argc == 5)
    {
        DeleteFileStream(argv[2], argv[3], argv[4]);

        return 0;
    }
    else
    {
        OnDeleteHelp();

        return -1;
    }

}

void
OnWriteHelp() 
{
    _tprintf_s(TEXT("Usage : FileStreams.exe write <volume pathname> <stream name> <stream type> <content>\n")
               TEXT("   Eg : FileStreams.exe write C:\\stream.txt abc content\n")
               TEXT("   Eg : FileStreams.exe write C:\\stream.txt abc $DATA content\n"));
}

int
OnWrite(int argc,  TCHAR* argv[]) 
{
    if (argc == 5)
    {
        CreateOrWriteFileStream(argv[2],
                                argv[3],
                                nullptr,
                                argv[4]);

        return 0;
    }
    else if (argc == 6)
    {
        CreateOrWriteFileStream(argv[2],
                                argv[3],
                                argv[4],
                                argv[5]);

        return 0;
    }
    else
    {
        OnWriteHelp();
        return -1;
    }
}

void
OnAppendHelp() 
{
    _tprintf_s(TEXT("Usage : FileStreams.exe append <volume pathname> <stream name> <volume path name> <stream name> \n")
               TEXT("   Eg : FileStreams.exe append F:\\1.txt test1 F:\\2.txt\n")
               TEXT("   Eg : FileStreams.exe append F:\\1.txt test1 F:\\2.txt test\n"));
}

int
OnAppend(int argc, TCHAR* argv[]) 
{
    if (argc == 5)
    {
        AppendFileToString(argv[2],
                           argv[3],
                           nullptr,
                           argv[4],
                           nullptr,
                           nullptr);

        return 0;
    }
    else if (argc == 6)
    {
        AppendFileToString(argv[2],
                           argv[3],
                           nullptr,
                           argv[4],
                           argv[5],
                           nullptr);

        return 0;
    }
    else
    {
        OnAppendHelp();

        return -1;
    }
}

void
OnLaunchHelp() 
{
    _tprintf_s(TEXT("Usage : FileStreams.exe launch <volume pathname> <stream name> <stream type>\n")
               TEXT("   Eg : FileStreams.exe launch F:\1.txt testExe\n")
               TEXT("   Eg : FileStreams.exe launch F:\1.txt testExe $DATA\n"));
}

int
OnLaunch(int argc, TCHAR* argv[]) 
{
    if (argc == 4)
    {
        LaunchFileStream(argv[2],
                         argv[3],
                         nullptr);

        return 0;
    }
    else if (argc == 5)
    {
        LaunchFileStream(argv[2],
                         argv[3],
                         argv[4]);

        return 0;
    }
    else
    {
        OnLaunchHelp();

        return -1;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    if (argc == 1)
    {
        OutputCommandSupport();
        return 0;
    }

    const TCHAR *Command = argv[1];

    if (_tcsicmp(Command, TEXT("create")) == 0)
    {
        return OnCreate(argc, argv);
    }
    else if (_tcsicmp(Command, TEXT("delete")) == 0)
    {
        return OnDelete(argc, argv);
    }
    else if (_tcsicmp(Command, TEXT("write")) == 0)
    {
        return OnWrite(argc, argv);
    }
    else if (_tcsicmp(Command, TEXT("append")) == 0)
    {
        return OnAppend(argc, argv);
    }
    else if (_tcsicmp(Command, TEXT("enum")) == 0)
    {
        return OnEnum(argc, argv);
    }
    else if (_tcsicmp(Command, TEXT("launch")) == 0)
    {
        return OnLaunch(argc, argv);
    }
    else
    {
        _ftprintf_s(stderr, TEXT("%s is an invalid parameters.\n"), argv[1]);
        OutputCommandSupport();
    }

	return 0;
}

void
SplitStreamString(__in const TCHAR *StreamString,
                  __out std::wstring &StreamName,
                  __out std::wstring &StreamType)
{
    StreamName.clear();
    StreamType.clear();

    if (StreamString[0] != TEXT(':'))
    {
        return;
    }

    const TCHAR *p = _tcschr(StreamString + 1, TEXT(':'));

    if (!p)
    {
        return;
    }

    StreamName.assign(StreamString + 1, p);
    StreamType.assign(p + 1);
}

void
EnumFileStreams(__in const TCHAR *Path)
{
    std::wstring StreamName;
    std::wstring StreamType;
    WIN32_FIND_STREAM_DATA FindStreamData;
    HANDLE FindHandle = FindFirstStreamW(Path, FindStreamInfoStandard, &FindStreamData, 0);

    if (FindHandle == INVALID_HANDLE_VALUE)
    {
        _ftprintf_s(stderr, TEXT("FindFirstStream failed : %d\n"), GetLastError());
        return;
    }

    _tprintf_s(TEXT("%s file stream:\n"), Path);

    do
    {
        SplitStreamString(FindStreamData.cStreamName, StreamName, StreamType);

        _tprintf_s(TEXT("Stream name : %s\tStream type : %s\tStream size : %I64d\n"),
                   (StreamName.empty() ? TEXT("default") : StreamName.c_str()),
                   StreamType.c_str(),
                   FindStreamData.StreamSize.QuadPart);

    } while (FindNextStreamW(FindHandle, &FindStreamData));

    FindClose(FindHandle);

    _tprintf_s(TEXT("\n"));
}

std::wstring
FormatPath(__in const TCHAR * PathString,
           __in_opt const TCHAR * StreamName,
           __in_opt const TCHAR * StreamType)
{
    std::wstring Path = PathString;

    if (StreamName)
    {
        Path += L":";
        Path += StreamName;
    }
    else
    {
        return Path;
    }

    if (StreamType)
    {
        Path += L":";
        Path += StreamType;
    }

    return Path;
}

void
CreateOrWriteFileStream(__in const TCHAR *PathString,
                        __in const TCHAR *StreamName,
                        __in const TCHAR *StreamType,
                        __in const TCHAR *StreamContent)
{
    std::wstring Path = FormatPath(PathString, StreamName, StreamType);

    HANDLE FileHandle = CreateFile(Path.c_str(),
                                   GENERIC_READ | GENERIC_WRITE,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   nullptr,
                                   OPEN_ALWAYS,
                                   FILE_ATTRIBUTE_NORMAL,
                                   nullptr);

    if (FileHandle == INVALID_HANDLE_VALUE)
    {
        _ftprintf_s(stderr, TEXT("Creating file stream failed:(%s), %d"), Path.c_str(), GetLastError());
        return;
    }
    else if (StreamContent)
    {
        DWORD NumberOfBytesWrite = 0;
        DWORD WriteBytes = _tcslen(StreamContent) * sizeof(TCHAR);

        BOOL fOk = WriteFile(FileHandle,
                             StreamContent,
                             WriteBytes,
                             &NumberOfBytesWrite,
                             nullptr);

        if (!fOk || NumberOfBytesWrite != WriteBytes)
        {
            _ftprintf_s(stderr, TEXT("Writing file stream failed : %s, %d"), Path.c_str(), GetLastError());
        }
        else
        {
            _tprintf_s(TEXT("%s write stream success"), PathString);
        }
    }
    else
    {
        _tprintf_s(TEXT("%s create stream success\n"), PathString);
    }

    CloseHandle(FileHandle);
}

void
DeleteFileStream(__in const TCHAR *PathString,
                 __in const TCHAR *StreamName,
                 __in const TCHAR *StreamType)
{
    std::wstring Path = FormatPath(PathString, StreamName, StreamType);

    if (StreamName == nullptr)
    {
        _tprintf_s(TEXT("Warning you are going to delete this file\n"));
    }

    HANDLE FileHandle = CreateFile(Path.c_str(),
                                   DELETE,
                                   FILE_SHARE_DELETE,
                                   nullptr,
                                   OPEN_EXISTING,
                                   FILE_FLAG_DELETE_ON_CLOSE,
                                   NULL);

    if (FileHandle == INVALID_HANDLE_VALUE)
    {
        _ftprintf_s(stderr, TEXT("Delete %s failed: %d\n"), Path.c_str(), GetLastError());
        return;
    }

    CloseHandle(FileHandle);

    _tprintf_s(TEXT("Delete file success\n"));
}

void
AppendFileToString(__in const TCHAR *SourcePathString,
                   __in const TCHAR *SourceStreamName,
                   __in const TCHAR *SourceStreamType,
                   __in const TCHAR *DestPathString,
                   __in const TCHAR *DestStreamName,
                   __in const TCHAR *DestStreamType)
{
    std::wstring SourcePath = FormatPath(SourcePathString, SourceStreamName, SourceStreamType);
    std::wstring DestPath   = FormatPath(DestPathString, DestStreamName, DestStreamType);

    auto_handle SourceHandle(CreateFile(SourcePath.c_str(),
                                        GENERIC_WRITE,
                                        FILE_SHARE_READ,
                                        nullptr,
                                        OPEN_ALWAYS,
                                        0,
                                        nullptr));

    if (SourceHandle.get() == INVALID_HANDLE_VALUE)
    {
        _ftprintf_s(stderr, TEXT("Open source file failed : %d\n"), GetLastError());
        return;
    }

    auto_handle DestHandle(CreateFile(DestPath.c_str(),
                                      GENERIC_READ,
                                      FILE_SHARE_READ,
                                      nullptr,
                                      OPEN_EXISTING,
                                      0,
                                      nullptr));

    if (DestHandle.get() == INVALID_HANDLE_VALUE)
    {
        _ftprintf_s(stderr, TEXT("Open destination file failed : %d\n"), GetLastError());
        return;
    }

    std::unique_ptr<BYTE[]> Buffer(new BYTE[4096]);
    DWORD NumberOfBytesWritten  = 0;
    DWORD NumberOfBytesRead     = 0;
    BOOL fOk = FALSE;

    while (TRUE)
    {
        fOk = ReadFile(DestHandle.get(), Buffer.get(), 4096, &NumberOfBytesRead, nullptr);

        if (!fOk)
        {
            break;
        }

        if (NumberOfBytesRead == 0)
        {
            fOk = TRUE; // End
            break;
        }

        fOk = WriteFile(SourceHandle.get(), Buffer.get(), NumberOfBytesRead, &NumberOfBytesWritten, nullptr);

        if (!fOk)
        {
            break;
        }

        if (NumberOfBytesWritten != NumberOfBytesRead)
        {
            break;
        }
    }

    if (fOk)
    {
        _ftprintf_s(stderr, TEXT("Append file success\n"));
    }
    else
    {
        _ftprintf_s(stderr, TEXT("Write file failed : %d\n"), GetLastError());
    }
}

void
LaunchFileStream(__in const TCHAR *PathString,
                 __in const TCHAR *StreamName,
                 __in const TCHAR *StreamType)
{
    std::wstring Path = FormatPath(PathString, StreamName, StreamType);

    STARTUPINFO st = { sizeof(st) };
    PROCESS_INFORMATION pi;

    BOOL fOk = CreateProcess(NULL,
                             const_cast<LPWSTR>(Path.c_str()),
                             nullptr,
                             nullptr,
                             FALSE,
                             0,
                             nullptr,
                             nullptr,
                             &st,
                             &pi);

    if (fOk)
    {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        _tprintf_s(TEXT("launch %s success\n"), Path.c_str());
    }
    else
    {
        _ftprintf_s(stderr, TEXT("launch %s failed : %d\n"), Path.c_str(), GetLastError());
    }
}