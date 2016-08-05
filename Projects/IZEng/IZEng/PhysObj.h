#pragma once
#include "VisObj.h"

class PhysObj: public VisObj,public IPhysics, public ILinearMovement,
	public IRotation, public IOrbitMovement, public IAccelMovement, public IResistForces, public IJump {
public:
	PhysObj();
	virtual ~PhysObj();
public: //IPhysics
	HRESULT STDMETHODCALLTYPE CheckStopped(BOOL *pbStopped);
	HRESULT STDMETHODCALLTYPE SetGround(int nYGroundLevel);
	HRESULT STDMETHODCALLTYPE SetNoGround();
	HRESULT STDMETHODCALLTYPE SetBounds(RECT rcBounds,BOOL bMoveWithCamera);
	HRESULT STDMETHODCALLTYPE SetBoundsReact(int nReact);
	HRESULT STDMETHODCALLTYPE UpdatePhysics();
	HRESULT STDMETHODCALLTYPE CheckCollisionCircleCircle(IParams* pOtherObj, BOOL *bCollision);
public: //ILinearMovement - $UNSUPPORTED$
	HRESULT STDMETHODCALLTYPE SetSpeed( float fVel);
	HRESULT STDMETHODCALLTYPE SetOrtVel(POINTF *portVel, BOOL bSetSpeedIgnored);
	HRESULT STDMETHODCALLTYPE SetVel(POINTF *pvecVel);
	HRESULT STDMETHODCALLTYPE GetOrtVel(POINTF *portVel);
	HRESULT STDMETHODCALLTYPE GetVel(POINTF *pvecVel);
	HRESULT STDMETHODCALLTYPE GetRealSpeed(float *pfSpeed);
	//UNSAFE!
	HRESULT STDMETHODCALLTYPE SetDirX( float fEX, BOOL bSetSpeedIgnored);
	HRESULT STDMETHODCALLTYPE SetDirY( float fEY, BOOL bSetSpeedIgnored);
	HRESULT STDMETHODCALLTYPE GetVelX( float *pfEX);
	HRESULT STDMETHODCALLTYPE GetVelY( float *pfEY);
public: //IAccelMovement
	HRESULT STDMETHODCALLTYPE SetAccel(float fAccel);
	HRESULT STDMETHODCALLTYPE SetMaxSpeed(float fMaxSpeed);
	HRESULT STDMETHODCALLTYPE EnableAccel(int nAccelType);
	HRESULT STDMETHODCALLTYPE SetOrtAccel(POINTF *portAcc);
	//Get
	HRESULT STDMETHODCALLTYPE GetAccel(float *pfAccel);
	HRESULT STDMETHODCALLTYPE GetOrtAccel(POINTF *portAccel);
	HRESULT STDMETHODCALLTYPE GetMaxSpeed(float *pfMaxSpeed);
	HRESULT STDMETHODCALLTYPE GetAccelType(int *pnAccelType);
	HRESULT STDMETHODCALLTYPE GetVecAccel(POINTF *vecAccel);
	//UNSAFE!
	HRESULT STDMETHODCALLTYPE SetAccelDirX(float fEX);
	HRESULT STDMETHODCALLTYPE SetAccelDirY(float fEY);
	HRESULT STDMETHODCALLTYPE GetAccelEX(float *pfEX);
	HRESULT STDMETHODCALLTYPE GetAccelEY(float *pfEY);
public: //IRotation
	HRESULT STDMETHODCALLTYPE SetTurnAngle( float fAngle);
	HRESULT STDMETHODCALLTYPE Turn( int nDirection);
	HRESULT STDMETHODCALLTYPE StepTo(POINTF *pvec);
	HRESULT STDMETHODCALLTYPE TurnImm(POINTF *pvec);
	//Get
	HRESULT STDMETHODCALLTYPE GetTurnAngle(float* pfAngle);
public: //IOrbitMovement
	HRESULT STDMETHODCALLTYPE PutOnOrbit(POINTF* pptOrbitCentre,float fAngle,float fRadOrbit);
	HRESULT STDMETHODCALLTYPE MakeCurPosBeOnOrbit(POINTF* pptOrbitCentre);
	HRESULT STDMETHODCALLTYPE SetOrbitDir(int nMoveDir);
	HRESULT STDMETHODCALLTYPE EnableOrbitMovement(BOOL bIsOnOrbit);
	HRESULT STDMETHODCALLTYPE GetOrbitCentre(POINTF* pptOrbitCentre);
	HRESULT STDMETHODCALLTYPE CheckOnOrbit(BOOL *pbIsOnOrbit);
public: //IResistForces
	HRESULT STDMETHODCALLTYPE ResetForces();
	HRESULT STDMETHODCALLTYPE SetGravity(POINTF *pvecGravAccel);
	HRESULT STDMETHODCALLTYPE SetFriction(POINTF *pvecFric);
public: //IJump
	HRESULT STDMETHODCALLTYPE SetJumpSpeed(float fJSpeed);
	HRESULT STDMETHODCALLTYPE Jump();
public: //IUnknown
	STDMETHODIMP QueryInterface(REFIID idInterface, void **ppInterface);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
protected: //ILinearMovement and FOR ALL
	float m_fVel;
	POINTF m_vecVel;
protected: //IAccelMovement
	float m_fAccel;
	POINTF m_ortAcc;
	int m_nAccOn;
	float m_fMaxVel;
private: //IRotation
	float m_fAngle;
	float m_sina,m_cosa;
private: //IOrbitMovement
	POINTF m_ptOrbitCentre;
	float m_fOrbitRad;
	bool m_bOnOrbit;
	int m_nOrbitDir;
private: //IResistForces
	POINTF m_vecGravAccel;
	POINTF m_vecFricAccel;
private: //IJump
	float m_fJumpVel;
private: //IPhysics
	int m_nGroundY;
	int m_nReactBoundsType;
	RECT m_rcMoveBounds;
	BOOL m_bBoundsMoveWithCamera;

//OTHER FUN
private:
	HRESULT STDMETHODCALLTYPE KeepOnOrbit(int nDirectionMove);
	HRESULT STDMETHODCALLTYPE CalculateSpeed();
	HRESULT STDMETHODCALLTYPE Move();
};