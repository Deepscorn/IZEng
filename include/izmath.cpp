#include "izmath.h"
#include <cmath>
using namespace std;

namespace izmath {
//defs
		//PI's
	#define PI         ((float)3.141592654f)
	#define PI_DIV_2 ((float)1.570796327f)
	#define PI_DIV_180 ((float)0.017453292f)
	#define NIL 0.1
//fun
	int sign(float dbNum) { if(dbNum==0) return(0); return (dbNum<0)?-1:1; }
	float sqr(float f) { return f*f;}
	 BOOL IsNil(float f) { return(abs(f)<=NIL);}
	 void Set(POINTF& pt,float x, float y) {
		pt.x=x;
		pt.y=y;
	}
	 void Set(RECT& rc,int x0,int y0, int x1, int y1) {
		rc.left=x0;
		rc.top=y0;
		rc.right=x1;
		rc.bottom=y1;
	}
	//POINTS AND VECTORS
	POINTF operator+(POINTF pt1, POINTF pt2) {
		POINTF ptRes;
		ptRes.x=pt1.x+pt2.x;
		ptRes.y=pt1.y+pt2.y;
		return(ptRes);
	}

	POINTF operator-(POINTF pt1, POINTF pt2) {
		POINTF ptRes;
		ptRes.x=pt1.x-pt2.x;
		ptRes.y=pt1.y-pt2.y;
		return(ptRes);
	}

	POINTF operator-(POINTF pt1,float f) {
		POINTF ptRes;
		ptRes.x=pt1.x-f;
		ptRes.y=pt1.y-f;
		return(ptRes);
	}

	POINTF operator-(POINTF pt) {
		pt.x=-pt.x;
		pt.y=-pt.y;
		return(pt);
	}

	POINTF operator/=(POINTF& pt1, double db) {
		pt1.x/=db;
		pt1.y/=db;
		return(pt1);
	}
	POINTF operator*=(POINTF& pt1, double db) {
		pt1.x*=db;
		pt1.y*=db;
		return(pt1);
	}

	POINTF operator*(POINTF pt1, double db) {
		POINTF ptRes;
		ptRes.x=pt1.x*db;
		ptRes.y=pt1.y*db;
		return(ptRes);
	}
	POINTF operator/(POINTF pt1, float f) {
		POINTF ptRes;
		ptRes.x=pt1.x/f;
		ptRes.y=pt1.y/f;
		return(ptRes);
	}
	 inline float length(POINTF& vector) {
		return dist(vector);
		//return(sqrt(sqr(vector.x)+sqr(vector.y)));
	}
	 POINTF Normal(POINTF& vec,int nDir) {
		 POINTF vecNormal = {nDir*vec.y,nDir*(-vec.x) };
		 return(vecNormal);
	 }
	 POINTF Normal(POINTF& vec) {
		 POINTF vecNormal = {vec.y,-vec.x};
		 return(vecNormal);
	 }
	 int dist(POINTF& vector)
	{
		int x = abs(vector.x);
		int y = abs(vector.y);
		int mn = min(x,y);
		return(x+y-(mn>>1)-(mn>>2)+(mn>>4));
	}
	 POINTF& ToOrt(POINTF& vec) { //преобразует вектор к орту
		return vec/=length(vec);
	}
	 POINTF& ToPerpendicular(POINTF& vec,int nDir) {//поворачивает вектор на 90 градусов,
		//-1 - левый перпендикуляр, 1 - правый
		float fX = vec.x;
		vec.x=vec.y;
		vec.y=fX;
		if(nDir==1)
			vec.x=-vec.x;
		if(nDir==-1)
			vec.y=-vec.y;
		return vec;
	}
	 POINTF Ort(POINTF& vec) {
		POINTF ortRes = {0,0};
		float len = sqrt(sqr(vec.x)+sqr(vec.y));
		if(!IsNil(len))
			ortRes=vec/len;
		return(ortRes);
	}

	POINTF Vec(float x, float y) {
		POINTF vecRes = {x,y};
		return(vecRes);
	}

	 BOOL PtInRect(POINTF& pt,RECT& rc) {
		return(rc.left<=pt.x && pt.x<=rc.right &&
			rc.top<=pt.y && pt.y<=rc.bottom);
	}
	 RECT operator+(RECT rc, POINTF pt) {
		 RECT rcRes = rc;
		 rcRes.left+=pt.x;
		 rcRes.top+=pt.y;
		 rcRes.right+=pt.x;
		 rcRes.bottom+=pt.y;
		 return(rcRes);
	 }
	 RECT operator-(RECT rc, POINTF pt) {
		 RECT rcRes = rc;
		 rcRes.left-=pt.x;
		 rcRes.top-=pt.y;
		 rcRes.right-=pt.x;
		 rcRes.bottom-=pt.y;
		 return(rcRes);
	 }
	void Normalize(POINTF ort) {
		if(IsNil(abs(ort.x)-abs(ort.y))) {
			ort.x=sign(ort.x)*0.707;
			ort.y=sign(ort.y)*0.707;
		}
	}
	void Rotate(POINTF& vecToRot,POINTF vecAngle) {
		float xo=vecToRot.x,yo=vecToRot.y;
		vecToRot.x=xo*vecAngle.x-yo*vecAngle.y;
		vecToRot.y=xo*vecAngle.y+yo*vecAngle.x;
	}
	//POINT
	POINT operator*(POINT pt, int n) {
		POINT ptRes;
		ptRes.x=pt.x*n;
		ptRes.y=pt.y*n;
		return(ptRes);
	}
	BOOL operator!=(POINT pt1,POINT pt2) {
		return (pt1.x!=pt2.x || pt1.y!=pt2.y);
	}

	float cos_look[360];
float sin_look[360];

float LookSin(int nAngle) {
	return(sin_look[nAngle%360]);
}

float LookCos(int nAngle) {
	return(cos_look[nAngle%360]);
}

//FUNCTIONS
void Build_Sin_Cos_Tables(void)
{
  
// create sin/cos lookup table
// note the creation of one extra element; 360
// this helps with logic in using the tables

// generate the tables 0 - 360 inclusive
for (int ang = 0; ang < 360; ang++)
    {
    // convert ang to radians
    float theta = (float)ang*PI/(float)180;

    // insert next entry into table
    cos_look[ang] = cos(theta);
    sin_look[ang] = sin(theta);

    } // end for ang

} // end Build_Sin_Cos_Tables

int sign(int n) { /*if(n==0) return(0); */return (n<0)?-1:1; }
int rand_range(int a, int b) { return a + rand()%(b-a+1); }
double length(const POINTF& vec) {
	return(sqrt(sqr(vec.x)+sqr(vec.y)));
}
int dist(const POINTF& vector)
{
	int x = abs(vector.x);
	int y = abs(vector.y);
	int mn = min(x,y);
	return(x+y-(mn>>1)-(mn>>2)+(mn>>4));
}
//POINTF arithmetics
POINTF operator/=(POINTF& pt, float fNum) {
	pt.x/=fNum;
	pt.y/=fNum;
	return(pt);
}

POINTF operator*(POINTF pt1, float f) {
	POINTF ptRes;
	ptRes.x=pt1.x*f;
	ptRes.y=pt1.y*f;
	return(ptRes);
}

POINTF operator*(double d, POINTF pt) {
	POINTF ptRes=pt;
	ptRes.x*=d;
	ptRes.y*=d;
	return(ptRes);
}

BOOL operator<=(POINTF pt1,POINTF pt2) {
	return(sqrt(sqr(pt1.x)+sqr(pt1.y))<=sqrt(sqr(pt2.x)+sqr(pt2.y)));
}
BOOL operator>(POINTF& pt1,POINTF& pt2) {
	return(dist(pt1)>dist(pt2));
}

POINTF operator+=(POINTF& ptDest,POINTF ptToAdd) {
	ptDest.x+=ptToAdd.x;
	ptDest.y+=ptToAdd.y;
	return(ptDest);
}

RECT operator+=(RECT& rc,POINTF& pt) {
	rc.left+=pt.x;
	rc.right+=pt.x;
	rc.top+=pt.y;
	rc.bottom+=pt.y;
	return(rc);
}
BOOL IsNil(POINTF& pt) {
	return(abs(pt.x)<NIL && abs(pt.y)<NIL);
}
BOOL operator>(POINTF& pt, float f) {
	return(dist(pt)>f);
}
POINTF MultSeparate(POINTF& vec1, POINTF& vec2) {
	POINTF ptRes = vec1;
	ptRes.x *= vec2.x;
	ptRes.y *= vec2.y;
	return(ptRes);
}
//OTHER

POINTF sign(POINTF& pt) {
	POINTF ptRes = {sign(pt.x),sign(pt.y)};
	return(ptRes);
}
POINTF operator/=(POINTF& pt1, int n) {
	pt1.x/=n;
	pt1.y/=n;
	return(pt1);
}

//FUNCTIONS
//CLOCK
DWORD tmStartClock=0;

DWORD StartClock() {
	return(tmStartClock = GetTickCount());
}
DWORD GetClock() {
	return(GetTickCount());
}
DWORD WaitClock(DWORD tmWait) {
	while(GetClock()-tmStartClock < tmWait);
	tmStartClock = GetClock();
	return(GetClock());
}
//OTHER
int round(float f)
{ 
	return int(f+0.5); 
}
int sround(float f) {
	if(f<0)
		return int(f-0.5);
	return int(f+0.5);
}
bool CheckInRect(int x,int y,RECT& rc) {
	return (rc.left<=x && x<=rc.right && rc.top<=y && y<=rc.bottom);
}

void Nullify(POINTF& pt) {
	pt.x=0;
	pt.y=0;
}
BOOL approx_coords(float& x, int w,int l, int r) {
	if(x+w>r) {
		x=r-w;
		return(TRUE);
	}
	if(x<l) {
		x=l;
		return(TRUE);
	}
	return(FALSE);
}
void approx_coords(POINTF& pt, int w,int h,RECT rcBounds) {
	approx_coords(pt.x,w,rcBounds.left,rcBounds.right);
	approx_coords(pt.y,h,rcBounds.top,rcBounds.bottom);
}

BOOL teleport_coord(float& x, int w, int l, int r) {
	if(x+w<l) {
		x=r;
		return(TRUE);
	}
	if(x>r) {
		x=l-w;
		return(TRUE);
	}
	return(FALSE);
}

void teleport_coords(POINTF& ptCoords,int w, int h,RECT rcMoveBounds) {
	teleport_coord(ptCoords.x,w,rcMoveBounds.left,rcMoveBounds.right);
	teleport_coord(ptCoords.y,h,rcMoveBounds.top,rcMoveBounds.bottom);
}

void teleport_coords_rand(POINTF& ptCoords,int w, int h,RECT rcMoveBounds) {
	if(teleport_coord(ptCoords.x,w,rcMoveBounds.left,rcMoveBounds.right))
		ptCoords.y=rand_range(rcMoveBounds.top,rcMoveBounds.bottom);
	if(teleport_coord(ptCoords.y,h,rcMoveBounds.top,rcMoveBounds.bottom))
		ptCoords.x=rand_range(rcMoveBounds.left,rcMoveBounds.right);
}

RECT GetRect(POINTF pt,int w,int h) {
	RECT rcRes = {pt.x,pt.y,pt.x+w,pt.y+h};
	return(rcRes);
}

RECT GetRectWH(POINTF pt,int w,int h) {
	RECT rcRes = {pt.x,pt.y,w,h};
	return(rcRes);
}


void Rotate(POINTF& vecToRot,POINTF vecAngle,int nDir) {
	float xo=vecToRot.x,yo=vecToRot.y;
	vecToRot.x=xo*vecAngle.x-nDir*yo*vecAngle.y;
	vecToRot.y=nDir*xo*vecAngle.y+yo*vecAngle.x;
}

POINTF LeftTopOf(const RECT& rc) {
	POINTF result = { rc.left, rc.top };
	return result;
}

POINTF RightBottomOf(const RECT& rc) {
	POINTF result = { rc.right, rc.bottom };
	return result;
}

POINTF RightTopOf(const RECT& rc) {
	POINTF result = { rc.right, rc.top };
	return result;
}

POINTF LeftBottomOf(const RECT& rc) {
	POINTF result = { rc.left, rc.bottom };
	return result;
}

}