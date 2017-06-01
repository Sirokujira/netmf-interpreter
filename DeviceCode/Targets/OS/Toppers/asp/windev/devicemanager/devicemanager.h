

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __devicemanager_h__
#define __devicemanager_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IInformation_FWD_DEFINED__
#define __IInformation_FWD_DEFINED__
typedef interface IInformation IInformation;

#endif 	/* __IInformation_FWD_DEFINED__ */


#ifndef __IDevice_FWD_DEFINED__
#define __IDevice_FWD_DEFINED__
typedef interface IDevice IDevice;

#endif 	/* __IDevice_FWD_DEFINED__ */


#ifndef ___IDeviceEvents_FWD_DEFINED__
#define ___IDeviceEvents_FWD_DEFINED__
typedef interface _IDeviceEvents _IDeviceEvents;

#endif 	/* ___IDeviceEvents_FWD_DEFINED__ */


#ifndef __IKernel_FWD_DEFINED__
#define __IKernel_FWD_DEFINED__
typedef interface IKernel IKernel;

#endif 	/* __IKernel_FWD_DEFINED__ */


#ifndef ___IKernelEvents_FWD_DEFINED__
#define ___IKernelEvents_FWD_DEFINED__
typedef interface _IKernelEvents _IKernelEvents;

#endif 	/* ___IKernelEvents_FWD_DEFINED__ */


#ifndef ___IInformationEvents_FWD_DEFINED__
#define ___IInformationEvents_FWD_DEFINED__
typedef interface _IInformationEvents _IInformationEvents;

#endif 	/* ___IInformationEvents_FWD_DEFINED__ */


#ifndef __IKernelLog_FWD_DEFINED__
#define __IKernelLog_FWD_DEFINED__
typedef interface IKernelLog IKernelLog;

#endif 	/* __IKernelLog_FWD_DEFINED__ */


#ifndef ___IKernelLogEvents_FWD_DEFINED__
#define ___IKernelLogEvents_FWD_DEFINED__
typedef interface _IKernelLogEvents _IKernelLogEvents;

#endif 	/* ___IKernelLogEvents_FWD_DEFINED__ */


#ifndef __Device_FWD_DEFINED__
#define __Device_FWD_DEFINED__

#ifdef __cplusplus
typedef class Device Device;
#else
typedef struct Device Device;
#endif /* __cplusplus */

#endif 	/* __Device_FWD_DEFINED__ */


#ifndef __Information_FWD_DEFINED__
#define __Information_FWD_DEFINED__

#ifdef __cplusplus
typedef class Information Information;
#else
typedef struct Information Information;
#endif /* __cplusplus */

#endif 	/* __Information_FWD_DEFINED__ */


#ifndef __Kernel_FWD_DEFINED__
#define __Kernel_FWD_DEFINED__

#ifdef __cplusplus
typedef class Kernel Kernel;
#else
typedef struct Kernel Kernel;
#endif /* __cplusplus */

#endif 	/* __Kernel_FWD_DEFINED__ */


#ifndef __KernelLog_FWD_DEFINED__
#define __KernelLog_FWD_DEFINED__

#ifdef __cplusplus
typedef class KernelLog KernelLog;
#else
typedef struct KernelLog KernelLog;
#endif /* __cplusplus */

#endif 	/* __KernelLog_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IInformation_INTERFACE_DEFINED__
#define __IInformation_INTERFACE_DEFINED__

/* interface IInformation */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IInformation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0FDFFA99-68D5-4BE0-8984-FB6A3A2C0AAC")
    IInformation : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IInformationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInformation * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInformation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInformation * This);
        
        END_INTERFACE
    } IInformationVtbl;

    interface IInformation
    {
        CONST_VTBL struct IInformationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInformation_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInformation_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInformation_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInformation_INTERFACE_DEFINED__ */


#ifndef __IDevice_INTERFACE_DEFINED__
#define __IDevice_INTERFACE_DEFINED__

/* interface IDevice */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6575FAAB-8750-42D2-ADDD-4BE764AA2767")
    IDevice : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsValid( 
            /* [out] */ BOOL *valid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDeviceName( 
            /* [in] */ BSTR devname) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Map( 
            /* [in] */ unsigned long address,
            /* [in] */ unsigned long size) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Unmap( 
            /* [in] */ unsigned long address) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RaiseInterrupt( 
            /* [in] */ unsigned long inhno) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDevice * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDevice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDevice * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsValid )( 
            IDevice * This,
            /* [out] */ BOOL *valid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetDeviceName )( 
            IDevice * This,
            /* [in] */ BSTR devname);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Map )( 
            IDevice * This,
            /* [in] */ unsigned long address,
            /* [in] */ unsigned long size);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Unmap )( 
            IDevice * This,
            /* [in] */ unsigned long address);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RaiseInterrupt )( 
            IDevice * This,
            /* [in] */ unsigned long inhno);
        
        END_INTERFACE
    } IDeviceVtbl;

    interface IDevice
    {
        CONST_VTBL struct IDeviceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDevice_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDevice_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDevice_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDevice_IsValid(This,valid)	\
    ( (This)->lpVtbl -> IsValid(This,valid) ) 

#define IDevice_SetDeviceName(This,devname)	\
    ( (This)->lpVtbl -> SetDeviceName(This,devname) ) 

#define IDevice_Map(This,address,size)	\
    ( (This)->lpVtbl -> Map(This,address,size) ) 

#define IDevice_Unmap(This,address)	\
    ( (This)->lpVtbl -> Unmap(This,address) ) 

#define IDevice_RaiseInterrupt(This,inhno)	\
    ( (This)->lpVtbl -> RaiseInterrupt(This,inhno) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDevice_INTERFACE_DEFINED__ */


#ifndef ___IDeviceEvents_INTERFACE_DEFINED__
#define ___IDeviceEvents_INTERFACE_DEFINED__

/* interface _IDeviceEvents */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID__IDeviceEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DA93137D-FB52-4421-B95D-9077340AD03B")
    _IDeviceEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnRead( 
            /* [in] */ long address,
            /* [in] */ long sz,
            /* [length_is][size_is][out] */ byte data[  ]) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnWrite( 
            /* [in] */ long address,
            /* [in] */ long sz,
            /* [length_is][size_is][in] */ byte data[  ]) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnKernelStart( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnKernelExit( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct _IDeviceEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IDeviceEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IDeviceEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IDeviceEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnRead )( 
            _IDeviceEvents * This,
            /* [in] */ long address,
            /* [in] */ long sz,
            /* [length_is][size_is][out] */ byte data[  ]);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnWrite )( 
            _IDeviceEvents * This,
            /* [in] */ long address,
            /* [in] */ long sz,
            /* [length_is][size_is][in] */ byte data[  ]);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnKernelStart )( 
            _IDeviceEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnKernelExit )( 
            _IDeviceEvents * This);
        
        END_INTERFACE
    } _IDeviceEventsVtbl;

    interface _IDeviceEvents
    {
        CONST_VTBL struct _IDeviceEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IDeviceEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IDeviceEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IDeviceEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IDeviceEvents_OnRead(This,address,sz,data)	\
    ( (This)->lpVtbl -> OnRead(This,address,sz,data) ) 

#define _IDeviceEvents_OnWrite(This,address,sz,data)	\
    ( (This)->lpVtbl -> OnWrite(This,address,sz,data) ) 

#define _IDeviceEvents_OnKernelStart(This)	\
    ( (This)->lpVtbl -> OnKernelStart(This) ) 

#define _IDeviceEvents_OnKernelExit(This)	\
    ( (This)->lpVtbl -> OnKernelExit(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___IDeviceEvents_INTERFACE_DEFINED__ */


#ifndef __IKernel_INTERFACE_DEFINED__
#define __IKernel_INTERFACE_DEFINED__

/* interface IKernel */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IKernel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D3E42099-3FDD-4A78-BDBD-4E57D362F5ED")
    IKernel : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Read( 
            /* [in] */ unsigned long address,
            /* [in] */ unsigned long sz,
            /* [length_is][size_is][out] */ byte data[  ]) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsValid( 
            /* [out] */ BOOL *valid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Write( 
            /* [in] */ unsigned long address,
            /* [in] */ unsigned long sz,
            /* [length_is][size_is][in] */ byte data[  ]) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnLogEvent( 
            /* [in] */ long sz,
            /* [length_is][size_is][in] */ byte data[  ]) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IKernelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IKernel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IKernel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IKernel * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Read )( 
            IKernel * This,
            /* [in] */ unsigned long address,
            /* [in] */ unsigned long sz,
            /* [length_is][size_is][out] */ byte data[  ]);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsValid )( 
            IKernel * This,
            /* [out] */ BOOL *valid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Write )( 
            IKernel * This,
            /* [in] */ unsigned long address,
            /* [in] */ unsigned long sz,
            /* [length_is][size_is][in] */ byte data[  ]);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLogEvent )( 
            IKernel * This,
            /* [in] */ long sz,
            /* [length_is][size_is][in] */ byte data[  ]);
        
        END_INTERFACE
    } IKernelVtbl;

    interface IKernel
    {
        CONST_VTBL struct IKernelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IKernel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IKernel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IKernel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IKernel_Read(This,address,sz,data)	\
    ( (This)->lpVtbl -> Read(This,address,sz,data) ) 

#define IKernel_IsValid(This,valid)	\
    ( (This)->lpVtbl -> IsValid(This,valid) ) 

#define IKernel_Write(This,address,sz,data)	\
    ( (This)->lpVtbl -> Write(This,address,sz,data) ) 

#define IKernel_OnLogEvent(This,sz,data)	\
    ( (This)->lpVtbl -> OnLogEvent(This,sz,data) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IKernel_INTERFACE_DEFINED__ */


#ifndef ___IKernelEvents_INTERFACE_DEFINED__
#define ___IKernelEvents_INTERFACE_DEFINED__

/* interface _IKernelEvents */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID__IKernelEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1353969D-E84F-463F-B211-337E9BCFB99E")
    _IKernelEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnInterruptRequest( 
            /* [in] */ unsigned long inhno) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct _IKernelEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IKernelEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IKernelEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IKernelEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnInterruptRequest )( 
            _IKernelEvents * This,
            /* [in] */ unsigned long inhno);
        
        END_INTERFACE
    } _IKernelEventsVtbl;

    interface _IKernelEvents
    {
        CONST_VTBL struct _IKernelEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IKernelEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IKernelEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IKernelEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IKernelEvents_OnInterruptRequest(This,inhno)	\
    ( (This)->lpVtbl -> OnInterruptRequest(This,inhno) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___IKernelEvents_INTERFACE_DEFINED__ */


#ifndef ___IInformationEvents_INTERFACE_DEFINED__
#define ___IInformationEvents_INTERFACE_DEFINED__

/* interface _IInformationEvents */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID__IInformationEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11E125BE-FC60-4DC9-8393-DC393B556D06")
    _IInformationEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDeviceChanged( 
            short reason,
            long devid,
            long extra) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnKernelChanged( 
            short reason) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct _IInformationEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IInformationEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IInformationEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IInformationEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDeviceChanged )( 
            _IInformationEvents * This,
            short reason,
            long devid,
            long extra);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnKernelChanged )( 
            _IInformationEvents * This,
            short reason);
        
        END_INTERFACE
    } _IInformationEventsVtbl;

    interface _IInformationEvents
    {
        CONST_VTBL struct _IInformationEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IInformationEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IInformationEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IInformationEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IInformationEvents_OnDeviceChanged(This,reason,devid,extra)	\
    ( (This)->lpVtbl -> OnDeviceChanged(This,reason,devid,extra) ) 

#define _IInformationEvents_OnKernelChanged(This,reason)	\
    ( (This)->lpVtbl -> OnKernelChanged(This,reason) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___IInformationEvents_INTERFACE_DEFINED__ */


#ifndef __IKernelLog_INTERFACE_DEFINED__
#define __IKernelLog_INTERFACE_DEFINED__

/* interface IKernelLog */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IKernelLog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("395F900A-AC7E-4A78-9BC1-EE5EF76254FF")
    IKernelLog : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IKernelLogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IKernelLog * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IKernelLog * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IKernelLog * This);
        
        END_INTERFACE
    } IKernelLogVtbl;

    interface IKernelLog
    {
        CONST_VTBL struct IKernelLogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IKernelLog_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IKernelLog_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IKernelLog_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IKernelLog_INTERFACE_DEFINED__ */


#ifndef ___IKernelLogEvents_INTERFACE_DEFINED__
#define ___IKernelLogEvents_INTERFACE_DEFINED__

/* interface _IKernelLogEvents */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID__IKernelLogEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35E35399-55ED-45FC-8F0B-4A1BC6CEA3F0")
    _IKernelLogEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnKernelStart( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnKernelExit( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnLogEvent( 
            /* [in] */ long sz,
            /* [length_is][size_is][in] */ byte data[  ]) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct _IKernelLogEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IKernelLogEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IKernelLogEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IKernelLogEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnKernelStart )( 
            _IKernelLogEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnKernelExit )( 
            _IKernelLogEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLogEvent )( 
            _IKernelLogEvents * This,
            /* [in] */ long sz,
            /* [length_is][size_is][in] */ byte data[  ]);
        
        END_INTERFACE
    } _IKernelLogEventsVtbl;

    interface _IKernelLogEvents
    {
        CONST_VTBL struct _IKernelLogEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IKernelLogEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IKernelLogEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IKernelLogEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IKernelLogEvents_OnKernelStart(This)	\
    ( (This)->lpVtbl -> OnKernelStart(This) ) 

#define _IKernelLogEvents_OnKernelExit(This)	\
    ( (This)->lpVtbl -> OnKernelExit(This) ) 

#define _IKernelLogEvents_OnLogEvent(This,sz,data)	\
    ( (This)->lpVtbl -> OnLogEvent(This,sz,data) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___IKernelLogEvents_INTERFACE_DEFINED__ */



#ifndef __ATLDEVICEMANAGERLib_LIBRARY_DEFINED__
#define __ATLDEVICEMANAGERLib_LIBRARY_DEFINED__

/* library ATLDEVICEMANAGERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ATLDEVICEMANAGERLib;

EXTERN_C const CLSID CLSID_Device;

#ifdef __cplusplus

class DECLSPEC_UUID("FEE2A68B-7F98-40E0-9853-183EE68BC7F8")
Device;
#endif

EXTERN_C const CLSID CLSID_Information;

#ifdef __cplusplus

class DECLSPEC_UUID("D7AAF617-008A-4961-BB51-041CFD490ED3")
Information;
#endif

EXTERN_C const CLSID CLSID_Kernel;

#ifdef __cplusplus

class DECLSPEC_UUID("51789667-9F20-40AF-AF7F-9856325DFB0B")
Kernel;
#endif

EXTERN_C const CLSID CLSID_KernelLog;

#ifdef __cplusplus

class DECLSPEC_UUID("4BD327FC-9E4A-4A5D-9503-27C979A8E802")
KernelLog;
#endif
#endif /* __ATLDEVICEMANAGERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


