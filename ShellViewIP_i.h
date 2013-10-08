

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Oct 08 10:33:58 2013
 */
/* Compiler settings for ShellViewIP.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
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

#ifndef __ShellViewIP_i_h__
#define __ShellViewIP_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIPViewer_FWD_DEFINED__
#define __IIPViewer_FWD_DEFINED__
typedef interface IIPViewer IIPViewer;
#endif 	/* __IIPViewer_FWD_DEFINED__ */


#ifndef __IPViewer_FWD_DEFINED__
#define __IPViewer_FWD_DEFINED__

#ifdef __cplusplus
typedef class IPViewer IPViewer;
#else
typedef struct IPViewer IPViewer;
#endif /* __cplusplus */

#endif 	/* __IPViewer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IIPViewer_INTERFACE_DEFINED__
#define __IIPViewer_INTERFACE_DEFINED__

/* interface IIPViewer */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IIPViewer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C1605A03-256A-405A-81C8-13E43011A0ED")
    IIPViewer : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IIPViewerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIPViewer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIPViewer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIPViewer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIPViewer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIPViewer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIPViewer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIPViewer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IIPViewerVtbl;

    interface IIPViewer
    {
        CONST_VTBL struct IIPViewerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIPViewer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIPViewer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIPViewer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIPViewer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIPViewer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIPViewer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIPViewer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIPViewer_INTERFACE_DEFINED__ */



#ifndef __ShellViewIPLib_LIBRARY_DEFINED__
#define __ShellViewIPLib_LIBRARY_DEFINED__

/* library ShellViewIPLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ShellViewIPLib;

EXTERN_C const CLSID CLSID_IPViewer;

#ifdef __cplusplus

class DECLSPEC_UUID("C881A3F1-F127-41D0-A0C6-6598B6A105A9")
IPViewer;
#endif
#endif /* __ShellViewIPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


