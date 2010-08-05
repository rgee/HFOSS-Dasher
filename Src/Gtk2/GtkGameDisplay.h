#include "../DasherCore/GameDisplay.h"
#include "dasher_editor.h"
#include <gtk/gtk.h>
#include <string>
#include <cstring>

class GtkGameDisplay : public Dasher::CGameDisplay {

public:


  /**
   * @param pContainer - the table that all of the
   *	widgets for the game display live in
   *	@param pEditor - reference to the dasher editor
   */ 
  GtkGameDisplay(GtkWidget *pContainer, DasherEditor *pEditor) :
    Dasher::CGameDisplay(),
    m_pContainer(pContainer),
    m_pEditor(pEditor)
  {
   m_pChunkDisplay = gtk_label_new(NULL);
   gtk_container_add(GTK_CONTAINER(m_pContainer), m_pChunkDisplay);
  }	 

  virtual void DisplayChunkText(std::string text, std::vector<std::string>& colors);

  virtual void Alert(std::string message);

  virtual void ClearEditor();

  virtual void SetVisible(bool visibility); 

private:

  /**
   * The Gtk table containing the game mode UI.
   */ 
  GtkWidget *m_pContainer;


 /**
  * The label object used to display the text.
  */
  GtkWidget *m_pChunkDisplay;
  DasherEditor *m_pEditor;

};
