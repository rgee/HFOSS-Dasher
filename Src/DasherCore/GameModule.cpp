#include "GameModule.h"
#include <sstream>

using namespace Dasher;

/**
 * Static members of non-integral type must be initialized outside of
 * class definitions.
 */
const int Dasher::CGameModule::vEvents[3] = {EV_EDIT, EV_GAME_NODE_DRAWN, EV_NO_GAME_NODE, }; 

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
                {
                    // Check if the typed character is correct
                  if(CharacterFound(evt)) {
                      // Check if we've reached the end of a chunk
                      if((m_iCurrentStringPos)  == m_sTargetString.length() - 2) {
                        GenerateChunk();

                      } else {
                          ++m_iCurrentStringPos;

                            DecorateDisplay();

                            m_pEventHandler->InsertEvent(
                              new CGameTargetChangedEvent(m_sTargetString.substr(m_iCurrentStringPos + 1, 1))
                            );
                      }
                    }
                    break;
                }
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
    }
    return;

}

void CGameModule::SetWordGenerator(CWordGeneratorBase *pWordGenerator) {
	m_pWordGenerator = pWordGenerator;
	GenerateChunk();
}

void CGameModule::reset() {

	m_sTargetString = "";
	m_iCurrentStringPos = -1;
	m_iTargetX = 0;
	m_iTargetY = 0;

	if(m_pGameDisplay)
		m_pGameDisplay->hide();

	if(m_pWordGenerator)
		delete m_pWordGenerator;

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

  std::string nextWord;

  for(int i = 0; i < m_iTargetChunkSize; i++) {
    nextWord = m_pWordGenerator->GetNextWord();
    
	//done with game text
	if(nextWord == "") {

      m_sTargetString = "";
	  m_pGameDisplay->alert("Congratulations! You've completed Dasher game mode!");
      m_pEventHandler->InsertEvent(new CGameModeCompleteEvent());

      return;
    } else {
      m_sTargetString += nextWord;
      m_sTargetString += " ";
    }
  }
  m_pEventHandler->InsertEvent(
      new CGameTargetChangedEvent(m_sTargetString.substr(0, 1))
      );

  DecorateDisplay();
}

void CGameModule::DecorateDisplay() {

	if(m_pGameDisplay == NULL) return;

	std::vector<std::string> colors = std::vector<std::string>();
	
	for(int pos = 0; pos < m_sTargetString.length(); pos++) {
		
		if(pos < m_iCurrentStringPos + 1) {	
			colors.push_back("blue");
		}
		else if(pos == m_iCurrentStringPos + 1) {
			colors.push_back("red");
		}
		else {
			colors.push_back("black");
		}
	}

	m_pGameDisplay->DisplayChunkText(m_sTargetString, colors);

}

void CGameModule::SetGameDisplay(CGameDisplay *pGameDisplay) {
  m_pGameDisplay = pGameDisplay;
}
