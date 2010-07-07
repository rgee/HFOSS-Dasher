#include "gtest/gtest.h"
#include "../../Src/TestPlatform/MockInterfaceBase.h"
#include "../../Src/TestPlatform/MockSettingsStore.h"
#include "../../Src/DasherCore/EventHandler.h"
#include "../../Src/DasherCore/SettingsStore.h"

//A Dasher component that allows tests to easily determine whether
//or not it was notified of an event which it subscribed to
class DummyComponent : public Dasher::CDasherComponent {
	
	public:
		
		int evtCount;
		
		DummyComponent(Dasher::CEventHandler* pEventHandler, CSettingsStore* pSettingsStore) :
					   Dasher::CDasherComponent(pEventHandler, pSettingsStore) {
			evtCount = 0;
		}
		
		virtual void HandleEvent(Dasher::CEvent *pEvent) {
			evtCount++;
		}
};

//An extension of DummyComponent that fires a CStartEvent every time its HandleEvent is called
class RecursionComponent : public DummyComponent {
	
	public:
	
		RecursionComponent(Dasher::CEventHandler* pEventHandler, CSettingsStore* pSettingsStore) :
					   DummyComponent(pEventHandler, pSettingsStore) {
		}
		
		void HandleEvent(Dasher::CEvent *pEvent) {
			
			evtCount++;
			m_pEventHandler->InsertEvent(new Dasher::CStartEvent());
		}
};

//Test fixture - sets up the EventHandler, SettingsStore, and InterfaceBase instances.
class EventTest : public ::testing::Test {
	
	public:
	
		EventTest() {
			
			interfaceBase = new CMockInterfaceBase();
			evtHandler = new Dasher::CEventHandler(interfaceBase);
			settingsStore = new CMockSettingsStore(evtHandler);
		}
		
	protected:
	
		Dasher::CEventHandler *evtHandler;
		CMockInterfaceBase *interfaceBase;
		CMockSettingsStore *settingsStore;
};

//very basic test - subscribe 5 components, fire one event, and assert that they all were notified
/*TEST_F(EventTest, SingleEventBasic) {	
 
	DummyComponent *listener1 = new DummyComponent(evtHandler, settingsStore);
	DummyComponent *listener2 = new DummyComponent(evtHandler, settingsStore);
	DummyComponent *listener3 = new DummyComponent(evtHandler, settingsStore);
	DummyComponent *listener4 = new DummyComponent(evtHandler, settingsStore);
	DummyComponent *listener5 = new DummyComponent(evtHandler, settingsStore);
	
	evtHandler->RegisterListener(listener1, EV_PARAM_NOTIFY);
	evtHandler->RegisterListener(listener2, EV_PARAM_NOTIFY);
	evtHandler->RegisterListener(listener3, EV_PARAM_NOTIFY);
	evtHandler->RegisterListener(listener4, EV_PARAM_NOTIFY);
	evtHandler->RegisterListener(listener5, EV_PARAM_NOTIFY);
	
	evtHandler->InsertEvent(new CParameterNotificationEvent(12));
	
	ASSERT_EQ(listener1->evtCount, 1);
	ASSERT_EQ(listener2->evtCount, 1);
	ASSERT_EQ(listener3->evtCount, 1);
	ASSERT_EQ(listener4->evtCount, 1);
	ASSERT_EQ(listener5->evtCount, 1);
}

//stress test - register a lot of listeners, fire a lot of events, and assert that 
//everything was notified without crashing
TEST_F(EventTest, StressTestBasic) {
	
	std::vector<DummyComponent*> components;
	
	for(int c = 0; c < 10000; c++) {
		
		DummyComponent *newComponent = new DummyComponent(evtHandler, settingsStore);
		evtHandler->RegisterListener(newComponent, EV_PARAM_NOTIFY);
	}
	
	for(int c = 0; c < 10000; c++) {
		evtHandler->InsertEvent(new CParameterNotificationEvent(0));
	}
	
	for(std::vector<DummyComponent*>::iterator iter = components.begin(); iter != components.end(); ++iter) {
		ASSERT_EQ((*iter)->evtCount, 10000);
	}
}*/

TEST_F(EventTest, RecursionTestBasic) {
	
	RecursionComponent *rec1 = new RecursionComponent(evtHandler, settingsStore);
	RecursionComponent *rec2 = new RecursionComponent(evtHandler, settingsStore);
	DummyComponent *listener = new DummyComponent(evtHandler, settingsStore);
	
	evtHandler->RegisterListener(rec1, EV_PARAM_NOTIFY);
	evtHandler->RegisterListener(rec2, EV_PARAM_NOTIFY);
	evtHandler->RegisterListener(listener, EV_START);
	
	evtHandler->InsertEvent(new Dasher::CParameterNotificationEvent(0));
	
	ASSERT_EQ(rec1->evtCount, 1);
	ASSERT_EQ(rec2->evtCount, 1);
	ASSERT_EQ(listener->evtCount, 2);
}
