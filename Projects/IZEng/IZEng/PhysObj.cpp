#include "PhysObj.h"
#include <cmath>

//OTHER
#include "izmath.h"

using namespace std;
using namespace izmath;

////////CONSTRUCTOR/////////////////////////////

PhysObj::PhysObj() {
//ILinearMovement and for ALL
	m_fVel=0;
	Nullify(m_vecVel);
//IAccelMovement
	m_fAccel=0;
	Nullify(m_ortAcc);
	m_fMaxVel=32000;
	m_nAccOn=TYPE_NO;
//IRotation
	m_sina=LookSin(0);
	m_cosa=LookCos(0);
//IOrbitMovement
	ZeroMemory((void*)&m_ptOrbitCentre,sizeof(m_ptOrbitCentre));
	m_nOrbitDir=1;
	m_bOnOrbit=false;
	m_fOrbitRad=200;
//IResistForces
	ResetForces();
//IPhysics
	m_nGroundY=32000;
//IJump
	m_fJumpVel=0;
//bounds react
	m_nReactBoundsType=REACT_NO;
	m_bBoundsMoveWithCamera=FALSE;
}

PhysObj::~PhysObj() {}

/////////IPHYSICS////////////////////

HRESULT STDMETHODCALLTYPE PhysObj::CheckStopped(BOOL *pbStopped) {
	*pbStopped = (abs(m_vecVel.x)<NIL) && (abs(m_vecVel.y)<NIL);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetNoGround() {
	m_nGroundY=INFINITE;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetGround(int nYGroundLevel) {
	m_nGroundY = nYGroundLevel;
	m_ptCoords.y=nYGroundLevel-m_nFrameH;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetBounds(RECT rcBounds,BOOL bMoveWithCamera) {
	m_bBoundsMoveWithCamera = bMoveWithCamera;
	m_rcMoveBounds = rcBounds;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetBoundsReact(int nReact) {
	m_nReactBoundsType = nReact;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::CalculateSpeed() {
	//{NAME}
	//{TRY: new}
	//{analyse: new and old => make changes}
	//{analyse: logics =>make changes}
	//{SET: new speed}

	//Orbit movement
	if(m_bOnOrbit)
		KeepOnOrbit(m_nOrbitDir);
	//Here goes all calculations, where accel is needed!
	//so let's return if no accel is used (only velocity, for example)
	if(m_nAccOn == TYPE_NO)
		return(S_OK);
	//Acceleration
	POINTF vecVel_new = {0,0};
	if(m_nAccOn==TYPE_ACCEL)
		vecVel_new = m_vecVel + m_nAccOn*m_ortAcc*m_fAccel;
	if(m_nAccOn==TYPE_BRAKE)
		vecVel_new = m_vecVel + m_nAccOn*Ort(m_vecVel)*m_fAccel;
	//vecVel_new = m_vecVel + m_nAccOn*m_ortAcc*m_fAccel;
	if(m_nAccOn==TYPE_BRAKE) { //brake
		if(abs(m_vecVel.x)<abs(vecVel_new.x))
			vecVel_new.x=0;
		if(abs(m_vecVel.y)<abs(vecVel_new.y))
			vecVel_new.y=0;
	}	
	if(vecVel_new>m_fMaxVel) //speed bound
		vecVel_new = Ort(vecVel_new)*m_fMaxVel;
	m_vecVel = vecVel_new;
	//Friction
	vecVel_new = m_vecVel - MultSeparate(m_vecFricAccel,sign(m_vecVel));
	if(abs(m_vecVel.x)<abs(vecVel_new.x))
		vecVel_new.x=0;
	if(abs(m_vecVel.y)<abs(vecVel_new.y))
		vecVel_new.y=0;
	m_vecVel = vecVel_new;
	//Gravity
	vecVel_new = m_vecVel + m_vecGravAccel;
	if(m_ptCoords.y+vecVel_new.y+m_nFrameH>m_nGroundY) //ground bound
		vecVel_new.y = m_nGroundY-m_ptCoords.y-m_nFrameH;
	m_vecVel=vecVel_new;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::Move() {
//COORDINATES INCREASES
	m_ptCoords+=m_vecVel;
//BOUNDS REACT (if they exist)
	if(m_nReactBoundsType==REACT_NO)
		return(S_OK);

	RECT rcMoveBounds = m_rcMoveBounds; //get bounds
	if(m_bBoundsMoveWithCamera)
		rcMoveBounds+=m_ptCam;

	if(m_nReactBoundsType==REACT_STOP) {
		if(approx_coords(m_ptCoords.x,m_nFrameW,rcMoveBounds.left,rcMoveBounds.right))
			m_vecVel.x=0;
		if(approx_coords(m_ptCoords.y,m_nFrameH,rcMoveBounds.top,rcMoveBounds.bottom))
			m_vecVel.y=0;
	}
	if(m_nReactBoundsType==REACT_BOUNCE) {
		if(approx_coords(m_ptCoords.x,m_nFrameW,rcMoveBounds.left,rcMoveBounds.right))
			m_vecVel.x=-m_vecVel.x;
		if(approx_coords(m_ptCoords.y,m_nFrameH,rcMoveBounds.top,rcMoveBounds.bottom))
			m_vecVel.y=-m_vecVel.y;
	}
	if(m_nReactBoundsType==REACT_TELEPORT) {
		teleport_coords(m_ptCoords,m_nFrameW,m_nFrameH,rcMoveBounds);
	}
	if(m_nReactBoundsType==REACT_RAND_TELEPORT) {
		teleport_coords_rand(m_ptCoords,m_nFrameW,m_nFrameH,rcMoveBounds);
	}
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::UpdatePhysics() {
	list<VisObj*>::iterator it;
	for(it = m_visObjs.begin();it!=m_visObjs.end();it++) {
		((PhysObj*)*it)->CalculateSpeed();
		((PhysObj*)*it)->Move();
	}
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::CheckCollisionCircleCircle(IParams* pOtherObj, BOOL* bCollision) {
	*bCollision = FALSE;
	POINTF ptA,ptB;
	float radA,radB;
	GetCentreCoordsPt(&ptA);
	pOtherObj->GetCentreCoordsPt(&ptB);
	GetSmallestRad(&radA);
	pOtherObj->GetSmallestRad(&radB);
	if(dist(ptB - ptA)<radA+radB)
		*bCollision = TRUE;
	return(S_OK);
}

///////ILINEARMOVEMENT////////////////
HRESULT STDMETHODCALLTYPE PhysObj::SetSpeed(float fSpeed) {
	m_fVel = fSpeed;
	if(IsNil(dist(m_vecVel))) return(S_OK);
	m_vecVel = Ort(m_vecVel)*fSpeed;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetOrtVel(POINTF *portVel, BOOL bSetSpeedIgnored) {
	if(bSetSpeedIgnored)
		m_fVel = dist(m_vecVel);
	m_vecVel=*portVel*m_fVel;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetVel(POINTF *pvecVel) {
	m_vecVel = *pvecVel;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetVel(POINTF *pvecVel) {
	*pvecVel = m_vecVel;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetOrtVel(POINTF *portVel) {
	*portVel = Ort(m_vecVel);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetRealSpeed(float *pfSpeed) {
	*pfSpeed = dist(m_vecVel);
	return(S_OK);
}

//UNSAFE!
HRESULT STDMETHODCALLTYPE PhysObj::SetDirX(float fEX, BOOL bSetSpeedIgnored) {
	if(bSetSpeedIgnored)
		m_fVel = dist(m_vecVel);
	m_vecVel.x = fEX*m_fVel;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetDirY(float fEY, BOOL bSetSpeedIgnored) {
	if(bSetSpeedIgnored)
		m_fVel = dist(m_vecVel);
	m_vecVel.y = fEY*m_fVel;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetVelX( float *pfVelX) {
	*pfVelX=m_vecVel.x;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetVelY( float *pfVelY) {
	*pfVelY=m_vecVel.y;
	return(S_OK);
}

///////////IAccelMovement/////////////////
HRESULT STDMETHODCALLTYPE PhysObj::SetAccel(float fAccel) {
	m_fAccel=fAccel;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetMaxSpeed(float fMaxSpeed) {
	m_fMaxVel = fMaxSpeed;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetOrtAccel(POINTF *portAcc) {
	m_ortAcc = *portAcc;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::EnableAccel(int nAccelType) {
	m_nAccOn = nAccelType;
	return(S_OK);
}

//Get
HRESULT STDMETHODCALLTYPE PhysObj::GetAccel(float *pfAccel) {
	*pfAccel=m_fAccel;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetOrtAccel(POINTF *portAccel) {
	*portAccel = m_ortAcc;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetMaxSpeed(float *pfMaxSpeed) {
	*pfMaxSpeed=m_fMaxVel;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetAccelType(int *pnAccelType) {
	*pnAccelType = m_nAccOn;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetVecAccel(POINTF *vecAccel) {
	*vecAccel = m_ortAcc*m_fAccel;
	return(S_OK);
}

//UNSAFE!

HRESULT STDMETHODCALLTYPE PhysObj::SetAccelDirX(float fEX) {
	m_ortAcc.x = fEX;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetAccelDirY(float fEY) {
	m_ortAcc.y = fEY;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetAccelEX(float *pfEX) {
	*pfEX = m_ortAcc.x;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetAccelEY(float *pfEY) {
	*pfEY = m_ortAcc.y;
	return(S_OK);
}

/////////////IRotation////////////////////
HRESULT STDMETHODCALLTYPE PhysObj::SetTurnAngle(float fAngle) {
	m_fAngle = fAngle;
	m_sina = LookSin(fAngle);
	m_cosa = LookCos(fAngle);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::Turn( int nDirection) {
	if(abs(nDirection)!=1) return(S_FALSE);
	//развернем вектор скорости
	POINTF vecRotation = {m_cosa,m_sina};
	Rotate(m_vecVel,vecRotation,nDirection);
	//развернем вектор ускорения
	Rotate(m_ortAcc,vecRotation,nDirection);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::StepTo(POINTF *pvec) {
	float dx=pvec->x,
		dy=pvec->y;
	double alpha=0;
	if(IsNil(dx))
		alpha=((dy>0)?90:-90);
	else {
		alpha = atan(dy/dx)/PI_DIV_180; 
		if(dx<0) //особенности atan
			alpha+=180;
	}
	double beta=0; 
	if(IsNil(m_vecVel.x))
		beta = ((m_vecVel.y>0)?90:-90);
	else {
		beta = atan(m_vecVel.y/m_vecVel.x)/PI_DIV_180;
		if(m_vecVel.x<0)
			beta+=180;
	}
	//если скорость ноль - анализ по ускорению, т.к. может быть
	//разворачиваем именно его
	if(IsNil(m_vecVel.x) && IsNil(m_vecVel.y)) {
		if(IsNil(m_ortAcc.x))
			beta = ((m_ortAcc.y>0)?90:-90);
		else {
			beta = atan(m_ortAcc.y/m_ortAcc.x)/PI_DIV_180;
			if(m_ortAcc.x<0)
				beta+=180;
		}
	}
	if(abs(alpha-beta)<acos(m_cosa)/PI_DIV_180) { //если угол поворота слишком велик чтобы повернуть 
		//на заданный курс (dx,dy)
		TurnImm(pvec);
		return(S_OK);
	}
	if(!IsNil(m_vecVel))
		return Turn(sign(dy*m_vecVel.x-dx*m_vecVel.y));
	else
		return Turn(sign(dy*m_ortAcc.x-dx*m_ortAcc.y));
}

HRESULT STDMETHODCALLTYPE PhysObj::TurnImm(POINTF* pvec) {
	POINTF ortAngle = Ort(*pvec);
	if(IsNil(ortAngle))
		return(FALSE);
	m_ortAcc=ortAngle;
	float fRealVel = dist(m_vecVel);
	if(!IsNil(fRealVel))
		m_vecVel = ortAngle*fRealVel;
	return(S_OK);
}

//GET
HRESULT STDMETHODCALLTYPE PhysObj::GetTurnAngle(float* pfAngle) {
	*pfAngle = m_fAngle;
	return(S_OK);
}

//////IOrbitMovement////////////////////////
HRESULT STDMETHODCALLTYPE PhysObj::PutOnOrbit(POINTF* pptOrbitCentre,float fAngle,float fRadOrbit) {
	m_ptOrbitCentre = *pptOrbitCentre;
	POINTF ortDir = {1,0};
	POINTF ortAngle = {LookCos(fAngle),LookSin(fAngle)};
	Rotate(ortDir,ortAngle);
	m_fOrbitRad=fRadOrbit;
	POINTF pt = m_ptOrbitCentre + ortDir*fRadOrbit - Vec(m_nFrameW*0.5,m_nFrameH*0.5);
	SetPos(&pt);
	m_bOnOrbit = true;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::MakeCurPosBeOnOrbit(POINTF* pptOrbitCentre) {
	m_ptOrbitCentre = *pptOrbitCentre;
	POINTF ptPhysObj;
	GetCentreCoordsPt(&ptPhysObj);
	m_fOrbitRad = dist(ptPhysObj-m_ptOrbitCentre);
	m_bOnOrbit = true;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetOrbitDir(int nMoveDir) {
	m_nOrbitDir = nMoveDir;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::EnableOrbitMovement(BOOL bIsOnOrbit) {
	m_bOnOrbit = bIsOnOrbit;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::GetOrbitCentre(POINTF* pptOrbitCentre) {
	*pptOrbitCentre=m_ptOrbitCentre;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::CheckOnOrbit(BOOL *pbIsOnOrbit) {
	*pbIsOnOrbit = m_bOnOrbit;
	return(S_OK);
}

////////////////////////////////////////

//////IResistForces/////////////////////
HRESULT STDMETHODCALLTYPE PhysObj::ResetForces() {
	Nullify(m_vecGravAccel);
	Nullify(m_vecFricAccel);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetGravity(POINTF *pvecGravAccel) {//действует постоянно
	m_vecGravAccel=*pvecGravAccel;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::SetFriction(POINTF *pvecFric) {
	m_vecFricAccel = *pvecFric;
	return(S_OK);
}

/////////IJump/////////////
HRESULT STDMETHODCALLTYPE PhysObj::SetJumpSpeed(float fJSpeed) {
	m_fJumpVel = fJSpeed;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE PhysObj::Jump() { 
	if(m_ptCoords.y+m_nFrameH==m_nGroundY)
		m_vecVel.y = -m_fJumpVel;
	return(S_OK);
}

/////////IUnknown//
STDMETHODIMP PhysObj::QueryInterface(REFIID idInterface, void **ppInterface) {
	*ppInterface=NULL;
	if(idInterface==IID_IPhysics)
		*ppInterface = (IPhysics*)this;
	if(idInterface==IID_ILinearMovement)
		*ppInterface = (ILinearMovement*)this;
	if(idInterface==IID_IRotation)
		*ppInterface = (IRotation*)this;
	if(idInterface==IID_IOrbitMovement)
		*ppInterface = (IOrbitMovement*)this;
	if(idInterface==IID_IAccelMovement)
		*ppInterface = (IAccelMovement*)this;
	if(idInterface==IID_IResistForces)
		*ppInterface = (IResistForces*)this;
	if(idInterface==IID_IJump)
		*ppInterface = (IJump*)this;
	if(*ppInterface) {
		((IUnknown*)*ppInterface)->AddRef();
		return(S_OK);
	}
	return VisObj::QueryInterface(idInterface,ppInterface);
}

STDMETHODIMP_(ULONG) PhysObj::AddRef() {return(++m_nRefCount);}
	
STDMETHODIMP_(ULONG) PhysObj::Release() {
	m_nRefCount--;
	if(m_nRefCount<=0)
		delete this;
	return(m_nRefCount);
}

//OTHER FUN

HRESULT STDMETHODCALLTYPE PhysObj::KeepOnOrbit(int nDirectionMove) {
	POINTF O = m_ptOrbitCentre;
	POINTF A;
	GetCentreCoordsPt(&A);
	POINTF r0 = A - O;
	POINTF r = m_fOrbitRad * Ort(A - O);
	POINTF v;
	GetVel(&v);
	
	if(IsNil(v))
		return(S_OK);

	POINTF r2 = r;
	float len_v = length(v),
		len_r = length(r);
	float temp = len_v/(2*len_r);
	POINTF vecSinCos = {cos(asin(temp)),temp};
	Rotate(r2,vecSinCos,nDirectionMove);

	POINTF v2 = O + r2 - A;
	SetOrtAccel(&Ort(v2));
	//SetVel(&v2);
	return(S_OK);
}