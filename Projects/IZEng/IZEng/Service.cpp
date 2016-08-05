#include "PhysObj.h"
//#include "Interfaces_h.h"
#include "Factory.h"

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppV) {
	HRESULT hR = S_FALSE;
	*ppV = NULL;
	if(rclsid == CLSID_VisObj) {
		CoFactory *pFactory = new CoFactory;
		hR = pFactory->QueryInterface(riid,ppV);
		return(hR);
	}
	return(hR);
}

STDAPI DllCreateInstance(REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv) {
	*ppv = NULL;
	if(rclsid==CLSID_VisObj) {
		*ppv = new PhysObj;
		return ((IUnknown*)*ppv)->QueryInterface(riid,ppv);
	}
	return(S_FALSE);
}

