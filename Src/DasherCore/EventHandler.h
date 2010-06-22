#ifndef __eventhandler_h__
#define __eventhandler_h__

#include <vector>

namespace Dasher {
  class CEventHandler;
  class CDasherComponent;
  class CDasherInterfaceBase;
  class CEvent;
}
/**
 * @var typedef vector<vector<CDasherComponent*>> ListenerMap
 * @brief A 2d vector of Dasher Components where each sub-vector corresponds
 *			  to a specific event. The contents of the sub-vectors are the components
 *				that subscribe to this event.
 */
typedef std::vector<std::vector<CDasherComponent*>> ListenerMap;

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

  void InsertEvent(Dasher::CEvent * pEvent)



	/**
   * Register a listener for ALL events. To specify one, pass it
   * as a second parameter.
   * @param pListener The Dasher Component to be registered for all events.
   */
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

	/**
   * Unregister a listener from ALL events.
   * @param pListener The Dasher Component to unregister from all events.
   */
  void UnregisterListener(Dasher::CDasherComponent * pListener);

protected:
  /**
   * A 2-dimensional vector of listeners where each sub-vector represents
   * the listener for a specific event type (Defined in the event type enumeration
   * in Event.h. To access a vector for a specific event type, index into the top-level
   * vector using the event type as an index.
   */
  ListenerMap m_vSpecificListeners;

	/**
	 * A container identical in structure to m_vSpecificListeners that holds Dasher Components
   * that have yet to be processed.
 	 */
  ListenerMap m_vSpecificListenerQueue;

  int m_iInHandler;

  Dasher::CDasherInterfaceBase * m_pInterface;

};
/// @}

#endif
