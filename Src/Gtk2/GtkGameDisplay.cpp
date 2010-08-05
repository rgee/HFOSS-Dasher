#include "GtkGameDisplay.h"

using namespace std;

void GtkGameDisplay::DisplayChunkText(std::string text, std::vector<std::string>& colors) {

	std::string markup = "<span font-weight = \"bold\" font_size = \"xx-large\">";
	
	for(int pos = 0; pos < text.length(); pos++) {
		markup += "<span foreground = \""+ colors[pos]+"\">"+text.substr(pos, 1)+"</span>";
	}

	markup += "</span>";

	gtk_label_set_markup(GTK_LABEL(m_pChunkDisplay), markup.c_str());	
}

void GtkGameDisplay::Alert(std::string message) {
	
	GtkWidget *dialog =	gtk_message_dialog_new(NULL,
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_OTHER,
						GTK_BUTTONS_OK,
						message.c_str()
						);

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(GTK_WIDGET(dialog));
}

void GtkGameDisplay::ClearEditor() {
	dasher_editor_clear_text(m_pEditor);
}

void GtkGameDisplay::SetVisible(bool visibility) {
  if(!visibility) {
    gtk_label_set_markup(GTK_LABEL(m_pChunkDisplay), "");
  }
  gtk_widget_set_visible(m_pContainer, visibility);
}
