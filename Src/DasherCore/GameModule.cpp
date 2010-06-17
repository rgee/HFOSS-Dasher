#include "GameModule.h"

void CGameModule::HandleEvent(Dasher::CEvent *pEvent) {

	g_pLogger->Log("Inside event handler");	  
	
    switch(pEvent->m_iEventType)
	{
		case EV_EDIT:

			g_pLogger->Log("Capturing an edit event");	  
			
			switch(static_cast<CEditEvent*>(pEvent)->m_iEditType)
			{
				// Added a new character (Stepped one node forward)
				case 0:
					currentStringPos++;
					pLastTypedNode = StringToNode(pEvent->m_sText); 
					break;
				// Removed a character (Stepped one node back)
				case 1:
					break;
				default:
					break;
			}
			break;
        default:
			break;

	}
	return;
}

CDasherNode CGameModule::StringToNode(std::string sText) {
	
}

std::string CGameModule::GetTypedTarget() {
	return m_sTargetString.substr(0, m_stCurrentStringPos - 1);
}

std::string CGameModule::GetUntypedtarget() {
	return m_sTargetString.substr(m_stCurrentStringPos);
}
