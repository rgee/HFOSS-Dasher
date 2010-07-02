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
                    if(CharacterFound(evt)) {
                      // Check if we've reached the end of a chunk
                      if((m_iCurrentStringPos)  == m_sTargetString.length() - 2) {
                        GenerateChunk();
                      } else {
                          ++m_iCurrentStringPos;
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
          if(CharacterFound(evt)) { 
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

bool CGameModule::CharacterFound(CEditEvent* pEvent) {
  return !pEvent->m_sText.compare(m_sTargetString.substr(m_iCurrentStringPos + 1, 1));
}

bool CGameModule::CharacterFound(CTextDrawEvent* pEvent) {
  return !pEvent->m_sDisplayText.compare(m_sTargetString.substr(m_iCurrentStringPos + 1, 1));
}

bool CGameModule::DecorateView(CDasherView *pView) {
    screenint screenTargetX, screenTargetY;
    pView->Dasher2Screen(m_iTargetX, m_iTargetY, screenTargetX, screenTargetY);
    
    screenint x[2];
    screenint y[2];
    
    // Top Line
    x[0] = screenTargetX + m_iCrosshairExtent;
    x[1] = screenTargetX - m_iCrosshairExtent;
    y[0] = screenTargetY - m_iCrosshairExtent;
    y[1] = screenTargetY - m_iCrosshairExtent;
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
    
    // Right Line
    x[0] = screenTargetX - m_iCrosshairExtent;
    x[1] = screenTargetX - m_iCrosshairExtent;
    y[0] = screenTargetY - m_iCrosshairExtent;
    y[1] = screenTargetY + m_iCrosshairExtent;
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
    
    // Left Line
    x[0] = screenTargetX + m_iCrosshairExtent;
    x[1] = screenTargetX + m_iCrosshairExtent;
    y[0] = screenTargetY - m_iCrosshairExtent;
    y[1] = screenTargetY + m_iCrosshairExtent;
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);


    // Bottom Line
    x[0] = screenTargetX + m_iCrosshairExtent;
    x[1] = screenTargetX - m_iCrosshairExtent;
    y[0] = screenTargetY + m_iCrosshairExtent;
    y[1] = screenTargetY + m_iCrosshairExtent;
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
    
    // Vertical Crosshair Line
    x[0] = screenTargetX;
    x[1] = screenTargetX;
    y[0] = screenTargetY + m_iCrosshairCrosslineLength;
    y[1] = screenTargetY - m_iCrosshairCrosslineLength;
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);


    // Horizontal Crosshair Line
    x[0] = screenTargetX + m_iCrosshairCrosslineLength;
    x[1] = screenTargetX - m_iCrosshairCrosslineLength;
    y[0] = screenTargetY;
    y[1] = screenTargetY;
    pView->ScreenPolyline(x, y, m_iCrosshairNumPoints, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
    pView->DrawText(m_sTargetString, 400, 17, m_iFontSize, m_iCrosshairColor);
    pView->DrawText(GetTypedTarget(), 400, 20, m_iFontSize, m_iCrosshairColor - 20);
    return true;
}


std::string CGameModule::GetTypedTarget() {
    return ((m_iCurrentStringPos == -1) ?
            "" : m_sTargetString.substr(0, m_iCurrentStringPos + 1));
}

std::string CGameModule::GetUntypedTarget() {
  return m_sTargetString.substr(m_iCurrentStringPos + 1);
}

void CGameModule::GenerateChunk() {
  m_iCurrentStringPos = -1;
  m_sTargetString.clear();
  for(int i = 0; i < m_iTargetChunkSize; i++) {
    m_sTargetString += m_pWordGenerator->GetNextWord();
    m_sTargetString += " ";
  }
}
