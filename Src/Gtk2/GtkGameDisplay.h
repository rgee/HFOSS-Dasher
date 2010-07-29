#include "../DasherCore/GameDisplay.h"
#include <gtk/gtk.h>
#include <string>
#include <cstring>

class GtkGameDisplay : public Dasher::CGameDisplay {

	public:

	 
	 /**
	  * @param pContainer - the table that all of the
	  *	widgets for the game display live in
	  */ 
	 GtkGameDisplay(GtkWidget *pContainer) :
		 Dasher::CGameDisplay(),
		 m_pContainer(pContainer)
	 {
		m_pChunkDisplay = gtk_label_new(NULL);
		gtk_container_add(GTK_CONTAINER(m_pContainer), m_pChunkDisplay);
		//gtk_misc_set_alignment(GTK_MISC(m_pChunkDisplay), 0, .5);
		gtk_widget_set_visible(m_pChunkDisplay, true);

	 }	 

	 virtual void DisplayChunkText(std::string text, std::vector<std::string> *colors);

	private:

	 /**
	  * The Gtk table containing the game mode UI.
	  */ 
	 GtkWidget *m_pContainer;
	 GtkWidget *m_pChunkDisplay;

};
