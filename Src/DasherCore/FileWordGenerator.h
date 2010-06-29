#ifndef __FileWordGenerator_h__
#define __FileWordGenerator_h__

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#include "WordGeneratorBase.h"
#include "DasherInterfaceBase.h"

namespace Dasher {
class CFileWordGenerator : public CWordGeneratorBase {
public:
  CFileWordGenerator(std::string path, int regen) 
      // This path is set manually for now debug/dev purposes. -rgee
    : m_sPath("~/Desktop/test_text.txt"),
      CWordGeneratorBase(regen) 
      {Generate();}
  CFileWordGenerator(std::string path)
    : m_sPath("~/Desktop/test_text.txt"),
      CWordGeneratorBase(0)
      {Generate();}
      
  virtual ~CFileWordGenerator() {
    m_sFileHandle.close();
  }
  
  
  /**
   * The generator function. In this implementation, it reads from a file to produce strings.
   * In this implementation, failure means file io has failed for some
   * reason.
   * @see CWordGeneratorBase::Generate
   */
  virtual bool Generate();

  /**
   * Returns the next word that was read
   * @return The next word in the word generator model if there is one.
   *          Otherwise, returns an empty string.
   */
  virtual std::string GetNextWord();


  /**
   * File path getter
   * @return The path to the file this generator reads from.
   */
  std::string GetPath();

  /**
   * File name getter
   * @return The actual name of the file being read from
   */
  std::string GetFilename();
  
  
  /**
   * Checks if there are any words left to produce.
   * @return true if there are words left, false otherwise
   */
  bool WordsLeft() { return m_bWordsLeft; }
private:
  /**
   * The string that has been generated.
   */
  std::string m_sGeneratedString;

  /**
   * The path to the file this generator reads from.
   */
  std::string m_sPath;

  /**
   * The position we're currently reading from in the string.
   */
  size_t m_uiPos;
  
  /**
   * Flag for whether there are words left in this model.
   */
  bool m_bWordsLeft;
  
  /**
   * The input stream that acts as the handle to the underlying file.
   */
  ifstream m_sFileHandle;
};
}

#endif
