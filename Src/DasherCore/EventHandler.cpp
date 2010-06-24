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

	for(std::vector<CDasherComponent*>::const_iterator it = m_vSpecificListeners[pEvent->m_iEventType].begin();
			it != m_vSpecificListeners[pEvent->m_iEventType].end();
		 ++it) 
	{
			(*it)->HandleEvent(pEvent);
	}

	m_pInterface->InterfaceEventHandler(pEvent);
	
	m_pInterface->ExternalEventHandler(pEvent);

	--m_iInHandler;

	if(m_iInHandler == 0) {
	    
		//loop through the queue of specific listeners waiting to be registered and register them
		for(ListenerQueue::iterator it = m_vSpecificListenerQueue.begin(); it != m_vSpecificListenerQueue.end(); ++it) {
			RegisterListener((*it).first, (*it).second); 
		} 
	}
}

void CEventHandler::RegisterListener(CDasherComponent *pListener) {

    if(std::find(m_vGeneralListenerQueue.begin(), m_vGeneralListenerQueue.end(), pListener) == m_vGeneralListenerQueue.end()) {
		return;
	}
	else {

		for(ListenerMap::iterator it = m_vSpecificListeners.begin(); it != m_vSpecificListeners.end(); ++it) {

			if((std::find((*it).begin(), (*it).end(), pListener) == (*it).end())) {
					if(m_iInHandler == 0) {
						(*it).push_back(pListener);
					}
					else {
						m_vGeneralListenerQueue.push_back(pListener);
					}
			}
			else {
				// Can't add the same listener twice	
			}
		}
   }
}

void CEventHandler::RegisterListener(CDasherComponent *pListener, int iEventType) {

	if((std::find(m_vSpecificListeners[iEventType].begin(), m_vSpecificListeners[iEventType].end(), pListener)  == m_vSpecificListeners[iEventType].end())) {	
		if(m_iInHandler == 0)
			m_vSpecificListeners[iEventType].push_back(pListener);
		else
			m_vSpecificListenerQueue.push_back(std::make_pair(pListener, iEventType));
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

    std::vector < CDasherComponent * >::iterator mapFound;

	for(ListenerMap::iterator it = m_vSpecificListeners.begin(); it != m_vSpecificListeners.end(); ++it) { 
		mapFound = std::find((*it).begin(), (*it).end(), pListener);
		if(mapFound != (*it).end())
			(*it).erase(mapFound);
	}

	std::vector < CDasherComponent * >::iterator queueFound = std::find(m_vGeneralListenerQueue.begin(), m_vGeneralListenerQueue.end(), pListener);
	if(queueFound != m_vGeneralListenerQueue.end())
			m_vGeneralListenerQueue.erase(queueFound);

	for(ListenerQueue::iterator it = m_vSpecificListenerQueue.begin(); it != m_vSpecificListenerQueue.end(); ++it) {
		if((*it).first == pListener) {
			it = m_vSpecificListenerQueue.erase(it);
		}
	}
  
}
