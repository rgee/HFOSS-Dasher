#include "FileWordGenerator.h"

using namespace Dasher;

bool CFileWordGenerator::Generate() {
  g_pLogger->Log("About to open file");
  if(!m_bWordsReady) {
    std::ifstream file_in("test_text.txt");

      string buffer;
      while(!std::getline(file_in, buffer).eof())
      {
        m_sGeneratedString += buffer;
      }
      file_in.close();
      g_pLogger->Log(m_sGeneratedString);
    
    m_uiPos = 0;
  }
  return true;
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

std::string CFileWordGenerator::GetNextWord() {
  
  // Check if there are any spaces left in the file from the current
  // position to the end. If not, we know we are either right before
  // the last word or there are no more left.
  size_t found = m_sGeneratedString.substr(m_uiPos).find(" ");
  
  if(found != string::npos) {
    // If we're at the end of the string
    if((m_uiPos + 1) == m_sGeneratedString.length()) {
      return std::string("");
    }else {      
      // Grab the next word.
      std::string result = m_sGeneratedString.substr(m_uiPos, found);
      
      // Set the current position to 1 after the space character.
      // (i.e. The first letter of the next word.)
      m_uiPos = found + 1;
      
      return result;
    }
  }
  return std::string("");
}
