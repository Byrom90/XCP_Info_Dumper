#pragma once

#ifndef UTIL_H
#define UTIL_H
#include "stdafx.h"

#define NAME_KERNEL				    "xboxkrnl.exe"
#define NAME_XAM				    "xam.xex"

FARPROC ResolveFunction(HMODULE hHandle, DWORD Ordinal);
FARPROC ResolveFunction(CHAR* ModuleName, DWORD Ordinal);
VOID PatchInJump(DWORD* addr, DWORD dest, BOOL linked);
DWORD PatchModuleImport(PLDR_DATA_TABLE_ENTRY Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress);
DWORD PatchModuleImport(CHAR* Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress);
BOOL IsTrayOpen();
VOID ThreadMe(LPTHREAD_START_ROUTINE lpStartAddress);
VOID XNotify(LPCWSTR pwszStringParam);

// Prints are only enabled is DO_PRINTS is defined below
#define DO_PRINTS // Comment out to disable prints

#ifdef DO_PRINTS
#define Byrom_Dbg(x, ...) { do { /*Byrom_Print*/DbgPrint("[xcpid] " x "\n", __VA_ARGS__); } while(0); }
#else
#define Byrom_Dbg
#endif

#endif