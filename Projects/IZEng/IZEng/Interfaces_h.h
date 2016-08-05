

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Thu May 12 21:51:40 2011
 */
/* Compiler settings for .\Interfaces.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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

#ifndef __Interfaces_h_h__
#define __Interfaces_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IScreen_FWD_DEFINED__
#define __IScreen_FWD_DEFINED__
typedef interface IScreen IScreen;
#endif 	/* __IScreen_FWD_DEFINED__ */


#ifndef __IInput_FWD_DEFINED__
#define __IInput_FWD_DEFINED__
typedef interface IInput IInput;
#endif 	/* __IInput_FWD_DEFINED__ */


#ifndef __IAnim_FWD_DEFINED__
#define __IAnim_FWD_DEFINED__
typedef interface IAnim IAnim;
#endif 	/* __IAnim_FWD_DEFINED__ */


#ifndef __IDraw_FWD_DEFINED__
#define __IDraw_FWD_DEFINED__
typedef interface IDraw IDraw;
#endif 	/* __IDraw_FWD_DEFINED__ */


#ifndef __IAngledDraw_FWD_DEFINED__
#define __IAngledDraw_FWD_DEFINED__
typedef interface IAngledDraw IAngledDraw;
#endif 	/* __IAngledDraw_FWD_DEFINED__ */


#ifndef __IParams_FWD_DEFINED__
#define __IParams_FWD_DEFINED__
typedef interface IParams IParams;
#endif 	/* __IParams_FWD_DEFINED__ */


#ifndef __IHUD_FWD_DEFINED__
#define __IHUD_FWD_DEFINED__
typedef interface IHUD IHUD;
#endif 	/* __IHUD_FWD_DEFINED__ */


#ifndef __IPhysics_FWD_DEFINED__
#define __IPhysics_FWD_DEFINED__
typedef interface IPhysics IPhysics;
#endif 	/* __IPhysics_FWD_DEFINED__ */


#ifndef __ILinearMovement_FWD_DEFINED__
#define __ILinearMovement_FWD_DEFINED__
typedef interface ILinearMovement ILinearMovement;
#endif 	/* __ILinearMovement_FWD_DEFINED__ */


#ifndef __IAccelMovement_FWD_DEFINED__
#define __IAccelMovement_FWD_DEFINED__
typedef interface IAccelMovement IAccelMovement;
#endif 	/* __IAccelMovement_FWD_DEFINED__ */


#ifndef __IRotation_FWD_DEFINED__
#define __IRotation_FWD_DEFINED__
typedef interface IRotation IRotation;
#endif 	/* __IRotation_FWD_DEFINED__ */


#ifndef __IOrbitMovement_FWD_DEFINED__
#define __IOrbitMovement_FWD_DEFINED__
typedef interface IOrbitMovement IOrbitMovement;
#endif 	/* __IOrbitMovement_FWD_DEFINED__ */


#ifndef __IJump_FWD_DEFINED__
#define __IJump_FWD_DEFINED__
typedef interface IJump IJump;
#endif 	/* __IJump_FWD_DEFINED__ */


#ifndef __IResistForces_FWD_DEFINED__
#define __IResistForces_FWD_DEFINED__
typedef interface IResistForces IResistForces;
#endif 	/* __IResistForces_FWD_DEFINED__ */


#ifndef __VisObj_FWD_DEFINED__
#define __VisObj_FWD_DEFINED__

#ifdef __cplusplus
typedef class VisObj VisObj;
#else
typedef struct VisObj VisObj;
#endif /* __cplusplus */

#endif 	/* __VisObj_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_Interfaces_0000_0000 */
/* [local] */ 


enum __MIDL___MIDL_itf_Interfaces_0000_0000_0001
    {	PLAY_REPEAT	= 0,
	PLAY_ONCE	= ( PLAY_REPEAT + 1 ) 
    } ;

enum __MIDL___MIDL_itf_Interfaces_0000_0000_0002
    {	REACT_NO	= 0,
	REACT_BOUNCE	= ( REACT_NO + 1 ) ,
	REACT_TELEPORT	= ( REACT_BOUNCE + 1 ) ,
	REACT_STOP	= ( REACT_TELEPORT + 1 ) ,
	REACT_RAND_TELEPORT	= ( REACT_STOP + 1 ) 
    } ;

enum __MIDL___MIDL_itf_Interfaces_0000_0000_0003
    {	TYPE_BRAKE	= -1,
	TYPE_NO	= 0,
	TYPE_ACCEL	= 1
    } ;

enum __MIDL___MIDL_itf_Interfaces_0000_0000_0004
    {	TXT_CENTER	= 0x25,
	TXT_HCENTER	= 0x1,
	TXT_VCENTER	= 0x24,
	TXT_LEFT	= 0,
	TXT_RIGHT	= 0x2,
	TXT_TOP	= 0,
	TXT_BOTTOM	= 0x8
    } ;


extern RPC_IF_HANDLE __MIDL_itf_Interfaces_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Interfaces_0000_0000_v0_0_s_ifspec;

#ifndef __IScreen_INTERFACE_DEFINED__
#define __IScreen_INTERFACE_DEFINED__

/* interface IScreen */
/* [uuid][object] */ 


EXTERN_C const IID IID_IScreen;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("095EFAFC-4B15-4ab6-9712-F70CA70C0DCA")
    IScreen : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetDisplay( 
            /* [in] */ HWND hDispWnd,
            /* [in] */ int nWidth,
            /* [in] */ int nHeight,
            /* [in] */ int nRefRate,
            /* [in] */ BOOL bFullscreen,
            /* [in] */ int nFPS) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateScreen( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveCamera( 
            /* [in] */ POINTF *pvecD) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCamera( 
            /* [in] */ POINTF *pptCam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCameraPos( 
            /* [out][in] */ POINTF *pptCam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShutDown( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetScreenRect( 
            /* [out][in] */ RECT *prcScreen) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetScreenWH( 
            /* [out][in] */ POINTF *pptScreen) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCameraRect( 
            /* [out][in] */ RECT *prcCam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCameraRBPos( 
            /* [out][in] */ POINTF *pptCam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWorldBounds( 
            /* [in] */ RECT *prcBounds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWorldBounds( 
            /* [out][in] */ RECT *prcBounds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddFrameTable( 
            /* [out][in] */ int *pnID,
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddBMPFrameTable( 
            /* [out][in] */ int *pnID,
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddAngledTables( 
            /* [out][in] */ int *pnID,
            /* [in] */ int *pidSrcFrameTable,
            /* [in] */ float fTurnAngle,
            /* [in] */ float fNeededAngleOfFirstTable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddOrGetExistingFrameTable( 
            /* [out][in] */ int *pnID,
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddEmptyFrameTable( 
            /* [out][in] */ int *pnID,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparentFill,
            /* [in] */ DWORD dwFillColor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScreenVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScreen * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScreen * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScreen * This);
        
        HRESULT ( STDMETHODCALLTYPE *ResetDisplay )( 
            IScreen * This,
            /* [in] */ HWND hDispWnd,
            /* [in] */ int nWidth,
            /* [in] */ int nHeight,
            /* [in] */ int nRefRate,
            /* [in] */ BOOL bFullscreen,
            /* [in] */ int nFPS);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateScreen )( 
            IScreen * This);
        
        HRESULT ( STDMETHODCALLTYPE *MoveCamera )( 
            IScreen * This,
            /* [in] */ POINTF *pvecD);
        
        HRESULT ( STDMETHODCALLTYPE *SetCamera )( 
            IScreen * This,
            /* [in] */ POINTF *pptCam);
        
        HRESULT ( STDMETHODCALLTYPE *GetCameraPos )( 
            IScreen * This,
            /* [out][in] */ POINTF *pptCam);
        
        HRESULT ( STDMETHODCALLTYPE *ShutDown )( 
            IScreen * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetScreenRect )( 
            IScreen * This,
            /* [out][in] */ RECT *prcScreen);
        
        HRESULT ( STDMETHODCALLTYPE *GetScreenWH )( 
            IScreen * This,
            /* [out][in] */ POINTF *pptScreen);
        
        HRESULT ( STDMETHODCALLTYPE *GetCameraRect )( 
            IScreen * This,
            /* [out][in] */ RECT *prcCam);
        
        HRESULT ( STDMETHODCALLTYPE *GetCameraRBPos )( 
            IScreen * This,
            /* [out][in] */ POINTF *pptCam);
        
        HRESULT ( STDMETHODCALLTYPE *SetWorldBounds )( 
            IScreen * This,
            /* [in] */ RECT *prcBounds);
        
        HRESULT ( STDMETHODCALLTYPE *GetWorldBounds )( 
            IScreen * This,
            /* [out][in] */ RECT *prcBounds);
        
        HRESULT ( STDMETHODCALLTYPE *AddFrameTable )( 
            IScreen * This,
            /* [out][in] */ int *pnID,
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor);
        
        HRESULT ( STDMETHODCALLTYPE *AddBMPFrameTable )( 
            IScreen * This,
            /* [out][in] */ int *pnID,
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor);
        
        HRESULT ( STDMETHODCALLTYPE *AddAngledTables )( 
            IScreen * This,
            /* [out][in] */ int *pnID,
            /* [in] */ int *pidSrcFrameTable,
            /* [in] */ float fTurnAngle,
            /* [in] */ float fNeededAngleOfFirstTable);
        
        HRESULT ( STDMETHODCALLTYPE *AddOrGetExistingFrameTable )( 
            IScreen * This,
            /* [out][in] */ int *pnID,
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor);
        
        HRESULT ( STDMETHODCALLTYPE *AddEmptyFrameTable )( 
            IScreen * This,
            /* [out][in] */ int *pnID,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparentFill,
            /* [in] */ DWORD dwFillColor);
        
        END_INTERFACE
    } IScreenVtbl;

    interface IScreen
    {
        CONST_VTBL struct IScreenVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScreen_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IScreen_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IScreen_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IScreen_ResetDisplay(This,hDispWnd,nWidth,nHeight,nRefRate,bFullscreen,nFPS)	\
    ( (This)->lpVtbl -> ResetDisplay(This,hDispWnd,nWidth,nHeight,nRefRate,bFullscreen,nFPS) ) 

#define IScreen_UpdateScreen(This)	\
    ( (This)->lpVtbl -> UpdateScreen(This) ) 

#define IScreen_MoveCamera(This,pvecD)	\
    ( (This)->lpVtbl -> MoveCamera(This,pvecD) ) 

#define IScreen_SetCamera(This,pptCam)	\
    ( (This)->lpVtbl -> SetCamera(This,pptCam) ) 

#define IScreen_GetCameraPos(This,pptCam)	\
    ( (This)->lpVtbl -> GetCameraPos(This,pptCam) ) 

#define IScreen_ShutDown(This)	\
    ( (This)->lpVtbl -> ShutDown(This) ) 

#define IScreen_GetScreenRect(This,prcScreen)	\
    ( (This)->lpVtbl -> GetScreenRect(This,prcScreen) ) 

#define IScreen_GetScreenWH(This,pptScreen)	\
    ( (This)->lpVtbl -> GetScreenWH(This,pptScreen) ) 

#define IScreen_GetCameraRect(This,prcCam)	\
    ( (This)->lpVtbl -> GetCameraRect(This,prcCam) ) 

#define IScreen_GetCameraRBPos(This,pptCam)	\
    ( (This)->lpVtbl -> GetCameraRBPos(This,pptCam) ) 

#define IScreen_SetWorldBounds(This,prcBounds)	\
    ( (This)->lpVtbl -> SetWorldBounds(This,prcBounds) ) 

#define IScreen_GetWorldBounds(This,prcBounds)	\
    ( (This)->lpVtbl -> GetWorldBounds(This,prcBounds) ) 

#define IScreen_AddFrameTable(This,pnID,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor)	\
    ( (This)->lpVtbl -> AddFrameTable(This,pnID,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor) ) 

#define IScreen_AddBMPFrameTable(This,pnID,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor)	\
    ( (This)->lpVtbl -> AddBMPFrameTable(This,pnID,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor) ) 

#define IScreen_AddAngledTables(This,pnID,pidSrcFrameTable,fTurnAngle,fNeededAngleOfFirstTable)	\
    ( (This)->lpVtbl -> AddAngledTables(This,pnID,pidSrcFrameTable,fTurnAngle,fNeededAngleOfFirstTable) ) 

#define IScreen_AddOrGetExistingFrameTable(This,pnID,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor)	\
    ( (This)->lpVtbl -> AddOrGetExistingFrameTable(This,pnID,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor) ) 

#define IScreen_AddEmptyFrameTable(This,pnID,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparentFill,dwFillColor)	\
    ( (This)->lpVtbl -> AddEmptyFrameTable(This,pnID,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparentFill,dwFillColor) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IScreen_INTERFACE_DEFINED__ */


#ifndef __IInput_INTERFACE_DEFINED__
#define __IInput_INTERFACE_DEFINED__

/* interface IInput */
/* [uuid][object] */ 


EXTERN_C const IID IID_IInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C7870A77-E3FB-4b3b-9863-FEFE4FA00DAC")
    IInput : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CheckKeyDown( 
            /* [in] */ int vKey,
            /* [out][in] */ BOOL *bRes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckKeyUp( 
            /* [in] */ int vKey,
            /* [out][in] */ BOOL *bRes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInput * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInput * This);
        
        HRESULT ( STDMETHODCALLTYPE *CheckKeyDown )( 
            IInput * This,
            /* [in] */ int vKey,
            /* [out][in] */ BOOL *bRes);
        
        HRESULT ( STDMETHODCALLTYPE *CheckKeyUp )( 
            IInput * This,
            /* [in] */ int vKey,
            /* [out][in] */ BOOL *bRes);
        
        END_INTERFACE
    } IInputVtbl;

    interface IInput
    {
        CONST_VTBL struct IInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInput_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInput_CheckKeyDown(This,vKey,bRes)	\
    ( (This)->lpVtbl -> CheckKeyDown(This,vKey,bRes) ) 

#define IInput_CheckKeyUp(This,vKey,bRes)	\
    ( (This)->lpVtbl -> CheckKeyUp(This,vKey,bRes) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInput_INTERFACE_DEFINED__ */


#ifndef __IAnim_INTERFACE_DEFINED__
#define __IAnim_INTERFACE_DEFINED__

/* interface IAnim */
/* [uuid][object] */ 


EXTERN_C const IID IID_IAnim;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FA21E599-0F20-49ce-B809-4E086D793899")
    IAnim : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE UseExistingFrameTable( 
            /* [in] */ int *pnID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFrameTime( 
            /* [in] */ int nAnimInd,
            /* [in] */ int msTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateAnim( 
            /* [in] */ int nAnimInd,
            /* [in] */ int nFramesAmount,
            /* [in] */ int *arrFrameInds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAnimType( 
            /* [in] */ int nAnimInd,
            /* [in] */ int nPlayType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectActiveAnim( 
            /* [in] */ int nAnimInd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectActiveFrame( 
            /* [in] */ int nFrameInd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FreezeFrame( 
            /* [in] */ BOOL bFreeze) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurAnimInd( 
            /* [out][in] */ int *pnCurAnimInd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckEndAnim( 
            /* [out][in] */ BOOL *pbEndAnim) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckHalfAnimPlayed( 
            /* [out][in] */ BOOL *pbHalfAnim) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameAmountInTable( 
            /* [out][in] */ int *pnFrames) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UseExistingFrameTableAsSimpleAnim( 
            /* [in] */ int *pnID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSimpleAnim( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateLinearAnim( 
            /* [in] */ int nAnimInd,
            /* [in] */ int nStartFrame,
            /* [in] */ int nEndFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadSimpleAnim( 
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadFrameTable( 
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadOrUseExistingSimpleAnim( 
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadOrUseExistingFrameTable( 
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAnimVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAnim * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAnim * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAnim * This);
        
        HRESULT ( STDMETHODCALLTYPE *UseExistingFrameTable )( 
            IAnim * This,
            /* [in] */ int *pnID);
        
        HRESULT ( STDMETHODCALLTYPE *SetFrameTime )( 
            IAnim * This,
            /* [in] */ int nAnimInd,
            /* [in] */ int msTime);
        
        HRESULT ( STDMETHODCALLTYPE *CreateAnim )( 
            IAnim * This,
            /* [in] */ int nAnimInd,
            /* [in] */ int nFramesAmount,
            /* [in] */ int *arrFrameInds);
        
        HRESULT ( STDMETHODCALLTYPE *SetAnimType )( 
            IAnim * This,
            /* [in] */ int nAnimInd,
            /* [in] */ int nPlayType);
        
        HRESULT ( STDMETHODCALLTYPE *SelectActiveAnim )( 
            IAnim * This,
            /* [in] */ int nAnimInd);
        
        HRESULT ( STDMETHODCALLTYPE *SelectActiveFrame )( 
            IAnim * This,
            /* [in] */ int nFrameInd);
        
        HRESULT ( STDMETHODCALLTYPE *FreezeFrame )( 
            IAnim * This,
            /* [in] */ BOOL bFreeze);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurAnimInd )( 
            IAnim * This,
            /* [out][in] */ int *pnCurAnimInd);
        
        HRESULT ( STDMETHODCALLTYPE *CheckEndAnim )( 
            IAnim * This,
            /* [out][in] */ BOOL *pbEndAnim);
        
        HRESULT ( STDMETHODCALLTYPE *CheckHalfAnimPlayed )( 
            IAnim * This,
            /* [out][in] */ BOOL *pbHalfAnim);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameAmountInTable )( 
            IAnim * This,
            /* [out][in] */ int *pnFrames);
        
        HRESULT ( STDMETHODCALLTYPE *UseExistingFrameTableAsSimpleAnim )( 
            IAnim * This,
            /* [in] */ int *pnID);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSimpleAnim )( 
            IAnim * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateLinearAnim )( 
            IAnim * This,
            /* [in] */ int nAnimInd,
            /* [in] */ int nStartFrame,
            /* [in] */ int nEndFrame);
        
        HRESULT ( STDMETHODCALLTYPE *LoadSimpleAnim )( 
            IAnim * This,
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor);
        
        HRESULT ( STDMETHODCALLTYPE *LoadFrameTable )( 
            IAnim * This,
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor);
        
        HRESULT ( STDMETHODCALLTYPE *LoadOrUseExistingSimpleAnim )( 
            IAnim * This,
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor);
        
        HRESULT ( STDMETHODCALLTYPE *LoadOrUseExistingFrameTable )( 
            IAnim * This,
            /* [in] */ UCHAR *strPathToFile,
            /* [in] */ int nNeededFrameW,
            /* [in] */ int nNeededFrameH,
            /* [in] */ int nColumns,
            /* [in] */ int nRows,
            /* [in] */ BOOL bTransparent,
            /* [in] */ DWORD dwTranspColor);
        
        END_INTERFACE
    } IAnimVtbl;

    interface IAnim
    {
        CONST_VTBL struct IAnimVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnim_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAnim_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAnim_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAnim_UseExistingFrameTable(This,pnID)	\
    ( (This)->lpVtbl -> UseExistingFrameTable(This,pnID) ) 

#define IAnim_SetFrameTime(This,nAnimInd,msTime)	\
    ( (This)->lpVtbl -> SetFrameTime(This,nAnimInd,msTime) ) 

#define IAnim_CreateAnim(This,nAnimInd,nFramesAmount,arrFrameInds)	\
    ( (This)->lpVtbl -> CreateAnim(This,nAnimInd,nFramesAmount,arrFrameInds) ) 

#define IAnim_SetAnimType(This,nAnimInd,nPlayType)	\
    ( (This)->lpVtbl -> SetAnimType(This,nAnimInd,nPlayType) ) 

#define IAnim_SelectActiveAnim(This,nAnimInd)	\
    ( (This)->lpVtbl -> SelectActiveAnim(This,nAnimInd) ) 

#define IAnim_SelectActiveFrame(This,nFrameInd)	\
    ( (This)->lpVtbl -> SelectActiveFrame(This,nFrameInd) ) 

#define IAnim_FreezeFrame(This,bFreeze)	\
    ( (This)->lpVtbl -> FreezeFrame(This,bFreeze) ) 

#define IAnim_GetCurAnimInd(This,pnCurAnimInd)	\
    ( (This)->lpVtbl -> GetCurAnimInd(This,pnCurAnimInd) ) 

#define IAnim_CheckEndAnim(This,pbEndAnim)	\
    ( (This)->lpVtbl -> CheckEndAnim(This,pbEndAnim) ) 

#define IAnim_CheckHalfAnimPlayed(This,pbHalfAnim)	\
    ( (This)->lpVtbl -> CheckHalfAnimPlayed(This,pbHalfAnim) ) 

#define IAnim_GetFrameAmountInTable(This,pnFrames)	\
    ( (This)->lpVtbl -> GetFrameAmountInTable(This,pnFrames) ) 

#define IAnim_UseExistingFrameTableAsSimpleAnim(This,pnID)	\
    ( (This)->lpVtbl -> UseExistingFrameTableAsSimpleAnim(This,pnID) ) 

#define IAnim_CreateSimpleAnim(This)	\
    ( (This)->lpVtbl -> CreateSimpleAnim(This) ) 

#define IAnim_CreateLinearAnim(This,nAnimInd,nStartFrame,nEndFrame)	\
    ( (This)->lpVtbl -> CreateLinearAnim(This,nAnimInd,nStartFrame,nEndFrame) ) 

#define IAnim_LoadSimpleAnim(This,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor)	\
    ( (This)->lpVtbl -> LoadSimpleAnim(This,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor) ) 

#define IAnim_LoadFrameTable(This,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor)	\
    ( (This)->lpVtbl -> LoadFrameTable(This,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor) ) 

#define IAnim_LoadOrUseExistingSimpleAnim(This,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor)	\
    ( (This)->lpVtbl -> LoadOrUseExistingSimpleAnim(This,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor) ) 

#define IAnim_LoadOrUseExistingFrameTable(This,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor)	\
    ( (This)->lpVtbl -> LoadOrUseExistingFrameTable(This,strPathToFile,nNeededFrameW,nNeededFrameH,nColumns,nRows,bTransparent,dwTranspColor) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAnim_INTERFACE_DEFINED__ */


#ifndef __IDraw_INTERFACE_DEFINED__
#define __IDraw_INTERFACE_DEFINED__

/* interface IDraw */
/* [uuid][object] */ 


EXTERN_C const IID IID_IDraw;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("107B86D6-DC6F-4f5b-9AB9-FB106ECABBC0")
    IDraw : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Show( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Hide( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShowOn( 
            /* [in] */ int depth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckVisible( 
            /* [out][in] */ BOOL *pRes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTranspColor( 
            /* [out][in] */ DWORD *pdwColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Lock( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPixel( 
            /* [in] */ POINTF *pptWhere,
            /* [out][in] */ DWORD *pdwPixColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unlock( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDrawVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDraw * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDraw * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDraw * This);
        
        HRESULT ( STDMETHODCALLTYPE *Show )( 
            IDraw * This);
        
        HRESULT ( STDMETHODCALLTYPE *Hide )( 
            IDraw * This);
        
        HRESULT ( STDMETHODCALLTYPE *ShowOn )( 
            IDraw * This,
            /* [in] */ int depth);
        
        HRESULT ( STDMETHODCALLTYPE *CheckVisible )( 
            IDraw * This,
            /* [out][in] */ BOOL *pRes);
        
        HRESULT ( STDMETHODCALLTYPE *GetTranspColor )( 
            IDraw * This,
            /* [out][in] */ DWORD *pdwColor);
        
        HRESULT ( STDMETHODCALLTYPE *Lock )( 
            IDraw * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPixel )( 
            IDraw * This,
            /* [in] */ POINTF *pptWhere,
            /* [out][in] */ DWORD *pdwPixColor);
        
        HRESULT ( STDMETHODCALLTYPE *Unlock )( 
            IDraw * This);
        
        END_INTERFACE
    } IDrawVtbl;

    interface IDraw
    {
        CONST_VTBL struct IDrawVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDraw_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDraw_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDraw_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDraw_Show(This)	\
    ( (This)->lpVtbl -> Show(This) ) 

#define IDraw_Hide(This)	\
    ( (This)->lpVtbl -> Hide(This) ) 

#define IDraw_ShowOn(This,depth)	\
    ( (This)->lpVtbl -> ShowOn(This,depth) ) 

#define IDraw_CheckVisible(This,pRes)	\
    ( (This)->lpVtbl -> CheckVisible(This,pRes) ) 

#define IDraw_GetTranspColor(This,pdwColor)	\
    ( (This)->lpVtbl -> GetTranspColor(This,pdwColor) ) 

#define IDraw_Lock(This)	\
    ( (This)->lpVtbl -> Lock(This) ) 

#define IDraw_GetPixel(This,pptWhere,pdwPixColor)	\
    ( (This)->lpVtbl -> GetPixel(This,pptWhere,pdwPixColor) ) 

#define IDraw_Unlock(This)	\
    ( (This)->lpVtbl -> Unlock(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDraw_INTERFACE_DEFINED__ */


#ifndef __IAngledDraw_INTERFACE_DEFINED__
#define __IAngledDraw_INTERFACE_DEFINED__

/* interface IAngledDraw */
/* [uuid][object] */ 


EXTERN_C const IID IID_IAngledDraw;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6C265245-E8BB-4cac-9283-BEB8DAEE1B91")
    IAngledDraw : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE UseExistingAngledTables( 
            /* [in] */ int *pnAngledTablesPack) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UseExistingAngledTablesAndSimpleAnim( 
            /* [in] */ int *pnAngledTablesPack,
            /* [in] */ int nNumStartTable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNumTables( 
            /* [out][in] */ int *pnNumTables) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectTable( 
            /* [in] */ int nNo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectTableByAngle( 
            /* [in] */ float fAngle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectTableByVector( 
            /* [in] */ POINTF *pvec) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAngledDrawVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAngledDraw * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAngledDraw * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAngledDraw * This);
        
        HRESULT ( STDMETHODCALLTYPE *UseExistingAngledTables )( 
            IAngledDraw * This,
            /* [in] */ int *pnAngledTablesPack);
        
        HRESULT ( STDMETHODCALLTYPE *UseExistingAngledTablesAndSimpleAnim )( 
            IAngledDraw * This,
            /* [in] */ int *pnAngledTablesPack,
            /* [in] */ int nNumStartTable);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumTables )( 
            IAngledDraw * This,
            /* [out][in] */ int *pnNumTables);
        
        HRESULT ( STDMETHODCALLTYPE *SelectTable )( 
            IAngledDraw * This,
            /* [in] */ int nNo);
        
        HRESULT ( STDMETHODCALLTYPE *SelectTableByAngle )( 
            IAngledDraw * This,
            /* [in] */ float fAngle);
        
        HRESULT ( STDMETHODCALLTYPE *SelectTableByVector )( 
            IAngledDraw * This,
            /* [in] */ POINTF *pvec);
        
        END_INTERFACE
    } IAngledDrawVtbl;

    interface IAngledDraw
    {
        CONST_VTBL struct IAngledDrawVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAngledDraw_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAngledDraw_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAngledDraw_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAngledDraw_UseExistingAngledTables(This,pnAngledTablesPack)	\
    ( (This)->lpVtbl -> UseExistingAngledTables(This,pnAngledTablesPack) ) 

#define IAngledDraw_UseExistingAngledTablesAndSimpleAnim(This,pnAngledTablesPack,nNumStartTable)	\
    ( (This)->lpVtbl -> UseExistingAngledTablesAndSimpleAnim(This,pnAngledTablesPack,nNumStartTable) ) 

#define IAngledDraw_GetNumTables(This,pnNumTables)	\
    ( (This)->lpVtbl -> GetNumTables(This,pnNumTables) ) 

#define IAngledDraw_SelectTable(This,nNo)	\
    ( (This)->lpVtbl -> SelectTable(This,nNo) ) 

#define IAngledDraw_SelectTableByAngle(This,fAngle)	\
    ( (This)->lpVtbl -> SelectTableByAngle(This,fAngle) ) 

#define IAngledDraw_SelectTableByVector(This,pvec)	\
    ( (This)->lpVtbl -> SelectTableByVector(This,pvec) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAngledDraw_INTERFACE_DEFINED__ */


#ifndef __IParams_INTERFACE_DEFINED__
#define __IParams_INTERFACE_DEFINED__

/* interface IParams */
/* [uuid][object] */ 


EXTERN_C const IID IID_IParams;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("33E213D7-2E97-4647-9488-F73E7DEB5360")
    IParams : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetPos( 
            /* [in] */ POINTF *pptPos) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ POINTF *pvecShift) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSmallestRad( 
            /* [out][in] */ float *pfRad) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBiggestRad( 
            /* [out][in] */ float *pfRad) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCoordsRect( 
            /* [out][in] */ RECT *rcCoords) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCoordsWHRect( 
            /* [out][in] */ RECT *rcCoordsWH) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCoordsPt( 
            /* [out][in] */ POINTF *ptCoords) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCentreCoordsPt( 
            /* [out][in] */ POINTF *ptCentreCoords) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWidthAndHeight( 
            /* [out][in] */ POINTF *pwhFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHalfWidthAndHeight( 
            /* [out][in] */ POINTF *pwhFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWidth( 
            /* [out][in] */ int *pnWidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHeight( 
            /* [out][in] */ int *pnHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLX( 
            /* [out][in] */ int *pnLX) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTY( 
            /* [out][in] */ int *pnTY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCX( 
            /* [out][in] */ int *pnCX) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRX( 
            /* [out][in] */ int *pnRX) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCY( 
            /* [out][in] */ int *pnCY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBY( 
            /* [out][in] */ int *pnBY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resize( 
            /* [in] */ int nNewWidth,
            int nNewHeight) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IParamsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IParams * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IParams * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IParams * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPos )( 
            IParams * This,
            /* [in] */ POINTF *pptPos);
        
        HRESULT ( STDMETHODCALLTYPE *Move )( 
            IParams * This,
            /* [in] */ POINTF *pvecShift);
        
        HRESULT ( STDMETHODCALLTYPE *GetSmallestRad )( 
            IParams * This,
            /* [out][in] */ float *pfRad);
        
        HRESULT ( STDMETHODCALLTYPE *GetBiggestRad )( 
            IParams * This,
            /* [out][in] */ float *pfRad);
        
        HRESULT ( STDMETHODCALLTYPE *GetCoordsRect )( 
            IParams * This,
            /* [out][in] */ RECT *rcCoords);
        
        HRESULT ( STDMETHODCALLTYPE *GetCoordsWHRect )( 
            IParams * This,
            /* [out][in] */ RECT *rcCoordsWH);
        
        HRESULT ( STDMETHODCALLTYPE *GetCoordsPt )( 
            IParams * This,
            /* [out][in] */ POINTF *ptCoords);
        
        HRESULT ( STDMETHODCALLTYPE *GetCentreCoordsPt )( 
            IParams * This,
            /* [out][in] */ POINTF *ptCentreCoords);
        
        HRESULT ( STDMETHODCALLTYPE *GetWidthAndHeight )( 
            IParams * This,
            /* [out][in] */ POINTF *pwhFrame);
        
        HRESULT ( STDMETHODCALLTYPE *GetHalfWidthAndHeight )( 
            IParams * This,
            /* [out][in] */ POINTF *pwhFrame);
        
        HRESULT ( STDMETHODCALLTYPE *GetWidth )( 
            IParams * This,
            /* [out][in] */ int *pnWidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetHeight )( 
            IParams * This,
            /* [out][in] */ int *pnHeight);
        
        HRESULT ( STDMETHODCALLTYPE *GetLX )( 
            IParams * This,
            /* [out][in] */ int *pnLX);
        
        HRESULT ( STDMETHODCALLTYPE *GetTY )( 
            IParams * This,
            /* [out][in] */ int *pnTY);
        
        HRESULT ( STDMETHODCALLTYPE *GetCX )( 
            IParams * This,
            /* [out][in] */ int *pnCX);
        
        HRESULT ( STDMETHODCALLTYPE *GetRX )( 
            IParams * This,
            /* [out][in] */ int *pnRX);
        
        HRESULT ( STDMETHODCALLTYPE *GetCY )( 
            IParams * This,
            /* [out][in] */ int *pnCY);
        
        HRESULT ( STDMETHODCALLTYPE *GetBY )( 
            IParams * This,
            /* [out][in] */ int *pnBY);
        
        HRESULT ( STDMETHODCALLTYPE *Resize )( 
            IParams * This,
            /* [in] */ int nNewWidth,
            int nNewHeight);
        
        END_INTERFACE
    } IParamsVtbl;

    interface IParams
    {
        CONST_VTBL struct IParamsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IParams_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IParams_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IParams_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IParams_SetPos(This,pptPos)	\
    ( (This)->lpVtbl -> SetPos(This,pptPos) ) 

#define IParams_Move(This,pvecShift)	\
    ( (This)->lpVtbl -> Move(This,pvecShift) ) 

#define IParams_GetSmallestRad(This,pfRad)	\
    ( (This)->lpVtbl -> GetSmallestRad(This,pfRad) ) 

#define IParams_GetBiggestRad(This,pfRad)	\
    ( (This)->lpVtbl -> GetBiggestRad(This,pfRad) ) 

#define IParams_GetCoordsRect(This,rcCoords)	\
    ( (This)->lpVtbl -> GetCoordsRect(This,rcCoords) ) 

#define IParams_GetCoordsWHRect(This,rcCoordsWH)	\
    ( (This)->lpVtbl -> GetCoordsWHRect(This,rcCoordsWH) ) 

#define IParams_GetCoordsPt(This,ptCoords)	\
    ( (This)->lpVtbl -> GetCoordsPt(This,ptCoords) ) 

#define IParams_GetCentreCoordsPt(This,ptCentreCoords)	\
    ( (This)->lpVtbl -> GetCentreCoordsPt(This,ptCentreCoords) ) 

#define IParams_GetWidthAndHeight(This,pwhFrame)	\
    ( (This)->lpVtbl -> GetWidthAndHeight(This,pwhFrame) ) 

#define IParams_GetHalfWidthAndHeight(This,pwhFrame)	\
    ( (This)->lpVtbl -> GetHalfWidthAndHeight(This,pwhFrame) ) 

#define IParams_GetWidth(This,pnWidth)	\
    ( (This)->lpVtbl -> GetWidth(This,pnWidth) ) 

#define IParams_GetHeight(This,pnHeight)	\
    ( (This)->lpVtbl -> GetHeight(This,pnHeight) ) 

#define IParams_GetLX(This,pnLX)	\
    ( (This)->lpVtbl -> GetLX(This,pnLX) ) 

#define IParams_GetTY(This,pnTY)	\
    ( (This)->lpVtbl -> GetTY(This,pnTY) ) 

#define IParams_GetCX(This,pnCX)	\
    ( (This)->lpVtbl -> GetCX(This,pnCX) ) 

#define IParams_GetRX(This,pnRX)	\
    ( (This)->lpVtbl -> GetRX(This,pnRX) ) 

#define IParams_GetCY(This,pnCY)	\
    ( (This)->lpVtbl -> GetCY(This,pnCY) ) 

#define IParams_GetBY(This,pnBY)	\
    ( (This)->lpVtbl -> GetBY(This,pnBY) ) 

#define IParams_Resize(This,nNewWidth,nNewHeight)	\
    ( (This)->lpVtbl -> Resize(This,nNewWidth,nNewHeight) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IParams_INTERFACE_DEFINED__ */


#ifndef __IHUD_INTERFACE_DEFINED__
#define __IHUD_INTERFACE_DEFINED__

/* interface IHUD */
/* [uuid][object] */ 


EXTERN_C const IID IID_IHUD;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("77C81842-F7E2-41b9-B5B4-BF8250B6C345")
    IHUD : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DrawText( 
            /* [in] */ LPRECT prcTextBox,
            /* [in] */ LPWSTR strText,
            DWORD dwColor,
            int nHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DrawLine( 
            /* [in] */ POINTF *ppt1,
            /* [in] */ POINTF *ppt2,
            /* [in] */ DWORD dwColor,
            /* [in] */ int nWidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DrawVLine( 
            /* [in] */ int x,
            /* [in] */ int y0,
            /* [in] */ int y1,
            /* [in] */ int nRad,
            /* [in] */ DWORD dwColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DrawHLine( 
            /* [in] */ int x0,
            /* [in] */ int x1,
            /* [in] */ int y,
            /* [in] */ int nRad,
            /* [in] */ DWORD dwColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ColorFill( 
            /* [in] */ RECT *pRect,
            /* [in] */ DWORD dwColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DrawPoint( 
            /* [in] */ POINTF *ppt,
            /* [in] */ DWORD dwColor,
            /* [in] */ int nWidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddText( 
            /* [in] */ LPRECT prcTextBox,
            /* [in] */ UCHAR *strText,
            /* [in] */ DWORD dwColor,
            /* [in] */ int nHeight,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddColorFill( 
            /* [in] */ RECT *pRect,
            /* [in] */ DWORD dwColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddHLine( 
            /* [in] */ int x0,
            /* [in] */ int x1,
            /* [in] */ int y,
            /* [in] */ int nWidth,
            /* [in] */ DWORD dwColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddVLine( 
            /* [in] */ int x,
            /* [in] */ int y0,
            /* [in] */ int y1,
            /* [in] */ int nWidth,
            /* [in] */ DWORD dwColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddLine( 
            /* [in] */ POINTF *ppt1,
            /* [in] */ POINTF *ppt2,
            /* [in] */ DWORD dwColor,
            /* [in] */ int nWidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddBtnView( 
            /* [in] */ RECT rcBounds,
            /* [in] */ int nBorderWidth,
            /* [in] */ DWORD clBack,
            /* [in] */ DWORD clBorder,
            /* [in] */ UCHAR *caption,
            /* [in] */ DWORD clFont,
            /* [in] */ int nFontHeight,
            /* [in] */ int nFontFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHUDVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHUD * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHUD * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHUD * This);
        
        HRESULT ( STDMETHODCALLTYPE *DrawText )( 
            IHUD * This,
            /* [in] */ LPRECT prcTextBox,
            /* [in] */ LPWSTR strText,
            DWORD dwColor,
            int nHeight);
        
        HRESULT ( STDMETHODCALLTYPE *DrawLine )( 
            IHUD * This,
            /* [in] */ POINTF *ppt1,
            /* [in] */ POINTF *ppt2,
            /* [in] */ DWORD dwColor,
            /* [in] */ int nWidth);
        
        HRESULT ( STDMETHODCALLTYPE *DrawVLine )( 
            IHUD * This,
            /* [in] */ int x,
            /* [in] */ int y0,
            /* [in] */ int y1,
            /* [in] */ int nRad,
            /* [in] */ DWORD dwColor);
        
        HRESULT ( STDMETHODCALLTYPE *DrawHLine )( 
            IHUD * This,
            /* [in] */ int x0,
            /* [in] */ int x1,
            /* [in] */ int y,
            /* [in] */ int nRad,
            /* [in] */ DWORD dwColor);
        
        HRESULT ( STDMETHODCALLTYPE *ColorFill )( 
            IHUD * This,
            /* [in] */ RECT *pRect,
            /* [in] */ DWORD dwColor);
        
        HRESULT ( STDMETHODCALLTYPE *DrawPoint )( 
            IHUD * This,
            /* [in] */ POINTF *ppt,
            /* [in] */ DWORD dwColor,
            /* [in] */ int nWidth);
        
        HRESULT ( STDMETHODCALLTYPE *AddText )( 
            IHUD * This,
            /* [in] */ LPRECT prcTextBox,
            /* [in] */ UCHAR *strText,
            /* [in] */ DWORD dwColor,
            /* [in] */ int nHeight,
            /* [in] */ DWORD dwFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddColorFill )( 
            IHUD * This,
            /* [in] */ RECT *pRect,
            /* [in] */ DWORD dwColor);
        
        HRESULT ( STDMETHODCALLTYPE *AddHLine )( 
            IHUD * This,
            /* [in] */ int x0,
            /* [in] */ int x1,
            /* [in] */ int y,
            /* [in] */ int nWidth,
            /* [in] */ DWORD dwColor);
        
        HRESULT ( STDMETHODCALLTYPE *AddVLine )( 
            IHUD * This,
            /* [in] */ int x,
            /* [in] */ int y0,
            /* [in] */ int y1,
            /* [in] */ int nWidth,
            /* [in] */ DWORD dwColor);
        
        HRESULT ( STDMETHODCALLTYPE *AddLine )( 
            IHUD * This,
            /* [in] */ POINTF *ppt1,
            /* [in] */ POINTF *ppt2,
            /* [in] */ DWORD dwColor,
            /* [in] */ int nWidth);
        
        HRESULT ( STDMETHODCALLTYPE *AddBtnView )( 
            IHUD * This,
            /* [in] */ RECT rcBounds,
            /* [in] */ int nBorderWidth,
            /* [in] */ DWORD clBack,
            /* [in] */ DWORD clBorder,
            /* [in] */ UCHAR *caption,
            /* [in] */ DWORD clFont,
            /* [in] */ int nFontHeight,
            /* [in] */ int nFontFlags);
        
        END_INTERFACE
    } IHUDVtbl;

    interface IHUD
    {
        CONST_VTBL struct IHUDVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHUD_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHUD_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHUD_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHUD_DrawText(This,prcTextBox,strText,dwColor,nHeight)	\
    ( (This)->lpVtbl -> DrawText(This,prcTextBox,strText,dwColor,nHeight) ) 

#define IHUD_DrawLine(This,ppt1,ppt2,dwColor,nWidth)	\
    ( (This)->lpVtbl -> DrawLine(This,ppt1,ppt2,dwColor,nWidth) ) 

#define IHUD_DrawVLine(This,x,y0,y1,nRad,dwColor)	\
    ( (This)->lpVtbl -> DrawVLine(This,x,y0,y1,nRad,dwColor) ) 

#define IHUD_DrawHLine(This,x0,x1,y,nRad,dwColor)	\
    ( (This)->lpVtbl -> DrawHLine(This,x0,x1,y,nRad,dwColor) ) 

#define IHUD_ColorFill(This,pRect,dwColor)	\
    ( (This)->lpVtbl -> ColorFill(This,pRect,dwColor) ) 

#define IHUD_DrawPoint(This,ppt,dwColor,nWidth)	\
    ( (This)->lpVtbl -> DrawPoint(This,ppt,dwColor,nWidth) ) 

#define IHUD_AddText(This,prcTextBox,strText,dwColor,nHeight,dwFlags)	\
    ( (This)->lpVtbl -> AddText(This,prcTextBox,strText,dwColor,nHeight,dwFlags) ) 

#define IHUD_AddColorFill(This,pRect,dwColor)	\
    ( (This)->lpVtbl -> AddColorFill(This,pRect,dwColor) ) 

#define IHUD_AddHLine(This,x0,x1,y,nWidth,dwColor)	\
    ( (This)->lpVtbl -> AddHLine(This,x0,x1,y,nWidth,dwColor) ) 

#define IHUD_AddVLine(This,x,y0,y1,nWidth,dwColor)	\
    ( (This)->lpVtbl -> AddVLine(This,x,y0,y1,nWidth,dwColor) ) 

#define IHUD_AddLine(This,ppt1,ppt2,dwColor,nWidth)	\
    ( (This)->lpVtbl -> AddLine(This,ppt1,ppt2,dwColor,nWidth) ) 

#define IHUD_AddBtnView(This,rcBounds,nBorderWidth,clBack,clBorder,caption,clFont,nFontHeight,nFontFlags)	\
    ( (This)->lpVtbl -> AddBtnView(This,rcBounds,nBorderWidth,clBack,clBorder,caption,clFont,nFontHeight,nFontFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHUD_INTERFACE_DEFINED__ */


#ifndef __IPhysics_INTERFACE_DEFINED__
#define __IPhysics_INTERFACE_DEFINED__

/* interface IPhysics */
/* [uuid][object] */ 


EXTERN_C const IID IID_IPhysics;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("17891271-BC0F-471b-ABD9-397172F963C1")
    IPhysics : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CheckStopped( 
            /* [out][in] */ BOOL *pbStopped) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGround( 
            /* [in] */ int nYGroundLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNoGround( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetBounds( 
            /* [in] */ RECT rcBounds,
            /* [in] */ BOOL bMoveWithCamera) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetBoundsReact( 
            /* [in] */ int nReact) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdatePhysics( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CheckCollisionCircleCircle( 
            /* [in] */ IParams *pOtherObj,
            /* [out][in] */ BOOL *bCollision) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPhysicsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPhysics * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPhysics * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPhysics * This);
        
        HRESULT ( STDMETHODCALLTYPE *CheckStopped )( 
            IPhysics * This,
            /* [out][in] */ BOOL *pbStopped);
        
        HRESULT ( STDMETHODCALLTYPE *SetGround )( 
            IPhysics * This,
            /* [in] */ int nYGroundLevel);
        
        HRESULT ( STDMETHODCALLTYPE *SetNoGround )( 
            IPhysics * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetBounds )( 
            IPhysics * This,
            /* [in] */ RECT rcBounds,
            /* [in] */ BOOL bMoveWithCamera);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetBoundsReact )( 
            IPhysics * This,
            /* [in] */ int nReact);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdatePhysics )( 
            IPhysics * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CheckCollisionCircleCircle )( 
            IPhysics * This,
            /* [in] */ IParams *pOtherObj,
            /* [out][in] */ BOOL *bCollision);
        
        END_INTERFACE
    } IPhysicsVtbl;

    interface IPhysics
    {
        CONST_VTBL struct IPhysicsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPhysics_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPhysics_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPhysics_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPhysics_CheckStopped(This,pbStopped)	\
    ( (This)->lpVtbl -> CheckStopped(This,pbStopped) ) 

#define IPhysics_SetGround(This,nYGroundLevel)	\
    ( (This)->lpVtbl -> SetGround(This,nYGroundLevel) ) 

#define IPhysics_SetNoGround(This)	\
    ( (This)->lpVtbl -> SetNoGround(This) ) 

#define IPhysics_SetBounds(This,rcBounds,bMoveWithCamera)	\
    ( (This)->lpVtbl -> SetBounds(This,rcBounds,bMoveWithCamera) ) 

#define IPhysics_SetBoundsReact(This,nReact)	\
    ( (This)->lpVtbl -> SetBoundsReact(This,nReact) ) 

#define IPhysics_UpdatePhysics(This)	\
    ( (This)->lpVtbl -> UpdatePhysics(This) ) 

#define IPhysics_CheckCollisionCircleCircle(This,pOtherObj,bCollision)	\
    ( (This)->lpVtbl -> CheckCollisionCircleCircle(This,pOtherObj,bCollision) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPhysics_INTERFACE_DEFINED__ */


#ifndef __ILinearMovement_INTERFACE_DEFINED__
#define __ILinearMovement_INTERFACE_DEFINED__

/* interface ILinearMovement */
/* [uuid][object] */ 


EXTERN_C const IID IID_ILinearMovement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4FBFB4E6-9B1A-4f5d-862B-072F2590C111")
    ILinearMovement : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSpeed( 
            /* [in] */ float fSpeed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOrtVel( 
            /* [in] */ POINTF *portVel,
            /* [in] */ BOOL bSetSpeedIgnored) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVel( 
            /* [in] */ POINTF *pvecVel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVel( 
            /* [out][in] */ POINTF *pvecVel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOrtVel( 
            /* [out][in] */ POINTF *portVel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRealSpeed( 
            /* [out][in] */ float *pfSpeed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDirX( 
            /* [in] */ float fEX,
            /* [in] */ BOOL bSetSpeedIgnored) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDirY( 
            /* [in] */ float fEY,
            /* [in] */ BOOL bSetSpeedIgnored) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVelX( 
            /* [out][in] */ float *pfEX) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVelY( 
            /* [out][in] */ float *pfEY) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILinearMovementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILinearMovement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILinearMovement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILinearMovement * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetSpeed )( 
            ILinearMovement * This,
            /* [in] */ float fSpeed);
        
        HRESULT ( STDMETHODCALLTYPE *SetOrtVel )( 
            ILinearMovement * This,
            /* [in] */ POINTF *portVel,
            /* [in] */ BOOL bSetSpeedIgnored);
        
        HRESULT ( STDMETHODCALLTYPE *SetVel )( 
            ILinearMovement * This,
            /* [in] */ POINTF *pvecVel);
        
        HRESULT ( STDMETHODCALLTYPE *GetVel )( 
            ILinearMovement * This,
            /* [out][in] */ POINTF *pvecVel);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrtVel )( 
            ILinearMovement * This,
            /* [out][in] */ POINTF *portVel);
        
        HRESULT ( STDMETHODCALLTYPE *GetRealSpeed )( 
            ILinearMovement * This,
            /* [out][in] */ float *pfSpeed);
        
        HRESULT ( STDMETHODCALLTYPE *SetDirX )( 
            ILinearMovement * This,
            /* [in] */ float fEX,
            /* [in] */ BOOL bSetSpeedIgnored);
        
        HRESULT ( STDMETHODCALLTYPE *SetDirY )( 
            ILinearMovement * This,
            /* [in] */ float fEY,
            /* [in] */ BOOL bSetSpeedIgnored);
        
        HRESULT ( STDMETHODCALLTYPE *GetVelX )( 
            ILinearMovement * This,
            /* [out][in] */ float *pfEX);
        
        HRESULT ( STDMETHODCALLTYPE *GetVelY )( 
            ILinearMovement * This,
            /* [out][in] */ float *pfEY);
        
        END_INTERFACE
    } ILinearMovementVtbl;

    interface ILinearMovement
    {
        CONST_VTBL struct ILinearMovementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILinearMovement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILinearMovement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILinearMovement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILinearMovement_SetSpeed(This,fSpeed)	\
    ( (This)->lpVtbl -> SetSpeed(This,fSpeed) ) 

#define ILinearMovement_SetOrtVel(This,portVel,bSetSpeedIgnored)	\
    ( (This)->lpVtbl -> SetOrtVel(This,portVel,bSetSpeedIgnored) ) 

#define ILinearMovement_SetVel(This,pvecVel)	\
    ( (This)->lpVtbl -> SetVel(This,pvecVel) ) 

#define ILinearMovement_GetVel(This,pvecVel)	\
    ( (This)->lpVtbl -> GetVel(This,pvecVel) ) 

#define ILinearMovement_GetOrtVel(This,portVel)	\
    ( (This)->lpVtbl -> GetOrtVel(This,portVel) ) 

#define ILinearMovement_GetRealSpeed(This,pfSpeed)	\
    ( (This)->lpVtbl -> GetRealSpeed(This,pfSpeed) ) 

#define ILinearMovement_SetDirX(This,fEX,bSetSpeedIgnored)	\
    ( (This)->lpVtbl -> SetDirX(This,fEX,bSetSpeedIgnored) ) 

#define ILinearMovement_SetDirY(This,fEY,bSetSpeedIgnored)	\
    ( (This)->lpVtbl -> SetDirY(This,fEY,bSetSpeedIgnored) ) 

#define ILinearMovement_GetVelX(This,pfEX)	\
    ( (This)->lpVtbl -> GetVelX(This,pfEX) ) 

#define ILinearMovement_GetVelY(This,pfEY)	\
    ( (This)->lpVtbl -> GetVelY(This,pfEY) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILinearMovement_INTERFACE_DEFINED__ */


#ifndef __IAccelMovement_INTERFACE_DEFINED__
#define __IAccelMovement_INTERFACE_DEFINED__

/* interface IAccelMovement */
/* [uuid][object] */ 


EXTERN_C const IID IID_IAccelMovement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("72A3CC05-7390-49d7-ABA8-74B9A459D7C1")
    IAccelMovement : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetAccel( 
            /* [in] */ float fAccel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMaxSpeed( 
            /* [in] */ float fMaxSpeed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOrtAccel( 
            /* [in] */ POINTF *portAcc) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableAccel( 
            /* [in] */ int nAccelType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAccel( 
            /* [out][in] */ float *pfAccel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxSpeed( 
            /* [out][in] */ float *pfMaxSpeed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOrtAccel( 
            /* [out][in] */ POINTF *portAccel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAccelType( 
            /* [out][in] */ int *pnAccelType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVecAccel( 
            /* [out][in] */ POINTF *vecAccel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAccelDirX( 
            /* [in] */ float fEX) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAccelDirY( 
            /* [in] */ float fEY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAccelEX( 
            /* [out][in] */ float *pfEX) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAccelEY( 
            /* [out][in] */ float *pfEY) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAccelMovementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAccelMovement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAccelMovement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAccelMovement * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetAccel )( 
            IAccelMovement * This,
            /* [in] */ float fAccel);
        
        HRESULT ( STDMETHODCALLTYPE *SetMaxSpeed )( 
            IAccelMovement * This,
            /* [in] */ float fMaxSpeed);
        
        HRESULT ( STDMETHODCALLTYPE *SetOrtAccel )( 
            IAccelMovement * This,
            /* [in] */ POINTF *portAcc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableAccel )( 
            IAccelMovement * This,
            /* [in] */ int nAccelType);
        
        HRESULT ( STDMETHODCALLTYPE *GetAccel )( 
            IAccelMovement * This,
            /* [out][in] */ float *pfAccel);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxSpeed )( 
            IAccelMovement * This,
            /* [out][in] */ float *pfMaxSpeed);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrtAccel )( 
            IAccelMovement * This,
            /* [out][in] */ POINTF *portAccel);
        
        HRESULT ( STDMETHODCALLTYPE *GetAccelType )( 
            IAccelMovement * This,
            /* [out][in] */ int *pnAccelType);
        
        HRESULT ( STDMETHODCALLTYPE *GetVecAccel )( 
            IAccelMovement * This,
            /* [out][in] */ POINTF *vecAccel);
        
        HRESULT ( STDMETHODCALLTYPE *SetAccelDirX )( 
            IAccelMovement * This,
            /* [in] */ float fEX);
        
        HRESULT ( STDMETHODCALLTYPE *SetAccelDirY )( 
            IAccelMovement * This,
            /* [in] */ float fEY);
        
        HRESULT ( STDMETHODCALLTYPE *GetAccelEX )( 
            IAccelMovement * This,
            /* [out][in] */ float *pfEX);
        
        HRESULT ( STDMETHODCALLTYPE *GetAccelEY )( 
            IAccelMovement * This,
            /* [out][in] */ float *pfEY);
        
        END_INTERFACE
    } IAccelMovementVtbl;

    interface IAccelMovement
    {
        CONST_VTBL struct IAccelMovementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAccelMovement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAccelMovement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAccelMovement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAccelMovement_SetAccel(This,fAccel)	\
    ( (This)->lpVtbl -> SetAccel(This,fAccel) ) 

#define IAccelMovement_SetMaxSpeed(This,fMaxSpeed)	\
    ( (This)->lpVtbl -> SetMaxSpeed(This,fMaxSpeed) ) 

#define IAccelMovement_SetOrtAccel(This,portAcc)	\
    ( (This)->lpVtbl -> SetOrtAccel(This,portAcc) ) 

#define IAccelMovement_EnableAccel(This,nAccelType)	\
    ( (This)->lpVtbl -> EnableAccel(This,nAccelType) ) 

#define IAccelMovement_GetAccel(This,pfAccel)	\
    ( (This)->lpVtbl -> GetAccel(This,pfAccel) ) 

#define IAccelMovement_GetMaxSpeed(This,pfMaxSpeed)	\
    ( (This)->lpVtbl -> GetMaxSpeed(This,pfMaxSpeed) ) 

#define IAccelMovement_GetOrtAccel(This,portAccel)	\
    ( (This)->lpVtbl -> GetOrtAccel(This,portAccel) ) 

#define IAccelMovement_GetAccelType(This,pnAccelType)	\
    ( (This)->lpVtbl -> GetAccelType(This,pnAccelType) ) 

#define IAccelMovement_GetVecAccel(This,vecAccel)	\
    ( (This)->lpVtbl -> GetVecAccel(This,vecAccel) ) 

#define IAccelMovement_SetAccelDirX(This,fEX)	\
    ( (This)->lpVtbl -> SetAccelDirX(This,fEX) ) 

#define IAccelMovement_SetAccelDirY(This,fEY)	\
    ( (This)->lpVtbl -> SetAccelDirY(This,fEY) ) 

#define IAccelMovement_GetAccelEX(This,pfEX)	\
    ( (This)->lpVtbl -> GetAccelEX(This,pfEX) ) 

#define IAccelMovement_GetAccelEY(This,pfEY)	\
    ( (This)->lpVtbl -> GetAccelEY(This,pfEY) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAccelMovement_INTERFACE_DEFINED__ */


#ifndef __IRotation_INTERFACE_DEFINED__
#define __IRotation_INTERFACE_DEFINED__

/* interface IRotation */
/* [uuid][object] */ 


EXTERN_C const IID IID_IRotation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("54DC2001-5C70-48a1-B9F2-3979CD521D3B")
    IRotation : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetTurnAngle( 
            /* [in] */ float fAngle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Turn( 
            /* [in] */ int nDirection) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StepTo( 
            /* [in] */ POINTF *pvec) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TurnImm( 
            /* [in] */ POINTF *pvec) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRotationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRotation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRotation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRotation * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetTurnAngle )( 
            IRotation * This,
            /* [in] */ float fAngle);
        
        HRESULT ( STDMETHODCALLTYPE *Turn )( 
            IRotation * This,
            /* [in] */ int nDirection);
        
        HRESULT ( STDMETHODCALLTYPE *StepTo )( 
            IRotation * This,
            /* [in] */ POINTF *pvec);
        
        HRESULT ( STDMETHODCALLTYPE *TurnImm )( 
            IRotation * This,
            /* [in] */ POINTF *pvec);
        
        END_INTERFACE
    } IRotationVtbl;

    interface IRotation
    {
        CONST_VTBL struct IRotationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRotation_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRotation_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRotation_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRotation_SetTurnAngle(This,fAngle)	\
    ( (This)->lpVtbl -> SetTurnAngle(This,fAngle) ) 

#define IRotation_Turn(This,nDirection)	\
    ( (This)->lpVtbl -> Turn(This,nDirection) ) 

#define IRotation_StepTo(This,pvec)	\
    ( (This)->lpVtbl -> StepTo(This,pvec) ) 

#define IRotation_TurnImm(This,pvec)	\
    ( (This)->lpVtbl -> TurnImm(This,pvec) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRotation_INTERFACE_DEFINED__ */


#ifndef __IOrbitMovement_INTERFACE_DEFINED__
#define __IOrbitMovement_INTERFACE_DEFINED__

/* interface IOrbitMovement */
/* [uuid][object] */ 


EXTERN_C const IID IID_IOrbitMovement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("42FEC7E4-C715-4428-BC8F-631ED6DFB8D6")
    IOrbitMovement : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE PutOnOrbit( 
            /* [in] */ POINTF *pptOrbitCentre,
            /* [in] */ float fAngle,
            /* [in] */ float fRadOrbit) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MakeCurPosBeOnOrbit( 
            /* [in] */ POINTF *pptOrbitCentre) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOrbitDir( 
            /* [in] */ int nMoveDir) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnableOrbitMovement( 
            /* [in] */ BOOL bIsOnOrbit) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOrbitCentre( 
            /* [out][in] */ POINTF *pptOrbitCentre) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckOnOrbit( 
            /* [out][in] */ BOOL *pbIsOnOrbit) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOrbitMovementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOrbitMovement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOrbitMovement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOrbitMovement * This);
        
        HRESULT ( STDMETHODCALLTYPE *PutOnOrbit )( 
            IOrbitMovement * This,
            /* [in] */ POINTF *pptOrbitCentre,
            /* [in] */ float fAngle,
            /* [in] */ float fRadOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *MakeCurPosBeOnOrbit )( 
            IOrbitMovement * This,
            /* [in] */ POINTF *pptOrbitCentre);
        
        HRESULT ( STDMETHODCALLTYPE *SetOrbitDir )( 
            IOrbitMovement * This,
            /* [in] */ int nMoveDir);
        
        HRESULT ( STDMETHODCALLTYPE *EnableOrbitMovement )( 
            IOrbitMovement * This,
            /* [in] */ BOOL bIsOnOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitCentre )( 
            IOrbitMovement * This,
            /* [out][in] */ POINTF *pptOrbitCentre);
        
        HRESULT ( STDMETHODCALLTYPE *CheckOnOrbit )( 
            IOrbitMovement * This,
            /* [out][in] */ BOOL *pbIsOnOrbit);
        
        END_INTERFACE
    } IOrbitMovementVtbl;

    interface IOrbitMovement
    {
        CONST_VTBL struct IOrbitMovementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOrbitMovement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOrbitMovement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOrbitMovement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOrbitMovement_PutOnOrbit(This,pptOrbitCentre,fAngle,fRadOrbit)	\
    ( (This)->lpVtbl -> PutOnOrbit(This,pptOrbitCentre,fAngle,fRadOrbit) ) 

#define IOrbitMovement_MakeCurPosBeOnOrbit(This,pptOrbitCentre)	\
    ( (This)->lpVtbl -> MakeCurPosBeOnOrbit(This,pptOrbitCentre) ) 

#define IOrbitMovement_SetOrbitDir(This,nMoveDir)	\
    ( (This)->lpVtbl -> SetOrbitDir(This,nMoveDir) ) 

#define IOrbitMovement_EnableOrbitMovement(This,bIsOnOrbit)	\
    ( (This)->lpVtbl -> EnableOrbitMovement(This,bIsOnOrbit) ) 

#define IOrbitMovement_GetOrbitCentre(This,pptOrbitCentre)	\
    ( (This)->lpVtbl -> GetOrbitCentre(This,pptOrbitCentre) ) 

#define IOrbitMovement_CheckOnOrbit(This,pbIsOnOrbit)	\
    ( (This)->lpVtbl -> CheckOnOrbit(This,pbIsOnOrbit) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IOrbitMovement_INTERFACE_DEFINED__ */


#ifndef __IJump_INTERFACE_DEFINED__
#define __IJump_INTERFACE_DEFINED__

/* interface IJump */
/* [uuid][object] */ 


EXTERN_C const IID IID_IJump;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8B3042C4-0071-4780-8B66-A88EF0AEDB9C")
    IJump : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetJumpSpeed( 
            /* [in] */ float fJSpeed) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Jump( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IJumpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJump * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJump * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJump * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetJumpSpeed )( 
            IJump * This,
            /* [in] */ float fJSpeed);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Jump )( 
            IJump * This);
        
        END_INTERFACE
    } IJumpVtbl;

    interface IJump
    {
        CONST_VTBL struct IJumpVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJump_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJump_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJump_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJump_SetJumpSpeed(This,fJSpeed)	\
    ( (This)->lpVtbl -> SetJumpSpeed(This,fJSpeed) ) 

#define IJump_Jump(This)	\
    ( (This)->lpVtbl -> Jump(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IJump_INTERFACE_DEFINED__ */


#ifndef __IResistForces_INTERFACE_DEFINED__
#define __IResistForces_INTERFACE_DEFINED__

/* interface IResistForces */
/* [uuid][object] */ 


EXTERN_C const IID IID_IResistForces;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FBFF4301-8175-443c-A456-E42BE908620C")
    IResistForces : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetForces( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGravity( 
            /* [in] */ POINTF *pvecGravAccel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFriction( 
            /* [in] */ POINTF *pvecFric) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResistForcesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IResistForces * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IResistForces * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IResistForces * This);
        
        HRESULT ( STDMETHODCALLTYPE *ResetForces )( 
            IResistForces * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetGravity )( 
            IResistForces * This,
            /* [in] */ POINTF *pvecGravAccel);
        
        HRESULT ( STDMETHODCALLTYPE *SetFriction )( 
            IResistForces * This,
            /* [in] */ POINTF *pvecFric);
        
        END_INTERFACE
    } IResistForcesVtbl;

    interface IResistForces
    {
        CONST_VTBL struct IResistForcesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResistForces_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IResistForces_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IResistForces_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IResistForces_ResetForces(This)	\
    ( (This)->lpVtbl -> ResetForces(This) ) 

#define IResistForces_SetGravity(This,pvecGravAccel)	\
    ( (This)->lpVtbl -> SetGravity(This,pvecGravAccel) ) 

#define IResistForces_SetFriction(This,pvecFric)	\
    ( (This)->lpVtbl -> SetFriction(This,pvecFric) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IResistForces_INTERFACE_DEFINED__ */



#ifndef __VisObjLib_LIBRARY_DEFINED__
#define __VisObjLib_LIBRARY_DEFINED__

/* library VisObjLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VisObjLib;

EXTERN_C const CLSID CLSID_VisObj;

#ifdef __cplusplus

class DECLSPEC_UUID("4BCD9790-ABCE-4b14-837B-C48F521FE2FD")
VisObj;
#endif
#endif /* __VisObjLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long *, HWND * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


