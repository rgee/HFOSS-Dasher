
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

void CEventHandler::InsertEvent(CEvent *pEvent) {
	++m_iInHandler;

	for(std::vector<CdasherComponent*>::const_iterator it = m_vSpecificListeners[pEvent->m_iEventType].begin();
			it != m_vSpecificListeners[pEvent->m_iEventType].end();
		 ++it) 
	{
			(*it)->HandleEvent(pEvent);
	}

	m_pInterface->InterfaceEventHandler(pEvent);
	
	m_pInterface->ExternalEventHandler(pEvent);

	--m_iInHandler;

	if(m_iInHandler == 0) {
		
	}


//
//  // We may end up here recursively, so keep track of how far down we
//  // are, and only permit new handlers to be registered after all
//  // messages are processed.
//
//  // An alternative approach would be a message queue - this might actually be a bit more sensible
//  ++m_iInHandler;
//
//  // Loop through components and notify them of the event
//  for(std::vector < CDasherComponent * >::iterator iCurrent(m_vListeners.begin()); iCurrent != m_vListeners.end(); ++iCurrent) {
//    (*iCurrent)->HandleEvent(pEvent);
//  }
//
//  // Call external handler last, to make sure that internal components are fully up to date before external events happen
//
//  m_pInterface->InterfaceEventHandler(pEvent);
//
//  m_pInterface->ExternalEventHandler(pEvent);
//
//  --m_iInHandler;
//
//  if(m_iInHandler == 0) {
//    for(std::vector < CDasherComponent * >::iterator iCurrent(m_vListenerQueue.begin()); iCurrent != m_vListenerQueue.end(); ++iCurrent)
//      m_vListeners.push_back(*iCurrent); 
//    m_vListenerQueue.clear();
//  }
}

void CEventHandler::RegisterListener(CDasherComponent *pListener) {
	if((std::find(m_vSpecificListeners.begin(), m_vSpecificListeneres.end(), pListener)  == m_vListeners.end()) &&
		 (std::find(m_vSpecificListeners.begin(), m_vListenerQueue.end(), pListener) == m_vSpecificListenerQueue.end())) {
			if(!m_viInHandler > 0)
				for(std::vector<std::vector<CDasherComponent*>>::const_iterator it = m_vSpecificListeners.begin(); it != m_vSpecificListeners.end(); ++it) {
					it.push_back(pListener);
				}
			else
				for(std::vector<CDasherComponent*>>::cosnt_iterator it = m_vSpecificListenerQueue.begin(); it != m_vSpecificListenerQueue.end(); ++it) {
					it.push_back(pListener);
				}
	}
	else {
		// Can't add the same listener twice	
	}
// ===OLD EVENT CODE==
//  if((std::find(m_vListeners.begin(), m_vListeners.end(), pListener) == m_vListeners.end()) &&
//     (std::find(m_vListenerQueue.begin(), m_vListenerQueue.end(), pListener) == m_vListenerQueue.end())) {
//    if(!m_iInHandler > 0)
//      m_vListeners.push_back(pListener);
//    else
//      m_vListenerQueue.push_back(pListener);
//  }
//  else {
//    // Can't add the same listener twice
//  }
}

void CEventHandler::RegisterListener(CDasherComponent *pListener, int iEventType) {
	if((std::find(m_vSpecificListeners.begin(), m_vSpecificListeneres.end(), pListener)  == m_vListeners.end()) &&
	   (std::find(m_vSpecificListeners.begin(), m_vListenerQueue.end(), pListener) == m_vSpecificListenerQueue.end())) {	
		if(!m_vInHandler > 0)
			m_vSpecificListener[iEventType].push_back(pListener);
		else
			m_vSpecificListenerQueue[iEventType].push_back(pListener);
	}
}

void CEventHandler::UnregisterListener(CDasherComponent *pListener, int iEventType) {
	for(std::vector<CDasherComponent*>::const_iterator it = m_vSpecificListeners[iEventType].begin(); it != m_vSpecificListeners[iEventType].end(); ++it) {
		if( (*it) == pListener)
			m_vSpecificListeners[iEventType].erase(it);
	}
}

void CEventHandler::UnregisterListener(CDasherComponent *pListener) {

  std::vector < CDasherComponent * >::iterator iFound;

  iFound = std::find(m_vListeners.begin(), m_vListeners.end(), pListener);

  if(iFound != m_vListeners.end())
    m_vListeners.erase(iFound);

  iFound = std::find(m_vListenerQueue.begin(), m_vListenerQueue.end(), pListener);

  if(iFound != m_vListenerQueue.end())
    m_vListenerQueue.erase(iFound);
}
