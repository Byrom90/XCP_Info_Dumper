#include "stdafx.h"
#include "Utilities.h"
#include "Detour.h"

// Quick fix - For whatever reason any type of prints done inside the findmediainst hook don't work when using xbWatson.
// This just does it in a system thread instead.
DWORD g_status[1];
VOID DoInfoPrint(PMEDIA_INSTANCE_URLS PMIU)
{
	if (bIsDevkit) // Printing on devkit works correctly with new lines etc. Bundling it all together in one print ensures it doesn't get split up by other prints in kdnet
	{
		char MediaID[50];
		sprintf(MediaID, "MediaID: %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", PMIU->MediaID.Data1, PMIU->MediaID.Data2, PMIU->MediaID.Data3, PMIU->MediaID.Data4[0], PMIU->MediaID.Data4[1], PMIU->MediaID.Data4[2], PMIU->MediaID.Data4[3], PMIU->MediaID.Data4[4], PMIU->MediaID.Data4[5], PMIU->MediaID.Data4[6], PMIU->MediaID.Data4[7]);

		char MediaInstanceID[60];
		sprintf(MediaInstanceID, "MediaInstanceID: %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", PMIU->MediaInstanceID.Data1, PMIU->MediaInstanceID.Data2, PMIU->MediaInstanceID.Data3, PMIU->MediaInstanceID.Data4[0], PMIU->MediaInstanceID.Data4[1], PMIU->MediaInstanceID.Data4[2], PMIU->MediaInstanceID.Data4[3], PMIU->MediaInstanceID.Data4[4], PMIU->MediaInstanceID.Data4[5], PMIU->MediaInstanceID.Data4[6], PMIU->MediaInstanceID.Data4[7]);

		char Url[110];
		sprintf(Url, "Url: %s", PMIU->pUrls[0].pszUrl);

		char Key[45];
		sprintf(Key, "Key: %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", PMIU->rgbSymKey[0], PMIU->rgbSymKey[1], PMIU->rgbSymKey[2], PMIU->rgbSymKey[3], PMIU->rgbSymKey[4], PMIU->rgbSymKey[5],
			PMIU->rgbSymKey[6], PMIU->rgbSymKey[7], PMIU->rgbSymKey[8], PMIU->rgbSymKey[9], PMIU->rgbSymKey[10], PMIU->rgbSymKey[11], PMIU->rgbSymKey[12], PMIU->rgbSymKey[13], PMIU->rgbSymKey[14], PMIU->rgbSymKey[15]);

		Byrom_Dbg("=== XCP Info ===\n%s\n%s\n%s\n%s\n====================", MediaID, MediaInstanceID, Url, Key);

		if (bPrintAddInfo)
		{
			char PackageSize[55];
			sprintf(PackageSize, "Package Size: 0x%016X (%llu bytes)", PMIU->qwPackageSize, PMIU->qwPackageSize);

			char InstallSize[55];
			sprintf(InstallSize, "Install Size: 0x%016X (%llu bytes)", PMIU->qwInstallSize, PMIU->qwInstallSize);

			char PackageType[30];
			sprintf(PackageType, "Package Type: 0x%08X", PMIU->dwPackageType);

			char UrlCount[30];
			sprintf(UrlCount, "Url Count: 0x%08X", PMIU->dwUrlCount);

			char Url0[110];
			sprintf(Url0, "Url[0]: %s", PMIU->pUrls[0].pszUrl);

			char Url1[110];
			sprintf(Url1, "Url[1]: %s", PMIU->dwUrlCount > 1 ? PMIU->pUrls[1].pszUrl : "NULL");

			char Url2[110];
			sprintf(Url2, "Url[2]: %s", PMIU->dwUrlCount > 2 ? PMIU->pUrls[2].pszUrl : "NULL");

			Byrom_Dbg("=== Additional Info ===\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n=======================", PackageSize, InstallSize, PackageType, UrlCount, Url0, Url1, Url2);
		}
	}
	else // Jtag version of xbdm gets weird when printing content containing new lines so we do it all individually
	{
		Byrom_Dbg("=== XCP Info ===");
		Byrom_Dbg("MediaID: %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", PMIU->MediaID.Data1, PMIU->MediaID.Data2, PMIU->MediaID.Data3, PMIU->MediaID.Data4[0], PMIU->MediaID.Data4[1], PMIU->MediaID.Data4[2], PMIU->MediaID.Data4[3], PMIU->MediaID.Data4[4], PMIU->MediaID.Data4[5], PMIU->MediaID.Data4[6], PMIU->MediaID.Data4[7]);
		Byrom_Dbg("MediaInstanceID: %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", PMIU->MediaInstanceID.Data1, PMIU->MediaInstanceID.Data2, PMIU->MediaInstanceID.Data3, PMIU->MediaInstanceID.Data4[0], PMIU->MediaInstanceID.Data4[1], PMIU->MediaInstanceID.Data4[2], PMIU->MediaInstanceID.Data4[3], PMIU->MediaInstanceID.Data4[4], PMIU->MediaInstanceID.Data4[5], PMIU->MediaInstanceID.Data4[6], PMIU->MediaInstanceID.Data4[7]);
		Byrom_Dbg("Url: %s", PMIU->pUrls[0].pszUrl);
		Byrom_Dbg("Key: %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", PMIU->rgbSymKey[0], PMIU->rgbSymKey[1], PMIU->rgbSymKey[2], PMIU->rgbSymKey[3], PMIU->rgbSymKey[4], PMIU->rgbSymKey[5],
			PMIU->rgbSymKey[6], PMIU->rgbSymKey[7], PMIU->rgbSymKey[8], PMIU->rgbSymKey[9], PMIU->rgbSymKey[10], PMIU->rgbSymKey[11], PMIU->rgbSymKey[12], PMIU->rgbSymKey[13], PMIU->rgbSymKey[14], PMIU->rgbSymKey[15]);
		Byrom_Dbg("====================");

		if (bPrintAddInfo)
		{
			Byrom_Dbg("=== Additional Info ===");
			Byrom_Dbg("Package Size: 0x%016X (%llu bytes)", PMIU->qwPackageSize, PMIU->qwPackageSize);
			Byrom_Dbg("Install Size: 0x%016X (%llu bytes)", PMIU->qwInstallSize, PMIU->qwInstallSize);
			Byrom_Dbg("Package Type: 0x%08X", PMIU->dwPackageType);
			Byrom_Dbg("Url Count: 0x%08X", PMIU->dwUrlCount);
			Byrom_Dbg("Url[0]: %s", PMIU->pUrls[0].pszUrl);
			Byrom_Dbg("Url[1]: %s", PMIU->dwUrlCount > 0 ? PMIU->pUrls[1].pszUrl : "NULL");
			Byrom_Dbg("Url[2]: %s", PMIU->dwUrlCount > 1 ? PMIU->pUrls[2].pszUrl : "NULL");
			Byrom_Dbg("=======================");
		}
	}
	g_status[0] = 1;
	__dcbst(0, g_status);
	__sync();
	__isync();
}


VOID SysPrintXCPInfo(PMEDIA_INSTANCE_URLS PMIU)
{
	HANDLE pthread;
	DWORD pthreadid;
	DWORD sta;
	g_status[0] = 0;
	__dcbst(0, g_status);
	__sync();
	__isync();

	sta = ExCreateThread(&pthread, 0, &pthreadid, (PVOID)XapiThreadStartup, (LPTHREAD_START_ROUTINE)DoInfoPrint, (LPVOID)PMIU, 0x2);
	XSetThreadProcessor(pthread, 4);
	SetThreadPriority(pthread, THREAD_PRIORITY_TIME_CRITICAL);
	ResumeThread(pthread);
	CloseHandle(pthread);

	// wait for thread to run it's course
	while (g_status[0] == 0)
	{
		Sleep(100);
	}
}

Detour XOnlineFindMediaInstanceUrlsDetour;
#define XOnlineFindMediaInstanceUrls_Addr_DEVKIT 0x819CC760  // DEVKIT 17489
#define XOnlineFindMediaInstanceUrls_Addr_RETAIL 0x81826580 // RETAIL 17559
HRESULT XOnlineFindMediaInstanceUrlsHook(unsigned long unk1, _GUID* GUID1, unsigned long unk2, _FIND_MEDIA_INSTANCE_URLS_RESPONSE* FMIRR, _XOVERLAPPED* XOXO)
{
	// Prints in here DO NOT WORK! Pointless to have them enabled.
	
	//Byrom_Dbg("[FindMedInst Hook] Called");
	//if (bReplaceGUID)
	//	Byrom_Dbg("[FindMedInst Hook] Using replacement GUID: %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
	//		ReplacementGUID.Data1, ReplacementGUID.Data2, ReplacementGUID.Data3, ReplacementGUID.Data4[0], ReplacementGUID.Data4[1], ReplacementGUID.Data4[2], ReplacementGUID.Data4[3], ReplacementGUID.Data4[4], ReplacementGUID.Data4[5], ReplacementGUID.Data4[6], ReplacementGUID.Data4[7]);
	
	auto Original = XOnlineFindMediaInstanceUrlsDetour.GetOriginal<decltype(&XOnlineFindMediaInstanceUrlsHook)>();
	HRESULT Result = Original(unk1, (bReplaceGUID ? &ReplacementGUID : GUID1), unk2, FMIRR, XOXO);

	if (XOXO != NULL)
	{
		int timeoutcounter = 0;
		while (!XHasOverlappedIoCompleted(XOXO))
		{
			timeoutcounter++;
			if (timeoutcounter >= 15)
				return ERROR_CAN_NOT_COMPLETE; // idk if this will work but fuck it
			//Byrom_Dbg("[FindMedInst Hook] Waiting for XOverlapped to complete");
			Sleep(500);
		}
	}

	//Byrom_Dbg("[FindMedInst Hook] XOverlappedIoCompleted");

	if (FMIRR->dwMediaInstanceIdsCount != 0)
	{
		SysPrintXCPInfo(FMIRR->pMediaInstanceIds);
	}
	//else
	//	Byrom_Dbg("[FindMedInst Hook] MediaInstanceIdsCount is 0! Invalid GUID provided???\n");

	return Result;
}

// These 2 hooks are added to catch title updates since those don't go through the above hook
// Better solutions may exist but I already had this

// # void *__fastcall CXHttp::XHttpOpenRequestUsingMemory(CXHttp *__hidden this, void *, const char *, const char *, const char *, const char *, const char **, void *, unsigned int, unsigned int)
Detour XAMXHttpOpenRequestUsingMemoryDetour;
#define XAM_XHttpOpenRequestUsingMemory_Addr_DEVKIT 0x81A1CD90 // DEVKIT 17489
#define XAM_XHttpOpenRequestUsingMemory_Addr_RETAIL 0x81858238 // RETAIL 17559
DWORD XAMXHttpOpenRequestUsingMemoryHook(DWORD hConnect, const CHAR* pcszVerb, const CHAR* pcszObjectName, const CHAR* pcszVersion, const CHAR* pcszReferrer, const CHAR** ppReserved, PVOID UNKNOWN, DWORD UNKNOWN2, DWORD dwFlags)
{
	auto Original = XAMXHttpOpenRequestUsingMemoryDetour.GetOriginal<decltype(&XAMXHttpOpenRequestUsingMemoryHook)>();

	if (strstr(pcszObjectName, ".xcp")) // Only print for xcp files
	{
		Byrom_Dbg("[XHttp Hook] Url: %s", pcszObjectName);
	}

	DWORD Result = Original(hConnect, pcszVerb, pcszObjectName, pcszVersion, pcszReferrer, ppReserved, UNKNOWN, UNKNOWN2, dwFlags);
	return Result;
}

// void __cdecl CXCabCryptHelper::InitializeDecryption(struct _RC4_SHA_HEADER const *, unsigned long, unsigned char const *, unsigned long)
Detour InitializeDecryptionDetour;
#define InitializeDecryption_Addr_DEVKIT 0x81B0BA10 // DEVKIT 17489
#define InitializeDecryption_Addr_RETAIL 0x818F8A78 // RETAIL 17559
PBYTE PreviousKey = 0;
VOID InitializeDecryptionHook(DWORD CXCabCryptHelper_p,  const RC4_SHA_HEADER* shahead, DWORD unk1, const PBYTE pbKey, DWORD cbKey)
{
	auto Original = InitializeDecryptionDetour.GetOriginal<decltype(&InitializeDecryptionHook)>();

	if (pbKey != PreviousKey) // Prevent it spamming the same key
	{
		PreviousKey = pbKey;
		Byrom_Dbg("[InitDecryption Hook] Key: %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
			pbKey[0], pbKey[1], pbKey[2], pbKey[3], pbKey[4], pbKey[5], pbKey[6], pbKey[7], pbKey[8], pbKey[9], pbKey[10], pbKey[11], pbKey[12], pbKey[13], pbKey[14], pbKey[15]);
	}

	Original(CXCabCryptHelper_p, shahead, unk1, pbKey, cbKey);
}

VOID SetupHooks()
{
	Byrom_Dbg("Applying hooks");

	// Catch most content here
	XOnlineFindMediaInstanceUrlsDetour = Detour((void*)(bIsDevkit ? XOnlineFindMediaInstanceUrls_Addr_DEVKIT : XOnlineFindMediaInstanceUrls_Addr_RETAIL), XOnlineFindMediaInstanceUrlsHook);
	XOnlineFindMediaInstanceUrlsDetour.Install();

	// Catch title update with these
	XAMXHttpOpenRequestUsingMemoryDetour = Detour((void*)(bIsDevkit ? XAM_XHttpOpenRequestUsingMemory_Addr_DEVKIT : XAM_XHttpOpenRequestUsingMemory_Addr_RETAIL), XAMXHttpOpenRequestUsingMemoryHook);
	XAMXHttpOpenRequestUsingMemoryDetour.Install();

	InitializeDecryptionDetour = Detour((void*)(bIsDevkit ? InitializeDecryption_Addr_DEVKIT : InitializeDecryption_Addr_RETAIL), InitializeDecryptionHook);
	InitializeDecryptionDetour.Install();
}

VOID RemoveHooks()
{
	Byrom_Dbg("Removing hooks");

	XOnlineFindMediaInstanceUrlsDetour.Remove();
	XAMXHttpOpenRequestUsingMemoryDetour.Remove();
	InitializeDecryptionDetour.Remove();
}



