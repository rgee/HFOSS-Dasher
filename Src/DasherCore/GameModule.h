// GameModule.h

#ifndef GAME_MODULE_H
#define GAME_MODULE_H

#include <string>
using namespace std;

#include "DasherModule.h"
#include "DasherModel.h"
#include "DasherNode.h"
#include "DasherView.h"

namespace Dasher {
  class CDasherInterfaceBase;
}

namespace Dasher {

/*
 * This Dasher Module encapsulates all game mode logic. In game mode, users will be given
 * a target string to type as well as visual feedback for their progress and a helpful 
 * arrow to guide them in the right path through the dasher model.
 *
 * This class handles logic and drawing code with respect to the above.
 */
class CGameModule : public CDasherModule {
 pulbic:
  // I don't actually know what the type is supposed to be for this...it's not an input method or an input filter.
  // Maybe we should define a new one. I've labeled it 0 for now. - rgee
  CGameModule(Dasher::CEventHandler *pEventHandler, CSettingsStore *pSettingsStore, CDasherInterfaceBase *pInterface, ModuleID_t iID, const char *szName)
  : CDasherModule(pEventHandler, pSettingsStore, iID, 0, szName)

  // TODO: Methods will go here, clearly.

 private:
  //
  // The last node the user typed.
  //
  CDasherNode *pLastTypedNode;

  //
  // The next node the user must type
  //
  CDasherNode *pNextTargetNode;

  //
  // The current target string (That the user must type)
  //
  std::string targetString;

  //
  // The current position in the string. Stored as a size_t to easily use
  // substring to determine what's been typed and what hasn't.
  //
  size_t currentStringPos;
};
} 


#endif
