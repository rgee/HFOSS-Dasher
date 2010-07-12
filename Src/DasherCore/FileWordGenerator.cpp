#include "FileWordGenerator.h"

using namespace Dasher;


bool CFileWordGenerator::Generate() { 
  if(!m_sFileHandle.is_open())
    m_sFileHandle.open(m_sPath.c_str());
  
   
  m_uiPos = 0;
  m_sGeneratedString.clear();
  if(m_sFileHandle.eof()) {
    m_sCurrentWord = "";
    return false;
  } else if(m_sFileHandle.good()) {
    std::getline(m_sFileHandle, m_sGeneratedString);
    FindNextWord();
    return true;
  } else {
    return false;
  }
}

std::string CFileWordGenerator::GetPath() {
  return m_sPath; 
}
std::string CFileWordGenerator::GetFilename() {
  return m_sPath.substr(m_sPath.rfind("/")+1);
}

std::string CFileWordGenerator::GetNextWord() {
  std::string result = m_sCurrentWord;
  FindNextWord();
  
  return result;
}

void CFileWordGenerator::FindNextWord() {
  std::string result;
  
  // We are at the end of the buffer.
  if(m_uiPos >= m_sGeneratedString.length()) { 
    // Attempt to reload the buffer.
    if(!Generate())
    {
      // If file IO fails, set the current word to empty.
      result = "";
      m_sCurrentWord =  result;
      return;
    }
  } 
  
  size_t found = m_sGeneratedString.substr(m_uiPos).find(" ");
  
  // If there are no space characters.
  if(found != string::npos) 
  {
    result = m_sGeneratedString.substr(m_uiPos, found);

    m_uiPos += (found + 1);
  } else {
    result = m_sGeneratedString.substr(m_uiPos);
  }
  m_sCurrentWord = result;
}

