//========================================================================================================================
//  - XCP Info Dumper (xcpid) -
//  Basic Xbox 360 plugin designed to debug print digital content information as it's being downloaded on the console. 
//  Key parts being the URL & the encryption key to allow download and decryption on PC.
//			
//  Created by: Byrom
// 
//  Notes: This is based on a set of rough hooks I created years ago that have been copied from a larger project.
//         The plugin will function but there may be other unused/incomplete bits and pieces included here.
//========================================================================================================================

// Example Info Dump
/*
[xcpid] === XCP Info ===
[xcpid] MediaID: 00000000-0000-400C-80CF-00214156081C
[xcpid] MediaInstanceID: 11DE4253-7A55-403E-805D-89499983E937
[xcpid] Url: http://download.xbox.com/content/4156081c/11de42537a553e5d89499983e93751e045f78f88.xcp
[xcpid] Key: 2422FCCB6FB833A367FB8F31343922A8
[xcpid] ====================
[xcpid] === Additional Info ===
[xcpid] Package Size: 0x0000000051307677 (1362130551 bytes)
[xcpid] Install Size: 0x0000000000016779 (92025 bytes)
[xcpid] Package Type: 0x00000001
[xcpid] Url Count: 0x00000003
[xcpid] Url[0]: http://download.xbox.com/content/4156081c/11de42537a553e5d89499983e93751e045f78f88.xcp
[xcpid] Url[1]: http://download.xbox.com.edgesuite.net/content/4156081c/11de42537a553e5d89499983e93751e045f78f88.xcp
[xcpid] Url[2]: http://xbox-ecn102.vo.msecnd.net/content/4156081c/11de42537a553e5d89499983e93751e045f78f88.xcp
[xcpid] =======================
*/

#include "stdafx.h"
#include "CoreHooks.h"
#include "Utilities.h"

FLOAT xcpidVers = 1.00;

HANDLE hXam;
BOOL bIsDevkit;

GUID ReplacementGUID;
BOOL bReplaceGUID = FALSE;
BOOL bPrintAddInfo = TRUE;

VOID Initialise()
{
	hXam = GetModuleHandle(MODULE_XAM);
	SetupHooks();
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (IsTrayOpen())
		{
			Byrom_Dbg("Plugin load aborted! Disc tray is open");
			*(WORD*)((DWORD)hModule + 64) = 1;
			return FALSE;
		}
		
		bIsDevkit = *(DWORD*)0x8E038610 & 0x8000 ? FALSE : TRUE; // Simple devkit check
		Byrom_Dbg("v%.02f loaded! Running on %s kernel", xcpidVers, bIsDevkit ? "Devkit" : "Retail");
		Byrom_Dbg("XCP information dumper. Created by Byrom.");
		ThreadMe((LPTHREAD_START_ROUTINE)Initialise);
		
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		RemoveHooks();
		Sleep(500);
		Byrom_Dbg("Unload complete! Goodbye...");
		break;

	}
	return TRUE;
}
