#include "stdafx.h"
#include "Utilities.h"

// These are setup to be called by a jrpc2 based pc tool (Not included here)

extern "C" VOID PrintTest()
{
	Byrom_Dbg("[Exported Function] [PrintTest] Hello from xcpid.xex!");
}

extern "C" VOID XNotifyTest()
{
	XNotify(L"[Exported Function] [XNotifyTest] Hello from xcpid.xex!\n");
}

GUID CreateGuid(const byte* data)
{
	const byte redordered[] = { data[3], data[2], data[1], data[0], data[5], data[4], data[7], data[6], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15] };
	GUID guid;
	std::memcpy(&guid, &redordered, sizeof(GUID)); // Assuming no padding!
	return guid;
}

extern "C" VOID SetGUID(byte * guid)
{

	ReplacementGUID = CreateGuid(guid);
	bReplaceGUID = TRUE;
	Byrom_Dbg("[Exported Function] [SetGUID] Replacement Set: %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X - Initiate a download to resolve the matching XCP info.",
		ReplacementGUID.Data1, ReplacementGUID.Data2, ReplacementGUID.Data3, ReplacementGUID.Data4[0], ReplacementGUID.Data4[1],
		ReplacementGUID.Data4[2], ReplacementGUID.Data4[3], ReplacementGUID.Data4[4], ReplacementGUID.Data4[5], ReplacementGUID.Data4[6], ReplacementGUID.Data4[7]);
}

extern "C" VOID DisableReplaceGUID()
{
	Byrom_Dbg("[Exported Function] [DisableReplaceGUID] GUID replacement disabled! XCP info will be resolved for the original item being downloaded.");
	bReplaceGUID = FALSE;
}

extern "C" VOID ToggleAddPrints(BOOL toggle)
{
	Byrom_Dbg("[Exported Function] [ToggleAddPrints] Additional Prints: %s", toggle ? "Enabled" : "Disabled");
	bPrintAddInfo = toggle;
}