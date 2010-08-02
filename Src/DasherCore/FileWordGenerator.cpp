#include "FileWordGenerator.h"
#include "DasherInterfaceBase.h"
using namespace Dasher;


bool CFileWordGenerator::GenerateForward() { 
  if(!m_sFileHandle.is_open()) {
    m_sFileHandle.open(m_sPath.c_str());
    m_vPreviousLines.push_back(m_sFileHandle.tellg());
  }
  if(m_sFileHandle.fail()) {
    throw std::runtime_error("File: " + m_sPath + " cannot be read.");
  }
  
  m_uiPos = 0;
  m_sGeneratedString.clear();
  
  if(m_sFileHandle.eof()) {
    return false;
  } else if(m_sFileHandle.good()) {
    std::getline(m_sFileHandle, m_sGeneratedString);
    m_vPreviousLines.push_back(m_sFileHandle.tellg());
    return true;
  }
}

bool CFileWordGenerator::GenerateReverse() {
  if(m_sFileHandle.fail()) {
    throw std::runtime_error("File: " + m_sPath + " cannot be read.");
  }

  m_sGeneratedString.clear();
  std::streampos sp = m_vPreviousLines.back();
  m_vPreviousLines.erase(m_vPreviousLines.end());

  if(sp == 0) {
    return false;
  } else {
    m_sFileHandle.seekg(sp);
    std::getline(m_sFileHandle, m_sGeneratedString);
    return true;
  }
}

std::string CFileWordGenerator::GetPath() {
  return m_sPath; 
}
std::string CFileWordGenerator::GetFilename() {
  return m_sPath.substr(m_sPath.rfind("/")+1);
}

std::string CFileWordGenerator::GetPreviousWord() {
  if(m_uiPos == 0){
    if(!GenerateReverse()) {
      return "";
    }
    
    size_t found = m_sGeneratedString.rfind(" ");
    m_uiPos = found;

    if(found == string::npos) {
      // We just take the entire string here for the following reasons
      //
      // If m_sGeneratedString is of the form "someword", we return that
      // word. If it's of the form "" for some reason, we indicate failure
      // by returning it.
      return m_sGeneratedString;
    } else {
      return m_sGeneratedString.substr(found);
    }
  } 
}

std::string CFileWordGenerator::GetNextWord() {
  if(m_uiPos >= m_sGeneratedString.length()) {
    // Attempt to reload the buffer.
    if(!GenerateForward()) {
      return "";
    }
  } 
  
  size_t found = m_sGeneratedString.substr(m_uiPos).find(" ");
  std::string result;
  
    // If there are no space characters.
  if(found != string::npos) 
  {
    result = m_sGeneratedString.substr(m_uiPos, found);
    m_uiPos += (found + 1);
  } else {
    result = m_sGeneratedString.substr(m_uiPos);
    m_uiPos = m_sGeneratedString.length();
  };
  
  return result;
}


