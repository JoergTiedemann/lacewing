
/*
    Copyright (C) 2011 James McLaughlin

    This file is part of Lacewing.

    Lacewing is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Lacewing is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Lacewing.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Common.h"

Lacewing::Sync Sync_DebugOutput;
ostringstream DebugOutput;

#ifdef LacewingWindows
    Lacewing::Sync Sync_GMTime;
#endif

const char * Lacewing::Version()
{
    static bool GotVersion = false;
    static char VersionString[64];

    if(!GotVersion)
    {
        const char * Version, * Platform;

        #ifdef LacewingWindows
            Platform = "Windows";
        #else
            utsname name;
            uname(&name);
            Platform = name.sysname;
        #endif

        #ifdef COXSDK
            Version = "Build #18 Alpha 4";
        #else
            Version = "0.1.0";
        #endif

        sprintf(VersionString, "Lacewing %s (%s/%s)", Version, Platform, sizeof(void *) == 8 ? "x64" : "x86");
        GotVersion = true;
    }

    return VersionString;
}

bool Initialised = false;

void LacewingInitialise()
{
    if(Initialised)
        return;

    #ifdef LacewingWindows

        WSADATA WinsockData;

        if(WSAStartup(MAKEWORD(2, 2), &WinsockData))
            return;
    
    #else

        SSL_library_init();

        STACK_OF(SSL_COMP) * comp_methods = SSL_COMP_get_compression_methods();
        sk_SSL_COMP_zero(comp_methods);

    #endif

    Initialised = true;
}

void Lacewing::Pause(int Milliseconds)
{
    Sleep(Milliseconds);
}

void Lacewing::Yield()
{
    LacewingYield();
}

bool Lacewing::FileExists(const char * Filename)
{
    #ifdef LacewingWindows

        return (GetFileAttributesA(Filename) & FILE_ATTRIBUTE_DIRECTORY) == 0;
        
    #else

        struct stat Attributes;

        if(stat(Filename, &Attributes) == 0)
            return !S_ISDIR(Attributes.st_mode);

        return false;

    #endif

    return false;
}

lw_i64 Lacewing::FileSize(const char * Filename)
{
    #ifdef LacewingWindows
    
        WIN32_FILE_ATTRIBUTE_DATA FileInformation;

        if(!GetFileAttributesExA(Filename, GetFileExInfoStandard, &FileInformation))
            return 0;

        LARGE_INTEGER Size;
        
        Size.LowPart = FileInformation.nFileSizeLow;
        Size.HighPart = FileInformation.nFileSizeHigh;

        return Size.QuadPart;
        
    #else
        
        struct stat Attributes;

        if(stat(Filename, &Attributes) != 0)
            return 0;

        return Attributes.st_size;
        
    #endif
    
}

lw_i64 Lacewing::LastModified(const char * Filename)
{   
    #ifdef LacewingWindows
    
        WIN32_FILE_ATTRIBUTE_DATA FileInformation;

        if(!GetFileAttributesExA(Filename, GetFileExInfoStandard, &FileInformation))
            return 0;
    
        return FileTimeToUnixTime(FileInformation.ftLastWriteTime);
    
    #else
    
        struct stat Attributes;

        if(stat(Filename, &Attributes) != 0)
            return 0;

        return Attributes.st_mtime;
        
    #endif
}

bool Lacewing::StartThread(void * Function, void * Parameter)
{
    #ifdef LacewingWindows

        HANDLE Thread = (HANDLE) _beginthreadex(0, 0, (unsigned (__stdcall *) (void *)) Function, Parameter, 0, 0);
        CloseHandle(Thread);

        return Thread != INVALID_HANDLE_VALUE;

    #else
    
        pthread_t Thread = 0;

        if(pthread_create(&Thread, 0, (void * (*) (void *)) Function, Parameter))
            return false;
        
        return true;

    #endif

    return false;
}

/* TODO : Returning pthread_self as a lw_i64 is a hack, because pthread_t is opaque
          We should assign our own thread IDs (which should be 32-bit anyway) */
    
lw_i64 Lacewing::CurrentThreadID()
{
    #ifdef LacewingWindows

        return GetCurrentThreadId();

    #else

        return (lw_i64) pthread_self();

    #endif

    return -1;
}

void Lacewing::SetCurrentThreadName(const char * Name)
{
    #ifdef LacewingWindows
        
        struct
        {
              DWORD dwType;
              LPCSTR szName;
              DWORD dwThreadID;
              DWORD dwFlags;

        } ThreadNameInfo;

        ThreadNameInfo.dwType      = 0x1000;
        ThreadNameInfo.szName      =   Name;
        ThreadNameInfo.dwThreadID  =     -1;
        ThreadNameInfo.dwFlags     =      0;

        __try
        {
            RaiseException(0x406D1388, 0, sizeof(ThreadNameInfo) / sizeof(ULONG), (ULONG *) &ThreadNameInfo);
        }
        __except (EXCEPTION_CONTINUE_EXECUTION)
        {
        }

    #else

        #if HAVE_DECL_PR_SET_NAME != 0
            prctl(PR_SET_NAME, Name, 0, 0, 0);
        #endif
        
    #endif
}

int Lacewing::CountProcessors()
{

#ifdef LacewingWindows

    static int ProcessorCount = 0;

    if(!ProcessorCount)
    {
        SYSTEM_INFO SystemInformation;
        GetSystemInfo(&SystemInformation);
        ProcessorCount = SystemInformation.dwNumberOfProcessors;
    }

    return ProcessorCount;

#else

    #ifdef HAVE_CORESERVICES_CORESERVICES_H
        return MPProcessors();
    #endif
    
    /* TODO : Unix, and not Darwin */
    
    return 2;

#endif

}

void Lacewing::Int64ToString(lw_i64 Value, char * Output)
{
    sprintf(Output, I64Format, Value);
}

void Lacewing::TempPath(char * Buffer, int Length)
{
    #ifdef LacewingWindows

        GetTempPathA(Length, Buffer);

        for(char * i = Buffer; *i; ++ i)
            if(*i == '\\')
                *i = '/';

    #else

        char * Temp = getenv("TMPDIR");

        if(Temp)
        {
            strcpy(Buffer, Temp);
            return;
        }

        if(P_tmpdir)
        {
            strcpy(Buffer, P_tmpdir);
            return;
        }

        strcpy(Buffer, "/tmp/");
        return;
            
    #endif
}

void Lacewing::NewTempFile(char * Buffer, int Length)
{
    /* TODO: This ignores Length */

    FILE * File;

    do
    {   char TempName[64];

        for(int i = 0; i < sizeof(TempName); i += sizeof(lw_i64))
            *(lw_i64 *) (TempName + i) = i % 2 == 0 ? (lw_i64) time(0) : (lw_i64) rand();

        MD5Hasher MD5;
        MD5.HashBase64(TempName, sizeof(TempName));

        char Path[MAX_PATH];
        TempPath(Path, sizeof(Path));

        if(Path[strlen(Path) - 1] != '/')
        {
            Path[strlen(Path) + 1] =   0;
            Path[strlen(Path)]     = '/';
        }

        sprintf(Buffer, "%slw-temp-%s", Path, TempName);
    }
    while(Lacewing::FileExists(Buffer) || !(File = fopen(Buffer, "wb")));

    fclose(File);
}
