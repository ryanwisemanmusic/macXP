#ifndef DDK_DEFS_H
#define DDK_DEFS_H

#include "win32defs.h"

/* Fallback scalar types when win32defs is excluded by platform guards. */
#ifndef VOID
#define VOID void
#endif

#ifndef UCHAR
typedef unsigned char UCHAR;
#endif

#ifndef USHORT
typedef unsigned short USHORT;
#endif

#ifndef ULONG
typedef unsigned long ULONG;
#endif

#ifndef LONG
typedef long LONG;
#endif

#ifndef PVOID
typedef void *PVOID;
#endif

#ifndef LUID
typedef struct _LUID {
	ULONG LowPart;
	LONG HighPart;
} LUID, *PLUID;
#endif

#ifndef LUID_AND_ATTRIBUTES
typedef struct _LUID_AND_ATTRIBUTES {
	LUID Luid;
	ULONG Attributes;
} LUID_AND_ATTRIBUTES, *PLUID_AND_ATTRIBUTES;
#endif

#ifndef PACCESS_TOKEN
typedef PVOID PACCESS_TOKEN;
#endif

#ifndef SECURITY_IMPERSONATION_LEVEL
typedef enum _SECURITY_IMPERSONATION_LEVEL {
	SecurityAnonymous,
	SecurityIdentification,
	SecurityImpersonation,
	SecurityDelegation
} SECURITY_IMPERSONATION_LEVEL, *PSECURITY_IMPERSONATION_LEVEL;
#endif

#ifndef POBJECT_ATTRIBUTES
typedef struct _OBJECT_ATTRIBUTES OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;
#endif

#ifndef PSECURITY_DESCRIPTOR
typedef struct _SECURITY_DESCRIPTOR SECURITY_DESCRIPTOR, *PSECURITY_DESCRIPTOR;
#endif

#ifndef PGENERIC_MAPPING
typedef struct _GENERIC_MAPPING {
	ULONG GenericRead;
	ULONG GenericWrite;
	ULONG GenericExecute;
	ULONG GenericAll;
} GENERIC_MAPPING, *PGENERIC_MAPPING;
#endif

#ifndef PPRIVILEGE_SET
#ifndef ANYSIZE_ARRAY
#define ANYSIZE_ARRAY 1
#endif
typedef struct _PRIVILEGE_SET {
	ULONG PrivilegeCount;
	ULONG Control;
	LUID_AND_ATTRIBUTES Privilege[ANYSIZE_ARRAY];
} PRIVILEGE_SET, *PPRIVILEGE_SET;
#endif

#ifndef PPRIVELEGE_SET
typedef PPRIVILEGE_SET PPRIVELEGE_SET;
#endif

#ifndef PRIVELEGE_SET
typedef PRIVILEGE_SET PRIVELEGE_SET;
#endif

#ifndef PKFLOATING_SAVE
typedef struct _FLOATING_SAVE FLOATING_SAVE, *PKFLOATING_SAVE;
#endif

#ifndef NTSTATUS
typedef long NTSTATUS;
#endif

#ifndef PNTSTATUS
typedef NTSTATUS *PNTSTATUS;
#endif

#ifndef SECURITY_INFORMATION
typedef ULONG SECURITY_INFORMATION;
#endif

#ifndef LCID
typedef ULONG LCID;
#endif

#ifndef PSINGLE_LIST_ENTRY
typedef struct _SINGLE_LIST_ENTRY {
	struct _SINGLE_LIST_ENTRY *Next;
} SINGLE_LIST_ENTRY, *PSINGLE_LIST_ENTRY;
#endif

#ifndef PSLIST_ENTRY
typedef struct _SLIST_ENTRY SLIST_ENTRY, *PSLIST_ENTRY;
#endif

#ifndef SLIST_HEADER
typedef union _SLIST_HEADER {
	ULONGLONG Alignment;
	struct {
		PSINGLE_LIST_ENTRY Next;
		USHORT Depth;
		USHORT Sequence;
	} DUMMYSTRUCTNAME;
} SLIST_HEADER, *PSLIST_HEADER;
#endif

#ifndef SECTION_INHERIT
typedef enum _SECTION_INHERIT {
	ViewShare = 1,
	ViewUnmap = 2
} SECTION_INHERIT;
#endif

#ifndef POWER_ACTION
typedef enum _POWER_ACTION {
	PowerActionNone = 0,
	PowerActionReserved,
	PowerActionSleep,
	PowerActionHibernate,
	PowerActionShutdown,
	PowerActionShutdownReset,
	PowerActionShutdownOff,
	PowerActionWarmEject
} POWER_ACTION, *PPOWER_ACTION;
#endif

#ifndef PSECURITY_QUALITY_OF_SERVICE
typedef struct _SECURITY_QUALITY_OF_SERVICE {
	ULONG Length;
	SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
	UCHAR ContextTrackingMode;
	BOOLEAN EffectiveOnly;
} SECURITY_QUALITY_OF_SERVICE, *PSECURITY_QUALITY_OF_SERVICE;
#endif

#ifndef PSECURITY_QUALIT_OF_SERVICE
typedef PSECURITY_QUALITY_OF_SERVICE PSECURITY_QUALIT_OF_SERVICE;
#endif

#ifndef STDCALL
#define STDCALL __stdcall
#endif

#ifndef DDKAPI
#define DDKAPI STDCALL
#endif

#ifndef DECLSPEC_IMPORT
#define DECLSPEC_IMPORT __declspec(dllimport)
#endif

#ifndef DECLSPEC_EXPORT
#define DECLSPEC_EXPORT __declspec(dllexport)
#endif

#ifndef PHYSICAL_ADDRESS
typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;
#endif

#ifndef SYSTEM_POWER_STATE
typedef enum _SYSTEM_POWER_STATE {
	PowerSystemUnspecified = 0,
	PowerSystemWorking = 1,
	PowerSystemSleeping1 = 2,
	PowerSystemSleeping2 = 3,
	PowerSystemSleeping3 = 4,
	PowerSystemHibernate = 5,
	PowerSystemShutdown = 6,
	PowerSystemMaximum = 7
} SYSTEM_POWER_STATE, *PSYSTEM_POWER_STATE;
#endif

#ifndef DEVICE_POWER_STATE
typedef enum _DEVICE_POWER_STATE {
	PowerDeviceUnspecified = 0,
	PowerDeviceD0 = 1,
	PowerDeviceD1 = 2,
	PowerDeviceD2 = 3,
	PowerDeviceD3 = 4,
	PowerDeviceMaximum = 5
} DEVICE_POWER_STATE, *PDEVICE_POWER_STATE;
#endif

#ifndef PGET_SET_DEVICE_DATA
typedef ULONG DDKAPI
(*PGET_SET_DEVICE_DATA)(
	/*IN*/ PVOID  Context,
	/*IN*/ ULONG  DataType,
	/*IN*/ PVOID  Buffer,
	/*IN*/ ULONG  Offset,
	/*IN*/ ULONG  Length);
#endif

#ifndef FILE_DEVICE_UNKNOWN
#define FILE_DEVICE_UNKNOWN 0x00000022
#endif

#ifndef METHOD_NEITHER
#define METHOD_NEITHER 3
#endif

#ifndef FILE_ANY_ACCESS
#define FILE_ANY_ACCESS 0
#endif

#ifndef CTL_CODE
#define CTL_CODE(DeviceType, Function, Method, Access) \
	(((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method))
#endif

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _SCSI_REQUEST_BLOCK SCSI_REQUEST_BLOCK;
typedef SCSI_REQUEST_BLOCK *PSCSI_REQUEST_BLOCK;

typedef struct _DEVICE_OBJECT DEVICE_OBJECT;
typedef DEVICE_OBJECT *PDEVICE_OBJECT;

typedef struct _IRP IRP;
typedef IRP *PIRP;

typedef struct _DRIVER_OBJECT DRIVER_OBJECT;
typedef DRIVER_OBJECT *PDRIVER_OBJECT;

#ifndef EMULATOR_ACCESS_ENTRY_DEFINED
#define EMULATOR_ACCESS_ENTRY_DEFINED
typedef enum _EMULATOR_PORT_ACCESS_TYPE {
	Uchar,
	Ushort,
	Ulong
} EMULATOR_PORT_ACCESS_TYPE, *PEMULATOR_PORT_ACCESS_TYPE;

typedef struct _EMULATOR_ACCESS_ENTRY {
	ULONG BasePort;
	ULONG NumConsecutivePorts;
	EMULATOR_PORT_ACCESS_TYPE AccessType;
	UCHAR AccessMode;
	UCHAR StringSupport;
	PVOID Routine;
} EMULATOR_ACCESS_ENTRY, *PEMULATOR_ACCESS_ENTRY;
#endif

#ifndef BANKED_SECTION_ROUTINE_DEFINED
#define BANKED_SECTION_ROUTINE_DEFINED
typedef VOID DDKAPI
(*PBANKED_SECTION_ROUTINE)(
	/*IN*/ ULONG ReadBank,
	/*IN*/ ULONG WriteBank,
	/*IN*/ PVOID Context);
#endif

/* Keep compatibility with legacy typo'd alias names used by some headers. */
typedef SCSI_REQUEST_BLOCK SCI_REQUEST_BLOCK;
typedef SCI_REQUEST_BLOCK *PSCI_REQUEST_BLOCK;

#ifndef _GUID_DEFINED
#define _GUID_DEFINED
typedef struct _GUID {
	ULONG Data1;
	USHORT Data2;
	USHORT Data3;
	UCHAR Data4[8];
} GUID;
typedef GUID *LPGUID;
typedef const GUID *LPCGUID;
typedef const GUID *REFGUID;
#endif

#ifndef DEFINE_GUID
#ifdef INITGUID
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	EXTERN_C const GUID name = { (ULONG)(l), (USHORT)(w1), (USHORT)(w2), \
	{ (UCHAR)(b1), (UCHAR)(b2), (UCHAR)(b3), (UCHAR)(b4), \
	  (UCHAR)(b5), (UCHAR)(b6), (UCHAR)(b7), (UCHAR)(b8) } }
#else
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	EXTERN_C const GUID name
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* DDK_DEFS_H */
