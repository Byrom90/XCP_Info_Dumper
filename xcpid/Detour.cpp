#include "stdafx.h"
#include "Detour.h"

BYTE   Detour::TrampolineBuffer[200 * 20] = {};
SIZE_T Detour::TrampolineSize = 0;