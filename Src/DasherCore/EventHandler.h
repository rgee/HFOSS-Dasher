#ifndef __eventhandler_h__
#define __eventhandler_h__

#include <vector>
#include "Event.h"

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

  /**
   * @var typedef vector<vector<CDasherComponent*>> ListenerMap
   * @brief A 2d vector of Dasher Components where each sub-vector corresponds
   * to a specific event. The contents of the sub-vectors are the components
   * that subscribe to this event.
   */
  typedef std::vector<std::vector<CDasherComponent*> > ListenerMap;

  /**
   * @var typedef vector<pair<CDasherComponent*, int> > ListenerQueue
   * @brief A queue whose elements represent 1 to 1 associations between
   * Dasher Components and Dasher core event types
   */
  typedef std::vector<std::pair<CDasherComponent*, int> > ListenerQueue;
  

  CEventHandler(Dasher::CDasherInterfaceBase * pInterface): m_iNUM_EVENTS(12), m_pInterface(pInterface) {
    m_iInHandler = 0;

    // Initialize the event listener container (and queue) so we can add elements without
    // checking if the sub-vectors actually exist or not.
    for(int i = 0; i < m_iNUM_EVENTS; i++) {
      m_vSpecificListeners.push_back(std::vector<CDasherComponent*>());
    }
  };

  ~CEventHandler() {

  };

  // Insert an event, which will be propagated to all listeners.

  void InsertEvent(Dasher::CEvent * pEvent);



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
   *        that represents the event to which you'd like to unsubscribe.
   */
  void UnregisterListener(Dasher::CDasherComponent * pListener, int iEventType);

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
   * The queue of listeners waiting to be registered with specific
   * events while InsertEvent is still processing. Used to prevent
   * m_vSpecificListeners from being modified while InsertEvent is
   * iterating over it.
  */
  ListenerQueue m_vSpecificListenerQueue;

  /**
   * The queue of "old style" listeners waiting to be registered
   * with all events while InsertEvent is still processing. Used
   * to prevent m_vSpecificListeners from being modified while
   * InsertEvent is iterating over it.
   */
  std::vector<CDasherComponent*> m_vGeneralListenerQueue;

  int m_iInHandler;

  Dasher::CDasherInterfaceBase * m_pInterface;


private:

  /**
 * @var m_iNUM_EVENTS
 * @brief The number of event types in the enumeration of Dasher events in Event.h. Had
 * to put it here to stop the compiler from complaining about multiple definitions. Please
 * keep this up to date with the number of items in the enumeration.
 * TODO - figure out a better solution to the compiler problem - this one is kind of clumsy
 */
  const int m_iNUM_EVENTS;


};
/// @}

#endif
