/* World.h

The MIT License (MIT)

Copyright (c) 2007 Evgeny A. Kozhevnikov <evgeny@kozhevnikov.org>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


Revision history:
	02 Mar 2007 - initial creation

*/

#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

#include <math.h>

// Forward declarations
class CWorldRenderer;

const int nMaxParticles = 65536;		// ������������ ����� ������

struct SParticle
{
	double x,y;		// position
	double vx, vy;	// velocity
	int color;		// 0 ������� �������� �����, 1 - ������
};

struct SGeometry
{
	double Xleft, ParticleXleft;			// ����� ������� (� ������)
	double Xcenter, ParticleWLeft, ParticleWRight;			// ����������� (� ������)
	double WThickness;		// Wall thickness
	double WLeft, WRight;
	double YGapTop;			// ������� ���� �����������
	double YGapBottom;		// ������ ���� �����������
	double ParticleHoleTop, ParticleHoleBottom;
	double HoleSize, HolePosition;
	double Xright, ParticleXright;			// ������ ������� (� ������)
	double Ymax, ParticleYmax;			// ������� ������� (� ������)
	double Ymin, ParticleYmin;			// ������ ������� (� ������)
	double Rparticle;		// ������ ����� �������  (� ������)
};


class CWorld
{
// Construction/destruction
public:
	CWorld();
	virtual ~CWorld();

// Public overridable methods
public:

// Protected overridable methods
protected:

// Public methods
public:
	BOOL InitialDistribution();
	void OnIdle();
	int GetLeftParticleCount() { return nLeftParticles; }
	int GetRightParticleCount() { return nRightParticles; }
	int GetParticleCount() { return (nLeftParticles+nRightParticles); }
	SParticle *GetParticle(int iParticle) { return particle + iParticle; }
	SGeometry *GetGeometry() { return &Geometry; }
	unsigned char *getLeftColor() { return m_LeftColor.c; }
	unsigned char *getRightColor() { return m_RightColor.c; }
	void SetRenderer(CWorldRenderer *pRenderer) { m_pRenderer = pRenderer; }

// Public members
public:
	double			Time;				// ������� ����� (� ��������)
	double			DeltaTime;			// ��� �� ������� (� ��������)
	unsigned long	nRight;				// ���������� ������ � ������ �����
	unsigned long	nLeft;				// ���������� ������ � ����� �����
	double			VaverageR;			// ������� �������� ������ � ������ �����
	double			VaverageL;			// ������� �������� ������ � ����� �����
	int nLeftParticles, nRightParticles;// �������� ����� ������


// Protected methods
protected:
	int LoadInt(char *pszValueName, int nDefaultValue);
	void SaveInt(char *pszValueName, int nValue);
	double LoadDouble(char *pszValueName, double fDefaultValue);
	void SaveDouble(char *pszValueName, double fValue);
	double random(double from, double to);
	double Distance2(SParticle &p1, SParticle &p2);
	double Distance(SParticle &p1, SParticle &p2) { return sqrt(Distance2(p1, p2)); }
	BOOL InContact(SParticle &p1, SParticle &p2) { return (Distance(p1, p2) < 2*Geometry.Rparticle); }
	BOOL Approaching(SParticle &p1, SParticle &p2);
	double GetVelocity(SParticle &p) { return sqrt(p.vx*p.vx + p.vy*p.vy); }
	void Collision(SParticle &p1, SParticle &p2);
	void RandomVelocity(SParticle &p);
	void CalcTimeStep();
	void RecalcStat();
	void MoveParticle(SParticle &p, double dt);
	void BounceX(SParticle &p) { p.vx = -p.vx; }
	void BounceY(SParticle &p) { p.vy = -p.vy; }
	void WriteStat();
	BOOL OneTimeStep();
	BOOL CorrectParticleByGeometry(SParticle &p);


// Private methods
private:

// Protected members
protected:
	SParticle particle[nMaxParticles];		// ���� �������
	SGeometry Geometry;
	double Vinit;			// ��������� �������� ���� ������ (� ������/���)
	// Collisions
	double DeltaVtop;		// ������� ��������, ������� �������� �������, �������� � ������� ������
	double DeltaVbottom;	// ������� ��������, ������� �������� �������, �������� � ������ ������
	double DeltaVside;		// ������� ��������, ������� �������� �������, �������� � ������� ������
	double loss;			// ����������� ���������� ������������ �������

	double g;				// ��������� ���������� ������� (� �/�**2)

	CString FileName;		// ��� ����� � ���������� �����������

	// ����������� �������� (����������)
	unsigned long	nTimeSteps;			// ���������� ���������� ����� �� �������

	double			LastTimeWritten;	// �����, ������� ���� �������� � ���� ��������� ���
	int				nFluxFromLeft;
	int				nFluxFromRight;
	union
	{
		unsigned char c[4];
		COLORREF rgb;
	} m_LeftColor, m_RightColor;
	CWorldRenderer *m_pRenderer;

// Private members
private:
};


#endif //__WORLD_H_INCLUDED__

