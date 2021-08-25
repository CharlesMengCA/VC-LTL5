﻿
#include <corecrt.h>
#include <internal_shared.h>
#include <ehdata.h>
#include <float.h>
#include <mbstring.h>
#include <locale.h>
#include <corecrt_io.h>
#include <corecrt_wio.h>
#include <corecrt_wtime.h>
#include <time.h>
#include <intrin.h> 
#include <stdio.h>
#include <conio.h>

#if WindowsTargetPlatformMinVersion < WindowsTargetPlatformWindows6

#if defined _X86_

extern "C" __declspec(dllimport) EXCEPTION_DISPOSITION __CxxFrameHandler(
	EHExceptionRecord  *pExcept,
	EHRegistrationNode *pRN,
	void *pContext,
	DispatcherContext  *pDC
	);

extern "C" __declspec(naked) DECLSPEC_GUARD_SUPPRESS EXCEPTION_DISPOSITION __cdecl __CxxFrameHandler3(
	/*
	EAX=FuncInfo   *pFuncInfo,          // Static information for this frame
	*/
	EHExceptionRecord  *pExcept,        // Information for this exception
	EHRegistrationNode *pRN,            // Dynamic information for this frame
	void               *pContext,       // Context info (we don't care what's in it)
	DispatcherContext  *pDC             // More dynamic info for this frame (ignored on Intel)
	)
{
	//FuncInfo   *pFuncInfo;
	_s_FuncInfo FuncInfo_downlevel;

	__asm
	{
		//
		// Standard function prolog
		//
		push    ebp
		mov     ebp, esp
		sub     esp, 0x24
		push    ebx
		push    esi
		push    edi
		cld             // A bit of paranoia -- Our code-gen assumes this

		//
		// Save the extra parameter
		//
		mov     esi, eax
		mov     ecx, 9
		lea     edi, FuncInfo_downlevel
		rep movsd
	}

	FuncInfo_downlevel.magicNumber = EH_MAGIC_NUMBER1;

	__asm
	{
		lea eax, FuncInfo_downlevel
	}

	__CxxFrameHandler(pExcept, pRN, pContext, pDC);

	__asm
	{
		pop     edi
		pop     esi
		pop     ebx
		mov     esp, ebp
		pop     ebp
		retn
	}
}
#elif defined _AMD64_

extern "C" __declspec(dllimport) EXCEPTION_DISPOSITION __CxxFrameHandler(
	EHExceptionRecord  *pExcept,
	EHRegistrationNode RN,
	CONTEXT *pContext,
	DispatcherContext  *pDC
	);

static volatile long ProtectFlag = 0;

extern "C" DECLSPEC_GUARD_SUPPRESS EXCEPTION_DISPOSITION __cdecl __CxxFrameHandler3(
	EHExceptionRecord  *pExcept,         // Information for this exception
	EHRegistrationNode RN,               // Dynamic information for this frame
	CONTEXT            *pContext,        // Context info
	DispatcherContext  *pDC              // More dynamic info for this frame
	)
{
	auto pFuncInfo = (_s_FuncInfo*)(pDC->ImageBase + *(DWORD*)pDC->HandlerData);

	if (pExcept->ExceptionCode == EH_EXCEPTION_NUMBER && pFuncInfo->magicNumber <= EH_MAGIC_NUMBER3 && pFuncInfo->magicNumber > EH_MAGIC_NUMBER1)
	{

		while (InterlockedExchange(&ProtectFlag, 1) == 1)
		{
			Sleep(10);
		}

		DWORD OldProtect;

		//开启修改magicNumber
		if (VirtualProtect(pFuncInfo, 4, PAGE_EXECUTE_READWRITE, &OldProtect))
		{
			pFuncInfo->magicNumber = EH_MAGIC_NUMBER1;

			VirtualProtect(pFuncInfo, 4, OldProtect, &OldProtect);
		}

		InterlockedExchange(&ProtectFlag, 0);
	}

	return __CxxFrameHandler(pExcept, RN, pContext, pDC);
}
#endif

_LCRT_DEFINE_IAT_SYMBOL(__CxxFrameHandler3);

#endif