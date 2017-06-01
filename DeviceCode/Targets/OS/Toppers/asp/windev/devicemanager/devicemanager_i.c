

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Jun 20 00:05:29 2016
 */
/* Compiler settings for devicemanager.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IInformation,0x0FDFFA99,0x68D5,0x4BE0,0x89,0x84,0xFB,0x6A,0x3A,0x2C,0x0A,0xAC);


MIDL_DEFINE_GUID(IID, IID_IDevice,0x6575FAAB,0x8750,0x42D2,0xAD,0xDD,0x4B,0xE7,0x64,0xAA,0x27,0x67);


MIDL_DEFINE_GUID(IID, IID__IDeviceEvents,0xDA93137D,0xFB52,0x4421,0xB9,0x5D,0x90,0x77,0x34,0x0A,0xD0,0x3B);


MIDL_DEFINE_GUID(IID, IID_IKernel,0xD3E42099,0x3FDD,0x4A78,0xBD,0xBD,0x4E,0x57,0xD3,0x62,0xF5,0xED);


MIDL_DEFINE_GUID(IID, IID__IKernelEvents,0x1353969D,0xE84F,0x463F,0xB2,0x11,0x33,0x7E,0x9B,0xCF,0xB9,0x9E);


MIDL_DEFINE_GUID(IID, IID__IInformationEvents,0x11E125BE,0xFC60,0x4DC9,0x83,0x93,0xDC,0x39,0x3B,0x55,0x6D,0x06);


MIDL_DEFINE_GUID(IID, IID_IKernelLog,0x395F900A,0xAC7E,0x4A78,0x9B,0xC1,0xEE,0x5E,0xF7,0x62,0x54,0xFF);


MIDL_DEFINE_GUID(IID, IID__IKernelLogEvents,0x35E35399,0x55ED,0x45FC,0x8F,0x0B,0x4A,0x1B,0xC6,0xCE,0xA3,0xF0);


MIDL_DEFINE_GUID(IID, LIBID_ATLDEVICEMANAGERLib,0xF15F5272,0x83F3,0x42C3,0x87,0x4C,0xE4,0xFF,0x2B,0x90,0x4A,0xC2);


MIDL_DEFINE_GUID(CLSID, CLSID_Device,0xFEE2A68B,0x7F98,0x40E0,0x98,0x53,0x18,0x3E,0xE6,0x8B,0xC7,0xF8);


MIDL_DEFINE_GUID(CLSID, CLSID_Information,0xD7AAF617,0x008A,0x4961,0xBB,0x51,0x04,0x1C,0xFD,0x49,0x0E,0xD3);


MIDL_DEFINE_GUID(CLSID, CLSID_Kernel,0x51789667,0x9F20,0x40AF,0xAF,0x7F,0x98,0x56,0x32,0x5D,0xFB,0x0B);


MIDL_DEFINE_GUID(CLSID, CLSID_KernelLog,0x4BD327FC,0x9E4A,0x4A5D,0x95,0x03,0x27,0xC9,0x79,0xA8,0xE8,0x02);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



