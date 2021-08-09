﻿#include <framework.h>
#include <Windows.h>
#pragma pack(push)
#pragma pack()

namespace
{
	typedef _Return_type_success_(return >= 0) LONG NTSTATUS;

	typedef struct _UNICODE_STRING {
		USHORT Length;
		USHORT MaximumLength;
		PWSTR  Buffer;
	} UNICODE_STRING, * PUNICODE_STRING;
	typedef const UNICODE_STRING* PCUNICODE_STRING;

	typedef struct _PEB_LDR_DATA* PPEB_LDR_DATA;
	typedef struct _RTL_USER_PROCESS_PARAMETERS* PRTL_USER_PROCESS_PARAMETERS;

	typedef struct _PEB
	{
		BOOLEAN InheritedAddressSpace;
		BOOLEAN ReadImageFileExecOptions;
		BOOLEAN BeingDebugged;
		union
		{
			BOOLEAN BitField;
			struct
			{
				BOOLEAN ImageUsesLargePages : 1;
				BOOLEAN IsProtectedProcess : 1;
				BOOLEAN IsImageDynamicallyRelocated : 1;
				BOOLEAN SkipPatchingUser32Forwarders : 1;
				BOOLEAN IsPackagedProcess : 1;
				BOOLEAN IsAppContainer : 1;
				BOOLEAN IsProtectedProcessLight : 1;
				BOOLEAN IsLongPathAwareProcess : 1;
			};
		};

		HANDLE Mutant;

		PVOID ImageBaseAddress;
		PPEB_LDR_DATA Ldr;
		PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
		PVOID SubSystemData;
		PVOID ProcessHeap;
		PRTL_CRITICAL_SECTION FastPebLock;
		PVOID AtlThunkSListPtr;
		PVOID IFEOKey;
		union
		{
			ULONG CrossProcessFlags;
			struct
			{
				ULONG ProcessInJob : 1;
				ULONG ProcessInitializing : 1;
				ULONG ProcessUsingVEH : 1;
				ULONG ProcessUsingVCH : 1;
				ULONG ProcessUsingFTH : 1;
				ULONG ReservedBits0 : 27;
			};
		};
		union
		{
			PVOID KernelCallbackTable;
			PVOID UserSharedInfoPtr;
		};
		ULONG SystemReserved[1];
		ULONG AtlThunkSListPtr32;
		PVOID ApiSetMap;
		ULONG TlsExpansionCounter;
		PVOID TlsBitmap;
		ULONG TlsBitmapBits[2];
		PVOID ReadOnlySharedMemoryBase;
		PVOID HotpatchInformation;
		PVOID* ReadOnlyStaticServerData;
		PVOID AnsiCodePageData;
		PVOID OemCodePageData;
		PVOID UnicodeCaseTableData;

		ULONG NumberOfProcessors;
		ULONG NtGlobalFlag;

		LARGE_INTEGER CriticalSectionTimeout;
		SIZE_T HeapSegmentReserve;
		SIZE_T HeapSegmentCommit;
		SIZE_T HeapDeCommitTotalFreeThreshold;
		SIZE_T HeapDeCommitFreeBlockThreshold;

		ULONG NumberOfHeaps;
		ULONG MaximumNumberOfHeaps;
		PVOID* ProcessHeaps;

		PVOID GdiSharedHandleTable;
		PVOID ProcessStarterHelper;
		ULONG GdiDCAttributeList;

		PRTL_CRITICAL_SECTION LoaderLock;

		ULONG OSMajorVersion;
		ULONG OSMinorVersion;
		USHORT OSBuildNumber;
		USHORT OSCSDVersion;
		ULONG OSPlatformId;
		ULONG ImageSubsystem;
		ULONG ImageSubsystemMajorVersion;
		ULONG ImageSubsystemMinorVersion;
		ULONG_PTR ActiveProcessAffinityMask;
#ifdef _AMD64_
		ULONG GdiHandleBuffer[60];
#else
		ULONG GdiHandleBuffer[34];
#endif
		PVOID PostProcessInitRoutine;

		PVOID TlsExpansionBitmap;
		ULONG TlsExpansionBitmapBits[32];

		ULONG SessionId;

		ULARGE_INTEGER AppCompatFlags;
		ULARGE_INTEGER AppCompatFlagsUser;
		PVOID pShimData;
		PVOID AppCompatInfo;

		UNICODE_STRING CSDVersion;

		PVOID ActivationContextData;
		PVOID ProcessAssemblyStorageMap;
		PVOID SystemDefaultActivationContextData;
		PVOID SystemAssemblyStorageMap;

		SIZE_T MinimumStackCommit;

		PVOID* FlsCallback;
		LIST_ENTRY FlsListHead;
		PVOID FlsBitmap;
		ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
		ULONG FlsHighIndex;

		PVOID WerRegistrationData;
		PVOID WerShipAssertPtr;
		PVOID pContextData;
		PVOID pImageHeaderHash;
		union
		{
			ULONG TracingFlags;
			struct
			{
				ULONG HeapTracingEnabled : 1;
				ULONG CritSecTracingEnabled : 1;
				ULONG LibLoaderTracingEnabled : 1;
				ULONG SpareTracingBits : 29;
			};
		};
		ULONGLONG CsrServerReadOnlySharedMemoryBase;
		PVOID TppWorkerpListLock;
		LIST_ENTRY TppWorkerpList;
		PVOID WaitOnAddressHashTable[128];
	} PEB, * PPEB;

	typedef struct _TEB_ACTIVE_FRAME* PTEB_ACTIVE_FRAME;

	typedef struct _CLIENT_ID {
		HANDLE UniqueProcess;
		HANDLE UniqueThread;
	} CLIENT_ID, * PCLIENT_ID;

	typedef struct _GDI_TEB_BATCH
	{
		ULONG Offset;
		HDC hdc;
		ULONG buffer[310];
	} GDI_TEB_BATCH;

	typedef struct _TEB
	{
		NT_TIB NtTib;

		PVOID EnvironmentPointer;
		CLIENT_ID ClientId;
		PVOID ActiveRpcHandle;
		PVOID ThreadLocalStoragePointer;
		PPEB ProcessEnvironmentBlock;

		ULONG LastErrorValue;
		ULONG CountOfOwnedCriticalSections;
		PVOID CsrClientThread;
		PVOID Win32ThreadInfo;
		ULONG User32Reserved[26];
		ULONG UserReserved[5];
		PVOID WOW32Reserved;
		LCID CurrentLocale;
		ULONG FpSoftwareStatusRegister;
		PVOID ReservedForDebuggerInstrumentation[16];
		PVOID SystemReserved1[37];
		UCHAR WorkingOnBehalfTicket[8];
		NTSTATUS ExceptionCode;

		PVOID ActivationContextStackPointer;
		ULONG_PTR InstrumentationCallbackSp;
		ULONG_PTR InstrumentationCallbackPreviousPc;
		ULONG_PTR InstrumentationCallbackPreviousSp;
		ULONG TxFsContext;

		BOOLEAN InstrumentationCallbackDisabled;
		GDI_TEB_BATCH GdiTebBatch;
		CLIENT_ID RealClientId;
		HANDLE GdiCachedProcessHandle;
		ULONG GdiClientPID;
		ULONG GdiClientTID;
		PVOID GdiThreadLocalInfo;
		ULONG_PTR Win32ClientInfo[62];
		PVOID glDispatchTable[233];
		ULONG_PTR glReserved1[29];
		PVOID glReserved2;
		PVOID glSectionInfo;
		PVOID glSection;
		PVOID glTable;
		PVOID glCurrentRC;
		PVOID glContext;

		NTSTATUS LastStatusValue;
		UNICODE_STRING StaticUnicodeString;
		WCHAR StaticUnicodeBuffer[261];

		PVOID DeallocationStack;
		PVOID TlsSlots[64];
		LIST_ENTRY TlsLinks;

		PVOID Vdm;
		PVOID ReservedForNtRpc;
		PVOID DbgSsReserved[2];

		ULONG HardErrorMode;
#ifdef _WIN64
		PVOID Instrumentation[11];
#else
		PVOID Instrumentation[9];
#endif
		GUID ActivityId;

		PVOID SubProcessTag;
		PVOID PerflibData;
		PVOID EtwTraceData;
		PVOID WinSockData;
		ULONG GdiBatchCount;

		union
		{
			PROCESSOR_NUMBER CurrentIdealProcessor;
			ULONG IdealProcessorValue;
			struct
			{
				UCHAR ReservedPad0;
				UCHAR ReservedPad1;
				UCHAR ReservedPad2;
				UCHAR IdealProcessor;
			};
		};

		ULONG GuaranteedStackBytes;
		PVOID ReservedForPerf;
		PVOID ReservedForOle;
		ULONG WaitingOnLoaderLock;
		PVOID SavedPriorityState;
		ULONG_PTR ReservedForCodeCoverage;
		PVOID ThreadPoolData;
		PVOID* TlsExpansionSlots;
#ifdef _WIN64
		PVOID DeallocationBStore;
		PVOID BStoreLimit;
#endif
		ULONG MuiGeneration;
		ULONG IsImpersonating;
		PVOID NlsCache;
		PVOID pShimData;
		USHORT HeapVirtualAffinity;
		USHORT LowFragHeapDataSlot;
		HANDLE CurrentTransactionHandle;
		PTEB_ACTIVE_FRAME ActiveFrame;
		PVOID FlsData;

		PVOID PreferredLanguages;
		PVOID UserPrefLanguages;
		PVOID MergedPrefLanguages;
		ULONG MuiImpersonation;

		union
		{
			USHORT CrossTebFlags;
			USHORT SpareCrossTebBits : 16;
		};
		union
		{
			USHORT SameTebFlags;
			struct
			{
				USHORT SafeThunkCall : 1;
				USHORT InDebugPrint : 1;
				USHORT HasFiberData : 1;
				USHORT SkipThreadAttach : 1;
				USHORT WerInShipAssertCode : 1;
				USHORT RanProcessInit : 1;
				USHORT ClonedThread : 1;
				USHORT SuppressDebugMsg : 1;
				USHORT DisableUserStackWalk : 1;
				USHORT RtlExceptionAttached : 1;
				USHORT InitialThread : 1;
				USHORT SessionAware : 1;
				USHORT LoadOwner : 1;
				USHORT LoaderWorker : 1;
				USHORT SpareSameTebBits : 2;
			};
		};

		PVOID TxnScopeEnterCallback;
		PVOID TxnScopeExitCallback;
		PVOID TxnScopeContext;
		ULONG LockCount;
		LONG WowTebOffset;
		PVOID ResourceRetValue;
		PVOID ReservedForWdf;
		ULONGLONG ReservedForCrt;
		GUID EffectiveContainerId;
	} TEB, * PTEB;

}


#pragma pack(pop)

EXTERN_C unsigned __cdecl __LTL_GetOsMinVersion()
{
	auto pPeb = ((TEB*)NtCurrentTeb())->ProcessEnvironmentBlock;

	return MakeMiniVersion(pPeb->OSMajorVersion, pPeb->OSMinorVersion);
}