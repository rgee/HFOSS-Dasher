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
                case 1:
                    // Check if the typed character is correct
                    if(!evt->m_sText.compare(m_sTargetString.substr(m_stCurrentStringPos + 1, 1))) {
                      // Check if we've reached the end of a chunk
                      if((m_stCurrentStringPos + 1) == m_sTargetString.length()) {
                        GenerateChunk();
                      } else {
                        ++m_stCurrentStringPos;
                      }
                    }
                    break;
                // Removed a character (Stepped one node back)
                case 0:
                    g_pLogger->Log("Removed a character: " + evt->m_sText);
                    break;
                default:
                    break;
            }
            break;
        }
        case EV_TEXTDRAW:
        {
          CTextDrawEvent *evt = static_cast<CTextDrawEvent*>(pEvent);
          // Check whether the text that was drawn is the current target character.
          if(!m_sTargetString.substr(m_stCurrentStringPos + 1, 1).compare(evt->m_sDisplayText)) { 
                  
               //the x and y coordinates (in Dasher coords) of the target node
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
    screenint screenTargetX, screenTargetY;
    pView->Dasher2Screen(m_iTargetX, m_iTargetY, screenTargetX, screenTargetY);
    
    
    // Top Line
    screenint x[2] = {screenTargetX + m_iCrosshairExtent, screenTargetX - m_iCrosshairExtent};
    screenint y[2] = {screenTargetY - m_iCrosshairExtent, screenTargetY - m_iCrosshairExtent};
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
    
    // Right Line
    x = {screenTargetX - m_iCrosshairExtent, screenTargetX - m_iCrosshairExtent};
    y = {screenTargetY - m_iCrosshairExtent, screenTargetY + m_iCrosshairExtent};
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
    
    // Left Line
    x = {screenTargetX + m_iCrosshairExtent, screenTargetX + m_iCrosshairExtent};
    y = {screenTargetY - m_iCrosshairExtent, screenTargetY + m_iCrosshairExtent};
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);


    // Bottom Line
    x = {screenTargetX + m_iCrosshairExtent, screenTargetX - m_iCrosshairExtent};
    y = {screenTargetY + m_iCrosshairExtent, screenTargetY + m_iCrosshairExtent};
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
    
    // Vertical Crosshair Line
    x = {screenTargetX, screenTargetX};
    y = {screenTargetY + m_iCrosshairCrosslineLength, screenTargetY - m_iCrosshairCrosslineLength};
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);


    // Horizontal Crosshair Line
    x = {screenTargetX + m_iCrosshairCrosslineLength, screenTargetX - m_iCrosshairCrosslineLength};
    y = {screenTargetY, screenTargetY};
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
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

void CGameModule::GenerateChunk() {
  m_stCurrentStringPos = 0;
  m_sTargetString.clear();
  for(int i = 0; i < m_iTargetChunkSize; i++) {
    m_sTargetString += m_pWordGenerator->GetNextWord();
  }
}
