#include "GtkGameDisplay.h"

using namespace std;

void GtkGameDisplay::DisplayChunkText(std::string text, std::vector<std::string> *colors) {

	std::string markup = "<span font-weight = \"bold\" font_size = \"xx-large\">";
	
	for(int pos = 0; pos < text.length(); pos++) {
		markup += "<span foreground = \""+(*colors)[pos]+"\">"+text.substr(pos, 1)+"</span>";
	}

	markup += "</span>";

	gtk_label_set_markup(GTK_LABEL(m_pChunkDisplay), markup.c_str());	
}
