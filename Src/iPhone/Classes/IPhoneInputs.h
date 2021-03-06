/*
 *  CIPhoneInput.h
 *  Dasher
 *
 *  Created by Alan Lawrence on 29/04/2009.
 *  Copyright 2009 Cavendish Laboratory. All rights reserved.
 *
 */

#import "../DasherCore/DasherInput.h"
#import "../DasherCore/DasherTypes.h"

#import "SBTree.h"
#import <deque>
#import "Vec3.h"
//A bit odd I admit, but we use the same string as is the default input device in Parameters.h...
#define TOUCH_INPUT "Mouse Input"
#define TILT_INPUT "Tilt Input"
#define MIXED_INPUT "Mixed Inputs"
#define REVERSE_MIX "Reverse Mix"
namespace Dasher {

class CIPhoneInput : public CDasherInput {
public:
	CIPhoneInput(CEventHandler *pEventHandler, CSettingsStore *pSettingsStore, const char *name)
	: CDasherInput(pEventHandler, pSettingsStore, 0, 0, name) {};
	void SetScreenBounds(int maxX, int maxY) {this->maxX=maxX; this->maxY=maxY;}
		
	int GetCoordinateCount() {return 2;}
	
	// Fill pCoordinates with iN coordinate values, return 0 if the
	// values were in screen coordinates or 1 if the values were in
	// Dasher coordinates.
	virtual int GetCoordinates(int iN, myint * pCoordinates) {
		
		pCoordinates[0] = m_iX;
		pCoordinates[1] = m_iY;
		
		return 0;
	};
	
protected:
	myint m_iX, m_iY;
  int maxX, maxY;
};

class CIPhoneTiltInput : public CIPhoneInput {
public:
	CIPhoneTiltInput(CEventHandler * pEventHandler, CSettingsStore * pSettingsStore); 
	~CIPhoneTiltInput();
	
	void NotifyTilt(float fx, float fy, float fz);
	
	void SetAxes(Vec3 main, float offset, Vec3 slow, float slow_off)
	{
		this->main = main;
		this->offset = offset;
		this->slow = slow;
		this->slow_off = slow_off;
	}
	
	void Activate();
	void Deactivate();
	
private:
	Vec3 main, slow;
	float offset, slow_off;
	SBTree *xTilts, *yTilts;
	std::deque<int> *xHist, *yHist;
	id<UIAccelerometerDelegate> deleg;
};

class CIPhoneMouseInput : public CIPhoneInput {
public:
	CIPhoneMouseInput(CEventHandler * pEventHandler, CSettingsStore * pSettingsStore);

	void NotifyTouch(screenint _iX, screenint _iY) {
    if (GetBoolParameter(BP_DOUBLE_X)) _iX = std::min(2*_iX, maxX);
		m_iX = _iX;
		m_iY = _iY;
	};
};

class CMixedInput : public CDasherInput {
public:
	CMixedInput(CEventHandler *pEventHandler, CSettingsStore *pSettingsStore,
				CDasherInput *pXinput, CDasherInput *pYinput, const char *name)
	: CDasherInput(pEventHandler, pSettingsStore, 0, 0, name), m_pXinput(pXinput), m_pYinput(pYinput) {};
	
	int GetCoordinateCount() {return 2;}
	
	// Fill pCoordinates with iN coordinate values, return 0 if the
	// values were in screen coordinates or 1 if the values were in
	// Dasher coordinates.
	virtual int GetCoordinates(int iN, myint * pCoordinates);
	void Activate();
	void Deactivate();
private:
	CDasherInput *m_pXinput, *m_pYinput;
};
}
