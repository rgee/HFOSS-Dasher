#include "GameModule.h"
#include <sstream>
using namespace Dasher;

/**
 * Static members of non-integral type must be initialized outside of
 * class definitions.
 */
const int Dasher::CGameModule::vEvents[3] = {EV_EDIT, EV_GAME_NODE_DRAWN, EV_NO_GAME_NODE}; 

void CGameModule::HandleEvent(Dasher::CEvent *pEvent) {

    switch(pEvent->m_iEventType)
    {
        case EV_NO_GAME_NODE:
        {
            CNoGameNodeEvent* evt = static_cast<CNoGameNodeEvent*>(pEvent);
            std::stringstream log_stream;
            log_stream << "First: " << evt->m_pNodes.first << "Second: " << evt->m_pNodes.first << endl;
            g_pLogger->Log(log_stream.str());
        }
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
                            m_pEventHandler->InsertEvent(
                              new CGameTargetChangedEvent(m_sTargetString.substr(m_iCurrentStringPos + 1, 1))
                            );
                      }
                    }
                    break;
                // Removed a character (Stepped one node back)
                case 0:
                    break;
                default:
                    break;
            }
            break;
        }
        case EV_GAME_NODE_DRAWN:
        {
          CGameNodeDrawEvent* evt = static_cast<CGameNodeDrawEvent*>(pEvent);
          m_bApproximating = true;
          evt->m_pView->Screen2Dasher(evt->m_iX, evt->m_iY, m_iTargetX, m_iTargetY);
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

bool CGameModule::DecorateView(CDasherView *pView) {
    screenint screenTargetX, screenTargetY;
    pView->Dasher2Screen(m_iTargetX, m_iTargetY, screenTargetX, screenTargetY);

    CDasherScreen::point points[2];

    // Top Line
    points[0].x = screenTargetX + m_iCrosshairExtent;
    points[1].x = screenTargetX - m_iCrosshairExtent;
    points[0].y = screenTargetY - m_iCrosshairExtent;
    points[1].y = screenTargetY - m_iCrosshairExtent;
    pView->ScreenPolyline(points, 2, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
    
    // Right Line
    points[0].x = screenTargetX - m_iCrosshairExtent;
    points[1].x = screenTargetX - m_iCrosshairExtent;
    points[0].y = screenTargetY - m_iCrosshairExtent;
    points[1].y = screenTargetY + m_iCrosshairExtent;
    pView->ScreenPolyline(points, 2, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
    
    // Left Line
    points[0].x = screenTargetX + m_iCrosshairExtent;
    points[1].x = screenTargetX + m_iCrosshairExtent;
    points[0].y = screenTargetY - m_iCrosshairExtent;
    points[1].y = screenTargetY + m_iCrosshairExtent;
    pView->ScreenPolyline(points, 2, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);


    // Bottom Line
    points[0].x = screenTargetX + m_iCrosshairExtent;
    points[1].x = screenTargetX - m_iCrosshairExtent;
    points[0].y = screenTargetY + m_iCrosshairExtent;
    points[1].y = screenTargetY + m_iCrosshairExtent;
    pView->ScreenPolyline(points, 2, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
    
    // Vertical Crosshair Line
    points[0].x = screenTargetX;
    points[1].x = screenTargetX;
    points[0].y = screenTargetY + m_iCrosshairCrosslineLength;
    points[1].y = screenTargetY - m_iCrosshairCrosslineLength;
    pView->ScreenPolyline(points, 2, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);


    // Horizontal Crosshair Line
    points[0].x = screenTargetX + m_iCrosshairCrosslineLength;
    points[1].x = screenTargetX - m_iCrosshairCrosslineLength;
    points[0].y = screenTargetY;
    points[1].y = screenTargetY;
    pView->ScreenPolyline(points, 2, GetLongParameter(LP_LINE_WIDTH)*4, m_iCrosshairColor);
    
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
  m_pEventHandler->InsertEvent(
    new CGameTargetChangedEvent(m_sTargetString.substr(0, 1))
  );
}
