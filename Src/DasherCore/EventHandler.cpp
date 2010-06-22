
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
		// Loop through each specific event vector in the queue and transfer its elements to
    // the corresponding vector in the listener container
		for(int i = 0; i < iNUM_EVENTS; i++) {
			for(std::vector < CDasherComponent* >::const_iterator it = m_vSpecificListenerQueue[i].begin(); it != m_vSpecificListenerQueue[i].end(); ++it) {
				m_vSpecificListeners[i].push_back(*it);
			}
			m_vSpecificListenerQueue[i].clear();
		} 
	}
}

void CEventHandler::RegisterListener(CDasherComponent *pListener) {
	if((std::find(m_vSpecificListeners.begin(), m_vSpecificListeneres.end(), pListener)  == m_vListeners.end()) &&
		 (std::find(m_vSpecificListeners.begin(), m_vListenerQueue.end(), pListener) == m_vSpecificListenerQueue.end())) {
			if(!m_viInHandler > 0)
				for(ListenerMap::iterator it = m_vSpecificListeners.begin(); it != m_vSpecificListeners.end(); ++it) {
					(*it).push_back(pListener);
				}
			else
				for(std::vector<CDasherComponent*>>::iterator it = m_vSpecificListenerQueue.begin(); it != m_vSpecificListenerQueue.end(); ++it) {
					(*it).push_back(pListener);
				}
	}
	else {
		// Can't add the same listener twice	
	}
}

void CEventHandler::RegisterListener(CDasherComponent *pListener, int iEventType) {
	if((std::find(m_vSpecificListeners.begin(), m_vSpecificListeneres.end(), pListener)  == m_vListeners.end()) &&
	   (std::find(m_vSpecificListeners.begin(), m_vListenerQueue.end(), pListener) == m_vSpecificListenerQueue.end())) {	
		if(!m_vInHandler > 0)
			m_vSpecificListener[iEventType].push_back(pListener);
		else
			m_vSpecificListenerQueue[iEventType].push_back(pListener);
	}
	else {
		// Can't add the same listener twice 
	}
}

void CEventHandler::UnregisterListener(CDasherComponent *pListener, int iEventType) {
	for(std::vector<CDasherComponent*>::iterator it = m_vSpecificListeners[iEventType].begin(); it != m_vSpecificListeners[iEventType].end(); ++it) {
		if( (*it) == pListener)
			m_vSpecificListeners[iEventType].erase(it);
	}
}

void CEventHandler::UnregisterListener(CDasherComponent *pListener) {

  std::vector < CDasherComponent * >::iterator iFound;

	for(ListenerMap::iterator it = m_vSpecificListeners.begin(); it != m_vSpecificListeners.end(); ++it) { 
		iFound = std::find((*it).begin(), (*it).end(), pListener);
		if(iFound != (*it).end())
			(*it).erase(iFound);
	}
	for(ListenerMap::iterator it = m_vSpecificListenerQueue.begin(); it != m_vSpecificListenerQueue.end(); ++it) {
    iFound = std::find((*it).begin(), (*it).end(), pListener);
		if(iFound != (*it).end())
			(*it).erase(iFound);
  }
}
