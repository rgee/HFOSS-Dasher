#include "FileWordGenerator.h"

using namespace Dasher;


bool CFileWordGenerator::Generate() { 
  if(!m_sFileHandle.is_open())
    m_sFileHandle.open("test_text.txt");
  
   
  m_uiPos = 0;
  m_sGeneratedString.clear();
  if(m_sFileHandle.good()) {
    std::getline(m_sFileHandle, m_sGeneratedString);
    return true;
  } else {
    return false;
  }
}

std::string CFileWordGenerator::GetPath() {
  return m_sPath; 
}
std::string CFileWordGenerator::GetFilename() {
  return m_sPath.substr(m_sPath.rfind("/"));
}

std::string CFileWordGenerator::GetNextWord() {
  std::string result;
  
  // We are at the end of the buffer.
  if(m_uiPos >= m_sGeneratedString.length()) { 
    // Attempt to reload the buffer.
    if(!Generate())
    {
      // If file IO fails, return empty.
      result = "";
      return result;
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
  
  return result;
}
