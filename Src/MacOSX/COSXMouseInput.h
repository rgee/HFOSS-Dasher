/*
 *  COSXMouseInput.h
 *  Dasher
 *
 *  Created by Doug Dickinson on 21/11/2006.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#import "../DasherCore/DasherInput.h"
#import "../DasherCore/DasherTypes.h"

#import <iostream>

using namespace Dasher;

class COSXMouseInput : public CDasherInput {
public:
  COSXMouseInput(CEventHandler * pEventHandler, CSettingsStore * pSettingsStore) 
  : CDasherInput(pEventHandler, pSettingsStore, 0, 0, "Mouse Input") {
  };
  
  // Fill pCoordinates with iN coordinate values, return 0 if the
  // values were in screen coordinates or 1 if the values were in
  // Dasher coordinates.
  
  virtual int GetCoordinates(int iN, myint * pCoordinates) {
    
    pCoordinates[0] = m_iX;
    pCoordinates[1] = m_iY;
    
    return 0;
  };
  
  // Get the number of co-ordinates that this device supplies
  
  virtual int GetCoordinateCount() {
    return 2;
  };
  
  void SetCoordinates(myint _iX, myint _iY) {
    m_iX = _iX;
    m_iY = _iY;
  };
  
private:
    myint m_iX;
  myint m_iY;
  
};

static SModuleSettings sSettings[] = {
  {LP_YSCALE, T_LONG, 10, 2000, 1, 1, "Pixels covering Y range:"}
};

class COSX1DMouseInput:public CDasherInput {
public:
  COSX1DMouseInput(CEventHandler * pEventHandler, CSettingsStore * pSettingsStore) 
  : CDasherInput(pEventHandler, pSettingsStore, 2, 0, "One Dimensional Mouse Input") {
    
    m_iOffset = 0;
  };
  
  // Fill pCoordinates with iN coordinate values, return 0 if the
  // values were in screen coordinates or 1 if the values were in
  // Dasher coordinates.
  
  virtual int GetCoordinates(int iN, myint * pCoordinates) {
    
    pCoordinates[0] = m_iY - m_iOffset;// * m_iDasherMaxY / 1024;      // FIXME - hard coded screen resolution!!!!!!!!!!
    
    //    std::cout << m_iY << " " << pCoordinates[0] << std::endl;
    
    return 1;
  };
  
  // Get the number of co-ordinates that this device supplies
  
  virtual int GetCoordinateCount() {
    return 1;
  };
  
  virtual void SetMaxCoordinates(int iN, myint * iDasherMax) {
    
    // FIXME - need to cope with the more general case here
    
    m_iDasherMaxX = iDasherMax[0];
    m_iDasherMaxY = iDasherMax[1];
  };
  
  void SetCoordinates(myint _iX, myint _iY) {
    m_iX = _iX;
    m_iY = _iY;
  };
  
  void KeyDown(int iTime, int iId) {
    if(iId == 10) {
      m_iOffset = m_iY - 2048;
    }
  };
  
  bool GetSettings(SModuleSettings **pSettings, int *iCount) {
    *pSettings = sSettings;
    *iCount = sizeof(sSettings) / sizeof(SModuleSettings);
    
    return true;
  };
  
private:
    
    myint m_iDasherMaxX;
  myint m_iDasherMaxY;
  
  myint m_iX;
  myint m_iY;
  
  myint m_iOffset;
};
