// GameModule.h

#ifndef __GameModule_h__
#define __GameModule_h__

#include <string>
#include <cstring>

using namespace std;

#include "DasherScreen.h"
#include "DasherModel.h"
#include "DasherModule.h"
#include "DasherNode.h"
#include "DasherView.h"
#include "DasherTypes.h"
#include "DasherInterfaceBase.h"
#include "WordGeneratorBase.h"

namespace Dasher {

/**
 * This Dasher Module encapsulates all game mode logic. In game mode, users will be given
 * a target string to type as well as visual feedback for their progress and a helpful 
 * arrow to guide them in the right path through the dasher model.
 * 
 * The way target strings will be displayed and reasoned about in code is in terms
 * of chunks. Chunks represent the collection of strings that is displayed at once
 * on the screen. After typing all the words in a given chunk, a new chunk of size
 * m_iTargetChunkSize is gotten from the word generator and displayed.
 *
 * This class handles logic and drawing code with respect to the above.
 */
class CGameModule : public CDasherModule {
 public:
  CGameModule(Dasher::CEventHandler *pEventHandler, CSettingsStore *pSettingsStore,  
                CDasherInterfaceBase *pInterface, ModuleID_t iID, const char *szName,
                std::vector<int> vEvents, CWordGeneratorBase* pWordGenerator) 
  : m_iCrosshairColor(135),
    m_iCrosshairNumPoints(2),
    m_iCrosshairExtent(25),
    m_iCrosshairCrosslineLength(50),
    m_iTargetChunkSize(3),
    m_pWordGenerator(pWordGenerator),
    CDasherModule(pEventHandler, pSettingsStore, iID, 0, szName, vEvents)
  {     
    m_pInterface = pInterface;
    
    //TODO REMOVE THIS!!!
    if(m_pWordGenerator == NULL)
      g_pLogger->Log("Word generator creation FAILED");
    GenerateChunk();
    if(m_sTargetString == "")
      m_sTargetString = "My name is julian.";
    m_stCurrentStringPos = 0;
    
  }

  virtual ~CGameModule() {};

  /**
   * Gets the typed portion of the target string
   * @return The string that represents the current word(s) that have not been typed
   */
  std::string GetTypedTarget();

  /**
   * Gets the portion of the target string that has yet to be completed
   * @return The string that represents the current word(s) that have been typed
   */
  std::string GetUntypedTarget();


  /**
   * Draws Game Mode specific visuals to the screen.
   * @param pView The Dasher View to be modified
   * @return True if the view was modified, false otherwise.
   */
  bool DecorateView(CDasherView *pView);

  /**
   * Handle events from the event processing system
   * @param pEvent The event to be processed.
   */
  virtual void HandleEvent(Dasher::CEvent *pEvent); 

 private:

  /**
   * Helper function for generating (Or regenerating) a new chunk.
   * @warning This will destroy the previous chunk. Only use when you
   *          need to grab an entirely new chunk to display.
   */
  void GenerateChunk();

  /**
   * Get the distance of a given point (in Dasher Coordinates) from the origin.
   *
   * @param xCoord - the x coordinate of the point
   * @param yCoord - the y coordinate of the point
   * 
   */
  myint DistanceFromOrigin(myint xCoord, myint yCoord);

  /**
   * Searches for the dasher node under the current root that represents the desired string
   * @param text The string to search for
   * @return The node representing the string parameter
   */
   //Dasher::CDasherNode StringToNode(std::string sText); 
   
  /**
   * Pointer to the object that encapsulates the word generation
   * algorithm being used.
   */
  CWordGeneratorBase* m_pWordGenerator;
  
  /**
   * The last node the user typed.
   */
  CDasherNode *pLastTypedNode;

  /**
   * The next node (character) the user must type.
   */
  CDasherNode *pNextTargetNode;
  
  /**
   * The target string the user must type.
   */ 
  std::string m_sTargetString;

  /**
   * The current position in the string. 
   * Stored as a size_t to easily use substrings to determine what's been typed and what hasn't.
   */
  size_t m_stCurrentStringPos;

  /**
   * The dasher interface.
   */
  CDasherInterfaceBase *m_pInterface;
  
  /**
   * The target x coordinate for the crosshair to point to. 
   */
  myint m_iTargetX;

  /**
   * The target y coordinate for the crosshair to point to.
   */
  myint m_iTargetY;
  
/* ---------------------------------------------------------------------
 * Constants
 * ---------------------------------------------------------------------
 */

  /**
   * The color (in Dasher colors) to make the crosshair.
   */
  const int m_iCrosshairColor;
  /**
   * The number of points that the crosshair's lines pass through.
   */
  const int m_iCrosshairNumPoints;
  
  /**
   * The side length (in pixels) of the crosshair's square portion.
   */
  const int m_iCrosshairExtent;
  
  /**
   * The length of the lines comprising the crosshair's
   * "cross".
   */
  const int m_iCrosshairCrosslineLength;
  
  /**
   * The number of words displayed at once as a target for the user
   * to type.
   */
  const int m_iTargetChunkSize;

};
} 


#endif
