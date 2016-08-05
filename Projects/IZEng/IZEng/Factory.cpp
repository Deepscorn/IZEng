#include "Factory.h"
#include "PhysObj.h"

STDMETHODIMP CoFactory::CreateInstance(LPUNKNOWN pUnk, REFIID riid, void **ppV) {
	HRESULT hRes = S_FALSE;
	if(pUnk!=NULL)
		return S_FALSE;//CLASS_E_NOAGERATION;
	PhysObj *pObj = new PhysObj;
	hRes = pObj->QueryInterface(riid,ppV);
	if(FAILED(hRes))
		delete pObj;
	return(hRes);
}

STDMETHODIMP CoFactory::QueryInterface(REFIID idInterface, void **ppInterface) {
	*ppInterface=NULL;
	if(idInterface == IID_IUnknown)
		*ppInterface = (IUnknown*)this;
	if(idInterface == IID_IClassFactory)
		*ppInterface = (IClassFactory*)this;
	if(*ppInterface) {
		((IUnknown*)*ppInterface)->AddRef();
		return(S_OK);
	}
	if(m_nRefCount<=0) 
		delete this;
	return(E_NOINTERFACE);
}
	
STDMETHODIMP_(ULONG) CoFactory::Release() {
	m_nRefCount--;
	if(m_nRefCount<=0 && m_nLocksCount<=0)
		//не удаляем, пока стоит блокировка
		delete this;
	return(m_nRefCount);
}

STDMETHODIMP CoFactory::LockServer(BOOL bFlag) {
	if(bFlag)
		m_nLocksCount++;
	else
		m_nLocksCount--;
	return(m_nLocksCount);
}