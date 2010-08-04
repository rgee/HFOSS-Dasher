#include "../Common/Common.h"

#include "EventHandler.h"
#include "DasherComponent.h"
#include "DasherInterfaceBase.h"
#include "Event.h"
#include <algorithm>
#include <iostream>

using namespace Dasher;

// Track memory leaks on Windows to the line that new'd the memory
#ifdef _WIN32
#ifdef _DEBUG
#define DEBUG_NEW new( _NORMAL_BLOCK, THIS_FILE, __LINE__ )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

#include <sstream>

void CEventHandler::InsertEvent(CEvent *pEvent) {

  //put the event at the end of the queue
  EnqueueEvent(pEvent);
  
  //if we are already dispatching events, don't do it again
  //this is necessary to keep recursive calls from removing
  //events from the queue while we iterate over it
  if(m_bIsDispatching) {
  return;
  }
  else {
    ProcessEventQueue();
  }
  
}

void CEventHandler::ProcessEventQueue() {
  
  //iterate over the event queue until it's empty
  while(!m_qEventQueue.empty()) {

    CEvent *currEvent = m_qEventQueue.front();
    m_qEventQueue.pop();
    
    m_pInterface->InterfaceEventHandler(currEvent);
  
    m_pInterface->ExternalEventHandler(currEvent);
    
    //entering the dispatching loop - no longer safe to modify m_vSpecificListeners
    m_bIsDispatching = true;
    
    //dispatch the event at the front of the queue to all registered listeners
    for(std::vector<CDasherComponent*>::const_iterator it = m_vSpecificListeners[currEvent->m_iEventType - 1].begin();
        it != m_vSpecificListeners[currEvent->m_iEventType - 1].end(); ++it)
      {
    (*it)->HandleEvent(currEvent);
    }
    
    //done dispatching this event - safe to modify m_vSpecificListeners
    m_bIsDispatching = false;
    
    //register all listeners that have been waiting to be added
    for(EvtListenerCollection::iterator it = m_vPendingSpecificReg.begin(); it != m_vPendingSpecificReg.end(); ++it)
    RegisterListener((*it).first, (*it).second);
    
    //unregister all that have been waiting to be removed
    for(EvtListenerCollection::iterator it = m_vPendingSpecificUnreg.begin(); it != m_vPendingSpecificUnreg.end(); ++it)
    UnregisterListener((*it).first, (*it).second);
    
    m_vPendingSpecificUnreg.clear();
    m_vPendingSpecificReg.clear();
  }  
      
}

void CEventHandler::EnqueueEvent(CEvent *pEvent) {
  m_qEventQueue.push(pEvent);
}

void CEventHandler::RegisterListener(CDasherComponent *pListener, int iEventType) {
  if(m_bIsDispatching) {
    // Add the listener to the pending set if events are being dispatched
    m_vPendingSpecificReg.push_back(std::make_pair(pListener, iEventType));
  } // Only try to add a new listener if it doesn't already exist in the Listener map
  else if((std::find(m_vSpecificListeners[iEventType - 1].begin(), m_vSpecificListeners[iEventType - 1].end(), pListener) == m_vSpecificListeners[iEventType - 1].end())) { 
    m_vSpecificListeners[iEventType - 1].push_back(pListener);
  }
}

void CEventHandler::RegisterListener(CDasherComponent *pListener) {
   
   for(int curEvtType = 1; curEvtType <= NUM_EVENTS; curEvtType++) {
    RegisterListener(pListener, curEvtType);
   }
}

void CEventHandler::UnregisterListener(CDasherComponent *pListener, int iEventType) {
  
  if(!m_bIsDispatching) {
    
    for(std::vector<CDasherComponent*>::iterator it = m_vSpecificListeners[iEventType - 1].begin(); it != m_vSpecificListeners[iEventType - 1].end(); ++it) {
      if((*it) == pListener) {
        m_vSpecificListeners[iEventType - 1].erase(it);
        break;
      }
    }
  }
  else {
    m_vPendingSpecificUnreg.push_back(std::make_pair(pListener, iEventType));
  }
}

void CEventHandler::UnregisterListener(CDasherComponent *pListener) {    
  
  for(int curEvtType = 1; curEvtType <= NUM_EVENTS; curEvtType++) {
    UnregisterListener(pListener, curEvtType);
   }
}
