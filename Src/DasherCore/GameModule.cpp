#include "GameModule.h"

void CGameModule::HandleEvent(Dasher::CEvent *pEvent) {
    switch(pEvent->m_iEventType)
	{
		case EV_EDIT:
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
		case EV_TEXTDRAW:
			CTextDrawEvent* evt = static_cast<CTextDrawEvent*>(pEvent);
			if(!m_sTargetString[m_stCurrentStringPos + 1].compare(evt->m_sDisplayText)) {
				myint X, Y;
				
				m_pView->DasherPolyarrow(Screen2Dasher(evt->m_iX, evt->m_iY, X, Y));
				DasherPolyarrow(X, Y, 20, GetLongParameter(LP_LINE_WIDTH)*4 135);
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

