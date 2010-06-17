#include "FileWordGenerator.h"

bool CFileWordGenerator::Generate() {
	if(!m_bWordsReady) {
		ifstream file_in;
		file_in.open(path.c_str());
		char buffer;
		while(file_in.good()) {
			buffer = file_in.get();
			m_sGeneratedString.append(buffer);
		}
		m_uiPos = 0;
	}
}

std::string CFileWordGenerator::GetPath() {
	return m_sPath; 
}
std::string CFileWordGenerator::GetFilename() {
	return m_sPath.substr(m_sPath.rfind("/"));
}

void CFileWordGenerator::SetSource(std::string newPath) {
	m_sPath = newPath;
	m_bWordsReady = false;
	Generate();
}

virtual std::string CFileWordGenerator::GetNextWord() {
	return m_sGeneratedString.substr(m_uiPos, m_sGeneratedString.find(" "));
}
