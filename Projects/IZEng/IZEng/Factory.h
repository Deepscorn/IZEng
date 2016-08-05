#pragma once
#include "unknwn.h"

class CoFactory: public IClassFactory {
public:
	CoFactory() { m_nRefCount=0; m_nLocksCount=0; }
	~CoFactory() {}
	STDMETHODIMP CreateInstance(LPUNKNOWN pUnk, REFIID riid, void **ppV);
	STDMETHODIMP LockServer(BOOL bFlag);
	STDMETHODIMP QueryInterface(REFIID idInterface, void **ppInterface);
	STDMETHODIMP_(ULONG) AddRef() {return(++m_nRefCount);}
	STDMETHODIMP_(ULONG) Release();
private:
	int m_nRefCount;
	int m_nLocksCount;
};