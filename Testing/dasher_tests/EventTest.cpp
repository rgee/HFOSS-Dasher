#include "gtest/gtest.h"
#include "../../Src/TestPlatform/MockInterfaceBase.h"
#include "../../Src/TestPlatform/MockSettingsStore.h"
#include "../../Src/DasherCore/EventHandler.h"

class DummyComponent : public Dasher::CDasherComponent {
	
	public:
		
		bool receivedEvent;
		
		DummyComponent(Dasher::CEventHandler* pEventHandler, Dasher::CSettingsStore* pSettingsStore) :
					   Dasher::CDasherComponent(pEventHandler, pSettingsStore) {
			receivedEvent = false;
		}
		
		void HandleEvent(Dasher::CEvent *pEvent) {
			receivedEvent = true;
		}
};

class EventTest : public ::Testing::Test {
	
	public:
	
		EventTest() {
			
			interfaceBase = new CMockInterfaceBase();
			settingsStore = new CMockSettingsStore();
			evtHandler = new Dasher::CEventHandler(interfaceBase);
		}
		
	protected:
	
		Dasher::CEventHandler *evtHandler;
		CMockInterfaceBase *interfaceBase;
		CMockSettingsStore *settingsStore;
};

TEST_F(EventTest, BasicHandling) {	
 
	DummyComponent *listener = new DummyComponent(evtHandler, settingsStore);
	evtHandler->RegisterListener(listener, 1);
	evtHandler->InsertEvent(new CParameterNotificationEvent(12));
	ASSERT_TRUE(listener->receievedEvent);
}
