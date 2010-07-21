#ifndef __eventhandler_h__
#define __eventhandler_h__

#include <vector>
#include <queue>
#include "Event.h"

namespace Dasher {
  class CEventHandler;
  class CDasherComponent;
  class CDasherInterfaceBase;
  class CEvent;

}

/// \ingroup Core
/// @{
/**
 * This class handles the dispatch and management of events throughout Dasher.
 * Any class that derives from CDasherComponent can subscribe to events. These
 * events are enumerated in Event.h. All CDasherComponents are automatically
 * registered for their selected events on construction.
 * 
 * Components SHOULD specify exactly which events they're interested in
 * instead of omitting this information. This allows the event management
 * system to make optimal use of time in dispatching events. (i.e. cuts
 * down on unused event dispatching)
 */
class Dasher::CEventHandler {
  
public: 
  CEventHandler(Dasher::CDasherInterfaceBase * pInterface): m_iNUM_EVENTS(12), m_pInterface(pInterface) {

    m_bIsDispatching = false;
    
    // Initialize the event listener container (and queue) so we can add elements without
    // checking if the sub-vectors actually exist or not.
    for(int i = 0; i < m_iNUM_EVENTS; i++) {
      m_vSpecificListeners.push_back(std::vector<Dasher::CDasherComponent*>());
    }
  };

  ~CEventHandler() {

  };

 
  /**
   * TODO - when we refactor, rename this to DispatchEvent
   * Insert an event into the queue, then flush the queue
   * such that all event listeners are notified of the
   * events they subscribed to.
   * 
   * @warning If this is called from an Event Handler, (i.e. While events
   *          are being processed) the event is enqueued to be dispatched
   *          and NOT immediately dispatched.
   */ 
  void InsertEvent(Dasher::CEvent * pEvent);


  /**
   * Add an event to the event queue.
   * @param pEvent the event to add to the queue
   */
  void EnqueueEvent(Dasher::CEvent * pEvent);

  /**
   * Register a listener for all events.
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

private:
  /**
   * @var typedef vector<vector<CDasherComponent*>> EvtListenerTable
   * @brief A 2d vector of Dasher Components where each sub-vector corresponds
   * to a specific event. The contents of the sub-vectors are the components
   * that subscribe to this event.
   */
  typedef std::vector<std::vector<Dasher::CDasherComponent*> > EvtListenerTable;

  /**
   * @var typedef vector<pair<CDasherComponent*, int> > EvtListenerCollection
   * @brief A collection whose elements represent 1 to 1 associations between
   * Dasher Components and Dasher core event types
   */
  typedef std::vector<std::pair<Dasher::CDasherComponent*, int> > EvtListenerCollection;

  /**
   * Dispatch all the events in the event queue, and take
   * care of all the pending additions/deletions to m_vSpecificListeners
   * in between events. Empties m_qEventQueue, m_vPendingSpecificReg, and
   * m_vPendSpecificUnreg
   */ 
  void ProcessEventQueue();

  /**
   * The queue of events waiting to be dispatched. 
   */
  std::queue<Dasher::CEvent*> m_qEventQueue;

  /**
   * A 2-dimensional vector of listeners where each sub-vector represents
   * the listener for a specific event type (Defined in the event type enumeration
   * in Event.h). To access a vector for a specific event type, index into the top-level
   * vector using the event type as an index.
   */
  EvtListenerTable m_vSpecificListeners;

  /**
   * The set of specific listeners waiting to be registered
   * while m_vSpecificListeners is being iterated over.
  */
  EvtListenerCollection m_vPendingSpecificReg;
  
  /**
   * The set of specific listeners waiting to be unregistered
   * while m_vSpecificListeners is being iterated over.
  */
  EvtListenerCollection m_vPendingSpecificUnreg;


  Dasher::CDasherInterfaceBase * m_pInterface;

  /**
   * Boolean flag - true if we are in the middle of flushing
   * the event queue, false if not. Used to determine whether it
   * is safe to modify m_vSpecificListeners
   */ 
  bool m_bIsDispatching;

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
