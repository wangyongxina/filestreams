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
DumpFileStream(__in const TCHAR *Path,
			   __in const TCHAR *StreamName,
			   __in const TCHAR *StreamType,
			   __in size_t Length,
               __in size_t Offset);

void
OutputCommandSupport()
{
    _tprintf_s(TEXT("---- Commands Supported ----\n"));
    _tprintf_s(TEXT("\n"));
    _tprintf_s(TEXT("create      Create file stream\n"));
    _tprintf_s(TEXT("enum        Enumerate file streams\n"));
    _tprintf_s(TEXT("delete      Delete file stream\n"));
    _tprintf_s(TEXT("write       Write to file stream\n"));
    _tprintf_s(TEXT("append      Append a file to stream\n"));
    _tprintf_s(TEXT("launch      Start process from file stream\n"));
	_tprintf_s(TEXT("dump        Dump file stream\n"));
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
                                argv[4],
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

void
OnDumpHelp() 
{
    _tprintf_s(TEXT("Usage : FileStreams.exe dump <volume pathname> <stream name> <stream type> <Length> <Offset>\n")
               TEXT("   Eg : FileStreams.exe dump F:\\1.txt test 10\n")
               TEXT("   Eg : FileStreams.exe dump F:\\1.txt test 10	 0\n")
               TEXT("   Eg : FileStreams.exe dump F:\\1.txt test $DATA 10		0\n"));
}

int
OnDump(int argc, TCHAR* argv[]) 
{
    if (argc == 5)
    {
        DumpFileStream(argv[2],
                       argv[3],
                       nullptr,
                       _wtoi(argv[4]),
                       0);

        return 0;
    }
    else if (argc == 6)
    {
        DumpFileStream(argv[2],
                       argv[3],
                       nullptr,
                       _wtoi(argv[4]),
                       _wtoi(argv[5]));

        return 0;
    }
    else if (argc == 7)
    {
        DumpFileStream(argv[2],
                       argv[3],
                       argv[4],
                       _wtoi(argv[5]),
                       _wtoi(argv[6]));

        return 0;
    }
    else
    {
        OnDumpHelp();
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
    else if (_tcsicmp(Command, TEXT("dump")) == 0)
    {
        return OnDump(argc, argv);
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

UCHAR
ToPrintChar(__in BYTE aChar)
{
    if (isprint(aChar))
    {
        return (UCHAR)aChar;
    }
    else
    {
        return '.';
    }
}

void
DumpFileStream(__in const TCHAR *PathString,
               __in const TCHAR *StreamName,
               __in const TCHAR *StreamType,
               __in size_t Length,
               __in size_t Offset)
{
	std::wstring Path = FormatPath(PathString, StreamName, StreamType);

	auto_handle file_handle(CreateFile(Path.c_str(),
                                       GENERIC_READ,
                                       FILE_SHARE_READ,
                                       nullptr,
                                       OPEN_EXISTING,
                                       0,
                                       nullptr));

    if (file_handle.get() == INVALID_HANDLE_VALUE)
    {
        _ftprintf_s(stderr, TEXT("Open file for read failed : %d\n"), GetLastError());
        return;
    }

    if (Length == 0)
    {
        LARGE_INTEGER FileLength;

        if (!GetFileSizeEx(file_handle.get(), &FileLength))
        {
            _ftprintf_s(stderr, TEXT("Get file size failed : %d\n"), GetLastError());
            return;
        }

        Length = FileLength.LowPart;
    }

    if (Offset != 0)
    {
        if (!SetFilePointer(file_handle.get(), Offset, nullptr, FILE_BEGIN))
        {
            _ftprintf_s(stderr, TEXT("Set file pointer failed : %d\n"), GetLastError());
            return;
        }
    }

    std::unique_ptr<BYTE[]> ReadBuffer(new BYTE[Length]);
    DWORD NumberOfBytesRead = 0;

    BOOL fOk = ReadFile(file_handle.get(),
                        ReadBuffer.get(),
                        (DWORD)Length,
                        &NumberOfBytesRead,
                        nullptr);

    if (!fOk || !NumberOfBytesRead)
    {
        _ftprintf_s(stderr, TEXT("Read file failed : %d\n"), GetLastError());
        return;
    }

    _tprintf_s(TEXT("Stream content:\n"));

    TCHAR   Buffer[512]     = { 0 };
    PBYTE   ShowBuffer      = ReadBuffer.get();
    DWORD   Remaining       = 0;
    DWORD   CurrentOffset   = Offset;

    Remaining           = NumberOfBytesRead % 16;
    NumberOfBytesRead  -= Remaining;

    if (NumberOfBytesRead >= 16)
    {
        for (DWORD i = 0; i < NumberOfBytesRead; i += 16)
        {
            ShowBuffer      = ReadBuffer.get() + i;
            CurrentOffset   = Offset + i;

            _stprintf_s(Buffer,
                        TEXT("0x%04X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ")
                        TEXT("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"),
                        CurrentOffset,
                        ShowBuffer[0], ShowBuffer[1], ShowBuffer[2], ShowBuffer[3], ShowBuffer[4], ShowBuffer[5], ShowBuffer[6], ShowBuffer[7],
                        ShowBuffer[8], ShowBuffer[9], ShowBuffer[0xA], ShowBuffer[0xB], ShowBuffer[0xC], ShowBuffer[0xD], ShowBuffer[0xE], ShowBuffer[0xF],
                        ToPrintChar(ShowBuffer[0]), ToPrintChar(ShowBuffer[1]), ToPrintChar(ShowBuffer[2]), ToPrintChar(ShowBuffer[3]),
                        ToPrintChar(ShowBuffer[4]), ToPrintChar(ShowBuffer[5]), ToPrintChar(ShowBuffer[6]), ToPrintChar(ShowBuffer[7]),
                        ToPrintChar(ShowBuffer[8]), ToPrintChar(ShowBuffer[9]), ToPrintChar(ShowBuffer[10]), ToPrintChar(ShowBuffer[11]),
                        ToPrintChar(ShowBuffer[12]), ToPrintChar(ShowBuffer[13]), ToPrintChar(ShowBuffer[14]), ToPrintChar(ShowBuffer[15]));

            _tprintf_s(Buffer);
        }

        ShowBuffer      = ReadBuffer.get() + NumberOfBytesRead;
        CurrentOffset   = Offset + NumberOfBytesRead;
    }

    if (Remaining != 0)
    {
        _stprintf_s(Buffer, TEXT("0x%04X "), CurrentOffset);
        _tprintf_s(Buffer);

        for (DWORD i = 0; i < Remaining; ++i)
        {
            _stprintf_s(Buffer,
                        TEXT("%02X "),
                        ShowBuffer[i]);

            _tprintf_s(Buffer);
        }

        for (DWORD i = 0; i < 16 - Remaining; ++i)
        {
            _tprintf_s(TEXT("   "));
        }

        for (DWORD i = 0; i < Remaining; ++i)
        {
            _stprintf_s(Buffer,
                        TEXT("%c"),
                        ToPrintChar(ShowBuffer[i]));

            _tprintf_s(Buffer);
        }
    }

    _tprintf_s(TEXT("\n"));
}
