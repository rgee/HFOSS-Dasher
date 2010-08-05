#ifndef _GameDisplay_H_
#define _GameDisplay_H_

#include <vector>
#include <string>

using namespace std;

namespace Dasher {

/**
 * A class which allows GameModule to display formatted
 * information in a separate area on the screen. Currently,
 * the only information it can display is a color coded
 * representation of the current text chunk (see DispayChunkText).
 * There is a lot of room for extending this to support new features,
 * different types of games, etc.
 */ 
class CGameDisplay {
	
  public:
		
    CGameDisplay() {}

	/**
	 TODO: Improve this documentation

	 * Display a colored sequence of characters in the game display window.
	 * @param text the sequence of characters
	 * @param colors the color to give each index of text
	 */ 
	virtual void DisplayChunkText(std::string text, std::vector<std::string>& colors) = 0;

	/**
	 * Display a dialog alerting the user about something
	 * related to game mode.
	 */ 
	virtual void Alert(std::string message) = 0;

	/**
	 * Clear the dasher editor, as is appropriate when starting
	 * or ending game mode.
	 */ 
	virtual void ClearEditor() = 0;

  /**
   * Sets the visibility of the Game Display widget.
   */
  virtual void SetVisible(bool visibility) = 0;
};

}

#endif
