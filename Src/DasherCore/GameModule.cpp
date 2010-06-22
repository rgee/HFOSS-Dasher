#include "GameModule.h"

using namespace Dasher;

void CGameModule::HandleEvent(Dasher::CEvent *pEvent) {

	switch(pEvent->m_iEventType)
	{
		case EV_EDIT:
        {	  
				CEditEvent* evt = static_cast<CEditEvent*>(pEvent);

			switch(evt->m_iEditType)
			{
				// Added a new character (Stepped one node forward)
				case 0:
					m_stCurrentStringPos++;
					//pLastTypedNode = StringToNode(evt->m_sText); 
					break;
				// Removed a character (Stepped one node back)
				case 1:
					break;
				default:
					break;
			}
			break;
		}
		case EV_TEXTDRAW:
			{
				CTextDrawEvent *evt = static_cast<CTextDrawEvent*>(pEvent);
				if(!m_sTargetString.substr(m_stCurrentStringPos+1, 1).compare(evt->m_sDisplayText)
				   && evt->m_iY < GetLongParameter(LP_OX)) { 
					evt->m_pDasherView->Screen2Dasher(evt->m_iX, evt->m_iY, m_iTargetX, m_iTargetY);
				  }
			}
			break;
        default:
		break;

	}
	return;

}

bool CGameModule::DecorateView(CDasherView *pView) {
   
    //set up the points for the arrow through - starts at the crosshair, ends at the target letter	
    myint x[2] = {GetLongParameter(LP_OX), m_iTargetX};
	myint y[2] = {GetLongParameter(LP_OY), m_iTargetY};
	
	pView->DasherPolyarrow(x, y, m_iArrowNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iArrowColor, m_dArrowSizeFactor);
	
    return true;
}

//CDasherNode CGameModule::StringToNode(std::string sText) {
//	
//}

std::string CGameModule::GetTypedTarget() {
	return m_sTargetString.substr(0, m_stCurrentStringPos - 1);
}

std::string CGameModule::GetUntypedTarget() {
	return m_sTargetString.substr(m_stCurrentStringPos);
}

