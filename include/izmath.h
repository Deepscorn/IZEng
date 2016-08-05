///////////////////////////////////////////////////////////
//  tstr.h
//  string convertions
//  Created on:      25-мар-2011 21:59:07
///////////////////////////////////////////////////////////

#if !defined(GUID_2FB41100_EF12_4f55_8DC6_0E65FBFE10E5__INCLUDED_)
#define GUID_2FB41100_EF12_4f55_8DC6_0E65FBFE10E5__INCLUDED_

#include "ocidl.h"
#include <cmath>
using namespace std;

namespace izmath {
//<---CONSTANT--->//
const float PI = 3.141592654f;
const float PI_DIV_2 = 1.570796327f;
const float PI_DIV_180 = 0.017453292f;
const float NIL = 0.1f;
const float M180_DIV_PI = 57.295779513f;
const float PI_MUL_2 = 6.283185307f;

//>---CONSTANT---<//
//<---POINTS AND VECTORS (POINTF) REALIZATION--->//
	int sign(float dbNum);
	float sqr(float f);
	/*
	Грубая проверка float на ноль, abs(f)<=NIL значит, что f - ноль
	*/
	BOOL IsNil(float f);
	/*
	Инициализирует POINTF
	*/
	void Set(POINTF& pt,float x, float y);
	/*
	Инициализирует RECT
	*/
	void Set(RECT& rc,int x0,int y0, int x1, int y1);
	POINTF operator-(POINTF pt1, POINTF pt2);
	POINTF operator-(POINTF pt1,float f);
	POINTF operator-(POINTF pt);
	POINTF operator*=(POINTF& pt1, float f);
	POINTF operator/(POINTF pt1, float f);
	//вызывает более быстрый и менее точный dist()
	inline float length(POINTF& vector);
	POINTF Normal(POINTF& vec,int nDir);
	POINTF Normal(POINTF& vec);
	int dist(POINTF& vector);
	POINTF& ToOrt(POINTF& vec);
	BOOL PtInRect(POINTF& pt,RECT& rc);
	RECT operator+(RECT rc, POINTF pt);
	RECT operator-(RECT rc, POINTF pt);
	void Normalize(POINTF ort);
	//POINT
	POINT operator*(POINT pt, int n);
	BOOL operator!=(POINT pt1,POINT pt2);
//>---POINTS AND VECTORS (POINTF) REALIZATION---<//

//<---ADDITIONAL--->//
	////////VAR///////////////

//sin/cos
// storage for our lookup tables
extern float cos_look[360]; // 1 extra element so we can store 0-360 inclusive
extern float sin_look[360];

float LookSin(int nAngle);
float LookCos(int nAngle);

void Build_Sin_Cos_Tables(void);
//FUNCTIONS
int sign(int n);
int rand_range(int a, int b);
double length(const POINTF& vec);
int dist(const POINTF& vector);
POINTF operator/=(POINTF& pt, float fNum);
POINTF operator/=(POINTF& pt1, int n);
POINTF operator+(POINTF pt1, POINTF pt2);
POINTF operator-(POINTF pt1, POINTF pt2);
POINTF operator-(POINTF pt1,float f);
POINTF operator*(POINTF pt1, float f);
POINTF operator/(POINTF pt1, float f);
BOOL operator>(POINTF& pt1,POINTF& pt2);
POINTF Ort(POINTF& vec);
POINTF operator*(double d, POINTF pt);
BOOL operator<=(POINTF pt1,POINTF pt2);
POINTF operator+=(POINTF& ptDest,POINTF ptToAdd);
BOOL IsNil(POINTF& pt);
BOOL operator>(POINTF& pt, float f);
POINTF MultSeparate(POINTF& vec1, POINTF& vec2);
POINTF sign(POINTF& pt);
RECT operator+=(RECT& rc,POINTF& pt);
POINTF operator/=(POINTF& pt1, double db);
POINTF LeftTopOf(const RECT& rc);
POINTF RightBottomOf(const RECT& rc);
POINTF RightTopOf(const RECT& rc);
POINTF LeftBottomOf(const RECT& rc);
inline POINTF Pt(float x,float y) { POINTF result = {x,y}; return result; }
//FUNCTIONS
//CLOCK
extern DWORD tmStartClock;
DWORD StartClock();
DWORD GetClock();
DWORD WaitClock(DWORD tmWait);
//OTHER
int round(float f);
int sround(float f);
bool CheckInRect(int x,int y,RECT& rc);
void Nullify(POINTF& pt);
RECT GetRect(POINTF pt,int w,int h);
RECT GetRectWH(POINTF pt,int w,int h);
POINTF Vec(float x, float y);
void Rotate(POINTF& vecToRot,POINTF vecAngle,int nDir);
void Rotate(POINTF& vecToRot,POINTF vecAngle);
BOOL approx_coords(float& x, int w,int l, int r);
void approx_coords(POINTF& pt, int w,int h,RECT rcBounds);
BOOL teleport_coord(float& x, int w, int l, int r);
void teleport_coords(POINTF& ptCoords,int w, int h,RECT rcMoveBounds);
void teleport_coords_rand(POINTF& ptCoords,int w, int h,RECT rcMoveBounds);
//>---ADDITIONAL---<//
}

#endif //!defined(GUID_2FB41100_EF12_4f55_8DC6_0E65FBFE10E5__INCLUDED_)