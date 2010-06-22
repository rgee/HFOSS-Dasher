#ifndef __eventhandler_h__
#define __eventhandler_h__

#include <vector>

namespace Dasher {
  class CEventHandler;
  class CDasherComponent;
  class CDasherInterfaceBase;
  class CEvent;
}

/// \ingroup Core
/// @{
class Dasher::CEventHandler {
public:

  CEventHandler(Dasher::CDasherInterfaceBase * pInterface):m_pInterface(pInterface) {
    m_iInHandler = 0;

		// Initialize the event listener container (and queue) so we can add elements without
		// checking if the sub-vectors actually exist or not.
		for(int i = 0; i < iNUM_EVENTS; i++) {
    	m_vSpecificListeners.push_back(new Vector<CDasherComponent*>());
		}

		for(int i = 0; it < iNUM_EVENTS; i++) {
			m_vSpecificListenerQueue.push_back(new Vector<CDasherComponent*>());
		}
  };

  ~CEventHandler() {

  };

  // Insert an event, which will be propagated to all listeners.

  void InsertEvent(Dasher::CEvent * pEvent);

  // (Un)register a listener with the event handler.

  void RegisterListener(Dasher::CDasherComponent * pListener);

  /**
   * Register a listener to listen for specific events.
   * @param pListener A pointer to the dasher component that will listen for events
   * @param iEventType An integer defined in the event type enumeration in Event.h
	 *        that represents the event to which you'd like to subscribe.
   */
  void RegisterListener(Dasher::CDasherComponent * pListener, int iEventType);

	/**
	 * Unregister a listener from a specific event.
	 * @param pListener A pointer tot he dasher component to be unregistered
	 * @param iEventType An integer defined in the event type enumeration in Event.h
   *	      that represents the event to which you'd like to unsubscribe.
	 */
	void UnregisterListener(Dasher::CDashercomponent * pListener, int iEventType);
  void UnregisterListener(Dasher::CDasherComponent * pListener);

protected:

  // Vector containing all currently registered listeners.

  std::vector < Dasher::CDasherComponent * >m_vListeners;
  std::vector < Dasher::CDasherComponent * >m_vListenerQueue;



  /**
   * A 2-dimensional vector of listeners where each sub-vector represents
   * the listener for a specific event type (Defined in the event type enumeration
   * in Event.h. To access a vector for a specific event type, index into the top-level
   * vector using the event type as an index.
   */
  std::vector < std::vector < Dasher::CDasherComponent * > > m_vSpecificListeners;

	std::vector < std::vector < Dasher::CDasherComponent * > > m_vSpecificListenerQueue;

  int m_iInHandler;

  Dasher::CDasherInterfaceBase * m_pInterface;

};
/// @}

#endif
